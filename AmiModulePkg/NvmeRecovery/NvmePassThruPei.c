//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file NvmePassThruPei.c

**/
#include "NvmeRecovery.h"

extern EDKII_IOMMU_PPI *gEdk2IoMmuPpi;

/**
  @internal
	
    Verifies Get Log command's buffer length

    @param Packet        A pointer to the EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET instance
    
    @retval TRUE         Valid buffer length passed
    @retval FALSE        Invalid buffer length passed
    
  @endinternal
**/
BOOLEAN
ValidateGetLogBuffer (
    IN EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET  *Packet
)
{
    UINTN   Numdl;
    UINTN   NumOfBytes = 0;
    
    if(Packet->TransferBuffer == NULL) {
        return FALSE;
    }
    
    // Calculating the number of Dwords
    if((Packet->NvmeCmd->Flags & CDW11_VALID) != CDW11_VALID){
        NumOfBytes = (((Packet->NvmeCmd->Cdw10 >> 16) + 1) << 2);
    } else {
        // NUMDU
        Numdl = Packet->NvmeCmd->Cdw11;
        Numdl = Numdl << 16;
        
        //NUMDL
        Numdl = (Numdl | (Packet->NvmeCmd->Cdw10 >> 16));
        NumOfBytes = (Numdl + 1) << 2;
    }
    
    if(Packet->TransferLength < NumOfBytes ){
        return FALSE;
    }
    
    return TRUE;
}

/**
    Returns NVM Express controller device path

    @param This              A pointer to the EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI instance
    @param DevicePathLength  Returns DevicePath Length
    @param DevicePath        Returns DevicePath 

    @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
GetDevicePath(
    IN  EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI   *This,
    OUT UINTN                                 *DevicePathLength,
    OUT EFI_DEVICE_PATH_PROTOCOL              **DevicePath
)
{
    NVME_CONTROLLER_INFO *NvmeControllerInfo;
    
    if((This == NULL) || (DevicePathLength == NULL) || (DevicePath == NULL)) {
        return EFI_INVALID_PARAMETER;
    }
    
    NvmeControllerInfo = (NVME_CONTROLLER_INFO *)This;
    
    *DevicePathLength = PeiDpLength(NvmeControllerInfo->DevPath);
    *DevicePath = AllocateCopyPool(*DevicePathLength, NvmeControllerInfo->DevPath);
    if (*DevicePath == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    return EFI_SUCCESS;
}

/**
    API to get next valid NameSpace ID of the Nvme Device

    @param  This         A pointer to the EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI instance
    @param  NamespaceId  A pointer to a valid Namespace ID on this NVM Express controller 

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
GetNextNameSpace(
    IN     EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI   *This,
    IN OUT UINT32                                *NamespaceId
)
{
    NVME_CONTROLLER_INFO    *NvmeControllerInfo;
    ACTIVE_NAMESPACE_DATA   *ActiveNameSpaceData;
    LIST_ENTRY              *LinkData;
    BOOLEAN                 ReturnNextNameSpaceId = FALSE;
    
    if((This == NULL) || (NamespaceId == NULL)) {
        return EFI_INVALID_PARAMETER;
    }
    
    NvmeControllerInfo = (NVME_CONTROLLER_INFO *)This;
    
    if(*NamespaceId == MAX_UINT32) {
        ReturnNextNameSpaceId = TRUE;
    }
    
    for (LinkData = NvmeControllerInfo->ActiveNameSpaceList.ForwardLink; 
         LinkData != &NvmeControllerInfo->ActiveNameSpaceList; 
         LinkData = LinkData->ForwardLink) {
        
        ActiveNameSpaceData = BASE_CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);

        if(ReturnNextNameSpaceId) {
            *NamespaceId = ActiveNameSpaceData->ActiveNameSpaceId;
            return EFI_SUCCESS;
        }
        
        if(ActiveNameSpaceData->ActiveNameSpaceId == *NamespaceId) {
            ReturnNextNameSpaceId = TRUE;
        }
    }
    
    if(ReturnNextNameSpaceId) {
        return EFI_NOT_FOUND;
    }

    return EFI_INVALID_PARAMETER;  
}

/**
    Sends an NVM Express Command Packet to an NVM Express controller or namespace

    @param This         A pointer to the EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI instance
    @param NamespaceId  A 32 bit namespace ID as defined in the NVMe specification 
                        to which the NVM Express Command Packet will be sent.  
    @param Packet       A pointer to the NVM Express Command Packet to send to
                        the NVMe namespace specified by NamespaceId. 

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
PassThru (
    IN     EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI         *This,
    IN     UINT32                                      NamespaceId,
    IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET    *Packet
)
{
    EFI_STATUS                    Status = EFI_INVALID_PARAMETER;
    ACTIVE_NAMESPACE_DATA         *ActiveNameSpace = NULL;
    NVME_COMMAND_WRAPPER          *NvmeCmdWrapper;
    NVME_CONTROLLER_INFO          *NvmeControllerInfo;
    COMPLETION_QUEUE_ENTRY        *NvmeCompletionData;
    UINT8                         NvmeOpcode;
    UINT64                        LBA;
    UINTN                         BufferSize;
    UINTN                         MaxAllowableTransferSize;
    UINT32                        Nsid;
    EFI_PHYSICAL_ADDRESS          TransferBufferMappedAddr;
    VOID                          *TransferBufferUnMap = NULL;
    VOID                          *OrgTransferBuffer = NULL;
    UINTN                         OrgTransferLength;
    EDKII_IOMMU_OPERATION         IoOperation;
    
    if( !This || !Packet || (Packet->TransferLength && !Packet->TransferBuffer) || !Packet->NvmeCmd ||
        (Packet->QueueType > NVME_IO_QUEUE) || !Packet->NvmeCompletion) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Check Transfer buffer is NULL, if not,Check its memory is properly alligned or not
    if( Packet->TransferBuffer && ( This->Mode->IoAlign > 1 ) ) {
        if((!IS_ALIGNED((UINTN)Packet->TransferBuffer, This->Mode->IoAlign)) ||
           (!IS_ALIGNED(Packet->TransferLength, This->Mode->IoAlign))) {
            return EFI_INVALID_PARAMETER;
        }
    }
    
    NvmeControllerInfo = (NVME_CONTROLLER_INFO*)This;
    
    Nsid = Packet->NvmeCmd->Nsid ? Packet->NvmeCmd->Nsid : MAX_UINT32;
    ActiveNameSpace = GetActiveNameSpace(NvmeControllerInfo, Nsid);
    if(ActiveNameSpace == NULL) {
        return EFI_NOT_FOUND;
    }
    
    NvmeCompletionData = (COMPLETION_QUEUE_ENTRY*)Packet->NvmeCompletion;
    NvmeOpcode = (UINT8)Packet->NvmeCmd->Cdw0.Opcode;
    
    NvmeCmdWrapper = NvmeControllerInfo->NvmeCmdWrapper;
    
    ZeroMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    
    // Fill Common values of command
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NvmeOpcode;
    NvmeCmdWrapper->NvmCmd.Cmd0.FusedOperation = (UINT8)Packet->NvmeCmd->Cdw0.FusedOperation;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = \
            Packet->QueueType?  NvmeControllerInfo->CommandIdentifierQueue1 : NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Nsid = Packet->NvmeCmd->Nsid;
    NvmeCmdWrapper->AdminOrNVMCmdSet = Packet->QueueType ? FALSE : TRUE;
    NvmeCmdWrapper->SqIdentifier = Packet->QueueType;           // Queue 0 for Admin cmds,1 for I/O command
    
    if (Packet->CommandTimeout) {
        // If timeout is less than 1 millisecond, Assign Timeout value to 1 millisecond
        NvmeCmdWrapper->CmdTimeOut = (UINT32)(Packet->CommandTimeout < 10000 ? 1 : DivU64x32 (Packet->CommandTimeout, 10000));
    }
    
    if(Packet->NvmeCmd->Flags & CDW10_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw10 = Packet->NvmeCmd->Cdw10;
    }
    
    if(Packet->NvmeCmd->Flags & CDW11_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw11 = Packet->NvmeCmd->Cdw11;
    }
    
    if(Packet->NvmeCmd->Flags & CDW12_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw12 = Packet->NvmeCmd->Cdw12;
    }
    
    if(Packet->NvmeCmd->Flags & CDW13_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw13 = Packet->NvmeCmd->Cdw13;
    }
    
    if(Packet->NvmeCmd->Flags & CDW14_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw14 = Packet->NvmeCmd->Cdw14;
    }
    
    if(Packet->NvmeCmd->Flags & CDW15_VALID) {
        NvmeCmdWrapper->NvmCmd.Cdw15 = Packet->NvmeCmd->Cdw15;
    }
    
    if (Packet->TransferBuffer && Packet->TransferLength && gEdk2IoMmuPpi) { 
        // For read map/unmap is called inside NvmeReadBlocks()
        if (!((Packet->QueueType == NVME_IO_QUEUE) && (NvmeOpcode == NVME_IO_READ_OPC))) {   
            switch (NvmeOpcode & 3) {
                case 1:
                    IoOperation = EdkiiIoMmuOperationBusMasterRead;
                    break;
                case 2:
                    IoOperation = EdkiiIoMmuOperationBusMasterWrite;
                    break;
                case 3:
                    IoOperation = EdkiiIoMmuOperationBusMasterCommonBuffer;
                    break;
            }
            
            OrgTransferBuffer = Packet->TransferBuffer;
            OrgTransferLength = Packet->TransferLength;
            
            Status = gEdk2IoMmuPpi->Map( gEdk2IoMmuPpi,
                                         IoOperation,
                                         (VOID*)OrgTransferBuffer,
                                         &OrgTransferLength,
                                         &TransferBufferMappedAddr,
                                         &TransferBufferUnMap );
            if (EFI_ERROR (Status)) {
                return Status;
            }
            
            Packet->TransferBuffer = (VOID *)(UINTN)TransferBufferMappedAddr;
            Packet->TransferLength = (UINT32) OrgTransferLength;
        }
    }

    // if QueueType is 0, Admin Command
    // if QueueType is 1, I/O Command
    if ( Packet->QueueType == NVME_ADMIN_QUEUE )  {
        if( Packet->TransferBuffer ) {
        
            MaxAllowableTransferSize = (UINTN)LShiftU64(1, NvmeControllerInfo->IdentifyData->Mdts) * NvmeControllerInfo->MemoryPageSizeMin;
            
            // Check the transfer size to MDTS value
            if (NvmeControllerInfo->IdentifyData->Mdts && (Packet->TransferLength > MaxAllowableTransferSize)) {
                Packet->TransferLength = (UINT32)MaxAllowableTransferSize;
                Status = EFI_BAD_BUFFER_SIZE;
                goto PassThru_ErrorPath;
            }  
        
            // Program PRP1 and PRP2 entry        
            Status = ProgramPrpEntry(NvmeControllerInfo, 
                                     NvmeCmdWrapper, 
                                     Packet->TransferLength, 
                                     Packet->TransferBuffer, 
                                     ActiveNameSpace->Prp2List, 
                                     &BufferSize);
            if( EFI_ERROR(Status) ) {
                goto PassThru_ErrorPath;
            }
        }
        
        Status = EFI_INVALID_PARAMETER;
        switch(NvmeOpcode) {
        
            case NVME_ADMIN_SECURITY_SEND_CMD:
            case NVME_ADMIN_SECURITY_RECEIVE_CMD:
                
                // SECURITY_SEND and SECURITY_RECEIVE commands is supported only if BIT0 is set
                if (!((NvmeControllerInfo->IdentifyData->Oacs) & BIT0)) {
                    Status = EFI_UNSUPPORTED;
                    break;
                }
                if( (Packet->NvmeCmd->Flags & (CDW10_VALID|CDW11_VALID)) != 
                    (CDW10_VALID|CDW11_VALID) ) {
                    break;
                }
                
                if(Packet->TransferLength!=Packet->NvmeCmd->Cdw11) {
                    Status = EFI_BAD_BUFFER_SIZE;
                    break;
                }                
                
                NvmeCmdWrapper->NvmCmd.Cdw11 = (UINT32)BufferSize;  // BufferSize                
  
                Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);
                break;

            case NVME_ADMIN_GET_FEATURES_CMD:               
            case NVME_ADMIN_SET_FEATURES_CMD:
                
                if( (Packet->NvmeCmd->Flags & (CDW10_VALID|CDW11_VALID)) != 
                    (CDW10_VALID|CDW11_VALID) ) {
                        break;
                }                
                
                if((Packet->TransferBuffer) && (Packet->TransferLength ==0)) {
                    Status = EFI_BAD_BUFFER_SIZE;
                    break;
                }
                
                Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);               
                break;
                
            case NVME_ADMIN_GET_LOG_PAGE_CMD:
                if(NvmeControllerInfo->ControllerVersion < NVME_SPEC_VS_1_2_1){
                    if((Packet->NvmeCmd->Flags & (CDW10_VALID|CDW11_VALID|CDW12_VALID|CDW13_VALID)) != CDW10_VALID) {
                        break;
                    }
                } else if((Packet->NvmeCmd->Flags & CDW10_VALID) != CDW10_VALID) {
                    break;
                }
                
                if(ValidateGetLogBuffer(Packet)) {
                    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);
                } else {
                    Status = EFI_BAD_BUFFER_SIZE;
                }
                
                break;
                
            case NVME_ADMIN_IDENTIFY_CMD:
                if( !(Packet->NvmeCmd->Flags & CDW10_VALID) ) {
                    break;
                }
                
                if( Packet->TransferLength < sizeof(NVME_ADMIN_CONTROLLER_DATA) ) {
                    Packet->TransferLength = sizeof(NVME_ADMIN_CONTROLLER_DATA);
                    Status = EFI_BAD_BUFFER_SIZE;
                    break;
                }                
                
                if(Packet->TransferBuffer) {
                    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, (COMPLETION_QUEUE_ENTRY*)NvmeCompletionData);
                }
                break;
                
            default:
                Status = EFI_UNSUPPORTED;
                break;
        }
    } else {
        switch(NvmeOpcode) {

            case NVME_IO_READ_OPC:
                if( (Packet->NvmeCmd->Flags & (CDW10_VALID|CDW11_VALID|CDW12_VALID|CDW14_VALID|CDW15_VALID)) != 
                    (CDW10_VALID|CDW11_VALID|CDW12_VALID|CDW14_VALID|CDW15_VALID) ) {
                    break;
                }
                
                LBA = Packet->NvmeCmd->Cdw11;
                LBA = LShiftU64 (LBA, 32) | ( (UINT64)Packet->NvmeCmd->Cdw10 & 0x0FFFFFFFF );
    
                ActiveNameSpace = GetActiveNameSpace( NvmeControllerInfo, Packet->NvmeCmd->Nsid );
                if( ActiveNameSpace == NULL ) {
                    break;
                }
    
                Status = NvmeReadBlocks ( ActiveNameSpace,
                                          LBA,
                                          Packet->TransferLength,
                                          Packet->TransferBuffer,
                                          NvmeCompletionData );
                 break;
                 
            case NVME_IO_WRITE_OPC: // Write not supported
            default:
                break;
     
        }
    }
    
PassThru_ErrorPath:
    
    //IOMMU_Support
    if (TransferBufferUnMap){
        gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, TransferBufferUnMap);  
    }
    
    if (OrgTransferBuffer) {
        Packet->TransferBuffer = OrgTransferBuffer;
    }
    
    return Status;
    
}

/**
  @internal
  
    Installs NvmePassThru PPI
   
    @param NvmeControllerInfo
   
    @return EFI_STATUS
  
  @endinternal
**/
EFI_STATUS
InstallNvmePassThruPpi(
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
)
{
    EFI_STATUS                        Status;
    EFI_NVM_EXPRESS_PASS_THRU_MODE    *Mode;
    EFI_PEI_PPI_DESCRIPTOR            *NvmePassThruPpi;
    
    Mode = AllocateZeroPool(sizeof(EFI_NVM_EXPRESS_PASS_THRU_MODE));
    if ( Mode == NULL ) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    NvmeControllerInfo->NvmePassThru.Revision          = EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI_REVISION;
    NvmeControllerInfo->NvmePassThru.Mode              = Mode;
    NvmeControllerInfo->NvmePassThru.PassThru          = PassThru;
    NvmeControllerInfo->NvmePassThru.GetDevicePath     = GetDevicePath;
    NvmeControllerInfo->NvmePassThru.GetNextNameSpace  = GetNextNameSpace;
    
    // Set the attributes accordingly
    Mode->Attributes  = EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL | EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM;
    Mode->IoAlign     = 4; // DWORD aligned
    Mode->NvmeVersion = NvmeControllerInfo->ControllerVersion;
    
    NvmePassThruPpi = AllocateZeroPool(sizeof(EFI_PEI_PPI_DESCRIPTOR));
    if ( NvmePassThruPpi == NULL ) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    NvmePassThruPpi->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    NvmePassThruPpi->Ppi = (VOID *)&NvmeControllerInfo->NvmePassThru;
    NvmePassThruPpi->Guid = &gEdkiiPeiNvmExpressPassThruPpiGuid;
    
    Status = PeiServicesInstallPpi(NvmePassThruPpi);
    return Status;
}
