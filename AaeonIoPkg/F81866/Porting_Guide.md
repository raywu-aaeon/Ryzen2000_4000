Table of content
1. [F81866](#f81866)
2. [PORTING NOTE](#porting-note)
3. [DEPENDENCIES](#dependencies)
4. [NOTE](#note)

F81866
================================

Supported Funtion:

* Floppy / Keyboard / Mouse / LPT / WDT / HWN / Smart Fan
* 6 * UART, with default mode and resource:
   * UART 3 - 6 currently only support sharing IRQ by this module. Additional porting required for independent IRQ.

| #     | RS232/485 | IRQ Mode        | Default ASL file                 | COM# | IO   | IRQ# |
| ----- | --------- | --------------- | -------------------------------- | ---- | ---- | ---- |
| UART1 | RS232     | Level No shared | AaeonCommonPkg\ACPI\SIOUART1.asl | COM1 | 3F8h | 4    |
| UART2 | RS232     | Level No shared | AaeonCommonPkg\ACPI\SIOUART2.asl | COM2 | 2F8h | 3    |
| UART3 | RS232     | Level shared    | AaeonCommonPkg\ACPI\SIOUART3.asl | COM3 | 3E8h | 11   |
| UART4 | RS232     | Level shared    | AaeonCommonPkg\ACPI\SIOUART4.asl | COM4 | 2E8h | 11   |
| UART5 | RS232     | Level shared    | AaeonCommonPkg\ACPI\SIOUART5.asl | COM5 | 2D0h | 11   |
| UART6 | RS232     | Level shared    | AaeonCommonPkg\ACPI\SIOUART6.asl | COM6 | 2C0h | 11   |

PORTING NOTE
================================

* Override following tokens in project .sdl file, and configure these tokens according your Project circuit design -

   * F81866_CONFIG_INDEX : 2E or 4E

      ```
      Name  = "F81866_CONFIG_INDEX"
      Value  = "0x2E"
      ```

   * F81866_CONFIG_DATA : 2F or 4F

      ```
      Name  = "F81866_CONFIG_DATA"
      Value  = "0x2F"
      ```

   * F81866_CLOCK : 48Mhz, 14.318MHz or 24MHz.

      ```
      Name  = "F81866_CLOCK"
      Value  = "0"
      Help  = "0/1/2 for 48Mhz/14.318MHz/24MHz"
      ```

   * Floppy Port Present

      ```
      Name  = "F81866_FLOPPY_PORT_PRESENT"
      Value  = "0"
      Help  = "Floppy Port Present / Not Present."
      ```

   * Keyboard Present

      ```
      Name  = "F81866_KEYBOARD_PRESENT"
      Value  = "1"
      Help  = "Keyboard Present / Not Present."
      ```
      
   * Mouse Present

      ```
      Name  = "F81866_MOUSE_PRESENT"
      Value  = "1"
      Help  = "Mouse Present / Not Present."
      ```
      
   * Serial Port 1 ~ 6 Present tokens

      ```
      Name  = "F81866_SERIAL_PORT1_PRESENT"
      Value  = "1"
      Help  = "Serial Port 1 (COMA / UART1) Present / Not Present."
      ```
      and so on.

   * LPT Port Present

      ```
      Name  = "F81866_PARALLEL_PORT_PRESENT"
      Value  = "1"
      Help  = "LPT Port Present / Not Present."
      ```

   * Watch Dog Time Present

      ```
      Name  = "F81866_WDT_PRESENT"
      Value  = "1"
      Help  = "Watch Dog Time Present / Not Present."
      ```

   * HWM Port Present

      ```
      Name  = "F81866_HWM_PRESENT"
      Value  = "1"
      Help  = "HWM Port Present / Not Present."
      ```
     
   * HWM PECI support

      ```
      Name  = "F81866_HWM_PECI_SUPPORT"
      Value  = "0"
      Help  = "0: No PECI support (default).\1: Enable PECI support."
      ```

   * HWM Resister value tokens for voltage sensors.

      ```
      Name  = "VIN1_RA"
      Value  = "0"
      ```
      and so on.

   * SmartFan control support

      ```
      Name  = "F81866_SMF_SUPPORT"
      Value  = "1"
      Help  = "F81866 SmartFan control support"
      ```
            
   * Base address for I/O resource

      ```
      Name  = "F81866_TOTAL_BASE_ADDRESS"
      Value  = "0xA00"
      Help  = "It's used for IODecode, System will open TOTAL_BASE_ADDRESS+TOTAL_LENGTH IODecode for GPIO+PME+..."
      ```

   *  Power loss state via setting ACPI control register.

      ```
      Name = "ONEOF_F81866RESTOREACPOWERLOSS_DEFAULT"
      Value = "0"
      Help = "0: Last State\1: Always On\2: Always Off"
      ```

   *  ERP Power saving mode support

      ```
      Name  = "F81866_ERP_SUPPORT"
      Value  = "1"
      ```

   *  "GPIO" or "Multi function" selecting tokens

      ```
      Name  = "PIN71_EN"
      Value  = "0"
      Help  = "0: BEEP/GPIO16/SDA\1: Reserved"
      ```
      ```
      Name  = "GPIO65_EN"
      Value  = "1"
      Help  = "0: PME#\1: GPIO65"
      ```
      and so on.

   *  GPIO "Input" or "Output" selecting  tokens

      ```
      Name  = "F81866GPIO01_OE_DEFAULT"
      Value  = "0"
      Help  = "0: Input\1: Output"
      ```
      and so on.

   *  GPIO "Hi" or "Low" selecting  tokens

      ```
      Name  = "F81866GPIO00_VAL_DEFAULT"
      Value  = "1"
      Help  = "0: Low\1: High"
      ```
      and so on.

   *  GPIO "Open Drain" or "Push Pull" selecting tokens

      ```
      Name  = "F81866GPIO00_DRVEN_DEFAULT"
      Value  = "0"
      Help  = "0: Open Drain\1: Push Pull"
      ```
      and so on.

   * For Serial Port 1 ~ 6, RS232/RS485 Selecting tokens.

      ```
      Name  = "F81866_UART1_RS485_EN"
      Value  = "1"
      Help  = "1: Enabled, RTS# is driven high automatically\0: Disabled"
      ```

* For Serial Port 3 - 6, override following tokens in project .sdl file, and configure these tokens according your overall COM port IRQ

   * Function Selecting tokens. Selects "Full UART" or "Simple UART".

      ```
      Name  = "F81866_UART3_FUNC_SEL"
      Value  = "3"
      Help  = "UART3 Function Select. 0: No UART \ 1: Simple UART(SIN3 and SOUT3) \ 2: Simple UART with RTS \ 3: Full UART"
      ```

   * IRQ sharing tokens. IRQ is "sharing" or "not sharing" with other device.
      * If switching this token off for using independent IRQ, additional porting required : uartx.asl file(Ex: ACPI\UART1.asl).

      ```
      Name  = "F81866_UART3_IRQ_SHARE"
      Value  = "1"
      Help  = "Select to share IRQ with other UART or not.\1: IRQ is sharing with the other device.\\Note: When switching this token off for independent IRQ,additional porting required : uartx.asl file."
      ```

   * IRQ mode tokens. IRQ triggered by "Edge" or "Level".
      * Fintek IRQ_MODE1(OTP6[3]) and IRQ_MODE0(OPT0[1]) will be configured according to this token:
      * On  - 00: Sharing IRQ active low Level mode.
      * Off - 01: Sharing IRQ active high edge mode.

      ```
      Name  = "F81866_UART3_LEVEL_EDGE_SHARE_MODE"
      Value  = "1"
      Help  = "Select sharing IRQ active by Level or edge mode.\ Off: Sharing IRQ active low Level mode.\ On: Sharing IRQ active high edge mode.\ Note: For details, please refer to F81866\Porting_Guide.md."
      ```

   * NOTE: When set IRQ to edge triggering, LDEVICE token will be switch to the one with edge .asl file.

      ```
      AaeonCommonPkg\ACPI\UARTx.asl
      =>
      AaeonCommonPkg\F81866\UARTx_Edge.asl
      ```

* If UART 1 ~ 6 is not used as COM3,4,11,11,11,11; or IO/IRQ resource need to be changed -

   * Copy UARTx.asl (or UARTx_Edge.asl) into project folder, for overriding.

      ```
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\UART3.asl
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\UART4.asl
       ...
      or
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\UART3_edge.asl
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\UART4_edge.asl
       ...
      ```

   * Modify followings according to project requirement, to UARTx.asl.

      ```
      Name(_DDN, "COM3")
      ...
      IO(Decode16, 0x3E8, 0x3E8, 1, 8)
      IRQ(Level,ActiveLow,Shared) {11}
      ```
   
      * COM port number

        ```
        Name(_DDN, "COM3")
        ```
        
      * IRQ number.

        ```
        IRQ(Level,ActiveLow,Shared) {11}
        ```

   * Override LDEVICE tokens in project .sdl file, and configure these tokens according to project requirement

      ```
      Name  = "Com3"
      SioDevice  = "F81866"
      Dev_Type  = "dsUART"
      LDev_Num  = "012h"
      UID  = "03h"
      PnPID  = "0501h"
        ...
      ASLfile  = "'AaeonIoPkg\F81866\UART3_Edge.ASL'"
      ASLdeviceName  = "UAR3"
      ```

      * Change ASL path to overridding UARTx.asl

         ```
         ASLfile  = "'Override\AaeonIoPkg\ACPI\UART3.asl'"
         ```

      * Make sure UID for each COM ports is unique.

         ```
         UID  = "03h"
         ```
   
      * Make sure ASLdeviceName for each COM ports is unique.

         ```
         ASLdeviceName  = "UAR3"
         ```

* Override ISA_IRQ_MASK token in project .sdl file, Make sure IRQ resource used by F81866 is "Available".

   ```
   Name  = "ISA_IRQ_MASK"
   Value  = "0x2305"
   Help  = "This is an IRQ mask which may be used by ISA evices\ If BIT == 0 IRQ Available BIT == 1 IRQ sed.\DEFAULT  VALUE == 0xE305."
   ```

DEPENDENCIES
================================

N/A

NOTE
================================

* Both low Level, high edge or high Level Share mode have been tested passed overnight.

   ```
   Board: VPC-3350S
   Chipest: Apollolake
   OS: Windows 1703
   Tool: Burn-in test
   Duration: overnight
   ```