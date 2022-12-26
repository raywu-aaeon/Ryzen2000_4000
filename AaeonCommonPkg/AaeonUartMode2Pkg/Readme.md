Table of content
1. [AAEON UART MODE 2](#AAEON-UART-MODE-2)
2. [FILES NOTE](#FILES-NOTE)
3. [DEPENDENCIES](#DEPENDENCIES)
4. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)
5. [MODULE IMPROVEMENT NOTE](#MODULE-IMPROVEMENT-NOTE)

AAEON UART MODE 2
================================

## Goal

* Allow use to easily programing "UART Mode Function" by setup items.

## Use Case

* System support UART mode includes RS232/RS422/RS485 which can be programed by setup items.
* DVT motherboard changed circuit of UART mode, RD can simply modify setup default to support new configuration.
* Customer request to change UART mode default value, AE can modify setup default setting by AMI BCP.

## This module

* Support 2 type of UART mode transceiver with setup item "UART Mode Transceiver".
* Support 6 set of "UART Mode" setup items. Each set is capable for
   * Select "UART Source" to choose the SIO chip of UART
   * Select "GPIO Source" to choose the SIO/DIO chip of UART control GPIO
   * Select "UART UID Number" to fill the target UART number which support UART mode
   * Select "GPIO 0/1/2 Number" to fill the number of GPIO which use for control UART mode
* For porting -
   * Support configuring setup default by token.

FILES NOTE
================================

## .sdl

* AaeonUartMode2Pkg.sdl - Main configurations to this module.

## .c

* AaeonUartMode2.c - Main function for UART mode initialization
* AaeonUartMode2Callback.c - Initial UART mode when user change the UART mode setting.
* AaeonUartMode2LoadDefaults.c - Override the dynamic UART mode default by setup items.
* AaeonUartMode2Pkg.c - Initial UART mode at the first boot after clear CMOS.

## .h
* AaeonUartMode2.h - Define the prototype of UART mode function.

DEPENDENCIES
================================

* N/A

PROJECT PORTING NOTE
================================

## General

* Enable master TOKEN "AaeonUartMode2Pkg_SUPPORT".
* Set transceiver of UART mode by TOKEN "ONEOF_AAEON_UARTMODE_TRANSCEIVER_DEFAULT".
* Make sure truth table is correct by TOKEN "F81438_RS###_TRUTH_TABLE" or "HW_DESIGN_RS###_TRUTH_TABLE" which use for control RS232/422/485 mode.
* Enable the UART mode support by TOKEN "CHECKBOX_AAEON_UART#MODE_DEFAULT".
* Set UID for target UART by TOKEN "NUMERIC_AAEON_UARTMODE_UID_DEFAULT".
* Set GPIO source chip connect to UART mode transceiver by TOKEN "ONEOF_AAEON_UART#MODE_SOURCE_DEFAULT".
* Set SIO source chip for target UART by TOKEN "ONEOF_AAEON_UART#MODE_UART_SOURCE_DEFAULT".
* Set GPIO number which use for control transceiver by TOKEN "NUMERIC_AAEON_UART#MODE_GPIO_DEFAULT"
* There are 6 UART mode control item in this module

## (Optional if needed) Changing default value of UART mode

* Modify UART mode default by TOKEN "DEFAULT_AAEON_UART#MODE". (Default setting is RS232)
* Follow the tag AAEON_OVERRIDE to override file SioDynamicSetup.c to prevent default value was overridden when load setup default.

```c
   VOID EFIAPI EFIAPI LoadLdDefaults(EFI_QUESTION_ID KeyValue){
       UINTN  i=(UINTN)(KeyValue & (~SIO_GOTO_ID_BASE));
       LD_SETUP_GOTO_DATA      *gotodata;
    //-------------------------------   
       //Using KeyValue - locate Goto Form Data...
       gotodata=gSioIfrInfo.LdSetupData[i];   
   
       SIO_TRACE((TRACE_SIO,"SioSetup: Loading Defaults for NV_SIO%X_LD%X;\n", gotodata->SioIdx, gotodata->LdIdx));
       
       gotodata->SetupNvData.DevEnable = 1;
       gotodata->SetupNvData.DevPrsId = 0;
       //AAEON_OVERRIDE-- gotodata->SetupNvData.DevMode = 0;
   }
```
MODULE IMPROVEMENT NOTE
================================

## TODO: N/A