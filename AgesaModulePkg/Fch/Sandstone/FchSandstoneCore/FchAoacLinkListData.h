/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD FCH AOAC SMM Data
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
 *
 */
/******************************************************************************
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
//
// Register information
//
// RegisterInfo[31:0]
//
// RegisterInfo[7:0] -  Link list ID
// RegisterInfo[31:16]-  Order in link list
// RegisterInfo[9:8] -  00: (default); 01: Make First ; 02: Make Last; 03: Make Override to the same order
//
#define FCH_AOAC_SW_VALUE          0x66
#define FCH_MAKE_FIRST             0x01
#define FCH_MAKE_LAST              0x02
#define FCH_OVERRIDE               0x03


//
//
// RegisterInfo[15:8] = Software SMI B1[7:0] for Link List ID
//
//


// Fch Controllers ID

#define FCH_HWACPI                 0x00
#define FCH_AB                     0x01
#define FCH_SD                     0x04
#define FCH_USB2                   0x07
#define FCH_USB3                   0x08
#define FCH_SATA                   0x09
#define FCH_AZALIA                 0x0A
#define FCH_EHCI1                  0x0B
#define FCH_EHCI2                  0x0C
#define FCH_EHCI3                  0x0D

// Callback Phase

#define FCH_CONTROLLER_POWER_ON    0x00
#define OEM_POWER_ON               0x10
#define FCH_CONTROLLER_ENV         0x20
#define OEM_BEFORE_PCI_INIT        0x30
#define FCH_CONTROLLER_MID         0x40
#define OEM_AFTER_PCI_INIT         0x50
#define FCH_CONTROLLER_LATE        0x60


#define FCH_CONTROLLER_D3_SAVE     0xA0
#define FCH_CONTROLLER_D0_RESTORE  0xB0
#define OEM_D3_SAVE                0xC0
#define OEM_D0_RESTORE             0xD0

#define FCH_EARLY_INIT             0x20
#define FCH_GENERIC_INIT           0x80
#define FCH_LATE_INIT              0xC0
#define FCH_LAST_INIT              0xF0

//
// Trigger Value of 0xB1 port (00 - FF)
// Link ID definition
//

// Cold Boot (Group 0x)

#define COLD_BOOT_GROUP            0x00

#define FCH_SMI_DATA_POST_ENV      (COLD_BOOT_GROUP + (FCH_CONTROLLER_ENV  >> 4))           //0x02
#define FCH_SMI_DATA_POST_MID      (COLD_BOOT_GROUP + (FCH_CONTROLLER_MID  >> 4))           //0x04
#define FCH_SMI_DATA_POST_LATE     (COLD_BOOT_GROUP + (FCH_CONTROLLER_LATE >> 4))           //0x06

// S3 enter (Group 3x)

#define S3_ENTER_GROUP             0x30

#define FCH_S3_ENTER_GENERIC       S3_ENTER_GROUP + (FCH_GENERIC_INIT >> 4)               //0x38

// S3 resume (Group 4x AND 5x)

#define S3_EXIT_GROUP_ONE          0x40
#define FCH_S3_EXIT_GEN_ONE        S3_EXIT_GROUP_ONE + (FCH_GENERIC_INIT >> 4)            //0x48
#define S3_EXIT_GROUP_TWO          0x50
#define FCH_S3_EXIT_GEN_TWO        S3_EXIT_GROUP_TWO + (FCH_GENERIC_INIT >> 4)            //0x58
#define FCH_S3_EXIT_FIRST          0x00
#define FCH_S3_EXIT_LAST           0xFFFF
// S0i3 enter (Group 7x)

#define S0I3_ENTER_GROUP           0x70

#define FCH_S0I3_ENTER_GENERIC     S0I3_ENTER_GROUP + (FCH_GENERIC_INIT >> 4)             //0x78


// S0i3 exit (Group 8x)

#define S0I3_EXIT_GROUP            0x80

#define FCH_S0I3_EXIT_GENERIC      S0I3_EXIT_GROUP + (FCH_GENERIC_INIT >> 4)              //0x88


// AOAC D0 -> D3 (Group Ax)

#define AOAC_D3_GROUP              0xA0

#define FCH_HWACPI_AOAC_D3         AOAC_D3_GROUP + FCH_HWACPI                  //0xA0
#define FCH_AB_AOAC_D3             AOAC_D3_GROUP + FCH_AB                      //0xA1
#define FCH_USB2_AOAC_D3           AOAC_D3_GROUP + FCH_USB2                    //0xA7
#define FCH_USB3_AOAC_D3           AOAC_D3_GROUP + FCH_USB3                    //0xA8
#define FCH_SATA_AOAC_D3           AOAC_D3_GROUP + FCH_SATA                    //0xA9
#define FCH_SD_AOAC_D3             AOAC_D3_GROUP + FCH_SD                      //0xAA
#define FCH_EHCI1_AOAC_D3          AOAC_D3_GROUP + FCH_EHCI1                   //0xAB
#define FCH_EHCI2_AOAC_D3          AOAC_D3_GROUP + FCH_EHCI2                   //0xAC
#define FCH_EHCI3_AOAC_D3          AOAC_D3_GROUP + FCH_EHCI3                   //0xAD

// AOAC D3 -> D0 (Group Bx)

#define AOAC_D0_GROUP              0xB0

#define FCH_HWACPI_AOAC_D0         AOAC_D0_GROUP + FCH_HWACPI                  //0xB0
#define FCH_AB_AOAC_D0             AOAC_D0_GROUP + FCH_AB                      //0xB1
#define FCH_USB2_AOAC_D0           AOAC_D0_GROUP + FCH_USB2                    //0xB7
#define FCH_USB3_AOAC_D0           AOAC_D0_GROUP + FCH_USB3                    //0xB8
#define FCH_SATA_AOAC_D0           AOAC_D0_GROUP + FCH_SATA                    //0xB9
#define FCH_SD_AOAC_D0             AOAC_D0_GROUP + FCH_SD                      //0xBA
#define FCH_EHCI1_AOAC_D0          AOAC_D0_GROUP + FCH_EHCI1                   //0xBB
#define FCH_EHCI2_AOAC_D0          AOAC_D0_GROUP + FCH_EHCI2                   //0xBC
#define FCH_EHCI3_AOAC_D0          AOAC_D0_GROUP + FCH_EHCI3                   //0xBD



//
// Register "Order" value (0000 - FFFF)
//

// reserved device order
#define FCH_RESERVED_LPC           0x02
#define FCH_RESERVED_SPI           0x03
#define FCH_RESERVED_IMC           0x05
#define FCH_RESERVED_USB           0x06
#define FCH_RESERVED_LPC_IMC       0x05
#define FCH_RESERVED_IR            0x0B
#define FCH_RESERVED_HWM           0x0C


// HWACPI
#define FCH_HWACPI_INIT_ENV_P      ((FCH_CONTROLLER_ENV << 8) + (FCH_EARLY_INIT << 4 )   +  (FCH_HWACPI << 4))                     //0x2200
#define FCH_HWACPI_INIT_ENV        ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_HWACPI << 4))                     //0x2800
//#define FCH_HWACPI_INIT_MID        ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_HWACPI << 4))                   //0x4800
#define FCH_HWACPI_INIT_LATE       ((FCH_CONTROLLER_LATE << 8) + (FCH_LAST_INIT << 4 )    +  (FCH_HWACPI << 4))                     //0x6F00

// AB
#define FCH_AB_INIT_ENV            ((FCH_CONTROLLER_ENV << 8) + (FCH_LATE_INIT << 4 )    +  (FCH_AB << 4))                         //0x2C10
//#define FCH_AB_INIT_MID            ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 )   +  (FCH_AB << 4))                     //0x4810
//#define FCH_AB_INIT_LATE           FCH_CONTROLLER_LATE       +  (FCH_AB << 1)                       //0x92
//#define FCH_AB_INIT_D3_SAVE        FCH_CONTROLLER_D3_SAVE    +  FCH_AB                              //0xB1
//#define FCH_AB_INIT_D3_RESTORE     FCH_CONTROLLER_D3_RESTORE +  FCH_AB                              //0xC1

//SD
#define FCH_SD_INIT_ENV            ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SD << 4))                         //0x2840
//#define FCH_SD_INIT_MID          ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SD << 4))                         //0x4870
//#define FCH_SD_INIT_LATE         ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SD << 4))                        //0x6870

// USB GENERIC
#define FCH_USB_INIT_ENV           ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_USB << 4))               //0x2860
#define FCH_USB_INIT_MID           ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_USB << 4))               //0x4860
#define FCH_USB_INIT_LATE          ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_USB << 4))              //0x6860

// USB2
#define FCH_USB2_INIT_ENV          ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB2 << 4))                       //0x2870
#define FCH_USB2_INIT_MID          ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB2 << 4))                       //0x4870
#define FCH_USB2_INIT_LATE         ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB2 << 4))                      //0x6870
//#define FCH_USB2_INIT_D3_SAVE      (FCH_USB2 << 4) + FCH_CONTROLLER_D3_SAVE         //0x2A
//#define FCH_USB2_INIT_D3_RESTORE   (FCH_USB2 << 4) + FCH_CONTROLLER_D3_RESTORE      //0x2B

//#define OEM_USB2_NO_BAR_INIT       (FCH_USB2 << 4) + OEM_NO_BAR_INIT                //0x23
//#define OEM_USB2_BAR_INIT          (FCH_USB2 << 4) + OEM_BAR_INIT                   //0x25
//#define OEM_USB2_D3_SAVE           (FCH_USB2 << 4) + OEM_D3_SAVE                    //0x29
//#define OEM_USB2_D3_RESTORE        (FCH_USB2 << 4) + OEM_D3_RESTORE                 //0x2C

// USB3
#define FCH_USB3_INIT_ENV          ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB3 << 4))                       //0x2880
#define FCH_USB3_INIT_MID          ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB3 << 4))                       //0x4880
#define FCH_USB3_INIT_LATE         ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_USB3 << 4))                      //0x6880

// SATA
#define FCH_SATA_INIT_ENV          ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SATA << 4))                       //0x2890
#define FCH_SATA_INIT_MID          ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SATA << 4))                       //0x4890
#define FCH_SATA_INIT_LATE         ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_SATA << 4))                      //0x6890

//AZALIA
#define FCH_AZALIA_INIT_ENV        ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_AZALIA << 4))                     //0x28A0
#define FCH_AZALIA_INIT_MID        ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_AZALIA << 4))                     //0x48A0
#define FCH_AZALIA_INIT_LATE       ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_AZALIA << 4))                    //0x68A0

//SPI
#define FCH_SPI_INIT_ENV           ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_SPI << 4))               //0x2830
//#define FCH_SPI_INIT_MID          ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_SPI << 4))              //0x4830
#define FCH_SPI_INIT_LATE          ((FCH_CONTROLLER_LATE << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_SPI << 4))              //0x6830

//IR
#define FCH_IR_INIT_ENV            ((FCH_CONTROLLER_ENV << 8) + (FCH_EARLY_INIT << 4 ) +  (FCH_RESERVED_IR << 4))                  //0x22B0

//IMC
#define FCH_IMC_INIT_ENV            ((FCH_CONTROLLER_ENV << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_IMC << 4))              //0x2850
#define FCH_IMC_INIT_MID            ((FCH_CONTROLLER_MID << 8) + (FCH_GENERIC_INIT << 4 ) +  (FCH_RESERVED_IMC << 4))              //0x4850
#define FCH_IMC_INIT_LATE           ((FCH_CONTROLLER_LATE << 8) + (FCH_LATE_INIT << 4 ) +  (FCH_RESERVED_IMC << 4))                //0x6C50

//HWM
#define FCH_HWM_INIT_LATE           ((FCH_CONTROLLER_LATE << 8) + (FCH_LATE_INIT << 4 ) +  (FCH_RESERVED_HWM << 4))                //0x6CC0

