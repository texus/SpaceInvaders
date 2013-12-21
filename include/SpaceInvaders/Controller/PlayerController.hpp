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


#ifndef SPACE_INVADERS_PLAYER_CONTROLLER_HPP
#define SPACE_INVADERS_PLAYER_CONTROLLER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        /// @brief Class that has control over the player
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        class PlayerController : public Observable
        {
        public:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor to initialize the player
            ///
            /// @param player Player entity which the controller will control
            /// @param view   Pointer to the view, only needed for finishing the creation of the player
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            PlayerController(AttackingEntityPtr player, View::AbstractView* view);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Update the position of the player and fire if needed
            ///
            /// @param elapsedTime  Time passed since the last time this function was called
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            void update(const sf::Time& elapsedTime);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if a bullet has hit the player
            ///
            /// @param entity  The bullet to check against the player
            ///
            /// @return True when the player overlapped and is now destroyed.
            ///         False when the player did not overlap with the bullet entity.
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            bool checkCollision(EntityPtr entity);


            ////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Return the player
            ///
            /// @return Pointer to the player entity
            ///
            ////////////////////////////////////////////////////////////////////////////////////////////////
            AttackingEntityPtr& getPlayer();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:

            ////////////////////////////////////////////////////////////////////////////////////////////////
            // Fires the gun if the cooldown time has expired.
            ////////////////////////////////////////////////////////////////////////////////////////////////
            void fireGun();


            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            AttackingEntityPtr m_player;
            bool m_moveLeftKeyDown = false;
            bool m_moveRightKeyDown = false;
            bool m_fireKeyDown = false;
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_PLAYER_CONTROLLER_HPP