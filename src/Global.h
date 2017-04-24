#ifndef GLOBAL_H
#define GLOBAL_H

#include <inttypes.h>
#include <string>
#include <set>

  struct __CommandStatusBase {                                     \
    int number;                                                    \
    std::string name;                                              \
    bool operator==(const int errorCode) const {                   \
      return number == errorCode;                                  \
    }                                                              \
    bool operator<(const __CommandStatusBase& commandStatus) const { \
      return number < commandStatus.number;                        \
    }                                                              \
  };                                                               \


  #define STRUCT_COMMAND_STATUS(ERROR_CODE_NAME, VALUE) \
  struct ERROR_CODE_NAME : __CommandStatusBase {       \
    ERROR_CODE_NAME()                                \
    : __CommandStatusBase{VALUE , #ERROR_CODE_NAME} {} \
    }; \

  static std::set<__CommandStatusBase> CommandsStatusErrors;

namespace nsSmppClient {
  inline int32_t dataToInt32(const char* data) {
    return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
  }
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


 STRUCT_COMMAND_STATUS(ESME_RINVMSGLEN       , 0x00000001 )
 STRUCT_COMMAND_STATUS(ESME_RINVCMDLEN       , 0x00000002 )
 STRUCT_COMMAND_STATUS(ESME_RINVCMDID        , 0x00000003 )
 STRUCT_COMMAND_STATUS(ESME_RINVBNDSTS       , 0x00000004 )
 STRUCT_COMMAND_STATUS(ESME_RALYBND          , 0x00000005 )
 STRUCT_COMMAND_STATUS(ESME_RINVPRTFLG       , 0x00000006 )
 STRUCT_COMMAND_STATUS(ESME_RINVREGDLVFLG    , 0x00000007 )
 STRUCT_COMMAND_STATUS(ESME_RSYSERR          , 0x00000008 )
 STRUCT_COMMAND_STATUS(ESME_RINVSRCADR       , 0x0000000A )
 STRUCT_COMMAND_STATUS(ESME_RINVDSTADR       , 0x0000000B )
 STRUCT_COMMAND_STATUS(ESME_RINVMSGID        , 0x0000000C )
 STRUCT_COMMAND_STATUS(ESME_RBINDFAIL        , 0x0000000D )
 STRUCT_COMMAND_STATUS(ESME_RINVPASWD        , 0x0000000E )
 STRUCT_COMMAND_STATUS(ESME_RINVSYSID        , 0x0000000F )
 STRUCT_COMMAND_STATUS(ESME_RCANCELFAIL      , 0x00000011 )
 STRUCT_COMMAND_STATUS(ESME_RREPLACEFAIL     , 0x00000013 )
 STRUCT_COMMAND_STATUS(ESME_RMSGQFUL         , 0x00000014 )
 STRUCT_COMMAND_STATUS(ESME_RINVSERTYP       , 0x00000015 )
 STRUCT_COMMAND_STATUS(ESME_RINVNUMDESTS     , 0x00000033 )
 STRUCT_COMMAND_STATUS(ESME_RINVDLNAME       , 0x00000034 )
 STRUCT_COMMAND_STATUS(ESME_RINVDESTFLAG     , 0x00000040 )
 STRUCT_COMMAND_STATUS(ESME_RINVSUBREP       , 0x00000042 )
 STRUCT_COMMAND_STATUS(ESME_RINVESMCLASS     , 0x00000043 )
 STRUCT_COMMAND_STATUS(ESME_RCNTSUBDL        , 0x00000044 )
 STRUCT_COMMAND_STATUS(ESME_RSUBMITFAIL      , 0x00000045 )
 STRUCT_COMMAND_STATUS(ESME_RINVSRCTON       , 0x00000048 )
 STRUCT_COMMAND_STATUS(ESME_RINVSRCNPI       , 0x00000049 )
 STRUCT_COMMAND_STATUS(ESME_RINVDSTTON       , 0x00000050 )
 STRUCT_COMMAND_STATUS(ESME_RINVDSTNPI       , 0x00000051 )
 STRUCT_COMMAND_STATUS(ESME_RINVSYSTYP       , 0x00000053 )
 STRUCT_COMMAND_STATUS(ESME_RINVREPFLAG      , 0x00000054 )
 STRUCT_COMMAND_STATUS(ESME_RINVNUMMSGS      , 0x00000055 )
 STRUCT_COMMAND_STATUS(ESME_RTHROTTLED       , 0x00000058 )
 STRUCT_COMMAND_STATUS(ESME_RINVSCHED        , 0x00000061 )
 STRUCT_COMMAND_STATUS(ESME_RINVEXPIRY       , 0x00000062 )
 STRUCT_COMMAND_STATUS(ESME_RINVDFTMSGID     , 0x00000063 )
 STRUCT_COMMAND_STATUS(ESME_RX_T_APPN        , 0x00000064 )
 STRUCT_COMMAND_STATUS(ESME_RX_P_APPN        , 0x00000065 )
 STRUCT_COMMAND_STATUS(ESME_RX_R_APPN        , 0x00000066 )
 STRUCT_COMMAND_STATUS(ESME_RQUERYFAIL       , 0x00000067 )
 STRUCT_COMMAND_STATUS(ESME_RINVOPTPARSTREAM , 0x000000C0 )
 STRUCT_COMMAND_STATUS(ESME_ROPTPARNOTALLWD  , 0x000000C1 )
 STRUCT_COMMAND_STATUS(ESME_RINVPARLEN       , 0x000000C2 )
 STRUCT_COMMAND_STATUS(ESME_RMISSINGOPTPARAM , 0x000000C3 )
 STRUCT_COMMAND_STATUS(ESME_RINVOPTPARAMVAL  , 0x000000C4 )
 STRUCT_COMMAND_STATUS(ESME_RDELIVERYFAILURE , 0x000000FE )
 STRUCT_COMMAND_STATUS(ESME_RUNKNOWNERR      , 0x000000FF )
}

#endif // GLOBAL_H
