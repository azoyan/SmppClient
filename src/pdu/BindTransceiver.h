#ifndef BINDTRANSCEIVER_H
#define BINDTRANSCEIVER_H

#include <inttypes.h>
#include <string>
#include <ostream>

#include <vector>

namespace nsSmppClient {
  class BindTransceiver {
  public:
    BindTransceiver();

    enum { SystemIdMaxLength     = 16,
           PasswordMaxLength     = 9,
           SystemTypeMaxLength   = 13,
           AddressRangeMaxLength = 41 };

    void setParameteres(const std::string& systemId,
                        const std::string& password,
                        const std::string& systemType,
                        int8_t interfaceVersion, const std::__cxx11::string& addressRange);

    bool isCorrect() const;

    std::vector<char> byteArray();

  private:
    //header
    int32_t mCommandLength;
    int32_t mCommandId;
    int32_t mCommandStatus;
    int32_t mSequenceNumber;

    //body
    std::string mSystemID;
    std::string mPassowrd;
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
