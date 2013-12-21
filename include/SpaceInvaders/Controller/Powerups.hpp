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


#ifndef SPACE_INVADERS_POWERUPS_HPP
#define SPACE_INVADERS_POWERUPS_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Global.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Base class for the powerups
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class Powerup
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor to initialize the powerup
            ///
            /// @param entity   The entity on which the powerup will work
            /// @param duration The duration of the powerup
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            Powerup(EntityPtr entity, const sf::Time& duration);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            virtual ~Powerup();


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Update the time passed to decide if the powerup should be deactivated
            ///
            /// @param elapsedTime  Time passed since the last time this function was called
            ///
            /// @return True when the powerup is still active.
            ///         False when the powerup should be deactivated.
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            virtual bool update(const sf::Time& elapsedTime);


            ////////////////////////////////////////////////////////////////////////////////////////////////
        protected:
            EntityPtr m_entity;
            sf::Time  m_duration;
            sf::Time  m_elapsed;
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Powerup that changes the speed of an entity
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class SpeedChangePowerup : public Powerup
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor to initialize the powerup
            ///
            /// @param entity      The entity on which the powerup will work
            /// @param duration    The duration of the powerup
            /// @param speedFactor The factor with which the speed will be multiplied
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            SpeedChangePowerup(AttackingEntityPtr entity, const sf::Time& duration, float speedFactor);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            ~SpeedChangePowerup();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            float m_speedFactor;
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Powerup that changes the fire rate of the gun of an entity
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class FireRatePowerup : public Powerup
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor to initialize the powerup
            ///
            /// @param entity         The entity on which the powerup will work
            /// @param duration       The duration of the powerup
            /// @param fireRateFactor The factor with which the fire rate will be multiplied
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            FireRatePowerup(AttackingEntityPtr entity, const sf::Time& duration, float fireRateFactor);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            ~FireRatePowerup();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            float m_fireRateFactor;
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_POWERUPS_HPP
