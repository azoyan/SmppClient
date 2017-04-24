#include "BindTransceiverResponse.h"
#include "../Global.h"

#include <iostream>

nsSmppClient::BindTransceiverResponse::BindTransceiverResponse()
: mCommandLength (0)
, mCommandId     (0)
, mCommandStatus (0)
, mSequenceNumber(0)
{

}

void nsSmppClient::BindTransceiverResponse::setData(const char* data) {

  std::cout << std::endl;
  for (char i = 0; i < MaxBindTransceiverRespSize; ++i) {
    std::cout << static_cast<int>(data[i]) << " ";
  }
  std::cout << std::endl;


  mCommandLength  = dataToInt32(data);
  if (mCommandLength < MaxBindTransceiverRespSize &&
      mCommandLength > MinBindTransceiverRespSize) {

    mCommandId      = dataToInt32(data + sizeof(mCommandLength));
    mCommandStatus  = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId));
    mSequenceNumber = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId) + sizeof(mCommandStatus));

    const char* systemIdBegin = data + HeaderLength;
    size_t systemIdSize = mCommandLength - (HeaderLength);

    mSystemID.assign(systemIdBegin, systemIdSize);
  }
}

void nsSmppClient::BindTransceiverResponse::clear() {
  mCommandLength  = 0;
  mCommandId      = 0;
  mCommandStatus  = 0;
  mSequenceNumber = 0;
  mSystemID.clear();
}

int32_t nsSmppClient::BindTransceiverResponse::commandLength() const {
  return mCommandLength;
}

int32_t nsSmppClient::BindTransceiverResponse::commandId() const {
  return mCommandId;
}

int32_t nsSmppClient::BindTransceiverResponse::sequenceNumber() const {
  return mSequenceNumber;
}

int32_t nsSmppClient::BindTransceiverResponse::commandStatus() const {
  return mCommandStatus;
}

std::string nsSmppClient::BindTransceiverResponse::systemId() const {
  return mSystemID;
}

