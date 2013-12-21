////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2013 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <SpaceInvaders/Controller/Controller.hpp>
#include <SpaceInvaders/Controller/Powerups.hpp>
#include <SpaceInvaders/Factory/DebugEntityFactory.hpp>
#include <SpaceInvaders/View/AbstractView.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Controller::Controller(View::AbstractView* view, unsigned int difficulty) :
            m_difficulty      (difficulty),
            m_view            (view),
            m_factory         (new DebugEntityFactory()),
            m_playerController(m_factory->createPlayer(difficulty), view),
            m_enemyController (m_factory->createEnemies(difficulty), view),
            m_wallController  (m_factory->createWalls(difficulty), view)
        {
            // We are responsible for creating the bullets (because it involves a factory)
            m_playerController.addObserver(std::bind(&Controller::createBullet, this, std::placeholders::_1), Event::Type::GunFired);
            m_enemyController.addObserver(std::bind(&Controller::createBullet, this, std::placeholders::_1), Event::Type::GunFired);

            // We will also be handling the powerups
            m_enemyController.addObserver(std::bind(&Controller::powerupActivated, this, std::placeholders::_1), Event::Type::PowerupActivated);
            m_powerupController.addObserver(std::bind(&Controller::powerupDeactivated, this, std::placeholders::_1), Event::Type::PowerupDeactivated);

            // We need to know when the enemy moves (if they get too low then the game should end) and when it dies (to keep track of the score)
            for (auto& enemy : m_enemyController.getEnemies())
            {
                enemy->addObserver(std::bind(&Controller::enemyMoved, this, std::placeholders::_1), Event::Type::PositionChanged);
                enemy->addObserver(std::bind(&Controller::scoreChanged, this, std::placeholders::_1), Event::Type::ScoreChanged);
            }

            // Find out when the player dies
            m_playerController.addObserver(std::bind(&Controller::livesChanged, this, std::placeholders::_1), Event::Type::LivesChanged);

            // Let the view know when the player dies
            addObserver(std::bind(&View::AbstractView::livesChanged, view, std::placeholders::_1), Event::Type::LivesChanged);

            // When the game ends, reset the contoller
            addObserver(std::bind(&Controller::gameOver, this, std::placeholders::_1), Event::Type::GameOver);

            // Let anyone who is interested know the default amount of lives of the player
            Event event{Event::Type::LivesChanged, m_playerController.getPlayer().get()};
            event.lives = dynamic_cast<Model::PlayerEntity*>(m_playerController.getPlayer().get())->getLives();
            notifyObservers(event);

            // The enemies are not allowed to get below the defence walls
            for (auto& wall : m_wallController.getWalls())
            {
                if (wall->getPosition().y + wall->getSize().y > m_lowestEnemyPosition)
                    m_lowestEnemyPosition = wall->getPosition().y + wall->getSize().y;
            }

            // If there are no defence walls then the enemies can get until the player
            if (m_lowestEnemyPosition == 0)
                m_lowestEnemyPosition = m_playerController.getPlayer()->getPosition().y;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::update(const sf::Time& elapsedTime)
        {
            m_playerController.update(elapsedTime);
            m_enemyController.update(elapsedTime);
            m_powerupController.update(elapsedTime);

            updateBullets(elapsedTime);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::updateBullets(const sf::Time& elapsedTime)
        {
            for (unsigned int i = 0; i < m_bullets.size();)
            {
                // Update the position of the bullet
                m_bullets[i]->setPosition(Vector2f{m_bullets[i]->getPosition().x,
                                                   m_bullets[i]->getPosition().y + (m_bullets[i]->getSpeed() * elapsedTime.asSeconds())});

                // Check if the bullet collides with one of the entities
                if (m_bullets[i]->getSpeed() < 0)
                {
                    if ((m_wallController.checkCollision(m_bullets[i])) || (m_enemyController.checkCollision(m_bullets[i])))
                    {
                        // If all emenies are dead then the level is over
                        if (m_enemyController.getEnemies().empty())
                        {
                            notifyObservers(Event{Event::Type::LevelComplete});
                            return;
                        }

                        m_bullets[i]->destroy();
                        m_bullets.erase(m_bullets.begin()+i);
                        continue;
                    }
                }
                else if (m_bullets[i]->getSpeed() > 0)
                {
                    if ((m_playerController.checkCollision(m_bullets[i])) || (m_wallController.checkCollision(m_bullets[i])))
                    {
                        if (m_bullets.empty())
                            break;

                        m_bullets[i]->destroy();
                        m_bullets.erase(m_bullets.begin()+i);
                        continue;
                    }
                }

                // Remove the bullet once it leaves the screen
                if ((m_bullets[i]->getPosition().y > SCREEN_HEIGHT) || (m_bullets[i]->getPosition().y + m_bullets[i]->getSize().y < 0))
                {
                    m_bullets[i]->destroy();
                    m_bullets.erase(m_bullets.begin()+i);
                    continue;
                }
                else
                    i++;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::livesChanged(const Event& event)
        {
            // Reset the position of the player
            event.entity->setPosition(m_factory->createPlayer(m_difficulty)->getPosition());

            // Remove all bullets
            for (auto& bullet : m_bullets)
                bullet->destroy();
            m_bullets.clear();

            // Notify the others about the event
            notifyObservers(event);

            // Stop the game when there are no more lives left
            if (event.lives == 0)
                notifyObservers(Event{Event::Type::GameOver});
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::powerupActivated(const Event& event)
        {
            switch (event.powerup)
            {
                case PowerupType::SpeedBoost:
                {
                    m_powerupController.addPowerup(PowerupPtr{new SpeedChangePowerup{m_playerController.getPlayer(), sf::seconds(10), 2.0f}});

                    m_view->setMessage("SpeedBoost");
                    break;
                }
                case PowerupType::Slowdown:
                {
                    for (auto& enemy : m_enemyController.getEnemies())
                        m_powerupController.addPowerup(PowerupPtr{new SpeedChangePowerup{enemy, sf::seconds(5), 0.33f}});

                    m_view->setMessage("Slowdown");
                    break;
                }
                case PowerupType::RapidFire:
                {
                    m_powerupController.addPowerup(PowerupPtr{new FireRatePowerup{m_playerController.getPlayer(), sf::seconds(3), 4.0f}});

                    m_view->setMessage("RapidFire");
                    break;
                }
                default:
                    throw std::logic_error("Unknown powerup type.");
            };
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::powerupDeactivated(const Event&)
        {
            m_view->removeMessage();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::createBullet(const Event& event)
        {
            Model::Gun gun = dynamic_cast<Model::AttackingEntity*>(event.entity)->getGun();

            BulletPtr bullet = BulletPtr{new Model::BulletEntity(gun.getBulletFilename(), gun.getBulletSpeed())};
            bullet->setSize(gun.getBulletSize());
            bullet->setPosition(Vector2f{event.entity->getPosition().x + ((event.entity->getSize().x - bullet->getSize().x) / 2.0f),
                                         event.entity->getPosition().y + ((event.entity->getSize().y - bullet->getSize().y) / 2.0f)});
            m_view->addEntity(bullet);
            m_bullets.push_back(bullet);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::enemyMoved(const Event& event)
        {
            // If one of the enemies gets too low then the game should end
            if (event.position.y + event.entity->getSize().y > m_lowestEnemyPosition)
                notifyObservers(Event{Event::Type::GameOver});
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::scoreChanged(const Event& event)
        {
            Event newEvent{Event::Type::ScoreChanged, event.entity};
            newEvent.score = event.score;
            notifyObservers(newEvent);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Controller::gameOver(const Event&)
        {
            m_bullets.clear();
            m_wallController.getWalls().clear();
            m_enemyController.getEnemies().clear();
            m_playerController.getPlayer() = nullptr;
            m_powerupController.getPowerups().clear();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
