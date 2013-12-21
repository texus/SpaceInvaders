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


#include <SpaceInvaders/Controller/PowerupController.hpp>
#include <SpaceInvaders/Controller/Powerups.hpp>

namespace Game
{
    namespace Controller
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void PowerupController::addPowerup(PowerupPtr powerup)
        {
            m_powerups.push_back(std::move(powerup));
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void PowerupController::update(const sf::Time& elapsedTime)
        {
            for (unsigned int i = 0; i < m_powerups.size();)
            {
                if (!m_powerups[i]->update(elapsedTime))
                {
                    notifyObservers(Event{Event::Type::PowerupDeactivated});
                    m_powerups.erase(m_powerups.begin()+i);
                    continue;
                }

                i++;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        std::vector<PowerupPtr>& PowerupController::getPowerups()
        {
            return m_powerups;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
