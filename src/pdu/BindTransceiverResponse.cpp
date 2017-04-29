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

void nsSmppClient::BindTransceiverResponse::setCommandLength(uint32_t commandLength) {
  mCommandLength = commandLength;
}

void nsSmppClient::BindTransceiverResponse::setCommandId(uint32_t commandId) {
  mCommandId = commandId;
}

void nsSmppClient::BindTransceiverResponse::setSequenceNumber(uint32_t sequenceNumber) {
  mSequenceNumber = sequenceNumber;
}

void nsSmppClient::BindTransceiverResponse::setCommandStatus(uint32_t commandStatus){
  mCommandStatus = commandStatus;
}

void nsSmppClient::BindTransceiverResponse::setData(const char* data) {
  mCommandLength  = dataToInt32(data);
  if (mCommandLength > MinBindTransceiverRespSize &&
      mCommandLength < MaxBindTransceiverRespSize) {

    mCommandId      = dataToInt32(data + sizeof(mCommandLength));
    mCommandStatus  = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId));
    mSequenceNumber = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId) + sizeof(mCommandStatus));

    const char* systemIdBegin = data + HeaderLength;
    size_t systemIdSize = mCommandLength - (HeaderLength);

    mSystemID.assign(systemIdBegin, systemIdSize);
  }
}

void nsSmppClient::BindTransceiverResponse::setData(std::vector<char> data) {
  setData(data.data());
}

void nsSmppClient::BindTransceiverResponse::clear() {
  mCommandLength  = 0;
  mCommandId      = 0;
  mCommandStatus  = 0;
  mSequenceNumber = 0;
  mSystemID.clear();
}

uint32_t nsSmppClient::BindTransceiverResponse::commandLength() const {
  return mCommandLength;
}

uint32_t nsSmppClient::BindTransceiverResponse::commandId() const {
  return mCommandId;
}

uint32_t nsSmppClient::BindTransceiverResponse::sequenceNumber() const {
  return mSequenceNumber;
}

uint32_t nsSmppClient::BindTransceiverResponse::commandStatus() const {
  return mCommandStatus;
}

std::string nsSmppClient::BindTransceiverResponse::systemId() const {
  return mSystemID;
}

uint32_t nsSmppClient::BindTransceiverResponse::dataToInt32(const char* data) {
  return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

}

