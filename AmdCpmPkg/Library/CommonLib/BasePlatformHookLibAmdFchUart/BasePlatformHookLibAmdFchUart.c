/*****************************************************************************
 *
 * Copyright 2016 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 ******************************************************************************
 */
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/PlatformHookLib.h>

#define FCH_IOMUXx87_UART0_CTS_L_UART2_RXD_EGPIO135 0xFED80D87ul
#define FCH_IOMUXx89_UART0_RTS_L_EGPIO137        0xFED80D89ul
#define FCH_IOMUXx8A_UART0_TXD_EGPIO138          0xFED80D8Aul

#define UART1_CTS_L_UART3_TXD_EGPIO140           0xFED80D8Cul
#define FCH_IOMUXx8E_UART1_RTS_L_EGPIO142        0xFED80D8Eul
#define FCH_IOMUXx8F_UART1_TXD_EGPIO143          0xFED80D8Ful

#define FCH_AOACx40_D3_CONTROL                   0xFED81E40ul
#define FCH_AOACx56_UART0                        0x16          // UART0
#define FCH_AOACx58_UART1                        0x18          // UART1
#define FCH_AOACx62_AMBA                         0x22          // AMBA
#define AOAC_PWR_ON_DEV                          BIT3          // PwrOnDev

/**
  Performs platform specific initialization required for the CPU to access
  the hardware associated with a SerialPortLib instance.  This function does
  not intiailzie the serial port hardware itself.  Instead, it initializes
  hardware devices that are required for the CPU to access the serial port
  hardware.  This function may be called more than once.

  @retval RETURN_SUCCESS       The platform specific initialization succeeded.
  @retval RETURN_DEVICE_ERROR  The platform specific initialization could not be completed.

**/
RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )
{
  //
  // Initialize for FCH UART
  //

  // AOAC 'PwrOnDev' bit of AMBA & UART
  if (PcdGet8 (PcdFchUartPort) == 0) {
    if ((MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA) & 0x03) != 0x03) {
      MmioWrite8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA, (MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA) | AOAC_PWR_ON_DEV));
    }
    if ((MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx56_UART0) & 0x03) != 0x03) {
      MmioWrite8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx56_UART0, (MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx56_UART0) | AOAC_PWR_ON_DEV));
    }
    // Switch to UART0_CTS_L, UART0_RTS_L & UART0_TXD
    MmioWrite8 (FCH_IOMUXx87_UART0_CTS_L_UART2_RXD_EGPIO135, 0);
    MmioWrite8 (FCH_IOMUXx89_UART0_RTS_L_EGPIO137, 0);
    MmioWrite8 (FCH_IOMUXx8A_UART0_TXD_EGPIO138, 0);
  } else if (PcdGet8 (PcdFchUartPort) == 1) {
    if ((MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA) & 0x03) != 0x03) {
      MmioWrite8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA, (MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx62_AMBA) | AOAC_PWR_ON_DEV));
    }
    if ((MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx58_UART1) & 0x03) != 0x03) {
      MmioWrite8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx58_UART1, (MmioRead8 (FCH_AOACx40_D3_CONTROL + FCH_AOACx58_UART1) | AOAC_PWR_ON_DEV));
    }
    // Switch to UART1_CTS_L, UART1_RTS_L & UART1_TXD
    MmioWrite8 (UART1_CTS_L_UART3_TXD_EGPIO140, 0);
    MmioWrite8 (FCH_IOMUXx8E_UART1_RTS_L_EGPIO142, 0);
    MmioWrite8 (FCH_IOMUXx8F_UART1_TXD_EGPIO143, 0);
  } else {
    return RETURN_DEVICE_ERROR;
  }

 if (MmioRead32 ((UINTN)PcdGet64 (PcdSerialRegisterBase)) == 0xFFFFFFFF) {
     return RETURN_DEVICE_ERROR;
 }

  return RETURN_SUCCESS;
}

