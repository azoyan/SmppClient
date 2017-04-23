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

    void push(const std::string& message);
    void pop();
    std::string take();
    bool isEmpty() const;
    size_t size() const;

    std::queue<std::string>& queue();

    std::mutex mMutex;
  private:
    SmppClient& mSmppClient;
    std::queue<std::string> mQueue;

  };
}

#endif // MESSAGEQUEUE_H
