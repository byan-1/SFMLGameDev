#ifndef PLAYER_H
#define PLAYER_H

#include "CommandQueue.h"
#include <cassert>

class Player
{
public:
  enum Action
  {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    ActionCount
  };
  Player();
  void handleEvent(const sf::Event &event, CommandQueue &commands);
  void handleRealtimeInput(CommandQueue &commands);
  void assignKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key getAssignedKey(Action action) const;

private:
  void initializeActions();
  static bool isRealTimeAction(Action action);
  std::map<sf::Keyboard::Key, Action> mKeyBinding;
  std::map<Action, Command> mActionBinding;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode &, sf::Time)> derivedAction(Function fn)
{
  return [=](SceneNode &node, sf::Time dt) {
    assert(dynamic_cast<GameObject *>(&node) != nullptr);
    fn(static_cast<GameObject &>(node), dt);
  };
}

#endif