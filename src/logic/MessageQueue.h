#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "SmppClient.h"
#include <queue>

#include <mutex>
#include <string>

namespace nsSmppClient {
  class MessageQueue {
  public:
    MessageQueue(SmppClient& smppClient);    

    void sending();
    void receiving();

    void push(const std::vector<char>& message);
    void pop();
    std::vector<char> take();
    bool isEmpty() const;
    size_t size() const;    

  private:
    SmppClient& mSmppClient;
    std::queue<std::vector<char>> mQueue;
    std::mutex mMutex;
  };
}

#endif // MESSAGEQUEUE_H
