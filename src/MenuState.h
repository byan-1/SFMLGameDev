#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"

class MenuState : public State
{
public:
  MenuState(StateStack &stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event &event);
  void updateOptionText();

private:
  enum OptionNames
  {
    Play,
    Exit
  };
  sf::Sprite mBackgroundSprite;
  std::vector<sf::Text> mOptions;
  std::size_t mOptionsIndex;
};

#endif