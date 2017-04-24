#ifndef GLOBAL_H
#define GLOBAL_H

#include <inttypes.h>

namespace nsSmppClient {
  inline int32_t dataToInt32(const char* data) {
    return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
//      return data[0] << 8 | data[1] << 16 | data[2] << 24 | data[3];
  }
}

#endif // GLOBAL_H
