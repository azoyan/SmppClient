#ifndef GLOBAL_H
#define GLOBAL_H

#include <inttypes.h>
#include <string>
#include <map>

extern std::map<uint32_t, std::string> ErrorCodes;
extern std::map<uint32_t, std::string> CommandId;
namespace nsSmppClient {


  namespace Command {
    enum ID { GenerickNack        = 0x80000000 ,
              BindReceiver        = 0x00000001 ,
              BindReceiverResp    = 0x80000001 ,
              BindTransmitter     = 0x00000002 ,
              BindTransmitterResp = 0x80000002 ,
              QuerySm             = 0x00000003 ,
              QuerySmResp         = 0x80000003 ,
              SubmitSm            = 0x00000004 ,
              SubmitSmResp        = 0x80000004 ,
              DeliverSm           = 0x00000005 ,
              DeliverSmResp       = 0x80000005 ,
              Unbind              = 0x00000006 ,
              UnbindResp          = 0x80000006 ,
              ReplaceSm           = 0x00000007 ,
              ReplaceSmResp       = 0x80000007 ,
              CancelSm            = 0x00000008 ,
              CancelSmResp        = 0x80000008 ,
              BindTransceiver     = 0x00000009 ,
              BindTransceiverResp = 0x80000009 ,
              Outbind             = 0x0000000B ,
              EnquireLink         = 0x00000015 ,
              EnquireLinkResp     = 0x80000015 ,
              SubmitMulti         = 0x00000021 ,
              SubmitMultiResp     = 0x80000021 ,
              AlertNotification   = 0x80000102 ,
              DataSm              = 0x00000103 ,
              DataSmResp          = 0x80000103 };
  }
}

#endif // GLOBAL_H
