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


#ifndef SPACE_INVADERS_GUN_HPP
#define SPACE_INVADERS_GUN_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Global.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    namespace Model
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gun that can be connected to an entity
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class Gun
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Contructor to initialize the gun
            ///
            /// @param bulletFilename  Filename of the bullet which this gun fires
            /// @param bulletSize      Size of the bullet which this gun fires
            /// @param bulletSpeed     Speed of the bullet which this gun fires
            /// @param coolDownTime    Time needed by the gun before it fire another bullet
            /// @param chanceIncrease  How fast the chance raises that an enemy with this gun will fire
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            Gun(const std::string& bulletFilename, const Vector2f& bulletSize, float bulletSpeed, const sf::Time& coolDownTime, float chanceIncrease = 0);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the filename that is needed to display the bullet on the screen
            ///
            /// @return Filename of the bullet which this gun fires
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            std::string getBulletFilename() const;


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the size of the bullet
            ///
            /// @return Size of the bullet which this gun fires
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            Vector2f getBulletSize() const;


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the speed of the bullet
            ///
            /// @return Speed of the bullet which this gun fires
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            float getBulletSpeed() const;


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns how fast the chance raises that an enemy with this gun will fire
            ///
            /// @return How fast the chance raises that an enemy with this gun will fire
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            float getChanceIncrease() const;


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Changes the cooldown time of the gun
            ///
            /// @param coolDownTime New cooldown time of the gun
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            void setCoolDownTime(const sf::Time& coolDownTime);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Returns the cooldown time of the gun
            ///
            /// @return Cooldown time of the gun
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            sf::Time getCoolDownTime() const;


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Make an attempt to fire a bullet
            ///
            /// @return True when a bullet is fired, false when the cooldown time hasn't expired yet
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            bool tryToFire();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            std::string m_bulletFilename;
            Vector2f    m_bulletSize;

            float       m_bulletSpeed;

            sf::Time    m_coolDownTime;
            sf::Clock   m_cooldownTimer;

            float       m_chanceIncrease;
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_GUN_HPP
