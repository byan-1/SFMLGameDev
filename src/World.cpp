#include "World.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include <math.h>

World::World(sf::RenderWindow &window) : mWindow(window),
                                         mScrollSpeed(-50.f),
                                         mWorldView(window.getDefaultView()),
                                         mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
                                         mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f),
                                         mPlayerAircraft(nullptr)
{
  loadTextures();
  buildScene();
  mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
  mTextures.load(Textures::ID::Eagle, "Textures/Eagle.png");
  mTextures.load(Textures::ID::Raptor, "Textures/Raptor.png");
  mTextures.load(Textures::ID::Desert, "Textures/Desert.png");
}

void World::buildScene()
{
  //initialize different layers
  for (std::size_t i = 0; i < LayerCount; ++i)
  {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();
    mSceneGraph.attachChild(std::move(layer));
  }

  //prepare tiled background
  sf::Texture &texture = mTextures.get(Textures::ID::Desert);
  sf::IntRect textureRect(mWorldBounds);
  texture.setRepeated(true);

  //add background sprite to scene
  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  //add player's aircraft
  std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
  mPlayerAircraft = leader.get();
  mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
  mPlayerAircraft->setPosition(mSpawnPosition);
  mSceneLayers[Air]->attachChild(std::move(leader));

  //add two escording aircrafts, placed relative to main plane
  std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
  leftEscort->setPosition(-80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(leftEscort));

  std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
  rightEscort->setPosition(80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw()
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
  mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
  mPlayerAircraft->setVelocity(0.f, 0.f);

  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), dt);

  sf::Vector2f velocity = mPlayerAircraft->getVelocity();

  if (velocity.x != 0.f && velocity.y != 0.f)
    mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
  mPlayerAircraft->accelerate(0.f, mScrollSpeed);
  mSceneGraph.update(dt);

  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
  const float borderDistance = 40.f;

  sf::Vector2f position = mPlayerAircraft->getPosition();
  position.x = std::max(position.x, viewBounds.left + borderDistance);
  position.x = std::min(position.x, viewBounds.width - borderDistance);
  position.y = std::max(position.y, viewBounds.top + borderDistance);
  position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
  mPlayerAircraft->setPosition(position);
}

CommandQueue &World::getCommandQueue()
{
  return mCommandQueue;
}