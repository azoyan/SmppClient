#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <condition_variable>
#include <functional>
#include <chrono>

#include "pdu/BindTransceiver.h"
#include "pdu/BindTransceiverResponse.h"
#include "logic/TcpClient.h"

nsSmppClient::BindTransceiver createBindTransceiver() {
  std::string systemId, password, systemType;
  int sequenceNumber;
  std::cin >> systemId;
  std::cin >> password;
  std::cin >> systemType;
  std::cin >> sequenceNumber;
  nsSmppClient::BindTransceiver  pdu;
  pdu.setSystemId(systemId);
  pdu.setPassword(password);
  pdu.setSystemType(systemType);
  pdu.setSequenceNumber(sequenceNumber);
  return pdu;
}

void print(const nsSmppClient::BindTransceiverResponse& pduBindTransceiverResponse) {
  uint32_t commandLength    = pduBindTransceiverResponse.commandLength();
  uint32_t commandId        = pduBindTransceiverResponse.commandId();
  uint32_t commandStatus    = pduBindTransceiverResponse.commandStatus();
  uint32_t sequenceNumber   = pduBindTransceiverResponse.sequenceNumber();

  std::string systemId      = pduBindTransceiverResponse.systemId();

  std::string commandIdName = commandIdToString(commandId);

  std::string commandStatusName = errorCodeToString(commandStatus);

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
  tcpClient.setReceiveBufferSize(nsSmppClient::BindTransceiverResponse::MaxBindTransceiverRespSize);
  tcpClient.setSendBufferSize(nsSmppClient::BindTransceiver::MaxBindTransceiverSize);

  bool isConnected = tcpClient.connect(ipAddress, port);
  if (isConnected) std::cout << "Connected" << std::endl;
  else {
    std::cerr << "Connection error!" << std::endl;
    return 0;
  }

  std::cout << "BIND_TRANSCEIVER format: [system ID] [password] [system type] [sequence number]\n\n";

  std::queue<std::vector<char>> sendingQueue;
  std::condition_variable sendCondition;

  // создаём поток для отправки сообщений
  std::thread sendingThread([&tcpClient, &sendingQueue, &sendCondition] {
    std::mutex mutex;
    while(true) {
      std::unique_lock<std::mutex> lock(mutex);
      sendCondition.wait(lock, [&sendingQueue] { return !sendingQueue.empty(); } );
      std::cout << "in sending  " << std::this_thread::get_id() << std::endl;
      while (!sendingQueue.empty()) {
        auto message = sendingQueue.front();
        sendingQueue.pop();
        tcpClient.sendMessage(message);
      }
      std::cout << "sending end\n";
      mutex.unlock();
    }
  });

  std::queue<std::vector<char>> receivingQueue;

  std::condition_variable receiveCondition;
  // создаём поток для приёма сообщений

  std::thread receivingThread( [&tcpClient, &receivingQueue, &receiveCondition] {
    std::mutex mutex;
    while (true) {
      std::unique_lock<std::mutex> lock(mutex);
      std::cout << "in read  " << std::this_thread::get_id() << std::endl;
      tcpClient.read();

      while(tcpClient.hasResponses()) {
        auto msg = tcpClient.takeMessage();
        receivingQueue.push(msg);
      }
      receiveCondition.wait(lock, [&receivingQueue] { return !receivingQueue.empty(); } );
      mutex.unlock();
      std::cout << "read done\n"  ;
    }
  });

  bool needWork = true;

  while (needWork) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    while (!receivingQueue.empty()) {
      nsSmppClient::BindTransceiverResponse pduBindTransceiverResponse;
      pduBindTransceiverResponse.setData(receivingQueue.front());
      receivingQueue.pop();
      print(pduBindTransceiverResponse);
      bool ok = pduBindTransceiverResponse.commandStatus() == CommandStatus::ESME_ROK;
      if (ok) {
        std::cout << "Connection was successful" << std::endl;
      }
    }
    if (sendingQueue.empty()) {
      auto pdu = createBindTransceiver().byteArray();
      sendingQueue.push(pdu);
    }
    receiveCondition.notify_all();
    sendCondition.notify_all();
  }

  receivingThread.join();
  sendingThread.join();
  return 0;
}
