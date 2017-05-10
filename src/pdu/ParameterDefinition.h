#ifndef GLOBAL_H
#define GLOBAL_H

#include <inttypes.h>
#include <string>
#include <map>

std::string errorCodeToString(int commandStatus);
std::string commandIdToString(int commandId);

enum CommandId {
  GenerickNack        = 0x80000000 ,
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
  DataSmResp          = 0x80000103
};

enum CommandStatus {
  ESME_ROK              = 0x00000000,
  ESME_RINVMSGLEN       = 0x00000001,
  ESME_RINVCMDLEN       = 0x00000002,
  ESME_RINVCMDID        = 0x00000003,
  ESME_RINVBNDSTS       = 0x00000004,
  ESME_RALYBND          = 0x00000005,
  ESME_RINVPRTFLG       = 0x00000006,
  ESME_RINVREGDLVFLG    = 0x00000007,
  ESME_RSYSERR          = 0x00000008,
  ESME_RINVSRCADR       = 0x0000000A,
  ESME_RINVDSTADR       = 0x0000000B,
  ESME_RINVMSGID        = 0x0000000C,
  ESME_RBINDFAIL        = 0x0000000D,
  ESME_RINVPASWD        = 0x0000000E,
  ESME_RINVSYSID        = 0x0000000F,
  ESME_RCANCELFAIL      = 0x00000011,
  ESME_RREPLACEFAIL     = 0x00000013,
  ESME_RMSGQFUL         = 0x00000014,
  ESME_RINVSERTYP       = 0x00000015,
  ESME_RINVNUMDESTS     = 0x00000033,
  ESME_RINVDLNAME       = 0x00000034,
  ESME_RINVDESTFLAG     = 0x00000040,
  ESME_RINVSUBREP       = 0x00000042,
  ESME_RINVESMCLASS     = 0x00000043,
  ESME_RCNTSUBDL        = 0x00000044,
  ESME_RSUBMITFAIL      = 0x00000045,
  ESME_RINVSRCTON       = 0x00000048,
  ESME_RINVSRCNPI       = 0x00000049,
  ESME_RINVDSTTON       = 0x00000050,
  ESME_RINVDSTNPI       = 0x00000051,
  ESME_RINVSYSTYP       = 0x00000053,
  ESME_RINVREPFLAG      = 0x00000054,
  ESME_RINVNUMMSGS      = 0x00000055,
  ESME_RTHROTTLED       = 0x00000058,
  ESME_RINVSCHED        = 0x00000061,
  ESME_RINVEXPIRY       = 0x00000062,
  ESME_RINVDFTMSGID     = 0x00000063,
  ESME_RX_T_APPN        = 0x00000064,
  ESME_RX_P_APPN        = 0x00000065,
  ESME_RX_R_APPN        = 0x00000066,
  ESME_RQUERYFAIL       = 0x00000067,
  ESME_RINVOPTPARSTREAM = 0x000000C0,
  ESME_ROPTPARNOTALLWD  = 0x000000C1,
  ESME_RINVPARLEN       = 0x000000C2,
  ESME_RMISSINGOPTPARAM = 0x000000C3,
  ESME_RINVOPTPARAMVAL  = 0x000000C4,
  ESME_RDELIVERYFAILURE = 0x000000FE,
  ESME_RUNKNOWNERR      = 0x000000FF
};

#endif // GLOBAL_H
