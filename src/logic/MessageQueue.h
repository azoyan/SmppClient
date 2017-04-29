#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "TcpClient.h"
#include <queue>

#include <mutex>
#include <condition_variable>
#include <string>
#include <functional>

namespace nsSmppClient {
  class MessageQueue {
  public:
    MessageQueue(TcpClient& smppClient);

    void sending();
    void receiving();

    void push(const std::vector<char>& message);
    void pop();
    std::vector<char> take();
    bool isEmpty() const;
    size_t size() const;    
    void notify();


  private:
    TcpClient& mTcpClient;
    std::function<void()> callFunction;

    std::queue<std::vector<char>> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
  };
}

#endif // MESSAGEQUEUE_H
