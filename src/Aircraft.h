#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.h"
#include "ResourceHolder.h"

class Aircraft : public Entity
{
public:
  enum Type
  {
    Eagle,
    Raptor
  };
  explicit Aircraft(Type type, const TextureHolder &textures);
  virtual unsigned int getCategory() const override;

private:
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
  Type mType;
  sf::Sprite mSprite;
};

#endif