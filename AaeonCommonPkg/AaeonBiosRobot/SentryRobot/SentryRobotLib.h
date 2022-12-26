#include <Library/BaseLib.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>

UINT8 GetSmbusValue(UINT8 SlaveAdd, UINT8 offset);
UINT8 GetTheDioValue(UINT8  RobotNum,SETUP_DATA SetupData);
UINT8 GetTheLegacyIoValue(UINT32 IoAdd);
UINT8 GetTheIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
UINT8 GetTheWatchValue(UINT8  RobotNum,SETUP_DATA SetupData);

VOID
EFIAPI
SentryRobot(SETUP_DATA   SetupData,UINT32  Attributes);

VOID
EFIAPI
SentryRobotCheckFunction(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE *SystemTable);

VOID
EFIAPI
SentryRobotCheckBeforeLogo(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE *SystemTable);
