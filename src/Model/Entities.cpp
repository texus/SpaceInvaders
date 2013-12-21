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


#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace Model
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Entity::Entity(const std::string& filename) :
            m_imageFilename(filename)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Entity::~Entity()
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Entity::setPosition(const Vector2f& position)
        {
            m_area.left = position.x;
            m_area.top = position.y;

            Event event{Event::Type::PositionChanged, this};
            event.position = position;
            notifyObservers(event);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector2f Entity::getPosition() const
        {
            return Vector2f{m_area.left, m_area.top};
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Entity::setSize(const Vector2f& size)
        {
            m_area.width = size.x;
            m_area.height = size.y;

            Event event{Event::Type::SizeChanged, this};
            event.position = size;
            notifyObservers(event);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector2f Entity::getSize() const
        {
            return Vector2f{m_area.width, m_area.height};
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string Entity::getImageFilename() const
        {
            return m_imageFilename;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void Entity::destroy()
        {
            notifyObservers(Event{Event::Type::Destroyed, this});
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        AttackingEntity::AttackingEntity(const std::string& filename, const Gun& gun) :
            Entity (filename),
            m_gun  (gun)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        AttackingEntity::~AttackingEntity()
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Gun& AttackingEntity::getGun()
        {
            return m_gun;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void AttackingEntity::setSpeed(float speed)
        {
            m_speed = speed;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float AttackingEntity::getSpeed() const
        {
            return m_speed;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        WallEntity::WallEntity(const std::string& filename) :
            Entity(filename)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        EnemyEntity::EnemyEntity(const std::string& filename, const Gun& gun, unsigned int killPoints) :
            AttackingEntity(filename, gun),
            m_killPoints   (killPoints)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        unsigned int EnemyEntity::getKillPoints() const
        {
            return m_killPoints;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void EnemyEntity::destroy()
        {
            Event event{Event::Type::ScoreChanged, this};
            event.score = getKillPoints();
            notifyObservers(event);

            Entity::destroy();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        PlayerEntity::PlayerEntity(const std::string& filename, const Gun& gun) :
            AttackingEntity(filename, gun)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void PlayerEntity::setLives(unsigned int lives)
        {
            m_lives = lives;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        unsigned int PlayerEntity::getLives() const
        {
            return m_lives;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        BulletEntity::BulletEntity(const std::string& filename, float speed) :
            Entity (filename),
            m_speed(speed)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float BulletEntity::getSpeed() const
        {
            return m_speed;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
