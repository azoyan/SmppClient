#include "BindTransceiver.h"
#include <algorithm>
#include <sstream>

#include <cstring>
#include <iostream>
#include "../Global.h"


nsSmppClient::BindTransceiver::BindTransceiver()
: mCommandLength(DefaultLength)
, mCommandId(CommandId::BindTransceiverId)
, mCommandStatus(177)
, mSequenceNumber(22)
, mInterfaceVersion(0)
, mAddrTon(0)
, mAddrNpi(0)
, mIsCorrect(false)
{

}

void nsSmppClient::BindTransceiver::setSystemId(const std::string& systemId) {
  mCommandLength += systemId.size();
  mSystemID = systemId;
}

void nsSmppClient::BindTransceiver::setPassword(const std::string& password) {
  mCommandLength += password.size();
  mPassword = password;
}

void nsSmppClient::BindTransceiver::setSystemType(const std::string& systemType) {
  mCommandLength += systemType.size();
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
  mCommandLength += addressRange.size();
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
  char commandLength   [sizeof(mCommandLength)];
  char commandId       [sizeof(mCommandId)];
  char commandStatus   [sizeof(mCommandStatus)];
  char sequenceNumber  [sizeof(mSequenceNumber)];
  char interfaceVersion[sizeof(mInterfaceVersion)];
  char addrTon         [sizeof(mAddrTon)];
  char addrNpi         [sizeof(mAddrNpi)];

  memcpy(&commandLength,    &mCommandLength,    sizeof(commandLength));
  memcpy(&commandId,        &mCommandId,        sizeof(commandId));
  memcpy(&commandStatus,    &mCommandStatus,    sizeof(commandStatus));
  memcpy(&sequenceNumber,   &mSequenceNumber,   sizeof(sequenceNumber));
  memcpy(&interfaceVersion, &mInterfaceVersion, sizeof(interfaceVersion));
  memcpy(&addrTon,          &mAddrTon,          sizeof(addrTon));
  memcpy(&addrNpi,          &mAddrNpi,          sizeof(addrNpi));

  char   bytes [mCommandLength];
  strcat(bytes, commandLength);
  strcat(bytes, commandId);
  strcat(bytes, commandStatus);
  strcat(bytes, sequenceNumber);
  strcat(bytes, mSystemID.c_str());
  strcat(bytes, mPassword.c_str());
  strcat(bytes, mSystemType.c_str());
  strcat(bytes, interfaceVersion);
  strcat(bytes, addrTon);
  strcat(bytes, addrNpi);
  strcat(bytes, mAddressRange.c_str());

  std::vector<char> result;
  result.assign(bytes, bytes + sizeof(bytes));

  return result;
}
