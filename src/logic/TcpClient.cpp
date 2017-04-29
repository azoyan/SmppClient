#include "TcpClient.h"

#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <iostream>
#include <unistd.h>

#include <string>
#include "../pdu/BindTransceiver.h"
#include "../pdu/BindTransceiverResponse.h"

nsSmppClient::TcpClient::TcpClient()
: mSendBufferSize(34)
, mReceiveBufferSize(21)
, mSocket(0)
{

}

nsSmppClient::TcpClient::~TcpClient() {
  ::shutdown(mSocket, SHUT_RDWR);
  ::close(mSocket);
}

bool nsSmppClient::TcpClient::connect(const std::string& ipAddress, const std::string& port) {
  addrinfo hints{};
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE;

  addrinfo* res;
  int status = ::getaddrinfo(ipAddress.data(), port.data(), &hints, &res);
  mSocket    = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  bool ok = mSocket != -1;
  status = ::connect(mSocket, res->ai_addr, res->ai_addrlen);
  ok = ok && (status != -1);
  if(ok) freeaddrinfo(res);
  return ok;
}

void nsSmppClient::TcpClient::setReceiveBufferSize(size_t receiveBufferSize) {
  mReceiveBufferSize = receiveBufferSize;
}

void nsSmppClient::TcpClient::read() {
  char receiveBuffer[mReceiveBufferSize];
  int numbytes = recv(mSocket, receiveBuffer, mReceiveBufferSize, MSG_NOSIGNAL );
  receiveBuffer[numbytes] = '\0';

  if (numbytes != -1) {
    std::copy(receiveBuffer, receiveBuffer + mReceiveBufferSize, std::back_inserter(mReceivedMessage));
  }
}

bool nsSmppClient::TcpClient::hasResponses() {
  return !mReceivedMessage.empty();
}

std::vector<char> nsSmppClient::TcpClient::takeMessage() {
  std::vector<char> s = mReceivedMessage;
  mReceivedMessage.clear();
  return s;
}

void nsSmppClient::TcpClient::sendMessage(const std::vector<char>& message) {
  std::cout << std::endl;
  ssize_t sended = send(mSocket, message.data(), message.size(), 0);

  if (sended < 0) std::cerr << "Couldn't send" << std::endl;
}

void nsSmppClient::TcpClient::sendMessage(const char* data) {
  ssize_t sended = send(mSocket, data, 4, MSG_NOSIGNAL);

  if (sended < 0) std::cerr << "Couldn't send" << std::endl;
}
