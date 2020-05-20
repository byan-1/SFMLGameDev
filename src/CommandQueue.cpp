#include "CommandQueue.h"

void CommandQueue::push(const Command &command)
{
  mQueue.push(command);
}

Command CommandQueue::pop()
{
  auto front = mQueue.front();
  mQueue.pop();
  return front;
}
bool CommandQueue::isEmpty() const
{
  return mQueue.empty();
}