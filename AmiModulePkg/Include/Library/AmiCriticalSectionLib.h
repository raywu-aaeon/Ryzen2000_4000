//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************
/** @file
  Definition of the AmiCriticalSectionLib library class.
*/
#ifndef __AMI_CRITICAL_SECTION_LIB__H__
#define __AMI_CRITICAL_SECTION_LIB__H__

typedef VOID* CRITICAL_SECTION;

EFI_STATUS CreateCriticalSection(OUT CRITICAL_SECTION *);
EFI_STATUS BeginCriticalSection(IN CRITICAL_SECTION);
EFI_STATUS EndCriticalSection(IN CRITICAL_SECTION);
EFI_STATUS DestroyCriticalSection(IN CRITICAL_SECTION);

#define AMI_BEGIN_CRITICAL_SECTION(Cs) {\
    EFI_STATUS __Status__ = BeginCriticalSection(Cs);\
    ASSERT(__Status__==EFI_SUCCESS || __Status__==EFI_ACCESS_DENIED);\
    if (EFI_ERROR(__Status__)) return __Status__;\
}

#if !defined(MDEPKG_NDEBUG)
#define AMI_END_CRITICAL_SECTION(Cs) {\
    EFI_STATUS __Status__ = EndCriticalSection(Cs);\
    ASSERT_EFI_ERROR(__Status__);\
}
#else
#define AMI_END_CRITICAL_SECTION(Cs) EndCriticalSection(Cs)
#endif

#endif
