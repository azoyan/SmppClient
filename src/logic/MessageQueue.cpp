#include "MessageQueue.h"
#include <cassert>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

#include "../pdu/BindTransceiverResponse.h"

nsSmppClient::MessageQueue::MessageQueue(TcpClient& smppClient)
: mTcpClient(smppClient)
{

}

void nsSmppClient::MessageQueue::sending() {
  while(true) {
  std::unique_lock<std::mutex> lock(mMutex);
  mCondition.wait(lock, [this] { return !mQueue.empty(); } );
    std::cout << "in sending  " << std::this_thread::get_id() << std::endl;
    while (!mQueue.empty()) {
      auto message = mQueue.front();
      mQueue.pop();
      mTcpClient.sendMessage(message);
    }
    std::cout << "sending end\n";
    mMutex.unlock();
  }
}

void nsSmppClient::MessageQueue::receiving() {
  while (true) {
//    std::unique_lock<std::mutex> lock(mMutex);
//    mCondition.wait(lock, [this] { return !mQueue.empty(); } );
    mMutex.lock();
    std::cout << "in read  " << std::this_thread::get_id() << std::endl;
    mTcpClient.read();
    while(mTcpClient.hasResponses()) {
      auto msg = mTcpClient.takeMessage();
      mQueue.push(msg);
    }
    std::cout << "read done\n"  ;
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
