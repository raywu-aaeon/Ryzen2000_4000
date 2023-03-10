/* $NoKeywords:$ */
/**
 * @file
 *
 * Describes compiler dependencies - to support several compile time environments
 *
 * Contains compiler environment porting descriptions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Includes
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 **/

#ifndef _PORTING_H_
#define _PORTING_H_

#pragma warning(push)
#if defined (_MSC_VER)
  #pragma warning(disable: 4103 4001 4324)
  // -----------------------------------------------------------------------
  //   Define a code_seg MACRO
  //
  #define MAKE_AS_A_STRING(arg) #arg

  #define CODE_GROUP(arg) __pragma (code_seg (MAKE_AS_A_STRING (.t##arg)))

  #define RDATA_GROUP(arg) __pragma (const_seg (MAKE_AS_A_STRING (.d##arg)))

  //#include <intrin.h>  // MS has built-in functions

  #if _MSC_VER < 900
    // -----------------------------------------------------------------------
    //    Assume MSVC 1.52C (16-bit)
    //
    //    NOTE: When using MSVC 1.52C use the following command line:
    //
    //       CL.EXE /G3 /AL /O1i /Fa <FILENAME.C>
    //
    //    This will produce 32-bit code in USE16 segment that is optimized for code
    //    size.
    typedef void          VOID;

    // Create the universal 32, 16, and 8-bit data types
    typedef unsigned long   UINTN;
    typedef          long   INT32;
    typedef unsigned long   UINT32;
    typedef          int    INT16;
    typedef unsigned int    UINT16;
    typedef          char   INT8;
    typedef unsigned char   UINT8;
    typedef          char   CHAR8;
    typedef unsigned short  CHAR16;

    /// struct for 16-bit environment handling of 64-bit value
    typedef struct _UINT64 {
      IN OUT  UINT32 lo;      ///< lower 32-bits of 64-bit value
      IN OUT  UINT32 hi;      ///< highest 32-bits of 64-bit value
    } UINT64;

    // Create the Boolean type
    #define TRUE  1
    #define FALSE 0
    typedef unsigned char BOOLEAN;

    #define CONST const
    #define STATIC static
    #define VOLATILE volatile
    #define CALLCONV __pascal
    #define ROMDATA __based( __segname( "_CODE" ) )
    #define _16BYTE_ALIGN   __declspec(align(16))
    #define _8BYTE_ALIGN   __declspec(align(8))
    #define _4BYTE_ALIGN   __declspec(align(4))
    #define _2BYTE_ALIGN   __declspec(align(2))
    #define _1BYTE_ALIGN   __declspec(align(1))

    // Force tight packing of structures
    // Note: Entire AGESA (Project / Solution) will be using pragma pack 1
    #pragma warning( disable : 4103 ) // Disable '#pragma pack' in .h warning
//    #pragma pack(1)

    //   Disable WORD->BYTE automatic conversion warnings.  Example:
    //   BYTE LocalByte;
    //   void MyFunc(BYTE val);
    //
    //   MyFunc(LocalByte*2+1); // Warning, automatic conversion
    //
    //   The problem is any time math is performed on a BYTE, it is converted to a
    //   WORD by MSVC 1.52c, and then when it is converted back to a BYTE, a warning
    //   is generated.  Disable warning C4761
    #pragma warning( disable : 4761 )

  #else
    // -----------------------------------------------------------------------
    //   Assume a 32-bit MSVC++
    //
    // Disable the following warnings:
    // 4100 - 'identifier' : unreferenced formal parameter
    // 4276 - 'function' : no prototype provided; assumed no parameters
    // 4214 - non standard extension used : bit field types other than int
    // 4001 - nonstandard extension 'single line comment' was used
    // 4142 - benign redefinition of type for following declaration
    //      - typedef char    INT8
    #if defined (_M_IX86)
      #pragma warning (disable: 4100 4276 4214 4001 4142 4305 4306)

      #ifndef VOID
        typedef void VOID;
      #endif
    // Create the universal 32, 16, and 8-bit data types
      #ifndef UINTN
        typedef unsigned __w64 UINTN;
      #endif
      typedef          __int64 INT64;
      typedef unsigned __int64 UINT64;
      typedef          int   INT32;
      typedef unsigned int   UINT32;
      typedef          short INT16;
      typedef unsigned short UINT16;
      typedef          char  INT8;
      typedef unsigned char  UINT8;
      typedef          char  CHAR8;
      typedef unsigned short CHAR16;

    // Create the Boolean type
      //#ifndef TRUE
      #undef TRUE
      #define TRUE  1
      //#endif
      //#ifndef FALSE
      #undef FALSE
      #define FALSE 0
      //#endif
      typedef unsigned char BOOLEAN;

      // Force tight packing of structures
      // Note: Entire AGESA (Project / Solution) will be using pragma pack 1
//      #pragma pack(1)

      #define CONST const
      #define STATIC static
      #define VOLATILE volatile
      #define CALLCONV
      #define ROMDATA
      #define _16BYTE_ALIGN   __declspec(align(64))
      #define _8BYTE_ALIGN   __declspec(align(8))
      #define _4BYTE_ALIGN   __declspec(align(4))
      #define _2BYTE_ALIGN   __declspec(align(2))
      #define _1BYTE_ALIGN   __declspec(align(1))
      //Support for variadic macros was introduced in Visual C++ 2005.
      #if _MSC_VER >= 1400
        #define VA_ARGS_SUPPORTED
      #endif
      // 64 bit of compiler
    #else
      #pragma warning (disable: 4100 4276 4214 4001 4142 4305 4306 4366)

      #ifndef VOID
        typedef void VOID;
      #endif
      // Create the universal 32, 16, and 8-bit data types
      #ifndef UINTN
        typedef unsigned __int64 UINTN;
      #endif
      typedef          __int64 INT64;
      typedef unsigned __int64 UINT64;
      typedef          int   INT32;
      typedef unsigned int   UINT32;
      typedef          short INT16;
      typedef unsigned short UINT16;
      typedef          char  INT8;
      typedef unsigned char  UINT8;
      typedef          char  CHAR8;
      typedef unsigned short CHAR16;

      // Create the Boolean type
      //#ifndef TRUE
      #undef TRUE
      #define TRUE  1
      //#endif
      //#ifndef FALSE
      #undef FALSE
      #define FALSE 0
      //#endif
      typedef unsigned char BOOLEAN;
      #define _16BYTE_ALIGN   __declspec(align(16))
      #define _8BYTE_ALIGN   __declspec(align(8))
      #define _4BYTE_ALIGN   __declspec(align(4))
      #define _2BYTE_ALIGN   __declspec(align(2))
      #define _1BYTE_ALIGN   __declspec(align(1))
      // Force tight packing of structures
      // Note: Entire AGESA (Project / Solution) will be using pragma pack 1
//      #pragma pack(1)

      #define CONST const
      #define STATIC static
      #define VOLATILE volatile
      #define CALLCONV
      #define ROMDATA
    #endif
  #endif
  // -----------------------------------------------------------------------
  // End of MS compiler versions


#elif defined __GNUC__

  #define IN
  #define OUT
  #define STATIC static
  #define VOLATILE volatile
  #define TRUE 1
  #define FALSE 0
  #define CONST const
  #define ROMDATA
  #define CALLCONV
  #define _16BYTE_ALIGN __attribute__ ((aligned (16)))
  #define _8BYTE_ALIGN __attribute__ ((aligned (8)))
  #define _4BYTE_ALIGN __attribute__ ((aligned (4)))
  #define _2BYTE_ALIGN __attribute__ ((aligned (2)))
  #define _1BYTE_ALIGN __attribute__ ((aligned (1)))

  typedef unsigned char  BOOLEAN;
  typedef   signed char  INT8;
  typedef   signed short INT16;
  typedef   signed long  INT32;
  typedef          char  CHAR8;
  typedef unsigned char  UINT8;
  typedef unsigned short UINT16;
  typedef unsigned long  UINT32;
  typedef unsigned long  UINTN;
  typedef unsigned long  long UINT64;
  typedef void VOID;
  //typedef unsigned long  size_t;
  typedef unsigned int   uintptr_t;
  #define CODE_GROUP(arg)
  #define RDATA_GROUP(arg)

  //#include <intrin.h>                   // MingW-w64 library header
  #include <MyIntrinsics.h>               // AGESA temp file for GCC until support is added to MinGW

#else
  // -----------------------------------------------------------------------
  // Unknown or unsupported compiler - use for ARM compiler
  //
  #include <MyIntrinsics.h>               // AGESA temp file for ARM GCC
#endif



// -----------------------------------------------------------------------
// Common definitions for all compilers
//

//Support forward reference construct
#define AGESA_FORWARD_DECLARATION(x) typedef struct _##x x

#undef NULL
#define NULL              0

// The following are use in conformance to the UEFI style guide
#define IN
#define OUT

#endif // _PORTING_H_

