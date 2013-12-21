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


#ifndef SPACE_INVADERS_GLOBAL_HPP
#define SPACE_INVADERS_GLOBAL_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    namespace Model
    {
        class Entity;
        class BulletEntity;
        class AttackingEntity;
    }

    namespace Controller
    {
        class Powerup;
    }

    typedef std::unique_ptr<Controller::Powerup> PowerupPtr;
    typedef std::shared_ptr<Model::Entity> EntityPtr;
    typedef std::shared_ptr<Model::BulletEntity> BulletPtr;
    typedef std::vector<std::shared_ptr<Model::Entity>> EntityList;
    typedef std::shared_ptr<Model::AttackingEntity> AttackingEntityPtr;
    typedef std::vector<std::shared_ptr<Model::AttackingEntity>> AttackingEntityList;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Two-dimensional math vector
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct Vector2f
    {
        float x; ///< x-coordinate
        float y; ///< y-coordinate
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Rectangle with float coordinates
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct FloatRect
    {
        float left;   ///< x-coordinate of the rectangle
        float top;    ///< y-coordinate of the rectangle
        float width;  ///< width of the rectangle
        float height; ///< height of the rectangle
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Type of the powerup
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class PowerupType
    {
        SpeedBoost, ///< Player moves faster
        Slowdown,   ///< Enemies move slower
        RapidFire,  ///< Player shoots faster
        Count       ///< Amount of powerup types
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief States that the game can be in
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class GameState
    {
        MainMenu, ///< The main menu screen
        Paused,   ///< The pause screen
        Playing,  ///< The game itself
        GameOver  ///< The game over screen
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The type of gun, which will determine the type of the bullets being fired
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class GunType
    {
        Normal, ///< Default gun used by the player
        Enemy1, ///< Default gun used by enemies of type 1
        Enemy2, ///< Default gun used by enemies of type 2
        Enemy3  ///< Default gun used by enemies of type 3
    };


    /// @brief The width of the screen
    const unsigned int SCREEN_WIDTH  = 800;

    /// @brief The height of the screen
    const unsigned int SCREEN_HEIGHT = 600;

    /// @brief The distance that the enemy moves down
    const float ENEMY_CHANGE_TOP_DIFF = 50;

    /// @brief The chance to get a powerup after shooting an enemy
    const double POWERUP_CHANCE = 0.035;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_GLOBAL_HPP
