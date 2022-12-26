Table of content
1. [AAEON BFPI](#aaeon-bfpi)
2. [FILES NOTE](#files-note)
3. [DEPENDENCIES](#dependencies)
4. [PROJECT PORTING NOTE](#project-porting-note)
5. [MODULE IMPROVEMENT NOTE](#module-improvement-note)
6. [FLOWCHARTS](#flowcharts)
7. [PORTING REQUIREMENT FOR EXTERNAL MODULE](#porting-requirement-for-external-module)

AAEON BFPI
================================

* This module provides framework for AAEON BFPI. It's goal is to make BFPI functional with minimal porting.

* This module supports a certain number of controllers -

| Interface | Number                  |
| --------- | ----------------------- |
| DIO       | Check AaeonDio3 module  |
| WDT       | 2                       |
| HWM       | Not limited             |
| Backlight | TODO                    |
| Smart Fan | Not limited             |
| LED       | 1, OEM only             |
| I2C/SMBUS | TODO                    |
| PWM       | TODO                    |

* For each interface, this module calls external functions in other modules according to arguments given to BFPI. Corresponded functions must be implemented externally.

| Source Type | Module should provide function |
| ----------- | ------------------------------ |
| OEM         | AaeonProjectPkg                |
| SoC         | Platform package (AAEON CRB)   |
| SIO1        | 1st SIO module                 |
| SIO2        | 2nd SIO module                 |
| SIO3        | 3rd SIO module                 |
| EC          | EC SIO module                  |
| EC2         | EC 2nd SIO module              |
| I2C         | TBD, Should be new module      |
| SMBUS       | TBD, Should be new module      |

* For transfering data between hardware and WMI, this module reserves 4352 (0x1100) bytes memory as EfiACPIMemoryNVS.

FILES NOTE
================================

## .sdl

* AaeonBfpi.sdl - Main configurations to this module.
* AaeonBfpiReportCapability.sdl - Misc configurations, basically require no porting between projects.

## .c

* AaeonBfpiDxe.c - Register a callback for allocate memory and prepare data to AAEON BFPI

## .asl

* AaeonBfpi.asl - Dispatch AAEON BFPI input data to corresponding operations.
* AaeonBfpiWdt.asl - Dispatch WDT operations to methods in external modules.
* AaeonBfpiHwm.asl - Dispatch HWM operations to methods in external modules.
* AaeonBfpiSmf.asl - Dispatch SMF operations to methods in external modules.
* AaeonBfpiLed.asl - Dispatch Led operations to methods in external modules.
* OemBfpiTemplate.asl - Template for OEM interface porting.

DEPENDENCIES
================================

Some tokens will be switched ON automatically depending on presence of other module. Refer to "Tokens override xxxx" sections in AaeonBfpiReportCapability.sdl.

PROJECT PORTING NOTE
================================

## General

* AaeonBfpi.sdl
  * Review tokens in "xxxx Configurations" sections, regarding to your project design. Override those tokens in project .sdl if necessary.
* External modules
  * Make sure you are using module with BFPI support.
  * Review tokens in regarding to your project design. Override those tokens in project .sdl if necessary.

## Support OEM DIO/WDT/LED Controller

If there is an OEM controller which is not common to other AAEON projects, you can add OEM porting by following steps -
1. Switch corresponding "xxxx_TYPE_OEM_SUPPORT" token ON.
2. Override corresponding "source type" tokens from AaeonBfpi.sdl, with value $(SOURCE_TYPE_OEM), in you project .sdl.
3. Copy 'OemBfpiTempate.asl' or create new .asl, in your project folder.
4. Override the token "Aaeon OEM BFPI Container" PCIDEVICE token from AaeonBfpiReportCapability.sdl, redirect .asl file to new one.
5. Override "OEM_xxxx_METHOD" tokens from AaeonBfpiReportCapability.sdl, if you are not using default method name.
6. Do your OEM porting in the new .asl file.

## Support OEM HWM Controller

Basically follow previous section, but with additional step:
* Override tokens from AaeonBfpiReportCapability.sdl "--- HWM Source Type OEM ---" section.

MODULE IMPROVEMENT NOTE
================================

## Add more controller

Take adding 3rd WDT controller as example:
1. AaeonBfpi.sdl
   * Add "THIRD_WDT_TYPE" and "THIRD_WDT_NAME" tokens in refer to "SECOND_WDT_xxx" tokens.
2. AaeonBfpiReportCapability.sdl
   * Add "WDTC_THIRD_WDT" token in refer to "WDTC_SECOND_WDT" token.
   * Modify "WDTC" token, add "$(WDTC_THIRD_WDT)" at end.
3. AaeonBfpiWdt.asl
   * Add ASL_THIRD_WDT_TYPE in TWDT

## Add more source type

Take adding SMBUS as new source type as example:
1. Create new module for new source
2. Implement ASL function methods in new module.
3. AaeonBfpiReportCapability.sdl
   * Add "SOURCE_TYPE_SMBUS" token and give it a unique value.
   * Add "xxx_TYPE_SMBUS_SUPPORT" tokens for each interface (WDT...) supported by the source.
4. AaeonBfpixxx.asl for each interface (WDT...) supported by the source
   * Add ASL code for calling function methods.

FLOWCHARTS
================================

1. [BFPI base flow](#BFPI-BASE-FlOW)
2. [BFPI overall flow](#BFPI-OVERALL-FLOW)
3. [Function Operation flow](#FUNCTION-OPERATION-FLOW)
4. [HWM/SMF Function Operation flow](#HWMSMF-FUNCTION-OPERATION-FLOW)

To see these diagrams:
1. (Recommended) View this file on VSCODE, install "Markdown Preview Mermaid Support" extension module, then click "preview" on top-right of vscode window.
2. Copy&paste codes to [Mermaid Live Editor](https://mermaidjs.github.io/mermaid-live-editor/) for preview.

## BFPI base flow

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph BFPI
    A(WMI)
    B[WMNB]
    C{Function?}
    D1[DIOO]
    D2[WDTO]
    D3[HWMO]
    D4[xxxO...]
    E(Return value to WMI)
  end

%% Routings
  A --> B
  B --> C
  C -- DIO --> D1
  C -- WDT --> D2
  C -- HWM --> D3
  C -. Other functions... .-> D4
  D1 --> E
  D2 --> E
  D3 --> E
  D4 -.-> E
```

## BFPI overall flow

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph Windows
    A(WMI BFPI Emtry)
    subgraph AaeonBfpi
      B[WMNB]
      C{Function?}
      subgraph Function Operation
        D2[WDTO]
        D3[HWMO]
        D4[xxxO...]
      end
    end
        subgraph AaeonDio3
      subgraph Function Operation
          D1[DIOO]
        end
        D2[WDTO]
        D3[HWMO]
        D4[xxxO...]
      end
      subgraph Aaeon IO Modules
        E1[xxRC, xxGL, xxSL, xxGD, xxSD]
        E2[xxRC, xxGT, xxST]
        E3[xxRC, xxRS]
        E4[xxxx...]
      end
    E(WMI BFPI Exit)
  end

%% Routings
  A --> B
  B --> C
  C -- DIO --> D1
  C -- WDT --> D2
  C -- HWM --> D3
  C -. Other functions... .-> D4
  D1 ==> E1
  D2 ==> E2
  D3 ==> E3
  D4 -.-> E4
  E1 == Return value ==> E
  E2 == Return value ==> E
  E3 == Return value ==> E
  E4 -. Return value .-> E
```

## Function Operation flow

Basically DIO and WDT follows this flow.

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph Function operation
    A(xxxO)
    B{Sub-function?}
    subgraph Sub-function operation
      C1(sub-function1)
      C2(sub-function2)
      C3(sub-function3...)
    end
    E(Return value)
  end

%% Routings
  A --> B
  B -- function 1 --> C1
  B -- function 2 --> C2
  B -. function 3... .-> C3
  C1 --> E
  C2 --> E
  C3 -.-> E
```

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph Sub-function operation
    E(Sub-function)
    F{Source?}
    subgraph Aaeon IO Modules
      G1(Call OEM)
      G2(Call SOC)
      G3(Call SIO1, 2...)
    end
    I(Return value)
  end

%% Routings
  E --> F
  F -- OEM --> G1
  F -- SOC --> G2
  F -. SIO1,2... .-> G3
  G1 --> I
  G2 --> I
  G3 -.-> I
```

## HWM/SMF Function Operation flow

HWM and SMF have different Function Operation flow. Take HWM as example -

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph AaeonBfpi
    A(HWMO)
    E(HWRS)
    B{Index format?}
    C1[Get name from standard table]
    C2[Get name from HMSS]
    D{Name found?}
    F[Get name from data buffer]
    G(Call AHRS)
  end

%% Routings
  A --> E
  E --> B
  B -- Standard Mapping --> C1
  B -- Flatten Mapping --> C2
  C1 --> D
  C2 --> D
  D -- Yes --> G
  D -- No --> F
  F --> G
```

``` mermaid
%% Diagram and State definitions
graph TD
  subgraph AaeonBfpi
    E(AHRS)
    subgraph Aaeon IO Modules
      F{Result from OEM?}
      G{Result from SOC?}
      H{Result from SIO1,2...?}
    end
    I(Return reading)
    J(Return NOT_SUPPORTED)
  end

%% Routings
  E -- Call each supported controller with name string --> F
  F -- NOT_SUPPORTED --> G
  G -. NOT_SUPPORTED .-> H
  H -- NOT_SUPPORTED --> J
  H -. Reading get .-> I
  F -- Reading get --> I
  G -- Reading get --> I
```

PORTING REQUIREMENT FOR EXTERNAL MODULE
================================

## For HWM function

### HWM Module Design

* Each sensor source should have correspond set of tokens in .sdl - one "SUPPORT" token, one "NAME" token, and one "STRING" token.
  * SUPPORT - When switched on :
    * Support reporting this sensor through BFPI
    * Support showing this sensor in BIOS setup menu
  * NAME -
    * For BIOS setup to display as sensor name
    * Must use one of pre-defined name in AaeonIoPkg.sdl first
  * STRING -
    * Same as "NAME" but is used in ASL code.

  ```
  TOKEN
    Name  = "W83627DHG_SYSTIN_SUPPORT"
    Value  = "1"
    Help  = "Switch on if SYSTIN is designed and is used."
    TokenType = Boolean
    TargetH = Yes
    TargetMAK = Yes
  End

  TOKEN
    Name  = "W83627DHG_SYSTIN_NAME"
    Value  = "$(STD_SYS_TEMP)"
    Help  = "Sensor name to be displayed in setup menu and to be reported in BFPI. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no   matchness. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no matchness."
    TokenType = Expression
    TargetMAK = Yes
    Token = "W83627DHG_SYSTIN_SUPPORT" "=" "1"
  End
  
  TOKEN
    Name  = "W83627DHG_SYSTIN_STRING"
    Value  = '"$(W83627DHG_SYSTIN_NAME)"'
    Help  = "Name for the temperature sensor."
    TokenType = Expression
    TargetH = Yes
    Token = "W83627DHG_SYSTIN_SUPPORT" "=" "1"
  End
  ```

### HWM Project Porting

* For sensors from each HWM controller (SIO, EC...), override "NAME" token with value as TANDARD_NAME tokens defined in AaeonIoPkg.sdl "Standard string Constants" section.
* Each sensor should be named differently to others.
* For products use having non-standard sensor name, still override "NAME" tokens with standard ones, and then override STANDARD_NAME token with value as non-standard string. Otherwise SDK support "BFPI V0.4 basic" only will be not able to read sensor.

  ```
  # HWM example:

  ## SENSOR_NAME in IT851XX_EC1_BFPI.sdl
  TOKEN
      Name  = "EC1_IT85XX_THRM_SEN1_NAME"  ## token name may be different between module.
      Value  = "$(STD_STS_TEMP)"  ## Use STANDARD_NAME token
      Help  = "Sensor name to be displayed in setup menu and to be reported in BFPI. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no matchness."
      TokenType = Expression
      TargetMAK = Yes
      Token = "IT851X_PECI_ENABLE" "=" "1"
  End

  ## STANDARD_NAME in AaeonIoPkg.sdl
  TOKEN
      Name = "STD_SYS_TEMP"
      Value = "System Temperature"
      Help = "Standard name for CPU temperature sensor"
      TokenType = Expression
      TargetMAK = Yes
  End

  ## STANDARD_NAME overriden in COM-series project.sdl
  TOKEN
      Name  = "STD_SYS_TEMP"
      Value  = "Thermal Source 1(T1)"
      Help  = "Sensor name to be displayed in setup menu and to be reported in BFPI. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no matchness."
      TokenType = Expression
      TargetMAK = Yes
      Token = "IT851X_PECI_ENABLE" "=" "1"
      Token = "ECD_THRM_RULE" "=" "1"
  End
  ```
