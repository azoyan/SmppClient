#include "BindTransceiver.h"
#include <sstream>

#include <cstring>
#include <iostream>
#include "../Global.h"

nsSmppClient::BindTransceiver::BindTransceiver()
: mCommandId(Command::ID::BindTransceiver)
, mCommandStatus(0)
, mSequenceNumber(0)
, mInterfaceVersion(0x34)
, mAddrTon(0)
, mAddrNpi(0)
, mAddressRange("")
, mIsCorrect(false)
{

}

void nsSmppClient::BindTransceiver::setSequenceNumber(uint32_t sequenceNumber) {
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

void nsSmppClient::BindTransceiver::setInterfaceVersion(uint8_t interfaceVersion) {
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
  uint32_t length = DefaultLength
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
  std::cout << "Interface Version: " << static_cast<int>(mInterfaceVersion) << std::endl;

  result.push_back(mAddrTon);
  result.push_back(mAddrNpi);

  result.insert(result.end(), mAddressRange.begin(), mAddressRange.end());
  result.push_back('\0');
  return result;
}

std::vector<char> nsSmppClient::BindTransceiver::intToBytes(uint32_t number) {
  std::vector<char> result(sizeof(number));
  for (int i = 0; i < sizeof(number); i++) {
    result.at(3 - i) = number >> (i * 8) & 0xFF;
  }
  return result;
}


