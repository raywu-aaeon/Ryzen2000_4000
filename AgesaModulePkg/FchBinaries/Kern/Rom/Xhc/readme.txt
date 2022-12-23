############################Release Notes#################################

(c) Copyright 2009-2015 Advanced Micro Devices, Inc.  All rights reserved.  

LIMITATION OF LIABILITY:  THE MATERIALS ARE PROVIDED AS IS WITHOUT ANY EXPRESS OR
IMPLIED WARRANTY OF ANY KIND INCLUDING WARRANTIES OF MERCHANTABILITY, 
NONINFRINGEMENT OF THIRD-PARTY INTELLECTUAL PROPERTY, OR FITNESS FOR ANY PARTICULAR
PURPOSE. IN NO EVENT SHALL AMD OR ITS SUPPLIERS BE LIABLE FOR ANY DAMAGES 
WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
INTERRUPTION, LOSS OF INFORMATION) ARISING OUT OF THE USE OF OR INABILITY TO USE
THE MATERIALS, EVEN IF AMD HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
BECAUSE SOME JURISDICTIONS PROHIBIT THE EXCLUSION OR LIMITATION OF LIABILITY FOR
CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
AMD does not assume any responsibility for any errors which may appear in the 
Materials nor any responsibility to support or update the Materials.  AMD
retains the right to make changes to its test specifications at any time, 
without notice.  NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, 
or make any further information, software, technical information, know-how, or 
show-how available to you.
U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials and documentation are provided 
with RESTRICTED RIGHTS.  Use, duplication or disclosure by the Government is 
subject to restrictions as set forth in FAR52.227014 and DFAR252.227-7013, et
seq., or its successor.  Use of the Materials by the Government constitutes
acknowledgment of AMD’s proprietary rights in them.


===========================================================================
                                                                         
            	      AMD xhc firmware for KERN
                         Version 2.1.0.0085
                      Release date (01/21/2015)

Contents

  1  Introduction
  2  Included Files
  3  integration
  4  Revision History

===========================================================================


1. Introduction
===============

xHC firmware based on Bolton & Yangtze.
And add new features: 4port, AOAC and standard service interval
support MIPI instead of PCI.


2. Included Files
=================
Kern.rom -xhc firmware binary.


3. integration
==========================================================
Firmware will be checked into http://svn/BIOS/Frameworks/AGESA/AGESA-V5/trunk/Addendum/Fch/Kern/Rom/Xhc.  
Refer to section 8 of the Hudson-2-3 RPR document for information on integrating the firmware image into system BIOS.


4. Revision History
===================

Version 2.1.0.0085 (01/21/2015)
	Fix ENH4: Firmware to set the PORTSC.DR for each port.
	Merge UBTS-Bug fix from WT.

Version 2.1.0.0082 (10/22/2014)
	Fix OBS: add a WA for clear D3Cold status when driver reset controller.

Version 2.1.0.0071 (09/17/2014)
	Fix UBTSBug  : [FW]After S3 wake on overcurrent in D3Hot2D3Cold windown, LTSSM stuck at SS.Disabled 
	Fix UBTS Bug : [AOAC]the link wouldn't be in L1 after waking from D3.
	Fix UBTS Bug : Stopped transfer event not generated on stop endpoint command execution if the endpoint was already in stopped state
	Fix UBTS Bug :
		AOAC-FPGA: Parts of the contexts are corrupted by FW when saving into system memory in [KernCZ][FW-USB3]
		Update FW for Streaminfo(SS-Stream) DW5[14:9] in [KernCZ][FW-USB3]
	Fix UBTS Bug : Review All FW Change Request in "Kern_USB3_4P_FW_change_req" in [KernCZ].
	Fix UBTS Bug : Update FW for Streaminfo(SS-Stream) DW5[14:9] in [KernCZ]
	Fixed UBTS Bug : RPN in Resolve Table is not programmed properly in [KernCZ][FW-USB3].
	Fixed UBTS Bug : MVSIM failed case.change sequence for adding endpoint schedule.
	Support to Display FW build version with BIOS
	Support full range service interval.
	Support 4 ports and AOAC.
	Creat kern branch based on trunk.
