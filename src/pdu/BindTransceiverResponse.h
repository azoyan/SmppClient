#ifndef BINDTRANSCEIVERRESPONSE_H
#define BINDTRANSCEIVERRESPONSE_H

#include "../Global.h"
#include <string>

namespace nsSmppClient {
  class BindTransceiverResponse {
    enum CommandId { BindTransceiverRespId = 0x80000009 };
    enum { HeaderLength = 16, SystemIdMaxLength = 16 };
  public:
    BindTransceiverResponse();

    void setData(const char* data);
    void clear();
    int32_t sequenceNumber() const;

    enum { MinBindTransceiverRespSize = HeaderLength, MaxBindTransceiverRespSize = 32 };

  private:
    //header
    int32_t mCommandLength;
    int32_t mCommandId;
    int32_t mCommandStatus;
    int32_t mSequenceNumber;
    //body
    std::string mSystemID;
  };
}

#endif // BINDTRANSCEIVERRESPONSE_H
