
  Name(RDHW,0) 
  Name(CNSB,0)
  Name(CRBR, 0xFFFFFFFF)
  OperationRegion(CRBN, SystemMemory, CRBR, 0x00000008)
  Field(CRBN, AnyAcc, Lock, Preserve)
  {
    MWTT, 8,
    THPN, 8,
    THPD, 8,
    NFCS, 8,
    ALST, 8,
    DPTC, 8,
    RV2I, 8,
    ISDS, 8,        
  }