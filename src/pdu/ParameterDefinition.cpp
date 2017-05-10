#include "ParameterDefinition.h"



std::string commandIdToString(int commandId) {
  static std::map<uint32_t, std::string> map =
  {
    { GenerickNack        ,   "GenerickNack"        },
    { BindReceiver        ,   "BindReceiver"        },
    { BindReceiverResp    ,   "BindReceiverResp"    },
    { BindTransmitter     ,   "BindTransmitter"     },
    { BindTransmitterResp ,   "BindTransmitterResp" },
    { QuerySm             ,   "QuerySm"             },
    { QuerySmResp         ,   "QuerySmResp"         },
    { SubmitSm            ,   "SubmitSm"            },
    { SubmitSmResp        ,   "SubmitSmResp"        },
    { DeliverSm           ,   "DeliverSm"           },
    { DeliverSmResp       ,   "DeliverSmResp"       },
    { Unbind              ,   "Unbind"              },
    { UnbindResp          ,   "UnbindResp"          },
    { ReplaceSm           ,   "ReplaceSm"           },
    { ReplaceSmResp       ,   "ReplaceSmResp"       },
    { CancelSm            ,   "CancelSm"            },
    { CancelSmResp        ,   "CancelSmResp"        },
    { BindTransceiver     ,   "BindTransceiver"     },
    { BindTransceiverResp ,   "BindTransceiverResp" },
    { Outbind             ,   "Outbind"             },
    { EnquireLink         ,   "EnquireLink"         },
    { EnquireLinkResp     ,   "EnquireLinkResp"     },
    { SubmitMulti         ,   "SubmitMulti"         },
    { SubmitMultiResp     ,   "SubmitMultiResp"     },
    { AlertNotification   ,   "AlertNotification"   },
    { DataSm              ,   "DataSm"              },
    { DataSmResp          ,   "DataSmResp"          }
  };

  return map[commandId];
}

std::string errorCodeToString(int commandStatus) {
  static std::map<uint32_t, std::string> map =
  {
    { 0x00000000, "ESME_ROK"              },
    { 0x00000001, "ESME_RINVMSGLEN"       },
    { 0x00000002, "ESME_RINVCMDLEN"       },
    { 0x00000003, "ESME_RINVCMDID"        },
    { 0x00000004, "ESME_RINVBNDSTS"       },
    { 0x00000005, "ESME_RALYBND"          },
    { 0x00000006, "ESME_RINVPRTFLG"       },
    { 0x00000007, "ESME_RINVREGDLVFLG"    },
    { 0x00000008, "ESME_RSYSERR"          },
    { 0x0000000A, "ESME_RINVSRCADR"       },
    { 0x0000000B, "ESME_RINVDSTADR"       },
    { 0x0000000C, "ESME_RINVMSGID"        },
    { 0x0000000D, "ESME_RBINDFAIL"        },
    { 0x0000000E, "ESME_RINVPASWD"        },
    { 0x0000000F, "ESME_RINVSYSID"        },
    { 0x00000011, "ESME_RCANCELFAIL"      },
    { 0x00000013, "ESME_RREPLACEFAIL"     },
    { 0x00000014, "ESME_RMSGQFUL"         },
    { 0x00000015, "ESME_RINVSERTYP"       },
    { 0x00000033, "ESME_RINVNUMDESTS"     },
    { 0x00000034, "ESME_RINVDLNAME"       },
    { 0x00000040, "ESME_RINVDESTFLAG"     },
    { 0x00000042, "ESME_RINVSUBREP"       },
    { 0x00000043, "ESME_RINVESMCLASS"     },
    { 0x00000044, "ESME_RCNTSUBDL"        },
    { 0x00000045, "ESME_RSUBMITFAIL"      },
    { 0x00000048, "ESME_RINVSRCTON"       },
    { 0x00000049, "ESME_RINVSRCNPI"       },
    { 0x00000050, "ESME_RINVDSTTON"       },
    { 0x00000051, "ESME_RINVDSTNPI"       },
    { 0x00000053, "ESME_RINVSYSTYP"       },
    { 0x00000054, "ESME_RINVREPFLAG"      },
    { 0x00000055, "ESME_RINVNUMMSGS"      },
    { 0x00000058, "ESME_RTHROTTLED"       },
    { 0x00000061, "ESME_RINVSCHED"        },
    { 0x00000062, "ESME_RINVEXPIRY"       },
    { 0x00000063, "ESME_RINVDFTMSGID"     },
    { 0x00000064, "ESME_RX_T_APPN"        },
    { 0x00000065, "ESME_RX_P_APPN"        },
    { 0x00000066, "ESME_RX_R_APPN"        },
    { 0x00000067, "ESME_RQUERYFAIL"       },
    { 0x000000C0, "ESME_RINVOPTPARSTREAM" },
    { 0x000000C1, "ESME_ROPTPARNOTALLWD"  },
    { 0x000000C2, "ESME_RINVPARLEN"       },
    { 0x000000C3, "ESME_RMISSINGOPTPARAM" },
    { 0x000000C4, "ESME_RINVOPTPARAMVAL"  },
    { 0x000000FE, "ESME_RDELIVERYFAILURE" },
    { 0x000000FF, "ESME_RUNKNOWNERR"      },
  };

  return map[commandStatus];
}
