//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Definition of the AmiProgressReportLib library class.
*/
#ifndef __AMI_PROGRESS_REPORT_LIB__H__
#define __AMI_PROGRESS_REPORT_LIB__H__

#include <Uefi.h>

/// The library class is used by the ReFlash module to show flash process progress

/**
  Shows progress of the operation

  @param PercentComplete Operation completeness percentage (0 - 100)

  @retval  EFI_SUCCESS  Progress displayed
  @retval  Other        Error occurred during operation
*/
EFI_STATUS AmiShowProgress (
    IN UINTN PercentComplete    //(0% - 100%)
);

/**
  Shows progress of the operation along with progress messages
  In Post, the progress is shown using DisplayProgress PostManager interface 
  in QuietBoot, the progress and messages are drawn at the bottom of the screen

  @param  Title - Message box title
  @param  Message - Help message
  @param PercentComplete Operation completeness percentage (0 - 100)

  @retval  EFI_SUCCESS  Progress displayed
  @retval  Other        Error occurred during operation
*/
EFI_STATUS AmiShowProgressEx (
	IN CHAR16* Title, 
	IN CHAR16* Message, 
	IN UINTN PercentComplete //(0% - 100%)
);

#endif
//**********************************************************************
