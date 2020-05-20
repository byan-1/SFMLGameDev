#include "StateStack.h"

StateStack::StateStack(State::Context context) : mStack(), mPendingList(), mContext(context), mFactories()
{
}

void StateStack::update(sf::Time dt)
{
  for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
  {
    if (!(*it)->update(dt))
      break;
  }
  applyPendingChanges();
}

void StateStack::draw()
{
  for (auto &state : mStack)
    state->draw();
}

State::Ptr StateStack::createState(States::ID stateID)
{
  auto found = mFactories.find(stateID);
  assert(found != mFactories.end());

  return found->second();
}

void StateStack::handleEvent(const sf::Event &event)
{
  for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
  {
    if (!(*it)->handleEvent(event))
      return;
  }
  applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
  mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
  mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
  mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
  return mStack.empty();
}

void StateStack::applyPendingChanges()
{
  for (auto &change : mPendingList)
  {
    switch (change.action)
    {
    case Action::Push:
      mStack.push_back(createState(change.stateID));
      break;
    case Action::Pop:
      mStack.pop_back();
      break;
    case Action::Clear:
      mStack.clear();
      break;
    }
  }
  mPendingList.clear();
}