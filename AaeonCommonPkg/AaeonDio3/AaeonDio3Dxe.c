#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <AaeonDio3.h>

extern VOID *
EFIAPI
ZeroMem (
  OUT VOID  *Buffer,
  IN UINTN  Length
);

extern EFI_STATUS
LocateAcpiTableBySignature (
  IN      UINT32                        Signature,
  IN OUT  EFI_ACPI_DESCRIPTION_HEADER   **Table,
  IN OUT  UINTN                         *Handle
  );

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
    This function allocates memory resource for DIO device,
    put memory address to DIO ASL opregion,
    and map BIOS DIO settings into allocated memory.

    @param Event   - Event of callback
    @param Context - Context of callback.

    @retval VOID
**/

VOID UpdateDioAcpiArea (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  AAEON_DIO_GLOBAL_NVS_AREA  *AaeonDioGnvs = NULL;
  EFI_ACPI_DESCRIPTION_HEADER  *FacpTable;
  UINTN    AcpiHandle = 0;
  UINT8    *CurrPtr;
  UINT8    *DsdtPointer;
  UINT8    *Operation;
  UINT32    *Signature;
  UINT32    *Address;


  CurrPtr = NULL;
  Status = pBS->AllocatePool(EfiACPIMemoryNVS, 0x800, (VOID **)&AaeonDioGnvs);
  if (!EFI_ERROR(Status))
  {
    Status = LocateAcpiTableBySignature (
                EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE,
                (EFI_ACPI_DESCRIPTION_HEADER **)  &FacpTable,
                &AcpiHandle
                );
          
    if (!EFI_ERROR(Status))
    {
      Status = EFI_NOT_FOUND;
      //
      // Loop through the ASL looking for WDCB.
      //
      CurrPtr = (VOID*)(UINTN)((EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE *)FacpTable)->Dsdt;
      for (DsdtPointer = CurrPtr;
           DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
           DsdtPointer++
          ) {
        Signature = (UINT32 *) DsdtPointer;
        if (*Signature == SIGNATURE_32 ('W', 'D', 'C', 'B'))
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
            *Address  = (UINT32)AaeonDioGnvs;
            Status = EFI_SUCCESS;
          }
        }
      } // for (Didtpointer ...

      if (!EFI_ERROR(Status))
      {
        EFI_GUID	SetupGuid = SETUP_GUID;
        SETUP_DATA	SetupData;
        UINTN		VariableSize = sizeof(SetupData);
        UINT32		Attribute = 0;
        UINT8  i;
        UINT8 *ptr;
        UINT8 SioSourceType[] = DIO_TYPE_SIO1_GROUP_LIST;
        UINT8 Sio2SourceType[] = DIO_TYPE_SIO2_GROUP_LIST;
        UINT8 Sio3SourceType[] = DIO_TYPE_SIO3_GROUP_LIST;
        UINT8 Ec1SourceType[] = DIO_TYPE_EC1_GROUP_LIST;
        UINT8 Ec2SourceType[] = DIO_TYPE_EC2_GROUP_LIST;
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(SECOND_DIO_NUMBER) && (SECOND_DIO_NUMBER > 0)
        UINT8  j,k;
        #endif
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        UINT8  l,m;
        #endif

        ZeroMem (AaeonDioGnvs, sizeof(AAEON_DIO_GLOBAL_NVS_AREA));
        AaeonDioGnvs->DioBufferAddress  = (UINT32)AaeonDioGnvs;

	      Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);

        //
        // Start updating DIO configuration according to BIOS setup
        //

        //
        // Update DIO capability maps
        //
        #if defined(SECOND_DIO_NUMBER) && (SECOND_DIO_NUMBER > 0)
        j = (DIO_END_NUMBER + 1) / 8;
        k = (DIO_END_NUMBER + 1) % 8;
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        l = (SECOND_DIO_END_NUMBER + 1) / 8;
        m = (SECOND_DIO_END_NUMBER + 1) % 8;
        #endif
        #endif

        ptr = (UINT8 *)AaeonDioGnvs->DioInCap;
        *(UINT32 *)ptr = DIO_INPUT_CAPABLE_MAP;
        #if defined (DIO_INPUT_CAPABLE_MAP2)
        *(UINT32 *)(ptr + 4) = DIO_INPUT_CAPABLE_MAP2;
        #endif
        #if defined(SECOND_DIO_NUMBER) && (SECOND_DIO_NUMBER > 0)
        *(ptr + j) |= (UINT8)(SECOND_DIO_INPUT_CAPABLE_MAP << k);
        *(UINT32 *)(ptr + j + 1) = (SECOND_DIO_INPUT_CAPABLE_MAP >> (8 - k));
        #if defined (SECOND_DIO_INPUT_CAPABLE_MAP2)
        *(UINT8 *)(ptr + j + 4) |= (UINT8)(SECOND_DIO_INPUT_CAPABLE_MAP2 << k);
        *(ptr + j + 5) = (SECOND_DIO_INPUT_CAPABLE_MAP2 >> (8 - k));
        #endif
        #endif
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        *(ptr + l) |= (UINT8)(THIRD_DIO_INPUT_CAPABLE_MAP << m);
        *(UINT32 *)(ptr + l + 1) = (THIRD_DIO_INPUT_CAPABLE_MAP >> (8 - m));
        #if defined (THIRD_DIO_INPUT_CAPABLE_MAP2)
        *(UINT8 *)(ptr + l + 4) |= (UINT8)(THIRD_DIO_INPUT_CAPABLE_MAP2 << m);
        *(ptr + l + 5) = (THIRD_DIO_INPUT_CAPABLE_MAP2 >> (8 - m));
        #endif
        #endif

        ptr = (UINT8 *)AaeonDioGnvs->DioOutCap;
        *(UINT32 *)ptr = DIO_OUTPUT_CAPABLE_MAP;
        #if defined (DIO_OUTPUT_CAPABLE_MAP2)
        *(UINT32 *)(ptr + 4) = DIO_OUTPUT_CAPABLE_MAP2;
        #endif
        #if defined(SECOND_DIO_NUMBER) && (SECOND_DIO_NUMBER > 0)
        *(ptr + j) |= (UINT8)(SECOND_DIO_OUTPUT_CAPABLE_MAP << k);
        *(UINT32 *)(ptr + j + 1) = (SECOND_DIO_OUTPUT_CAPABLE_MAP >> (8 - k));
        #if defined (SECOND_DIO_OUTPUT_CAPABLE_MAP2)
        *(ptr + j + 4) |= (UINT8)(SECOND_DIO_OUTPUT_CAPABLE_MAP2 << k);
        *(UINT32 *)(ptr + j + 5) = (SECOND_DIO_OUTPUT_CAPABLE_MAP2 >> (8 - k));
        #endif
        #endif
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        *(ptr + l) |= (UINT8)(THIRD_DIO_OUTPUT_CAPABLE_MAP << m);
        *(UINT32 *)(ptr + l + 1) = (THIRD_DIO_OUTPUT_CAPABLE_MAP >> (8 - m));
        #if defined (THIRD_DIO_OUTPUT_CAPABLE_MAP2)
        *(ptr + l + 4) |= (UINT8)(THIRD_DIO_OUTPUT_CAPABLE_MAP2 << m);
        *(UINT32 *)(ptr + l + 5) = (THIRD_DIO_OUTPUT_CAPABLE_MAP2 >> (8 - m));
        #endif
        #endif

        ptr = (UINT8 *)AaeonDioGnvs->DioIntCap;
        *(UINT32 *)ptr = DIO_INTERRUPT_CAPABLE_MAP;
        #if defined (DIO_INTERRUPT_CAPABLE_MAP2)
        *(UINT32 *)(ptr + 4) = DIO_INTERRUPT_CAPABLE_MAP2;
        #endif
        #if defined(SECOND_DIO_NUMBER) && (SECOND_DIO_NUMBER > 0)
        *(ptr + j) |= (UINT8)(SECOND_DIO_INTERRUPT_CAPABLE_MAP << k);
        *(UINT32 *)(ptr + j + 1) = (SECOND_DIO_INTERRUPT_CAPABLE_MAP >> (8 - k));
        #if defined (SECOND_DIO_INTERRUPT_CAPABLE_MAP2)
        *(ptr + j + 4) |= (UINT8)(SECOND_DIO_INTERRUPT_CAPABLE_MAP2 << k);
        *(UINT32 *)(ptr + j + 5) = (SECOND_DIO_INTERRUPT_CAPABLE_MAP2 >> (8 - k));
        #endif
        #endif
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        *(ptr + l) |= (UINT8)(THIRD_DIO_INTERRUPT_CAPABLE_MAP << m);
        *(UINT32 *)(ptr + l + 1) = (THIRD_DIO_INTERRUPT_CAPABLE_MAP >> (8 - m));
        #if defined (THIRD_DIO_INTERRUPT_CAPABLE_MAP2)
        *(ptr + l + 4) |= (UINT8)(THIRD_DIO_INTERRUPT_CAPABLE_MAP2 << m);
        *(UINT32 *)(ptr + l + 5) = (THIRD_DIO_INTERRUPT_CAPABLE_MAP2 >> (8 - m));
        #endif
        #endif

        //
        // Update DIO source type
        //
        AaeonDioGnvs->DioSource = SetupData.DioSource;
        AaeonDioGnvs->Dio2Source = SetupData.Dio2Source;
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        AaeonDioGnvs->Dio3Source = SetupData.Dio3Source;
        #endif

        ////
        //// Check whether source should use group type instead of chip type.
        //// Because of that there is only one ASL device for those types.
        //// For example, no matter source is F81866, W83627... etc,
        //// there is only one "SIO1" device in ASL to service GPIO controll.
        ////

        ////
        //// For SIO1 group
        ////
        if (sizeof(SioSourceType) > 1)
        {
          for (i = 0; i < (sizeof(SioSourceType) - 1); i++)
          {
            if (SioSourceType[i] == AaeonDioGnvs->DioSource)
              AaeonDioGnvs->DioSource = DIO_TYPE_SIO1;
            if (SioSourceType[i] == AaeonDioGnvs->Dio2Source)
              AaeonDioGnvs->Dio2Source = DIO_TYPE_SIO1;
            // TODO: Porting may be required if 3rd DIO controller is supported.
            #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
            if (SioSourceType[i] == AaeonDioGnvs->Dio23ource)
              AaeonDioGnvs->Dio3Source = DIO_TYPE_SIO1;
            #endif
          }
        }
        ////
        //// For SIO2 group
        ////
        if (sizeof(Sio2SourceType) > 1)
        {
          for (i = 0; i < (sizeof(Sio2SourceType) - 1); i++)
          {
            if (Sio2SourceType[i] == AaeonDioGnvs->DioSource)
              AaeonDioGnvs->DioSource = DIO_TYPE_SIO2;
            if (Sio2SourceType[i] == AaeonDioGnvs->Dio2Source)
              AaeonDioGnvs->Dio2Source = DIO_TYPE_SIO2;
            // TODO: Porting may be required if 3rd DIO controller is supported.
            #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
            if (Sio2SourceType[i] == AaeonDioGnvs->Dio3Source)
              AaeonDioGnvs->Dio3Source = DIO_TYPE_SIO2;
            #endif
          }
        }
        ////
        //// For SIO3 group
        ////
        if (sizeof(Sio3SourceType) > 1)
        {
          for (i = 0; i < (sizeof(Sio3SourceType) - 1); i++)
          {
            if (Sio3SourceType[i] == AaeonDioGnvs->DioSource)
              AaeonDioGnvs->DioSource = DIO_TYPE_SIO3;
            if (Sio3SourceType[i] == AaeonDioGnvs->Dio2Source)
              AaeonDioGnvs->Dio2Source = DIO_TYPE_SIO3;
            // TODO: Porting may be required if 3rd DIO controller is supported.
            #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
            if (Sio3SourceType[i] == AaeonDioGnvs->Dio3Source)
              AaeonDioGnvs->Dio3Source = DIO_TYPE_SIO3;
            #endif
          }
        }
        ////
        //// For EC1 group
        ////
        if (sizeof(Ec1SourceType) > 1)
        {
          for (i = 0; i < (sizeof(Ec1SourceType) - 1); i++)
          {
            if (Ec1SourceType[i] == AaeonDioGnvs->DioSource)
              AaeonDioGnvs->DioSource = DIO_TYPE_EC1;
            if (Ec1SourceType[i] == AaeonDioGnvs->Dio2Source)
              AaeonDioGnvs->Dio2Source = DIO_TYPE_EC1;
            // TODO: Porting may be required if 3rd DIO controller is supported.
            #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
            if (Ec1SourceType[i] == AaeonDioGnvs->Dio3Source)
              AaeonDioGnvs->Dio3Source = DIO_TYPE_EC1;
            #endif
          }
        }
        ////
        //// For EC2 group
        ////
        if (sizeof(Ec2SourceType) > 1)
        {
          for (i = 0; i < (sizeof(Ec2SourceType) - 1); i++)
          {
            if (Ec2SourceType[i] == AaeonDioGnvs->DioSource)
              AaeonDioGnvs->DioSource = DIO_TYPE_EC2;
            if (Ec2SourceType[i] == AaeonDioGnvs->Dio2Source)
              AaeonDioGnvs->Dio2Source = DIO_TYPE_EC2;
            // TODO: Porting may be required if 3rd DIO controller is supported.
            #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
            if (Ec2SourceType[i] == AaeonDioGnvs->Dio3Source)
              AaeonDioGnvs->Dio3Source = DIO_TYPE_EC2;
            #endif
          }
        }

        //
        // Update DIO GPIO number
        //
        for (i=0; i < FIRST_DIO_NUMBER; i++)
        {
          AaeonDioGnvs->DioGpioNum[i] = SetupData.DioGpioNum[i];
          AaeonDioGnvs->Config0 |= SetupData.DioInterrupt[i];  // Enable ADIO device if any interrupt is enabled for any DIO pin.
        }
        #if SECOND_DIO_NUMBER > 0
        for (i=0; i < SECOND_DIO_NUMBER; i++)
        {
          AaeonDioGnvs->Dio2GpioNum[i] = SetupData.Dio2GpioNum[i];
          AaeonDioGnvs->Config0 |= SetupData.Dio2Interrupt[i];  // Enable ADIO device if any interrupt is enabled for any DIO pin.
        }
        #endif
        // TODO: Porting may be required if 3rd DIO controller is supported.
        #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
        for (i=0; i < THIRD_DIO_NUMBER; i++)
        {
          AaeonDioGnvs->Dio3GpioNum[i] = SetupData.Dio3GpioNum[i];
          AaeonDioGnvs->Config0 |= SetupData.Dio3Interrupt[i];  // Enable ADIO device if any interrupt is enabled for any DIO pin.
        }
        #endif
  	  }
    }
  }
  if (EFI_ERROR (Status)) {
    TRACE((-1,"ERROR: AaeonDio3: fail to UpdateDioAcpiArea. This will cause BSOD.\n"));
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
  AAEON DIO 3 DXE Entry function.

  @param[in] ImageHandle     Handle for this drivers loaded image protocol.
  @param[in] SystemTable     EFI system table.

  @retval EFI_SUCCESS        The driver installed without error.
  @retval EFI_ABORTED        The driver encountered an error and could not complete installation of
                             the ACPI tables.

**/
EFI_STATUS
EFIAPI
AaeonDio3DxeEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;

  InitAmiLib(ImageHandle, SystemTable);

  UpdateDioAcpiArea(NULL, NULL);

  return Status;
}