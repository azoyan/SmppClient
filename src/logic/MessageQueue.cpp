#include "MessageQueue.h"
#include <cassert>
#include <iostream>
#include <unistd.h>
#include <thread>

#include "../pdu/BindTransceiverResponse.h"

nsSmppClient::MessageQueue::MessageQueue(TcpClient& smppClient)
: mTcpClient(smppClient)
{

}

void nsSmppClient::MessageQueue::sending() {
  while(true) {
    while (!mQueue.empty()) {
      auto message = mQueue.front();
      mQueue.pop();
      mTcpClient.sendMessage(message);
    }
    mMutex.unlock();
  }
}

void nsSmppClient::MessageQueue::receiving() {
  while (true) {
    mMutex.lock();
    std::cout << "in read  " << std::this_thread::get_id() << std::endl;
    mTcpClient.read();
    std::cout << "read done\n"  ;
    while(mTcpClient.hasResponses()) {
      auto msg = mTcpClient.takeMessage();
      mQueue.push(msg);
    }
    mMutex.unlock();
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

void nsSmppClient::MessageQueue::notify() {
  mCondition.notify_all();
}
