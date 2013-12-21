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


#include <SpaceInvaders/View/SFMLEntityRepresentation.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace View
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        SFMLEntityRepresentation::SFMLEntityRepresentation(sf::RenderTarget& renderTarget, EntityPtr entity) :
            m_renderTarget(renderTarget)
        {
            std::string filename = entity->getImageFilename();

            if (!filename.empty())
            {
                if (!m_texture.loadFromFile(filename))
                    throw std::runtime_error("Failed to create EntityRepresentation (filename was '" + filename + "').");

                m_sprite.setTexture(m_texture);
                m_sprite.setPosition(entity->getPosition().x, entity->getPosition().y);
                m_sprite.setScale(entity->getSize().x / m_texture.getSize().x, entity->getSize().y / m_texture.getSize().y);
            }

            entity->addObserver(std::bind(&SFMLEntityRepresentation::positionChanged, this, std::placeholders::_1), Event::Type::PositionChanged);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLEntityRepresentation::draw()
        {
            m_renderTarget.draw(m_sprite);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLEntityRepresentation::positionChanged(const Event& event)
        {
            m_sprite.setPosition(event.position.x, event.position.y);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
