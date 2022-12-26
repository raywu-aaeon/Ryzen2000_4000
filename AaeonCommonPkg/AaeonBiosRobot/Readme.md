Table of content
1. [AAEON BIOS Robot](#AAEON BIOS Robot)
2. [FILES NOTE](#FILES-NOTE)
3. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)

AAEON BIOS Robot
================================

1.Support watch dog before BIOS post.
  Robot set Watch Dog Timer(WDT) right after power on, before BIOS start POST process.
  And then Robot will clear WDT on completion of POST.

2.Support watch dog before booting os.
  Robot set Watch Dog Timer(WDT) after POST completion, before BIOS transfer control to OS.

3.Support delay post.
  Robot holds BIOS from starting POST, right after power on.

4.Support reset system once on each boot.
  Robot resets system for one time on each boot.

5.Support five device detecting configuration.

FILES NOTE
================================

* .sdl
  * AaeonBiosRobot.sdl - Main configurations to this module.
  * WatchRobot.sdl - Configurations to WatchRobot module.
  * SentryRobot.sdl - Configurations to SentryRobot module.
  * PowerOnRobot.sdl - Configurations to PowerOnRobot module.
* .c
  * WatchDogRobotPei.c - Enable watch dog function before the system initial memory.
  * WatchDogRobotDxeLib.c - Close watch dog function before the system boot to  OS. 
  * WatchDogRobotACPILib.c - Enable watch dog function before the system boot to  OS. 
  * PowerOnRobotDxeReset.c - Reset system for one time on each boot.
  * PowerOnRobotDxe.c - Follow bios setting to Period of time for Robot to hold BIOS from POST at DXE phase.
  * PowerOnRobotPei.c - Follow bios setting to Period of time for Robot to hold BIOS from POST at PEI phase.
  * SentryRobotLib.c - Device detecting configuration function.
  * BIOSRobotCommonFunction.C - EC access common function.
* .h
  * BIOSRobotCommonFunction.h - Define EC access and SIO access variable.	

PROJECT PORTING NOTE
================================
1. The project need support DIO3 for DIO status check function.
   If your project don't need to support DIO status check function don't care DIO3 module support.
       
2. Add following codes after ""AaeonCommon\AaeonCommonPkg.cif"= Private" in veb file.
==>>
"AaeonCommonPkg\AaeonBiosRobot\AaeonBiosRobot.cif"= Private
"AaeonCommonPkg\AaeonBiosRobot\PowerOnRobot\PowerOnRobot.cif"= Private
"AaeonCommonPkg\AaeonBiosRobot\SentryRobot\SentryRobot.cif"= Private
"AaeonCommonPkg\AaeonBiosRobot\WatchRobot\WatchRobot.cif"= Private
<<==

3. Add the "AaeonBiosRobot" under module part in "AaeonCommonPkg\AaeonCommonPkg.cif" file.

4. BIOS robot module use 2 cmos registers please help to check no other one using.
   Token:BIOS_ROBOT_FLAG_REG¡BOS_WATCH_DOG_TIME_FLAG_REG

5. The module has re-define the token value in AaeonBiosRobotCommonLib.h dependent on SIO module setting.
   Setting SIO entry key and index data port in "AaeonBiosRobotPkg.sdl if you don't want to use default setting.

6. Modify the "ROBOT_WDT_CHIP_TYPE" token to select watch dog chip type if your project not support BFPI.

7. Modify the "ROBOT_MONITOR_SIO_CHIP_TYPE" token to select BIOS robot monitor SIO chip type if your project not support BFPI.
   The monitor SIO chip default setting is same as watch dog chip type if your project support BFPI.


