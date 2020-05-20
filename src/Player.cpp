#include "Player.h"
#include "Aircraft.h"

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

struct AircraftMover
{
  AircraftMover(float vx, float vy) : velocity(vx, vy) {}

  void operator()(Aircraft &aircraft, sf::Time) const
  {
    aircraft.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

Player::Player()
{
  mKeyBinding[sf::Keyboard::Left] = MoveLeft;
  mKeyBinding[sf::Keyboard::Right] = MoveRight;
  mKeyBinding[sf::Keyboard::Up] = MoveUp;
  mKeyBinding[sf::Keyboard::Down] = MoveDown;

  initializeActions();

  for (auto &pair : mActionBinding)
    pair.second.category = Category::PlayerAircraft;
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
  for (auto pair : mKeyBinding)
  {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
      commands.push(mActionBinding[pair.second]);
  }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands)
{
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
  {
    Command output;
    output.category = Category::PlayerAircraft;
    output.action = [](SceneNode &s, sf::Time) {
      std::cout << s.getPosition().x << "," << s.getPosition().y << "\n";
    };
    commands.push(output);
  }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
  for (auto it = mKeyBinding.begin(); it != mKeyBinding.end();)
  {
    if (it->second == action)
      mKeyBinding.erase(it++);
    else
      ++it;
  }
  mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
  for (auto pair : mKeyBinding)
  {
    if (pair.second == action)
      return pair.first;
  }
  return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
  const float playerSpeed = 200.f;
  mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
  mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
  mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
  mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

bool Player::isRealTimeAction(Action action)
{
  switch (action)
  {
  case MoveLeft:
  case MoveRight:
  case MoveDown:
  case MoveUp:
    return true;

  default:
    return false;
  }
}