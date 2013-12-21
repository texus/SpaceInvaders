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


#include <SpaceInvaders/Factory/DebugEntityFactory.hpp>

namespace Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AttackingEntityList DebugEntityFactory::createEnemies(unsigned int difficulty)
    {
        auto enemies = AttackingEntityList();

        // Create the enemies with the correct position
        for (unsigned int row = 0; row < 4; ++row)
        {
            for (unsigned int col = 0; col < 10; ++col)
            {
                if (row == 0)
                    enemies.insert(enemies.end(), AttackingEntityPtr{new Model::EnemyEntity{"Resources/Enemy3.png", createGun(difficulty, GunType::Enemy3), difficulty * 20}});
                else if (row == 1)
                    enemies.insert(enemies.end(), AttackingEntityPtr{new Model::EnemyEntity{"Resources/Enemy2.png", createGun(difficulty, GunType::Enemy2), difficulty * 10}});
                else
                    enemies.insert(enemies.end(), AttackingEntityPtr{new Model::EnemyEntity{"Resources/Enemy1.png", createGun(difficulty, GunType::Enemy1), difficulty * 5}});

                enemies.back()->setSize(Vector2f{1.0f/16.0f * SCREEN_WIDTH, 1.0f/16.0f * SCREEN_WIDTH});
                enemies.back()->setSpeed(20 + (4 * difficulty));
                enemies.back()->setPosition(Vector2f{(1.0f/14.0f * SCREEN_WIDTH) * col,
                                                     (1.0f/14.0f * SCREEN_WIDTH) * row + (1.0f/24.0f * SCREEN_WIDTH)});
            }
        }

        return enemies;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    EntityList DebugEntityFactory::createWalls(unsigned int)
    {
        auto walls = EntityList();

        // Create the wall blocks with the correct position
        for (unsigned int block = 0; block < 3; ++block)
        {
            Vector2f blockPosition{(1.0f/7.0f * SCREEN_WIDTH) + ((2.0f/7.0f * SCREEN_WIDTH) * block),
                                   (9.0f/12.0f) * SCREEN_HEIGHT};

            for (unsigned int col = 0; col < 4; ++col)
            {
                unsigned int rows = (col == 0 || col == 3) ? 5 : 3;
                for (unsigned int row = 0; row < rows; ++row)
                {
                    walls.insert(walls.end(), std::shared_ptr<Model::Entity>{new Model::WallEntity("Resources/Wall.png")});
                    walls.back()->setSize(Vector2f{1.0f/7.0f * SCREEN_WIDTH / 4, 1.0f/18.0f * SCREEN_HEIGHT / 3});
                    walls.back()->setPosition(Vector2f{blockPosition.x + (walls.back()->getSize().x * col), blockPosition.y + (walls.back()->getSize().y * row)});
                }
            }
        }

        return walls;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AttackingEntityPtr DebugEntityFactory::createPlayer(unsigned int difficulty)
    {
        auto player = std::shared_ptr<Model::PlayerEntity>(new Model::PlayerEntity{"Resources/Player.png", createGun(difficulty, GunType::Normal)});
        player->setSpeed(260 - (5 * difficulty));
        player->setLives(3);

        player->setSize(Vector2f{2.0f / 20.0f * SCREEN_WIDTH, 5.0f / 80.0f * SCREEN_HEIGHT});
        player->setPosition(Vector2f{(SCREEN_WIDTH - player->getSize().x) / 2.0f, SCREEN_HEIGHT - (player->getSize().y * (3.0f / 2.0f))});

        return player;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Model::Gun DebugEntityFactory::createGun(unsigned int difficulty, GunType type)
    {
        switch (type)
        {
            case GunType::Normal:
                return Model::Gun{ "Resources/Bullet.png", // bullet filename
                                   Vector2f{1.0f / 120.0f * SCREEN_WIDTH, 1.0f / 40.0f * SCREEN_HEIGHT}, // bullet size
                                   -350.0f + (10.0f * difficulty), // bullet speed
                                   sf::milliseconds(600 + (20 * difficulty)) // cooldown
                                 };

            case GunType::Enemy1:
            case GunType::Enemy2:
            case GunType::Enemy3:
                return Model::Gun{ "Resources/Bullet.png", // bullet filename
                                   Vector2f{1.0f / 120.0f * SCREEN_WIDTH, 1.0f / 40.0f * SCREEN_HEIGHT}, // bullet size
                                   250.0f + (15 * difficulty), // bullet speed
                                   sf::milliseconds(0), // cooldown
                                   80.0f * difficulty // Chance of firing per second
                                 };

            default:
                throw std::logic_error("Firing an unknown gun type.");
        };
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}
