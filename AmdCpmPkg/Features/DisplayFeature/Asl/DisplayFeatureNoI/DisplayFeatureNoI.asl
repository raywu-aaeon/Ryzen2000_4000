/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

DefinitionBlock (
    "DisplayFeatureNoI.aml",        // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMDFNOI",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_DISPLAY_FEATURE_ASL

    External(\_SB.PCI0.PB2.VGA.AFN0, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN1, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN2, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN3, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN4, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN5, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN6, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN7, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN8, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFNC, MethodObj)

    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC, MethodObj)

    Method(AFN0, 0, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN0)) {
            \_SB.PCI0.PB2.VGA.AFN0()
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0()
        }
    }
    Method(AFN1, 1, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN1)) {
            \_SB.PCI0.PB2.VGA.AFN1(Arg0)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1(Arg0)
        }
    }
    Method(AFN2, 2, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN2)) {
            \_SB.PCI0.PB2.VGA.AFN2(Arg0, Arg1)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2(Arg0, Arg1)
        }
    }
    Method(AFN3, 2, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN3)) {
            \_SB.PCI0.PB2.VGA.AFN3(Arg0, Arg1)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3(Arg0, Arg1)
        }
    }
    Method(AFN4, 1, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN4)) {
            \_SB.PCI0.PB2.VGA.AFN4(Arg0)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4(Arg0)
        }
    }
    Method(AFN5, 0, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN5)) {
            \_SB.PCI0.PB2.VGA.AFN5()
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5()
        }
    }
    Method(AFN6, 0, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN6)) {
            \_SB.PCI0.PB2.VGA.AFN6()
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6()
        }
    }
    Method(AFN7, 1, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN7)) {
            \_SB.PCI0.PB2.VGA.AFN7(Arg0)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7(Arg0)
        }
    }
    Method(AFN8, 0, Serialized)
    {
        // Goes to DGPU's ATIF function when HPD is happened
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN8)) {
            \_SB.PCI0.PB2.VGA.AFN8()
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8()
        }
    }
    Method(AFNC, 2, Serialized)
    {
        If(CondRefOf(\_SB.PCI0.PB2.VGA.AFNC)) {
            \_SB.PCI0.PB2.VGA.AFNC(Arg0, Arg1)
        }
        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC)) {
            \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC(Arg0, Arg1)
        }
    }

}