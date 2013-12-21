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


#include <SpaceInvaders/Controller/PlayerController.hpp>
#include <SpaceInvaders/View/AbstractView.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        PlayerController::PlayerController(AttackingEntityPtr player, View::AbstractView* view) :
            m_player(player)
        {
            // Add the player to the view
            view->addEntity(player);

            // Request a signal when a key is pressed
            view->addObserver([this](const Event&){ m_moveLeftKeyDown = false; }, Event::Type::MoveLeftKeyReleased);
            view->addObserver([this](const Event&){ m_moveLeftKeyDown = true; }, Event::Type::MoveLeftKeyPressed);
            view->addObserver([this](const Event&){ m_moveRightKeyDown = false; }, Event::Type::MoveRightKeyReleased);
            view->addObserver([this](const Event&){ m_moveRightKeyDown = true; }, Event::Type::MoveRightKeyPressed);
            view->addObserver([this](const Event&){ m_fireKeyDown = false; }, Event::Type::FireKeyReleased);
            view->addObserver([this](const Event&){ m_fireKeyDown = true; fireGun(); }, Event::Type::FireKeyPressed);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void PlayerController::update(const sf::Time& elapsedTime)
        {
            // Move the player to the left if needed
            if (m_moveLeftKeyDown)
            {
                m_player->setPosition(Vector2f{m_player->getPosition().x - (m_player->getSpeed() * elapsedTime.asSeconds()), m_player->getPosition().y});

                if (m_player->getPosition().x < 0)
                    m_player->setPosition(Vector2f{0, m_player->getPosition().y});
            }

            // Move the player to the right if needed
            if (m_moveRightKeyDown)
            {
                m_player->setPosition(Vector2f{m_player->getPosition().x + (m_player->getSpeed() * elapsedTime.asSeconds()), m_player->getPosition().y});

                if (m_player->getPosition().x + m_player->getSize().x > SCREEN_WIDTH)
                    m_player->setPosition(Vector2f{SCREEN_WIDTH - m_player->getSize().x, m_player->getPosition().y});
            }

            // Fire the gun if needed
            if (m_fireKeyDown)
                fireGun();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool PlayerController::checkCollision(EntityPtr entity)
        {
            if (((m_player->getPosition().x >= entity->getPosition().x) && (m_player->getPosition().x < entity->getPosition().x + entity->getSize().x))
             || ((m_player->getPosition().x <= entity->getPosition().x) && (m_player->getPosition().x + m_player->getSize().x > entity->getPosition().x)))
            {
                if (((m_player->getPosition().y >= entity->getPosition().y) && (m_player->getPosition().y < entity->getPosition().y + entity->getSize().y))
                 || ((m_player->getPosition().y <= entity->getPosition().y) && (m_player->getPosition().y + m_player->getSize().y > entity->getPosition().y)))
                {
                    Model::PlayerEntity* player = dynamic_cast<Model::PlayerEntity*>(m_player.get());
                    player->setLives(player->getLives() - 1);

                    Event event{Event::Type::LivesChanged, m_player.get()};
                    event.lives = player->getLives();
                    notifyObservers(event);
                    return true;
                }
            }

            return false;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        AttackingEntityPtr& PlayerController::getPlayer()
        {
            return m_player;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void PlayerController::fireGun()
        {
            // Only fire the gun when the cooldown period is over
            if (m_player->getGun().tryToFire())
                notifyObservers(Event{Event::Type::GunFired, m_player.get()});
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
