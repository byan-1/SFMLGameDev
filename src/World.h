#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include <array>
#include "CommandQueue.h"

class World : private sf::NonCopyable
{
public:
  explicit World(sf::RenderWindow &window);
  void update(sf::Time dt);
  void draw();
  CommandQueue &getCommandQueue();

private:
  void loadTextures();
  void buildScene();
  enum Layer
  {
    Background,
    Air,
    LayerCount
  };
  sf::RenderWindow &mWindow;
  sf::View mWorldView;
  TextureHolder mTextures;
  SceneNode mSceneGraph;
  std::array<SceneNode *, LayerCount> mSceneLayers;
  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  float mScrollSpeed;
  Aircraft *mPlayerAircraft;
  CommandQueue mCommandQueue;
};

#endif