#ifndef BINDTRANSCEIVERRESPONSE_H
#define BINDTRANSCEIVERRESPONSE_H

#include "../Global.h"
#include <string>

namespace nsSmppClient {
  class BindTransceiverResponse {
  public:
    BindTransceiverResponse();
    enum { SystemIdMaxLength = 16 };

    void setData(const char* data);

  public:
    void clear();
  public:
    int32_t sequenceNumber() const;
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
