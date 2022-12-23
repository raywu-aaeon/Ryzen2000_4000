//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file TscTimerLib.c
    This file contains TimeLib library instance

**/

#include <Base.h>
#include <Token.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>

#define  PCI_ADDRESS(bus, dev, func, reg) \
            ((UINT64) ( (((UINT8)bus) << 16) + (((UINT8)dev) << 11) + \
            (((UINT8)func) << 8) + ((UINT8)reg) )) & 0x00000000ffffffff

// This is copied from AmdSoc.h
#define AMI_CPUID_STEPPING_MASK      0x0000000F
#define AMI_CPUID_BASE_MODEL_MASK    0x000000F0
#define AMI_CPUID_BASE_FAMILY_MASK   0x00000F00
#define AMI_CPUID_EXT_MODEL_MASK     0x000F0000
#define AMI_CPUID_EXT_FAMILY_MASK    0x0FF00000

#define AMI_RAW_FAMILY_ID_MASK (UINT32) (AMI_CPUID_EXT_FAMILY_MASK | AMI_CPUID_EXT_MODEL_MASK | AMI_CPUID_BASE_FAMILY_MASK)

#define AMI_F15_BR_RAW_ID   0x00660F00

/**
    Stalls the CPU for at least the given number of ticks.

    @param Delay A period of time to delay in ticks.

**/

VOID
InternalX86Delay (
  IN UINT64         Delay
  )
{
  UINT64            Ticks;

  //
  // The target timer count is calculated here
  //
  Ticks = AsmReadTsc() + Delay;

    //
    // Wait until time out
    // Timer wrap-arounds are NOT handled correctly by this function.
    // Thus, this function must be called within 10 years of reset since
    // Intel guarantees a minimum of 10 years before the TSC wraps.
    //
    while (AsmReadTsc() <= Ticks)
        CpuPause();
}

/**
    Read the PCI Register

    @param Address :(UINT32) ( (((UINT32)bus) << 24) + (((UINT32)dev) << 19) \
        + (((UINT32)func) << 16) + ((UINT32)reg) )
    @param ExtAccess : TRUE for extended access, FALSE is for normal access

    @retval UINT32 return value from the PCI Register.

**/
UINT32
TscReadPci32(
    IN UINT32 Address,
    IN BOOLEAN  ExtAccess
)
{
    UINT32  Value32;
    UINT32  AddrCf8 = (1 << 31) + (Address & 0xFFFF00) + (Address & 0xFC);

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        AddrCf8 |= 0x1000000;

    IoWrite32(0xCF8, AddrCf8);
    Value32 = IoRead32(0xCFC);
    return Value32;
}

/**
    Get CPU frequency

    @param VOID

    @retval UINT64 The number of TSC counts per second.

**/

UINT64
InternalGetTscFrequency (
  VOID
  )
{
  UINT64                TscFrequency;
  UINT64                Buffer64;
  UINT64                Temp64;
  UINT32                RegValue;
  UINT32                CpuFid;
  UINT32                CpuDid;
  UINT32                NumBoostStates;
  UINT32                CurrPstate;
  UINT32                RegEax;
  UINTN                 Frequency;
  UINT32                PstateMsr;
  UINT32                Index;

  NumBoostStates = 0;
  PstateMsr = 0xC0010064;

  AsmCpuid(0x80000001, &RegEax, NULL, NULL, NULL);

  if ((RegEax & AMI_RAW_FAMILY_ID_MASK) == AMI_F15_BR_RAW_ID)
  {
      //It's family 15h
      Temp64 = 0x400000000000;

      Buffer64 = AsmReadMsr64(0xC001001F);

      if (!(Buffer64 & Temp64))  // if bit 46 EnableCf8ExtCfg is not then set it for accessing D18F4x15C
      {
          AsmWriteMsr64(0xC001001F, Buffer64 | Temp64);
          Buffer64 &= ~Temp64;
      }
      NumBoostStates = TscReadPci32(PCI_ADDRESS(0, 0x18, 4, 0x15C), TRUE);

      AsmWriteMsr64(0xC001001F, Buffer64); // restore the original value to NB_CFG
      NumBoostStates = (UINT32)((NumBoostStates >> 2) & 0x7);  // Get NumBoostStates

      CurrPstate = (UINT32)(AsmReadMsr64(0xC0010063) & 0x7);
      RegValue = (UINT32)AsmReadMsr64(PstateMsr + NumBoostStates + CurrPstate);

      //Extract the FID and DID.
      //Frequency = ((FID + 10h) * 100) / (2^DID)
      CpuFid = (UINT8)RegValue & 0x3F;
      CpuDid = (UINT8)(RegValue >> 6) & 7;
      CpuDid = (UINT8)(1 << CpuDid); //2^DID
      TscFrequency = (CpuFid + 0x10);
      TscFrequency = DivU64x32(MultU64x64(TscFrequency, 100), CpuDid);
      TscFrequency = MultU64x64(TscFrequency, 1000000);
  }
  else
  {
      //It's family 17h
      // The amount of pstate is 8
      for (Index = 0; Index < 8; Index++)
      {
          Buffer64 = AsmReadMsr64 (PstateMsr + Index);
          if ((Buffer64 & BIT63) == 0)
          {
              continue;
          }
          else
          {
              break;
          }
      }

      if (Index == 8)
      {
          TscFrequency = 0x100; // A fake value
          return TscFrequency;
      }

      // Below code is copied from CcxGetPstateInfo function in AgesaModulePkg\Library\CcxPstatesZenZpLib\CcxPstatesZenZpLib.c
      CpuFid = (UINT32)(Buffer64 & 0x00FF); // Fid is Bit 7:0
      CpuDid = (UINT32)(RShiftU64(Buffer64, 8) & 0x003F) ;

      if (CpuDid == 0)
      {
          Frequency = 0;
      }
      else if ((CpuDid >= 8) && (CpuDid <= 0x3C))
      {
          Frequency = (UINTN) ((200 * CpuFid) / CpuDid);
      }
      else
      {
          Frequency = (UINTN) (25 * CpuFid);
      }
      TscFrequency = MultU64x64(Frequency, 1000000);
  }

  return TscFrequency;
}

/**
    This function delays for the number of micro seconds passed in

    @param MicroSeconds Number of microseconds(us) to delay

    @retval UINTN Value passed in for microseconds delay

**/

UINTN
EFIAPI
MicroSecondDelay (
  IN UINTN          MicroSeconds
  )
{
  InternalX86Delay (
    DivU64x32 (
      MultU64x64 (
        InternalGetTscFrequency (),
        MicroSeconds
        ),
      1000000u
    )
  );
  return MicroSeconds;
}

/**
    This function delays for the number of nano seconds passed in

    @param MicroSeconds Number of nanoseconds(ns) to delay

    @retval UINTN Value passed in for nanoseconds delay

**/

UINTN
EFIAPI
NanoSecondDelay (
  IN UINTN          NanoSeconds
  )
{ 
  InternalX86Delay (
    DivU64x32 (
      MultU64x32 (
        InternalGetTscFrequency (),
        (UINT32)NanoSeconds
      ),
      1000000000u
    )
  );
  return NanoSeconds;  
}

/**
    Retrieves the current value of a 64-bit free running
    performance counter.

    @param VOID

    @retval UINT64 The current value of the free running performance counter.

**/

UINT64
EFIAPI
GetPerformanceCounter (
  VOID
  )
{
  return AsmReadTsc ();
}

/**
    Retrieves the 64-bit frequency in Hz and the range of
    performance counter values.

    @param StartValue The value the performance counter starts with when
        it rolls over.
    @param EndValue The value that the performance counter ends with
        before it rolls over.

    @retval UINT64 The frequency in Hz.

**/

UINT64
EFIAPI
GetPerformanceCounterProperties (
  OUT      UINT64                    *StartValue,  OPTIONAL
  OUT      UINT64                    *EndValue     OPTIONAL
  )
{
    if (StartValue != NULL)
        *StartValue = 0;

    if (EndValue != NULL)
        *EndValue = 0xFFFFFFFFFFFFFFFFull;

    return InternalGetTscFrequency ();
}

/**
    This function converts the elapsed ticks of running performance
    counter to time value in unit of nanoseconds.

    @param Ticks The number of elapsed ticks of running performance
        counter.

    @retval UINT64 The elapsed time in nanoseconds.

**/

UINT64
EFIAPI
GetTimeInNanoSecond (
  IN      UINT64                     Ticks
  )
{
  UINT64  Frequency;
  UINT64  NanoSeconds;
  UINT64  Remainder;
  INTN    Shift;

  Frequency = GetPerformanceCounterProperties (NULL, NULL);

  //
  //          Ticks
  // Time = --------- x 1,000,000,000
  //        Frequency
  //
  NanoSeconds = MultU64x32 (DivU64x64Remainder (Ticks, Frequency, &Remainder), 1000000000u);

  //
  // Ensure (Remainder * 1,000,000,000) will not overflow 64-bit.
  // Since 2^29 < 1,000,000,000 = 0x3B9ACA00 < 2^30, Remainder should < 2^(64-30) = 2^34,
  // i.e. highest bit set in Remainder should <= 33.
  //
  Shift = MAX (0, HighBitSet64 (Remainder) - 33);
  Remainder = RShiftU64 (Remainder, (UINTN) Shift);
  Frequency = RShiftU64 (Frequency, (UINTN) Shift);
  NanoSeconds += DivU64x64Remainder (MultU64x32 (Remainder, 1000000000u), Frequency, NULL);

  return NanoSeconds;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
