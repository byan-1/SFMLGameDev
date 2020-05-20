#ifndef SCENENODE_H
#define SCENENODE_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Category.h"
#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
  typedef std::unique_ptr<SceneNode> Ptr;
  SceneNode() : mParent(nullptr){};
  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode &node);
  void update(sf::Time dt);
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;
  virtual unsigned int getCategory() const { return Category::Scene; };
  void onCommand(const Command &command, sf::Time dt);

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override final;
  virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt);
  std::vector<Ptr> mChildren;
  SceneNode *mParent;
};

#endif