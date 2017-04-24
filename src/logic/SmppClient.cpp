#include "SmppClient.h"

#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <iostream>
#include <unistd.h>

#include <string>
#include "../pdu/BindTransceiver.h"
#include "../pdu/BindTransceiverResponse.h"

nsSmppClient::SmppClient::SmppClient()
: mSendBufferSize(BindTransceiver::MaxBindTransceiverSize)
, mReceiveBufferSize(BindTransceiverResponse::MaxBindTransceiverRespSize)
, mSocket(0)
{

}

nsSmppClient::SmppClient::~SmppClient() {
  ::close(mSocket);
}

bool nsSmppClient::SmppClient::connect(const std::string& ipAddress, const std::string& port) {
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
  freeaddrinfo(res);
  return ok;
}

void nsSmppClient::SmppClient::setReceiveBufferSize(size_t receiveBufferSize) {
  mReceiveBufferSize = receiveBufferSize;
}

void nsSmppClient::SmppClient::read() {
  char receiveBuffer[mReceiveBufferSize];
  int numbytes = recv(mSocket, receiveBuffer, mReceiveBufferSize, MSG_NOSIGNAL );
  receiveBuffer[numbytes] = '\0';

  if (numbytes != -1) {
    std::copy(receiveBuffer, receiveBuffer + mReceiveBufferSize, std::back_inserter(mReceivedMessage));
  }
}

bool nsSmppClient::SmppClient::hasResponses() {
  return !mReceivedMessage.empty();
}

std::vector<char> nsSmppClient::SmppClient::takeMessage() {
  std::vector<char> s = mReceivedMessage;
  mReceivedMessage.clear();
  return s;
}

void nsSmppClient::SmppClient::sendMessage(const std::vector<char>& message) {
  ssize_t sended = send(mSocket, message.data(), message.size(), MSG_NOSIGNAL);
  if (sended < 0) std::cerr << "Couldn't send" << std::endl;
}
