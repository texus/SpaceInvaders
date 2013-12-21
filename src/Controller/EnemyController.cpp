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


#include <SpaceInvaders/Controller/EnemyController.hpp>
#include <SpaceInvaders/View/AbstractView.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        EnemyController::EnemyController(AttackingEntityList enemies, View::AbstractView* view) :
            m_enemies(enemies)
        {
            for (auto& enemy : m_enemies)
                view->addEntity(enemy);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void EnemyController::update(const sf::Time& elapsedTime)
        {
            float elapsedSeconds = elapsedTime.asSeconds();

            // Check if the movement is vertical
            if (m_movingDown)
            {
                int reverseMovement = 0;

                if (!m_enemies.empty())
                    m_movingDownDistance += std::abs(m_enemies[0]->getSpeed()) * elapsedSeconds;

                // Move all enemies depending on their speed
                for (auto& enemy : m_enemies)
                {
                    float distanceDiff = std::abs(enemy->getSpeed()) * elapsedSeconds;

                    if (m_movingDownDistance > ENEMY_CHANGE_TOP_DIFF)
                        reverseMovement = m_movingDownDistance - ENEMY_CHANGE_TOP_DIFF;

                    enemy->setPosition(Vector2f{enemy->getPosition().x, enemy->getPosition().y + distanceDiff});

                    // If there are no more enemies then the game was ended
                    if (m_enemies.empty())
                        return;
                }

                // If one of the enemies has gone too far then revert part of the movement and start moving in another direction
                if (reverseMovement != 0)
                {
                    m_movingDown = false;

                    for (auto& enemy : m_enemies)
                    {
                        enemy->setPosition(Vector2f{enemy->getPosition().x, enemy->getPosition().y - reverseMovement});
                        enemy->setSpeed(-enemy->getSpeed());
                    }
                }
            }
            else // The movement is horizontal
            {
                int reverseMovement = 0;

                // Move all enemies depending on their speed
                for (auto& enemy : m_enemies)
                {
                    float distanceDiff = enemy->getSpeed() * elapsedSeconds;

                    if (enemy->getSpeed() > 0)
                    {
                        if (enemy->getPosition().x + enemy->getSize().x + distanceDiff > SCREEN_WIDTH)
                            reverseMovement = enemy->getPosition().x + enemy->getSize().x + distanceDiff - SCREEN_WIDTH;
                    }
                    else // The enemies are moving to the left
                    {
                        if (enemy->getPosition().x + distanceDiff < 0)
                            reverseMovement = enemy->getPosition().x + distanceDiff;
                    }

                    enemy->setPosition(Vector2f{enemy->getPosition().x + distanceDiff, enemy->getPosition().y});
                }

                // If one of the enemies has gone too far then revert part of the movement and start moving in another direction
                if (reverseMovement != 0)
                {
                    m_movingDown = true;
                    m_movingDownDistance = 0;

                    for (auto& enemy : m_enemies)
                        enemy->setPosition(Vector2f{enemy->getPosition().x - reverseMovement, enemy->getPosition().y});
                }
            }

            // Only the bottom enemy of every row can fire
            std::map<int, AttackingEntityPtr> fireCapableEnemies;
            for (auto& enemy : m_enemies)
            {
                if (fireCapableEnemies[enemy->getPosition().x] == nullptr)
                    fireCapableEnemies[enemy->getPosition().x] = enemy;
                else
                {
                    if (fireCapableEnemies[enemy->getPosition().x]->getPosition().y < enemy->getPosition().y)
                        fireCapableEnemies[enemy->getPosition().x] = enemy;
                }
            }

            // There has to be at least one enemy left to fire
            if (!fireCapableEnemies.empty())
            {
                // Find the enemy that will fire
                auto it = fireCapableEnemies.begin();
                std::advance(it, std::uniform_int_distribution<decltype(fireCapableEnemies.size())>{0, fireCapableEnemies.size()-1}(generator));

                // Check if one of the enemies should fire
                m_fireChance += (it->second->getGun().getChanceIncrease() * elapsedSeconds);
                if (m_fireChance * elapsedSeconds > std::uniform_real_distribution<float>{0.1f, 100.0f}(generator))
                {
                    m_fireChance = 0;

                    // Fire the bullet
                    if (it->second->getGun().tryToFire())
                        notifyObservers(Event{Event::Type::GunFired, it->second.get()});
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool EnemyController::checkCollision(EntityPtr entity)
        {
            bool hit = false;
            for (unsigned int i = 0; i < m_enemies.size();)
            {
                if (((m_enemies[i]->getPosition().x >= entity->getPosition().x) && (m_enemies[i]->getPosition().x < entity->getPosition().x + entity->getSize().x))
                 || ((m_enemies[i]->getPosition().x <= entity->getPosition().x) && (m_enemies[i]->getPosition().x + m_enemies[i]->getSize().x > entity->getPosition().x)))
                {
                    if (((m_enemies[i]->getPosition().y >= entity->getPosition().y) && (m_enemies[i]->getPosition().y < entity->getPosition().y + entity->getSize().y))
                     || ((m_enemies[i]->getPosition().y <= entity->getPosition().y) && (m_enemies[i]->getPosition().y + m_enemies[i]->getSize().y > entity->getPosition().y)))
                    {
                        // Destroy the enemy
                        m_enemies[i]->destroy();
                        m_enemies.erase(m_enemies.begin()+i);
                        hit = true;

                        // Check if you earned a powerup
                        if (std::uniform_real_distribution<double>{0.0, 1.0}(generator) < POWERUP_CHANCE)
                        {
                            // Select a random powerup
                            auto random = std::uniform_int_distribution<unsigned int>(0, static_cast<unsigned int>(PowerupType::Count)-1)(generator);

                            // Activate the powerup
                            Event powerupEvent{Event::Type::PowerupActivated, m_enemies[i].get()};
                            powerupEvent.powerup = static_cast<PowerupType>(random);
                            notifyObservers(powerupEvent);
                        }

                        continue;
                    }
                }

                i++;
            }

            return hit;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        AttackingEntityList& EnemyController::getEnemies()
        {
            return m_enemies;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
