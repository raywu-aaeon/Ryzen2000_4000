IF %1 == BR (
	@start /MAX /WAIT AmiPspPkg\WaitForSign.cmd %1 PSB\%1\RTM.bin PSB\%1\RTM_L1.sig
) else (
	@start /MAX /WAIT AmiPspPkg\WaitForSign.cmd %1 PSB\%1\RTM_L1.bin PSB\%1\RTM_L1_L2.bin PSB\%1\RTM_L1.sig PSB\%1\RTM_L1_L2.sig
)
