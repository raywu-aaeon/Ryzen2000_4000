//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
//*************************************************************************
// $Header:  $
//
// $Revision:  $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log:  $
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <AmiTcg/TcgCommon20.h>
#include <AmiTcg/sha.h>
#include <AmiTcg/TCGMisc.h>
#include <Token.h>
#include <AmiTcg/TpmLib.h>
#include <AmiTcg/TcgPc.h>
#include <AmiTcg/Tpm20Pei.h>
#include "Ppi/TcgService.h"
#include "Ppi/TpmDevice.h"
#include "Ppi/AmiTreePpi.h"
#include "Ppi/Edk2Tcg.h"
#include "Ppi/CpuIo.h"
#include "Ppi/LoadFile.h"
#include <Ffs.h>
#include "Ppi/TcgPlatformSetupPeiPolicy.h"
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PeiServicesLib.h>
#include <AmiTcg/AmiTpmStatusCodes.h>
#include <Guid/AmiTcgGuidIncludes.h>



extern EFI_GUID gAmiHashLogExtendExGuid;
extern EFI_GUID gTcgPeiPolicyGuid;
extern EFI_GUID AmiPeiHashInterfaceProtocolGuid;


UINT8 GetCurrentInterfaceType();
BOOLEAN IsPTP();
BOOLEAN CrbSupported();
BOOLEAN FIFOSupported();
UINT8 TisSupported();

#if defined (MDE_PKG_VERSION) && (MDE_PKG_VERSION > 9)
#ifndef TPM2_ALG_SHA1
#define TPM2_ALG_SHA1 TPM_ALG_SHA1
#endif
#ifndef TPM2_ALG_SHA256
#define TPM2_ALG_SHA256 TPM_ALG_SHA256
#endif
#ifndef TPM2_ALG_SHA384
#define TPM2_ALG_SHA384 TPM_ALG_SHA384
#endif
#ifndef TPM2_ALG_SHA512
#define TPM2_ALG_SHA512 TPM_ALG_SHA512
#endif
#ifndef TPM2_ALG_SM3_256
#define TPM2_ALG_SM3_256 TPM_ALG_SM3_256
#endif
#ifndef TPM2_ALG_ID
#define TPM2_ALG_ID TPM_ALG_ID
#endif
#endif
#pragma pack(push,1)

typedef struct
{
    TPM2_COMMAND_HEADER       Header;
    TPM_CAP                   Capability;
    UINT32                    Property;
    UINT32                    PropertyCount;
} TPM2_GET_CAPABILITY_COMMAND;

typedef struct
{
    TPM2_RESPONSE_HEADER      Header;
    TPMI_YES_NO               MoreData;
    TPMS_CAPABILITY_DATA      CapabilityData;
} TPM2_GET_CAPABILITY_RESPONSE;

#pragma pack(pop)

EFI_STATUS 
EFIAPI
TpmPeiReportStatusCode(  IN EFI_STATUS_CODE_TYPE   Type,
                         IN EFI_STATUS_CODE_VALUE  Value);

EFI_STATUS
EFIAPI Tpm20GetEventLog(
    OUT TCG_LOG_HOB     **EventLog );



#define TCG2_PROTOCOL_SPEC_TCG_1_2  0x01
#define TCG2_PROTOCOL_SPEC_TCG_2    0x02


EFI_STATUS
EFIAPI InstallEdkiiPpi(
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN VOID                      *Ppi );

EFI_PEI_NOTIFY_DESCRIPTOR   InstallEDKII_TCG_PPICallback =
{
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &AmiSignalEdkiiInstallGuid,
    InstallEdkiiPpi
};


EFI_STATUS
EFIAPI
Tpm2HashSequenceStart (
    IN  AMI_TREE_PPI    *TrEEPpi,
    IN TPMI_ALG_HASH   HashAlg,
    OUT TPMI_DH_OBJECT *SequenceHandle
);

EFI_STATUS
TrEEPeiGetDigestNonBIOSAlg(
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  OUT  UINT8              *Digest,
    IN  TPMI_ALG_HASH            AlgoId
);


EFI_STATUS
AmiPeiHashAllInterface (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  TPML_DIGEST_VALUES       *HashResults,
    IN  UINT32                   *AlgBitMap
);

EFI_STATUS
AmiPeiHashAllInterfaceInternal (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  TPML_DIGEST_VALUES       *HashResults,
    IN  UINT32                   *AlgBitMap
);


UINT32
EFIAPI
CopyAuthSessionCommand (
    IN      TPMS_AUTH_COMMAND         *AuthSessionIn, OPTIONAL
    OUT     UINT8                     *AuthSessionOut
);

EFI_STATUS GetAllDigestValues(UINT32 PcrBitMap,
                              TPML_DIGEST_VALUES *HashValues,
                              VOID            *HashData,
                              UINTN           HashDataLen,
                              UINTN           *TotalHashDigestLen);

EFI_STATUS
EFIAPI SHA384HashAll(
    IN  VOID            *HashData,
    IN  UINTN           HashDataLen,
    OUT UINT8           *Digest
);

EFI_STATUS
EFIAPI SHA512HashAll(
    IN  VOID            *HashData,
    IN  UINTN           HashDataLen,
    OUT UINT8           *Digest
);

EFI_STATUS
EFIAPI SM3HashAll(
    IN  VOID            *HashData,
    IN  UINTN           HashDataLen,
    OUT UINT8           *Digest
);


EFI_STATUS
EFIAPI
Tpm2SequenceUpdate (
    IN AMI_TREE_PPI    *TrEEPpi,
    IN TPMI_DH_OBJECT   SequenceHandle,
    IN TPM2B_MAX_BUFFER *Buffer
);

EFI_STATUS
EFIAPI
Tpm2SequenceComplete (
    IN  AMI_TREE_PPI    *TrEEPpi,
    IN TPMI_DH_OBJECT      SequenceHandle,
    IN TPM2B_MAX_BUFFER    *Buffer,
    OUT TPM2B_DIGEST       *Result
);

EFI_STATUS
EFIAPI TrEETisPeiInit()
{
    return Tpm20TisRequestLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) PORT_TPM_IOMEMBASE);
}

EFI_STATUS
EFIAPI TrEETisPeiClose()
{
    return Tpm20TisReleaseLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) PORT_TPM_IOMEMBASE);
}

void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0;
    UINTN j=0;

    for(i=0; i<BufferSize; i++)
    {

        if(i !=0)
        {
            DEBUG((DEBUG_INFO,"%02x ", Buffer[i]));
        }

        if(i%16 == 0)
        {
            DEBUG((DEBUG_INFO,"\n"));
            DEBUG((DEBUG_INFO,"%04x :", j));
            DEBUG((DEBUG_INFO,"%02x ", Buffer[i]));
            j+=1;
        }
    }
}


EFI_STATUS GetAllDigestValues(UINT32 PcrBitMap,
                              TPML_DIGEST_VALUES *HashValues,
                              VOID            *HashData,
                              UINTN           HashDataLen,
                              UINTN           *Digestsize)
{

    UINT32                      Count = 0;
    UINTN                       TotalSize=0;
    TCG_LOG_HOB                 *TcgLog = NULL;

    Tpm20GetEventLog(&TcgLog);

    if(TcgLog == NULL) return EFI_NOT_FOUND;

    DEBUG(( DEBUG_INFO," GetAllDigestValues:: PcrBitMap = %x \n", PcrBitMap));

    if(((PcrBitMap & 1) == 1))
    {
        //sha1
        Tpm20SHA1HashAll(NULL, HashData, HashDataLen, (UINT8 *)&HashValues->digests[Count].digest.sha1);
        HashValues->digests[Count].hashAlg = TPM2_ALG_SHA1;
        TotalSize += SHA1_DIGEST_SIZE;
        Count+=1;
    }

    DEBUG(( DEBUG_INFO," GetAllDigestValues:: Count = %x \n", Count));

    if(((PcrBitMap & 2) == 2) && (TcgLog->TableSize != 0))
    {
        //sha256
        DEBUG(( DEBUG_INFO," GetAllDigestValues::Sha256 \n"));
        SHA2HashAll(NULL, HashData, HashDataLen, (UINT8 *)&HashValues->digests[Count].digest.sha256);
        HashValues->digests[Count].hashAlg = TPM2_ALG_SHA256;
        TotalSize += SHA256_DIGEST_SIZE;
        Count+=1;
    }

    if(((PcrBitMap & 4) == 4) && (TcgLog->TableSize != 0))
    {
        //sha384
        SHA384HashAll(HashData, HashDataLen, (UINT8 *)&HashValues->digests[Count].digest.sha384);
        HashValues->digests[Count].hashAlg = TPM2_ALG_SHA384;
        TotalSize += SHA384_DIGEST_SIZE;
        Count+=1;
    }

    if(((PcrBitMap & 8) == 8) && (TcgLog->TableSize != 0))
    {
        //sha512
        SHA512HashAll(HashData, HashDataLen, (UINT8 *)&HashValues->digests[Count].digest.sha512);
        HashValues->digests[Count].hashAlg = TPM2_ALG_SHA512;
        TotalSize += SHA512_DIGEST_SIZE;
        Count+=1;
    }


    if(((PcrBitMap & 0x10) == 0x10) && (TcgLog->TableSize != 0))
    {
        DEBUG(( DEBUG_INFO," SM3 \n"));
        SM3HashAll(HashData, HashDataLen, (UINT8 *)&HashValues->digests[Count].digest.sm3_256);
        HashValues->digests[Count].hashAlg = TPM2_ALG_SM3_256;
        printbuffer((UINT8 *) &HashValues->digests[Count].digest.sm3_256, SM3_256_DIGEST_SIZE);
        TotalSize += SM3_256_DIGEST_SIZE;
        Count+=1;
    }

    DEBUG(( DEBUG_INFO," TotalSize = %x \n", TotalSize));

    HashValues->count = Count;
    *Digestsize = TotalSize;
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm2GetCapability (
    IN EFI_PEI_SERVICES               **PeiServices,
    IN      TPM_CAP                   Capability,
    IN      UINT32                    Property,
    IN      UINT32                    PropertyCount,
    OUT     TPMI_YES_NO               *MoreData,
    OUT     TPMS_CAPABILITY_DATA      *CapabilityData
)
{
    EFI_STATUS                        Status;
    TPM2_GET_CAPABILITY_COMMAND       SendBuffer;
    TPM2_GET_CAPABILITY_RESPONSE      RecvBuffer;
    UINT32                            SendBufferSize;
    UINT32                            RecvBufferSize;
    AMI_TREE_PPI                      *pTreePpi  =  NULL;

    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES    **)PeiServices,
                                       &gAmiTreePpiGuid,
                                       0,
                                       NULL,
                                       (void **)&pTreePpi);

    if(EFI_ERROR(Status))return Status;

    //
    // Construct command
    //
    SendBuffer.Header.tag = SwapBytes16(TPM_ST_NO_SESSIONS);
    SendBuffer.Header.commandCode = SwapBytes32(TPM_CC_GetCapability);

    SendBuffer.Capability = SwapBytes32 (Capability);
    SendBuffer.Property = SwapBytes32 (Property);
    SendBuffer.PropertyCount = SwapBytes32 (PropertyCount);

    SendBufferSize = (UINT32) sizeof (SendBuffer);
    SendBuffer.Header.paramSize = SwapBytes32 (SendBufferSize);

    //
    // send Tpm command
    //
    RecvBufferSize = sizeof (RecvBuffer);
    Status = pTreePpi->SubmitCommand (pTreePpi, SendBufferSize, (UINT8 *)&SendBuffer, RecvBufferSize, (UINT8 *)&RecvBuffer );
    if (EFI_ERROR (Status))
    {
        return Status;
    }

    if (RecvBufferSize <= sizeof (TPM2_RESPONSE_HEADER) + sizeof (UINT8))
    {
        return EFI_DEVICE_ERROR;
    }

    //
    // Return the response
    //
    *MoreData = RecvBuffer.MoreData;
    //
    // Does not unpack all possiable property here, the caller should unpack it and note the byte order.
    //
    CopyMem (CapabilityData, &RecvBuffer.CapabilityData, RecvBufferSize - sizeof (TPM2_RESPONSE_HEADER) - sizeof (UINT8));

    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilityManufactureID (
    IN      EFI_PEI_SERVICES        **PeiServices,
    OUT     UINT32                  *ManufactureId
)
{
    TPMS_CAPABILITY_DATA    TpmCap;
    TPMI_YES_NO             MoreData;
    EFI_STATUS              Status;

    Status = Tpm2GetCapability ( PeiServices,
                                 TPM_CAP_TPM_PROPERTIES,
                                 TPM_PT_MANUFACTURER,
                                 1,
                                 &MoreData,
                                 &TpmCap
                               );
    if (EFI_ERROR (Status))
    {
        return Status;
    }
    *ManufactureId = SwapBytes32 (TpmCap.data.tpmProperties.tpmProperty->value);

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Tpm2GetCapabilityMaxCommandResponseSize (
    IN  EFI_PEI_SERVICES        **PeiServices,
    OUT UINT32                    *MaxCommandSize,
    OUT UINT32                    *MaxResponseSize
)
{
    TPMS_CAPABILITY_DATA    TpmCap;
    TPMI_YES_NO             MoreData;
    EFI_STATUS              Status;

    Status = Tpm2GetCapability (PeiServices,
                                TPM_CAP_TPM_PROPERTIES,
                                TPM_PT_MAX_COMMAND_SIZE,
                                1,
                                &MoreData,
                                &TpmCap
                               );
    if (EFI_ERROR (Status))
    {
        return Status;
    }

    *MaxCommandSize = SwapBytes32 (TpmCap.data.tpmProperties.tpmProperty->value);

    Status = Tpm2GetCapability (PeiServices,
                                TPM_CAP_TPM_PROPERTIES,
                                TPM_PT_MAX_RESPONSE_SIZE,
                                1,
                                &MoreData,
                                &TpmCap
                               );
    if (EFI_ERROR (Status))
    {
        return Status;
    }

    *MaxResponseSize = SwapBytes32(TpmCap.data.tpmProperties.tpmProperty->value);
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
Tpm2GetCapabilitySupportedAlg (
    IN  EFI_PEI_SERVICES        **PeiServices,
    OUT TPML_ALG_PROPERTY      *AlgList
)
{
    TPMS_CAPABILITY_DATA    TpmCap;
    TPMI_YES_NO             MoreData;
    UINTN                   Index;
    EFI_STATUS              Status;

    Status = Tpm2GetCapability (PeiServices,
                                TPM_CAP_ALGS,
                                1,
                                MAX_CAP_ALGS,
                                &MoreData,
                                &TpmCap
                               );
    if (EFI_ERROR (Status))
    {
        return Status;
    }

    CopyMem (AlgList, &TpmCap.data.algorithms, sizeof (TPML_ALG_PROPERTY));

    AlgList->count = SwapBytes32 (AlgList->count);
    for (Index = 0; Index < AlgList->count; Index++)
    {
        AlgList->algProperties[Index].alg = SwapBytes16 (AlgList->algProperties[Index].alg);
        *(UINT32 *)&AlgList->algProperties[Index].algProperties = SwapBytes32 (*(UINT32 *)&AlgList->algProperties[Index].algProperties);
    }
    return EFI_SUCCESS;
}



EFI_STATUS
TreeGetCapability (
    IN AMI_TREE_PPI                *This,
    IN OUT AMI_TREE_BOOT_SERVICE_CAPABILITY *ProtocolCapability
)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_PEI_SERVICES        **PeiServices;
    UINT32                  ManufactureID = 0x0;
    UINT32                  MaxResponseSize = 0x0;
    UINT32                  MaxCommandSize  = 0x0;
    TCG_LOG_HOB             *TcgLog = NULL;

    Status = Tpm20GetEventLog(&TcgLog);
    if (NULL == TcgLog)
    {
        return EFI_UNSUPPORTED;
    }

    PeiServices = (EFI_PEI_SERVICES  **)GetPeiServicesTablePointer ();

    if((ProtocolCapability == NULL) || (This == NULL))
    {
        Status = EFI_INVALID_PARAMETER;
    }
    else
    {

        Status = Tpm2GetCapabilityManufactureID (PeiServices, &ManufactureID);
        if(EFI_ERROR(Status))
        {
            return Status;
        }

        Status = Tpm2GetCapabilityMaxCommandResponseSize (PeiServices, &MaxCommandSize, &MaxResponseSize);
        if(EFI_ERROR(Status))
        {
            return Status;
        }


        if(ProtocolCapability->Size < (sizeof(UINT8) + sizeof(AMI_TREE_VERSION) + sizeof(AMI_TREE_VERSION)))
        {
            Status = EFI_BUFFER_TOO_SMALL;
        }
        else
        {
            ProtocolCapability->StructureVersion.Major = 1;
            ProtocolCapability->StructureVersion.Minor = 0;
            ProtocolCapability->ProtocolVersion.Major  = 1;
            ProtocolCapability->ProtocolVersion.Minor  = 0;

            if (ProtocolCapability->Size < sizeof(AMI_TREE_BOOT_SERVICE_CAPABILITY))
            {
                ProtocolCapability->Size = sizeof(AMI_TREE_BOOT_SERVICE_CAPABILITY);
                Status = EFI_BUFFER_TOO_SMALL;
            }
            else
            {

                if( TcgLog->Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2)
                {
                    ProtocolCapability->HashAlgorithmBitmap = AMI_TREE_BOOT_HASH_ALG_SHA1;
                }
                else if(TcgLog->Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2)
                {
                    ProtocolCapability->HashAlgorithmBitmap = AMI_TREE_BOOT_HASH_ALG_SHA256;
                }

                ProtocolCapability->SupportedEventLogs  = AMI_TREE_EVENT_LOG_FORMAT_TCG_1_2;
                ProtocolCapability->TreePresentFlag     = TRUE;
                ProtocolCapability->MaxCommandSize      = (UINT16)MaxCommandSize;
                ProtocolCapability->MaxResponseSize     = (UINT16)MaxResponseSize;
                ProtocolCapability->ManufacturerID      = ManufactureID;
            }
        }
    }

    return Status;
}




EFI_STATUS
EFIAPI TrEECRBPeiTransmit(
    IN  AMI_TREE_PPI             *This,
    IN  UINT32                  InputParameterBlockSize,
    IN  UINT8                   *InputParameterBlock,
    IN  UINT32                  OutputParameterBlockSize,
    IN  UINT8                   *OutputParameterBlock )
{
    EFI_STATUS            Status     = EFI_SUCCESS;
    UINT32                Size = 0;

    if ( InputParameterBlock == NULL || OutputParameterBlock == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    Size = OutputParameterBlockSize;
    Status = CrbSubmitCmd(InputParameterBlock,
                          InputParameterBlockSize,
                          OutputParameterBlock,
                          &Size);

    return Status;
}



EFI_STATUS
EFIAPI TrEETisPeiTransmit(
    IN  AMI_TREE_PPI             *This,
    IN  UINT32                  InputParameterBlockSize,
    IN  UINT8                   *InputParameterBlock,
    IN  UINT32                  OutputParameterBlockSize,
    IN  UINT8                   *OutputParameterBlock )
{
    EFI_STATUS             Status     = EFI_SUCCESS;
    TPM_1_2_REGISTERS_PTR  TpmReg;
    EFI_PHYSICAL_ADDRESS   TPM_Base = (EFI_PHYSICAL_ADDRESS)PORT_TPM_IOMEMBASE;
    TPM_TRANSMIT_BUFFER      InBuffer[1], OutBuffer[1];

    if (InputParameterBlock == NULL || OutputParameterBlock == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    InBuffer[0].Buffer  = InputParameterBlock;
    InBuffer[0].Size    = InputParameterBlockSize;
    OutBuffer[0].Buffer = OutputParameterBlock;
    OutBuffer[0].Size   = OutputParameterBlockSize;

    TpmReg  = (TPM_1_2_REGISTERS_PTR)( UINTN ) TPM_Base;

    Status = TrEETisPeiInit();
    if(EFI_ERROR(Status))return Status;

    Status = Tpm20TpmLibPassThrough(
                  TpmReg,
                  sizeof (InBuffer) / sizeof (*InBuffer),
                  InBuffer,
                  sizeof (OutBuffer) / sizeof (*OutBuffer),
                  OutBuffer
              );

    TrEETisPeiClose();
    return Status;
}




EFI_STATUS SelectAndLockInterface(CONST EFI_PEI_SERVICES  **PeiServices, UINT8 Interface)
{
    volatile UINT8 *IntefSel = (volatile UINT8 *)(PORT_TPM_IOMEMBASE + 0x32);

    DEBUG((DEBUG_INFO, "GetCurrentInterfaceType results = %x \n", GetCurrentInterfaceType()));
    DEBUG((DEBUG_INFO, "Input InterfaceType = %x \n", Interface));

    if(GetCurrentInterfaceType()!=Interface)
    {
        if(Interface == 1)
        {
            //CRB interface, check if supported
            if(CrbSupported() == 0x02)
            {
                *IntefSel |= 0x02;  //set CRB
                (*(PeiServices))->ResetSystem(PeiServices);
                return EFI_SUCCESS;
            }
        }
        if(Interface == 0)
        {
            //CRB interface, check if supported
            if(FIFOSupported())
            {
                *IntefSel &= 0xFC;  //set CRB
                (*(PeiServices))->ResetSystem(PeiServices);
                return EFI_SUCCESS;
            }
        }
    }

    DEBUG((DEBUG_INFO, "IntefSel = %x \n", *IntefSel));
    if((*IntefSel & 0x08)==0)
    {
        *IntefSel |= 0x08;  //lock CRB
    }
    DEBUG((DEBUG_INFO, "IntefSel = %x \n", *IntefSel));
    return EFI_SUCCESS;
}


EFI_STATUS
PeiTrEEExtend(
    IN  AMI_TREE_PPI        *TrEEPpi,
    IN  TPM_PCRINDEX        PcrIndex,
    IN  TPML_DIGEST_VALUES  *Digest)
{
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    TPM2_PCRExtend_res_t  Tmpres;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;
    UINT32                DigestSize=0;
    UINT32                SessionInfoSize;
    EFI_STATUS            Status;
    UINTN                 i=0;

    Cmd.Tag          = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.CommandCode  = SwapBytes32(TPM_CC_PCR_Extend);
    Cmd.PcrHandle    = SwapBytes32(PcrIndex);

    Buffer = (UINT8 *)&Cmd.AuthSessionPcr;

    SessionInfoSize = CopyAuthSessionCommand (NULL, Buffer);
    Buffer += SessionInfoSize;
    Cmd.AuthorizationSize = SwapBytes32(SessionInfoSize);

    DEBUG ((DEBUG_INFO, " PeiTrEEExtend Cmd = %x \n", &Cmd));

    //Digest count
    *(UINT32 *)Buffer = SwapBytes32(Digest->count);
    Buffer += sizeof(UINT32);

    DEBUG ((DEBUG_INFO, " PeiTrEEExtend Buffer = %x \n", Buffer));

    for(i=0; i<Digest->count; i++)
    {
        *(UINT16 *)Buffer = SwapBytes16(Digest->digests[i].hashAlg);
        Buffer += sizeof(UINT16);
        DEBUG ((DEBUG_INFO, " Digest->digests[i].hashAlg = %x \n", Digest->digests[i].hashAlg));
        switch(Digest->digests[i].hashAlg)
        {
            case TPM2_ALG_SHA1:
                DigestSize = SHA1_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA256:
                DigestSize = SHA256_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA384:
                DigestSize = SHA384_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA512:
                DigestSize = SHA512_DIGEST_SIZE;
                break;
            case TPM2_ALG_SM3_256:
                DigestSize = SM3_256_DIGEST_SIZE;
                break;
            default:
                break;
        }

        Tpm20TcgCommonCopyMem(NULL, Buffer, &Digest->digests[i].digest, DigestSize);
        Buffer += DigestSize;
    }

    DEBUG ((DEBUG_INFO, " PeiTrEEExtend Buffer = %x \n", Buffer));

    DEBUG ((DEBUG_INFO, " PeiTrEEExtend Buffer-Cmd = %x \n", (Buffer - (UINT8 *)&Cmd)));

    DEBUG ((DEBUG_INFO, " PeiTrEEExtend DigestSize = %x \n", DigestSize));

    CmdSize = (UINT32)(Buffer - (UINTN)&Cmd);
    Cmd.CommandSize = SwapBytes32(CmdSize);

    ResultBuf     = (UINT8 *) &Tmpres;
    ResultBufSize = sizeof(Res);

    DEBUG ((DEBUG_INFO, "AmiHashLogExtend2 FwVol\n"));
    DEBUG ((DEBUG_INFO, "PeiTrEEExtend CmdSize = %x \n", CmdSize));
    //printbuffer((UINT8 *)&Cmd,(UINTN)CmdSize);

    Status  = TrEEPpi->SubmitCommand(TrEEPpi,CmdSize, (UINT8 *)&Cmd, ResultBufSize, ResultBuf);    

    return Status;
}


typedef UINT16 TPM2_ALG_ID;

EFI_STATUS
TrEEPeiGetDigestNonBIOSAlg(
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  OUT  UINT8              *Digest,
    IN  TPMI_ALG_HASH            AlgoId
)
{
    TPMI_DH_OBJECT        HashHandle;
    EFI_STATUS            Status;
    UINT64                HashLen;
    TPM2B_MAX_BUFFER      HashBuffer;
    UINT8                 *Buffer;
    TPM2B_DIGEST          Result;
    CONST EFI_PEI_SERVICES      **PeiServices;
    AMI_TREE_PPI          *TrEEPpi  =  NULL;

    PeiServices = GetPeiServicesTablePointer ();

    Status = (*PeiServices)->LocatePpi(PeiServices,
                                       &gAmiTreePpiGuid,
                                       0,
                                       NULL,
                                       (void **)&TrEEPpi);

    if(EFI_ERROR(Status))return Status;

    DEBUG(( DEBUG_INFO," Tpm2HashSequenceStarting \n"));

    Status = Tpm2HashSequenceStart (TrEEPpi, AlgoId, &HashHandle);
    DEBUG(( DEBUG_INFO," Tpm2HashSequenceStarting results = %r \n", Status));

    Buffer = DataToHash;
    for (HashLen = DataSize; HashLen > sizeof(HashBuffer.buffer); HashLen -= sizeof(HashBuffer.buffer))
    {

        HashBuffer.size = sizeof(HashBuffer.buffer);
        CopyMem(HashBuffer.buffer, Buffer, sizeof(HashBuffer.buffer));
        Buffer += sizeof(HashBuffer.buffer);

        Status = Tpm2SequenceUpdate(TrEEPpi, (TPMI_DH_OBJECT)HashHandle, &HashBuffer);
        DEBUG(( DEBUG_INFO," Tpm2SequenceUpdate results = %r \n", Status));
        if (EFI_ERROR(Status))
        {
            return EFI_DEVICE_ERROR;
        }
    }


    HashBuffer.size = (UINT16)HashLen;
    CopyMem(HashBuffer.buffer, Buffer, (UINTN)HashLen);
    Status = Tpm2SequenceUpdate(TrEEPpi, (TPMI_DH_OBJECT)HashHandle, &HashBuffer);
    if (EFI_ERROR(Status))
    {
        return EFI_DEVICE_ERROR;
    }

    Status = Tpm2SequenceComplete (
                 TrEEPpi,
                 HashHandle,
                 &HashBuffer,
                 &Result
             );
    if (EFI_ERROR(Status))
    {
        return EFI_DEVICE_ERROR;
    }

    DEBUG(( DEBUG_INFO," Tpm2SequenceComplete Status = %r \n", Status));
    DEBUG(( DEBUG_INFO," Tpm2SequenceComplete Result.size = %x \n", Result.size));

    printbuffer((UINT8 *) &Result.buffer, Result.size);

    CopyMem (Digest, Result.buffer, Result.size);

    return EFI_SUCCESS;
}

EFI_STATUS DigestListArrayToBuffer(TPML_DIGEST_VALUES *Array, TPML_DIGEST_VALUES *Buffer )
{
    UINT8 i=0;
    UINT8 *iter = (UINT8 *)Buffer;
    
    if(Array == NULL || Buffer == NULL ){
        return EFI_INVALID_PARAMETER;
    }
    
    *(UINT32 *)iter = Array->count;
    iter += sizeof (Array->count);
    
    for(i=0;i<Array->count; i++){
        switch (Array->digests[i].hashAlg){
            case TPM2_ALG_SHA1: //sha1
                CopyMem(iter,&Array->digests[i].hashAlg, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(iter,&Array->digests[i].digest, SHA1_DIGEST_SIZE);
                iter += SHA1_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA256:
                CopyMem(iter,&Array->digests[i].hashAlg, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(iter,&Array->digests[i].digest, SHA256_DIGEST_SIZE);
                iter += SHA256_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA384:
                CopyMem(iter,&Array->digests[i].hashAlg, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(iter,&Array->digests[i].digest, SHA384_DIGEST_SIZE);
                iter += SHA384_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA512:
                CopyMem(iter,&Array->digests[i].hashAlg, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(iter,&Array->digests[i].digest, SHA512_DIGEST_SIZE);
                iter += SHA512_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SM3_256:
                CopyMem(iter,&Array->digests[i].hashAlg, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(iter,&Array->digests[i].digest, SM3_256_DIGEST_SIZE);
                iter += SM3_256_DIGEST_SIZE;
                continue;
            default:
                continue;
      }
    }
    return EFI_SUCCESS;
}



EFI_STATUS DigestListBufferToArray(TPML_DIGEST_VALUES *Buffer, TPML_DIGEST_VALUES *Array )
{
    UINT8 i=0;
    UINT8 *iter = (UINT8 *)Buffer;
    TPMI_ALG_HASH   Algo;
    
    if(Array == NULL || Buffer == NULL ){
        return EFI_INVALID_PARAMETER;
    }
    
    
    iter += sizeof(UINT32);
    
    Array->count = ((TPML_DIGEST_VALUES *)Buffer)->count;
        
    for(i=0;i<((TPML_DIGEST_VALUES *)Buffer)->count; i++){
        Algo = *((TPMI_ALG_HASH *)iter);
        switch (Algo){
            case TPM2_ALG_SHA1: //sha1
                CopyMem(&Array->digests[i].hashAlg, iter, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(&Array->digests[i].digest.sha1, iter, SHA1_DIGEST_SIZE);
                iter += SHA1_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA256:
                CopyMem(&Array->digests[i].hashAlg, iter, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(&Array->digests[i].digest.sha256, iter,SHA256_DIGEST_SIZE);
                iter += SHA256_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA384:
                CopyMem(&Array->digests[i].hashAlg, iter, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(&Array->digests[i].digest, iter, SHA384_DIGEST_SIZE);
                iter += SHA384_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SHA512:
                CopyMem(&Array->digests[i].hashAlg, iter, sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(&Array->digests[i].digest, iter,SHA512_DIGEST_SIZE);
                iter += SHA512_DIGEST_SIZE;
                continue;
            case TPM2_ALG_SM3_256:
                CopyMem(&Array->digests[i].hashAlg, iter,sizeof(TPMI_ALG_HASH));
                iter += sizeof(TPMI_ALG_HASH);
                CopyMem(&Array->digests[i].digest, iter, SM3_256_DIGEST_SIZE);
                iter += SM3_256_DIGEST_SIZE;
                continue;
            default:
                continue;
      }
    }
  return EFI_SUCCESS;
}


EFI_STATUS
HashAndExtend(  
        IN TPMI_DH_PCR         PcrIndex,
        IN VOID                *DataToHash,
        IN UINTN               DataToHashLen,
        OUT TPML_DIGEST_VALUES *DigestList)
{
    EFI_STATUS       Status;
    AMI_TREE_PPI    *gTreePpi = NULL;
    CONST EFI_PEI_SERVICES    **PeiServices = NULL;
    TPML_DIGEST_VALUES DigestListArray;
    TCG_PLATFORM_SETUP_INTERFACE *TcgPeiPolicy;
    TCG_CONFIGURATION   gInternalConfigFlags;
    UINT32 gPcrBanks =0;
    
    if(DataToHash == NULL || DataToHashLen == 0)
        return EFI_INVALID_PARAMETER;
    
    PeiServices = GetPeiServicesTablePointer ();
    
    if( PeiServices == NULL || *PeiServices == NULL){
        DEBUG(( DEBUG_INFO," PeiServices not available \n"));
        return EFI_NOT_FOUND;
    }
    
    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES    **)PeiServices,
                                            &gAmiTreePpiGuid,
                                            0,
                                            NULL,
                                           (void **)&gTreePpi);

    if((EFI_ERROR(Status)) || (gTreePpi == NULL))return EFI_NOT_READY;
    
    Status = PeiServicesLocatePpi (
                     &gTcgPeiPolicyGuid,
                     0,
                     NULL,
                     (VOID **) &TcgPeiPolicy
                     );

    if(EFI_ERROR(Status))return Status;
    
    Status = TcgPeiPolicy->getTcgPeiPolicy(NULL, &gInternalConfigFlags);
    if(EFI_ERROR(Status))return Status;
    
    gPcrBanks = gInternalConfigFlags.PcrBanks;
    
    Status = AmiPeiHashAllInterfaceInternal(gTreePpi, DataToHash, DataToHashLen, 
                                    &DigestListArray, &gPcrBanks);
    
    if(EFI_ERROR(Status))return Status;
    
    //extend digest to TPM 
    Status = PeiTrEEExtend(gTreePpi,
                            PcrIndex,
                            &DigestListArray);
    
    DigestListArrayToBuffer(&DigestListArray,DigestList);
    
    return Status;
}

UINTN getHashLogSpaceFromTPML(TPML_DIGEST_VALUES *DigestList)
{
    UINT8 i = 0;
    TPMT_HA *DigestEntryPtr;
    UINT8   *Traverser = (UINT8 *)DigestList;
    UINTN   TotalHashSpace = 0;
    
    if(DigestList == NULL)
        return 0;
    
    Traverser += sizeof(UINT32);
    TotalHashSpace += sizeof(UINT32);
    
    for(i=0; i<DigestList->count ; i++){
        DigestEntryPtr = (TPMT_HA *)Traverser;
        switch (DigestEntryPtr->hashAlg){
            case TPM2_ALG_SHA1:
                TotalHashSpace += sizeof(TPMI_ALG_HASH);
                TotalHashSpace += SHA1_DIGEST_SIZE;
                Traverser += sizeof(TPMI_ALG_HASH) + SHA1_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA256:
                TotalHashSpace += sizeof(TPMI_ALG_HASH);
                TotalHashSpace += SHA256_DIGEST_SIZE;
                Traverser += sizeof(TPMI_ALG_HASH) + SHA256_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA384:
                TotalHashSpace += sizeof(TPMI_ALG_HASH);
                TotalHashSpace += SHA384_DIGEST_SIZE;
                Traverser += sizeof(TPMI_ALG_HASH) + SHA384_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA512:
                TotalHashSpace += sizeof(TPMI_ALG_HASH);
                TotalHashSpace += SHA512_DIGEST_SIZE;
                Traverser += sizeof(TPMI_ALG_HASH) + SHA512_DIGEST_SIZE;
                break;
            case TPM2_ALG_SM3_256:
                TotalHashSpace += sizeof(TPMI_ALG_HASH);
                TotalHashSpace += SM3_256_DIGEST_SIZE;
                Traverser += sizeof(TPMI_ALG_HASH) + TPM2_ALG_SM3_256;
                break;
            default:
                break;
        }
    }
    
    return TotalHashSpace;
}

EFI_STATUS
LogHashEvent ( TPML_DIGEST_VALUES *DigestList, 
               OUT  TCG_PCR_EVENT_HDR  *NewEventHdr,
               UINT8                    *NewEventData )
{
    TCG_LOG_HOB        *TcgLog = NULL;
    EFI_STATUS         Status;
    UINT8              i=0;
    TPMT_HA            *DigestEntryPtr;
    UINT8              *Iter = (UINT8 *)DigestList;
    UINT32              LogSize=0;
    UINTN               RequiredSpace=0;
    UINTN               TreeEventLogLocation = 0;
    UINT32             *Counter=NULL;
    UINT32              Count=0;
    TCG_PLATFORM_SETUP_INTERFACE *TcgPeiPolicy;
    TCG_CONFIGURATION   gInternalConfigFlags;
    UINT32              gPcrBanks =0;    
    
    if(DigestList == NULL || NewEventHdr == NULL 
            || NewEventData == NULL){
        
        return EFI_INVALID_PARAMETER;
    }
    
    Status = Tpm20GetEventLog (&TcgLog);
    if(EFI_ERROR(Status))return Status;
    
    Status = PeiServicesLocatePpi (
                 &gTcgPeiPolicyGuid,
                 0,
                 NULL,
                 (VOID **) &TcgPeiPolicy
                 );

    if(EFI_ERROR(Status))return Status;
    
    Status = TcgPeiPolicy->getTcgPeiPolicy(NULL, &gInternalConfigFlags);
    
    gPcrBanks = gInternalConfigFlags.PcrBanks;
    
    RequiredSpace = getHashLogSpaceFromTPML(DigestList);

    TreeEventLogLocation = (UINTN)TcgLog + sizeof(TCG_LOG_HOB);
    if((RequiredSpace + TcgLog->LastEntry) > \
                 (TreeEventLogLocation  + PEI_MAX_LOG_AREA_SIZE)){
        TcgLog->IEventLogTruncated = TRUE;
    }
    
    if(TcgLog->IEventLogTruncated)return EFI_VOLUME_FULL;
    
    CopyMem((VOID*)(UINTN)TcgLog->LastEntry, NewEventHdr,
                sizeof(TCG_PCRINDEX) +  sizeof(TCG_EVENTTYPE));
    
    LogSize = sizeof(TCG_PCRINDEX) +  sizeof(TCG_EVENTTYPE);
           
    if(gInternalConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2)
    {
        Iter += sizeof(UINT32);
        for(i=0; i<DigestList->count; i++){
            DigestEntryPtr = (TPMT_HA *)Iter;

            switch (DigestEntryPtr->hashAlg){
                case TPM2_ALG_SHA1:
                    break;
                default:
                    continue;
            }
        }
        
        if(DigestEntryPtr->hashAlg == TPM2_ALG_SHA1)
        {
            CopyMem(
            (UINT8 *)(UINTN)(TcgLog->LastEntry) + LogSize,
            (UINT8 *)&DigestEntryPtr->hashAlg,
            SHA1_DIGEST_SIZE + sizeof(TPM_ALG_ID));
        }
    }
    else if(gInternalConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2)
    {
        Counter = (UINT32 *)(UINTN)(TcgLog->LastEntry + LogSize);
        LogSize+= sizeof(UINT32);
        
        Iter += sizeof(UINT32);
        for(i=0; i<DigestList->count; i++){
           
            DigestEntryPtr = (TPMT_HA *)Iter;
            
            DEBUG(( DEBUG_INFO,"DigestEntryPtr->hashAlg = %x \n", DigestEntryPtr->hashAlg));

            switch (DigestEntryPtr->hashAlg){
                case TPM2_ALG_SHA1: //sha1
                    DEBUG(( DEBUG_INFO,"Case Sha-1 \n"));
                    if(gPcrBanks & 1)
                    {
                        DEBUG(( DEBUG_INFO,"System Supports Sha-1 \n"));
                        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + LogSize),
                                (UINT8 *)Iter,
                                (SHA1_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

                        LogSize += ((SHA1_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_1_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
                    }
                    Iter += sizeof(TPMI_ALG_HASH) + SHA1_DIGEST_SIZE;
                    continue;
                case TPM2_ALG_SHA256:
                    DEBUG(( DEBUG_INFO,"Case Sha-256 \n"));
                    if(gPcrBanks & 2)
                    {
                       //sha256
                        DEBUG(( DEBUG_INFO,"System Supports Sha-256\n"));
                        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + LogSize),
                                   (UINT8 *)Iter,
                                   (SHA256_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));
                        
                        LogSize += ((SHA256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_256_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
                        Count++;
                    }
                    Iter+= ((SHA256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                    continue;
                case TPM2_ALG_SHA384:
                    if(gPcrBanks & 4)
                    {
                        //sha256
                        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + LogSize) ,
                                (UINT8 *)Iter,
                                (SHA384_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

                        LogSize+= ((SHA384_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_384_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
                        Count++;
                    }
                        
                    Iter+= ((SHA384_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                    continue;
                case TPM2_ALG_SHA512:
                    if(gPcrBanks & 8)
                    {
                        //sha512
                        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + LogSize) ,
                                (UINT8 *)Iter,
                                (SHA512_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

                        LogSize+= ((SHA512_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_512_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
                        Count++;
                    }
                    
                    Iter+= ((SHA512_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                    continue;
                case TPM2_ALG_SM3_256:
                    if(gPcrBanks & 0x10)
                    {
                        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + LogSize) ,
                                (UINT8 *)Iter,
                                (SM3_256_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

                        LogSize+= ((SM3_256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_SM3_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
                        Count++;
                    }
                    
                    Iter+= ((SM3_256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
                    continue;
                default:
                    continue;
            }
        }
    }

    if(Counter != NULL){
        *Counter =Count;
    }
    
    CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + LogSize) ,
            &NewEventHdr->EventSize,
            sizeof(UINT32));
    
    LogSize+=sizeof(UINT32);

    DEBUG((DEBUG_INFO, "LogSize = %x \n", LogSize));
    CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + LogSize) ,
            NewEventData,
            NewEventHdr->EventSize);

    DEBUG((DEBUG_INFO, "NewEventHdr->EventType = %x \n", NewEventHdr->EventType));

    TcgLog->LastEventPtr = TcgLog->LastEntry;
    TcgLog->LastEntry = TcgLog->LastEventPtr + ((EFI_PHYSICAL_ADDRESS)(UINTN)(NewEventHdr->EventSize \
                        + LogSize));
    
    TcgLog->TableSize += (LogSize + NewEventHdr->EventSize);

    ++TcgLog->EventNum;
    
    return EFI_SUCCESS;
}


EFI_STATUS
AMIEdkIIHashLogExtentEvent(
    IN  EDKII_TCG_PPI       *This,
    IN  UINT64               Flags,
    IN  UINT8               *HashData,
    IN  UINTN                HashDataLen,
    IN  OUT  TCG_PCR_EVENT_HDR  *NewEventHdr,
    IN  UINT8                    *NewEventData
)
{
    EFI_STATUS                Status;
    TPML_DIGEST_VALUES        DigestList;
    TPML_DIGEST_VALUES        DigestListArray;
    CONST EFI_PEI_SERVICES    **PeiServices = NULL;
    AMI_TREE_PPI              *gTreePpi = NULL;

    DEBUG(( DEBUG_INFO," AMIEdkIIHashLogExtentEvent \n"));
    
    PeiServices = GetPeiServicesTablePointer ();
    
    if( PeiServices == NULL || *PeiServices == NULL){
        DEBUG(( DEBUG_INFO," PeiServices not available \n"));
        return EFI_NOT_FOUND;
    }
    
    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES    **)PeiServices,
                                            &gAmiTreePpiGuid,
                                            0,
                                            NULL,
                                           (void **)&gTreePpi);

    if((EFI_ERROR(Status)) || (gTreePpi == NULL))return EFI_NOT_READY;
    
    if ((Flags & EDKII_TCG_PRE_HASH) != 0 || (Flags & EDKII_TCG_PRE_HASH_LOG_ONLY) != 0) {
       ZeroMem (&DigestList, sizeof(DigestList));
       CopyMem (&DigestList, HashData, sizeof(DigestList));
       Status = EFI_SUCCESS;
       if ((Flags & EDKII_TCG_PRE_HASH) !=0 ) {
               DigestListBufferToArray((TPML_DIGEST_VALUES *)HashData, &DigestListArray);
               Status = PeiTrEEExtend(gTreePpi,
                                  NewEventHdr->PCRIndex,
                                  &DigestListArray);
       }
    }else {
        Status = HashAndExtend (
                   NewEventHdr->PCRIndex,
                   HashData,
                   HashDataLen,
                   &DigestList
                   );
    }
    
    if (!EFI_ERROR (Status)) {
        Status = LogHashEvent (&DigestList, NewEventHdr, NewEventData);
    }
    
    if (Status == EFI_DEVICE_ERROR) {
        return Status;
     }
    
    return EFI_SUCCESS;
}


/**
  Do a hash operation on a data buffer, extend a specific TPM PCR with the hash result,
  and build a GUIDed HOB recording the event which will be passed to the DXE phase and
  added into the Event Log.
  @param[in]      This          Indicates the calling context
  @param[in]      Flags         Bitmap providing additional information.
  @param[in]      HashData      Physical address of the start of the data buffer
                                to be hashed, extended, and logged.
  @param[in]      HashDataLen   The length, in bytes, of the buffer referenced by HashData.
  @param[in]      NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in]      NewEventData  Pointer to the new event data.
  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.
**/
EFI_STATUS
EFIAPI
HashLogExtendEvent (
  IN      EDKII_TCG_PPI             *This,
  IN      UINT64                    Flags,
  IN      UINT8                     *HashData,
  IN      UINTN                     HashDataLen,
  IN      TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  );

EDKII_TCG_PPI mEdkiiTcgPpi = {
   AMIEdkIIHashLogExtentEvent
};

EFI_PEI_PPI_DESCRIPTOR  edkIIPpiInstall = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEdkiiTcgPpiGuid,
  &mEdkiiTcgPpi
};

EFI_STATUS
EFIAPI InstallEdkiiPpi(
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN VOID                      *Ppi )
{
    EFI_STATUS Status;
    DEBUG((DEBUG_INFO, "Installing EdkiiPpi \n"));
    Status = PeiServicesInstallPpi (&edkIIPpiInstall);
    DEBUG((DEBUG_INFO, "EdkiiPpi Install status = %r \n", Status));
    ASSERT_EFI_ERROR(Status);
    return EFI_SUCCESS;
}


EFI_STATUS
TrEEPeiHashLogExtentEventInternal(
    IN CONST EFI_PEI_SERVICES       **PeiServices,
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *DataToHash,
    IN  UINT64                   Flags,
    IN  UINTN                    DataSize,
    IN  OUT  TCG_PCR_EVENT2_HDR  *NewEventHdr,
    IN  UINT8                    *NewEventData
)
{
    EFI_STATUS                Status;
    UINT32                    TempSize=0;
    UINTN                     RequiredSpace=0;
    TCG_PLATFORM_SETUP_INTERFACE *TcgPeiPolicy;

    TCG_CONFIGURATION       ConfigFlags;
    TCG_PCClient_PCR_Event2_Hdr   EventData;
    UINT32                    PcrBanks;
    UINT32                    Count=0;
    UINTN                     HashSize=0;
    UINT16                    i=0;
    TCG_LOG_HOB                 *TcgLog = NULL;
    UINTN                       TreeEventLogLocation = 0;

    DEBUG(( DEBUG_INFO," TpmHashLogExtendEvent Entry \n"));
#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(NewEventHdr->EventType == EV_EFI_ACTION && NewEventHdr->PCRIndex != 7)
    {
        return EFI_SUCCESS;
    }
#endif
    Status = (*PeiServices)->LocatePpi(PeiServices,
                                       &gTcgPeiPolicyGuid,
                                       0, NULL,
                                       (void **)&TcgPeiPolicy);

    if(EFI_ERROR(Status) || TcgPeiPolicy == NULL )return Status;

    Status = Tpm20GetEventLog (&TcgLog);

    Status = TcgPeiPolicy->getTcgPeiPolicy((EFI_PEI_SERVICES **)PeiServices, &ConfigFlags);
    PcrBanks = ConfigFlags.PcrBanks;
    if(TrEEPpi == NULL)return EFI_INVALID_PARAMETER;
    if(TcgLog == NULL)return EFI_NOT_FOUND;

    if( ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2)
    {
        PcrBanks = 1;
    }
    
    if((DataToHash != 0) && (DataSize != 0))
    {
        GetAllDigestValues(PcrBanks, &NewEventHdr->Digests, DataToHash, DataSize, &HashSize);
    }
    else
    {
        if((PcrBanks & 1) == 1)
        {
            HashSize += SHA1_DIGEST_SIZE;
            Count+=1;
        }

        if((PcrBanks & 2) == 2)
        {
            //sha256
            HashSize += SHA256_DIGEST_SIZE;
            Count+=1;
        }

        if((PcrBanks & 4) == 4)
        {
            //sha384
            HashSize += SHA384_DIGEST_SIZE;
            Count+=1;
        }

        if((PcrBanks & 8) == 8)
        {
            //sha512
            HashSize += SHA512_DIGEST_SIZE;
            Count+=1;
        }

        if((PcrBanks & 0x10) == 0x10)
        {
            //Special case //SM3 use hash sequence
            HashSize += SM3_256_DIGEST_SIZE;
            Count+=1;
        }

        NewEventHdr->Digests.count = Count;
    }


    EventData.pcrIndex = NewEventHdr->PCRIndex;
    EventData.eventType = NewEventHdr->EventType;
    EventData.digests.count = NewEventHdr->Digests.count;
    
    RequiredSpace = sizeof(TCG_PCClient_PCR_Event2_Hdr) - sizeof(TPML_DIGEST_VALUES)\
                    + sizeof(UINT32) + NewEventHdr->EventSize;

    RequiredSpace += (HashSize + NewEventHdr->Digests.count * sizeof(UINT16));

    TreeEventLogLocation = (UINTN)TcgLog + sizeof(TCG_LOG_HOB);
    if((RequiredSpace + TcgLog->LastEntry) > \
                 (TreeEventLogLocation  + PEI_MAX_LOG_AREA_SIZE)){
        TcgLog->IEventLogTruncated = TRUE;
    }
    
    if(NewEventHdr->EventType == EV_NO_ACTION)
    {
        i=0;
        if((PcrBanks & 1) == 1)
        {
            //sha1
            SetMem((UINT8 *)&NewEventHdr->Digests.digests[i].digest.sha1, SHA1_DIGEST_SIZE, 0);
            NewEventHdr->Digests.digests[i].hashAlg = TPM2_ALG_SHA1;
            i+=1;
        }

        if((PcrBanks & 2) == 2)
        {
            //sha256
            SetMem((UINT8 *)&NewEventHdr->Digests.digests[i].digest.sha256, SHA256_DIGEST_SIZE, 0);
            NewEventHdr->Digests.digests[i].hashAlg = TPM2_ALG_SHA256;
            i+=1;
        }

        if((PcrBanks & 4) == 4)
        {
            //sha384
            SetMem((UINT8 *)&NewEventHdr->Digests.digests[i].digest.sha384, SHA384_DIGEST_SIZE, 0);
            NewEventHdr->Digests.digests[i].hashAlg = TPM2_ALG_SHA384;
            i+=1;
        }

        if((PcrBanks & 8) == 8)
        {
            //sha512
            SetMem((UINT8 *)&NewEventHdr->Digests.digests[i].digest.sha512, SHA512_DIGEST_SIZE, 0);
            NewEventHdr->Digests.digests[i].hashAlg = TPM2_ALG_SHA512;
            i+=1;
        }

        if((PcrBanks & 0x10) == 0x10)
        {
            //SM3
            SetMem((UINT8 *)&NewEventHdr->Digests.digests[i].digest.sm3_256, SM3_256_DIGEST_SIZE, 0);
            NewEventHdr->Digests.digests[i].hashAlg = TPM2_ALG_SM3_256;
            i+=1;
        }
        goto EvNoAction;
    }

    Status = PeiTrEEExtend(TrEEPpi,
                           NewEventHdr->PCRIndex,
                           &NewEventHdr->Digests);

    if(EFI_ERROR(Status))return Status;

EvNoAction:
    
    if(TcgLog->IEventLogTruncated)return EFI_VOLUME_FULL;
    
    CopyMem((VOID*)(UINTN)TcgLog->LastEntry, NewEventHdr,
            sizeof(TCG_PCRINDEX) +  sizeof(TCG_EVENTTYPE));

    TempSize =  sizeof(TCG_PCRINDEX) +  sizeof(TCG_EVENTTYPE);

    if((ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2) ||
            (TcgLog->TableSize == 0))  //log event record
    {

        CopyMem(
            (VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
            (UINT8 *)&NewEventHdr->Digests.digests[0].digest.sha1,
            SHA1_DIGEST_SIZE);

        TempSize+= (SHA1_DIGEST_SIZE);
        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_1_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
    }
    else if(ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2)
    {

        CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + TempSize), &EventData.digests.count, sizeof(UINT32));
        TempSize+= sizeof(UINT32);

        i = 0;

        if(PcrBanks & 1)
        {
            //sha1
            CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
                    (UINT8 *)&NewEventHdr->Digests.digests[i],
                    (SHA1_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

            TempSize+= ((SHA1_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
            i+=1;
            TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_1_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
        }

        if(PcrBanks & 2)
        {
            //sha256
            CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
                    (UINT8 *)&NewEventHdr->Digests.digests[i],
                    (SHA256_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

            TempSize+= ((SHA256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
            i+=1;
            TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_256_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
        }

        if(PcrBanks & 4)
        {
            //sha256
            CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
                    (UINT8 *)&NewEventHdr->Digests.digests[i],
                    (SHA384_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

            TempSize+= ((SHA384_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
            i+=1;
            TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_384_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
        }

        if(PcrBanks & 8)
        {
            //sha512
            CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
                    (UINT8 *)&NewEventHdr->Digests.digests[i],
                    (SHA512_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

            TempSize+= ((SHA512_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
            i+=1;
            TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_512_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
        }


        if(PcrBanks & 0x10)
        {
            CopyMem((VOID*)(UINTN)(TcgLog->LastEntry  + TempSize) ,
                    (UINT8 *)&NewEventHdr->Digests.digests[i],
                    (SM3_256_DIGEST_SIZE + sizeof(TPM2_ALG_ID)));

            TempSize+= ((SM3_256_DIGEST_SIZE) + sizeof(TPM2_ALG_ID));
            i+=1;
            TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_SHA_SM3_ACTIVE | EFI_SOFTWARE_PEI_MODULE);
        }
    }

    DEBUG((DEBUG_INFO, "TempSize = %x \n", TempSize));
    DEBUG((DEBUG_INFO, "NewEventHdr->EventSize = %x \n", NewEventHdr->EventSize));
    CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + TempSize) ,
            &NewEventHdr->EventSize,
            sizeof(UINT32));
    TempSize+=sizeof(UINT32);

    DEBUG((DEBUG_INFO, "TempSize = %x \n", TempSize));
    CopyMem((VOID*)(UINTN)(TcgLog->LastEntry + TempSize) ,
            NewEventData,
            NewEventHdr->EventSize);

    DEBUG((DEBUG_INFO, "NewEventHdr->EventType = %x \n", NewEventHdr->EventType));

    TcgLog->LastEventPtr = TcgLog->LastEntry;
    TcgLog->LastEntry = TcgLog->LastEventPtr + ((EFI_PHYSICAL_ADDRESS)(UINTN)(NewEventHdr->EventSize \
                        + TempSize));
    
    //TcgLog->LastEventPtr = TcgLog->LastEntry;

    TcgLog->TableSize += (TempSize + NewEventHdr->EventSize);

    ++TcgLog->EventNum;


    return EFI_SUCCESS;
}


EFI_STATUS
AmiPeiHashInitInterface (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT32                   Alg,
    OUT VOID                     *Context,
    IN OUT UINTN                 *ContextSize
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    if(TrEEPpi == NULL)return EFI_INVALID_PARAMETER;
    if( NULL == ContextSize || NULL == Context ) return EFI_INVALID_PARAMETER;
    if( 0 == *ContextSize ) return EFI_INVALID_PARAMETER;

    //can only do one algorithm at a time
    if(Alg & 1)
    {
        if( sizeof(SHA1_CTX) > *ContextSize )
        {
            *ContextSize = sizeof(SHA1_CTX);
            Status = EFI_BUFFER_TOO_SMALL;
        }
        SHA1Init( (SHA1_CTX*)Context );
    }
    else if(Alg & 2)
    {
        if( sizeof(SHA2_CTX) > *ContextSize )
        {
            *ContextSize = sizeof(SHA2_CTX);
            Status = EFI_BUFFER_TOO_SMALL;
        }
        sha256_init( (SHA2_CTX*)Context );
    }
    else if(Alg & 4)
    {
        if( sizeof(SHA384_CTX) > *ContextSize )
        {
            *ContextSize = sizeof(SHA384_CTX);
            Status = EFI_BUFFER_TOO_SMALL;
        }
        sha384_init( (SHA384_CTX*)Context);
    }
    else if(Alg & 8)
    {
        if( sizeof(SHA512_CTX) > *ContextSize )
        {
            *ContextSize = sizeof(SHA512_CTX);
            Status = EFI_BUFFER_TOO_SMALL;
        }
        sha512_init( (SHA512_CTX*)Context);
    }
    else if(Alg & 0x10)
    {
        if( sizeof(SM3_CTX) > *ContextSize )
        {
            *ContextSize = sizeof(SM3_CTX);
            Status = EFI_BUFFER_TOO_SMALL;
        }
        Status = sm3_init ((SM3_CTX *) Context);
    }

    return Status;
}



EFI_STATUS
AmiPeiHashUpdateInterface (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *Data,
    IN  UINTN                     Datasize,
    IN  UINT32                   Alg,
    IN  OUT VOID                 *Context
)
{

    if(TrEEPpi == NULL)return EFI_INVALID_PARAMETER;
    if(Data == NULL)return EFI_INVALID_PARAMETER;
    if(Context == NULL) return EFI_INVALID_PARAMETER;

    //can only do one algorithm at a time
    if(Alg & 1)
    {
        SHA1Update( (SHA1_CTX *)Context, Data, (u32) Datasize );
    }
    else if(Alg & 2)
    {
        sha256_process((SHA2_CTX *)Context, Data, (u32)Datasize );
    }
    else if(Alg & 4)
    {
        sha512_process((SHA384_CTX *)Context, Data, (unsigned long)Datasize);
    }
    else if(Alg & 8)
    {
        sha512_process((SHA512_CTX *)Context, Data, (unsigned long)Datasize);
    }
    else if(Alg & 0x10)
    {
        
        sm3_update((SM3_CTX *)Context, Data, Datasize);
    }

    return EFI_SUCCESS;
}


EFI_STATUS
AmiPeiHashCompleteInterface (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  VOID                     *Context,
    IN  UINT32                   Alg,
    IN  OUT  UINT8               *resultsbuffer,
    IN  OUT  UINTN               *resultsbuffersize
)
{
    if(resultsbuffer == NULL) return EFI_INVALID_PARAMETER;
    if(resultsbuffersize == NULL) return EFI_INVALID_PARAMETER;
    if(*resultsbuffersize == 0) return EFI_INVALID_PARAMETER;
    if(Context == NULL) return EFI_INVALID_PARAMETER;

    if(Alg & 1)
    {
        if(*resultsbuffersize < 20)
        {
            *resultsbuffersize = 20;
            return EFI_BUFFER_TOO_SMALL;
        }
        SHA1Final( resultsbuffer, (SHA1_CTX *)Context );
        *resultsbuffersize = 20;
    }
    else if(Alg & 2)
    {
        if(*resultsbuffersize < 32)
        {
            *resultsbuffersize = 32;
            return EFI_BUFFER_TOO_SMALL;
        }
        sha256_done( (SHA2_CTX *)Context, (unsigned char *)resultsbuffer );
        *resultsbuffersize = 32;
    }
    else if(Alg & 4)
    {
        if(*resultsbuffersize < 48)
        {
            *resultsbuffersize = 48;
            return EFI_BUFFER_TOO_SMALL;
        }
        sha384_done((SHA384_CTX *)Context, (unsigned char *)resultsbuffer);
        *resultsbuffersize = 48;
    }
    else if(Alg & 8)
    {
        if(*resultsbuffersize < 64)
        {
            *resultsbuffersize = 64;
            return EFI_BUFFER_TOO_SMALL;
        }
        sha512_done((SHA512_CTX *)Context, (unsigned char *)resultsbuffer);
        *resultsbuffersize = 64;
    }
    else if(Alg & 0x10)
    {
        if(*resultsbuffersize < 32)
        {
            *resultsbuffersize = 32;
            return EFI_BUFFER_TOO_SMALL;
        }
        
        sm3_final((unsigned char *)resultsbuffer,  (SM3_CTX *)Context );
        *resultsbuffersize = 32;
    }

    return EFI_SUCCESS;
}


EFI_STATUS
AmiPeiHashAllInterface (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  TPML_DIGEST_VALUES       *HashResults,
    IN  UINT32                   *AlgBitMap
)
{
    UINT32   HashSize = 0;
    TPML_DIGEST_VALUES  HashArray;
    EFI_STATUS Status;
    
    Status = GetAllDigestValues(*AlgBitMap, &HashArray, DataToHash, DataSize, &HashSize);
    if(!EFI_ERROR(Status) && HashResults != NULL){
        DigestListArrayToBuffer(&HashArray, HashResults);
    }
    return Status;
}

EFI_STATUS
AmiPeiHashAllInterfaceInternal (
    IN  AMI_TREE_PPI             *TrEEPpi,
    IN  UINT8                    *DataToHash,
    IN  UINTN                    DataSize,
    IN  TPML_DIGEST_VALUES       *HashResults,
    IN  UINT32                   *AlgBitMap
)
{
    UINT32   HashSize = 0;
    EFI_STATUS Status;
    
    Status = GetAllDigestValues(*AlgBitMap, HashResults, DataToHash, DataSize, &HashSize);
    return Status;
}


EFI_STATUS
EFIAPI Tpm20GetEventLog(
    OUT TCG_LOG_HOB     **EventLog )
{
    EFI_STATUS Status;
    VOID       *HobStart;
    CONST EFI_PEI_SERVICES      **PeiServices;
    PeiServices = GetPeiServicesTablePointer ();

    Status = (*PeiServices)->GetHobList( PeiServices, &HobStart );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    return TcgGetNextGuidHob( &HobStart, &gEfiTcgTreeLogHobGuid, (void **)EventLog, NULL );
}



EFI_STATUS
TrEEHashLogExtentEvent (
    IN  AMI_TREE_PPI          *This,
    IN  UINT64                Flags,
    IN  EFI_PHYSICAL_ADDRESS  DataToHash,
    IN  UINT64                DataToHashLen,
    IN  AMI_TREE_EVENT            *TreeEvent
)
{
    EFI_STATUS            Status     = EFI_SUCCESS;
    TCG_PCR_EVENT2_HDR    TcgEvent;
    EFI_PEI_SERVICES      **PeiServices;

    PeiServices = (EFI_PEI_SERVICES  **)GetPeiServicesTablePointer ();

    if((This == NULL ) || (DataToHash == 0) || (TreeEvent == NULL))
    {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }
    else if(TreeEvent->Size < (TreeEvent->Header.HeaderSize + sizeof(UINT32))\
            || (TreeEvent->Header.PcrIndex > 23))
    {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    SetMem(&TcgEvent, sizeof(TCG_PCR_EVENT2_HDR), 0);

    TcgEvent.PCRIndex= TreeEvent->Header.PcrIndex;
    TcgEvent.EventType = TreeEvent->Header.EventType;
    TcgEvent.EventSize = TreeEvent->Size - sizeof(AMI_TREE_EVENT_HEADER) \
                         -sizeof(UINT32);

    Status = TrEEPeiHashLogExtentEventInternal((CONST EFI_PEI_SERVICES   **)PeiServices,
             This,
             (UINT8 *)(UINTN)DataToHash,
             Flags,
             (UINTN)  DataToHashLen,
             &TcgEvent,
             (UINT8 *)&TreeEvent->Event);
Exit:
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InternalPeiBuildHobGuid
//
// Description: Internal abstracted function to create a Hob
//
// Input:       IN  EFI_PEI_SERVICES  **PeiServices,
//              IN  EFI_GUID          *Guid,
//              IN  UINTN             DataLength,
//              OUT VOID              **Hob
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InternalPeiBuildHobGuid(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID         *Guid,
    IN UINTN            DataLength,
    OUT VOID            **Hob )
{
    EFI_STATUS Status;

    Status = (*PeiServices)->CreateHob(
                 (CONST EFI_PEI_SERVICES **)PeiServices,
                 EFI_HOB_TYPE_GUID_EXTENSION,
                 (UINT16) ( sizeof (EFI_HOB_GUID_TYPE) + DataLength ),
                 Hob
             );

    if ( EFI_ERROR( Status ))
    {
        DEBUG((DEBUG_INFO, "Failed to create TCG/TPM Hob Status = %r \n", Status));
        return Status;
    }

    DEBUG((DEBUG_INFO, "Hob created \n"));
    ((EFI_HOB_GUID_TYPE*)(*Hob))->Name = *Guid;

    return EFI_SUCCESS;
}



EFI_STATUS
TreeGetEventLog (
    IN  AMI_TREE_PPI           *This,
    IN  AMI_TREE_EVENTLOGTYPE      EventLogFormat,
    OUT EFI_PHYSICAL_ADDRESS  *EventLogLocation,
    OUT EFI_PHYSICAL_ADDRESS  *EventLogLastEntry,
    OUT BOOLEAN               *EventLogTruncated
)
{
    EFI_STATUS          Status = EFI_SUCCESS;
    TCG_LOG_HOB         *TcgLog = NULL;
    UINTN               TreeEventLogLocation = 0;

    Status = Tpm20GetEventLog(&TcgLog);
    if (NULL == TcgLog)
    {
        return EFI_UNSUPPORTED;
    }

    if(EventLogFormat != AMI_TREE_EVENT_LOG_FORMAT_TCG_1_2)
    {
        Status = EFI_INVALID_PARAMETER;
    }

    TreeEventLogLocation = (UINTN)TcgLog + sizeof(TCG_LOG_HOB);
    *EventLogLocation  = (EFI_PHYSICAL_ADDRESS)TreeEventLogLocation;
    *EventLogLastEntry = TcgLog->LastEventPtr;
    *EventLogTruncated = TcgLog->IEventLogTruncated;

    return Status;
}



static AMI_TREE_PPI   CrbmTpmPrivate =
{
    TreeGetCapability,
    TreeGetEventLog,
    TrEEHashLogExtentEvent,
    TrEECRBPeiTransmit
};

static EFI_PEI_PPI_DESCRIPTOR mCrbPpiList[] =
{
    {
    EFI_PEI_PPI_DESCRIPTOR_PPI
    | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmiTreePpiGuid,
    &CrbmTpmPrivate
    }
};


static AMI_INTERNAL_HLXE_PPI  InternalHashLogExtendEx =
{
    TrEEPeiHashLogExtentEventInternal
};

static AMI_PEI_HASH_INTERFACE_PPI  AmiTpmHashInterface =
{
    AmiPeiHashAllInterface,
    AmiPeiHashInitInterface,
    AmiPeiHashUpdateInterface,
    AmiPeiHashCompleteInterface
};

static EFI_PEI_PPI_DESCRIPTOR mAmiExtendLogPpiList[]=
{
    {
    EFI_PEI_PPI_DESCRIPTOR_PPI
    | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmiHashLogExtendExGuid,
    &InternalHashLogExtendEx
    }
};

static EFI_PEI_PPI_DESCRIPTOR mAmiHashInterfacePpiList[]=
{
    {
    EFI_PEI_PPI_DESCRIPTOR_PPI
    | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &AmiPeiHashInterfaceProtocolGuid,
    &AmiTpmHashInterface
    }
};


static AMI_TREE_PPI   TisTpmPrivate =
{
    TreeGetCapability,
    TreeGetEventLog,
    TrEEHashLogExtentEvent,
    TrEETisPeiTransmit
};

static EFI_PEI_PPI_DESCRIPTOR mTisPpiList[] =
{
    {
    EFI_PEI_PPI_DESCRIPTOR_PPI
    | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmiTreePpiGuid,
    &TisTpmPrivate
    }
};



EFI_STATUS
EFIAPI
Tpm2DisabledStartUpCmd(IN CONST EFI_PEI_SERVICES    **PeiServices,
                       IN UINT8 IntefaceType)
{
    AMI_TREE_PPI        *TreePpi=NULL;
    EFI_STATUS    Status = EFI_SUCCESS;
    TPM2_Common_RespHdr StartupReponse;
    TPM2_Startup_Cmd    StartupCmd;
    EFI_BOOT_MODE       BootMode;
    UINT32              ReturnSize = 0;
    
    DEBUG ((DEBUG_INFO, " Tpm2DisabledStartUpCmd Entry \n"));
    
    Status = (*PeiServices)->GetBootMode(PeiServices,&BootMode);
    if(EFI_ERROR(Status))return Status;
            
    StartupCmd.tag = SwapBytes16(TPM_ST_NO_SESSIONS);
    StartupCmd.CommandSize = SwapBytes32((sizeof(TPM2_Startup_Cmd)));
    StartupCmd.CommandCode = SwapBytes32(TPM_CC_Startup);
    
    StartupCmd.StartupType = SwapBytes16(TPM_SU_CLEAR);
    
    ReturnSize = (UINT32)sizeof(StartupReponse);
    SetMem((UINT8 *)&StartupReponse,(UINTN)sizeof(StartupReponse), 0);
    
    if(IntefaceType == 0){
        
        Status = TrEETisPeiTransmit( TreePpi, 
                            sizeof(TPM2_Startup_Cmd),
                            (UINT8 *)&StartupCmd,
                            ReturnSize,
                            (UINT8*)&StartupReponse);
                            
        DEBUG ((DEBUG_INFO, " Tpm2DisabledStartUpCmd TrEETisPeiTransmit Status = %r \n", Status ));
        
        if(EFI_ERROR(Status)) return Status;
    }else if(IntefaceType == 1){
        
        Status = TrEECRBPeiTransmit( TreePpi, 
                                    sizeof(TPM2_Startup_Cmd),
                                    (UINT8 *)&StartupCmd,
                                    ReturnSize,
                                    (UINT8*)&StartupReponse);
                                    
        DEBUG ((DEBUG_INFO, " Tpm2DisabledStartUpCmd TrEECRBPeiTransmit Status = %r \n", Status ));
        if(EFI_ERROR(Status)) return Status;
    }
    
    if((StartupReponse.ResponseCode) != TPM_RC_SUCCESS 
            && ((SwapBytes32(StartupReponse.ResponseCode))!= TPM_RC_INITIALIZE)
            &&  ((SwapBytes32(StartupReponse.ResponseCode))!= TPM_BAD_ORDINAL))  //TPM_BAD_ORDINAL for TPM 1.2 Device
    {
        DEBUG((DEBUG_INFO, "StartupReponse.ResponseCode = %x \n", SwapBytes32(StartupReponse.ResponseCode)));
        DEBUG((DEBUG_INFO, "StartupReponse.Status = %r \n", Status));
        TpmPeiReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_2_0_STARTUP_ERROR | EFI_SOFTWARE_PEI_MODULE);
        if(((SwapBytes32(StartupReponse.ResponseCode))!= TPM_RC_LOCALITY) ||
                (SwapBytes32(StartupReponse.ResponseCode)!= TPM_RC_LOCALITY)){ //PFP 1.2 2.3.2.1
            (*(PeiServices))->ResetSystem(PeiServices);
        }
        Status = EFI_DEVICE_ERROR;
        return Status;
    }
    
    DEBUG ((DEBUG_INFO, " Tpm2DisabledStartUpCmd Return Status = %r \n", Status ));
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Tpm20PeiSelfTest
//
// Description: Send TPM 20 SelfTest Command
//
//
// Input:       IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Tpm2DisabledSelfTest(IN CONST EFI_PEI_SERVICES    **PeiServices,
                                IN UINT8 IntefaceType)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    TPM2_SelfTest           SelfTestCmd;
    TPM2_Common_RespHdr     SelfTestReponse;
    UINT32                  ReturnSize = 0;
    EFI_HOB_GUID_TYPE       *DeviceHob;
    Tpm20DeviceHob          *TrEEDeviceHob;
    AMI_TREE_PPI            *TreePpi=NULL;
    
   
    SelfTestCmd.tag = SwapBytes16(TPM_ST_NO_SESSIONS);
    SelfTestCmd.CommandSize = SwapBytes32((sizeof(TPM2_SelfTest)));
    SelfTestCmd.CommandCode = SwapBytes32(TPM_CC_SelfTest);
  
    SelfTestCmd.SelfTestType = 0;
    
    ReturnSize = (UINT32)sizeof(SelfTestReponse);

    SetMem((UINT8 *)&SelfTestReponse,(UINTN)sizeof(SelfTestReponse), 0);

    if(IntefaceType == 0){
        Status = TrEETisPeiTransmit( TreePpi, 
                                     sizeof(SelfTestCmd),
                                     (UINT8 *)&SelfTestCmd,
                                     ReturnSize,
                                     (UINT8*)&SelfTestReponse);

        
        DEBUG ((DEBUG_INFO, "TrEETisPeiTransmit :: Status = %r\n", Status));   
    }else if(IntefaceType == 1){
        Status = TrEECRBPeiTransmit(TreePpi, 
                                    sizeof(SelfTestCmd),
                                    (UINT8 *)&SelfTestCmd,
                                    ReturnSize,
                                    (UINT8*)&SelfTestReponse);
                      
        DEBUG ((DEBUG_INFO, "TrEECRBPeiTransmit :: Status = %r\n", Status));                            
    }

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    // Check the device return Tag, if it is belong the TPM20 RSP_TAG
    if( SelfTestReponse.tag != SwapBytes16(TPM_ST_NO_SESSIONS) )
    {
        Status = EFI_DEVICE_ERROR;
        return Status;
    }
    
    Status = InternalPeiBuildHobGuid((EFI_PEI_SERVICES **)PeiServices, &gTpm20HobGuid,
                                        (sizeof(Tpm20DeviceHob)),  (void **)&DeviceHob);
    
    DEBUG((DEBUG_INFO, "SelfTestReponse.Tag = %x \n", SwapBytes16(SelfTestReponse.tag)));
    DEBUG((DEBUG_INFO, "SelfTestReponse.ResponseCode = %x \n", SwapBytes32(SelfTestReponse.ResponseCode)));
    DEBUG((DEBUG_INFO, "SelfTestReponse.Status = %r \n", Status));

    if(Status != EFI_DEVICE_ERROR && !EFI_ERROR(Status))
    {
        TrEEDeviceHob = (Tpm20DeviceHob*)(DeviceHob + 1);
        TrEEDeviceHob->Tpm20DeviceState = 1;
        TrEEDeviceHob->InterfaceType = IntefaceType;
    }

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  InternalTpmPei2HierarchyControl
//
// Description: enables and disables use of a hierarchy
//
//
// Input:       AuthSize
//
// Output:      UINT8* pOutBuf
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
InternalTpmPei2HierarchyControl (
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN       UINT8              IntefaceType,
    IN       TPMI_RH_HIERARCHY  AuthHandle,
    IN       TPMS_AUTH_COMMAND *AuthSession,
    IN       TPMI_RH_HIERARCHY  Hierarchy,
    IN       TPMI_YES_NO        State
)
{
    EFI_STATUS                       Status;
    AMI_TREE_PPI                    *TreePpi = NULL;
    AMI_TPM2_HIERARCHY_CONTROL_COMMAND   Cmd;
    AMI_TPM2_HIERARCHY_CONTROL_RESPONSE  Res;
    UINT32                           CmdSize;
    UINT32                           RespSize;
    UINT8                            *Buffer;
    UINT32                           SessionInfoSize;
    UINT8                            *ResultBuf;
    UINT32                           ResultBufSize;

    //
    // Construct command
    //
    Cmd.Header.tag          = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.Header.paramSize    = SwapBytes32(sizeof(Cmd));
    Cmd.Header.commandCode  = SwapBytes32(TPM_CC_HierarchyControl);
    Cmd.AuthHandle          = SwapBytes32(AuthHandle);

    //
    // Add in Auth session
    //
    Buffer = (UINT8 *)&Cmd.AuthSession;

    // sessionInfoSize
    SessionInfoSize = CopyAuthSessionCommand (AuthSession, Buffer);
    Buffer += SessionInfoSize;
    Cmd.AuthorizationSize = SwapBytes32(SessionInfoSize);

    WriteUnaligned32 ((UINT32 *)Buffer, SwapBytes32(Hierarchy));
    Buffer += sizeof(UINT32);

    *(UINT8 *)Buffer = State;
    Buffer += sizeof(UINT8);

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.Header.paramSize = SwapBytes32(CmdSize);

    ResultBuf     = (UINT8 *) &Res;
    ResultBufSize = sizeof(Res);

    if(IntefaceType == 0){
        Status = TrEETisPeiTransmit( TreePpi, 
                                     CmdSize,
                                     (UINT8 *)&Cmd,
                                     ResultBufSize,
                                     ResultBuf);
        
        DEBUG ((DEBUG_INFO, "TrEETisPeiTransmit :: Status = %r\n", Status));   
    }else if(IntefaceType == 1){
        Status = TrEECRBPeiTransmit(TreePpi, 
                                    CmdSize,
                                    (UINT8 *)&Cmd,
                                    ResultBufSize,
                                    ResultBuf);
                      
        DEBUG ((DEBUG_INFO, "TrEECRBPeiTransmit :: Status = %r\n", Status));                            
    }else{
        Status = EFI_INVALID_PARAMETER;
    }
    
    if(EFI_ERROR(Status))return Status;

    if (ResultBufSize > sizeof(Res))
    {
        DEBUG ((EFI_D_ERROR, "HierarchyControl: Failed ExecuteCommand: Buffer Too Small\r\n"));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Validate response headers
    //
    RespSize = SwapBytes32(Res.Header.paramSize);
    if (RespSize > sizeof(Res))
    {
        DEBUG ((EFI_D_ERROR, "HierarchyControl: Response size too large! %d\r\n", RespSize));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Fail if command failed
    //
    if (SwapBytes32(Res.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG((EFI_D_ERROR,"HierarchyControl: Response Code error! 0x%08x\r\n", SwapBytes32(Res.Header.responseCode)));
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}
    
EFI_STATUS
EFIAPI
ExtendPCRSTpm2(IN CONST EFI_PEI_SERVICES    **ps,
               IN UINT32 PCRIndex, 
               IN TPML_DIGEST_VALUES  *Digest,
               IN UINT8 IntefaceType)
{
    AMI_TREE_PPI        *TreePpi = NULL;
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;
    UINT32                DigestSize=0;
    UINT32                SessionInfoSize;
    EFI_STATUS            Status = EFI_SUCCESS;
    UINTN                 i=0;

    DEBUG ((DEBUG_INFO, " ExtendPCRSTpm2 Entry \n")); 
    
    Cmd.Tag          = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.CommandCode  = SwapBytes32(TPM_CC_PCR_Extend);
    Cmd.PcrHandle    = SwapBytes32(PCRIndex);

    Buffer = (UINT8 *)&Cmd.AuthSessionPcr;

    SessionInfoSize = CopyAuthSessionCommand (NULL, Buffer);
    Buffer += SessionInfoSize;
    Cmd.AuthorizationSize = SwapBytes32(SessionInfoSize);

    DEBUG ((DEBUG_INFO, " ExtendPCRSTpm2 Cmd = %x \n", &Cmd));

    //Digest count
    *(UINT32 *)Buffer = SwapBytes32(Digest->count);
    Buffer += sizeof(UINT32);
   
    DEBUG ((DEBUG_INFO, " Digest->count = %x \n", Digest->count));
    
    for(i=0; i<Digest->count; i++)
    {
        *(UINT16 *)Buffer = SwapBytes16(Digest->digests[i].hashAlg);
        Buffer += sizeof(UINT16);
        switch(Digest->digests[i].hashAlg)
        {
            case TPM2_ALG_SHA1:
                DigestSize = SHA1_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA256:
                DigestSize = SHA256_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA384:
                DigestSize = SHA384_DIGEST_SIZE;
                break;
            case TPM2_ALG_SHA512:
                DigestSize = SHA512_DIGEST_SIZE;
                break;
            case TPM2_ALG_SM3_256:
                DigestSize = SM3_256_DIGEST_SIZE;
                break;
            default:
                break;
        }

        Tpm20TcgCommonCopyMem(NULL, Buffer, &Digest->digests[i].digest, DigestSize);
        Buffer += DigestSize;
    }
    
    CmdSize = (UINT32)(Buffer - (UINTN)&Cmd);
    Cmd.CommandSize = SwapBytes32(CmdSize);

    ResultBuf     = (UINT8 *) &Res;
    ResultBufSize = sizeof(Res);
    
    DEBUG ((DEBUG_INFO, "ExtendPCRSTpm2 CmdSize = %x \n", CmdSize));
    
    if(IntefaceType == 0){
        Status = TrEETisPeiTransmit( TreePpi, 
                                     CmdSize,
                                     (UINT8 *)&Cmd,
                                     ResultBufSize,
                                     (UINT8*)&ResultBuf);
        
        DEBUG ((DEBUG_INFO, "TrEETisPeiTransmit :: Status = %r\n", Status));   
    }else if(IntefaceType == 1){
        Status = TrEECRBPeiTransmit(TreePpi, 
                                    CmdSize,
                                    (UINT8 *)&Cmd,
                                    ResultBufSize,
                                    (UINT8*)&ResultBuf);
                      
        DEBUG ((DEBUG_INFO, "TrEECRBPeiTransmit :: Status = %r\n", Status));                            
    }
    
    return Status;

}


EFI_STATUS
EFIAPI
ExtendSeparatorEvent (
    IN CONST EFI_PEI_SERVICES    **PeiServices,
    IN UINT32  PCRIndex,
    IN UINT8 IntefaceType
)
{
    UINT32              DataToHash = 0;
    UINTN               DataSize   = sizeof(UINT32);
    TPML_DIGEST_VALUES  Digests;
    EFI_STATUS          Status;
    TCG_PLATFORM_SETUP_INTERFACE *TcgPeiPolicy;
    UINT32              PcrBanks;
    TCG_CONFIGURATION   ConfigFlags;
    UINT32              Count=0;
    
    DEBUG ((DEBUG_INFO, "PeiServices = %x\n", PeiServices));                            
    DEBUG ((DEBUG_INFO, "PCRIndex = %x\n", PCRIndex));                            
    DEBUG ((DEBUG_INFO, "IntefaceType = %x\n", IntefaceType));                            
    
    Status = (*PeiServices)->LocatePpi(PeiServices,
                                         &gTcgPeiPolicyGuid,
                                         0, NULL,
                                         (void **) &TcgPeiPolicy);
        
    if(EFI_ERROR(Status))return Status;
    
    Status = TcgPeiPolicy->getTcgPeiPolicy((EFI_PEI_SERVICES **)PeiServices, &ConfigFlags);
    PcrBanks = ConfigFlags.PcrBanks;

    if(((PcrBanks & 1) == 1))
    {
        //sha1
        Tpm20SHA1HashAll(NULL, &DataToHash, DataSize, (UINT8 *)&Digests.digests[Count].digest.sha1);
        Digests.digests[Count].hashAlg = TPM2_ALG_SHA1;
        Count+=1;
    }

    if(((PcrBanks & 2) == 2))
    {
        //sha256
        SHA2HashAll(NULL, &DataToHash, DataSize, (UINT8 *)&Digests.digests[Count].digest.sha256);
        Digests.digests[Count].hashAlg = TPM2_ALG_SHA256;
        Count+=1;
    }

    if(((PcrBanks & 4) == 4))
    {
        //sha384
        SHA384HashAll(&DataToHash, DataSize, (UINT8 *)&Digests.digests[Count].digest.sha384);
        Digests.digests[Count].hashAlg = TPM2_ALG_SHA384;
        Count+=1;
    }

    if(((PcrBanks & 8) == 8))
    {
        //sha512
        SHA512HashAll(&DataToHash, DataSize, (UINT8 *)&Digests.digests[Count].digest.sha512);
        Digests.digests[Count].hashAlg = TPM2_ALG_SHA512;
        Count+=1;
    }
          
    Digests.count = Count;

    Status = ExtendPCRSTpm2(PeiServices, PCRIndex, &Digests, IntefaceType);    
    return Status;
}


EFI_STATUS
EFIAPI
ProcessTpmSupportDisabled (IN CONST EFI_PEI_SERVICES    **PeiServices){
    
    static UINT8 InterfaceType=0;
    EFI_STATUS Status = EFI_SUCCESS;
    static UINT32 i=0;
    
    
    DEBUG ((DEBUG_INFO, " ProcessTpmSupportDisabled Entry \n"));
    
    InterfaceType = GetCurrentInterfaceType();
    
    //0 = Tis Interface
    //1 = CRB Interface
    if(InterfaceType == 0 ){
        Status = Tpm20IsTpmPresent((TPM_1_2_REGISTERS_PTR)( UINTN ) PORT_TPM_IOMEMBASE );
        if(EFI_ERROR(Status)) return Status;
    }
    
    if(InterfaceType == 1){
       if(CrbSupported() != 0x02 && CrbSupported() != 0x01){
           return EFI_UNSUPPORTED;
       }
    }
    
    Status = Tpm2DisabledStartUpCmd(PeiServices, InterfaceType);
    if(EFI_ERROR(Status)) return Status;
    
    Status = Tpm2DisabledSelfTest(PeiServices, InterfaceType);
    if(EFI_ERROR(Status)) return Status;
    Status = InternalTpmPei2HierarchyControl(PeiServices, InterfaceType, TPM_RH_PLATFORM,\
                                                    NULL, TPM_RH_ENDORSEMENT,  0);
    
    if(EFI_ERROR(Status)){
       DEBUG ((DEBUG_INFO, "Tcg2 Support off Disable EH Status =%r \n", Status));
    }
    Status = InternalTpmPei2HierarchyControl(PeiServices, InterfaceType, TPM_RH_PLATFORM,\
                                                   NULL, TPM_RH_OWNER,  0);
    if(EFI_ERROR(Status)){
       DEBUG ((DEBUG_INFO, "Tcg2 Support off Disable SH Status =%r \n", Status));
    }
    
    for(i=0; i<8; i++){
        Status = ExtendSeparatorEvent(PeiServices, i, InterfaceType);
        DEBUG ((DEBUG_INFO, "ExtendSeparatorEvent :: Status = %r\n", Status));                            
        if(EFI_ERROR(Status))break;
    }
    
#if defined(Tpm20ResetPhPolicy_SUPPORT) && Tpm20ResetPhPolicy_SUPPORT == 1
    Status = InternalTpmPei2HierarchyControl(PeiServices, InterfaceType, TPM_RH_PLATFORM,\
                                                   NULL, TPM_RH_PLATFORM,  0);
    if(EFI_ERROR(Status)){
       DEBUG ((DEBUG_INFO, "Tcg2 Support off Disable PH Status =%r \n", Status));
    }
#endif
    return Status;    
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TrEEPeiEntry
//
// Description:
//
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TrEEPeiEntry(
    IN EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES    **PeiServices)
{
    EFI_STATUS              Status;
    TCG_CONFIGURATION       ConfigFlags;
    BOOLEAN                 InterfaceSupported = FALSE;
    BOOLEAN                 ErrorCrbInterface=FALSE;
    EFI_PHYSICAL_ADDRESS    TPM_Base = (EFI_PHYSICAL_ADDRESS)PORT_TPM_IOMEMBASE;
    TCG_PLATFORM_SETUP_INTERFACE *TcgPeiPolicy;
    EFI_HOB_GUID_TYPE       *Hob;
    TCG_LOG_HOB             *TcgLog = NULL;


    Status = (*PeiServices)->LocatePpi(
                 PeiServices,
                 &gTcgPeiPolicyGuid,
                 0, NULL,
                 (void **) &TcgPeiPolicy);

    if(EFI_ERROR(Status))return Status;

    Status = TcgPeiPolicy->getTcgPeiPolicy((EFI_PEI_SERVICES **)PeiServices, &ConfigFlags);
    if(EFI_ERROR(Status))return Status;

    if(ConfigFlags.DeviceType == 0) return EFI_SUCCESS;

    if(IsTcmSupportType())return EFI_SUCCESS; 
    
    if(ConfigFlags.TpmSupport == 0){
        Status = ProcessTpmSupportDisabled(PeiServices);
        return Status;
    }


#if (defined(ALLOWINTERFACESELECT) && (ALLOWINTERFACESELECT == 1))
    if(ConfigFlags.InterfaceSel == 0)
    {
        //check if CRB interface is supported
        if(CrbSupported()!=0)
        {
            InterfaceSupported = TRUE;
        }
        else
        {
            ConfigFlags.InterfaceSel = 1;
        }
    }

    if(ConfigFlags.InterfaceSel == 1)
    {
        //check if TIS interface
        Status = Tpm20IsTpmPresent((TPM_1_2_REGISTERS_PTR)( UINTN ) TPM_Base );
        if(!EFI_ERROR(Status))
        {
            if(TisSupported()!=0)
            {
                InterfaceSupported = TRUE;
            }
            else if(CrbSupported()!=0)
            {
                ConfigFlags.InterfaceSel = 0;
                InterfaceSupported = TRUE;
            }
        }
    }
#else
    InterfaceSupported = TRUE;
    ConfigFlags.InterfaceSel = (~GetCurrentInterfaceType() & 1);
#endif

    if(InterfaceSupported)
    {
        //Install TrEE for the Interface Type (TIS or CRB)
        if(ConfigFlags.InterfaceSel == 0)
        {
            if(CrbSupported()==0x02)
            {
                //dTPM 2.0 CRB interface
                if(IsPTP())
                {
                    DEBUG((DEBUG_INFO,  "Calling SelectAndLockInterface\n"));
                    Status = SelectAndLockInterface( PeiServices, (~ConfigFlags.InterfaceSel & 01));
                    if(EFI_ERROR(Status)) ErrorCrbInterface = TRUE;
                }

                //install TrEEPei
                if(ErrorCrbInterface != TRUE)
                {
                    Status = (*PeiServices)->InstallPpi( PeiServices, mCrbPpiList );
                    TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_COMM_INTERFACE_CRB | EFI_SOFTWARE_PEI_MODULE);
                }

            }
            else if(CrbSupported()==0x01)
            {
                Status = (*PeiServices)->InstallPpi( PeiServices, mCrbPpiList );
                TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_COMM_INTERFACE_CRB | EFI_SOFTWARE_PEI_MODULE);
            }

            if(ErrorCrbInterface == TRUE)ConfigFlags.InterfaceSel = 1;
        }

        if(ConfigFlags.InterfaceSel == 1)
        {

            //dTPM 2.0 TIS interface
            Status = Tpm20IsTpmPresent((TPM_1_2_REGISTERS_PTR)(UINTN )TPM_Base );
            if(!EFI_ERROR(Status))
            {
                if(IsPTP())
                {
                    DEBUG((DEBUG_INFO,  "Calling SelectAndLockInterface\n"));
                    Status = SelectAndLockInterface( PeiServices, (~ConfigFlags.InterfaceSel & 01));
                    if(!EFI_ERROR(Status))
                    {
                        Status = (*PeiServices)->InstallPpi( PeiServices, mTisPpiList );
                        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_COMM_INTERFACE_TIS| EFI_SOFTWARE_PEI_MODULE);
                    }
                    else
                    {
                        ErrorCrbInterface = TRUE;
                    }
                }
                else
                {
                    Status = (*PeiServices)->InstallPpi( PeiServices, mTisPpiList );
                    TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_COMM_INTERFACE_TIS| EFI_SOFTWARE_PEI_MODULE);
                }
            }
        }

        if(!ErrorCrbInterface && !EFI_ERROR(Status))
        {

            Status = (*PeiServices)->InstallPpi( PeiServices, mAmiHashInterfacePpiList );
            ASSERT_EFI_ERROR(Status);
            
            if(!EFI_ERROR(Status)){
                   //set callback to install edk2 ppi later
                   DEBUG((DEBUG_INFO, "Setting Notify for EdkiiPpiCallback \n"));
                   Status = (**PeiServices).NotifyPpi (PeiServices, &InstallEDKII_TCG_PPICallback);
                   if(EFI_ERROR(Status)){
                       DEBUG((DEBUG_INFO,  "Installing Edk2Ppi failed \n"));
                   }
             }                         

            Status = InternalPeiBuildHobGuid((EFI_PEI_SERVICES **)PeiServices, &gEfiTcgTreeLogHobGuid,
                                             (sizeof (*TcgLog) + PEI_MAX_LOG_AREA_SIZE),  (void **)& Hob);
            
            if(EFI_ERROR(Status))return Status; 

            DEBUG((DEBUG_INFO, "CrbBuild Hob Status = %r \n", Status));

            TcgLog = (TCG_LOG_HOB*)(Hob + 1);
            (*PeiServices)->SetMem( TcgLog, sizeof (*TcgLog), 0 );
            TcgLog->TableMaxSize = PEI_MAX_LOG_AREA_SIZE;
            TcgLog->TableSize = 0;
            TcgLog->EventNum = 0;
            TcgLog->IEventLogTruncated = FALSE;
            TcgLog->Tcg2SpecVersion = ConfigFlags.Tcg2SpecVersion;
            
            if(ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2){
                TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_PROTOCOL_SPEC_VERSION_1_1 | EFI_SOFTWARE_PEI_MODULE);
            }
            if(ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2){
                TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_PROTOCOL_SPEC_VERSION_1_0 | EFI_SOFTWARE_PEI_MODULE);
            }
            
            TcgLog->ActPcrBanks = ConfigFlags.PcrBanks; // Record the Activate BIOS PCR Bank
            
            DEBUG((DEBUG_INFO, "TcgLog loc = %x \n", TcgLog));

            TcgLog->LastEventPtr = (EFI_PHYSICAL_ADDRESS) ((UINTN)TcgLog + sizeof(TCG_LOG_HOB));
            TcgLog->LastEntry = TcgLog->LastEventPtr;

            Status = (*PeiServices)->InstallPpi( PeiServices, mAmiExtendLogPpiList );
            ASSERT_EFI_ERROR(Status);
            Status = EFI_SUCCESS; //installation failure of Internal PPI is not a fatal Error
            //continue
        }
    }

    return Status;
}
