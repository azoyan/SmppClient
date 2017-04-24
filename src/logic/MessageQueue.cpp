#include "MessageQueue.h"
#include <cassert>
#include <iostream>

nsSmppClient::MessageQueue::MessageQueue(SmppClient& smppClient)
: mSmppClient(smppClient)
{

}

void nsSmppClient::MessageQueue::sending() {
  while(true) {
    while (!mQueue.empty()) {
      auto message = mQueue.front();
      mQueue.pop();

      mMutex.lock();
      mSmppClient.sendMessage(message);
      mMutex.unlock();
    }
  }
}

void nsSmppClient::MessageQueue::receiving() {
  while (true) {
    mMutex.lock();
    mSmppClient.read();
    mMutex.unlock();
    while(mSmppClient.hasResponses()) {
      auto msg = mSmppClient.takeMessage();
      mQueue.push(msg);
    }
  }
}

void nsSmppClient::MessageQueue::push(const std::vector<char>& message) {
  mQueue.push(message);
}

void nsSmppClient::MessageQueue::pop() {
  mQueue.pop();
}

std::vector<char> nsSmppClient::MessageQueue::take() {
  assert(!mQueue.empty());

  auto result(mQueue.front());
  mQueue.pop();
  return result;
}

bool nsSmppClient::MessageQueue::isEmpty() const {
  return mQueue.empty();
}

size_t nsSmppClient::MessageQueue::size() const {
  return mQueue.size();
}
