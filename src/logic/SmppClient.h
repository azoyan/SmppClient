#ifndef SMPPCLIENT_H
#define SMPPCLIENT_H

#include <string>
#include <queue>

namespace  nsSmppClient {
  class SmppClient {
    using Socket = int;

  public:
    SmppClient();
    ~SmppClient();

    bool connect(const std::string& ipAddress, const std::string& port);
    void setReceiveBufferSize(size_t bufferSize);

    void read();
    bool hasResponses();

    std::vector<char> takeMessage();
    void sendMessage(const std::vector<char>& message);

private:
    int mSendBufferSize;
    int mReceiveBufferSize;
    Socket mSocket;
    std::vector<char> mReceivedMessage;
  };
}
#endif // SMPPCLIENT_H
