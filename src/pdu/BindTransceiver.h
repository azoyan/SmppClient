#ifndef BINDTRANSCEIVER_H
#define BINDTRANSCEIVER_H

#include <inttypes.h>
#include <string>
#include <ostream>

#include <vector>

namespace nsSmppClient {
  class BindTransceiver {
    enum { SystemIdMaxLength     = 16,
           PasswordMaxLength     = 9,
           SystemTypeMaxLength   = 13,
           AddressRangeMaxLength = 41 };
  public:
    BindTransceiver();

    enum { MaxBindTransceiverSize = 98 };


    void setSequenceNumber(uint32_t sequenceNumber);
    void setSystemId(const std::string& systemId);
    void setPassword(const std::string& password);
    void setSystemType(const std::string& systemType);
    void setInterfaceVersion(uint8_t interfaceVersion);
    void setAddrTon(int8_t addrTon);
    void setAddrNpi(int8_t addrNpi);
    void setAddresRange(const std::string& addressRange);

  public:
    bool isCorrect() const;
    std::vector<char> byteArray() const;

  private:
    //header
    uint32_t mCommandLength;
    uint32_t mCommandId;
    uint32_t mCommandStatus;
    uint32_t mSequenceNumber;

    //body
    std::string mSystemID;
    std::string mPassword;
    std::string mSystemType;
    uint8_t mInterfaceVersion;
    uint8_t mAddrTon;
    uint8_t mAddrNpi;
    std::string mAddressRange;

    static std::vector<char> intToBytes(uint32_t number);

  private:
    enum { DefaultLength = 19 };
    bool mIsCorrect;
  };
}

#endif // BINDTRANSCEIVER_H
