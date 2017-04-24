#include "BindTransceiver.h"
#include <algorithm>
#include <sstream>

#include <cstring>
#include <iostream>
#include "../Global.h"

#include <algorithm>


nsSmppClient::BindTransceiver::BindTransceiver()
  : mCommandId(CommandId::BindTransceiverId)
  , mCommandStatus(0)
  , mSequenceNumber(42)
  , mInterfaceVersion(5)
  , mAddrTon(0)
  , mAddrNpi(0)
  , mAddressRange()
  , mIsCorrect(false)
{

}

void nsSmppClient::BindTransceiver::setSequenceNumber(int32_t sequenceNumber) {
  mSequenceNumber = sequenceNumber;
}

void nsSmppClient::BindTransceiver::setSystemId(const std::string& systemId) {  
  mSystemID = systemId;
}

void nsSmppClient::BindTransceiver::setPassword(const std::string& password) {

  mPassword = password;
}

void nsSmppClient::BindTransceiver::setSystemType(const std::string& systemType) {  
  mSystemType = systemType;
}

void nsSmppClient::BindTransceiver::setInterfaceVersion(int8_t interfaceVersion) {
  mInterfaceVersion = interfaceVersion;
}

void nsSmppClient::BindTransceiver::setAddrTon(int8_t addrTon) {
  mAddrTon = addrTon;
}

void nsSmppClient::BindTransceiver::setAddrNpi(int8_t addrNpi){
  mAddrNpi = addrNpi;
}

void nsSmppClient::BindTransceiver::setAddresRange(const std::__cxx11::string& addressRange) {  
  mAddressRange = addressRange;
}

bool nsSmppClient::BindTransceiver::isCorrect() const {
  bool ok  = mSystemID.size()     <= SystemIdMaxLength;
  ok = ok && mPassword.size()     <= PasswordMaxLength;
  ok = ok && mSystemType.size()   <= SystemTypeMaxLength;
  ok = ok && mAddressRange.size() <= AddressRangeMaxLength;
  return ok;
}

std::vector<char> nsSmppClient::BindTransceiver::byteArray() const {
  int32_t length = DefaultLength
                   + mSystemID.size() + 1
                   + mPassword.size() + 1
                   + mSystemType.size() + 1
                   + mAddressRange.size() + 1;

  std::vector<char> result;
  result.reserve(length);

  std::vector<char> commandLength  = intToBytes(length);
  std::vector<char> commandId      = intToBytes(mCommandId);
  std::vector<char> commandStatus  = intToBytes(mCommandStatus);
  std::vector<char> sequenceNumber = intToBytes(mSequenceNumber);

  result.insert(result.end(), commandLength.begin(),  commandLength.end());
  result.insert(result.end(), commandId.begin(),      commandId.end());
  result.insert(result.end(), commandStatus.begin(),  commandStatus.end());
  result.insert(result.end(), sequenceNumber.begin(), sequenceNumber.end());

  result.insert(result.end(), mSystemID.begin(),   mSystemID.end());
  result.push_back('\0');
  result.insert(result.end(), mPassword.begin(),   mPassword.end());
  result.push_back('\0');
  result.insert(result.end(), mSystemType.begin(), mSystemType.end());
  result.push_back('\0');

  result.push_back(mInterfaceVersion);
  result.push_back(mAddrTon);
  result.push_back(mAddrNpi);

  result.insert(result.end(), mAddressRange.begin(), mAddressRange.end());
  result.push_back('\0');

//  std::cout << std::endl;

//    std::cout << result.size() << " : size, capacity: " << result.capacity() << std::endl;

  return result;
}

std::vector<char> nsSmppClient::BindTransceiver::intToBytes(int32_t number) {
  std::vector<char> result(sizeof(number));
  for (int i = 0; i < sizeof(number); i++) {
    result.at(3 - i) = number >> (i * 8);
  }
  return result;
}


