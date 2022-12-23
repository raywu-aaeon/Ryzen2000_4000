//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  NVRAM Services in PEI
**/

#include <Ppi/ReadOnlyVariable.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <AmiPeiLib.h>
#include <Token.h>
#include "NVRAM.h"
#include <Library/AmiRomLayoutLib.h>
#include <Library/DebugLib.h>
#include <Setup.h>
#include <AmiNvramPeiPlatformHooks.h>

BOOLEAN PeiNvramDataCompatiblityChecker(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
);
NVAR* NvGetFirstValid(NVRAM_STORE_INFO *pInfo);
//Defined in Tokens.c
extern UINTN NvramAddress;
extern UINTN NvramBackupAddress;
extern const UINTN NvramSize;
extern const BOOLEAN NvSimulation;

typedef struct{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI Ppi;
    UINT32 InfoCount;
    UINT32 LastInfoIndex;
    NVRAM_STORE_INFO NvramInfo[3];
    UINT32 PeiVarListSize;
    UINT16 PeiVarListNumber;
    VOID   *VarDataPtr;
} VARIABLE_PPI;

//--- GetVariable and GetNextVarName Hooks ------
EFI_STATUS PeiGetVariableHook(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data
){
    UINTN i;
    EFI_STATUS Result = EFI_UNSUPPORTED;
    for(i=0; PeiGetVariableHookList[i] && (Result == EFI_UNSUPPORTED); i++)
        Result = PeiGetVariableHookList[i](This,VariableName, VendorGuid,Attributes, DataSize, Data);
    return Result;
}

EFI_STATUS PeiGetNextVarNameHook(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
){
    UINTN i;
    EFI_STATUS Result = EFI_UNSUPPORTED;
    for(i=0; PeiGetNextVarNameHookList[i] && (Result == EFI_UNSUPPORTED); i++)
        Result = PeiGetNextVarNameHookList [i](This,VariableNameSize,VariableName, VendorGuid);
    return Result;
}
//---GetVariable and GetNextVarName Hooks END------

/**
  This function determines if the current NVRAM data
  (mainly Setup-related variables) is compatible with the current firmware.

  @param PeiServices pointer to a pointer to the PEI Services Table.
  @param ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI.
                           The pointer can be used to read and enumerate existing NVRAM variables.

  @retval:
    BOOLEAN
      TRUE - the NVRAM data is compatible
      FALSE - the NVRAM data is not compatible
**/
BOOLEAN PeiNvramDataCompatiblityChecker(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    static EFI_GUID SetupVariableGuid = SETUP_GUID;
    UINTN Size = 0;
    EFI_STATUS Status;

    Status=ReadVariablePpi->GetVariable(
        ReadVariablePpi, L"Setup",
        &SetupVariableGuid, NULL,
        &Size, NULL
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return TRUE;
    return Size==sizeof(SETUP_DATA);
}

/**
    This function calls a list of function defined at build time and
    return whether the functions completed successfully or not


    @param PeiServices pointer to the PeiServices Table
    @param ReadVariablePpi pointer to the Read Only Variable 2 PPI

    @retval
        BOOLEAN
        - TRUE - all functions returned correctly
        - FALSE - one of the functions failed during execution

    @note
  Similar to CallOneParamHooks except that these function also require
  a pointer to the Read Only Variable 2 PPI

**/
BOOLEAN CallNvramModeDetectionHooks(
    IN NVRAM_MODE_DETECTION_FUNCTION* FunctionList[],
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    UINTN i;
    BOOLEAN Result = FALSE;
    for(i=0; FunctionList[i] && !Result; i++)
        Result = FunctionList[i]((EFI_PEI_SERVICES **)PeiServices,ReadVariablePpi);
    return Result;
}

/**
    This function determines if the system in in manufacturing mode.
    This function is called by NVRAM code.
    If system is in manufacturing mode, manufacturing values for NVRAM variables
    are used.

    @param PeiServices - pointer to a pointer to the PEI Services Table.
    @param ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The pointer
           can be used to read and enumerate existing NVRAM variables.


    @retval TRUE Manufacturing mode is detected
    @retval FALSE Manufacturing mode is not detected

    @note
  This routine is called very early, prior to SBPEI and NBPEI
**/
BOOLEAN IsMfgMode(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
#if MANUFACTURING_MODE_SUPPORT
    //Use IsMfgMode eLink to install customer handlers
    return CallNvramModeDetectionHooks(IsMfgModeList, PeiServices, ReadVariablePpi);
#else
    //Do not change this.
    //This is needed to be able to disable manufacturing mode support using SDL token.
    return FALSE;
#endif
}

/**
    This function determines if the system configuration needs to be reset.
    This function is called by NVRAM code.

    @param PeiServices - pointer to a pointer to the PEI Services Table.
    @param ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The
           pointer can be used to read and enumerate existing NVRAM
           variables.


    @retval TRUE Reset Configuration condition is detected
    @retval FALSE Reset Configuration condition is not detected

    @note  This routine is called very early, prior to SBPEI and NBPEI
**/
BOOLEAN IsResetConfigMode(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    //Use IsResetConfigMode eLink to install customer handlers
    return CallNvramModeDetectionHooks(
        IsResetConfigModeList, PeiServices, ReadVariablePpi
    );
}

/**
    This function determines if the system should boot with the default configuration.
    This function is called by NVRAM code.
    If boot with default configuration is detected, default values for NVRAM
    variables are used.

    @param PeiServices - pointer to a pointer to the PEI Services Table.
    @param ReadVariablePpi - pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The pointer
           can be used to read and enumerate existing NVRAM variables.


    @retval TRUE Boot with default configuration is detected
    @retval FALSE Boot with default configuration is not detected

    @note
  This routine is called very early, prior to SBPEI and NBPEI

**/
BOOLEAN IsDefaultConfigMode(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
    // Use IsDefaultConfigMode eLink to install custom handlers
    return CallNvramModeDetectionHooks(
        IsDefaultConfigModeList, PeiServices, ReadVariablePpi
    );
}

/**
    This function searches for a Variable with specific GUID and Name

    @param PeiServices Double pointer to PEI Services instance
    @param VariableName pointer to Var Name in Unicode
    @param VendorGuid pointer to Var GUID
    @param Attributes Pointer to memory where Attributes will be returned
    @param DataSize size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL
        will be returned and DataSize will be set to actual size needed
    @param Data Pointer to memory where Var will be returned

    @retval EFI_STATUS based on result

**/
EFI_STATUS VarPpiGetVariable(
    IN EFI_PEI_SERVICES **PeiServices,
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data
)
{
    DEBUG((DEBUG_ERROR,"Deprecated ReadOnlyVariable PPI is used. Use ReadOnlyVariable2 PPI instead\n"));
    return PeiGetVariable(
            (CONST EFI_PEI_SERVICES**)PeiServices, VariableName, VendorGuid, Attributes, DataSize, Data
    );
}

/**
    Return the next variable name and GUID.

    This function is called multiple times to retrieve the VariableName
    and VariableGuid of all variables currently available in the system.
    On each call, the previous results are passed into the interface,
    and, on return, the interface returns the data for the next interface.
    When the entire variable list has been returned, EFI_NOT_FOUND is returned.

    @param PeiServices double pointer to PEI Services instance
    @param  VariableNameSize  On entry, points to the size of the buffer pointed to by VariableName.
                              On return, the size of the variable name buffer.
    @param  VariableName      On entry, a pointer to a null-terminated string that is the variable's name.
                              On return, points to the next variable's null-terminated name string.

    @param  VariableGuid      On entry, a pointer to an EFI_GUID that is the variable's GUID.
                              On return, a pointer to the next variable's GUID.

    @retval EFI_SUCCESS           The variable was read successfully.
    @retval EFI_NOT_FOUND         The variable could not be found.
    @retval EFI_BUFFER_TOO_SMALL  The VariableNameSize is too small for the resulting
                                  data. VariableNameSize is updated with the size
                                  required for the specified variable.
    @retval EFI_INVALID_PARAMETER VariableName, VariableGuid or
                                  VariableNameSize is NULL.
    @retval EFI_DEVICE_ERROR      The variable could not be retrieved because of a device error.
**/
EFI_STATUS VarPpiGetNextVariableName(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
)
{
    DEBUG((DEBUG_ERROR,"Deprecated ReadOnlyVariable PPI is used. Use ReadOnlyVariable2 PPI instead\n"));
    return PeiGetNextVariableName(
        (CONST EFI_PEI_SERVICES**)PeiServices, VariableNameSize, VariableName, VendorGuid
    );
}

/**
    This function searches for Variable with specific name and GUID

    @param This pointer to FI_PEI_READ_ONLY_VARIABLE2_PPI
    @param VariableName pointer to Var Name in Unicode
    @param VendorGuid pointer to Var GUID
    @param Attributes Pointer to memory where Attributes will be returned
    @param DataSize size of Var - if smaller than actual EFI_BUFFER_TOO_SMALL
        will be returned and DataSize will be set to actual size needed
    @param Data Pointer to memory where Var will be returned

    @retval EFI_STATUS based on result

**/
EFI_STATUS VarPpi2GetVariable(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName, IN CONST EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, IN OUT UINTN *DataSize, OUT VOID *Data
)
{
    EFI_STATUS Status;
    VARIABLE_PPI *VarPpi = (VARIABLE_PPI*)This;
    
    Status = PeiGetVariableHook (
                This, VariableName, VendorGuid, Attributes, DataSize, Data
             );
    if (Status != EFI_UNSUPPORTED) return Status;

    if (!VariableName || !VendorGuid || !DataSize || (!Data && *DataSize))
        return EFI_INVALID_PARAMETER;
    if ((VarPpi->PeiVarListNumber != 0) && (VarPpi->PeiVarListNumber != 0xFFFF))
    {
        UINTN *VarAddressPointer = (UINTN*) (VOID*)((UINTN)&(VarPpi->VarDataPtr) + sizeof(VOID*));
        NVRAM_PEI_VAR_LIST_ENTRY *ListEnt = (NVRAM_PEI_VAR_LIST_ENTRY*)VarPpi->VarDataPtr; 
        UINT16 i;
        
        for (i = 0; i < VarPpi->PeiVarListNumber; i++)
        {
            if (!guidcmp((EFI_GUID*)VendorGuid, &ListEnt->Guid) && (ListEnt->NameSize == (UINT16)StrSize(VariableName)))
            {
                // Unaligned word access causes exception on ARM.
                // Since pN may be not word aligned, we are using unaligned access functions.
                CHAR16 *ListName = &ListEnt->Name, *VarName = (CHAR16*)VariableName;
                UINT16 MaxNameSize = ListEnt->NameSize;

                while (ReadUnaligned16(ListName) && ReadUnaligned16(ListName)==*VarName && MaxNameSize>0) 
                {
                    ListName++; VarName++; MaxNameSize-=sizeof(CHAR16);
                }

                if (ReadUnaligned16(ListName)==*VarName) //Names match 
                {
                    NVAR *Var = (NVAR*)(VOID*)VarAddressPointer[i];
                    UINTN Size;
                    UINTN DataOffset = sizeof(NVAR);
                    UINTN ExtSize;
                    if (VarAddressPointer[i] == 0)
                    {    
                        return EFI_NOT_FOUND;
                    }
                    if (Attributes)
                        *Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;
                    if ( Attributes && !(Var->flags & NVRAM_FLAG_DATA_ONLY))
                    {
                    
                        if ( Var->flags & NVRAM_FLAG_RUNTIME )
                            *Attributes|=EFI_VARIABLE_RUNTIME_ACCESS;
                        if ( Var->flags & NVRAM_FLAG_HARDWARE_ERROR_RECORD )
                            *Attributes|=EFI_VARIABLE_HARDWARE_ERROR_RECORD;
                        if ( Var->flags & NVRAM_FLAG_AUTH_WRITE )
                            *Attributes|= (UINT8)(*NvGetExtFlags (Var) & UEFI23_1_AUTHENTICATED_VARIABLE_ATTRIBUTES);
                    }
                    if (Var->flags & NVRAM_FLAG_EXT_HEDER) 
                        ExtSize = NvExtSize(Var);
                    else 
                        ExtSize = 0;
                    if (!(Var->flags&NVRAM_FLAG_DATA_ONLY))
                    {
                        if(Var->flags&NVRAM_FLAG_ASCII_NAME)
                    
                            DataOffset +=  StrSize(VariableName)/2
                                    + (   Var->flags&NVRAM_FLAG_GUID
                                            ? sizeof(EFI_GUID) : 1
                                    );
                        else 
                            DataOffset +=  StrSize(VariableName)
                                    + (   Var->flags&NVRAM_FLAG_GUID
                                            ? sizeof(EFI_GUID) : 1
                                    );
                    }

                    Size = NvSize(Var) - DataOffset - ExtSize;
                
                    if (*DataSize<Size) 
                    { 
                        *DataSize=Size; 
                        return EFI_BUFFER_TOO_SMALL;
                    }
                
                    *DataSize=Size;

                    MemCpy(Data, (INT8*)Var+DataOffset, Size);

                    return EFI_SUCCESS; 
                }
            }
            ListEnt = (NVRAM_PEI_VAR_LIST_ENTRY*)((UINT8*)ListEnt + sizeof(NVRAM_PEI_VAR_LIST_ENTRY) + ListEnt->NameSize - sizeof(CHAR16));
        }
        VarPpi->PeiVarListNumber = 0;
    }
    
    Status = NvGetVariable2(
                (CHAR16*)VariableName, (EFI_GUID*)VendorGuid, Attributes,
                DataSize, Data, VarPpi->InfoCount, VarPpi->NvramInfo
             );

    if (VarPpi->PeiVarListNumber == 0)
    {
        NVRAM_PEI_VAR_HOB *VarHob = NULL;
        EFI_GUID PeiVarListGuid = NVRAM_PEI_VAR_LIST_HOB_GUID;
        UINT16 NameSize = (UINT16)StrSize(VariableName);
        CONST EFI_PEI_SERVICES **PeiServices;
        EFI_STATUS Status1;

        PeiServices = GetPeiServicesTablePointer();
        
        Status1 = (*PeiServices)->GetHobList((CONST EFI_PEI_SERVICES **)PeiServices, (VOID **)&VarHob);

        while (!EFI_ERROR(Status1))
        {
            Status1 = FindNextHobByGuid(&PeiVarListGuid, (VOID **)&VarHob);
            if (!EFI_ERROR(Status1))
            {
                if (!StrCmp (&(VarHob->Entry.Name), VariableName) && !guidcmp(&(VarHob->Entry.Guid), (EFI_GUID*)VendorGuid))
                {
                    return Status;
                }
            }   
        }
            
        
  
        Status1=(*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, 
                                           sizeof(NVRAM_PEI_VAR_HOB) + NameSize - sizeof(CHAR16),
                                           (VOID**)&VarHob);
           
        ASSERT_EFI_ERROR(Status1);
        if (!EFI_ERROR(Status1))
        {
            VarHob->Header.Name = PeiVarListGuid;
            VarHob->Entry.NameSize = NameSize;
            MemCpy(&(VarHob->Entry.Name), (CHAR16*)VariableName, NameSize);
            MemCpy(&(VarHob->Entry.Guid), (EFI_GUID*)VendorGuid, sizeof(EFI_GUID));
        }
   }

    return Status;
}

/**
    Return the next variable name and GUID.

    This function is called multiple times to retrieve the VariableName
    and VariableGuid of all variables currently available in the system.
    On each call, the previous results are passed into the interface,
    and, on return, the interface returns the data for the next interface.
    When the entire variable list has been returned, EFI_NOT_FOUND is returned.

    @param  This              A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.

    @param  VariableNameSize  On entry, points to the size of the buffer pointed to by VariableName.
                              On return, the size of the variable name buffer.
    @param  VariableName      On entry, a pointer to a null-terminated string that is the variable's name.
                              On return, points to the next variable's null-terminated name string.

    @param  VariableGuid      On entry, a pointer to an EFI_GUID that is the variable's GUID.
                              On return, a pointer to the next variable's GUID.

    @retval EFI_SUCCESS           The variable was read successfully.
    @retval EFI_NOT_FOUND         The variable could not be found.
    @retval EFI_BUFFER_TOO_SMALL  The VariableNameSize is too small for the resulting
                                  data. VariableNameSize is updated with the size
                                  required for the specified variable.
    @retval EFI_INVALID_PARAMETER VariableName, VariableGuid or
                                  VariableNameSize is NULL.
    @retval EFI_DEVICE_ERROR      The variable could not be retrieved because of a device error.
**/
EFI_STATUS VarPpi2GetNextVariableName(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName, IN OUT EFI_GUID *VendorGuid
)
{
    EFI_STATUS Status;
    VARIABLE_PPI *VarPpi = (VARIABLE_PPI*)This;
    Status = PeiGetNextVarNameHook (
                This, VariableNameSize, VariableName, VendorGuid
             );
    if (Status != EFI_UNSUPPORTED) return Status;
    Status = NvGetNextVariableName2(
                 VariableNameSize, VariableName, VendorGuid,
                 VarPpi->InfoCount, VarPpi->NvramInfo,
                 &(VarPpi->LastInfoIndex),FALSE
           );
    return Status;
}

// PPI interface definition
EFI_PEI_READ_ONLY_VARIABLE_PPI VariablePpi = {VarPpiGetVariable, VarPpiGetNextVariableName};
EFI_PEI_READ_ONLY_VARIABLE2_PPI Variable2Ppi = {VarPpi2GetVariable, VarPpi2GetNextVariableName};

// PPI to be installed
EFI_PEI_PPI_DESCRIPTOR VariablePpiListTemplate[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI,
        &gEfiPeiReadOnlyVariable2PpiGuid, &Variable2Ppi
    },
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPeiReadOnlyVariablePpiGuid, &VariablePpi
    }
};

EFI_STATUS GetNvramLocation (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  OUT UINT8 **MyNvramAddress,
  OUT UINT8 **MyNvramBackupAddress,
  OUT UINTN *MyNvramSize
)
{
    AMI_ROM_AREA *RomArea = NULL;

    RomArea = AmiGetFirstRomAreaByGuid (&gAmiNvramMainRomAreaGuid);
    if (RomArea != NULL)
    {
        *MyNvramAddress = (UINT8*)(UINTN)RomArea->Address;
        *MyNvramSize = RomArea->Size;
    }
    else
    {
        DEBUG((DEBUG_ERROR, "NVRAM PEI: NVRAM ROM area was not found!!! Using default address.\n"));
        *MyNvramAddress = (UINT8*)NvramAddress;
        *MyNvramSize = NvramSize;
    }
    RomArea = NULL;
    RomArea = AmiGetFirstRomAreaByGuid (&gAmiNvramBackupRomAreaGuid);
    if (RomArea != NULL)
    {
        *MyNvramBackupAddress = (UINT8*)(UINTN)RomArea->Address;
    }
    else
    {
        DEBUG((DEBUG_ERROR, "NVRAM PEI: NVRAM BACKUP ROM area was not found!!! Using default address.\n"));
        *MyNvramBackupAddress = (UINT8*)NvramBackupAddress;
    }
    return EFI_SUCCESS;
}

#define FV_BB_DEFAULTS_FFS_FILE_GUID \
    { 0xaf516361, 0xb4c5, 0x436e, { 0xa7, 0xe3, 0xa1, 0x49, 0xa3, 0x1b, 0x14, 0x61 } }

EFI_STATUS GetDefaultsInfoFromFvBb (
    IN CONST EFI_PEI_SERVICES  **PeiServices, IN NVRAM_STORE_INFO *DefInfo
){
    UINTN FvInstance = 0;
    EFI_PEI_FV_HANDLE FvHandle;
    EFI_PEI_FILE_HANDLE  FileHandle;
    static EFI_GUID gFvBbDefaultsFfsFileGuid = FV_BB_DEFAULTS_FFS_FILE_GUID;
    EFI_STATUS Status;

    while(TRUE) {
        VOID *Buffer;
        UINTN Size;
        NVRAM_STORE_INFO WrapperInfo;

        FvHandle = NULL;
        Status = (*PeiServices)->FfsFindNextVolume (PeiServices, FvInstance++, &FvHandle);
        if (EFI_ERROR (Status)) return Status;
        FileHandle = NULL;
        // Find file
        Status = (*PeiServices)->FfsFindFileByName (&gFvBbDefaultsFfsFileGuid, FvHandle, &FileHandle);
        if (EFI_ERROR (Status)) continue;
        // Read section data
        Status = (*PeiServices)->FfsFindSectionData(PeiServices, EFI_SECTION_RAW, FileHandle, &Buffer);
        if (EFI_ERROR (Status)) continue;
        Size = SECTION_SIZE((EFI_COMMON_SECTION_HEADER*)Buffer - 1) - sizeof(EFI_COMMON_SECTION_HEADER);
        WrapperInfo.NvramAddress = Buffer;
        WrapperInfo.NvramSize = Size;
        NvInitInfoBuffer(
            &WrapperInfo, 0,
              NVRAM_STORE_FLAG_NON_VALATILE
            | NVRAM_STORE_FLAG_READ_ONLY
            | NVRAM_STORE_FLAG_DO_NOT_ENUMERATE,
            NULL
        );
        if ( NvGetDefaultsInfo(StdDefaults, &WrapperInfo, DefInfo) == NULL ) continue;
        DefInfo->Flags |= NVRAM_STORE_FLAG_DEF_FROM_BB;
        return EFI_SUCCESS;
    }
}

NVRAM_STORE_INFO* PeiGetStdDefaultsInfo(IN NVRAM_STORE_INFO *InInfo, OUT NVRAM_STORE_INFO *OutInfo){
    CONST EFI_PEI_SERVICES **PeiServices;

    if (NvGetDefaultsInfo( StdDefaults, InInfo, OutInfo)!= NULL) return OutInfo;
    PeiServices = GetPeiServicesTablePointer();
    DEBUG((DEBUG_WARN, "NVRAM PEI: Built-in NVRAM Defaults are not found\n"));
    if (!EFI_ERROR(GetDefaultsInfoFromFvBb(PeiServices, OutInfo))) {
        DEBUG((DEBUG_WARN, "NVRAM PEI: Using FV_BB NVRAM Defaults\n"));
        return OutInfo;
    }
    return NULL;
}

/**
    Relocates NVRAM services to memory
**/
VOID NvramRelocateToMemory(IN CONST EFI_PEI_SERVICES **PeiServices){
    EFI_STATUS                      Status;
    EFI_PEI_PPI_DESCRIPTOR          *OldReadOnlyVariable2Descriptor;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *OldReadOnlyVariable2Ppi;
    VARIABLE_PPI                    *VarPpi;
    UINT8                           i; 

    Status = (*PeiServices)->LocatePpi(
        PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0,
        &OldReadOnlyVariable2Descriptor, (VOID **)&OldReadOnlyVariable2Ppi
    );

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    VarPpi = (VARIABLE_PPI*)OldReadOnlyVariable2Ppi;
    VarPpi->Ppi = Variable2Ppi;
    
        
    for (i = 0; i < VarPpi->InfoCount; i++) 
    {
        if (VarPpi->NvramInfo[i].Flags & NVRAM_STORE_FLAG_DEF_FROM_BB)
        {
            GetDefaultsInfoFromFvBb(PeiServices, &VarPpi->NvramInfo[i]);
        }      
    }

}

/**
    NVRAM PEIM Entry Point

    @param FfsHeader pointer to FfsHeader
    @param PeiServices double pointer to the PEI Services structure

    @retval EFI_STATUS based on result

**/
EFI_STATUS EFIAPI PeiInitNvram (
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS Status;
    EFI_PEI_PPI_DESCRIPTOR *VariablePpiList;
    VARIABLE_PPI *VarPpi;
    UINT32 NvramMode=0;
    BOOLEAN ResetConfigMode;
    NVRAM_STORE_INFO MainNvram;
    VARIABLE_PPI TmpVarPpi;
    UINT8 *BackupNvramAddress;
    BOOLEAN NvramIsCorrupted = FALSE;
    UINT32 HeaderLength;
    NVRAM_HOB *pHob;
    BOOLEAN BackupStoreValid;

    EFI_GUID AmiGlobalVarGuid        = gAmiGlobalVariableGuid;
    UINT32 Counter = 0;
    UINTN NameSize = 0, DataSize = sizeof(UINT32);
    NVAR *Var = NULL;
    VOID *pData = NULL;
    UINT32 i, j;
    NVRAM_PEI_VAR_LIST_ENTRY *ListEnt;
    UINTN *VarAddressPointer;
    
    
    //----------------------------------------

    if( (*PeiServices)->RegisterForShadow(FileHandle) == EFI_ALREADY_STARTED ){
        // NVRAM entry point has been launched second time after shadowing PEIM to memory.
        // Relocate NVRAM services to memory.
        NvramRelocateToMemory( PeiServices );
        return EFI_SUCCESS;
    }
    Status = GetNvramLocation(PeiServices,&MainNvram.NvramAddress,&BackupNvramAddress,&MainNvram.NvramSize);
    if (EFI_ERROR(Status)) return Status;
    if (!IsMainNvramStoreValid(MainNvram.NvramAddress, BackupNvramAddress,&BackupStoreValid)){
        if (BackupStoreValid){
            UINT8 *Tmp = BackupNvramAddress;
            BackupNvramAddress = MainNvram.NvramAddress;
            MainNvram.NvramAddress = Tmp;
        }else{
            NvramIsCorrupted = TRUE;
        }
    }
    HeaderLength = GetNvStoreHeaderSize((VOID*)MainNvram.NvramAddress);
    DEBUG((DEBUG_INFO,
         "NVRAM PEI: NVRAM Address: %p; NVRAM Backup Address: %p; NVRAM Size: %X; Header Size: %X\n",
         MainNvram.NvramAddress, BackupNvramAddress, MainNvram.NvramSize, HeaderLength
    ));
    NvInitInfoBuffer(
         &MainNvram,
         HeaderLength,
         NVRAM_STORE_FLAG_NON_VALATILE,
         NULL
    );
    
    Var = (NVAR*)NvFindVariable(L"AmiPeiVarStr", &AmiGlobalVarGuid, &NameSize, &MainNvram);
    if (Var)
        NvGetDataNvar(Var, &MainNvram);
    if (Var == NULL){
        DataSize        = sizeof(UINT32);
        Status = NvGetVariable (L"MonotonicCounter", &AmiGlobalVarGuid, NULL, &DataSize, &Counter, &MainNvram, NULL);
    }
    else{
        pData = NvGetData(Var, NameSize, &DataSize, &MainNvram);
    }
    
    if (pData){
        NameSize = (((NVRAM_PEI_VAR_LIST*)pData)->EntriesNumber * sizeof(UINTN));
    }
    else{
        NameSize = 0;
    }
    
    Status = (*PeiServices)->AllocatePool(PeiServices, 
                            sizeof(VariablePpiListTemplate) + sizeof(VARIABLE_PPI) + NameSize, 
                            (VOID**)&VariablePpiList);
    if (EFI_ERROR(Status)) return Status;
    VariablePpiList[0]=VariablePpiListTemplate[0];
    VariablePpiList[1]=VariablePpiListTemplate[1];
    VarPpi = (VARIABLE_PPI*)(VariablePpiList + 2);
    VariablePpiList[0].Ppi = VarPpi;
    VarPpi->Ppi = Variable2Ppi;
    VarPpi->InfoCount = 0;
    VarPpi->LastInfoIndex = 0;
    VarPpi->PeiVarListNumber = (UINT16) -1;
    VarPpi->VarDataPtr = NULL;
    
#if NV_SIMULATION_NO_FLASH_READS
     NvramMode=NVRAM_MODE_RESET_CONFIGURATION;
     DEBUG((DEBUG_WARN, "NVRAM PEI: Working in simulation mode.\n"));
     return (*PeiServices)->InstallPpi(PeiServices,VariablePpiList);
#endif
    if (NvramIsCorrupted){
        NvramMode=NVRAM_MODE_RESET_CONFIGURATION;
        DEBUG((DEBUG_ERROR, "NVRAM PEI: NVRAM header corruption is detected\n"));
        if (!EFI_ERROR(GetDefaultsInfoFromFvBb(PeiServices, &VarPpi->NvramInfo[VarPpi->InfoCount]))){
            VarPpi->InfoCount++;
            DEBUG((DEBUG_WARN, "NVRAM PEI: Using FV_BB NVRAM Defaults\n"));
        }
    }else{
        TmpVarPpi = *VarPpi;
        TmpVarPpi.NvramInfo[0]=MainNvram;
        TmpVarPpi.InfoCount=1;
        if (   IsMfgMode(PeiServices,&TmpVarPpi.Ppi)
            && NvGetDefaultsInfo(
                   MfgDefaults,&MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
               ) != NULL
        ){
            VarPpi->InfoCount++;
            NvramMode|=NVRAM_MODE_MANUFACTORING;
        }
        ResetConfigMode = IsResetConfigMode(PeiServices,&TmpVarPpi.Ppi);
        if (!ResetConfigMode && !IsDefaultConfigMode(PeiServices,&TmpVarPpi.Ppi)){
            VarPpi->NvramInfo[VarPpi->InfoCount]=MainNvram;
            VarPpi->InfoCount++;
            if (PeiGetStdDefaultsInfo(
                    &MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
                ) != NULL
            ){
                VarPpi->InfoCount++;
            }
        }else{
            if (PeiGetStdDefaultsInfo(
                    &MainNvram,&VarPpi->NvramInfo[VarPpi->InfoCount]
                ) != NULL
            ){
                VarPpi->InfoCount++;
            }
            if (ResetConfigMode){
                NvramMode|=NVRAM_MODE_RESET_CONFIGURATION;
            }else{
                VarPpi->NvramInfo[VarPpi->InfoCount]=MainNvram;
                VarPpi->InfoCount++;
                NvramMode|=NVRAM_MODE_DEFAULT_CONFIGURATION;
            }
        }
        if (!CompatibilityChecker(PeiServices, &VarPpi->Ppi)){
            DEBUG((DEBUG_ERROR, "NVRAM PEI: Incompatible NVRAM detected\n"));
            VarPpi->InfoCount=0;
            if (!EFI_ERROR(GetDefaultsInfoFromFvBb(PeiServices, &VarPpi->NvramInfo[VarPpi->InfoCount]))){
                VarPpi->InfoCount++;
                DEBUG((DEBUG_WARN, "NVRAM PEI: Incompatible NVRAM. Using FV_BB NVRAM Defaults\n"));
            }
        }
    }
    
    if (NameSize == 0){
            VarPpi->PeiVarListSize = 0;
            if (Counter >= 3)
                VarPpi->PeiVarListNumber = 0;
        }  
        else{
            VarPpi->VarDataPtr = (VOID*)((UINTN)pData + sizeof(UINT16));
            VarPpi->PeiVarListSize = (UINT32)DataSize;
            VarPpi->PeiVarListNumber = ((NVRAM_PEI_VAR_LIST*)pData)->EntriesNumber;
            (*PeiServices)->SetMem ( (VOID*)((UINTN)&(VarPpi->VarDataPtr) + sizeof(UINTN)), VarPpi->PeiVarListNumber * sizeof(UINTN), 0);

        }
        
    //CollectPeiVarListData----------------------
    if (NameSize)
    {
        
        VarAddressPointer = (UINTN*) (VOID*)((UINTN)&(VarPpi->VarDataPtr) + sizeof(UINTN));

        for (i = 0 ; i < VarPpi->InfoCount; i++)
        {
            Var = NvGetFirstValid(&(VarPpi->NvramInfo[i]));
            
            for (; Var; Var=NvGetNextValid(Var, &(VarPpi->NvramInfo[i])))
            {
                ListEnt =  (NVRAM_PEI_VAR_LIST_ENTRY*)VarPpi->VarDataPtr; 
                for (j = 0; j < VarPpi->PeiVarListNumber; j++)
                {
                    if (VarAddressPointer[j] == 0) 
                    {

                        if (NvVarEq(Var, &(ListEnt->Name), &(ListEnt->Guid), NULL, &(VarPpi->NvramInfo[i])))
                        {
                            VarAddressPointer[j] = (UINTN)((VOID*)NvGetDataNvar(Var, &(VarPpi->NvramInfo[i])));
                            break;
                        } 
                    }
                    ListEnt = (NVRAM_PEI_VAR_LIST_ENTRY*) (VOID*)((UINTN)ListEnt + sizeof(NVRAM_PEI_VAR_LIST_ENTRY) + ListEnt->NameSize - 2); 
                }
            }
        }  
    }
    
    Status=(*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(NVRAM_HOB),(VOID**)&pHob);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)){
        pHob->Header.Name=AmiNvramHobGuid;
        pHob->NvramAddress=(EFI_PHYSICAL_ADDRESS)(UINTN)MainNvram.NvramAddress;
        pHob->BackupAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)BackupNvramAddress;
        pHob->NvramSize = (UINT32)MainNvram.NvramSize;
        if (NvSimulation) NvramMode|=NVRAM_MODE_SIMULATION;
        pHob->NvramMode = NvramMode;
        pHob->HeaderLength = HeaderLength;
    }
   
    return (*PeiServices)->InstallPpi(PeiServices,VariablePpiList);
   
}

