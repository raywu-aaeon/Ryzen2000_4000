Table of content
1. [GENERAL](#general)
2. [DEPENDENCIES](#dependencies)
3. [PROJECT PORTING NOTE](#project-porting-note)
4. [MODULE IMPROVEMENT NOTE](#module-improvement-note)

PORTING NOTE
================================

GENERAL
================================

* Add following codes after "AmiModulePkg\IO\AmiSioCore.cif" in veb file.

   ```
   "AaeonIoPkg\SioDynamicSetupLoadDefaults_Mod\SioDynamicSetupLoadDefaults.cif"
   "AaeonIoPkg\F81866\F81866.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81866;5.004_SIO_F81866_Gen03_A00"
   "AaeonIoPkg\F81866\F81866Asl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81866;5.004_SIO_F81866_Gen03_A00"
   "AaeonIoPkg\F81866\F81866Setup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81866;5.004_SIO_F81866_Gen03_A00"
   "AaeonIoPkg\F81866\F81866HwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81866;5.004_SIO_F81866_Gen03_A00"
   "AaeonIoPkg\F81966\F81966.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81966;5.004_SIO_F81966_Gen03_A00"
   "AaeonIoPkg\F81966\F81966Asl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81966;5.004_SIO_F81966_Gen03_A00"
   "AaeonIoPkg\F81966\F81966Setup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81966;5.004_SIO_F81966_Gen03_A00"
   "AaeonIoPkg\F81966\F81966HwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81966;5.004_SIO_F81966_Gen03_A00"
   "AaeonIoPkg\F81966\F81966Bfpi.cif"
   "AaeonIoPkg\F81216SEC\F81216SEC.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81216SEC;5.004_SIO_F81216SEC_Gen03_A00"
   "AaeonIoPkg\F81216SEC\F81216SECAsl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81216SEC/F81216SECAsl;5.004_SIO_F81216SEC_Gen03_A00"
   "AaeonIoPkg\F81216SEC\F81216SECSetup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Fintek/F81216SEC/F81216SECSetup;5.004_SIO_F81216SEC_Gen03_A00"
   "AaeonIoPkg\NCT6791D\NCT6791D.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT6791D;5.004_SIO_NCT6791D_Gen03_A00"
   "AaeonIoPkg\NCT6791D\NCT6791DAsl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT6791D/NCT6791DAsl;5.004_SIO_NCT6791D_Gen03_A00"
   "AaeonIoPkg\NCT6791D\NCT6791DSetup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT6791D/NCT6791DSetup;5.004_SIO_NCT6791D_Gen03_A00"
   "AaeonIoPkg\NCT6791D\NCT6791DHwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT6791D/NCT6791DHwMonitor;5.004_SIO_NCT6791D_Gen03_A00"
   "AaeonIoPkg\NCT6791D\NCT6791DMiscSetup.cif"= Private
   "AaeonIoPkg\IT8625\IT8625.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8625;IT8625_11"
   "AaeonIoPkg\IT8625\IT8625Asl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8625/IT8625Asl;IT8625_11"
   "AaeonIoPkg\IT8625\IT8625Setup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8625/IT8625Setup;IT8625_11"
   "AaeonIoPkg\IT8625\IT8625HwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8625/IT8625HwMonitor;IT8625_11"
   "AaeonIoPkg\IT8625\IT8625Bfpi.cif"= Private
   "AaeonIoPkg\IT8728F\IT8728F.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8728F;5.004_SIO_IT8728F_Gen03_A01"
   "AaeonIoPkg\IT8728F\IT8728FAsl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8728F/IT8728FAsl;5.004_SIO_IT8728F_Gen03_A01"
   "AaeonIoPkg\IT8728F\IT8728FSetup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8728F/IT8728FSetup;5.004_SIO_IT8728F_Gen03_A01"
   "AaeonIoPkg\IT8728F\IT8728FHwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/ITE/IT8728F/IT8728FHwMonitor;5.004_SIO_IT8728F_Gen03_A01"
   "AaeonIoPkg\IT8728F\IT8728FBfpi.cif"= Private
   "AaeonIoPkg\W83627DHG\W83627DHG.CIF"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Winbond/W83627DHG;5.004_SIO_W83627DHG_Gen03_A03"
   "AaeonIoPkg\W83627DHG\W83627DHGAsl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Winbond/W83627DHG/W83627DHG ASL;5.004_SIO_W83627DHG_Gen03_A03"
   "AaeonIoPkg\W83627DHG\W83627DHGSetup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Winbond/W83627DHG/W83627DHGSetup;5.004_SIO_W83627DHG_Gen03_A03"
   "AaeonIoPkg\W83627DHG\W83627DHGHwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Winbond/W83627DHG/W83627DHGHwMonitor;5.004_SIO_W83627DHG_Gen03_A03"
   "AaeonIoPkg\NCT5538D\NCT5538D.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT5538D;NCT5538D_00"
   "AaeonIoPkg\NCT5538D\NCT5538DAsl.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT5538D/NCT5538DAsl;NCT5538D_00"
   "AaeonIoPkg\NCT5538D\NCT5538DSetup.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT5538D/NCT5538DSetup;NCT5538D_00"
   "AaeonIoPkg\NCT5538D\NCT5538DHwMonitor.cif"= "SS: AptioV;$/AptioV/Source/Hardware/SuperIo/Nuvoton/NCT5538D/NCT5538DHwMonitor;NCT5538D_00"
   "AaeonIoPkg\NCT5538D\NCT5538DMiscSetup.cif"= Private
   "AaeonIoPkg\F81804\F81804.cif"= "Private"
   "AaeonIoPkg\F81804\F81804Asl.cif"= "Private"
   "AaeonIoPkg\F81804\F81804Setup.cif"= "Private"
   "AaeonIoPkg\F81804\F81804HwMonitor.cif"= "Private"
   "AaeonIoPkg\IT8518\IT8518.cif"= "Private"
   "AaeonIoPkg\IT8518\BFPI\IT85XX_EC1_Bfpi.cif"= "Private"
   "AaeonIoPkg\IT8518\IT8518Asl.cif"= "Private"
   "AaeonIoPkg\IT8518\IT8518Setup.cif"= "Private"
   "AaeonIoPkg\AaeonIoPkg\F75113\F75113.cif"= "Private"
   "AaeonIoPkg\AaeonIoPkg\F75113\F75113MiscSetup.cif"= "Private"
   ```

DEPENDENCIES
================================

N/A

PROJECT PORTING NOTE
================================

* Override and enable SIO MASTER tokens in project .sdl file.
   * Remember to remove "Master = Yes" in the token.

   ```
   TOKEN
     Name  = "XXXXXXXX_SUPPORT"
     Value  = "1"
     Help  = "Main switch to enable XXXXXXXX support in Project"
     TokenType = Boolean
     TargetEQU = Yes
     TargetH = Yes
   End
   ```

* Follow specific SIO porting guide:
   * For **F81216SEC** - [AaeonIoPkg\F81216SEC\Porting_Guide.md](F81216SEC/Porting_Guide.md)
   * For **F81866** - [AaeonIoPkg\F81216SEC\Porting_Guide.md](F81866/Porting_Guide.md)
   * For others -
      * Review all SIO .sdl tokens and override necessary tokens in project .sdl file.
      * If project COM port is different with SIO module default - Porting .asl and LDEVICE token according to project requirement.

MODULE IMPROVEMENT NOTE
================================

## Support BFPI

* Follow [BFPI Specification](https://aaeon365-my.sharepoint.com/:f:/r/personal/nas_aaeon_com_tw/Documents/007%E8%BB%9F%E9%AB%94%E9%96%8B%E7%99%BC%E8%99%95/BIOS/Public/Documents/BFPI).

* .asl - Implement function methods :
   * Number in method name should follow BFPI Spec.
      * X1XX - SIO1 (First SIO)
      * X2XX - SIO2 (Secondary SIO)
      * E1XX - EC1 (First EC)
      * E2XX - EC2 (Secondary EC)
   * Take SIO1 as example
      * DIO
         * D1GL, D1SL, D1GD, D1SD, D1GO(TBD), D1SO(TBD)
      * WDT
         * W1RC, W1ST
      * HWM
         * H1SS, H1SN, H1SL, H1RS
      * SMF
         * F1RN, F1FS, F1RL, F1TS, F1RM, F1PW, F1LP(SIO specific), F1RC, F1GM, F1SM, F1GP, F1SP

* .sdl - To support BFPI and ease project porting, improve token structure :
   * For HWM and SMF function, each sensor/FanOut should have correspond set of tokens in .sdl - one "SUPPORT" token, one "NAME" token, and one "STRING" token.
   * SUPPORT - When switched on :
      * Support sensor/FanOut through BFPI.
      * Support showing corresponded items in BIOS setup menu.
   * NAME -
      * For BIOS setup to display.
      * Must use one of pre-defined name in AaeonIoPkg.sdl first.
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
     Help  = "Sensor name to be displayed in setup menu and to be reported in BFPI. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no    matchness. Standard names in AaeonIoPkg.sdl 'Standard string Constants' section should be used, unless no matchness."
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

* .mak - Generate setup string according to tokens described above. (GenUniFile.exe required, refer to AaeonIoPkg.sdl and W83627DHG.mak)

* .sd - Hide HWM/SMF items according to "SUPPORT" tokens.

* For method template and descriptions, refer to following files :
   * AaeonDio3\OemDioTemplate.asl
   * AaeonBfpi\OemBfpiTemplate.asl

* Refer to W83627DHG as implementation example

* Specifically to SMF return slope unit (F1LP) function, refer to IT8518 as implementation example
