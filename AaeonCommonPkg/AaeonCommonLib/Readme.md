Table of content
1. [AAEON DXE LIBRARY](#AAEON-DXE-LIBRARY)
2. [FILES NOTE](#FILES-NOTE)
3. [DEPENDENCIES](#DEPENDENCIES)
4. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)
5. [MODULE IMPROVEMENT NOTE](#MODULE-IMPROVEMENT-NOTE)

AAEON DXE LIBRARY
================================

## Goal

* The library for AAEON common usage especially for GPIO control.

## Use Case

* Module "AaeonGpioIdPkg" use function "AaeonGetGpio" for getting GPIO ID status.
* Module "AaeonUartMode2Pkg" use function "AaeonSetGpio" for controlling GPIO of UART mode.
* Any function can use function "AaeonGetGpio" and "AaeonSetGpio" by including library "AaeonCommonLib".

## This module

* Support 4 SIO chip and 1 DIO chip includes:
   * F75111
   * F81804
   * F81866
   * F81966
   * IT8728
   * IT8625
   * F75113
* For porting -
   * Support configuring setup default by token.

FILES NOTE
================================

## .h

* AaeonCommonLib.h - Define the prototype of GPIO control function.

## .c

* GPIO.c - Define the AAEON GPIO control function for setting GPIO High/Low, input/output and getting GPIO status.
* F75111.c - Set GPIO High/Low and get GPIO status for F75111.
* F81804.c - Set GPIO High/Low and get GPIO status for F81804.
* F81866.c - Set GPIO High/Low and get GPIO status for F81866.
* F81966.c - Set GPIO High/Low and get GPIO status for F81966.
* IT8728.c - Set GPIO High/Low and get GPIO status for IT8728.
* IT8625.c - Set GPIO High/Low and get GPIO status for IT8625.
* F75113.c - Set GPIO High/Low and get GPIO status for F75113.

DEPENDENCIES
================================

* gEfiSmbusHcProtocolGuid - SmBus access library

PROJECT PORTING NOTE
================================

## General

* Include AaeonCommonLib.h to the C file for target module
* Add AaeonCommonPkg.dec to the [Packages] of inf file for target module
* Add AaeonPeiLib / AaeonDxeLib to the [LibraryClasses] of inf file for target module

## The TOKEN value of GPIO Source Chip
* 0 - F81866_CHIP_TYPE
* 1 - F81801_CHIP_TYPE (TODO)
* 2 - F81216SEC_CHIP_TYPE (TODO)
* 3 - IT8728F_CHIP_TYPE
* 4 - W83627DHG_CHIP_TYPE (TODO)
* 5 - F75111_CHIP_TYPE
* 6 - F81966_CHIP_TYPE
* 7 - F81804_CHIP_TYPE
* 8 - IT851X_CHIP_TYPE (TODO)
* 9 - F75113_CHIP_TYPE
* 10 - IT8625_CHIP_TYPE
* 0xFF - SOC_CHIP_TYPE (TODO)

## Supported AMI Library/module

* AmiCspLib
* AmiTsePkg

MODULE IMPROVEMENT NOTE
================================

## TODO: Support the GPIO control function for the other chips.