/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD IDS Routines
 *
 * Contains AMD AGESA Integrated Debug Macros
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 311976 $   @e \$Date: 2015-01-29 13:34:44 +0800 (Thu, 29 Jan 2015) $
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

  /* Macros to aid debugging */
  /* These definitions expand to zero (0) bytes of code when disabled */

#ifndef _IDS_H_
#define _IDS_H_

#include <AMD.h>
#include <AgesaPostCode.h>

#undef FALSE
#undef TRUE
#define FALSE 0
#define TRUE  1
#define IDS_STRINGIZE(a) #a ///< for define stringize macro
#ifndef IDS_DEADLOOP
  #define IDS_DEADLOOP()    { volatile UINTN __i; __i = 1; while (__i); }
#endif

/**
 *  Make a Progress Report to the User.
 *
 *  This Macro is always enabled. The default action is to write the TestPoint value
 *  to an I/O port. The I/O port is 8 bits in size and the default address is 0x80.
 *  IBVs can change AGESA's default port by defining IDS_DEBUG_PORT to desired port
 *  in OptionsIds.h in their build tip.
 *
 *  @param[in]      TestPoint       The value for display indicating progress
 *  @param[in,out]  StdHeader       Pointer of AMD_CONFIG_PARAMS
 *
 **/

#define AGESA_TESTPOINT(TestPoint, StdHeader) IdsAgesaTestPoint ((TestPoint), (StdHeader))


#ifdef STOP_CODE
  #undef STOP_CODE
#endif
#define STOP_CODE (((UINT32)FILECODE)*0x10000ul + \
                    ((__LINE__) % 10) + (((__LINE__ / 10) % 10)*0x10) + \
                    (((__LINE__ / 100) % 10)*0x100) + (((__LINE__ / 1000) % 10)*0x1000))
/**
 * @def STOP_HERE
 *  (macro) - Causes program to halt. This is @b only for use during active debugging .
 *
 *  Causes the program to halt and display the file number of the source of the
 *  halt (displayed in decimal).
 *
 **/
#ifndef IDSOPT_NDEBUG
  #define STOP_HERE IdsAssert (STOP_CODE);
#else
  #define STOP_HERE  STOP_HERE_Needs_To_Be_Removed //"WARNING: Debug code needs to be removed for production builds."
#endif

/**
 * @def ASSERT
 *  Test an assertion that the given statement is True.
 *
 *  The statement is evaluated to a boolean value. If the statement is True,
 *  then no action is taken (no error). If the statement is False, a error stop
 *  is generated to halt the program. Used for testing for fatal errors that
 *  must be resolved before production. This is used to do parameter checks,
 *  bounds checking, range checks and 'sanity' checks.
 *
 * @param[in]   conditional    Assert that evaluating this conditional results in TRUE.
 *
 **/
#ifndef IDSOPT_NDEBUG
  #ifndef ASSERT
    #define ASSERT(conditional) ((conditional) ? 0 : IdsAssert (STOP_CODE));
  #endif
#else
  #define ASSERT(conditional)
#endif

/**
 * @def DEBUG_CODE
 * Make the code active when IDSOPT_DEBUG_CODE_ENABLED enable
 *
 */
#ifndef IDSOPT_NDEBUG
  #ifndef DEBUG_CODE
    #define  DEBUG_CODE(Code) Code
  #endif
#else
  #define  DEBUG_CODE(Code)
#endif

/**
 * @def IDS_ERROR_TRAP
 * Trap AGESA Error events with stop code display.
 *
 * Works similarly to use of "ASSERT (FALSE);"
 *
 */
#ifndef IDSOPT_NDEBUG
  #define IDS_ERROR_TRAP  IdsAssert (STOP_CODE)
#else
  #define IDS_ERROR_TRAP
#endif


 //Note a is from 0 to 63
#define DEBUG_PRINT_SHIFT(a)   ((UINT64)1 << a)
//If you change the Bitmap definition below, please change the Hash in ParseFilter of hdtout2008.pl accordingly
//Memory Masks
#define MEM_SETREG                                  DEBUG_PRINT_SHIFT (0)
#define MEM_GETREG                                  DEBUG_PRINT_SHIFT (1)
#define MEM_FLOW                                    DEBUG_PRINT_SHIFT (2)
#define MEM_STATUS                                  DEBUG_PRINT_SHIFT (3)
#define MEM_UNDEF_BF                                DEBUG_PRINT_SHIFT (4)
#define MEM_PMU                                     DEBUG_PRINT_SHIFT (5)
#define MEMORY_TRACE_RSV3                           DEBUG_PRINT_SHIFT (6)
#define MEMORY_TRACE_RSV4                           DEBUG_PRINT_SHIFT (7)
#define MEMORY_TRACE_RSV5                           DEBUG_PRINT_SHIFT (8)
#define MEMORY_TRACE_RSV6                           DEBUG_PRINT_SHIFT (9)

//CPU Masks
#define CPU_TRACE                                   DEBUG_PRINT_SHIFT (10)
#define CPU_TRACE_RSV1                              DEBUG_PRINT_SHIFT (11)
#define CPU_TRACE_RSV2                              DEBUG_PRINT_SHIFT (12)
#define CPU_TRACE_RSV3                              DEBUG_PRINT_SHIFT (13)
#define CPU_TRACE_RSV4                              DEBUG_PRINT_SHIFT (14)
#define CPU_TRACE_RSV5                              DEBUG_PRINT_SHIFT (15)
#define CPU_TRACE_RSV6                              DEBUG_PRINT_SHIFT (16)
#define CPU_TRACE_RSV7                              DEBUG_PRINT_SHIFT (17)
#define CPU_TRACE_RSV8                              DEBUG_PRINT_SHIFT (18)
#define CPU_TRACE_RSV9                              DEBUG_PRINT_SHIFT (19)

//GNB Masks
#define GNB_TRACE                                   DEBUG_PRINT_SHIFT (20)
#define PCIE_MISC                                   DEBUG_PRINT_SHIFT (21)
#define PCIE_PORTREG_TRACE                          DEBUG_PRINT_SHIFT (22)
#define PCIE_HOSTREG_TRACE                          DEBUG_PRINT_SHIFT (23)
#define GNB_TRACE_RSV2                              DEBUG_PRINT_SHIFT (24)
#define NB_MISC                                     DEBUG_PRINT_SHIFT (25)
#define GNB_TRACE_RSV3                              DEBUG_PRINT_SHIFT (26)
#define GFX_MISC                                    DEBUG_PRINT_SHIFT (27)
#define NB_SMUREG_TRACE                             DEBUG_PRINT_SHIFT (28)
#define GNB_TRACE_RSV1                              DEBUG_PRINT_SHIFT (29)

//Topology Masks
#define TOPO_TRACE                                  DEBUG_PRINT_SHIFT (30)
// #define TOPO_TRACE_RSV1                             DEBUG_PRINT_SHIFT (31)
// #define TOPO_TRACE_RSV2                             DEBUG_PRINT_SHIFT (32)
// #define TOPO_TRACE_RSV3                             DEBUG_PRINT_SHIFT (33)
// #define TOPO_TRACE_RSV4                             DEBUG_PRINT_SHIFT (34)
// #define TOPO_TRACE_RSV5                             DEBUG_PRINT_SHIFT (35)
// #define TOPO_TRACE_RSV6                             DEBUG_PRINT_SHIFT (36)
// #define TOPO_TRACE_RSV7                             DEBUG_PRINT_SHIFT (37)
// #define TOPO_TRACE_RSV8                             DEBUG_PRINT_SHIFT (38)
// #define TOPO_TRACE_RSV9                             DEBUG_PRINT_SHIFT (39)
#define PSP_TRACE                                   DEBUG_PRINT_SHIFT (31)

//FCH Masks
#define FCH_TRACE                                    DEBUG_PRINT_SHIFT (40)
#define FCH_TRACE_RSV1                               DEBUG_PRINT_SHIFT (41)
#define FCH_TRACE_RSV2                               DEBUG_PRINT_SHIFT (42)
#define FCH_TRACE_RSV3                               DEBUG_PRINT_SHIFT (43)
#define FCH_TRACE_RSV4                               DEBUG_PRINT_SHIFT (44)
#define FCH_TRACE_RSV5                               DEBUG_PRINT_SHIFT (45)
#define FCH_TRACE_RSV6                               DEBUG_PRINT_SHIFT (46)
#define FCH_TRACE_RSV7                               DEBUG_PRINT_SHIFT (47)
#define FCH_TRACE_RSV8                               DEBUG_PRINT_SHIFT (48)
#define FCH_TRACE_RSV9                               DEBUG_PRINT_SHIFT (49)

//Other Masks
#define MAIN_FLOW                                    DEBUG_PRINT_SHIFT (50)
#define EVENT_LOG                                    DEBUG_PRINT_SHIFT (51)
#define PERFORMANCE_ANALYSE                          DEBUG_PRINT_SHIFT (52)

//Ids Masks
#define IDS_TRACE                                    DEBUG_PRINT_SHIFT (53)
#define BVM_TRACE                                    DEBUG_PRINT_SHIFT (54)
#define IDS_TRACE_RSV2                               DEBUG_PRINT_SHIFT (55)
#define IDS_TRACE_RSV3                               DEBUG_PRINT_SHIFT (56)

//S3
#define S3_TRACE                                     DEBUG_PRINT_SHIFT (57)

//Library function to read/write PCI/MSR registers
#define LIB_PCI_RD                                   DEBUG_PRINT_SHIFT (58)
#define LIB_PCI_WR                                   DEBUG_PRINT_SHIFT (59)

//AGESA test points
#define TEST_POINT                                   DEBUG_PRINT_SHIFT (60)

//Reserved for platform log
#define PLAT_RSV1                                    DEBUG_PRINT_SHIFT (61)
#define PLAT_RSV2                                    DEBUG_PRINT_SHIFT (62)
#define PLAT_RSV3                                    DEBUG_PRINT_SHIFT (63)

#ifndef IDSOPT_NDEBUG
  #define IDS_HDT_CONSOLE    IdsLibDebugPrint
#else
#endif

#define IDS_HDT_CONSOLE_PSP_TRACE(...) IDS_HDT_CONSOLE(PSP_TRACE, __VA_ARGS__)
// #define TRACE_MASK_ALL (0xFFFFFFFFFFFFFFFFull)
// #ifndef IDS_DEBUG_PRINT_MASK
//   #define IDS_DEBUG_PRINT_MASK (GNB_TRACE_DEFAULT  | CPU_TRACE_ALL | MEMORY_TRACE_DEFAULT | TOPO_TRACE_ALL | FCH_TRACE_ALL | MAIN_FLOW | TEST_POINT)
// #endif

// /// if no specific define INIT & EXIT will be NULL
// #define IDS_HDT_CONSOLE_INIT(x)
// #define IDS_HDT_CONSOLE_EXIT(x)

// /// AGESA tracing service
// #if IDSOPT_TRACING_ENABLED == TRUE
//   #ifdef VA_ARGS_SUPPORTED
//     #if IDSOPT_C_OPTIMIZATION_DISABLED == TRUE
//       #define IDS_HDT_CONSOLE(f, s, ...)        AmdIdsDebugPrint (f, s, __VA_ARGS__)
//     #else
//       #pragma warning(disable: 4127)
//       #define IDS_HDT_CONSOLE(f, s, ...)        if      (f == MEM_FLOW) AmdIdsDebugPrintMem (s, __VA_ARGS__); \
//                                                  else if (f == CPU_TRACE) AmdIdsDebugPrintCpu (s, __VA_ARGS__); \
//                                                   else if (f == TOPO_TRACE) AmdIdsDebugPrintTopology (s, __VA_ARGS__); \
//                                                   else if (f == GNB_TRACE) AmdIdsDebugPrintGnb (s, __VA_ARGS__); \
//                                                  else AmdIdsDebugPrint (f, s, __VA_ARGS__)
//     #endif
//   #else
//     #define IDS_HDT_CONSOLE    AmdIdsDebugPrint
//   #endif
//   #define CONSOLE            AmdIdsDebugPrintAll
//   #define IDS_HDT_CONSOLE_DEBUG_CODE(Code)  Code
//   #define IDS_TIMEOUT_CTL(t)                IdsMemTimeOut (t)
// #else
//   // #define IDS_HDT_CONSOLE           1 ? (VOID) 0 : AmdIdsDebugPrint
//   #define IDS_HDT_CONSOLE
//   #define IDS_HDT_CONSOLE_DEBUG_CODE(Code)
//   #define CONSOLE   CONSOLE_Needs_To_Be_Removed_For_Production_Build //"WARNING: CONSOLE needs to be removed for production builds."
//   #define IDS_TIMEOUT_CTL(t)
// #endif

// /// Macros for serial port tracing
// #ifdef IDSOPT_SERIAL_PORT
//   #define IDS_SERIAL_PORT IDSOPT_SERIAL_PORT
// #endif

// #ifndef IDS_SERIAL_PORT
//   #define IDS_SERIAL_PORT 0x3F8
// #endif

// // Macros for redirect IO tracing
// #ifdef IDSOPT_DEBUG_PRINT_IO_PORT
//   #define IDS_DEBUG_PRINT_IO_PORT IDSOPT_DEBUG_PRINT_IO_PORT
// #endif

// #ifndef IDS_DEBUG_PRINT_IO_PORT
//   #define IDS_DEBUG_PRINT_IO_PORT 0x80
// #endif

// #define IDS_DPRAM_BASE 0
// #define IDS_DPRAM_SIZE 0
// ///Default policy, shift the old data when buffer full
// #define IDS_DPRAM_STOP_LOGGING_WHEN_BUFFER_FULL FALSE
// #if IDSOPT_TRACING_CONSOLE_RAM  == TRUE
//   #ifdef IDSOPT_DPRAM_BASE
//     #undef IDS_DPRAM_BASE
//     #define IDS_DPRAM_BASE  IDSOPT_DPRAM_BASE
//   #else
//     #error "Debug Print Ram Base not specified, please define IDSOPT_DPRAM_BASE in optionsids.h"
//   #endif

//   #ifdef IDSOPT_DPRAM_SIZE
//     #undef IDS_DPRAM_SIZE
//     #define IDS_DPRAM_SIZE  IDSOPT_DPRAM_SIZE
//   #else
//     #error "Debug Print Ram size not specified, please define IDSOPT_DPRAM_SIZE in optionsids.h"
//   #endif

//   #ifdef IDSOPT_DPRAM_STOP_LOGGING_WHEN_BUFFER_FULL
//     #define IDS_DPRAM_STOP_LOGGING_WHEN_BUFFER_FULL IDSOPT_DPRAM_STOP_LOGGING_WHEN_BUFFER_FULL
//   #endif
// #endif
// /**
//  *  Macros to add HDT OUT
//  *
//  *  The default minimal action is to do nothing and there is no any code to increase.
//  *  For debug environments, the debug information can be displayed in HDT or other
//  *  devices.
//  *
//  **/
// #if IDSOPT_TRACING_CONSOLE_HDTOUT == TRUE
//   #undef IDS_HDT_CONSOLE_INIT
//   #undef IDS_HDT_CONSOLE_EXIT
//   #define IDS_HDT_CONSOLE_INIT(x)           AmdIdsDpHdtOutInit (x)
//   #define IDS_HDT_CONSOLE_EXIT(x)           AmdIdsDpHdtOutExit (x)
//   #define IDS_HDT_CONSOLE_S3_EXIT(x)        AmdIdsDpHdtOutS3Exit (x)
//   #define IDS_HDT_CONSOLE_S3_AP_EXIT(x)     AmdIdsDpHdtOutS3ApExit (x)

//   #define IDS_HDT_CONSOLE_FLUSH_BUFFER(x)   AmdIdsDpHdtOutBufferFlush (x)
//   #define IDS_HDT_CONSOLE_ASSERT(x)   AmdIdsDebugPrintAssert (x)
//   #define IDS_FUNCLIST_ADDR                 ScriptFuncList
//   #define IDS_FUNCLIST_EXTERN()             extern SCRIPT_FUNCTION ScriptFuncList[]
// #else
//   #define IDS_HDT_CONSOLE_S3_EXIT(x)
//   #define IDS_HDT_CONSOLE_S3_AP_EXIT(x)
//   #define IDS_HDT_CONSOLE_FLUSH_BUFFER(x)
//   #define IDS_HDT_CONSOLE_ASSERT(x)
//   #define IDS_FUNCLIST_ADDR                 NULL
//   #define IDS_FUNCLIST_EXTERN()
// #endif

// #if IDSOPT_TRACING_ENABLED == TRUE
//   #ifdef IDSOPT_CUSTOMIZE_TRACING_SERVICE
//     #undef  IDS_HDT_CONSOLE
//     #define IDS_HDT_CONSOLE        IDSOPT_CUSTOMIZE_TRACING_SERVICE
//   #endif
//   #ifdef IDSOPT_CUSTOMIZE_TRACING_SERVICE_INIT
//     #undef IDS_HDT_CONSOLE_INIT
//     #define IDS_HDT_CONSOLE_INIT(x)           IDSOPT_CUSTOMIZE_TRACING_SERVICE_INIT (x)
//   #endif
//   #ifdef IDSOPT_CUSTOMIZE_TRACING_SERVICE_EXIT
//     #undef IDS_HDT_CONSOLE_EXIT
//     #define IDS_HDT_CONSOLE_EXIT(x)           IDSOPT_CUSTOMIZE_TRACING_SERVICE_EXIT (x)
//   #endif
// #endif

// #define IDS_TRACE_SHOW_BLD_OPT_CFG  IDSOPT_TRACE_USER_OPTIONS

// #if IDSOPT_PERF_ANALYSIS == TRUE
//   #include "IdsPerf.h"
//   #ifdef STOP_CODE
//     #undef STOP_CODE
//   #endif
//   #define STOP_CODE (((UINT32)FILECODE)*0x10000ul + \
//                         ((__LINE__) % 10) + (((__LINE__ / 10) % 10)*0x10) + \
//                         (((__LINE__ / 100) % 10)*0x100) + (((__LINE__ / 1000) % 10)*0x1000))

//   #define IDS_PERF_TIMESTAMP(ID, StdHeader)  IdsPerfTimestamp (STOP_CODE, ID, (StdHeader))
//   #define IDS_PERF_ANALYSE(StdHeader)   IdsPerfAnalyseTimestamp (StdHeader)
// #else
//   #define IDS_PERF_TIMESTAMP(ID, StdHeader)
//   #define IDS_PERF_ANALYSE(StdHeader)
// #endif


VOID
IdsAgesaTestPoint (
  IN      AGESA_POST_CODE TestPoint,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

/**
 *  IDS Backend Function for ASSERT
 *
 * Halt execution with stop code display.  Stop Code is displayed on port 80, with rotation so that
 * it is visible on 8, 16, or 32 bit display.  The stop code is alternated with 0xDEAD on the display,
 * to help distinguish the stop code from a post code loop.
 * Additional features may be available if using simulation.
 *
 * @param[in]     FileCode    File code(define in FILECODE.h) mix with assert Line num.
 *
 * @retval         TRUE     No error
**/
BOOLEAN
IdsAssert (
  IN      UINT32 FileCode
  );

/**
 * The engine code for ASSERT MACRO
 *
 * Halt execution with stop code display.  Stop Code is displayed on port 80, with rotation so that
 * it is visible on 8, 16, or 32 bit display.  The stop code is alternated with 0xDEAD on the display,
 * to help distinguish the stop code from a post code loop.
 * Additional features may be available if using simulation.
 *
 * @param[in]     FileCode    File code(define in FILECODE.h) mix with assert Line num.
 *
 */
BOOLEAN
IdsErrorStop (
  IN      UINT32 FileCode
  );

VOID
IdsLibDebugPrint (
  IN      UINT64      Flag,
  IN      CONST CHAR8 *Format,
  IN      ...
  );
#if 0
VOID
AmdIdsDpHdtOutInit (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
AmdIdsDpHdtOutExit (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
AmdIdsDpHdtOutS3Exit (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
AmdIdsDpHdtOutS3ApExit (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
AmdIdsDebugPrint (
  IN       UINT64      Flag,
  IN       CONST CHAR8 *Format,
  IN       ...
  );

VOID
AmdIdsDebugPrintTopology (
  IN      CONST CHAR8 *Format,
  IN      ...
  );

VOID
AmdIdsDebugPrintCpu (
  IN      CONST CHAR8 *Format,
  IN      ...
  );

VOID
AmdIdsDebugPrintMem (
  IN      CONST CHAR8 *Format,
  IN      ...
  );

VOID
AmdIdsDebugPrintGnb (
  IN      CONST CHAR8 *Format,
  IN      ...
  );

VOID
AmdIdsDebugPrintAll (
  IN      CONST CHAR8 *Format,
  IN      ...
  );

VOID
AmdIdsDpHdtOutBufferFlush (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
IdsMemTimeOut (
  IN OUT   VOID *DataPtr
  );

VOID
IdsAgesaTestPoint (
  IN      AGESA_POST_CODE TestPoint,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

/**
 *  IDS Backend Function for ASSERT
 *
 * Halt execution with stop code display.  Stop Code is displayed on port 80, with rotation so that
 * it is visible on 8, 16, or 32 bit display.  The stop code is alternated with 0xDEAD on the display,
 * to help distinguish the stop code from a post code loop.
 * Additional features may be available if using simulation.
 *
 * @param[in]     FileCode    File code(define in FILECODE.h) mix with assert Line num.
 *
 * @retval         TRUE     No error
**/
BOOLEAN
IdsAssert (
  IN      UINT32 FileCode
  );

/**
 * The engine code for ASSERT MACRO
 *
 * Halt execution with stop code display.  Stop Code is displayed on port 80, with rotation so that
 * it is visible on 8, 16, or 32 bit display.  The stop code is alternated with 0xDEAD on the display,
 * to help distinguish the stop code from a post code loop.
 * Additional features may be available if using simulation.
 *
 * @param[in]     FileCode    File code(define in FILECODE.h) mix with assert Line num.
 *
 */
BOOLEAN
IdsErrorStop (
  IN      UINT32 FileCode
  );

VOID
IdsDelay (
  VOID
);

AGESA_STATUS
IdsPerfTimestamp (
  IN       UINT32 LineInFile,
  IN       UINT32 Description,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
IdsPerfAnalyseTimestamp (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

#if IDSOPT_IDS_ENABLED == FALSE
  #undef IEM_SKIP_CODE
  #undef IEM_INSERT_CODE
#endif
#ifndef IEM_SKIP_CODE
  #define IEM_SKIP_CODE(L)
#endif
#ifndef IEM_INSERT_CODE
  #define IEM_INSERT_CODE(L, Fn, Parm)
#endif
#endif
#endif // _IDS_H_

