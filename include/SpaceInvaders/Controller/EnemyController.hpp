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


#ifndef SPACE_INVADERS_ENEMY_CONTROLLER_HPP
#define SPACE_INVADERS_ENEMY_CONTROLLER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <random>
#include <chrono>
#include <SpaceInvaders/Observable.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    namespace View
    {
        class AbstractView;
    }

    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Class that has control over the enemies
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class EnemyController : public Observable
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor to initialize the controller
            ///
            /// @param enemies List of enemies which the controller will control
            /// @param view    Pointer to the view, only needed for finishing the creation of the enemies
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            EnemyController(AttackingEntityList enemies, View::AbstractView* view);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Update the position of the enemies and decide if it is time to let them fire
            ///
            /// @param elapsedTime  Time passed since the last time this function was called
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            void update(const sf::Time& elapsedTime);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if a bullet has hit one of the enemies
            ///
            /// @param entity  The bullet to check against the enemies
            ///
            /// @return True when one of the enemies overlapped and is now destroyed.
            ///         False when none of the enemies overlapped with the bullet entity.
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            bool checkCollision(EntityPtr entity);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Return the enemies
            ///
            /// @return List of enemies
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            AttackingEntityList& getEnemies();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            AttackingEntityList m_enemies;
            bool  m_movingDown = false;
            float m_movingDownDistance = 0;

            float m_fireChance = 0;

            std::default_random_engine generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_ENEMY_CONTROLLER_HPP
