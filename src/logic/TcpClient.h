#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>
#include <queue>

namespace  nsSmppClient {
  class TcpClient {
    using Socket = int;

  public:
    TcpClient();
    ~TcpClient();

    bool connect(const std::string& ipAddress, const std::string& port);
    void setReceiveBufferSize(size_t bufferSize);

    void read();
    bool hasResponses();

    std::vector<char> takeMessage();
    void sendMessage(const std::vector<char>& message);
    void sendMessage(const char* data);

private:
    int mSendBufferSize;
    int mReceiveBufferSize;
    Socket mSocket;
    std::vector<char> mReceivedMessage;
  };
}
#endif // TCPCLIENT_H
