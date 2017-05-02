#include <iostream>
#include <thread>

#include "logic/TcpClient.h"
#include "logic/MessageQueue.h"
#include <mutex>
#include <unistd.h>
#include "pdu/BindTransceiver.h"
#include "pdu/BindTransceiverResponse.h"

#include "logic/TcpClient.h"
#include <condition_variable>
#include <functional>
#include <chrono>

nsSmppClient::BindTransceiver createBindTransceiver() {
  std::string systemId1, password, systemType;
      int sequenceNumber1;
      std::cin >> systemId1;
      std::cin >> password;
      std::cin >> systemType;
      std::cin >> sequenceNumber1;
      nsSmppClient::BindTransceiver  pdu;
      pdu.setSystemId(systemId1);
      pdu.setPassword(password);
      pdu.setSystemType(systemType);
      pdu.setSequenceNumber(sequenceNumber1);
  return pdu;
}

void print(nsSmppClient::BindTransceiverResponse pduBindTransceiverResponse) {
  uint32_t commandLength    = pduBindTransceiverResponse.commandLength();
  uint32_t commandId        = pduBindTransceiverResponse.commandId();
  uint32_t commandStatus    = pduBindTransceiverResponse.commandStatus();
  uint32_t sequenceNumber   = pduBindTransceiverResponse.sequenceNumber();

  std::string systemId      = pduBindTransceiverResponse.systemId();

  std::string commandIdName = CommandId.find(commandId) != CommandId.end() ? CommandId.at(commandId) : "";

  std::string commandStatusName = ErrorCodes.find(commandStatus) != ErrorCodes.end() ? ErrorCodes.at(commandStatus) : "";

  std::cout << std::endl
            << "Command Length: "  << commandLength     << std::endl
            << "commandIdName: "   << commandIdName     << std::endl
            << "Command Status: "  << commandStatusName << std::endl
            << "Sequence number: " << sequenceNumber    << std::endl
            << "System ID: "       << systemId          << std::endl
            << std::endl;
}

int main(int argv, char* argc []) {
  std::string ipAddress;
  std::string port;
  if (argv > 2) {
    ipAddress = argc[1];
    port      = argc[2];
  }
  else {
    std::cout << "Enter address: ";
    std::cin  >> ipAddress;
    std::cout << "Enter port: ";
    std::cin  >> port;
  }

  nsSmppClient::TcpClient tcpClient;
//  tcpClient.setReceiveBufferSize(nsSmppClient::BindTransceiverResponse::MaxBindTransceiverRespSize);
  tcpClient.setReceiveBufferSize(21);
  tcpClient.setSendBufferSize(nsSmppClient::BindTransceiver::MaxBindTransceiverSize);

  bool isConnected = tcpClient.connect(ipAddress, port);
  if (isConnected) std::cout << "Connected" << std::endl;
  else {
    std::cerr << "Connection error!" << std::endl;
    return 0;
  }

  std::cout << "BIND_TRANSCEIVER format: [system ID] [password] [system type] [version] [sequence number]\n\n";

  nsSmppClient::MessageQueue sendingMessageQueue(tcpClient);
  // создаём поток для отправки сообщений
  std::thread sendingThread(&nsSmppClient::MessageQueue::sending, &sendingMessageQueue);


  nsSmppClient::MessageQueue receivingMessageQueue(tcpClient);
  // создаём поток для приёма сообщений
  std::thread receivingThread(&nsSmppClient::MessageQueue::receiving, &receivingMessageQueue);


  while (true) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    if (!receivingMessageQueue.isEmpty()) {
      nsSmppClient::BindTransceiverResponse pduBindTransceiverResponse;
      pduBindTransceiverResponse.setData(receivingMessageQueue.take());
      print(pduBindTransceiverResponse);
    }
    else if (sendingMessageQueue.isEmpty()) {
      sendingMessageQueue.push(createBindTransceiver().byteArray());
      sendingMessageQueue.notify();
    }
//    receivingMessageQueue.notify();
  }
  receivingThread.join();
  sendingThread.join();
  return 0;
}
