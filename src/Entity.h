#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "SceneNode.h"

class Entity : public SceneNode
{
public:
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float vx, float vy);
  sf::Vector2f getVelocity() const;
  void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); };
  void accelerate(float vx, float vy)
  {
    mVelocity.x += vx;
    mVelocity.y += vy;
  };

private:
  virtual void updateCurrent(sf::Time dt) override;
  sf::Vector2f mVelocity;
};

#endif