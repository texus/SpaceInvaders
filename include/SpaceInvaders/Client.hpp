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


#ifndef SPACE_INVADERS_CLIENT_HPP
#define SPACE_INVADERS_CLIENT_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Controller/Controller.hpp>
#include <SpaceInvaders/View/AbstractView.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The class that handles the main loop and controls the whole game (not just a single level)
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Client
    {
    public:

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        Client();


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Start the main loop of the game
        ///
        /// This function will only return when the application quits.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void mainLoop();


        ////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Load the next level of the game
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadNextLevel(const Event& event);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Callback function for when the state of the game changes
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void gameStateChanged(const Event& event);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Callback function for when the game is lost
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        void gameOver(const Event& event);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        unsigned int m_difficulty = 0;

        GameState m_gameState = GameState::MainMenu;

        std::unique_ptr<View::AbstractView> m_view;
        std::unique_ptr<Controller::Controller> m_controller;

        unsigned int m_score = 0;

        bool m_running = true;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_CLIENT_HPP