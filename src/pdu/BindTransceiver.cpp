#include "BindTransceiver.h"
#include <algorithm>
#include <sstream>

#include <cstring>
#include <iostream>
#include "../Global.h"


nsSmppClient::BindTransceiver::BindTransceiver()
: mCommandLength(0)
, mCommandId(CommandId::BindTransceiver)
, mCommandStatus(1)
, mSequenceNumber(1)
, mInterfaceVersion(0)
, mAddrTon(0)
, mAddrNpi(0)
, mIsCorrect(false)
{

}

void nsSmppClient::BindTransceiver::setParameteres(const std::string& systemId,
                                                   const std::string& password,
                                                   const std::string& systemType,
                                                   int8_t interfaceVersion,
                                                   const std::string& addressRange) {

  mIsCorrect = systemId.size() <= SystemIdMaxLength;
  mIsCorrect = mIsCorrect && password.size()     <= PasswordMaxLength;
  mIsCorrect = mIsCorrect && systemType.size()   <= SystemTypeMaxLength;
  mIsCorrect = mIsCorrect && addressRange.size() <= AddressRangeMaxLength;

  if (mIsCorrect) {
    mCommandLength = sizeof(mCommandLength)
                   + sizeof(mCommandId)
                   + sizeof(mCommandStatus)
                   + sizeof(mSequenceNumber)
                   + systemId.size()
                   + password.size()
                   + systemType.size()
                   + sizeof(mInterfaceVersion)
                   + sizeof(mAddrTon)
                   + sizeof(mAddrNpi)
                   + addressRange.size();

    mSystemID         = systemId;
    mPassowrd         = password;
    mSystemType       = systemType;
    mInterfaceVersion = interfaceVersion;
    mAddressRange     = addressRange;
  }
}

bool nsSmppClient::BindTransceiver::isCorrect() const {
  return mIsCorrect;
}

std::vector<char> nsSmppClient::BindTransceiver::byteArray() {
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
  strcat(bytes, mPassowrd.c_str());
  strcat(bytes, mSystemType.c_str());
  strcat(bytes, interfaceVersion);
  strcat(bytes, addrTon);
  strcat(bytes, addrNpi);
  strcat(bytes, mAddressRange.c_str());

  std::vector<char> result;
  result.assign(bytes, bytes + sizeof(bytes));

  return result;
}
