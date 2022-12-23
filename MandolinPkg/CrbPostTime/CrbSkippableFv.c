//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CrbSkippableFv.c
    This file contains code for CrbSkippableFv initialization in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Guid/ZeroGuid.h>
#include <Ppi/ReadOnlyVariable2.h>

#include <Token.h>
// AMI Compatibility header
#include <Setup.h>
#include <Guid/NetworkStackSetup.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------

EFI_STATUS
EFIAPI
CrbEndOfPeiSignalCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

extern EFI_GUID gCrbSkippableEmptyFvGuid; //define header file later.
extern EFI_GUID gCrbSkippableCsmFvFfsGuid; //define header file later.
extern EFI_GUID gCrbSkippableNetworkFvFfsGuid; //define header file later.
extern EFI_GUID gCrbSkippableTcgFvFfsGuid; //define header file later.

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  CrbSkippableFvNotifyList[] =
{
    {
		(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
		&gEfiEndOfPeiSignalPpiGuid,
		CrbEndOfPeiSignalCallback
    }
};

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function is the entry point for CrbSkippableFv PEIM.
    It initializes the chipset CrbSkippableFv in PEI phase.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
CrbSkippableFvConstructor (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
    EFI_STATUS                  	Status = EFI_SUCCESS;

	Status = PeiServicesNotifyPpi(CrbSkippableFvNotifyList);

    return Status;
}


/**
    This function is called at end of PEI phase. It disables the
    ROM cache to avoid the problem with flash.


    @param PeiServices Pointer to PeiServices
    @param NotifyDesc Pointer to NotifyDesc
    @param InvokePpi

    @retval EFI_STATUS EFI_SUCCESS

**/

EFI_STATUS
EFIAPI
CrbEndOfPeiSignalCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
  )
{
	EFI_STATUS                  		Status = EFI_SUCCESS;
	EFI_GUID        					SetupGuid = SETUP_GUID;
	UINTN                           	VariableSize;
	SETUP_DATA                         	SetupData;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;

	Status = PeiServicesLocatePpi(&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable);
	ASSERT_EFI_ERROR(Status);

	VariableSize = sizeof(SETUP_DATA);
	Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);
	if (EFI_ERROR(Status)) return Status; // abort the feature.

#if defined(CRB_SKIPPABLE_CSM_SUPPORT) && (CRB_SKIPPABLE_CSM_SUPPORT == 1)
	//
	// The function active if CSM off. skip FV for post time.
	//
	if (SetupData.CsmSupport == 0) {
		NETWORK_STACK				NetworkStackData;
		UINTN                       Instance;
		EFI_PEI_FV_HANDLE			VolumeHandle;
		UINTN						i = 0;
		struct {
			BOOLEAN						Active;
			EFI_PHYSICAL_ADDRESS        BaseAddress;
			UINT64                      Length;
			EFI_GUID                    FvName;
			EFI_GUID                    CONST *FileName;
		} SkipTblSize, SkippableFv[] = {
				//
				// A table to specify the skippable FVs.
				//
				{TRUE, 0, 0, ZERO_GUID, &gCrbSkippableCsmFvFfsGuid},  // set TRUE. default skip CSM because CsmSupport off.
				{FALSE, 0, 0, ZERO_GUID, &gCrbSkippableNetworkFvFfsGuid},
				{FALSE, 0, 0, ZERO_GUID, &gCrbSkippableTcgFvFfsGuid},
				//
				// Append more skippable Fv if need.......
				//
		};
		UINTN CONST SkipCount = sizeof(SkippableFv)/sizeof(SkipTblSize);

		VariableSize = sizeof(NETWORK_STACK);
#if defined(CRB_SKIPPABLE_NETWORK_SUPPORT) && (CRB_SKIPPABLE_NETWORK_SUPPORT == 1)
		Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"NetworkStackVar", &gEfiNetworkStackSetupGuid, NULL, &VariableSize, &NetworkStackData);
		if (!EFI_ERROR(Status) && NetworkStackData.Enable == 0) {
			for (i = 0; i < SkipCount; i++) {
				if (CompareGuid(SkippableFv[i].FileName, &gCrbSkippableNetworkFvFfsGuid)) SkippableFv[i].Active = TRUE;
			}
		}
#endif
#if defined(CRB_SKIPPABLE_TCG_SUPPORT) && (CRB_SKIPPABLE_TCG_SUPPORT == 1)
		if (SetupData.TpmSupport == 0) {
			for (i = 0; i < SkipCount; i++) {
				if (CompareGuid(SkippableFv[i].FileName, &gCrbSkippableTcgFvFfsGuid)) SkippableFv[i].Active = TRUE;
			}
		}
#endif

		for (Instance = 0; Instance < PcdGet32 (PcdPeiCoreMaxFvSupported); Instance++) {
			Status = PeiServicesFfsFindNextVolume (Instance, &VolumeHandle);

			DEBUG ((DEBUG_INFO,"<<[%a]-PeiServicesFfsFindNextVolume[%x]",gEfiCallerBaseName,Instance));

			if (!EFI_ERROR(Status)) {
				EFI_PEI_FILE_HANDLE		FileHandle;
				EFI_FV_INFO             VolumeInfo;

				Status = PeiServicesFfsGetVolumeInfo(VolumeHandle, &VolumeInfo);
				if (!EFI_ERROR(Status)) {

					DEBUG ((DEBUG_INFO,"-FvName[%g]",&VolumeInfo.FvName));
					DEBUG ((DEBUG_INFO,"-FvStart[%x]-FvSize[%lx]",VolumeInfo.FvStart,VolumeInfo.FvSize));

					//
					// Update a empty FV. Let DxeMain load EmptyFv instead skippable FV.
					//
					if (CompareGuid(&VolumeInfo.FvName, &gCrbSkippableEmptyFvGuid)) {
						for (i = 0; i < SkipCount; i++) {
							SkippableFv[i].BaseAddress = (EFI_PHYSICAL_ADDRESS) (UINTN)VolumeInfo.FvStart;
							SkippableFv[i].Length = VolumeInfo.FvSize;
						}
						DEBUG ((DEBUG_INFO,"-END[%x] >>\n",Instance));
						continue; // no other ffs behind empty FV. just skip
					}
				}

				//
				// Search FFS behind the parent FV and look for skippable FV.
				//
				FileHandle = NULL;
				do {
					Status = PeiServicesFfsFindNextFile (EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE, VolumeHandle, &FileHandle);
					if (!EFI_ERROR(Status)) {
						EFI_FFS_FILE_HEADER		*FfsHeader = FileHandle;

						//
						// Update the parent FV name and active.
						//
						for (i = 0; i < SkipCount; i++) {
							if (CompareGuid(&FfsHeader->Name, SkippableFv[i].FileName)) {
								CopyGuid(&SkippableFv[i].FvName, &VolumeInfo.FvName);

								DEBUG ((DEBUG_INFO,"-ParentFvName[%g]",&SkippableFv[i].FvName));
								DEBUG ((DEBUG_INFO,"-FvName[%g]",&FfsHeader->Name));
							}
						}
					}
				} while(FileHandle != NULL);
			}

			DEBUG ((DEBUG_INFO,"-END[%x] >>\n",Instance));
		}

		for (i = 0; i < SkipCount; i++) {

			DEBUG ((DEBUG_INFO,"<<    SkippableFv[%x]-BaseAddress[%lx]Length[%x] \n",i,SkippableFv[i].BaseAddress,SkippableFv[i].Length));
			DEBUG ((DEBUG_INFO,"               Active[%x] >>\n",SkippableFv[i].Active));
			DEBUG ((DEBUG_INFO,"               FvName [%g] >>\n",&SkippableFv[i].FvName));
			DEBUG ((DEBUG_INFO,"               FileName [%g] >>\n",SkippableFv[i].FileName));

			if (SkippableFv[i].Active == TRUE && SkippableFv[i].BaseAddress != 0 && SkippableFv[i].Length != 0 && !IsZeroGuid(&SkippableFv[i].FvName)) {
				//
				// build a empty FV. Let DxeMain load the empty FV if DxeMain attempt to load the skippable-FV.
				//
				BuildFv2Hob (
					SkippableFv[i].BaseAddress,
					SkippableFv[i].Length,
					&SkippableFv[i].FvName,
					SkippableFv[i].FileName
					);
			}
		}
	}
#endif

	return Status;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
