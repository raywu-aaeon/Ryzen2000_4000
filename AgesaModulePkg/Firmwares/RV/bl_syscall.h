/*****************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */
//EMB-FP5-PSP-START
#include "bl_errorcodes.h"
//EMB-FP5-PSP-END
#ifndef _BL_SYSCALL_H_
#define _BL_SYSCALL_H_

#define SVC_EXIT                            0x00    // used
#define SVC_MAP_USER_STACK                  0x01    // used
#define SVC_LOAD_BINARY                     0x02    // used
#define SVC_MAP_SMN_ON_DIE_NUM              0x03    // not used on RV
#define SVC_MAP_SMN_ON_CURRENT_DIE          0x04    // used 
#define SVC_UNMAP_SMN                       0x05    // used 
#define SVC_DEBUG_PRINT                     0x06    // used
#define SVC_MAP_SYSHUB                      0x07    // used
#define SVC_UNMAP_SYSHUB                    0x08    // used
#define SVC_READ_SYSHUB                     0x09    // not used
#define SVC_WRITE_SYSHUB                    0x0A    // used
#define SVC_SHA256                          0x0B    // used in secure_unlock
#define SVC_MODEXP                          0x0C    // used in secure_unlock
#define SVC_RSAPSS_VERIFY                   0x0D    // used in secure_unlock
#define SVC_AES_ECB_ENCRYPT                 0x0E    // used in secure_unlock
#define SVC_SHA256_OTP                      0x0F    // used in secure_unlock
#define SVC_GET_MCM_INFO                    0x10    // not used on RV
#define SVC_WAIT_FOR_MASTER_STATUS          0x11    // not used on RV
#define SVC_SET_MASTER_STATUS               0x12    // not used on RV
#define SVC_MASTER_BROACAST                 0x13    // not used on RV
#define SVC_SLAVE_GET_BROACAST_DATA         0x14    // not used on RV
#define SVC_SAVE_APOB_DATA                  0x15    // used
#define SVC_SEARCH_BIOS_DIR					0x16    // used
#define SVC_GET_DATA_FROM_SLAVES			0x17    // not used on RV
#define SVC_SEND_DATA_TO_MASTER				0x18    // not used on RV
#define SVC_SET_DEBUG_STATE					0x19    // used
#define SVC_DEBUG_PRINT_EX					0x1A    // used
#define SVC_WAIT_10NS_MULTIPLE				0x1B    // used - it seems ABL has not moved to 2F
#define SVC_GET_BOOT_MODE                   0x1C    // used
#define SVC_OTP_HMAC256_SIGN                0x1D    // used
#define SVC_SPILOAD_VALIDATE_HMAC256_APOB   0x1E    // used on resume
#define SVC_GET_DEBUG_UNLOCK_INFO           0x1F    // used in secure_unlock
#define SVC_SET_DEBUG_UNLOCK_INFO           0x20    // used in secure_unlock
#define SVC_PROGRAM_UMC_KEYS                0x21    // used
#define SVC_READ_SMBUS_BYTE					0x22    // not used on RV
#define SVC_SYNC_UNLOCK_VECTOR              0x23    // not used on RV
#define SVC_MCM_SYNC_ON_DATA                0x24    // not used on RV
#define SVC_MAP_SYSHUB_EX					0x25    // not used currently but can be used
#define SVC_READ_SYSHUB_EX					0x26    // used
#define SVC_WRITE_SYSHUB_EX					0x27    // used 
#define SVC_SEND_PSP_SMU_MSG				0x28    // used
#define SVC_WRITE_SMBUS_BYTE                0x29    // not used on RV
#define SVC_SET_PSP_SMU_RESERVED            0x2A    // used - why are we gettting this service call
#define SVC_MCM_SYNCHRONIZATION_POINT       0x2B    // used - why are we getting this service call
#define SVC_GMI_NON_FUNCTIONAL              0x2C    // not used on RV
#define SVC_LOAD_FW_IMAGE_BY_INSTANCE       0x2D    // used
#define SVC_READ_SECURE_RTC                 0x2E    // not used currently but requested by ABL
#define SVC_DELAY_IN_MICRO_SECONDS          0x2F    // not used currently but requested by ABL
#define SVC_ADD_ENTRY_MP2_RAM1              0x30    // not used currently but ABL need to use this
#define SVC_READ_ENTRY_MP2_RAM1             0x31    // not used currently but ABL need to use this
#define SVC_LOAD_BINARY_BY_ATTRIB           0x32    // used 
#define SVC_HMAC_256                        0x33    // not used currently but ABL need to use this.
#define SVC_LOAD_APOB_CHUNK_BY_CHUNK        0x34    // used on resume

// EMB-FP5-PSP-START
// Embedded-FP5 SYSCALLs
#define SVC_RPMC_SWITCH                     0x70
// EMB-FP5-PSP-END
/*-----------------------------------------------------------------------------
    Mod Exp parameter structure as services can only pass in 4 parameters
*/
typedef struct MOD_EXP_PARAMS_T
{
    char                *pExponent;     // Exponent address
    unsigned int        ExpSize;        // Exponent size in bytes
    char                *pModulus;      // Modulus address
    unsigned int        ModulusSize;    // Modulus size in bytes
    char                *pMessage;      // Message address
    char                *pOuput;        // Output address; Must be big enough to hold the data of ModulusSize
} MOD_EXP_PARAMS;

/*-----------------------------------------------------------------------------
    RSA PSS parameter structure as services can only pass in 4 parameters
*/
typedef struct RSAPSS_VERIFY_PARAMS_T
{
    char                *pHash;         // Message digest to verify the RSA signature
    unsigned int        HashLen;        // hash length in bytes
    char                *pModulus;      // Modulus address
    unsigned int        ModulusSize;    // Modulus length in bytes
    char                *pExponent;     // Exponent address
    unsigned int        ExpSize;        // Exponent length in bytes
    char                *pSig;          // Signature to be verified, same size as ModulusSize
} RSAPSS_VERIFY_PARAMS;

/*-----------------------------------------------------------------------------
    AES ECB parameter structure as services can only pass in 4 parameters
*/
typedef struct AES_ECB_ENCRYPT_PARAMS_T
{
    unsigned int        Key;            // Key (either pointer to local memory or LSB number)
    unsigned int        KeyMemType;     // Key memory type
    unsigned int        KeySize;        // Key size in bytes; valid values 16, 24 and 32
    char                *pSrc;          // Source address, must be 16 byte aligned
    unsigned int        SrcMemType;     // Source memory type
    unsigned int        SrcLen;         // Source length, must be non-zero multiple of 16
    char                *pDest;         // Destinateion address, must be 16 byte aligned
    unsigned int        DestMemType;    // Destination memory type
} AES_ECB_ENCRYPT_PARAMS;

// Type & BIOS_FIRMWARE Attribute field
//
typedef struct TypeAttrib_t
{
    uint32_t Type : 8;              // Type of BIOS entry 0x60,0x61,0x62
    uint32_t RegionType : 8;        // 0 - non Secure, 1 - ARM TA1 , 2 - ARM TA2 , 3 - ARM TMZ, 4 - Reset
    uint32_t BiosResetImage : 1;    // Set for SEC or EL3 fw,
    uint32_t Copy : 1;              // Set for copy
    uint32_t ReadOnly : 1;          // 0 - write, 1 - read only
    uint32_t CompressedZlib : 1;    // 0 - no compression, 1 - Zlib compressed
    uint32_t Instance : 4;          // Specify the instance of an entry
    uint32_t SubProgram : 3;        // Specify the SubProgram
    uint32_t RomId : 2;             // Specify the RomId
	uint32_t Writable : 1;          // 1:Region writable; 0: Region read-only  for ROM_ARMOR_2
	uint32_t Reserved : 2;
} TypeAttrib;

typedef uint8_t     BIOS_DIRECTORY_ENTRY_TYPE;
typedef TypeAttrib  BIOS_DIRECTORY_TYPE_ATTRIB;

typedef struct {
	BIOS_DIRECTORY_ENTRY_TYPE 	EntryType;
	uint32_t 					*pDataSourceAddr; 
	uint64_t 					*pDataDestAddr; 
	uint32_t 					*pDataLength; 
	BIOS_DIRECTORY_TYPE_ATTRIB 	*pAttrib; 
	uint8_t 					index;
}BIOS_DIR_SEARCH_PARMS;

typedef struct {
    uint32_t                    Size;               // Size of (BIOS_DIR_SEARCH_PARMS_v2)
    void                        **pSmnBiosDirBaseAddr; // SMN address mapped by PSP on gBiosBaseAddr
	BIOS_DIRECTORY_ENTRY_TYPE 	EntryType;
	uint32_t 					*pDataSourceAddr; 
	uint64_t 					*pDataDestAddr; 
	uint32_t 					*pDataLength; 
	BIOS_DIRECTORY_TYPE_ATTRIB 	*pAttrib; 
	uint8_t 					index;
}BIOS_DIR_SEARCH_PARMS_V2;

typedef enum _BIOS_DIRECTORY_ENTRY_TYPE {
    BIOS_PUBLIC_KEY                 = 0x05, // BIOS OEM public key, signed by AMD root private key
    BIOS_APCB_INFO					= 0x60, // Agesa PSP Customization Block (APCB)
    BIOS_APOB_INFO	                = 0x61, // Agesa PSP Output Block (APOB) target location
    BIOS_FIRMWARE           		= 0x62, // BIOS Firmware volumes, also referred as RTM volume with reset flag
    BIOS_APOB_DATA             		= 0x63, // Agesa PSP Output Block data and HMAC
    BIOS_APCB_RO_INFO               = 0x68, // Agesa RO PSP Customization Block (APCB)
    BIOS_MP2_CONFIG_FILE            = 0x6A,
} BIOS_DIRECTORY_ENTRY_TYPE_E;

typedef enum _PSP_BOOT_MODE
{
	PSP_BOOT_MODE_S0 = 0x0,
	PSP_BOOT_MODE_S0i3_RESUME = 0x1,
	PSP_BOOT_MODE_S3_RESUME = 0x2,
	PSP_BOOT_MODE_S4 = 0x3,
	PSP_BOOT_MODE_S5_COLD = 0x4,
	PSP_BOOT_MODE_S5_WARM = 0x5,
} PSP_BOOT_MODE;

//    TLB2_n settings for AWUSER and TLB3_n settings for ARUSER: 
//    USER[0] - ReqIO bit, 1'b1 for FCH MMIO address
//    USER[1] - Compat bit, 1'b1 for FCH access, 0 for everything else
//    USER[2] - ByPass_IOMMU bit, 1'b1 to always bypass IOMMU, 0 for IOMMU translation
typedef enum SYSHUB_TARGET_TYPE_E
{
	// Target Type						// Address				// [2:0] =[ Bypass,Compat,ReqIO]
	AxUSER_PCIE_HT0				= 0x0,	// PCIe HT (Bypass=0)		// [2:0] =[ 0,0,0]
	AxUSER_DRAM_VIA_IOMMU       = 0x1,  // DRAM ACCESS via IOMMU	// [2:0] =[ 0,0,1]
	AxUSER_PCIE_HT1				= 0x2,	// PCIe HT  (Bypass=1)		// [2:0] =[ 0,1,0]			
	AxUSER_RSVD					= 0x3,	// - NOT USED ,INVALID 		// [2:0] =[ 0,1,1]
	AxUSER_DRAM_BYPASS_IOMMU 	= 0x4, 	// GENERAL DRAM 			// [2:0] =[ 1,0,0]
	AxUSER_PCIE_MMIO			= 0x5,	// PCIe MMIO				// [2:0] =[ 1,0,1]
	AxUSER_FCH_HT_IO 			= 0x6,  // FCH HT (port80)			// [2:0] =[ 1,1,0]
#if 0
	AxUSER_FCH_MMIO 			= 0x7   // FCH MMIO 				// [2:0] =[ 1,1,1]
#else
        // TODO(bwd): clean-up properly
	AxUSER_FCH_MMIO 			= 0x6   // FCH MMIO 				// [2:0] =[ 1,1,1]
#endif
	// HDM: TODO Bit ATid[5:3] – Address Translation ID, indication of which page table will be used
	// in IOMMU, (only valid when Bypass=1’b0, but we have 3 of those)
} SYSHUB_TARGET_TYPE;


typedef struct SYSHUB_RW_PARMS_EX_E
{
	unsigned int SyshubAddressLo;
	unsigned int SyshubAddressHi;
	unsigned int* pValue;
	unsigned int Size;
	SYSHUB_TARGET_TYPE TargetType;
} SYSHUB_RW_PARMS_EX;

// Master status bits [31:24] assigned as AGESA status bits. It is up to AGESA team
// to define individual bit values.
#define AGESA_MASTER_STATUS_BITS        0xFF000000

#define CLIENT_ID_AGESA                 0

/*-----------------------------------------------------------------------------
    Exit to the main Boot Loader. This does not return back to user application.

    Parameters:
        Status  -   either Ok or error code defined by AGESA
*/
__svc(SVC_EXIT) void Svc_Exit( unsigned int Status );


/*-----------------------------------------------------------------------------
    Maps buffer for stack usage.

    Parameters:
        StartAddr   -   start address of the stack buffer
        EndAddr     -   end of the stack buffer
        pStackVa    -   [out] mapped stack Virtual Address

    Return value: BL_OK or error code
*/
__svc(SVC_MAP_USER_STACK) unsigned int Svc_MapUserStack(    unsigned int    StartAddr,
                                                            unsigned int    EndAddr,
                                                            unsigned int*   pStackVa );

/*-----------------------------------------------------------------------------
    Maps buffer for stack usage.

    Parameters:
        PspDirType  -   type of PSP directory entry to load from
        pDest       -   memory address to load data to
        pDestSize   -   on input - max pDest size, on output - actual loaded size

    Return value: BL_OK or error code
*/
__svc(SVC_LOAD_BINARY) unsigned int Svc_LoadBinary( BIOS_DIRECTORY_ENTRY_TYPE_E    PspDirType,
                                                    void*           pDest,
                                                    unsigned int*   pDestSize );

#if 0
/*-----------------------------------------------------------------------------
    Map SMN TLB for access to SMN address on specific die in MCM configuration.

    Parameters:
        SmnAddress  -   address in SMN address space
        DieNum      -   die number on which the SMN address is located

    Return value:
        on success  -   mapped address in AXI space
        on error    -   NULL
*/
__svc(SVC_MAP_SMN_ON_DIE_NUM) void* Svc_MapSmnOnDieNum( unsigned int    SmnAddress,
                                                        unsigned int    DieNum );
#endif

/*-----------------------------------------------------------------------------
    Map SMN TLB for access to SMN address on the current die.

    Parameters:
        SmnAddress  -   address in SMN address space

    Return value:
        on success  -   mapped address in AXI space
        on error    -   NULL
*/
__svc(SVC_MAP_SMN_ON_CURRENT_DIE) void* Svc_MapSmnOnCurrentDie( unsigned int SmnAddress );


/*-----------------------------------------------------------------------------
    Unmap SMN TLB for AXI address previously mapped using Svc_MapSmnOnDieNum()
    or Svc_MapSmnOnCurrentDie().

    Parameters:
        pAxiAddress -   address in AXI address space previously mapped
                        using Svc_MapSmnOnDieNum() or Svc_MapSmnOnCurrentDie()

    Return value: BL_OK or error code
*/
__svc(SVC_UNMAP_SMN) unsigned int Svc_UnmapSmn( void* pAxiAddress );


/*-----------------------------------------------------------------------------
    Enable or disable debug printing in simnow environment dynamically during runtime.

    Parameters:
        fEnable -   1 to enable debug print output, 0 to disable
*/
__svc(SVC_SET_DEBUG_STATE) void Svc_SetDebugState( uint32_t fEnable );


/*-----------------------------------------------------------------------------
    Print debug message into SimNow console. In emulation environment and on
    real silicon does not do anything.

    Parameters:
        pString -   null-terminated string
*/
__svc(SVC_DEBUG_PRINT) void Svc_DebugPrint( char* pString );


/*-----------------------------------------------------------------------------
    Print 4 DWORD values in hex into SimNow console. In emulation environment and on
    real silicon does not do anything.

    Parameters:
        Dword0...Dword3 - 32-bit DWORD to print
*/
__svc(SVC_DEBUG_PRINT_EX) void Svc_DebugPrintEx( 	uint32_t Dword0, 
													uint32_t Dword1,
													uint32_t Dword2,
													uint32_t Dword3);


/*-----------------------------------------------------------------------------
    Map SYSHUB TLB for access to SYSHUB address.

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space

    Return value:
        on success  -   mapped address in AXI space
        on error    -   NULL
*/
__svc(SVC_MAP_SYSHUB) void* Svc_MapSysHub( unsigned int SyshubAddressLo, unsigned int SyshubAddressHi );


/*-----------------------------------------------------------------------------
    Unmap SYSHUB TLB for AXI address previously mapped using Svc_MapSyshub().

    Parameters:
        pAxiAddress -   address in AXI address space previously mapped
                        using Svc_MapSyshub()

    Return value: BL_OK or error code
*/
__svc(SVC_UNMAP_SYSHUB) unsigned int Svc_UnmapSysHub( void* pAxiAddress );


/*-----------------------------------------------------------------------------
    Read 32-bit value from SYSHUB address.

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space
        pValue          -   location for the value to be written
        Size            -   size of the value in bytes; valid values: 1, 2 and 4

    Return value: BL_OK or error code
*/
__svc(SVC_READ_SYSHUB) unsigned int Svc_ReadSysHub( unsigned int    SyshubAddressLo,
                                                    unsigned int    SyshubAddressHi,
                                                    unsigned int*   pValue,
                                                    unsigned int    Size );

/*-----------------------------------------------------------------------------
    Write 32-bit value to SYSHUB address.

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space
        Value           -   value to be written
        Size            -   size of the value in bytes; valid values: 1, 2 and 4

    Return value: BL_OK or error code
*/
__svc(SVC_WRITE_SYSHUB) unsigned int Svc_WriteSysHub(   unsigned int SyshubAddressLo,
                                                        unsigned int SyshubAddressHi,
                                                        unsigned int Value,
                                                        unsigned int Size );

/*-----------------------------------------------------------------------------
    Calculate SHA256

    Parameters:
        pData           -   Address of the data to be hashed
        DataLen         -   Length of data to be hashed
        pHash           -   Hashed ouput
        Size            -   Size of hashed output

    Return value: BL_OK or error code
*/
__svc(SVC_SHA256) unsigned int Svc_SHA256(   char *         pData,
                                             unsigned int   DataLen,
                                             char *         pHash );

/*-----------------------------------------------------------------------------
    Calculate ModEx

    Parameters:
        pModExParams           -   ModExp parameters

    Return value: BL_OK or error code
*/
__svc(SVC_MODEXP) unsigned int Svc_MODEXP( MOD_EXP_PARAMS *         pModExParams );

/*-----------------------------------------------------------------------------
    RSA PSS Verification of signature and data

    Parameters:
        RSAPSS_VERIFY_PARAMS           -   Pointer to RSA PSS parameters

    Return value: BL_OK or error code
*/
__svc(SVC_RSAPSS_VERIFY) unsigned int Svc_RSAPSSVerify( RSAPSS_VERIFY_PARAMS *   pRSAPSSParams );

/*-----------------------------------------------------------------------------
    AES ECB Encrypt

    Parameters:
        AES_ECB_ENCRYPT_PARAMS           -   AES ECB Encrypt parameters

    Return value: BL_OK or error code
*/
__svc(SVC_AES_ECB_ENCRYPT) unsigned int Svc_AesEcbEncrypt( AES_ECB_ENCRYPT_PARAMS *   pAesEcbEncryptParam );

/*-----------------------------------------------------------------------------
    Compute SHA256 hash of OTP Key slot 0

    Parameters:
        pHash           -   Hash output

    Return value: BL_OK or error code
*/
__svc(SVC_SHA256_OTP) unsigned int Svc_Sha256OTP( char *   pHash );

//-----------------------------------------------------------------------------
// Description      : Reads BIOS Directory into global buffer, and searches the directory for an entry
//
// Parameters       :
//
// Return Values    : BL_OK or error code
//
//-----------------------------------------------------------------------------
__svc(SVC_SEARCH_BIOS_DIR) uint32_t Svc_BIOSDirectorySearch(BIOS_DIR_SEARCH_PARMS* pParms);

#if 0
/*-----------------------------------------------------------------------------
    Get data from one or more slave dies

    Parameters:
    	ClientId		 - Client Id
        pData             - Input/output pointer to place returned data
        pDataSize       - Input/output pointer to place return data block size (max 32Bytes)
        pSlaveId         - Input/output pointer to place returning ID of slave

    Return value: BL_OK, BL_ERR_MORE_DATA, or a BL error
*/
__svc(SVC_GET_DATA_FROM_SLAVES) uint32_t Svc_GetDataFromSlaves(uint32_t ClientId, uint32_t* pData,
															   uint32_t* pDataSize, uint32_t* pSlaveId );

/*-----------------------------------------------------------------------------
    Send data from slave to the local master

    Parameters:
    	ClientId		- Client Id 
        pData           - Input pointer containing data to send (max 32Bytes)
        DataSize       - Input integer containing number of 32bit DWORDs to send
        Eod         	- Input integer containing EoD signal when done sending blocks (0 or 1)

    Return value: BL_OK, or another BL error
*/
__svc(SVC_SEND_DATA_TO_MASTER) uint32_t Svc_SendDataToMaster(uint32_t ClientId, uint32_t* pData,
															 uint32_t DataSize, uint32_t Eod );
#endif

/*-----------------------------------------------------------------------------
    Waits in a blocking call for multiples of 10ns (100MHz timer) before returning

    Parameters:
    	Multiple		- The number of multiples of 10ns to wait

    Return value: BL_OK, or BL_ERR_TIMER_PARAM_OVERFLOW
*/
__svc(SVC_WAIT_10NS_MULTIPLE) uint32_t Svc_Wait10nsMultiple(uint32_t Multiple);


//-----------------------------------------------------------------------------
//
// Description      :   Returns the current boot mode from the type PSP_BOOT_MODE found in
//                      bl_public.h.
//
// Inputs           :   pBootMode - Output parameter passed in R0
//
// Outputs          :   The boot mode in pBootMode.
//                      See Return Values.
// 
// Return Values    :   BL_OK
//                      BL_ERR_NULL_PTR
//                      Other BL_ERRORs lofted up from called functions
//
//-----------------------------------------------------------------------------
__svc(SVC_GET_BOOT_MODE) uint32_t Svc_GetBootMode(uint32_t *pBootMode);

//-----------------------------------------------------------------------------
//
// Description      :   Returns the parameter for debug unlock information 
//                      bl_public.h.
//
// Inputs           :   pData  - Address point to DebugUnlockInfo Structure.
//                  :   DataSize - Size of the pData structure. 
//
// Outputs          :   NULL 
// 
// Return Values    :   BL_OK 
//                      BL_ERR_DATA_LENGTH - 
//                      Other BL_ERRORs lofted up from called functions
//
//-----------------------------------------------------------------------------
__svc(SVC_GET_DEBUG_UNLOCK_INFO) uint32_t Svc_GetDebugUnlockInfo(void *pData, void* pKdsPubKey, uint32_t KeyLen);



//-----------------------------------------------------------------------------
//
// Description      :   Communicate the debug unlock information back to BL  
//                      bl_public.h.
//
// Inputs           :   pData  - Address point to DebugUnlockInfo Structure.
//                  :   DataSize - Size of the pData structure. 
//
// Outputs          :   NULL 
// 
// Return Values    :   BL_OK 
//                      BL_ERR_DATA_LENGTH - 
//                      Other BL_ERRORs lofted up from called functions
//
//-----------------------------------------------------------------------------
__svc(SVC_SET_DEBUG_UNLOCK_INFO) uint32_t Svc_SetDebugUnlockInfo(void *pData);

//-----------------------------------------------------------------------------
// Description      : Calculate HMAC 256 bits using OPN derived HMAC key. 
//                    This API can calculate new HMAC or validate older HMAC
//                    based on flag parameter.
//					  This will use a special gApobHmacKey rather than the
//                    internal gHmacKey
//
// Parameters       : pData     [in]        - Pointer to Data for HMAC
//                    DataSize  [in]        - Size of Data
//                    pHmac     [in/out]    - Pointer to HMAC value
//                    Flag      [in]        - 0: Calculate new HMAC
//                                            1: Validate HMAC
//
// Return values    : BL_OK (0x0) - all requested operations passed successfully 
//                    BL_ERR_HMAC_VALIDATION (0x25) - HMAC validation fail 
//                    or error code - any other operation failed
//-----------------------------------------------------------------------------
__svc(SVC_HMAC_256) uint32_t Svc_Hmac256( uint8_t *pData, uint32_t DataSize, uint8_t *pHmac, uint32_t Flag );

//-----------------------------------------------------------------------------
// Description      : Validates HMAC and loads S3 data. Each die should call 
//                    this during S3 resume to get the APOB data
//
// Parameters       : DataApobOffset [in]  - S3 DataInfo offset from APOB entry 0x63
//                    pDestAddr      [out] - SRAM location to be copied
//                    DataSize       [in]  - S3 DataSize in bytes to read
//                    HmacApobOffset [in]  - SpiOffset from APOB entry where HMAC is stored
//                                          Will read 32 bytes from offset value provided
//
// Return Values    : BL_OK or error code
//
//----------------------------------------------------------------------------
__svc(SVC_LOAD_APOB_CHUNK_BY_CHUNK) uint32_t Svc_ValidateAndLoadAPOB(uint32_t DataApobOffset, uint8_t *pDestAddr, uint32_t DataSize, uint32_t HmacApobOffset);

//-----------------------------------------------------------------------------
//
// Description      :   Programs UMC keys -- generating them on S5, and restoring them from DRAM for S3.
//                      UMC keys must be shared between dies on S5 using DRAM as a shared mailbox,
//                      and restored from DRAM on S3.
//                      Therefore DRAM MUST be trained and PSP should be able to access PSP Secure Memory
//                      before AGESA calls Svc_ProgramUmcKeys().
//
// Inputs           :   None.
//
// Outputs          :   See Return Values.
// 
// Return Values    :   BL_OK
//
//-----------------------------------------------------------------------------
__svc(SVC_PROGRAM_UMC_KEYS) uint32_t Svc_ProgramUmcKeys(uint32_t Flags, uint16_t AddrTweakEn);

#if 0
/*-----------------------------------------------------------------------------
    Reads a byte from the slave specified with the command provided over SMBus

    Parameters:
    	SlaveAddr[in]		- The 7bit slave address shifted left by 1bit (x2)
    	Command[in]			- The 8bit device specific command
    	pByteRead[out]		- A pointer to a char to hold the byte read

    Return value: BL_OK, or a BL_ERROR code
*/
__svc(SVC_READ_SMBUS_BYTE) uint32_t Svc_ReadSmbusByte(char SlaveAddr, char Command, char* pByteRead);

/*-----------------------------------------------------------------------------
    Writes a byte to the slave specified with the command provided over SMBus

    Parameters:
    	SlaveAddr[in]		- The 7bit slave address shifted left by 1bit (x2)
    	Command[in]			- The 8bit device specific command
    	ByteRead[in]		- A byte to write to the specified address

    Return value: BL_OK, or a BL_ERROR code
*/
__svc(SVC_WRITE_SMBUS_BYTE) uint32_t Svc_WriteSmbusByte(char SlaveAddr, char Command, char ByteWrite);

/*-----------------------------------------------------------------------------
    For MCM master - broadcasts the vector information. For slaves - recives it

    Parameters:
        Aeb0, Aeb1, Mp1Aeb - unlock vector components

    Return value: BL_OK, or a BL_ERROR code
*/
__svc(SVC_SYNC_UNLOCK_VECTOR) uint32_t Svc_SyncUnlockVector(uint32_t* Aeb0, uint32_t* Aeb1, uint32_t* Mp1Aeb);

/*-----------------------------------------------------------------------------
    For MCM master - gathering the 32 bit information from each slave and storing in the array pointed with `data`
    For MCM slaves - sending the 32-bit data pointed by `data` to the master

    Return value: BL_OK, or a BL_ERROR code
*/
__svc(SVC_MCM_SYNC_ON_DATA) uint32_t Svc_McmSyncOnData(uint32_t* data);

#endif

/*-----------------------------------------------------------------------------
    Map 64-bit SYSHUB target address for access via 32-bit AXI address  (Extended functionality).

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space
        TargetType - type of SYSHUB target
        

    Return value:
        on success  -   mapped address in AXI space
        on error    -   NULL
*/
__svc(SVC_MAP_SYSHUB_EX) void* Svc_MapSysHubEx(uint32_t SyshubAddressLo,
                                               uint32_t SyshubAddressHi,
                                               SYSHUB_TARGET_TYPE TargetType);

/*-----------------------------------------------------------------------------
    Read 32-bit value from SYSHUB address (Extended functionality).

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space
        pValue          -   destination pointer
        Size            -   size of read value in bytes; valid values: 1, 2 and 4
        TargetType - type of SYSHUB target

    Return value: BL_OK or error code
*/
__svc(SVC_READ_SYSHUB_EX) unsigned int Svc_ReadSysHubEx(SYSHUB_RW_PARMS_EX* pParms);

/*-----------------------------------------------------------------------------
    Write 32-bit value to SYSHUB address (Extended functionality).

    Parameters:
        SyshubAddressLo -   low order 32 bit of address in SYSHUB address space
        SyshubAddressHi -   high order 32 bit of address in SYSHUB address space
        pValue           -   source pointer
        Size            -   size of source value in bytes; valid values: 1, 2 and 4
        TargetType - type of SYSHUB target

    Return value: BL_OK or error code
*/
__svc(SVC_WRITE_SYSHUB_EX) unsigned int Svc_WriteSysHubEx(SYSHUB_RW_PARMS_EX* pParms);


/*-----------------------------------------------------------------------------
    Send an SMU/SMC message from PSP to SMU, and block until a response is received.

    Parameters:
        MsgId 		- SMU2PSP message id to send (no error checking is done on validity)
        MsgArg 		- DWORD containing message specific payload/arguments
        pMsgResp    	- pointer to store response read/returned from SMU

    Return value: BL_OK or error code
*/
__svc(SVC_SEND_PSP_SMU_MSG) unsigned int Svc_SendPspSmuMsg(uint32_t MsgId, uint32_t MsgArg, uint32_t* pMsgResp);

#if 0
/*-----------------------------------------------------------------------------
    Synchronizes master and slaves at a "barrier" point.

    Parameters:
        SyncPointFlag 	- This flag must be used only once in a given boot sequence, and be unique from all
        					other flags. It is a bitmask of all of the flags slaves are expecting

    Return value: SyncPointFlag for master and the actual received status for the slaves
*/
__svc(SVC_MCM_SYNCHRONIZATION_POINT) uint32_t Svc_McmSynchronizationPoint(uint32_t SyncPointFlag);
#endif

// HDM - remove this when no more need of PCIe dGPU memory hack
__svc(SVC_SET_PSP_SMU_RESERVED) uint32_t Svc_SetPspSmuReservedAddrs(uint32_t PspSecurePhysAddrLo,
                                                                    uint32_t PspSecurePhysAddrHi,
                                                                    uint32_t SmuReservedPhysAddrLo,
                                                                    uint32_t SmuReservedPhysAddrHi);

#if 0

__svc(SVC_GMI_NON_FUNCTIONAL) uint32_t Svc_GmiNonFunctional(void);

#endif
/*-----------------------------------------------------------------------------
    Load a binary from the BIOS directory table by instance type. The binary should be signed, and can be
    compressed.

    Parameters:
        BiosDirType     - From entry header in BIOS directory table.
        pDest           - Pointer to where the binary should be loaded to.
        pDestSizeBytes  - Input/Output parameter: on input, max size. On output, size of binary loaded.
        InstanceType    - From entry header in BIOS directory table. An entry matching both BiosDirType and
                          InstanceType must be found in the BIOS directory table to load the bin.

    Return value: BL_OK or error code
*/
__svc(SVC_LOAD_FW_IMAGE_BY_INSTANCE) uint32_t
Svc_LoadBinaryByInstance(BIOS_DIRECTORY_ENTRY_TYPE_E    BiosDirType,
                         void                           *pDest,
                         uint32_t                       *pDestSizeBytes,
                         uint32_t                       InstanceType);




/*-----------------------------------------------------------------------------
    Load a binary from the BIOS directory table by its attributes word.
    The binary should be signed unless it is of the excepted types, and can be
    compressed.

    Parameters:
        AttribWord      - is the 32-bit long bit-coded attributes word
        AttribMask      - is the mask with 1s in the places corresponding to the attributes to be searched
        pDest           - Pointer to where the binary should be loaded to.
        pDestSizeBytes  - Input/Output parameter: on input, max size. On output, size of binary loaded.

    Return value: BL_OK or error code
*/
__svc(SVC_LOAD_BINARY_BY_ATTRIB)    uint32_t
Svc_LoadBinaryByAttrib(uint32_t AttribWord,
                       uint32_t AttribMask,
                       void     *pDest,
                       uint32_t *pDestSizeBytes);

/*-----------------------------------------------------------------------------
    Returns Secure RTC value in days

    Parameters:
        pCurrentSRTC 	- pointer to counter value in days

    Return value: BL_OK or error code
*/
__svc(SVC_READ_SECURE_RTC) uint32_t Svc_ReadSecureRTC(uint32_t *pCurrentSRTC);

/*-----------------------------------------------------------------------------
    Add delay in micro seconds

    Parameters:
        delay           - required delay value in microseconds

    Return value: NONE
*/
__svc(SVC_DELAY_IN_MICRO_SECONDS) void Svc_DelayInMicroSeconds( uint32_t delay );

/*-----------------------------------------------------------------------------
    Add new entry with data to MP2 RAM1 - validation of data is performed by PSP 

    Parameters:
        Id          - must be unique and equal or greater than 0x80000000
        pSrcAddr    - address pointer (must be aligned to 32 bytes) to source data location
        DataSize    - size (must be aligned to 32 bytes) of data which need to be saved on MP2 RAM1

    Return value: BL_OK or error code
*/
__svc(SVC_ADD_ENTRY_MP2_RAM1) uint32_t Svc_AddEntryToMp2Ram1( uint32_t Id, void* pSrcAddr, uint32_t DataSize );

/*-----------------------------------------------------------------------------
    Read entry with data from MP2 RAM1 - validation of data is performed by PSP 

    Parameters:
        Id              - should be previously used while saving same data
        pDestAddr       - address pointer (must be aligned to 32 bytes) to destination location
        AvailableSize   - maximum available size (must be aligned to 32 bytes) at destination location 
        RetrievedSize   - size of data retrieved from MP2 RAM1

    Return value: BL_OK or error code
*/
__svc(SVC_READ_ENTRY_MP2_RAM1) uint32_t Svc_ReadEntryFromMp2Ram1( uint32_t Id, void* pDestAddr, uint32_t AvailableSize, uint32_t* RetrievedSize );

// EMB-FP5-PSP-START
//-----------------------------------------------------------------------------
//
// Description      :   Control RPMC usage
//
// Inputs           :   RpmcCtl - 0: disable RPMC usage
//                                1: enable RPMC usage
//
// Return Values    :   BL_OK
//
//-----------------------------------------------------------------------------
__svc(SVC_RPMC_SWITCH) BL_RETCODE Svc_RpmcSwitch(uint32_t RpmcCtl);
// EMB-FP5-PSP-END

#endif /* _BL_SYSCALL_H_ */
