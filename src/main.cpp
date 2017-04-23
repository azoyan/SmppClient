#include <iostream>
#include <thread>

#include "logic//SmppClient.h"
#include "logic//MessageQueue.h"
#include <unistd.h>
#include <mutex>
#include "pdu/BindTransceiver.h"

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
  else             std::cerr << "Connection error!" << std::endl;

  nsSmppClient::BindTransceiver bt;
  bt.setParameteres("Test", "Test", "WWW", 34, "a");

  std::thread receivingThread(&nsSmppClient::MessageQueue::receiving, &receivingMessageQueue);
  std::thread sendingThread(&nsSmppClient::MessageQueue::sending, &sendingMessageQueue);

  std::thread inputThread([&sendingMessageQueue] {
    while(true) {
      std::string message;
      std::cin >> message;
      sendingMessageQueue.push(message);
    }
  } );

  while (true) {
    if (!receivingMessageQueue.isEmpty()) {
      std::cout << receivingMessageQueue.take();
    }
  }

  sendingThread.join();
  receivingThread.join();
  inputThread.join();
  return 0;
}
