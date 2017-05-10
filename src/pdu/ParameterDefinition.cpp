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
    { ESME_ROK             , "ESME_ROK"              },
    { ESME_RINVMSGLEN      , "ESME_RINVMSGLEN"       },
    { ESME_RINVCMDLEN      , "ESME_RINVCMDLEN"       },
    { ESME_RINVCMDID       , "ESME_RINVCMDID"        },
    { ESME_RINVBNDSTS      , "ESME_RINVBNDSTS"       },
    { ESME_RALYBND         , "ESME_RALYBND"          },
    { ESME_RINVPRTFLG      , "ESME_RINVPRTFLG"       },
    { ESME_RINVREGDLVFLG   , "ESME_RINVREGDLVFLG"    },
    { ESME_RSYSERR         , "ESME_RSYSERR"          },
    { ESME_RINVSRCADR      , "ESME_RINVSRCADR"       },
    { ESME_RINVDSTADR      , "ESME_RINVDSTADR"       },
    { ESME_RINVMSGID       , "ESME_RINVMSGID"        },
    { ESME_RBINDFAIL       , "ESME_RBINDFAIL"        },
    { ESME_RINVPASWD       , "ESME_RINVPASWD"        },
    { ESME_RINVSYSID       , "ESME_RINVSYSID"        },
    { ESME_RCANCELFAIL     , "ESME_RCANCELFAIL"      },
    { ESME_RREPLACEFAIL    , "ESME_RREPLACEFAIL"     },
    { ESME_RMSGQFUL        , "ESME_RMSGQFUL"         },
    { ESME_RINVSERTYP      , "ESME_RINVSERTYP"       },
    { ESME_RINVNUMDESTS    , "ESME_RINVNUMDESTS"     },
    { ESME_RINVDLNAME      , "ESME_RINVDLNAME"       },
    { ESME_RINVDESTFLAG    , "ESME_RINVDESTFLAG"     },
    { ESME_RINVSUBREP      , "ESME_RINVSUBREP"       },
    { ESME_RINVESMCLASS    , "ESME_RINVESMCLASS"     },
    { ESME_RCNTSUBDL       , "ESME_RCNTSUBDL"        },
    { ESME_RSUBMITFAIL     , "ESME_RSUBMITFAIL"      },
    { ESME_RINVSRCTON      , "ESME_RINVSRCTON"       },
    { ESME_RINVSRCNPI      , "ESME_RINVSRCNPI"       },
    { ESME_RINVDSTTON      , "ESME_RINVDSTTON"       },
    { ESME_RINVDSTNPI      , "ESME_RINVDSTNPI"       },
    { ESME_RINVSYSTYP      , "ESME_RINVSYSTYP"       },
    { ESME_RINVREPFLAG     , "ESME_RINVREPFLAG"      },
    { ESME_RINVNUMMSGS     , "ESME_RINVNUMMSGS"      },
    { ESME_RTHROTTLED      , "ESME_RTHROTTLED"       },
    { ESME_RINVSCHED       , "ESME_RINVSCHED"        },
    { ESME_RINVEXPIRY      , "ESME_RINVEXPIRY"       },
    { ESME_RINVDFTMSGID    , "ESME_RINVDFTMSGID"     },
    { ESME_RX_T_APPN       , "ESME_RX_T_APPN"        },
    { ESME_RX_P_APPN       , "ESME_RX_P_APPN"        },
    { ESME_RX_R_APPN       , "ESME_RX_R_APPN"        },
    { ESME_RQUERYFAIL      , "ESME_RQUERYFAIL"       },
    { ESME_RINVOPTPARSTREAM, "ESME_RINVOPTPARSTREAM" },
    { ESME_ROPTPARNOTALLWD , "ESME_ROPTPARNOTALLWD"  },
    { ESME_RINVPARLEN      , "ESME_RINVPARLEN"       },
    { ESME_RMISSINGOPTPARAM, "ESME_RMISSINGOPTPARAM" },
    { ESME_RINVOPTPARAMVAL , "ESME_RINVOPTPARAMVAL"  },
    { ESME_RDELIVERYFAILURE, "ESME_RDELIVERYFAILURE" },
    { ESME_RUNKNOWNERR     , "ESME_RUNKNOWNERR"      },
  };

  return map[commandStatus];
}
