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

#include <Uefi.h>
#include <PiPei.h>
#include "Pi/PiHob.h"
#include <AGESA.h>
#include "Library/AmdCalloutLib.h"
#include "Library/IoLib.h"
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include "Token.h"
#include <Library/DebugLib.h>
#include "Ppi/ReadOnlyVariable2.h"
#include "Ppi/Smbus2.h"
#include "OptionMemory.h"
#include "Ppi/AmdMemPpi.h"
//AMI PORTING-- #include "Mem/AmdMemCzPei/AmdMemCzPei.h"
#include "Library/AmdCalloutLib/AgesaReadSpd.h"
#include "PlatformMemoryConfiguration.h"
#include "AmiAgesaPei.h"
#include "Guid/AmiGlobalVariable.h"
#include <OemAgesaElinks.h>
#include "Ppi/AmdMemPpi.h"
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdCapsuleLib.h>
#include "Library/NbPolicy.h"
//
// Identify all static PPI produced by this module
//
PEI_AMD_PLATFORM_DIMM_SPD_PPI  PeiAmdPlatformDimmSpdPpi = {
            //PPI data object;
            NSOCKETS,                          //Total Number Of Socket
            DIMM_SLOTS_PER_SCKT,               //Total Number Of Dimms
            PlatformDimmSpdRead
            };

// [Fam15 only]>
UINTN   GetDayDifference(EFI_TIME EndDate, EFI_TIME StartDate);
BOOLEAN IsMemretrainNeed(IN  CONST  EFI_PEI_SERVICES **PeiServices);
BOOLEAN LeapYear(UINT16 Year);
UINT8   BcdToDec(UINT8 BCD);
// [Fam15 only]<

//
// Define the list of all PPI produced by this module
//
EFI_PEI_PPI_DESCRIPTOR PpiList[] = {
  { (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmdPlatformDimmSpdPpiGuid,
    &PeiAmdPlatformDimmSpdPpi
    }
  };

// [Fam15 only]
EFI_PEI_NOTIFY_DESCRIPTOR MemRestoreSaveNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gAmdMemoryInitCompletePpiGuid,
        MemRestoreSave
    }
};

// ---- PORTING REQUIRED ------
// Below is configuration for CRB 
DIMM_INFO_SMBUS DimmSmbus[] =
{
    DIMM_SPD_MAP
};
// ---- END OF PORTING -----

extern AMI_HOOK_BEFORE_READSPD AMI_HOOK_BEFORE_READ_SPD_LIST EndOfHookList;
AMI_HOOK_BEFORE_READSPD* AmiHookBeforeReadSpdList[] = {AMI_HOOK_BEFORE_READ_SPD_LIST NULL};

// [Fam15 only]
#if BRISTOL_MEMORY_CONFIGURATION_TABLE_CRB == 1
//The below table is copied from ApcbCustomizedDefinitions.h
PSO_ENTRY ROMDATA CrbPlatformMemoryConfigurationForAm4[] = {
        DRAM_TECHNOLOGY(ANY_SOCKET, DDR4_TECHNOLOGY),
        NUMBER_OF_CHANNELS_SUPPORTED (ANY_SOCKET, 2),
        NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, CHANNEL_A, DIMM_SLOTS_PER_CHNL),
        NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, CHANNEL_B, DIMM_SLOTS_PER_CHNL),
        MOTHER_BOARD_LAYERS (LAYERS_6),
        // Signal routing for AMD reference board
        MEMCLK_DIS_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        MEMCLK_DIS_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        CKE_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08),
        CKE_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08),
        ODT_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x04, 0x02, 0x08),
        ODT_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x04, 0x02, 0x08),
        CS_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        CS_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        PSO_END
};
#endif

CHAR16      SpdBypassData[]        = L"SpdBypassData";
CHAR16      SpdBypassSerial[]      = L"SpdBypassSerial";


/**
    This function Get Spd Data from OEM data Source,
    Using hook in SDL file to replace it.

    @param UINT8 **SpdBuffer - SPD Data Buffer Pointer
    @param PeiServices PEI Services table pointer

    @retval UINT8    SpdBuffer

**/
VOID
BeforeMemInitReadSpd(
 IN     EFI_PEI_SERVICES        **PeiServices,
 IN     AGESA_READ_SPD_PARAMS   *SpdData,
 IN OUT UINT8                   **SpdBuffer
)
{
    UINT8   index;
    
    for(index = 0; AmiHookBeforeReadSpdList[index] != NULL; index++)
    {
        AmiHookBeforeReadSpdList[index](PeiServices, SpdData, SpdBuffer);
    }
}

/**
    This function changes the SMBUS page number.
    A dummy write to the slave address of 6E is made to switch the page address to 1, prior to the SPD reading commands.
    Upon completion, another dummy write to the slave address of 6C is made to restore the original page address

    @param PeiServices PEI Services table pointer
    @param Page        Page number for switch
         
    @retval EFI_STATUS return EFI status

**/

VOID
SmbusPageChange (
  IN  CONST EFI_PEI_SERVICES     **PeiServices,
  IN  UINT8                      Page
  )
{
    EFI_STATUS                          Status;
    EFI_PEI_SMBUS2_PPI                  *SmbusPpi = NULL;
    EFI_SMBUS_DEVICE_ADDRESS            SmbusSlaveAddress;
    UINTN                               SmbusLength = 0;
    UINTN                               SmbusOffset = 0;
    UINT8                               Buffer = 0;


    (**PeiServices).LocatePpi(PeiServices, &gEfiPeiSmbus2PpiGuid, 0, NULL, &SmbusPpi);
    //A dummy write to the slave address of 6E is made to switch the page address to 1, prior to the SPD reading commands.
    //Upon completion, another dummy write to the slave address of 6C is made to restore the original page address

    SmbusLength = 1;
    SmbusOffset = 0;
    if (Page == 1)
    {
        SmbusSlaveAddress.SmbusDeviceAddress = (0x6E >> 1);
        Status = SmbusPpi->Execute(SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                EfiSmbusWriteByte, FALSE, &SmbusLength,
                                &Buffer );
        DEBUG((DEBUG_INFO, "\n\n Change SMBUS to page 1 %r\n", Status));
    }
    else
    {
        SmbusSlaveAddress.SmbusDeviceAddress = (0x6C >> 1);
        Status = SmbusPpi->Execute(SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                EfiSmbusWriteByte, FALSE, &SmbusLength,
                                &Buffer );
        DEBUG((DEBUG_INFO, "\n\n Change SMBUS to page 0 %r\n", Status));
    }
    
}


/**
    This function reads whole SPD to provided buffer.

    @param PeiServices PEI Services table pointer
    @param SaveAddr SMBus address of SPD
    @param SpdData Pointer to read SPD parameters structure
         
    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
MemInitReadSpd (
  IN  EFI_PEI_SERVICES   **PeiServices,
  IN  UINT8              SlaveAddr,
  IN OUT  AGESA_READ_SPD_PARAMS *SpdData
  )
{
    EFI_STATUS                          Status;
    EFI_SMBUS_DEVICE_ADDRESS            SmbusSlaveAddress;
    UINTN                               SmbusLength = 0;
    UINTN                               SmbusOffset = 0;
    EFI_PEI_SMBUS2_PPI                  *SmbusPpi = NULL;
    UINTN                               Index = 0;
    UINT8                               *Buffer2 = NULL;
    UINT8                               DimmSelect = 0;             // Dimm Number selection
    SPD_BYPASS_HOB                      *SpdInfoHob = NULL;         // ptr for SpdBypass HOB
    VOID                                *FirstHob = NULL;           // ptr for HOB
    UINT8                               *HobSerial = NULL;
    UINT8                               *HobBuf = NULL;
    UINT8                               NvRamSerial[DIMM_HOB_SERIAL_NO_LENGTH];
    UINT8                               NvRamBuf[DIMM_HOB_DATA_LENGTH];
    UINTN                               VariableSize = 0;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable = NULL;      // ptr for read Variavle PPI
    UINT8                               DramType = 0;   // B is DDR3, C is DDR4

    // Locate Smbus Device
    Status = (**PeiServices).LocatePpi( PeiServices, &gEfiPeiSmbus2PpiGuid, 0, NULL, &SmbusPpi );
    if (EFI_ERROR(Status))  return Status;

    SmbusSlaveAddress.SmbusDeviceAddress = (SlaveAddr >> 1);
    SmbusLength = 1;
    SmbusOffset = 2;    // Key Byte / DRAM Device Type    
    Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                          EfiSmbusReadByte, FALSE, &SmbusLength,
                          &DramType );
    //if SPD data not available at location 2, then we return status
    if (EFI_DEVICE_ERROR == Status)
        return Status;

//#if BY_PASS_SPD_CONTROL
    if (PcdGet8(PcdAgesaByPassSpdControl))
    {
        // Select Dimm Slot
#if (DIMM_SLOTS_PER_CHNL == 1)
        DimmSelect = SpdData->MemChannelId; // One DIMM per channel
#else if (DIMM_SLOTS_PER_CHNL == 2)
        DimmSelect = (SpdData->MemChannelId << 1) + SpdData->DimmId;    // MemChannelID = 0b, DimmId = 0b, 01b, 10b, 11b
#endif

        DEBUG((DEBUG_INFO, "\n SpdData->MemChannelId = %x\n", SpdData->MemChannelId));
        DEBUG((DEBUG_INFO, "\n SpdData->DimmId = %x\n", SpdData->DimmId));

        Status = EFI_SUCCESS;
        Buffer2 = SpdData->Buffer;
        Index = 0;

        // Locate HOB Data
        (*PeiServices)->GetHobList(PeiServices, &FirstHob);
        if (!FirstHob)
        {
            return  EFI_NOT_FOUND;
        }

        // Try to get SpdByPassHob
        SpdInfoHob = GetNextGuidHob(&gAmiAgesaSpdByPassHobGuid, FirstHob);
        if (SpdInfoHob == NULL)
        {
            DEBUG((DEBUG_INFO, " SpdInfoHob should be created once. \n"));
            // Create SPD Data HOB, this should be created once
            (**PeiServices).CreateHob( PeiServices, EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(SPD_BYPASS_HOB), &SpdInfoHob );
            SpdInfoHob->Header.Name = gAmiAgesaSpdByPassHobGuid;
            SpdInfoHob->SPDUpdate = 0;      // Assume we don't need to update SPD data in NVRAM
        }

        HobSerial   = SpdInfoHob->SPD_Serial;
        HobBuf      = SpdInfoHob->SPD_Data;

        // Shifter pointer to DimmSelect position
        HobSerial   = HobSerial + (DIMM_SPD_SERIAL_NO_LENGTH * DimmSelect);
        HobBuf      = HobBuf + (DIMM_SPD_DATA_LENGTH * DimmSelect);

        // Locate NvRam Variable PPI
        Status = (*PeiServices)->LocatePpi( PeiServices,
            &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );

        if ( Status != EFI_SUCCESS )
            return EFI_DEVICE_ERROR;

        // Read Dimm Serial Number in NvRam
        VariableSize = DIMM_HOB_SERIAL_NO_LENGTH;
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                    L"SpdBypassSerial", &gAmiGlobalVariableGuid, NULL,
                    &VariableSize, &NvRamSerial );

        if ( Status != EFI_SUCCESS )
        {
            SetMem( NvRamSerial, DIMM_HOB_SERIAL_NO_LENGTH, 0);
        }

        // Read Dimm Data in NvRam
        VariableSize = DIMM_HOB_DATA_LENGTH;
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                    L"SpdBypassData", &gAmiGlobalVariableGuid, NULL,
                    &VariableSize, &NvRamBuf );

        if ( Status != EFI_SUCCESS )
        {
            SetMem( NvRamBuf, DIMM_HOB_DATA_LENGTH, 0);
        }

        Status = EFI_SUCCESS;
        // read Serial Number from Device
        SmbusLength = 1;
        Buffer2 = SpdData->Buffer;

        DEBUG((DEBUG_INFO, "\n Serial number = \n"));

        //Change to page 1
        SmbusPageChange(PeiServices, 1);

        SmbusOffset = DIMM_SPD_SERIAL_NO_OFFSET_DDR4;
        for ( Index = 0; Index < DIMM_SPD_SERIAL_NO_LENGTH; Index++ )
        {
            Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                  EfiSmbusReadByte, FALSE, &SmbusLength,
                                  Buffer2 );
            DEBUG((DEBUG_INFO, " %x ", *Buffer2));
            //Copy Serial Number to HOB
            HobSerial[Index] = *Buffer2;
            SmbusOffset += 1;
            Buffer2++;
        }
            
        //Change to Page 0
        SmbusPageChange(PeiServices, 0);

    
        // Compare Serial Number
        Buffer2 = SpdData->Buffer;
        for ( Index = 0; Index < DIMM_SPD_SERIAL_NO_LENGTH; Index++ )
        {
            // Compare each byte if any different then break out loop
            if ( Buffer2[Index] != NvRamSerial[DIMM_SPD_SERIAL_NO_LENGTH * DimmSelect + Index] )
                break;
        }

        // if SN( Nvram == Spd )
        if ( Index == DIMM_SPD_SERIAL_NO_LENGTH )
        {
            DEBUG((DEBUG_INFO, " Serial Number is the same between Nvram and SPD  \n"));
            for ( Index = 0; Index < DIMM_SPD_DATA_LENGTH; Index++ )
                Buffer2[Index] = NvRamBuf[DIMM_SPD_DATA_LENGTH * DimmSelect + Index];
        }
        // if SN( Nvram != Spd )
        else
        {
            // Read whole Spd Data from Device
            Status = EFI_SUCCESS;
            SmbusLength = 1;
            SmbusOffset = 0;
            Buffer2 = SpdData->Buffer;

            //It's DDR4
            //The 256 bytes in Page 0
            for ( Index = 0; Index < DIMM_SPD_DATA_256; Index++ )
            {
                Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                      EfiSmbusReadByte, FALSE, &SmbusLength,
                                      Buffer2 );
                SmbusOffset += 1;
                Buffer2++;
            }

            //Change to page 1
            SmbusPageChange(PeiServices, 1);
            //The 256 bytes in Page 1
            for ( Index = 0; Index < DIMM_SPD_DATA_256; Index++ )
            {
                Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                      EfiSmbusReadByte, FALSE, &SmbusLength,
                                      Buffer2 );
                SmbusOffset += 1;
                Buffer2++;
            }

            //Change to Page 0
            SmbusPageChange(PeiServices, 0);

            // if it goes here, then we need to set variable for comparison at next time
            SpdInfoHob->SPDUpdate = 1;
        }

        // copy Spd Data to Hob
        Buffer2 = SpdData->Buffer;
        CopyMem( HobBuf, Buffer2, DIMM_SPD_DATA_LENGTH );
    }
    else    //if (PcdGet8(PcdAgesaByPassSpdControl))
    {
        Status = EFI_SUCCESS;
        SmbusLength = 1;
        SmbusOffset = 0;
        Buffer2 = SpdData->Buffer;

        //It's DDR4
        //The 256 bytes in Page 0
        for ( Index = 0; Index < DIMM_SPD_DATA_256; Index++ )
        {
            Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                  EfiSmbusReadByte, FALSE, &SmbusLength,
                                  Buffer2 );
            SmbusOffset += 1;
            Buffer2++;
        }

        //Change to page 1
        SmbusPageChange(PeiServices, 1);
        //The 256 bytes in Page 1
        for ( Index = 0; Index < DIMM_SPD_DATA_256; Index++ )
        {
            Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                                  EfiSmbusReadByte, FALSE, &SmbusLength,
                                  Buffer2 );
            SmbusOffset += 1;
            Buffer2++;
        }

        //Change to Page 0
        SmbusPageChange(PeiServices, 0);

    }

    return Status;
}

/**
    This function reads specific SPD to provided buffer.

           
    @param PeiServices PEI Services table pointer
    @param SpdData Pointer to read SPD parameters
           structure

    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
MemInitMemoryDownReadSpd (
 IN     EFI_PEI_SERVICES        **PeiServices,
 IN OUT AGESA_READ_SPD_PARAMS   *SpdData
)
{
    UINT8                           *SpdBuffer = NULL;

    // Read Spd data provided in BIOS
    BeforeMemInitReadSpd(PeiServices, SpdData, &SpdBuffer);

    if (SpdBuffer != NULL)
    {
        CopyMem(SpdData->Buffer, SpdBuffer, DIMM_SPD_DATA_LENGTH);

        return EFI_SUCCESS;
    }
    return EFI_DEVICE_ERROR;
}


/**
    This function reads provides SPD data if DIMM present.

           
    @param PeiServices PEI Services table pointer
    @param This Pointer to 
    @param SpdData Pointer to read SPD parameters
        structure

         
    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
EFIAPI
PlatformDimmSpdRead (
  IN      EFI_PEI_SERVICES      **PeiServices,
  IN      PEI_AMD_PLATFORM_DIMM_SPD_PPI      *This,
  IN OUT  AGESA_READ_SPD_PARAMS *SpdData
  )
{
    UINTN       Index;
    UINT8       SmbusAddress;
    EFI_STATUS  Status;

    IoWrite8(0x80, 0x2B);       // PEI_PROGRESS_CODE(PeiServices, PEI_MEMORY_SPD_READ);

    SmbusAddress = 0;
    Status = EFI_INVALID_PARAMETER;

    for (Index = 0; Index < DIMM_SLOTS_PER_SCKT; Index++)
    {
        if ((SpdData->MemChannelId == DimmSmbus[Index].ChannelId)
           && (SpdData->DimmId == DimmSmbus[Index].DimmId))
        {
            SmbusAddress = DimmSmbus[Index].SmbusAddress;
            Status = EFI_SUCCESS;
            break;
        }
    }

    if (SpdData->SocketId > (NSOCKETS - 1)) return Status;

    if (Status == EFI_INVALID_PARAMETER)
    {
        return Status;
    }  

    if (PcdGet8(PcdAgesaMemoryDownSupport))
    {
        Status = MemInitMemoryDownReadSpd(PeiServices, SpdData);
    }
    else
    {
        Status = MemInitReadSpd(PeiServices, SmbusAddress, SpdData);
    }

    DEBUG((DEBUG_INFO, "\n --Sckt-Ch-Dimm=[%x-%x-%x]--Dimm Addr %X  ---SPD Read Sts %x \n", \
                SpdData->SocketId,SpdData->MemChannelId,SpdData->DimmId,SmbusAddress, Status));
    return Status;
}

/**
    This function reads the serial number of SPD

    @param PeiServices PEI Services table pointer
    @param UINT8       SMBUS slave address to read
    @param Buffer      the data buffer to be sent out
    @param BufferIndex the buffer index

    @retval EFI_STATUS Status of result

**/
EFI_STATUS ReadSaveDimmSerial(
 IN   CONST EFI_PEI_SERVICES    **PeiServices,
 UINT8                          SlaveAddr,
 UINT8                          *Buffer,
 UINT8                          BufferIndex)
{

    UINT8                       Buffer2, Index;
    EFI_STATUS                  Status;
    EFI_SMBUS_DEVICE_ADDRESS    SmbusSlaveAddress;
    EFI_PEI_SMBUS2_PPI          *SmbusPpi = NULL;
    UINTN                       SmbusLength = 0;
    UINTN                       SmbusOffset = 0;
    UINT8                       DramType = 0;

    //Check if device Present by reading offset 2
    //if not present return
    //if device present, read the device serial
    //Update Buffer 
    //Returns error if cannot locate smbus ppi
    SmbusLength = 1;
    SmbusOffset = 2;    // Key Byte / DRAM Device Type

    DEBUG((DEBUG_INFO, "\n ReadSaveDimmSerial entry \n"));

    Status = (**PeiServices).LocatePpi( PeiServices,
                                        &gEfiPeiSmbus2PpiGuid,
                                        0, NULL, &SmbusPpi );

    if (EFI_ERROR(Status))  return  EFI_NOT_FOUND;

    DEBUG((DEBUG_INFO, "\n SlaveAddr = %x \n", SlaveAddr));
    DEBUG((DEBUG_INFO, "\n BufferIndex = %x \n", BufferIndex));

    SmbusSlaveAddress.SmbusDeviceAddress = (SlaveAddr >> 1);

    Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                          EfiSmbusReadByte, FALSE, &SmbusLength,
                          &DramType );
    //if SPD data is not available at offset 2, then we return status
    if (EFI_DEVICE_ERROR == Status)
        return Status;

    Status = EFI_SUCCESS;
    SmbusSlaveAddress.SmbusDeviceAddress = (SlaveAddr >> 1);
    SmbusLength = 1;

    //It's DDR4
    DEBUG((DEBUG_INFO, "\n DDR4 Serial number = \n"));

    //Change to page 1
    SmbusPageChange(PeiServices, 1);

    SmbusOffset = DIMM_SPD_SERIAL_NO_OFFSET_DDR4;
    for ( Index = 0; Index < DIMM_SPD_SERIAL_NO_LENGTH; Index++ )
    {
        Status = SmbusPpi->Execute( SmbusPpi, SmbusSlaveAddress, SmbusOffset,
                              EfiSmbusReadByte, FALSE, &SmbusLength,
                              &Buffer2 );
	    if(EFI_ERROR(Status))
		    DEBUG((DEBUG_ERROR, "Execute SmbusPpi %r", Status));
        DEBUG((DEBUG_INFO, " %x ", Buffer2));
        SmbusOffset += 1;
        Buffer[BufferIndex * DIMM_SPD_SERIAL_NO_LENGTH + Index] = Buffer2;
    }
        
    //Change to Page 0
    SmbusPageChange(PeiServices, 0);



    return EFI_SUCCESS;
}

// [Fam15 only]
/**
    This function checks if memory configuration match

    @param PeiServices PEI Services table pointer

    @retval BOOLEAN result of checking

**/
BOOLEAN CheckIfConfigChange(
 IN CONST   EFI_PEI_SERVICES **PeiServices,
 UINT8 *Buffer)
{
    UINT8                           NvRamSerial[MEMRESTORE_SERIAL_HOB_LENGTH], Index;
    UINTN                           VariableSize = 0;
    BOOLEAN                         RetStatus = TRUE;
    MEMRESTORE_SERIAL_HOB           *MemRestoreSerialHob = NULL;
    VOID                            *FirstHob = NULL;           // ptr for HOB
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;      // ptr for read Variavle PPI
    EFI_STATUS  Status;

    // Read NVRAM Serial HOBA Value
    // Read Dimm Serial Number in NvRam
    // Locate NvRam Variable PPI
    Status = (*PeiServices)->LocatePpi( PeiServices,
        &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );

    if ( Status != EFI_SUCCESS )
        return TRUE;

    VariableSize = MEMRESTORE_SERIAL_HOB_LENGTH;
    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                L"MemRestoreSerialLength", &gAmiGlobalVariableGuid, NULL,
                &VariableSize, &NvRamSerial );

    if ( Status != EFI_SUCCESS )
    {
        SetMem( NvRamSerial, MEMRESTORE_SERIAL_HOB_LENGTH, 0);
        RetStatus = TRUE;
    }
    else
    {
        for ( Index = 0; Index < MEMRESTORE_SERIAL_HOB_LENGTH; Index++ )
        {
            // Compare each byte if any different then break out loop
            if ( Buffer[Index] != NvRamSerial[Index] )
                break;
        }

        if (Index == MEMRESTORE_SERIAL_HOB_LENGTH )
            RetStatus = FALSE;  //No need for Hob or update NVRAM
     
    }

    if(RetStatus)
    {
        (**PeiServices).CreateHob( PeiServices, EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(MEMRESTORE_SERIAL_HOB), &MemRestoreSerialHob );
        MemRestoreSerialHob->Header.Name = gAmiAgesaMemRestoreSerialHobGuid;
        MemRestoreSerialHob->SPDUpdate = 1;      // Assume we need to update SPD data in NVRAM
        //Update HOB
        for ( Index = 0; Index < MEMRESTORE_SERIAL_HOB_LENGTH; Index++ )
        {
            MemRestoreSerialHob->SPD_Serial[Index] = Buffer[Index];
        }            
    }

    return RetStatus;
}

// [Fam15 only]
/**
    This function checks if memory configuration match

    @param PeiServices PEI Services table pointer

    @retval BOOLEAN result of checking

**/
BOOLEAN IsMemConfigMatch(
 IN  CONST EFI_PEI_SERVICES **PeiServices)
{

    UINT8 CurrentSocket, CurrentChannel, CurrentDimm, SmbusAddress, Index, BufferIndex;
    UINT8 MaxSocket = NSOCKETS, MaxChannelPerSocket = CHNLS_PER_NODE, MaxDimmPerChannel = DIMM_SLOTS_PER_CHNL;
    UINT8 Buffer[MEMRESTORE_SERIAL_HOB_LENGTH];
    EFI_STATUS Status;
    SmbusAddress = 0;
    BufferIndex = 0;
    SetMem( Buffer, MEMRESTORE_SERIAL_HOB_LENGTH, 0);

    for(CurrentSocket = 0; CurrentSocket < MaxSocket; CurrentSocket++)
    {  
        for(CurrentChannel = 0; CurrentChannel < MaxChannelPerSocket; CurrentChannel++)
        {
            for(CurrentDimm = 0; CurrentDimm < MaxDimmPerChannel; CurrentDimm++)
            {
                for(Index = 0; Index < sizeof(DimmSmbus)/sizeof(DIMM_INFO_SMBUS); Index++)
                {
                    if((CurrentChannel == DimmSmbus[Index].ChannelId) && (CurrentDimm == DimmSmbus[Index].DimmId))
                    {          
                        SmbusAddress = DimmSmbus[Index].SmbusAddress;
                        Status = ReadSaveDimmSerial(PeiServices, SmbusAddress, Buffer, BufferIndex);
                        BufferIndex++;
                        if(Status == EFI_NOT_FOUND)
                            return FALSE;
                        break;

                    }
                }
            }
        }
    }


    if (!CheckIfConfigChange(PeiServices, Buffer))   //Read From NVRAM compare to the Buffer...Note the HOB needs to be saved in DXE inside NVRAM
        return TRUE;
    else
        return FALSE;
}

/**
    This function checks if the CPU match

    @param PeiServices PEI Services table pointer

    @retval BOOLEAN result of checking

**/
BOOLEAN IsCpuCfgMatch(
 IN  CONST   EFI_PEI_SERVICES **PeiServices)
{

    UINT32                      CpuId = 0;
    UINT32                      RegEax = 0;
    UINT32                      RegEbx = 0;
    UINT32                      RegEcx = 0;
    UINT32                      RegEdx = 0;
    UINTN                       VariableSize = sizeof(UINT32);
    EFI_STATUS                  Status;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable = NULL;      // ptr for read Variavle PPI

    Status = (*PeiServices)->LocatePpi( PeiServices,
        &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );

    if ( Status != EFI_SUCCESS )
        return FALSE;

    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                L"MemRestoreCpuId", &gAmiGlobalVariableGuid, NULL,
                &VariableSize, &CpuId );

    if ( Status != EFI_SUCCESS )
    {
       return FALSE;
    }

    AsmCpuid(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    if (RegEax == CpuId)
        return TRUE;
    
    return FALSE;

}

// [Fam15 only]
/**
    This function checks if the AGESA Module version match

    @param PeiServices PEI Services table pointer

    @retval BOOLEAN result of checking

**/
BOOLEAN
IsVersionMatch(
 IN  CONST   EFI_PEI_SERVICES    **PeiServices)
{
    UINTN                               VariableSize = sizeof(UINT32);
    EFI_STATUS                          Status;
    UINT32                              VersionCheck = 0;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable = NULL;      // ptr for read Variavle PPI

    Status = (*PeiServices)->LocatePpi( PeiServices,
                &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );

    if ( Status != EFI_SUCCESS )
        return FALSE;

    Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable,
                                    L"ModuleVersion",
                                    &gAmiGlobalVariableGuid,
                                    NULL,
                                    &VariableSize,
                                    &VersionCheck
                                );

    DEBUG((DEBUG_INFO, "\n\n***MemSpd GetVariable Status = %r, ModuleVersion = %x\n", Status, VersionCheck));

    if (Status)
        // if error occurs, then it should go normal memory training path.
        return FALSE;
    else
    {
        // In case customer wants to update BIOS without clearing NVRAM, we need to
        // check if the version updated is the same as the one in NVRAM.
        if (VersionCheck == AGESA_MODULE_REVISION)
            return TRUE;
        else
            return FALSE;
    }

}

// [Fam15 only]
/**
    Check if the memory restore funciton is feasible

        
    @param PeiServices PEI Services table pointer
    @param This Pointer to PPI structure
    @param MemData Pointer to memory data structure

    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
EFIAPI
MemRestoreInit (
  IN  CONST EFI_PEI_SERVICES    **PeiServices  ///< Pointer to PeiServices
)
{
    EFI_STATUS                          Status = EFI_SUCCESS;
    MEM_RESTORE_HOB                     *MemRestoreHob;
    UINTN                               DataSize = 0;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    EFI_BOOT_MODE                       BootMode;
    UINT8                               Value8;
    BOOLEAN                             IsMemCfgGood = FALSE;
    BOOLEAN                             IsMemCfgMatch = TRUE;
    BOOLEAN                             IsCpuMatch = TRUE;
    BOOLEAN                             IsVerMatch = TRUE;
    VOID                                *NvStorage = NULL;

	DEBUG((DEBUG_INFO, "***** MemRestoreInit Entry \n"));

    Status = (*PeiServices)->LocatePpi(PeiServices,
            &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable);
    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "\n\n***LocatePpi gEfiPeiReadOnlyVariable2PpiGuid status : %r\n", Status));
        return  Status;
    }

    Status = (*PeiServices)->CreateHob (
                PeiServices,
                EFI_HOB_TYPE_GUID_EXTENSION,
                sizeof(MEM_RESTORE_HOB),
                &MemRestoreHob
            );
    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "\n\n***MemRestoreInit CreateHob : %r\n", Status));
        return  Status;
    }
    MemRestoreHob->Header.Name = gAmiAgesaMemRestoreGuid;
    MemRestoreHob->Count = 1;
    MemRestoreHob->Checksum = 0;
    MemRestoreHob->First = FALSE;

    //check if its memsafebit set.
    IoWrite8(0x72, PcdGet8(PcdCmosAgesaSpecified));
    IoRead8(0x61);
    Value8 = IoRead8(0x73); // Read from CMOS
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "\n\n***GetBootMode Status : %r\n", Status));
        return  Status;
    }

    //Two succesfull conditions. 
    //1. Warmboot with memconfig safe
    if ((Value8 & (BIT1 | BIT0)) == 3)
    {
        IsMemCfgGood = TRUE;
        DEBUG((DEBUG_INFO, "\n ***IsMemCfgGood (Value8 is 3) = TRUE\n"));
    }
    else
    {
        //PEI_PERF_START (PeiServices, L"ConfigCheck", NULL, 0);
        IsMemCfgMatch = IsMemConfigMatch(PeiServices);
        IsCpuMatch = IsCpuCfgMatch(PeiServices);
        IsVerMatch = IsVersionMatch(PeiServices);

        DEBUG((DEBUG_INFO, "\n ***IsMemCfgMatch = %x\n", IsMemCfgMatch));
        DEBUG((DEBUG_INFO, "\n ***IsCpuMatch = %x\n", IsCpuMatch));
        DEBUG((DEBUG_INFO, "\n ***IsVerMatch = %x\n", IsVerMatch));

        //PEI_PERF_END (PeiServices, L"ConfigCheck", NULL, 0);
        if ((Value8 & BIT1) && IsMemCfgMatch && IsCpuMatch && IsVerMatch) {
            IsMemCfgGood = TRUE;
        }
    }

//Reset bit, till Ready to BOOT
    Value8 &= ~BIT1;
//    PEI_PERF_START (PeiServices,L"DateCheck", NULL, 0);

    if (IsMemretrainNeed(PeiServices)) {
        IsMemCfgGood = FALSE;
        Value8 |= BIT2;
    }
    else
        Value8 &= ~BIT2;
//    PEI_PERF_END (PeiServices,L"DateCheck", NULL, 0);

    IoWrite8(0x73, Value8);

    if (AmdCapsuleGetStatus())
    {
        // if it is capsule situation, then memory must be good to do memory restore
        IsMemCfgGood = TRUE;
    }

    if (IsMemCfgGood) {// both bit 0 and 1 is set
        DEBUG((DEBUG_INFO, "\n\n***MemRestoreCtl = TRUE\n"));
        PcdSetBoolS(PcdAmdMemCfgMemRestoreCtl, TRUE);
        PcdSetBoolS(PcdAmdMemCfgSaveMemContextCtl, FALSE);
        //((MEM_PARAMETER_STRUCT*)MemData)->MemRestoreCtl = TRUE;
        //((MEM_PARAMETER_STRUCT*)MemData)->SaveMemContextCtl = FALSE;
        MemRestoreHob->SaveMemContext = FALSE;
    } else {
        PcdSetBoolS(PcdAmdMemCfgMemRestoreCtl, FALSE);
        PcdSetBoolS(PcdAmdMemCfgSaveMemContextCtl, TRUE);
        //((MEM_PARAMETER_STRUCT*)MemData)->MemRestoreCtl = FALSE;
        //((MEM_PARAMETER_STRUCT*)MemData)->SaveMemContextCtl = TRUE;
        MemRestoreHob->SaveMemContext = TRUE;
    }

    if (IsMemCfgGood)
    {
        MemRestoreHob->First = FALSE;

        //Get NvStorageSize which is saved on last boot
        DataSize = 0;
        Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, 
                                                    L"MemoryS3SaveNv",
                                                    &gAmiAgesaS3NonvolatileDataGuid, 
                                                    NULL,
                                                    &DataSize, 
                                                    NvStorage
                                                );
        DEBUG((DEBUG_INFO, "*** GetVariable(MemoryS3SaveNv)= %r: size = %x\n", Status, DataSize));
        if (DataSize)
        {
            //Restore NvStorage
            //((MEM_PARAMETER_STRUCT*)MemData)->MemContext.NvStorageSize = DataSize;
            PcdSet32S(PcdAmdMemCfgNvStorageSize, DataSize);
            (*PeiServices)->AllocatePool(PeiServices,
                                DataSize,
                                &NvStorage
                            );
            Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, 
                                            L"MemoryS3SaveNv",
                                            &gAmiAgesaS3NonvolatileDataGuid, 
                                            NULL,
                                            &DataSize, 
                                            NvStorage
                                        );
            DEBUG((DEBUG_INFO, " GetVariable(MemoryS3SaveNv) NvStorage:%lx = %r\n", NvStorage, Status));
            if (Status == EFI_SUCCESS)
            {
                PcdSet32S(PcdAmdMemCfgNvStorage, (UINT32)NvStorage);
            }
        }
    }

    return Status;
}

// [Fam15 only]
/**
    This function saves the data for the memory restore next time

    @param PeiServices PEI Services table pointer
    @param This Pointer to PPI structure
    @param MemData Pointer to memory data structure

    @retval EFI_STATUS return EFI status

**/
EFI_STATUS
EFIAPI
MemRestoreSave (
  IN  CONST EFI_PEI_SERVICES        **PeiServices,  ///< Pointer to PeiServices
  IN  EFI_PEI_NOTIFY_DESCRIPTOR     *NotifyDesc,
  IN  VOID                          *InvokePpi
)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    VOID                *FirstHob;
    MEM_RESTORE_HOB     *MemRestoreHob;

    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    if (FirstHob != NULL)
    {
        MemRestoreHob = GetNextGuidHob(&gAmiAgesaMemRestoreGuid, FirstHob);
        if (MemRestoreHob != NULL)
        {
            if (PcdGetBool(PcdAmdMemCfgSaveMemContextCtl))
            {
                DEBUG((DEBUG_INFO, "\n\n***MemRestoreSave: SaveMemContextCtl = TRUE\n\n"));

                MemRestoreHob->MemContext.Signature = PcdGet32(PcdAmdMemCfgSignature);
                MemRestoreHob->MemContext.Version = PcdGet16(PcdAmdMemCfgVersion);
                MemRestoreHob->MemContext.Flags = PcdGet32(PcdAmdMemCfgFlags);
                MemRestoreHob->MemContext.NvStorageSize = PcdGet32(PcdAmdMemCfgNvStorageSize);
                MemRestoreHob->MemContext.VolatileStorageSize = PcdGet32(PcdAmdMemCfgVolatileStorageSize);

                DEBUG((DEBUG_INFO, "***MemRestoreSave: Signature = %x \n", MemRestoreHob->MemContext.Signature));
                DEBUG((DEBUG_INFO, "***MemRestoreSave: Version = %x \n", MemRestoreHob->MemContext.Version));
                DEBUG((DEBUG_INFO, "***MemRestoreSave: Flags = %x \n", MemRestoreHob->MemContext.Flags));
                DEBUG((DEBUG_INFO, "***MemRestoreSave: NvStorageSize = %x \n", MemRestoreHob->MemContext.NvStorageSize));
                DEBUG((DEBUG_INFO, "***MemRestoreSave: VolatileStorageSize = %x \n", MemRestoreHob->MemContext.VolatileStorageSize));

            }
            else
            {
                DEBUG((DEBUG_INFO, "\n\n***MemRestoreSave: SaveMemContextCtl = FALSE\n\n"));
            }
        }
    }

    return Status;
}

// [Fam15 only]
/**
    This function checks if memory training is needed.

    @param EFI_PEI_SERVICES Pei services pointer
           
    @retval UINTN result TRUE = Do memory training, FALSE = Do Not

**/
BOOLEAN IsMemretrainNeed(
 IN  CONST  EFI_PEI_SERVICES **PeiServices)
{
//Read Date stored in NVRAM
    EFI_TIME PastDate, CurrDate;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable = NULL;      // ptr for read Variavle PPI
    UINTN DateSize = sizeof(EFI_TIME);
    EFI_STATUS Status;
    UINT8 Value8;
    UINTN DaysPassed = 0;

    // Locate NvRam Variable PPI
    Status = (*PeiServices)->LocatePpi( PeiServices,
        &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );

    if ( Status != EFI_SUCCESS )
        return TRUE;

    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                L"MemRestoreTime", &gAmiGlobalVariableGuid, NULL,
                &DateSize, &PastDate );

    if ( Status != EFI_SUCCESS)
        return TRUE;

 //If RTC Year only 1 digit, EFI spec says years range is 1998 - 2097
    IoWrite8(0x70, 0x32);
    IoRead8(0x61);
    Value8 = IoRead8(0x71);
    Value8 = BcdToDec(Value8);
    CurrDate.Year = (UINT16)Value8;

    IoWrite8(0x70, 9);
    IoRead8(0x61);
    Value8 = IoRead8(0x71);
    CurrDate.Year = (UINT16)(CurrDate.Year * 100 + BcdToDec(Value8));

    IoWrite8(0x70, 8);
    IoRead8(0x61);
    Value8 = IoRead8(0x71);
    Value8 = BcdToDec(Value8);
    CurrDate.Month = Value8;

    IoWrite8(0x70, 7);
    IoRead8(0x61);
    Value8 = IoRead8(0x71);
    Value8 = BcdToDec(Value8);
    CurrDate.Day = Value8;

    CurrDate.Hour      = 0;
    CurrDate.Minute    = 0;
    CurrDate.Second    = 0;
    CurrDate.Nanosecond = 0;

//Read Current Date
    DaysPassed = GetDayDifference(CurrDate, PastDate);

    if(DaysPassed > 29)     //If 30 days passed do training
        return TRUE;
    
    return FALSE;
}

// [Fam15 only]
/**
    This function checks the day difference

    @param EFI_TIME EndDate   value to be checked
    @param EFI_TIME StartDate start date for checking
           
    @retval UINTN result Total days

**/
UINTN   GetDayDifference(EFI_TIME EndDate, EFI_TIME StartDate)
{
    UINTN TotalDays=0, TotalDaysStartYear = 0, TotalDaysEndYear = 0;
    UINT16 Month, Year;
    UINT8 NumDays [13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//check valid parameters
//Return 30 to do memory training
    if(StartDate.Year > EndDate.Year)
        return 30;
    else if(StartDate.Year == EndDate.Year && StartDate.Month > EndDate.Month)
        return 30;
    else if(StartDate.Year == EndDate.Year && StartDate.Month == EndDate.Month && StartDate.Day > EndDate.Day)
        return 30;   

    for (Year = (StartDate.Year + 1); Year < EndDate.Year; Year++) //processes complete Years
    {
        if (LeapYear(Year) == TRUE)
            TotalDays += 366;
        else 
            TotalDays += 365;
     }

    Year = StartDate.Year;
    if (LeapYear(Year) == TRUE)
        NumDays[2] = 29;

    for(Month = StartDate.Month + 1; Month <= 12; Month++) //processes incomplete Year 1
    {
        TotalDaysStartYear += NumDays[Month];
    }

    Month = StartDate.Month;

    TotalDaysStartYear = TotalDaysStartYear + NumDays[StartDate.Month] - StartDate.Day + 1;
 


    Year = EndDate.Year;
    if (LeapYear(Year) == FALSE)
        NumDays[2] = 28;
    else
        NumDays[2] = 29;

    for(Month = EndDate.Month - 1; Month >= 1; Month--) //processes incomplete Year 2
    {
        TotalDaysEndYear += NumDays[Month];
    }

    
    TotalDaysEndYear +=  EndDate.Day; //no need for LeapYear function here- don't need to know Month max

    if (StartDate.Year == EndDate.Year)
    {
        TotalDays = TotalDaysEndYear + TotalDaysStartYear;

        if(LeapYear(StartDate.Year))
            TotalDays = TotalDays - 366;
        else
            TotalDays = TotalDays - 365;

    }
    else
        TotalDays += TotalDaysEndYear + TotalDaysStartYear;

    if (TotalDays <= 0)
        return 30;

    return TotalDays;
}

// [Fam15 only]
/**
    This function checks if this year is leap year or not

        
    @param value to be checked

           
    @retval BOOLEAN result TRUE = leap year, FALSE = Not leap year

**/
BOOLEAN LeapYear (UINT16 Year)
{
    BOOLEAN Leap = FALSE;
   if ((Year % 4 == 0) && !(Year % 100 == 0)|| (Year % 400 == 0))
        Leap = TRUE;
    return Leap;
}

// [Fam15 only]
/**
    This function converts data from BCD to DEC format

        
    @param value to be converted

           
    @retval UINT8 result of conversion

**/

UINT8 BcdToDec(UINT8 BCD)
{
    UINT8 FirstDigit = BCD & 0xf;
    UINT8 SecondDigit = BCD >> 4;;

    return SecondDigit * 10  + FirstDigit;
}

/**
 *  AmiAgesaPeiEntry
 *
 *  Description:
 *    This function will prepare the platform configuarion for AGESA use.
 *
 *  Parameters:
 *    @param[in]        **PeiServices
 *                      FileHandle
 *
 *
 *    @retval         VOID
 *
 **/
EFI_STATUS
EFIAPI
AmiAgesaPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS                                  Status = EFI_SUCCESS;
#if BRISTOL_MEMORY_CONFIGURATION_TABLE_CRB == 1
    EFI_PEI_PPI_DESCRIPTOR                      *MemoryConfigurationPtr; //[Fam15 only]
    AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI    *AmdAgesaMemPlatformConfigurationPpiPtr; //[Fam15 only]
#endif
    SOC_ID_STRUCT                               SocId;
    UINTN                                       VariableSize = sizeof(UINT64);
    EFI_PEI_READ_ONLY_VARIABLE2_PPI             *ReadOnlyVariable = NULL;      // Ptr for read Variavle PPI
    UINT64                                      MemCeilVar = 0;
    NB_SETUP_DATA                               NbSetupData;
    UINT32                                      MemoryFreqArray[] = {DDR1333_FREQUENCY, DDR1600_FREQUENCY,
                                                                     DDR1866_FREQUENCY, DDR2133_FREQUENCY,
                                                                     DDR2400_FREQUENCY};

    DEBUG ((DEBUG_INFO, "    AmiAgesaPeiEntry Entry\n"));

    Status = (*PeiServices)->InstallPpi(PeiServices, &PpiList[0]);
    if (EFI_SUCCESS != Status) {
        DEBUG ((DEBUG_ERROR, "gAmdPlatformDimmSpdPpiGuid installation failed  \n"));
        return Status;
    }
    
    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;
    
    if (SocHardwareIdentificationCheck (&SocId))
    {
        // Locate NvRam Variable PPI
        Status = (*PeiServices)->LocatePpi( PeiServices,
            &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
        if (EFI_SUCCESS != Status) {
            DEBUG ((DEBUG_ERROR, "Unable to locate ReadOnlyVariable  \n"));
            return Status;
        }

#if BRISTOL_MEMORY_CONFIGURATION_TABLE_CRB == 1
        Status = (*PeiServices)->AllocatePool (
                               PeiServices,
                               sizeof (EFI_PEI_PPI_DESCRIPTOR),
                               &MemoryConfigurationPtr
                               );
        if (EFI_SUCCESS != Status) {
            DEBUG ((DEBUG_ERROR, "Unable to allocate space for MemoryConfigurationPtr data \n"));
            return Status;
        }

        Status = (*PeiServices)->AllocatePool (
                               PeiServices,
                               sizeof (AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI),
                               &AmdAgesaMemPlatformConfigurationPpiPtr
                               );
        if (EFI_SUCCESS != Status) {
            DEBUG ((DEBUG_ERROR, "Unable to allocate space for AmdAgesaMemPlatformConfigurationPpiPtr data \n"));
            return Status;
        }

        AmdAgesaMemPlatformConfigurationPpiPtr->PlatformMemoryConfiguration = CrbPlatformMemoryConfigurationForAm4;

        MemoryConfigurationPtr->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
        MemoryConfigurationPtr->Guid = &gAmdMemoryPlatformConfigurationPpiGuid;
        MemoryConfigurationPtr->Ppi = AmdAgesaMemPlatformConfigurationPpiPtr;

        Status = (**PeiServices).InstallPpi (PeiServices, MemoryConfigurationPtr);
        if (EFI_SUCCESS != Status) {
            DEBUG ((DEBUG_ERROR, "MemoryConfigurationPtr installation failed  \n"));
            return Status;
        }
#endif

        if (PcdGet16(PcdAgesaMemrestoreSupport))
        {
            //Only BR AM4 has memory restore function
            MemRestoreInit(PeiServices);
            Status = (*PeiServices)->NotifyPpi(PeiServices, MemRestoreSaveNotify);
        }

        // Read memory ceiling from NvRam
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable,
                    L"MemCeil.", &gAmiGlobalVariableGuid, NULL,
                    &VariableSize, &MemCeilVar );
        PcdSet16S(PcdAmdMemCfgBottomIo, (UINT16)(MemCeilVar >> 24));
        if (Status != EFI_SUCCESS)
        {
#if defined(FIXED_MMIO_RESOURCE) && (FIXED_MMIO_RESOURCE != 0)
            PcdSet16S(PcdAmdMemCfgBottomIo, (UINT16)((0xFFFFFFFF - FIXED_MMIO_RESOURCE + 1) >> 24));  // Minimum is Predefined by BIOS Porting
#else
            PcdSet16S(PcdAmdMemCfgBottomIo, (UINT16)(MCT_BOTTOM_IO_VALUE));   // Minimum is Predefined by BIOS Porting
#endif
        }

        GetNbSetupData((EFI_PEI_SERVICES **)PeiServices, &NbSetupData, TRUE);
        PcdSet32S(PcdAmdMemCfgUserTimingMode, 0);
        if (NbSetupData.MemClk != 0)
        {
            PcdSet32S(PcdAmdMemCfgUserTimingMode, 2);
            PcdSet32S(PcdAmdMemCfgMemClockValue, MemoryFreqArray[NbSetupData.MemClk - 1]);
        }
        PcdSetBoolS(PcdAmdMemCfgEnableBankIntlv, NbSetupData.EnableBankIntlv);
        PcdSetBoolS(PcdAmdMemCfgEnableChannelIntlv, NbSetupData.EnableChannelIntlv);

        if (NbSetupData.MemClr)
        {
            PcdSetBoolS(PcdAmdMemCfgEnableMemClr, TRUE);
        }
    }

    DEBUG ((DEBUG_INFO, "    AmiAgesaPeiEntry Exit\n"));

    return  Status;
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
