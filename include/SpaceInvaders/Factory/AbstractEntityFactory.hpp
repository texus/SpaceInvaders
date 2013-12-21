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


#ifndef SPACE_INVADERS_ABSTRACT_ENTITY_FACTORY_HPP
#define SPACE_INVADERS_ABSTRACT_ENTITY_FACTORY_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SpaceInvaders/Model/Entities.hpp>
#include <SpaceInvaders/Model/Gun.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for the abstract factory pattern
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    class AbstractEntityFactory
    {
    public:

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~AbstractEntityFactory() {}


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the enemies
        ///
        /// @param difficulty  The difficulty
        ///
        /// The concrete factory will deal with the exact implementation of this function.
        /// The difficulty could be used in some calculation, but might also be treated as the level number
        /// to load the enemies from a config file that was written specifically for this level.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual AttackingEntityList createEnemies(unsigned int difficulty) = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the walls
        ///
        /// @param difficulty  The difficulty
        ///
        /// The concrete factory will deal with the exact implementation of this function.
        /// The difficulty could be used in some calculation, but might also be treated as the level number
        /// to load the walls from a config file that was written specifically for this level.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual EntityList createWalls(unsigned int difficulty) = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the player
        ///
        /// @param difficulty  The difficulty
        ///
        /// The concrete factory will deal with the exact implementation of this function.
        /// The difficulty could be used in some calculation, but might also be treated as the level number
        /// to load the player from a config file that was written specifically for this level.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual AttackingEntityPtr createPlayer(unsigned int difficulty) = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create a gun which can be attached to an entity
        ///
        /// @param difficulty  The difficulty
        /// @param type        Type of the gun to create
        ///
        /// The concrete factory will deal with the exact implementation of this function.
        /// The difficulty could be used in some calculation, but might also be treated as the level number
        /// to load the gun from a config file that was written specifically for this level.
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Model::Gun createGun(unsigned int difficulty, GunType type) = 0;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SPACE_INVADERS_ABSTRACT_ENTITY_FACTORY_HPP
