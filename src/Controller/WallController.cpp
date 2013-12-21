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


#include <SpaceInvaders/Controller/WallController.hpp>
#include <SpaceInvaders/View/AbstractView.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        WallController::WallController(EntityList walls, View::AbstractView* view) :
            m_walls(walls)
        {
            for (auto& wall : m_walls)
                view->addEntity(wall);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool WallController::checkCollision(EntityPtr entity)
        {
            bool hit = false;
            for (unsigned int i = 0; i < m_walls.size();)
            {
                if (((m_walls[i]->getPosition().x >= entity->getPosition().x) && (m_walls[i]->getPosition().x < entity->getPosition().x + entity->getSize().x))
                 || ((m_walls[i]->getPosition().x <= entity->getPosition().x) && (m_walls[i]->getPosition().x + m_walls[i]->getSize().x > entity->getPosition().x)))
                {
                    if (((m_walls[i]->getPosition().y >= entity->getPosition().y) && (m_walls[i]->getPosition().y < entity->getPosition().y + entity->getSize().y))
                     || ((m_walls[i]->getPosition().y <= entity->getPosition().y) && (m_walls[i]->getPosition().y + m_walls[i]->getSize().y > entity->getPosition().y)))
                    {
                        m_walls[i]->destroy();
                        m_walls.erase(m_walls.begin()+i);
                        hit = true;
                        continue;
                    }
                }

                i++;
            }

            return hit;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        EntityList& WallController::getWalls()
        {
            return m_walls;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
