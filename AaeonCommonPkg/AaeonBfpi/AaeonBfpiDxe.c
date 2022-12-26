#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.

#include <AaeonCommonLib.h>

extern EFI_BOOT_SERVICES		*pBS;
extern EFI_STATUS
LocateAcpiTableBySignature (
  IN      UINT32                        Signature,
  IN OUT  EFI_ACPI_DESCRIPTION_HEADER   **Table,
  IN OUT  UINTN                         *Handle
  );

extern VOID *
EFIAPI
ZeroMem (
  OUT VOID  *Buffer,
  IN UINTN  Length
);

typedef struct {
  UINT32    BfpiDataBuffer ;
  UINT8    BfpiBoardSkuId ;
  UINT8    BfpiPanelId ;
  // UINT8 Reserved[(WMI_DATA_BUFFER_LENGTH-6)]
} AAEON_BFPI_OPREGION ;

int _outp (unsigned short port, int databyte );

#pragma intrinsic(_outp)

VOID Debug_80(
UINT8	debugcode,
UINT8	Delay
){
	UINT32	Count;

	Count = Delay * 0x1FFFF;

	while(Count)
	{
		_outp(0x80, debugcode);
		Count--;
	}
}

/**
    This function allocates memory resource for BFPI
    and put memory address to BFPI ASL opregion.

    @param Event   - Event of callback
    @param Context - Context of callback.

    @retval VOID
**/

VOID UpdateBfpiAcpiArea (
    IN EFI_EVENT  Event,
    IN VOID       *Context )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  AAEON_BFPI_OPREGION  *AaeonBfpiOpRegion = NULL;
  EFI_ACPI_DESCRIPTION_HEADER  *FacpTable;
  UINTN    AcpiHandle = 0;
  UINT8    *CurrPtr;
  UINT8    *DsdtPointer;
  UINT32   *Signature;
  UINT8    *Operation;
  UINT32   *Address;
#if defined(AAEON_GPIO_ID_SUPPORT) && (AAEON_GPIO_ID_SUPPORT == 1)
  EFI_GUID   AaeonSetupGuid = AAEON_VAR_GUID;
  AAEON_SETUP_DATA    AaeonSetupData;
  UINTN    AaeonSetupVariableSize = sizeof(AaeonSetupData);
  UINT32   SetupAttribute = 0; 
#endif


  CurrPtr = NULL;
  Status = pBS->AllocatePool(EfiACPIMemoryNVS, WMI_DATA_BUFFER_LENGTH, (VOID **)&AaeonBfpiOpRegion);
  if (!EFI_ERROR(Status))
  {
    // Clean up OpRegion
    ZeroMem ((VOID *)AaeonBfpiOpRegion, WMI_DATA_BUFFER_LENGTH);

    // Allocate ACPI table and update it
    Status = LocateAcpiTableBySignature (
                EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE,
                (EFI_ACPI_DESCRIPTION_HEADER **)  &FacpTable,
                &AcpiHandle
                );

    if (!EFI_ERROR(Status))
    {
      //
      // Loop through the ASL looking for WMDB.
      //
      CurrPtr = (VOID*)(UINTN)((EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE *)FacpTable)->Dsdt;
      for (DsdtPointer = CurrPtr;
           DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
           DsdtPointer++
          ) {
        Signature = (UINT32 *) DsdtPointer;
        if (*Signature == SIGNATURE_32 ('W', 'M', 'D', 'B'))
        {
          //
          // Conditional match.  For Region Objects, the Operator will always be the
          // byte immediately before the specific name.  Therefore, subtract 1 to check
          // the Operator.
          //
          Operation = DsdtPointer - 1;
          if (*Operation == AML_EXT_REGION_OP)
          {
            Address   = (UINT32 *) (DsdtPointer + 6);
            *Address  = (UINT32)AaeonBfpiOpRegion;
            AaeonBfpiOpRegion->BfpiDataBuffer  = (UINT32)AaeonBfpiOpRegion + 0x100;  // Data buffer
#if defined(AAEON_GPIO_ID_SUPPORT) && (AAEON_GPIO_ID_SUPPORT == 1)
            Status = pRS->GetVariable( L"AaeonSetup", &AaeonSetupGuid, &SetupAttribute, &AaeonSetupVariableSize, &AaeonSetupData );
            if (!EFI_ERROR(Status)) 
            {
#if defined(AAEON_HW_BOARD_ID_SUPPORT) && (AAEON_HW_BOARD_ID_SUPPORT == 1)
              AaeonBfpiOpRegion->BfpiBoardSkuId  = AaeonSetupData.BoardId;
#endif //AAEON_BOARD_ID_SUPPORT

#if defined(AAEON_HW_PANEL_ID_SUPPORT) && (AAEON_HW_PANEL_ID_SUPPORT == 1)
              AaeonBfpiOpRegion->BfpiPanelId  = AaeonSetupData.PanelId;
#endif //AAEON_PANEL_ID_SUPPORT
            }
#endif
          }
        }
      }
    }
  }
  if (EFI_ERROR (Status)) {
    TRACE((-1,"ERROR: AaeonBfpi: fail to UpdateBfpiAcpiArea. This will cause BSOD.\n"));
    Debug_80(0xBF,1);
    Debug_80(0xEE,1);
    Debug_80(0xBF,1);
    Debug_80(0xEE,1);
    Debug_80(0xBF,1);
    Debug_80(0xEE,1);
  }
  pBS->CloseEvent(Event);
}

/**
  AAEON BFPI ACPI initialization function.

  @param[in] ImageHandle     Handle for this drivers loaded image protocol.
  @param[in] SystemTable     EFI system table.

  @retval EFI_SUCCESS        The driver installed without error.
  @retval EFI_ABORTED        The driver encountered an error and could not complete installation of
                             the ACPI tables.

**/
EFI_STATUS
EFIAPI
AaeonBfpiDxeEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;

  InitAmiLib(ImageHandle, SystemTable);

  UpdateBfpiAcpiArea(NULL, NULL);

  return EFI_SUCCESS;
}