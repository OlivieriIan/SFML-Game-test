
/* =================[Includes]=============================================== */
#include "Entity.hpp"

#include "ResourceManager.hpp"

/* =================[Private Data]=========================================== */

/* =================[Public Class Functions]================================= */

Entity::Entity() :
  m_id(-1),
  m_speed(1.0f)
{
}
Entity::~Entity() {}

void Entity::initialize(unsigned int id)
{
  m_id = id;
  TextureManager::instance().load(m_id,
    "resources/img/" + std::to_string(m_id) + ".png");
  m_sprite.setTexture(TextureManager::instance().get(m_id));

}

unsigned int Entity::id(void) const
{
  return(m_id);
}

float Entity::speed(void) const 
{
  return(m_speed);
}

void Entity::setSpeed(float speed)
{
  m_speed = speed;
}

bool Entity::isSolid(void) const
{
  return(m_isSolid);
}

void Entity::setSolid(bool isSolid)
{
  m_isSolid = isSolid;
}

/* Graphics */
const sf::Sprite& Entity::drawable(void)
{
  return m_sprite;
}
void Entity::move(const sf::Vector2f& offset)
{
  m_sprite.move(offset);
}

void Entity::setPosition(float x, float y)
{
  m_sprite.setPosition(x, y);
}

void Entity::setRotation(float angle)
{
  m_sprite.setRotation(angle);
}

void Entity::setScale(float x, float y)
{
  m_sprite.setScale(x, y);
}

/* =================[Private Class Functions]================================ */

/* =================[End of file]============================================ */