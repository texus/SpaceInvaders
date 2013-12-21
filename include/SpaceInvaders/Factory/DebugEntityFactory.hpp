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


#ifndef SPACE_INVADERS_DEBUG_ENTITY_FACTORY_HPP
#define SPACE_INVADERS_DEBUG_ENTITY_FACTORY_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Factory/AbstractEntityFactory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Concrete factory in the abstract factory pattern, which still uses some hardcoded values
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    class DebugEntityFactory final : public AbstractEntityFactory
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the enemies
        ///
        /// @param difficulty  The difficulty of the level.
        ///                    This will influence the moving speed, bullet fire rate and bullet speed.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        AttackingEntityList createEnemies(unsigned int difficulty);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the walls
        ///
        /// @param difficulty  The difficulty of the level.
        ///                    In this factory the difficulty has no influence on the walls.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        EntityList createWalls(unsigned int difficulty);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the player
        ///
        /// @param difficulty  The difficulty of the level.
        ///                    This will influence the moving speed, bullet fire rate and bullet speed.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        AttackingEntityPtr createPlayer(unsigned int difficulty);


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create a gun which can be attached to an entity
        ///
        /// @param difficulty  The difficulty of the level.
        ///                    This will influence the bullet fire rate and bullet speed.
        /// @param type        Type of the gun to create
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        Model::Gun createGun(unsigned int difficulty, GunType type);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_DEBUG_ENTITY_FACTORY_HPP
