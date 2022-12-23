/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimm.asl
 * 
 * 
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

Scope (_SB)
{
  OperationRegion (SMID, SystemIO, 0xB2, 1)
  Field (SMID, ByteAcc, NoLock, Preserve)
  {
    SMIC, 8,  // SW-SMI ctrl port
  }
  
  // Check if NVDIMM is present based on the bitmap (NVBM)
  // Arg0 – Socket(1..0)
  // Arg1 – Channel(7..0)
  // Arg2 – DIMM(1..0)
  // Return 1 if present, 0 if not
  Method (CNDP, 3, Serialized)
  {
    Shiftleft (1, ToInteger (Arg2), Local0)                       // Local0 = (1 << Dimm)
    Shiftleft (Local0, Multiply (ToInteger (Arg1), 2), Local0)    // Local0 = (Local0 << Channel*2)
    Shiftleft (Local0, Multiply (ToInteger (Arg0), 16), Local0)   // Local0 = (Local0 << Socket*16)
    If (LEqual (And (Local0, NVBM), 0))
    {
      Return (0x00)
    }
    Else {
      Return (0x01)
    }
  }
  
  // NFIT Health Event Notification
  Method (NVDN, 0)
  {
    If (LNotEqual (CNDP (0, 0, 0), 0))
    {
      Notify (\_SB.NVDR.NV00, 0x81)
    }
    If (LNotEqual (CNDP (0, 0, 1), 0))
    {
      Notify (\_SB.NVDR.NV01, 0x81)
    }
    If (LNotEqual (CNDP (0, 1, 0), 0))
    {
      Notify (\_SB.NVDR.NV02, 0x81)
    }
    If (LNotEqual (CNDP (0, 1, 1), 0))
    {
      Notify (\_SB.NVDR.NV03, 0x81)
    }
    If (LNotEqual (CNDP (0, 2, 0), 0))
    {
      Notify (\_SB.NVDR.NV04, 0x81)
    }
    If (LNotEqual (CNDP (0, 2, 1), 0))
    {
      Notify (\_SB.NVDR.NV05, 0x81)
    }
    If (LNotEqual (CNDP (0, 3, 0), 0))
    {
      Notify (\_SB.NVDR.NV06, 0x81)
    }
    If (LNotEqual (CNDP (0, 3, 1), 0))
    {
      Notify (\_SB.NVDR.NV07, 0x81)
    }
    If (LNotEqual (CNDP (0, 4, 0), 0))
    {
      Notify (\_SB.NVDR.NV08, 0x81)
    }
    If (LNotEqual (CNDP (0, 4, 1), 0))
    {
      Notify (\_SB.NVDR.NV09, 0x81)
    }
    If (LNotEqual (CNDP (0, 5, 0), 0))
    {
      Notify (\_SB.NVDR.NV10, 0x81)
    }
    If (LNotEqual (CNDP (0, 5, 1), 0))
    {
      Notify (\_SB.NVDR.NV11, 0x81)
    }
    If (LNotEqual (CNDP (0, 6, 0), 0))
    {
      Notify (\_SB.NVDR.NV12, 0x81)
    }
    If (LNotEqual (CNDP (0, 6, 1), 0))
    {
      Notify (\_SB.NVDR.NV13, 0x81)
    }
    If (LNotEqual (CNDP (0, 7, 0), 0))
    {
      Notify (\_SB.NVDR.NV14, 0x81)
    }
    If (LNotEqual (CNDP (0, 7, 1), 0))
    {
      Notify (\_SB.NVDR.NV15, 0x81)
    }
    If (LNotEqual (CNDP (1, 0, 0), 0))
    {
      Notify (\_SB.NVDR.NV16, 0x81)
    }
    If (LNotEqual (CNDP (1, 0, 1), 0))
    {
      Notify (\_SB.NVDR.NV17, 0x81)
    }
    If (LNotEqual (CNDP (1, 1, 0), 0))
    {
      Notify (\_SB.NVDR.NV18, 0x81)
    }
    If (LNotEqual (CNDP (1, 1, 1), 0))
    {
      Notify (\_SB.NVDR.NV19, 0x81)
    }
    If (LNotEqual (CNDP (1, 2, 0), 0))
    {
      Notify (\_SB.NVDR.NV20, 0x81)
    }
    If (LNotEqual (CNDP (1, 2, 1), 0))
    {
      Notify (\_SB.NVDR.NV21, 0x81)
    }
    If (LNotEqual (CNDP (1, 3, 0), 0))
    {
      Notify (\_SB.NVDR.NV22, 0x81)
    }
    If (LNotEqual (CNDP (1, 3, 1), 0))
    {
      Notify (\_SB.NVDR.NV23, 0x81)
    }
    If (LNotEqual (CNDP (1, 4, 0), 0))
    {
      Notify (\_SB.NVDR.NV24, 0x81)
    }
    If (LNotEqual (CNDP (1, 4, 1), 0))
    {
      Notify (\_SB.NVDR.NV25, 0x81)
    }
    If (LNotEqual (CNDP (1, 5, 0), 0))
    {
      Notify (\_SB.NVDR.NV26, 0x81)
    }
    If (LNotEqual (CNDP (1, 5, 1), 0))
    {
      Notify (\_SB.NVDR.NV27, 0x81)
    }
    If (LNotEqual (CNDP (1, 6, 0), 0))
    {
      Notify (\_SB.NVDR.NV28, 0x81)
    }
    If (LNotEqual (CNDP (1, 6, 1), 0))
    {
      Notify (\_SB.NVDR.NV29, 0x81)
    }
    If (LNotEqual (CNDP (1, 7, 0), 0))
    {
      Notify (\_SB.NVDR.NV30, 0x81)
    }
    If (LNotEqual (CNDP (1, 7, 1), 0))
    {
      Notify (\_SB.NVDR.NV31, 0x81)
    }
  }

  Device (NVDR)   // NVDIMM root device
  {
    Name (_HID, "ACPI0012")
    Method(_STA)
    {
      If (LEqual (NVBM, 0))
      {
        Return (0x00)
      }
      Else {
        Return (0x0F)
      } 
    }
    
    // Arg0 – UUID (set to 2f10e7a4-9e91-11e4-89d3-123b93f75cba)
    // Arg1 – Revision ID (set to 1)
    // Arg2 – Function Index
    // Arg3 - Function Arguments
    Method ( _DSM, 4, Serialized)
    {
      If (LEqual (Arg0, ToUUID("2f10e7a4-9e91-11e4-89d3-123b93f75cba")))
      {
        If (LEqual (ToInteger (Arg2), 0))
        {
          // ARS not supported
          Return (Buffer () {0x1})
        }
      }
    }
    
    // NVDIMM at socket 0 channel 1 DIMM 0
    // Arg0 – UUID (set to 1EE68B36-D4BD-4a1a-9A16-4F8E53D46E05)
    // Arg1 – Revision ID (set to 1)
    // Arg2 - Function Index
    // Arg3 - Function Arguments
    
    // Socket[0] Channel[0] Dimm[0]
    Device (NV00)
    {
      Name (_ADR, 0x0000)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[0] Dimm[1]
    Device (NV01)
    {
      Name (_ADR, 0x0001)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[1] Dimm[0]
    Device (NV02)
    {
      Name (_ADR, 0x0010)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[1] Dimm[1]
    Device (NV03)
    {
      Name (_ADR, 0x0011)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[2] Dimm[0]
    Device (NV04)
    {
      Name (_ADR, 0x0020)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[2] Dimm[1]
    Device (NV05)
    {
      Name (_ADR, 0x0021)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[3] Dimm[0]
    Device (NV06)
    {
      Name (_ADR, 0x0030)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[3] Dimm[1]
    Device (NV07)
    {
      Name (_ADR, 0x0031)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[4] Dimm[0]
    Device (NV08)
    {
      Name (_ADR, 0x0040)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[4] Dimm[1]
    Device (NV09)
    {
      Name (_ADR, 0x0041)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[5] Dimm[0]
    Device (NV10)
    {
      Name (_ADR, 0x0050)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[5] Dimm[1]
    Device (NV11)
    {
      Name (_ADR, 0x0051)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[6] Dimm[0]
    Device (NV12)
    {
      Name (_ADR, 0x0060)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[6] Dimm[1]
    Device (NV13)
    {
      Name (_ADR, 0x0061)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[7] Dimm[0]
    Device (NV14)
    {
      Name (_ADR, 0x0070)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[0] Channel[7] Dimm[1]
    Device (NV15)
    {
      Name (_ADR, 0x0071)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[0] Dimm[0]
    Device (NV16)
    {
      Name (_ADR, 0x1000)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[0] Dimm[1]
    Device (NV17)
    {
      Name (_ADR, 0x1001)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[1] Dimm[0]
    Device (NV18)
    {
      Name (_ADR, 0x1010)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[1] Dimm[1]
    Device (NV19)
    {
      Name (_ADR, 0x1011)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[2] Dimm[0]
    Device (NV20)
    {
      Name (_ADR, 0x1020)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[2] Dimm[1]
    Device (NV21)
    {
      Name (_ADR, 0x1021)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[3] Dimm[0]
    Device (NV22)
    {
      Name (_ADR, 0x1030)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[3] Dimm[1]
    Device (NV23)
    {
      Name (_ADR, 0x1031)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[4] Dimm[0]
    Device (NV24)
    {
      Name (_ADR, 0x1040)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[4] Dimm[1]
    Device (NV25)
    {
      Name (_ADR, 0x1041)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[5] Dimm[0]
    Device (NV26)
    {
      Name (_ADR, 0x1050)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[5] Dimm[1]
    Device (NV27)
    {
      Name (_ADR, 0x1051)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[6] Dimm[0]
    Device (NV28)
    {
      Name (_ADR, 0x1060)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[6] Dimm[1]
    Device (NV29)
    {
      Name (_ADR, 0x1061)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[7] Dimm[0]
    Device (NV30)
    {
      Name (_ADR, 0x1070)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
    
    // Socket[1] Channel[7] Dimm[1]
    Device (NV31)
    {
      Name (_ADR, 0x1071)
      Method (_DSM, 4, Serialized)
      {
        Return (DSMF (Arg0, Arg2, Arg3, _ADR))
      }
    }
  }

  // _DSM common function
  // Arg0: _DSM Arg0, UUID
  // Arg1: _DSM Arg2, Function Index
  // Arg2: _DSM Arg3, Function Arguments
  // Arg3: NFIT Device Handle - [15:12] Socket(1..0), [11:8] Memory Controller(0), [7:4] Channel(7..0), [3:0] DIMM(1..0)
  Method (DSMF, 4, Serialized)
  {
    If (LEqual (Arg0, ToUUID("1EE68B36-D4BD-4a1a-9A16-4F8E53D46E05")))
    {
      Switch (ToInteger(Arg1))        // Arg1: Function Index
      {
        // Query Implemented Functions (Function Index 0)
        Case (0)
        {
          Return (Buffer () {0xff, 0xff, 0xff, 0xff})
        }
        
        // Function does not require input data
        Case (Package () {1, 2, 3, 4, 5, 7, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 24})
        {
          If (LGreater (SizeOf (Index (Arg2, 0)), 0))
          {
            Return (Buffer () {2})  // If Arg2 not empty package, return Invalid Input Parameters
          }
          Store (0, Local0)
        }
        
        // Function requires input data
        Case (Package () {6, 8, 9, 17, 22, 23, 25, 26, 27, 28, 29, 30, 31})
        {
          Store (SizeOf (Index (Arg2, 0)), Local0)
        }
        
        Default
        {
          // If not function 0 - 31, return Not Supported
          Return (Buffer () {1})
        }
      }
      
      Store (ToInteger (Arg1), FIDX)  // Pass Function Index to SMM
      Store (ToInteger (Arg3), NDEV)  // Pass NFIT Device Handle to SMM
      
      // If input data then extract it to DSM_ACPI_SMM_DATA input data area
      If (LGreater(Local0, 0))
      {
        Store (Local0, ISIZ)          // Size of input data
        CreateField (DeRefOf (Index (Arg2, 0)), 0, Multiply (ISIZ, 8), IBUF)
        Mid (IBUF, 0, ISIZ, IDAT)
      }
      
      // Trigger DSM SMI
      Store (0xEB, SMIC)
      
      Name (RBUF, Buffer (OSIZ) {})   // Return buffer
      
      // If output data then extract it from DSM_ACPI_SMM_DATA output data area to return buffer
      If (LGreater(OSIZ, 0))
      {
        CreateField (RBUF, 0, Multiply (OSIZ, 8), OBUF)
        Mid (ODAT, 0, OSIZ, OBUF)
      }
      
      Return (RBUF)
    }
    
    // If not correct UUID, return Invalid Input Parameters
    Return (Buffer () {2})
  }
}

/*
  typedef struct _DSM_ACPI_SMM_DATA {
      UINT32  FunctionIndex;                  // Function Index 0 - 31
      UINT32  InputDataSize;                  // Size of input data
      UINT8   InputData[INPUT_DATA_SIZE];     // Input data (bytes)
      UINT32  OutputDataSize;                 // Size of output data
      UINT8   OutputData[OUTPUT_DATA_SIZE];   // Output data (bytes)
      UINT16  NfitDeviceHandle;               // NFIT Device Handle
      UINT32  NvdimmBitMap;                   // NVDIMM Bitmap
  } DSM_ACPI_SMM_DATA;
*/

  OperationRegion(DASD, SystemMemory, 0x4D44564E, 0x212)   // 0x4D44564E = ('N', 'V', 'D', 'M')
  Field(DASD, ByteAcc, NoLock, Preserve)
  {
    FIDX, 32,     // Function Index 0 - 31
    ISIZ, 32,     // Size of input data
    IDAT, 2048,   // Input data (bits)
    OSIZ, 32,     // Size of output data
    ODAT, 2048,   // Output data (bits)
    NDEV, 16,     // NFIT Device Handle (_ADR)
    NVBM, 32      // NVDIMM Bitmap
  }
