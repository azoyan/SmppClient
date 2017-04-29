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

  nsSmppClient::TcpClient smppClient;

  bool isConnected = smppClient.connect(ipAddress, port);
  if (isConnected) std::cout << "Connected" << std::endl;
  else {
    std::cerr << "Connection error!" << std::endl;
    return 0;
  }

  std::cout << "BIND_TRANSCEIVER format: [system ID] [password] [system type] [version] [sequence number]\n\n";

  nsSmppClient::MessageQueue sendingMessageQueue(smppClient);
  // создаём поток для отправки сообщений
  std::thread sendingThread(&nsSmppClient::MessageQueue::sending, std::ref(sendingMessageQueue));


  nsSmppClient::MessageQueue receivingMessageQueue(smppClient);
  // создаём поток для приёма сообщений
  std::thread receivingThread(&nsSmppClient::MessageQueue::receiving, std::ref(receivingMessageQueue));

  while (true) {
    if (!receivingMessageQueue.isEmpty()) {
      nsSmppClient::BindTransceiverResponse pduBindTransceiverResponse;
      pduBindTransceiverResponse.setData(receivingMessageQueue.take());
      uint32_t commandLength    = pduBindTransceiverResponse.commandLength();
      uint32_t commandId        = pduBindTransceiverResponse.commandId();
      uint32_t commandStatus    = pduBindTransceiverResponse.commandStatus();
      uint32_t sequenceNumber   = pduBindTransceiverResponse.sequenceNumber();

      std::string systemId      = pduBindTransceiverResponse.systemId();
      std::string commandIdName = CommandId.at(commandId);

      std::cout << std::endl
                << "Command Length: "  << commandLength << std::endl
                << "commandIdName: "   << commandIdName << std::endl
                << "Command Status: "  << ErrorCodes.at(commandStatus) << std::endl
                << "Sequence number: " << sequenceNumber << std::endl
                << "System ID: "       << systemId << std::endl
                << std::endl;

    }
    if (sendingMessageQueue.isEmpty()) {
      std::string systemId1, password, systemType;
      int sequenceNumber1;
      std::cin >> systemId1;
      std::cin >> password;
      std::cin >> systemType;
      std::cin >> sequenceNumber1;
      nsSmppClient::BindTransceiver pduBindTransceiver;
      pduBindTransceiver.setSystemId(systemId1);
      pduBindTransceiver.setPassword(password);
      pduBindTransceiver.setSystemType(systemType);
      pduBindTransceiver.setSequenceNumber(sequenceNumber1);
      sendingMessageQueue.push(pduBindTransceiver.byteArray());
      sleep(2);
      sendingMessageQueue.notify();

    }
 }
  receivingThread.join();
  sendingThread.join();
  return 0;
}
