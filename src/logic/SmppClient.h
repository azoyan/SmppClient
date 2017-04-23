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

    std::string takeMessage();
    void sendMessage(const std::string& message);

private:
    int mSendBufferSize;
    int mReceiveBufferSize;
    Socket mSocket;
    std::string mReceivedMessage;

    int setNonblocking(int fd);

  };
}
#endif // SMPPCLIENT_H
