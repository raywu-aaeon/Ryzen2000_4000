#include <Pei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/IoLib.h>
#include "token.h" 
#include <AmiChipsetIoLib.h>

//#define AAEON_R_PCH_PMC_GEN_PMCON_1		0x20	// General PM Configuration 1
//#define AAEON_B_PCH_PMC_GEN_PMCON_RTC_PWR_STS	BIT2	// RTC Power Status

#define AAEON_CMOS_ADDR_PORT			0x70	// CMOS Index Port
#define AAEON_CMOS_DATA_PORT			0x71	// CMOS Data Port
//#define AAEON_CMOS_DIAGNOSTIC_STATUS_REGISTER	0x0E

VOID AaeonCmosWrite8(UINT8 Offset, UINT8 Data8)
{
	IoWrite8(AAEON_CMOS_ADDR_PORT, Offset);
	IoWrite8(AAEON_CMOS_DATA_PORT, Data8);
}

BOOLEAN AAEON_AutoLoadDefault(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){
	BOOLEAN	RtcPwrSts = FALSE;
	UINT8	CmosDiagnosticSts = FALSE;

#if MMIO_READ_RTC_PWR_STS
	RtcPwrSts = (BOOLEAN)(READ_MMIO8(BASE_ADDRESS_MMIO_READ_RTC_PWR_STS + REG_MMIO_READ_RTC_PWR_STS) & (1 << BIT_MMIO_READ_RTC_PWR_STS));
#endif
#if PCI_READ_RTC_PWR_STS
	RtcPwrSts = (BOOLEAN)(READ_PCI8(BUS_PCI_READ_RTC_PWR_STS, DEVICE_PCI_READ_RTC_PWR_STS, FUNCTION_PCI_READ_RTC_PWR_STS, REG_PCI_READ_RTC_PWR_STS) & (1 << BIT_PCI_READ_RTC_PWR_STS));
#endif

	IoWrite8(AAEON_CMOS_ADDR_PORT, CMOS_DIAGNOSTIC_STATUS_REGISTER);
	CmosDiagnosticSts = IoRead8(AAEON_CMOS_DATA_PORT) & (BIT6 + BIT7);

	// Check RTC Power Status bit(RTC_PWR_STS)
	//if (MmioRead8 (PMC_BASE_ADDRESS + AAEON_R_PCH_PMC_GEN_PMCON_1) & AAEON_B_PCH_PMC_GEN_PMCON_RTC_PWR_STS)
	if(RtcPwrSts || CmosDiagnosticSts)
	{
		//clear CMOS of TPM D0,D1,E3
		//IoWrite8(0x70, 0x00);
		//IoWrite8(0x71, 0x00);
		//IoWrite8(0x70, 0x02);
		//IoWrite8(0x71, 0x00);
		//IoWrite8(0x70, 0x04);
		//IoWrite8(0x71, 0x00);

		AaeonCmosWrite8(0, 0);
		AaeonCmosWrite8(2, 0);
		AaeonCmosWrite8(4, 0);
		AaeonCmosWrite8(6, 0);
		AaeonCmosWrite8(7, 0);
		AaeonCmosWrite8(8, 0);
		AaeonCmosWrite8(9, 0);

		return TRUE; // CMOS clear
	}
	else
		return FALSE;
}
