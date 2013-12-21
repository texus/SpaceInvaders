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


#include <SpaceInvaders/Controller/Powerups.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Powerup::Powerup(EntityPtr entity, const sf::Time& duration) :
            m_entity  (entity),
            m_duration(duration)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Powerup::~Powerup()
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool Powerup::update(const sf::Time& elapsedTime)
        {
            m_elapsed += elapsedTime;

            if (m_elapsed > m_duration)
                return false;

            return true;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        SpeedChangePowerup::SpeedChangePowerup(AttackingEntityPtr entity, const sf::Time& duration, float speedFactor) :
            Powerup      (entity, duration),
            m_speedFactor(speedFactor)
        {
            entity->setSpeed(entity->getSpeed() * m_speedFactor);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        SpeedChangePowerup::~SpeedChangePowerup()
        {
            auto entity = std::dynamic_pointer_cast<Model::AttackingEntity>(m_entity);
            entity->setSpeed(entity->getSpeed() / m_speedFactor);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        FireRatePowerup::FireRatePowerup(AttackingEntityPtr entity, const sf::Time& duration, float fireRateFactor) :
            Powerup         (entity, duration),
            m_fireRateFactor(fireRateFactor)
        {
            entity->getGun().setCoolDownTime(entity->getGun().getCoolDownTime() / m_fireRateFactor);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        FireRatePowerup::~FireRatePowerup()
        {
            auto entity = std::dynamic_pointer_cast<Model::AttackingEntity>(m_entity);
            entity->getGun().setCoolDownTime(entity->getGun().getCoolDownTime() * m_fireRateFactor);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
