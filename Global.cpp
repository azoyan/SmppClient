#include "Global.h"

  std::map<uint32_t, std::string> ErrorCodes =
  { { 0x00000000, "ESME_ROK"              },
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

  std::map<uint32_t, std::string> CommandId =
  {
               { 0x80000000 ,   "GenerickNack"        },
               { 0x00000001 ,   "BindReceiver"        },
               { 0x80000001 ,   "BindReceiverResp"    },
               { 0x00000002 ,   "BindTransmitter"     },
               { 0x80000002 ,   "BindTransmitterResp" },
               { 0x00000003 ,   "QuerySm"             },
               { 0x80000003 ,   "QuerySmResp"         },
               { 0x00000004 ,   "SubmitSm"            },
               { 0x80000004 ,   "SubmitSmResp"        },
               { 0x00000005 ,   "DeliverSm"           },
               { 0x80000005 ,   "DeliverSmResp"       },
               { 0x00000006 ,   "Unbind"              },
               { 0x80000006 ,   "UnbindResp"          },
               { 0x00000007 ,   "ReplaceSm"           },
               { 0x80000007 ,   "ReplaceSmResp"       },
               { 0x00000008 ,   "CancelSm"            },
               { 0x80000008 ,   "CancelSmResp"        },
               { 0x00000009 ,   "BindTransceiver"     },
               { 0x80000009 ,   "BindTransceiverResp" },
               { 0x0000000B ,   "Outbind"             },
               { 0x00000015 ,   "EnquireLink"         },
               { 0x80000015 ,   "EnquireLinkResp"     },
               { 0x00000021 ,   "SubmitMulti"         },
               { 0x80000021 ,   "SubmitMultiResp"     },
               { 0x80000102 ,   "AlertNotification"   },
               { 0x00000103 ,   "DataSm"              },
               { 0x80000103 ,   "DataSmResp"          }
  };
