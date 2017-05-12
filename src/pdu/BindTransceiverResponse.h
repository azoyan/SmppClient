#ifndef BINDTRANSCEIVERRESPONSE_H
#define BINDTRANSCEIVERRESPONSE_H

#include "ParameterDefinition.h"
#include <string>
#include <vector>
#include <byteswap.h>
namespace nsSmppClient {
  class BindTransceiverResponse {
  public:
    BindTransceiverResponse();

    void setCommandLength(uint32_t commandLength);
    void setCommandId(uint32_t commandId);
    void setSequenceNumber(uint32_t sequenceNumber);
    void setCommandStatus(uint32_t commandStatus);

    void setData(const char* data);
    void setData(std::vector<char> data);

    void clear();

    uint32_t commandLength() const;
    uint32_t commandId() const;
    uint32_t commandStatus() const;
    uint32_t sequenceNumber() const;

    std::string systemId() const;

  private:
    static uint32_t dataToInt32(const char* data);

  private:
    //header
    uint32_t mCommandLength;
    uint32_t mCommandId;
    uint32_t mCommandStatus;
    uint32_t mSequenceNumber;
    //body
    std::string mSystemID;
    enum { HeaderLength = sizeof(mCommandId)
           + sizeof(mCommandId)
           + sizeof(mCommandStatus)
           + sizeof(mSequenceNumber) };
    enum { SystemIdMaxLength = 16 };
  public:
    enum { MinBindTransceiverRespSize = HeaderLength,
           MaxBindTransceiverRespSize = MinBindTransceiverRespSize + SystemIdMaxLength };
  };
}

#endif // BINDTRANSCEIVERRESPONSE_H
