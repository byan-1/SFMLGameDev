#ifndef COMMAND_H
#define COMMAND_H

#include <SFML/Graphics.hpp>
#include <functional>

class SceneNode;

struct Command
{
  Command();
  std::function<void(SceneNode &, sf::Time)> action;
  unsigned int category;
};

#endif