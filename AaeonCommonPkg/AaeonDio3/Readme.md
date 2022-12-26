Table of content
1. [AAEON DIO 3](#AAEON-DIO-3)
2. [FILES NOTE](#FILES-NOTE)
3. [DEPENDENCIES](#DEPENDENCIES)
4. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)
5. [MODULE IMPROVEMENT NOTE](#MODULE-IMPROVEMENT-NOTE)

AAEON DIO 3
================================

* This is 3rd generation of AAEON DIO module. It's goal is to make DIO functional with minimal porting.

* This module -
   * Support Dynamic DIO -
      * Support configuring DIO dynamically as In/Out or High/Low in setup menu
      * Follow 2nd generation, support changing DIO source and GPIO number to each DIO pin by setup menu.
   * Support AAEON BFPI.
   * For porting -
      * Support generating setup layout by token.
      * Support configuring setup default by token.
      * Capable for enable two DIO controllers at same time. Porting required if more controllers needed.
      * Default supports 16 pins for each DIO controller, 64 pins in maximum. Porting required if there are more than 16 pins from single controller.

| Maximum pin   | Default  | Basic Porting  | Ach. Change |
| ------------- | -------- |--------------- |------------ |
| Overall       | 128      | 128            | > 128       |
| First DIO     | 16       | 64             | > 64        |
| Second DIO    | 16       | 64             | > 64        |

* For POST initialization, this module calls AaeonSetGpio in AaeonCommonLib for actual GPIO operation. Corresponded functions must be implemented externally. 

* For BFPI, this module calls external ASL functions in other modules for actual GPIO operation. Corresponded functions must be implemented externally.

| Source Type | Module should provide function |
| ----------- | ------------------------------ |
| SoC         | Platform package (AAEON CRB)   |
| SIO1        | 1st SIO module                 |
| SIO2        | 2nd SIO module                 |
| SIO3        | 3rd SIO module                 |
| EC          | EC SIO module                  |
| EC2         | EC 2nd SIO module              |
| I2C         | TBD, Should be new module      |
| SMBUS       | TBD, Should be new module      |

* For transfering data from setup items to ACPI, this module reserves 2K (0x800) bytes memory as EfiACPIMemoryNVS.

FILES NOTE
================================

## .sdl

* AaeonDio3.sdl - Main configurations to this module.
* AaeonDio3ReportCapability.sdl - Misc configurations, basically require no porting between projects.

## .c

* AaeonDio3.c - Initial DIO when AAEON_DXE_INIT_FUNCTIONS called.
* AaeonDio3Dxe.c - Register a callback for allocate memory and prepare data to AAEON BFPI
* AaeonDio3SetupCallback.c - Provides setup callback to re-initial DIO.

## .h

* AaeonDio3.h - Define AAEON BFPI data structure
* AaeonDio3Setup.h - Parse setup default from .sdl default tokens

## .asl

* AaeonDio3.asl - Dispatch DIO operation from AAEON BFPI to methods in external modules.
* OemDioTemplate.asl - Template for OEM DIO porting.

DEPENDENCIES
================================

* Some tokens will be switched ON automatically depending on presence of other modules. Refer to "Tokens override xxxx" section in AaeonDio3ReportCapability.sdl.
* AaeonCommonPkg AaeonCommonLib module: It controls GPIO through setup items. Correspond module must support this GPIO controlling mechanism. Refer to AaeonCommonLib\GPIO.c for more detail.
* Modules listed in "Source Type" table above - Must support ASL functions for GPIO controlling.

PROJECT PORTING NOTE
================================

## General

Review tokens in "xxxx Configurations" sections, regarding to your project design. Override those tokens in project .sdl if necessary.
* Set pin numbers and name
* Set pin capability map. Corresponding setup items will be shown according to this map.
* Set pin default map. This map will be taken as setup default.
* Set GPIO number for each pin. Where number is controller specific.

## Supporting more than 16 pins from single DIO controller

Modify followings -
* AaeonDio3.sdl
  * Add "DIO_xx_GPIO_DEFAULT" tokens for each 17+ pin.
* AaeonDio3.sd
  * Add setup descriptions for each 17+ pin.

## Support OEM DIO Controller

If there is an OEM controller which is not common to other AAEON projects, you can add OEM porting by following steps -
* Switch corresponding "DIO_TYPE_OEM_SUPPORT" token ON.
* Override corresponding "source type" token with value $(SOURCE_TYPE_OEM), in you project .sdl.
* Copy 'OemDioTempate.asl' or create new .asl, in your project .sdl.
* Override "Aaeon OEM DIO Container" PCIDEVICE token, redirect .asl file to new one.
* Override "OEM_DIO_xx_METHOD" tokens if you are not using default method name.
* Do your OEM porting in the new .asl file.

MODULE IMPROVEMENT NOTE
================================

## Support new DIO controller

1. Implement ASL function methods in external module.
2. AaeonBfpiReportCapability.sdl
  * Add source type into group list token "DIO_TYPE_xxx_GROUP_LIST"

## Add more controller number enabled at same time

1. AaeonDio3.sdl
  * Add "THIRD_DIO_NUMBER", "THIRD_DIO_NAME" and "THIRD_DIO_TYPE" tokens in refer to "THIRD_DIO_xxx" tokens.
  * Add "THIRD_DIO_xx_GPIO_DEFAULT" tokens for GPIO configurations to 3rd controller.
2. AaeonBfpiReportCapability.sdl
  * Add "DIOC_THIRD_DIO", "THIRD_DIO_END_NUMBER" tokens.
  * Modify "DIOC" token, add "$(DIOC_THIRD_DIO)" at end.
  * Add tokens "THIRD_DIO_xxx_CAPABLE_MAP2" and "THIRD_DIO_xxx_DEFAULT2" which are pre-define for pin more than 32.
3. AaeonDio3.sd
  * Add setup variables - Dio3Direction, Dio3Level, Dio3Driving, Dio3Interrupt, Dio3GpioNum
  * Add setup descriptions for those variables, in refer to descriptsions for 2nd DIO controllers.
4. AaeonDio3Dxe.c & AaeonDio3.c & AaeonDio3.h & AaeonDio3.asl
  * Review all related code commented with "TODO".

## Add more source type - Take adding SMBUS as new source type as example:

1. Create new module for new source
2. Implement ASL function methods in new module.
3. AaeonBfpiReportCapability.sdl
  * Add "SOURCE_TYPE_SMBUS" token and give it a unique value.
  * Add "xxx_TYPE_SMBUS_SUPPORT" tokens for each interface (WDT...) supported by the source.
4. AaeonBfpixxx.asl for each interface (WDT...) supported by the source
  * Add ASL code for calling function methods.

## TODO: Support interrupt control in DioInit()

## TODO: Support driving control in DioInit()