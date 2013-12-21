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


#include <SpaceInvaders/Model/Gun.hpp>

namespace Game
{
    namespace Model
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Gun::Gun(const std::string& bulletFilename, const Vector2f& bulletSize, float bulletSpeed, const sf::Time& coolDownTime, float chanceIncrease) :
            m_bulletFilename(bulletFilename),
            m_bulletSize    (bulletSize),
            m_bulletSpeed   (bulletSpeed),
            m_coolDownTime  (coolDownTime),
            m_chanceIncrease(chanceIncrease)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string Gun::getBulletFilename() const
        {
            return m_bulletFilename;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector2f Gun::getBulletSize() const
        {
            return m_bulletSize;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float Gun::getBulletSpeed() const
        {
            return m_bulletSpeed;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float Gun::getChanceIncrease() const
        {
            return m_chanceIncrease;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Gun::setCoolDownTime(const sf::Time& coolDownTime)
        {
            m_coolDownTime = coolDownTime;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Time Gun::getCoolDownTime() const
        {
            return m_coolDownTime;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool Gun::tryToFire()
        {
            if (m_cooldownTimer.getElapsedTime() > m_coolDownTime)
            {
                m_cooldownTimer.restart();
                return true;
            }
            else
                return false;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
