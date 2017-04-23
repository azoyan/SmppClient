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
  mCommandLength  = dataToInt32(data);
  if (mCommandLength < MaxBindTransceiverRespSize) {
    mCommandId      = dataToInt32(data + sizeof(mCommandLength));
    mCommandStatus  = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId));
    mSequenceNumber = dataToInt32(data + sizeof(mCommandLength) + sizeof(mCommandId) + sizeof(mCommandStatus));
    const char* begin = data
                      + sizeof(mCommandLength)
                      + sizeof(mCommandId)
                      + sizeof(mCommandStatus)
                      + sizeof(mSequenceNumber);

    size_t size = mCommandLength - (16);

    mSystemID.assign(begin, size);

    std::cout << mSystemID << std::endl;
  }
}

void nsSmppClient::BindTransceiverResponse::clear() {
  mCommandLength  = 0;
  mCommandId      = 0;
  mCommandStatus  = 0;
  mSequenceNumber = 0;
  mSystemID.clear();
}

