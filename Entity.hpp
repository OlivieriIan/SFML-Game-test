#ifndef ENTITY_HPP
#define ENTITY_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
#include <iostream>
/* =================[Class Definition]======================================= */
class Entity
{
public:
  Entity();
  ~Entity();
  void              initialize(unsigned int id);

  /* Logic */
  unsigned int      id(void) const;
  float             speed(void) const;
  void              setSpeed(float speed);
  bool              isSolid(void) const;
  void              setSolid(bool isSolid);

  /* Graphics */
  const sf::Sprite& drawable(void);
  void              move(const sf::Vector2f& offset);
  void              setPosition(float x, float y);
  void              setRotation(float angle);
  void              setScale(float x, float y);
  
protected:

private: /* Functions */

private: /* Variables */
  /* Logic */
  unsigned int     m_id;
  float            m_speed;
  bool             m_isSolid; // Can collision with player and other objects

  /* Graphics */
  sf::Sprite       m_sprite;
};

#endif /* ENTITY_HPP */
/* =================[End of file]============================================ */