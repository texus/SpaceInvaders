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


#ifndef SPACE_INVADERS_EVENT_HPP
#define SPACE_INVADERS_EVENT_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Global.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Events are used throughout the code to let anyone interested know about a certain event
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct Event
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Type of the event, which indicates what has happened
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class Type
        {
            ApplicationExit,      ///< The application should exit (e.g. window was closed)
            PositionChanged,      ///< The position of an entity has changed
            SizeChanged,          ///< The size of an entity has changed
            MoveLeftKeyPressed,   ///< The key to move the player to the left has been pressed
            MoveLeftKeyReleased,  ///< The key to move the player to the left has been released
            MoveRightKeyPressed,  ///< The key to move the player to the right has been pressed
            MoveRightKeyReleased, ///< The key to move the player to the right has been released
            FireKeyPressed,       ///< The key to fire the gun of the player has been pressed
            FireKeyReleased,      ///< The key to fire the gun of the player has been released
            GunFired,             ///< A n entity has fired its gun
            Destroyed,            ///< An entity has been destroyed
            LevelComplete,        ///< The level has been completed
            GameOver,             ///< The game has been lost
            ScoreChanged,         ///< The score has changed
            LivesChanged,         ///< The lives of the player have changed
            GameStateChanged,     ///< The current game state has changed
            PowerupActivated,     ///< A powerup has been activated
            PowerupDeactivated    ///< A powerup has stopped working
        };

        Type type;             ///< The type of the event
        Model::Entity* entity; ///< Optional pointer to an entity which is connected to this event

        union
        {
            Vector2f     position;   ///< Position of the entity when type is PositionChanged
            Vector2f     size;       ///< Size of the entity when type is SizeChanged
            unsigned int score;      ///< Score to be added when type is ScoreChanged
            unsigned int lives;      ///< New amount of lives when type is LivesChanged
            GameState    gameState;  ///< The new game state when type is GameStateChanged
            PowerupType  powerup;    ///< The type of the powerup when type is PowerupActivated
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor to initialize the event
        ///
        /// @param eventType The type of the event
        /// @param entityPtr Optional pointer to an entity which is connected to this event
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        Event(Type eventType, Model::Entity* entityPtr = nullptr) :
            type(eventType),
            entity(entityPtr)
        {
        }
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_EVENT_HPP
