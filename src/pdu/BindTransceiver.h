#ifndef BINDTRANSCEIVER_H
#define BINDTRANSCEIVER_H

#include <inttypes.h>
#include <string>
#include <ostream>

#include <vector>

namespace nsSmppClient {
  class BindTransceiver {
    enum { DefaultLength = 19 }; //4 * int + 3  * char

    enum { SystemIdMaxLength     = 16,
           PasswordMaxLength     = 9,
           SystemTypeMaxLength   = 13,
           AddressRangeMaxLength = 41 };

    enum CommandId { BindTransceiverId = 0x00000009 };
  public:
    BindTransceiver();

    enum { MaxBindTransceiverSize = 98 };

    void setSystemId(const std::string& systemId);
    void setPassword(const std::string& password);
    void setSystemType(const std::string& systemType);
    void setInterfaceVersion(int8_t interfaceVersion);
    void setAddrTon(int8_t addrTon);
    void setAddrNpi(int8_t addrNpi);
    void setAddresRange(const std::string& addressRange);
  public:
    bool isCorrect() const;
    std::vector<char> byteArray() const;

  private:
    //header
    int32_t mCommandLength;
    int32_t mCommandId;
    int32_t mCommandStatus;
    int32_t mSequenceNumber;

    //body
    std::string mSystemID;
    std::string mPassword;
    std::string mSystemType;
    char mInterfaceVersion;
    char mAddrTon;
    char mAddrNpi;
    std::string mAddressRange;

  private:
    bool mIsCorrect;
  };
}

#endif // BINDTRANSCEIVER_H
