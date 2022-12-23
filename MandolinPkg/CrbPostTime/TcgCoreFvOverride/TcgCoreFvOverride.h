//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log: $

#include <Uefi.h>
#include <Token.h>
#include <AmiTcg/Tpm20.h>
#include <AmiTcg/TrEEProtocol.h>


#if defined(SMDBG_SUPPORT_LIB) && SMDBG_SUPPORT_LIB && 0
#undef TRACE
#undef DEBUG
    #define DEBUG(Args) SMDbgTrace Args
    #define TRACE(Arguments) SMDbgTrace Arguments
    #undef  ASSERT_EFI_ERROR
    #undef  ASSERT
    #define ASSERT(Condition) if(!(Condition)) { \
        SMDbgTrace((UINTN)-1,(CHAR8*)"ASSERT in %s on %i: %s\n",__FILE__, __LINE__, #Condition);\
        }
    #define ASSERT_EFI_ERROR(Status) ASSERT(!EFI_ERROR(Status))
#endif



