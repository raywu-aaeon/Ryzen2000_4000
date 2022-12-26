Table of content
1. [TERMINOLOGY](#TERMINOLOGY)
2. [AAEON UART OVERRIDE](#AAEON-UART-OVERRIDE)
3. [FILES NOTE](#FILES-NOTE)
4. [DEPENDENCIES](#DEPENDENCIES)
5. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)
6. [MODULE IMPROVEMENT NOTE](#MODULE-IMPROVEMENT-NOTE)

TERMINOLOGY
================================

* LDEVICE - a SDL generated data structure generated during build time.
* TODO - Some works to be done in future
* \# - represents a number between 0~9

AAEON UART OVERRIDE
================================

## Goal

* Allow use to easily override "UART configuration" and "Dynamic SIO setup" by setup items.
   * Note: Currently support override "UART present" only, others TODO.

## Use Case

* Project designer may use board ID to control the number of UART.
* When Customer wish to disable UART, customer/AE can use BIoX to make custom BIOS directly.
* When System project requires add/remove UART connector, EE can use BIoX to make system BIOS directly.

## This module

* Support 6 set of "UART Override" setup items. Each set is capable for
   * Select override "UART Present" to Enable/disable UART
   * Select target UART to override, by UID
* Support overriding UART configuration during POST time -
   * Override "UART present" by changing LDEVICE parameter -
      * "Implemented", "HasSetup", "Flags"
* For porting -
   * Support configuring setup default by token.

FILES NOTE
================================

## .sdl

* AaeonUartOverride.sdl - Main configurations to this module.

## .c

* AaeonUartOverridedxe.c - Initial UART override.
* AaeonUartOverridePrsdxe.c - Check the flags of LDEVICE for support dynamic IRQ sharing setting.

DEPENDENCIES
================================

* This module will be disabled if TOKEN "SIO_SUPPORT" was disabled.

PROJECT PORTING NOTE
================================

## General

* Enable master TOKEN "AAEON_UART_OVERRIDE_SUPPORT". (This is default setting)

## (Optional if needed) Changing default value of UART present

* Enable one UART override support by TOKEN "CHECKBOX_AAEON_UART_OVERRIDE_\#_SUPPORT_DEFAULT".
* Set the UID for target UART by TOKEN "NUMERIC_AAEON_UART_OVERRIDE_\#_UID_DEFAULT".
* Set default value of the target UART present by TOKEN "CHECKBOX_AAEON_UART_PRESENT_\#_DEFAULT".

## (Optional) Override more than 6 UART

* Modify the TOKEN "MAX_UART_OVERRIDE_ITEM" to the numbers of override UART.
* Clone the setup item group in AaeonUartOverride.sd and increase the numbers for new setup item group.

```java
    SUBTITLE(STRING_TOKEN(STR_AAEON_UART_OVERRIDE_6))
    AAEON_UART_OVERRIDE_ITEMS(
        5, 
        CHECKBOX_AAEON_UART_OVERRIDE_6_SUPPORT_DEFAULT,
        NUMERIC_AAEON_UART_OVERRIDE_6_UID_DEFAULT,
        CHECKBOX_AAEON_UART_PRESENT_6_DEFAULT)
```

* According to above setup item group to create setup string and default TOKEN.

MODULE IMPROVEMENT NOTE
================================

## TODO: Support modifying the default setting of UART dynamic setup items

## TODO: Support modifying LDEVICE parameter of UART by setup items

## TODO: Support modifying PRS resource of UART by setup items