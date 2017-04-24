#include <iostream>
#include <thread>

#include "logic/SmppClient.h"
#include "logic/MessageQueue.h"
#include <mutex>
#include "pdu/BindTransceiver.h"
#include "pdu/BindTransceiverResponse.h"

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

  nsSmppClient::SmppClient smppClient;
  nsSmppClient::MessageQueue sendingMessageQueue(smppClient);
  nsSmppClient::MessageQueue receivingMessageQueue(smppClient);

  bool isConnected = smppClient.connect(ipAddress, port);
  if (isConnected) std::cout << "Connected" << std::endl;
  else {
   std::cerr << "Connection error!" << std::endl;
   return 0;
   }


  //создаём поток для приёма сообщений
  std::thread receivingThread(&nsSmppClient::MessageQueue::receiving, &receivingMessageQueue);
  //создаём поток для отправки сообщений
  std::thread sendingThread(&nsSmppClient::MessageQueue::sending, &sendingMessageQueue);

  //отдельный поток на ввод, так как cin блокирует вывод
  std::thread inputThread([&sendingMessageQueue] {
    std::mutex mutex;
    while(true) {
      std::string systemId, password, systemType;
      int version, sequenceNumber;
      mutex.lock();
      std::cout << "BIND_TRANSCEIVER format: [system ID] [password] [system type] [version] [sequence number]\n";
      std::cin >> systemId;
      std::cin >> password;
      std::cin >> systemType;
      std::cin >> version;
      std::cin >> sequenceNumber;
      nsSmppClient::BindTransceiver pduBindTransceiver;
      pduBindTransceiver.setSystemId(systemId);
      pduBindTransceiver.setPassword(password);
      pduBindTransceiver.setSystemType(systemType);
      pduBindTransceiver.setInterfaceVersion(version);
      pduBindTransceiver.setSequenceNumber(sequenceNumber);


      std::cout << "\nsended message: \n";
      std::vector<char> v = pduBindTransceiver.byteArray();
      sendingMessageQueue.push(pduBindTransceiver.byteArray());
      mutex.unlock();

    }
  } );

  while (true) {
    if (!receivingMessageQueue.isEmpty()) {
      std::vector<char> receivedMessage = receivingMessageQueue.take();
//      std::cout << "Received message: " << receivedMessage.data() << " size: " << receivedMessage.size() << std::endl;
      nsSmppClient::BindTransceiverResponse pduBindTransceiverResponse;
      pduBindTransceiverResponse.setData(receivedMessage.data());
      std::cout
      << "Command Length: "  << pduBindTransceiverResponse.commandLength() << std::endl
      << "Command ID: "      << pduBindTransceiverResponse.commandId() << std::endl
      << "Command Status: "  << pduBindTransceiverResponse.commandStatus() << std::endl
      << "Sequence number: " << pduBindTransceiverResponse.sequenceNumber() << std::endl
      << "System ID: "       << pduBindTransceiverResponse.systemId() << std::endl
      << std::endl;
    }
  }

  sendingThread.join();
  receivingThread.join();
  inputThread.join();
  return 0;
}
