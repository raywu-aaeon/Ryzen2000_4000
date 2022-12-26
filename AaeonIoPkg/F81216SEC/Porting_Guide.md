
PORTING NOTE:
================================

**F81216SEC** 

Supported Funtion:

* WDT (no porting required)
* 4 * UART, with default mode and resource:

| #     | RS232/485 | IRQ Mode     | Default ASL file                 | COM# | IO   | IRQ# |
| ----- | --------- | ------------ | -------------------------------- | ---- | ---- | ---- |
| UART1 | RS232     | Level shared | AaeonCommonPkg\ACPI\SIOUART3.asl | COM3 | 3E8h | 11   |
| UART2 | RS232     | Level shared | AaeonCommonPkg\ACPI\SIOUART4.asl | COM4 | 2E8h | 11   |
| UART3 | RS232     | Level shared | AaeonCommonPkg\ACPI\SIOUART5.asl | COM5 | 2D0h | 11   |
| UART4 | RS232     | Level shared | AaeonCommonPkg\ACPI\SIOUART6.asl | COM6 | 2C0h | 11   |

General:
================================

1. Override following tokens in project .sdl file, and configure these tokens according your Project circuit design -

   * F81216SEC_CONFIG_INDEX : 2E or 4E
      ```
      Name  = "F81216SEC_CONFIG_INDEX_DATA_DEFAULT"
      Value  = "0"
      Help  = "0: index to 0x2E and data to 0x2F / 1: index to 0x4E and data to 0x4F"
      ```

   * F81216SEC_CLOCK : 48Mhz or 24MHz.
      ```
      Name  = "F81216SEC_CLOCK"
      Value  = "0"
      Help  = "0/1 for 24Mhz/48MHz"
      ```

   * F81216SEC_CONFIG_MODE_ENTER_VALUE : 0x77 or 0xA0 or 0x87 or 0x67
      ```
      Name  = "F81216SEC_CONFIG_MODE_ENTER_VALUE"
      Value  = "0x77"
      Help  = "Value to enter the SIO Configuration Mode."
      ```

   * Serial Port 1 / 2 / 3 / 4 Present
      ```
      Name  = "F81216SEC_SERIAL_PORT1_PRESENT"
      Value  = "1"
      Help  = "Serial Port 1 (COMA / UART1) Present / Not Present."
      ```

2. Override following tokens in project .sdl file, and configure these tokens according your overall COM port IRQ

   * Use "Edge" or "Level" trigger. PCI : level; ISA : Edge.
      ```
      Name  = "F81216SEC_URIRQ_MODE"
      Value  = "0"
      Help  = "IRQ sharing mode. 0: PCI \ 1: ISA."
      ```

   * IRQ is "sharing" or "not sharing" with other device.
      ```
      Name  = "F81216SEC_URIRQ_SHAR"
      Value  = "1"
      Help  = "0: IRQ is not sharing with other device. \ 1: IRQ is sharing with other device."
      ```

   * NOTE1: Above two tokens control all 4 F81216 COM ports at same time. Currently separating IRQ mode is not supported.

   * NOTE2: When set IRQ to edge triggering, LDEVICE token will be switch to the one with edge .asl file.
      ```
      AaeonCommonPkg\ACPI\SIOUARTx.asl
      =>
      AaeonCommonPkg\F81216\SIOUARTx_edge.asl
      ```

3. If UART1~4 is not used as COM3,4,5,6; or IO/IRQ resource need to be changed -

   * Copy SIO2UARTx.asl (or SIO2UARTx_edge.asl) into project folder, for overriding.
      ```
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\SIO2UART3.asl
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\SIO2UART4.asl
       ...
      or
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\SIO2UART3_edge.asl
      AaeonProjectPkg\XXXX\Override\AaeonIoPkg\ACPI\SIO2UART4_edge.asl
       ...
      ```

   * Modify followings according to project requirement, to SIO2UARTx.asl.
      ```
      Name(_DDN, "COM3")
      ...
      IO(Decode16, 0x3E8, 0x3E8, 1, 8)
      IRQ(Level,ActiveLow,Shared) {11}
      ```
   
      * COM port number
        ```
        Name(_DDN, "COM3")  <==
        ```
        
      * IRQ number.
        ```
        IRQ(Level,ActiveLow,Shared) {11}  <==
        ```

   * Override LDEVICE tokens in project .sdl file, and configure these tokens according to project requirement
      ```
      Name  = "Com11"
      SioDevice  = "F81216SEC"
      Dev_Type  = "dsUART"
      LDev_Num  = "00h"
      UID  = "03h"
      PnPID  = "0501h"
        ...
      ASLfile  = "'AaeonIoPkg\ACPI\SIO2UART3.asl'"
      ASLdeviceName  = "UR11"
      ```

      * Change ASL path to overridding SIO2UARTx.asl
         ```
         ASLfile  = "'Override\AaeonIoPkg\ACPI\SIO2UART3.asl'"
         ```

      * Make sure UID for each COM ports is unique.
         ```
         UID  = "06h"
         ```
   
      * Make sure ASLdeviceName for each COM ports is unique.
         ```
         ASLdeviceName  = "UR11"
         ```

4. Override following tokens in project .sdl file, Make sure IRQ resource used by F81216 is "Available".
   ```
   Name  = "ISA_IRQ_MASK"
   Value  = "0x2305"
   Help  = "This is an IRQ mask which may be used by ISA evices\ If BIT == 0 IRQ Available BIT == 1 IRQ sed.\DEFAULT  VALUE == 0xE305."
   ```

Dependencies :
================================

N/A

Note :
================================

1. According to Fintek application note, for Skylake/Kabylake, IRQ mode should be set to Edge-shared to prevent unkown CPU loading.
   ```
   Name  = "F81216SEC_URIRQ_MODE"
   Value  = "1"
   Help  = "IRQ sharing mode. 0: PCI \ 1: ISA."

   Name  = "F81216SEC_URIRQ_SHAR"
   Value  = "1"
   Help  = "0: IRQ is not sharing with other device. \ 1: IRQ is sharing with other device."
   ```

   * Fintek application note:
      ```
      BIOS - Datasheet\Fintek\SuperIO\Application_Note\Fintek SIO_170101AA_SkyLake.pdg
      ```

2. Both PCI-shared and ISA-shared mode have been tested passed overnight.
   ```
   Board: VPC-3350S
   Chipest: Apollolake
   OS: Windows 1703
   Tool: Burn-in test
   Duration: overnight
   ```