//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CpuCache.c
    This file contains code to program the memory cacheability in
    the CPU by programming CPU MTRR registers. 
    No porting is required

    Currently WP attribute is not supported. Not all possible 
    conditions are validated with this code

**/


//----------------------------------------------------------------------------
// Include files
//----------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include "CpuDxe.h"
#include <Library/DebugLib.h>
#include <Include/Base.h>
#include <Library/PcdLib.h>

//----------------------------------------------------------------------------
// Local structure definitions
//----------------------------------------------------------------------------

//This enumeration describes the values for the MTRR cache attribute values:
//UC (Uncacheable) = 0, WC (Write Combine) = 1, WT (Write Thru) = 4,
//WP (Write Protect) = 5, WB (Write Back) = 6.
typedef enum  {
    ATTRIB_UC=0,ATTRIB_WC,ATTRIB_WT=4,ATTRIB_WP,ATTRIB_WB
} CACHE_ATTRIBUTE;


//Fixed MTRRs will be read into an array of FIXED_MTRRS.
typedef struct {
    UINT16  Register;
    UINT64  Mtrr;
    UINT32  Base;
    UINT32  Length;
    BOOLEAN IsChanged;
} FIXED_MTRRS;

// MTRRs will be read in and sorted/combined/overlaps removed into an array
// of MEMORY_MAP.
// The final array will be WbCacheMap. An intermediate of uncached entries
// read in will be in UcCacheMap.
typedef struct {
	UINT64	Base;
	UINT64	End;
} MEMORY_MAP;

// Variable Mtrrs will be initially read into this array.
// At the end, the array will be updated to the Mtrrs to write.
typedef struct {
	UINT64	Base;
	UINT64	End;
	UINT8	Attributes;
	BOOLEAN	Valid;
} VARIABLE_MTRRS;

//----------------------------------------------------------------------------
// Function prototypes
//----------------------------------------------------------------------------
UINT64      GetPowerOfTwo64(IN  UINT64  Input);
BOOLEAN     PreMtrr();
void        PostMtrr(BOOLEAN);

//----------------------------------------------------------------------------
// External variables
//----------------------------------------------------------------------------
extern VOID *MpData;

//----------------------------------------------------------------------------
// Local variables
//----------------------------------------------------------------------------
// These are the Mtrr MSR Addresses.
UINT16 VariableMtrrAddress[] = {
    MTRR_PHYS_BASE_0,
    MTRR_PHYS_BASE_1,
    MTRR_PHYS_BASE_2,
    MTRR_PHYS_BASE_3,
    MTRR_PHYS_BASE_4,
    MTRR_PHYS_BASE_5,
    MTRR_PHYS_BASE_6,
    MTRR_PHYS_BASE_7
};
MTRR_SETTINGS   *gMtrrTable;
MEMORY_MAP  WbCacheMap[50]; // Memory map of wb cacheable regions.
MEMORY_MAP  UcCacheMap[NUM_OF_MTRR + 1];    // Inital memory map of uc cacheable regions from mtrrs.
MEMORY_MAP  MemMapEnd = {0, 0};
BOOLEAN     IsMtrrUpdated;

// This initiates a FIXED_MTRRS array and fill the structure
// with the description of each fixed MTRR register.
FIXED_MTRRS FixedMtrrs[] = {
    {MTRR_FIX_64K_00000, 0, 0, 0x10000, FALSE},
    {MTRR_FIX_16K_80000, 0, 0x80000, 0x04000, FALSE},
    {MTRR_FIX_16K_A0000, 0, 0xA0000, 0x04000, FALSE},
    {MTRR_FIX_4K_C0000, 0, 0xC0000, 0x01000, FALSE},
    {MTRR_FIX_4K_C8000, 0, 0xC8000, 0x01000, FALSE},
    {MTRR_FIX_4K_D0000, 0, 0xD0000, 0x01000, FALSE},
    {MTRR_FIX_4K_D8000, 0, 0xD8000, 0x01000, FALSE},
    {MTRR_FIX_4K_E0000, 0, 0xE0000, 0x01000, FALSE},
    {MTRR_FIX_4K_E8000, 0, 0xE8000, 0x01000, FALSE},
    {MTRR_FIX_4K_F0000, 0, 0xF0000, 0x01000, FALSE},
    {MTRR_FIX_4K_F8000, 0, 0xF8000, 0x01000, FALSE},
    {0, 0, 0x100000, 0, FALSE}  // End of table, This entry is important.
};

// This contains the MTRRs to be read and later written back.
VARIABLE_MTRRS  VariableMTRRs[NUM_OF_MTRR];

//----------------------------------------------------------------------------
// Function definitions
//----------------------------------------------------------------------------

/**
    This routine aligns the offset provided to the lowest power of two. If
    the input is 0xBFF00000 the return value is 0x100000. If the input is
    0xC0000000 then the return value will be 0x40000000.

    @param Base Base offset whose alignment value to be found

    @retval UINT64 Returns the lowest power of two.

**/

UINT64
GetBaseAlignment (
  IN    UINT64  Base
)
{
    UINT64  Length = Base;

    if (Base == 0)
        return 0;
    while (Length - GetPowerOfTwo64 (Base))
    {
        Length -= GetPowerOfTwo64 (Base);
        Base = Length;
    }
    return Length;
}

/**
    This routine returns the max power of two value that satisfies the
    provided length and alignment requirement.

        
    @param BaseAlign Alignment value to be satisfied
    @param Length Amount of data to be cached writeback

         
    @retval UINT64 Returns the size that can fit the above requirement

**/

UINT64
GetAlignedPowerOfTwo64 (
    IN  UINT64      Base,
    IN  UINT64      Length
)
{
    UINT64      BaseAlign;
    UINT64      UnalignedLength;

    BaseAlign = GetBaseAlignment (Base);
    UnalignedLength = GetPowerOfTwo64 (Length);

    if ((UnalignedLength & (BaseAlign -  1)))
    {
        // Alignment satisfied
        return UnalignedLength;
    }

    // Alignment is not satisfied.  
    return GetPowerOfTwo64(BaseAlign);
}

/**
    Check to see if few MTRR can be used by overlapping write-back and
    uncached.

        
    @param Base Base where the range starts (required for alignment)
    @param Length Amount of data to be cached writeback
    @param OverlapCheck If TRUE then performs the overlap check otherwise only
        performs calculation to figure out how many MTRR is
        needed for positive algorithm
    @param Pos If non-null returns the number of MTRR needed for Positive
    @param Sub If non-null returns the number of MTRR needed for subtractive

         
    @retval TRUE if WB/UC combination is the best bet
    @retval FALSE if usage of only WB is an optimized approach

    @note  
  The given size of data can be cached write-back by directly programming
  MTRR in power's of 2 (if it can be represented in power's of 2) or by
  overlapping write-back with uncached MTRR in power's of 2. In certain
  cases, one or the other method utilizes less number of MTRR. This routine
  checks how many MTRR it takes to program in both the mechanism and choose
  the best one.

**/

BOOLEAN 
DoOverlap (
    IN  UINT64      Base,
    IN  UINT64      Length,
	IN	BOOLEAN		OverlapCheck,
	OUT	UINT32		*Pos,
	OUT	UINT32		*Sub
)
{
    UINT32      Positive = 0;
    UINT32      Subtractive = 1;
    UINT64      Len;
    UINT64      ModBase;
    UINT64      AlignedLen;

	if (Pos)
		*Pos = 0;
	if (Sub)
		*Sub = 0;

    Len = Length;

    ModBase = Base;
    do
    {
        AlignedLen = GetAlignedPowerOfTwo64 (ModBase, Len);
        Len -= AlignedLen;
		ModBase += AlignedLen;
        ++Positive;
    } while(Len);

	if (Pos)
		*Pos = Positive;

	if (! OverlapCheck)
		return FALSE;

	Len = GetAlignedPowerOfTwo64(Base, (Shl64(Length, 1)));
	if (Len <= Length)
		return FALSE;		// Not possible
	Len -= Length;

    ModBase = Base + Length;
    do
    {
        AlignedLen = GetAlignedPowerOfTwo64 (ModBase, Len);
        Len -= AlignedLen;
		ModBase += AlignedLen;
        ++Subtractive;
    } while(Len);

	if (Sub)
		*Sub = Subtractive;

    if (Positive <= Subtractive) 
        return FALSE;       // Overlap is not efficient

	return TRUE;            // Overlap is the way to go!
}

/**
    Get Mapping of MTRR of a specific type starting from *index.

        
    @param Attrib Attribute to look for in the list of MTRR
    @param Index Index to start from (modified with new index)
    @param Map Pointer to MEMORY_MAP structure with matched entry

         
    @retval TRUE Matching entry found *Index  updated with the new index
    @retval FALSE No entry with that attribute found

**/

BOOLEAN 
GetNextMtrrType(
    IN      CACHE_ATTRIBUTE     Attrib, 
    IN OUT  UINT8               *Index, 
    OUT     MEMORY_MAP          *Map
)
{
    UINT8 i;

    for (i = *Index; i < NUM_OF_MTRR; ++i)
    {
        if (VariableMTRRs[i].Valid && VariableMTRRs[i].Attributes == Attrib)
        {
            Map->Base = VariableMTRRs[i].Base;
            Map->End = VariableMTRRs[i].End;
            *Index = i;
            return TRUE;
        }
    }
    return FALSE;
}

/**
    This routine adds the specified address range into the existing memory
    map of specified attributes.

        
    @param Index Starting MTRR index to work with
    @param Base Base address of the memory range
    @param End End address of the memory range
    @param Attrib Attribute to be set for the above address range

         
    @retval EFI_SUCCESS return the EFI status

**/

EFI_STATUS 
AddMtrrRange (
    IN OUT  UINT8               *Index, 
    IN      UINT64              Base, 
    IN      UINT64              End, 
    IN      CACHE_ATTRIBUTE     Attrib
)
{
	UINT64  TotalLength = End - Base;

// This routine will be called to add UC (for overlapping condition) and for
// WB caching when more than one MTRR needed. In the UC condition, most
// likely existing MTRR base has to be adjusted based-on end value. For
// example, the original value might be WB:(0-4GB), UC:(3.75-4GB) and the
// newly added UC (.25 at 3.5GB) made it to WB:(0-4GB), UC:(3.50-4GB).
// Whereas in the WB condition, it is more likely that end value in MTRR has
// to be changed.  For example, the original value might be WB:(0-2GB),
// WB:(2GB-3GB) and the newly added entry might change it to WB:(0-2GB),
// WB:(2GB-2.5GB). In the original code (before March 2nd 2007), the second
// condition was not taken care causing problem.  In the new code, we check
// attribute to check what condition we are handling, thus keep the original
// code intact.

	// Split range in to MTRRs.
    while (TotalLength)
    {
        UINT64 Length;
        if (*Index >= NUM_OF_MTRR)
            return EFI_OUT_OF_RESOURCES;    // Check see if out of MTRRs.

        Length = GetAlignedPowerOfTwo64 (Base, TotalLength);

        VariableMTRRs[*Index].Base = Base;
        VariableMTRRs[*Index].End = (Base + Length);
        VariableMTRRs[*Index].Attributes = Attrib;
        VariableMTRRs[*Index].Valid = TRUE;
        IsMtrrUpdated = TRUE;

        ++*Index;
        Base += Length; // Update Base value for next MTRR
                        // Necessary for the second condition (non-UC)
        End -= Length;  // Necessart for the UC condition
        TotalLength -= Length;
    }
    return EFI_SUCCESS;
}

/**
    Check to see if at end of memory map.

        
    @param Map Pointer to the memory map data structure

         
    @retval TRUE If both base and end are 0
    @retval FALSE Otherwise

**/

BOOLEAN 
IsMapEnd (
    IN  MEMORY_MAP      *Map
)
{
	if (Map->Base == 0 && Map->End == 0) 
        return TRUE;
	return FALSE;
}

/**
    Insert an a entry into the middle of the map.

        
    @param Map Pointer to the memory map list into which the new entry will
        be inserted
    @param Index Location (index) in the list to enter the new entry
    @param Base Base address of the address range to be inserted
    @param End End address of the range

         
    @retval VOID

**/

VOID 
InsertAtIndex(
    IN  MEMORY_MAP      *Map, 
    IN  UINT8           Index, 
    IN  UINT64          Base,
    IN  UINT64          End
)
{
	UINT8 i;
	MEMORY_MAP NewEntry;
	NewEntry.Base = Base;
	NewEntry.End = End;

	for(i = Index; !IsMapEnd(&Map[i]); ++i);	//Find end of map.

    // Shift all entries to make room for new entry.
    for(; i > Index; --i)
        Map[i] = Map[i - 1];
    Map[Index] = NewEntry;
}

/**
    Remove an entry from the memory map.

        
    @param Map Pointer to the memory map list from which the entry will be
        removed
    @param Index Location (index) in the list from where the entry will be
        removed

         
    @retval VOID

**/

VOID 
RemoveAtIndex(
    IN  MEMORY_MAP      *Map, 
    IN  UINT8           Index
)
{
    UINT8   i;
    for(i = Index; !IsMapEnd (&Map[i]); ++i)
    {
        Map[i] = Map[i + 1];
    }
}

/**
    Add an entry in the Memory Map and take care of overlaps.

        
    @param Map Pointer to the memory map list into which the new entry will
        be inserted
    @param Entry Memory map to be inserted

         
    @retval VOID

**/

VOID 
AddToMemoryMap(
    IN  MEMORY_MAP      *Map, 
    IN  MEMORY_MAP      Entry
)
{
	UINT8		i;
	UINT64		Base = Entry.Base;
	UINT64		End = Entry.End;

    // Remove all existing entries are a subset of the new entry.
    for (i = 0; !IsMapEnd (&Map[i]); )
    {
        // If existing entry in table overlaps or partially with new entry,
        // extend new entry to contain old, and remove old entry.
        if ((Base >= Map[i].Base && Base <= Map[i].End) ||
         (End >= Map[i].Base && End <= Map[i].End))
        {
            if (Base > Map[i].Base)
                Base = Map[i].Base;

			if (End < Map[i].End) 
				End   = Map[i].End;

            RemoveAtIndex (Map, i);
            // If the existing entry is a subset of the new entry, remove existing entry.
        }
        else
            if (Base < Map[i].Base && End > Map[i].End)
                RemoveAtIndex (Map, i);
            else 
                ++i;    // Doesn't over lap with current entry, check next entry.
    }

    // Check if no entries.
    if (IsMapEnd (&Map[0]))
    {
        InsertAtIndex (Map, 0, Base, End);
        return; // Next MTRR.
    }

    // Check if new entry should be first.
    if (End < Map[0].Base)
    {
        InsertAtIndex (Map, 0, Base, End);
        return; // Next MTRR.
	}

    for (i = 0; !IsMapEnd(&Map[i]); ++i)
    {
        // Check if new entry should be last or in the middle.
        if (Base > Map[i].End && (IsMapEnd (&Map[i + 1]) || End < Map[i+1].Base))
        {
            InsertAtIndex (Map, i + 1, Base, End);
            return; // Next MTRR
        }
    }
}

/**
    Remove an entry in the Memory Map and take care of overlaps.

        
    @param Map Pointer to the memory map list from which the entry will be
        removed
    @param Entry Memory map to be removed

         
    @retval VOID

**/

VOID 
RemoveFromMemoryMap(
    IN  MEMORY_MAP  *Map, 
    IN  MEMORY_MAP  Entry
)
{
	UINT8 i;
	UINT64 Base = Entry.Base;
	UINT64 End = Entry.End;

    for (i = 0; !IsMapEnd (&Map[i]); )
    {
        // If complete overlap remove entire entry.
        if ((Base <= Map[i].Base && End >= Map[i].End))
            RemoveAtIndex (Map, i);
        // Check if new entry is inside.
        else if (Base > Map[i].Base && End < Map[i].End)
        {
            // Create 2 entries from single entry to remove the overlapping new entry.
            InsertAtIndex (Map, i + 1, End, Map[i].End);    
            Map[i].End = End;
            i += 2; // Skip new entry.
            // Check for end overlap.
        }
        else if (End >= Map[i].Base && End <= Map[i].End)
        {
            Map[i++].Base = End;    // Reduce size by inside overlap.
        // Check for beginning overlap.
        }
        else if (Base >= Map[i].Base && Base <= Map[i].End)
            Map[i++].End = Base;
    } 
}

/**
    Adjust a WB map entry for UC regions by either reducing the new WB entry
    or split it into multiple regions.
    If TRUE returned, the it must be called again to get the next region.

        
    @param Entry Will be updated to 0, 0 if overlaps completely

         
    @retval TRUE call again for next entry

**/

BOOLEAN 
AdjustUcOverlap (
    IN  MEMORY_MAP      *Entry
)
{
	static UINT8 i;							//Position for second call.
	static MEMORY_MAP SavedEntry = {0,0};	//SaveEntry for second call.

    // Check if second or more call.
    if (!IsMapEnd (&SavedEntry))
    {
        *Entry = SavedEntry;
        SavedEntry = MemMapEnd;
    }
    else
        i = 0;

    if (Entry->End <= UcCacheMap[0].Base)
        return FALSE;   // No overlaps.

    for (; !IsMapEnd (&UcCacheMap[i]); ++i)
    {
        if (Entry->Base >= UcCacheMap[i].End)
            continue;   // No overlaps here.

        // Check if complete overlap.
        if (Entry->Base >= UcCacheMap[i].Base && Entry->End <= UcCacheMap[i].End)
        {
            Entry->Base = 0;
            Entry->End = 0;
            return FALSE;
        }

        // Check if end overlaps UC region
        if (Entry->Base < UcCacheMap[i].Base)
        {
            // If true, base doesn't overlap here.
            if (Entry->End <= UcCacheMap[i].Base)
                return FALSE;   // End doesn't overlap, so no overlap.

            // End overlaps.
            if (Entry->End <= UcCacheMap[i].End)
            {
                // Check if only over one region and not beyond.
                Entry->End = UcCacheMap[i].Base;
                return FALSE;
            }
            SavedEntry.Base = UcCacheMap[i].End;    // Overlaps beyond or muliple regions.
            SavedEntry.End = Entry->End;
            Entry->End = UcCacheMap[i].Base;
            return TRUE;
		}

        // For the following conditions the base overlaps a UC region.
        Entry->Base = UcCacheMap[i].End;
        // Check if next region exists.
        if (IsMapEnd (&UcCacheMap[i + 1]))
            return FALSE;

        // Check if overlaps any of next region
        if(Entry->End <= UcCacheMap[i + 1].End)
        {
            // Check if end doesn't extend past next region
            if(Entry->End > UcCacheMap[i + 1].Base)
                Entry->End = UcCacheMap[i + 1].Base;
            return  FALSE;
        }

		//Region extends past next region
		SavedEntry.Base = UcCacheMap[i+1].End;
		SavedEntry.End = Entry->End;
		Entry->End = UcCacheMap[i+1].Base;
		return TRUE;
	}
	//Region not in overlap UC.
	return FALSE;
}

/**
    Create the UcCacheMap and WbCacheMap maps and take care of overlaps.

        
    @param Base Base address of the new memory map
    @param End End address of themap
    @param Attribute Cache attribute to be set for the new memory map

         
    @retval VOID

**/

VOID 
CreateMemoryMapWithNewEntry(
    IN  UINT64              Base, 
    IN  UINT64              End, 
    IN  CACHE_ATTRIBUTE     Attribute
)
{
	UINT8 i;
	MEMORY_MAP Entry;
	BOOLEAN MultipleEntries;

	MemSet(WbCacheMap, sizeof(WbCacheMap), 0);
	MemSet(UcCacheMap, sizeof(UcCacheMap), 0);

    // Add all uncacheable entries in MTRRs into UC Memory map.
    for (i = 0; GetNextMtrrType (ATTRIB_UC, &i, &Entry); ++i)
    {
        //i maybe updated if function returns TRUE.
        AddToMemoryMap (UcCacheMap, Entry);
    }

	Entry.Base = Base;
	Entry.End = End;

    // Add new entry into proper memory map.
    if (Attribute == ATTRIB_UC)
        AddToMemoryMap (UcCacheMap, Entry);
    else
    {
        do
        {
            // Must take care of overlaps if WB before adding.
            MultipleEntries = AdjustUcOverlap (&Entry);
            if (!IsMapEnd (&Entry))
                AddToMemoryMap(WbCacheMap, Entry);
        } while (MultipleEntries);
    }

    // Add all WB memory regions in MTRRs and adjust for UC overlaps.
    for (i = 0; GetNextMtrrType (ATTRIB_WB, &i, &Entry); ++i)
    {
        // AdjustUcOverlap may create multiple entries for Entry from GetNextMtrrType.
        do
        {
            MultipleEntries = AdjustUcOverlap(&Entry);
            if (!IsMapEnd (&Entry))
                AddToMemoryMap (WbCacheMap, Entry);
        } while (MultipleEntries);
    }
}

/**
    This routine creates optimized MTRR entries with WB cachebility for the
    memory range specified.  It chooses either overlapping area or direct
    MTRR allocation.

        
    @param Base Base offset of the memory range
    @param Length Length of the memory range
    @param MtrrIndex Start from the specified MTRR index. Updates it if one or
        more entry is used

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
CreateMTRREntries (
    IN      UINT64      Base,
    IN      UINT64      Length,
    IN  OUT UINT8       *MtrrIndex
)
{
    UINT64      End = Base + Length;
    EFI_STATUS  Status;

    // Check if only 1 mtrr needed.
    if (GetAlignedPowerOfTwo64 (Base, Length) == Length)
    {
        if (*MtrrIndex >= NUM_OF_MTRR) 
            return EFI_OUT_OF_RESOURCES;

        VariableMTRRs[*MtrrIndex].Base = Base;
        VariableMTRRs[*MtrrIndex].End = End;
        VariableMTRRs[*MtrrIndex].Attributes = ATTRIB_WB;
        VariableMTRRs[*MtrrIndex].Valid = TRUE;
        IsMtrrUpdated = TRUE;
        ++(*MtrrIndex);
    }
    else
    {
        if (DoOverlap (Base, Length, TRUE, NULL, NULL))
        {
            // Check if overlapping UC & WB, use fewer mtrrs.
            UINT64  OverlapLength = GetPowerOfTwo64 ((Shl64 (Length, 1)));

            if (*MtrrIndex >= NUM_OF_MTRR) 
                return EFI_OUT_OF_RESOURCES;

            if ((OverlapLength == 0x100000000) && (Base == 0))
            {
                End = 0x80000000;

                VariableMTRRs[*MtrrIndex].Base = Base;
                VariableMTRRs[*MtrrIndex].End = End;
                VariableMTRRs[*MtrrIndex].Attributes = ATTRIB_WB;
                VariableMTRRs[*MtrrIndex].Valid = TRUE;
                ++(*MtrrIndex);
                Base = End;                
                if ((Length - Base) > 0x40000000)
                {
                    End = Base + 0x40000000;
                    VariableMTRRs[*MtrrIndex].Base = Base;
                    VariableMTRRs[*MtrrIndex].End = End;
                    VariableMTRRs[*MtrrIndex].Attributes = ATTRIB_WB;
                    VariableMTRRs[*MtrrIndex].Valid = TRUE;
                    ++(*MtrrIndex);
                    Base = End;
                }
                OverlapLength = GetPowerOfTwo64((Shl64((Length - Base), 1)));
            }

            End = Base + OverlapLength;
            VariableMTRRs[*MtrrIndex].Base = Base;
            VariableMTRRs[*MtrrIndex].End = End;
            VariableMTRRs[*MtrrIndex].Attributes = ATTRIB_WB;
            VariableMTRRs[*MtrrIndex].Valid = TRUE;
            ++(*MtrrIndex);
            IsMtrrUpdated = TRUE;

            if (Base == 0)
                Base += Length;
            else
                Base = Length;

            // At End of WB, program UC.
            Status = AddMtrrRange(MtrrIndex, Base, End, ATTRIB_UC);	//Set UC overlap.
            if (EFI_ERROR(Status)) 
                return Status;
        }
        else
        {
            // Get Mtrrs No overlap.
            Status = AddMtrrRange(MtrrIndex, Base, End, ATTRIB_WB);
            if (EFI_ERROR(Status)) 
				return Status;
		}
	}
	return EFI_SUCCESS;
}

/**
    From the WbCacheMap, get the new MTRR values.

        
    @param VOID

         
    @retval EFI_STATUS EFI_OUT_OF_RESOURCES    If not enough MTRR to program the
        required attribute
        -   EFI_SUCCESS             On successful completion of MTRR
        value adjustments

**/

EFI_STATUS 
GetNewMtrrs(
    VOID
)
{
	UINT8			i, MtrrIndex = 0;
	EFI_STATUS		Status;

    // For each Map entry, create 1 or more Mtrr.
    for (i = 0; !IsMapEnd (&WbCacheMap[i]); ++i)
    {
        UINT64  Length = WbCacheMap[i].End - WbCacheMap[i].Base;
        UINT64  Base = WbCacheMap[i].Base;

        // Check if we can merge two WB area together with an overlapping UC area
        if (!IsMapEnd (&WbCacheMap[i + 1]))
        {
            // Only valid if we do have one more entry
            UINT32      Pos, Sub, TotMtrr1, TotMtrr2;
            UINT64      sBase = WbCacheMap[i + 1].Base;
            UINT64      sLength = WbCacheMap[i + 1].End - WbCacheMap[i + 1].Base;
            MEMORY_MAP  MergeEntry, UcEntry;

			// First let us see how many MTRR needed for the two WB memory ranges
			// when specified separately
			if (DoOverlap(Base, Length, TRUE, &Pos, &Sub))
				TotMtrr1 = Sub;		// Overlapping is best solution
			else
				TotMtrr1 = Pos;		// Overlapping is not the best solution

			if (DoOverlap(sBase, sLength, TRUE, &Pos, &Sub))
				TotMtrr1 += Sub;		// Overlapping is best solution
			else
				TotMtrr1 += Pos;		// Overlapping is not the best solution

			// TotMtrr1 have the total amount of MTRR needed if two WB areas are represented 
			// separately

			// Now, let us consolidate the two WB areas
			MergeEntry.Base = sBase = WbCacheMap[i].Base;
			MergeEntry.End  = WbCacheMap[i+1].End;
			sLength			= MergeEntry.End - sBase;
			UcEntry.Base	= WbCacheMap[i].End;
			UcEntry.End		= WbCacheMap[i+1].Base;
			// Calculate number of MTRR needed for Merged WB
			if (DoOverlap(sBase, sLength, TRUE, &Pos, &Sub))
				TotMtrr2 = Sub;
			else
				TotMtrr2 = Pos;

			// Calculate the number of MTRR needed for UC area
			DoOverlap(UcEntry.Base, (UcEntry.End - UcEntry.Base), FALSE, &Pos, NULL);
			TotMtrr2 += Pos;

            if (TotMtrr1 >= TotMtrr2)
            {
                Status = CreateMTRREntries (sBase, sLength, &MtrrIndex);
                if (Status != EFI_SUCCESS)
                    return Status;

                Status = AddMtrrRange (&MtrrIndex, UcEntry.Base, UcEntry.End, ATTRIB_UC);   // Set UC overlap.
                if (EFI_ERROR (Status))
                    return Status;

                // Increment index (Skipping next entry too)
                ++i;
                continue;
            }
        }

        Status = CreateMTRREntries (Base, Length, &MtrrIndex);
        if (Status != EFI_SUCCESS)
            return Status;
    }

    // Invalidate unused MTRRs.
    for (i = MtrrIndex; i < NUM_OF_MTRR; ++i)
    {
        if (VariableMTRRs[i].Valid != FALSE)
        {
            VariableMTRRs[i].Valid = FALSE;
            IsMtrrUpdated = TRUE;
        }
    }

	return EFI_SUCCESS;
}

/**
    This function reads the fixed and variable MTRR for the boot processor
    and stores it in local data structure for processing.

        
    @param VOID

         
    @retval VOID

**/

VOID
ReadMtrrs()
{
    UINT8   i;
    UINT64  MsrSysCfg64;

    for (i = 0; i < 11; ++i)
    {
        // We have to enable the MTRR Fix DRAM Modfication enable bit.
        MsrSysCfg64 = ReadMsr (MSR_SYS_CFG);
  	    WriteMsr (MSR_SYS_CFG, MsrSysCfg64 | (3 << MtrrFixDramEnBit));
        FixedMtrrs[i].Mtrr = ReadMsr (FixedMtrrs[i].Register);
        WriteMsr (MSR_SYS_CFG, MsrSysCfg64);
    }
    for (i = 0; i < NUM_OF_MTRR; ++i)
    {
        UINT64  MtrrBase = ReadMsr (VariableMtrrAddress[i]);
        UINT64  MtrrMask = ReadMsr (VariableMtrrAddress[i] + 1);

        if (!(MtrrMask & 1 << 11))
            VariableMTRRs[i].Valid = FALSE;
        else
        {
            UINT64  Length;

            VariableMTRRs[i].Valid = TRUE;
            VariableMTRRs[i].Attributes = (UINT8)MtrrBase;  // Last 8 bits.

            //
            // Treat all attributes other than WB as WC.
            //
            if (VariableMTRRs[i].Attributes != ATTRIB_WB)
                VariableMTRRs[i].Attributes = ATTRIB_UC;

            MtrrBase &= 0xFFFFFFF000;   // Mask off RV and type.
            MtrrMask &= 0xFFFFFFF000;   // Mask off RV and valid bit.
            Length = ((~MtrrMask) & 0xFFFFFFFFFF) + 1;

            VariableMTRRs[i].Base = MtrrBase;
            VariableMTRRs[i].End = MtrrBase + Length;
            // Note: End is top address + 1.
        }
    }
}

/**
    This routine programs the fixed and variable MTRR if they are different.

        
    @param VOID

         
    @retval VOID

**/

VOID 
WriteMtrrs()
{
    UINT8   i;
    BOOLEAN InterruptState;
    UINT64  MsrSysCfg64, Temp64;
    UINT64  MtrrBaseValue;
    UINT64  MtrrMaskValue;
    UINT32  VarMtrrMsr = 0;
    UINT64  SmmAddr = 0;

    InterruptState = PreMtrr();

    // Write Fixed MTRRS
    for (i = 0; i < 11; ++i)
    {
        // We have to enable the MTRR Fix DRAM Modfication enable bit.
        MsrSysCfg64 = ReadMsr (MSR_SYS_CFG);
        WriteMsr (MSR_SYS_CFG, MsrSysCfg64 | (3 << MtrrFixDramEnBit));

        if (FixedMtrrs[i].IsChanged)
        {
            // We have to preserve the DRAM R/W 
            Temp64 = ReadMsr (FixedMtrrs[i].Register);
            Temp64 &= (UINT64)0x1818181818181818;   // Preserve the lock/unlock status
            Temp64 |= FixedMtrrs[i].Mtrr;
            WriteMsr (FixedMtrrs[i].Register, Temp64);
        }
        WriteMsr (MSR_SYS_CFG, MsrSysCfg64);
    }

    if (PcdGetBool(PcdSmmTsegWbSupport) == FALSE)
    {
        SmmAddr = ReadMsr (AMD_MSR_SMM_ADDR_HL);
        for (VarMtrrMsr = MTRR_PHYS_BASE_0; VarMtrrMsr < MTRR_PHYS_BASE_6; VarMtrrMsr += 2)
        {
            MtrrBaseValue = ReadMsr (VarMtrrMsr);
            MtrrMaskValue = ReadMsr (VarMtrrMsr + 1);

            if (MtrrBaseValue == SmmAddr)
                break;

            if ((MtrrBaseValue == 0) && (VarMtrrMsr < MTRR_PHYS_BASE_6))
            {
                WriteMsr (VarMtrrMsr, SmmAddr);
                Temp64 = ((~(TSEG_SIZE - 1) & 0x0FFFFFFFFFFFF) | (1 << 11));
                WriteMsr (VarMtrrMsr + 1, Temp64);
                break;
            }
        }   // for (VarMtrrMsr
    }

    PostMtrr (InterruptState);
    return;
}

/**
    This routine programs the fixed MTRR based on the address range provided.

        
    @param BaseAddress Start address of the address range
    @param EndAddress End address of the range
    @param Attribute Cache attribute to be set for the range

         
    @retval EFI_STATUS EFI_ACCESS_DENIED   If fixed MTRR is not starting or ending
        in required aligned boundary
        -  EFI_SUCCESS         On successful completion of caching

**/

EFI_STATUS 
ProgramFixedMtrrs(
    IN  UINT64              BaseAddress, 
    IN  UINT64              EndAddress, 
    IN  CACHE_ATTRIBUTE     Attribute
)
{
    UINT8       i, j, k, l;
    UINT8       MtrrByteGroupStart;
    UINT8       MtrrByteGroupEnd;
    UINT64      MtrrValue;

    if (EndAddress > 0x100000) 
        EndAddress = 0x100000;

    // Find entry (or MTRR register) in Fixed MTRR table for Base address.
    for (i = 1; i < sizeof (FixedMtrrs) / sizeof (FIXED_MTRRS); ++i)
    {
        // Start at second entry.
        if (BaseAddress < FixedMtrrs[i].Base)
        {
            // If true, entry+1 found in Fixed MTRR table.
            if ((BaseAddress & (FixedMtrrs[i - 1].Length - 1)) != 0) 
                return EFI_ACCESS_DENIED;   // Must start at aligned boundary.

            // Find entry (or MTRR register) in Fixed MTRR table End address.
            for (j = i; j < sizeof (FixedMtrrs) / sizeof (FIXED_MTRRS); ++j)
            {
                // Find entry+1 in Fixed MTRR table.
                if (EndAddress <= FixedMtrrs[j].Base)
                {
                    // Compare End address with End of Address for table entry.
                    // Now check end address for alignment. Note: end address (actually last cacheable address + 1) alignment
                    // will be the same as the alignment for the Fixed MTRR the end block is in.
                    if ((EndAddress & (FixedMtrrs[j - 1].Length - 1)) != 0) 
                        return EFI_ACCESS_DENIED;   // Must end at aligned boundary.
                    break;  // Break out of for loop.
                }
            }

            // End address found in table is guaranteed because EndAddress is less than 1MB.
            --i;
            --j;    // Set to table entry. It was entry+1.
            for (k = i; k <= j; ++k)
            {
                // Program MTRRs. Each loop is for a different register.
                MtrrByteGroupStart = 0;
                MtrrByteGroupEnd = 64;
                if (k == i) // k can be k=i=j
                    MtrrByteGroupStart = (UINT8) Div64 (BaseAddress - FixedMtrrs[i].Base,
                                                  FixedMtrrs[i].Length, NULL) * 8;
                if (k == j)
                    MtrrByteGroupEnd = (UINT8)Div64 (EndAddress - FixedMtrrs[j].Base,
                                               FixedMtrrs[j].Length, NULL) * 8;

                // Read MTRRs
                MtrrValue = FixedMtrrs[k].Mtrr;
                for (l = MtrrByteGroupStart; l < MtrrByteGroupEnd; l += 8)
                {
                    // This loop fills in a register.
                    if (l <= 24)
                    {
                        *(UINT32*)&MtrrValue &= ~(UINT32)(0xFF << l);   // 0;// ~Shl (0xFF, l);   // Mask
                        *(UINT32*)&MtrrValue |= (Attribute << l);
                    }
                    else
                    {
                        *((UINT32*)&MtrrValue + 1) &= ~(0xFF << (l - 32));  // Mask
                        *((UINT32*)&MtrrValue + 1) |= (Attribute << (l - 32));
                    }
                }

                // Set MTRRs
                if (FixedMtrrs[k].Mtrr != MtrrValue)
                {
                    FixedMtrrs[k].Mtrr = MtrrValue;
                    FixedMtrrs[k].IsChanged = TRUE;
                    IsMtrrUpdated = TRUE;
                }
            }
            return EFI_SUCCESS;
        }
    }
    return EFI_ACCESS_DENIED;
}

/**
    This routine prepares the system before MTRR programming. This routine
    disable Interrupts, disable cache, flush cache, disable MTRRs, and return
    original interrupts.

        
    @param VOID

         
    @retval BOOLEAN Returns current CPU interrupt state

**/

BOOLEAN 
PreMtrr() 
{
	BOOLEAN InterruptState = CPULib_GetInterruptState();

    CPULib_DisableInterrupt();
    DisableCacheInCR0();
    WriteMsr (MTRR_DEF_TYPE, 0);    // Disable mtrrs
    return InterruptState;
}

/**
    This routine prepares the system after MTRR programming. This routine
    enables Fixed and Variable MTRRs, enable cache, and set the flags to
    enable interrupts.

        
    @param InterruptState Boolean flag indicating whether to enable Interrupt or not

         
    @retval VOID

**/

VOID
PostMtrr (
  IN    BOOLEAN InterruptState
)
{
    WriteMsr (MTRR_DEF_TYPE, 3 << 10);  // Enable Fixed and Variable MTRRs, default UC
    EnableCacheInCR0();
    if (InterruptState) 
        CPULib_EnableInterrupt();
}


/**
    This routine is used to program MTRR for APs.

        
    @param Cpu CPU number
    @param Context Context of the call back

         
    @retval VOID

**/

VOID
WriteMttrsCpu (
    IN  UINT8       Cpu, 
    IN  VOID        *Context
)
{
    WriteMtrrs();			//Write MTRRs.
}

/**
  Synchronzies up the MTRR values with BSP for calling processor.

  This function synchronzies up the MTRR values with BSP for calling processor.

  @param  Buffer         Mtrr table address.

**/
VOID
LoadMtrrData (
    IN  UINT8       Cpu, 
    IN  VOID        *Context
)
{
  MtrrSetAllMtrrs (gMtrrTable);
}

/**
    This routine is used to set the cache attributes for the given memory
    range. This routine is part of the EFI_CPU_ARCH_PROTOCOL.

        
    @param This Pointer to the CPU architecture protocol
    @param BaseAddress Base address of the memory area
    @param Length Length of memory area
    @param Attributes Memory attributes to be set (Bit pattern)

         
    @retval EFI_STATUS EFI_UNSUPPORTED     Length is 0 or not 4K aligned (or)
        BaseAddress is not 4K aligned (or)
        EndAddress is greater than max address
        supported by the architecture (or)
        EndAddress is less than BaseAddress (or)
        Attribute is not one of EFI_MEMORY_UC,
        EFI_MEMORY_WC, EFI_MEMORY_WT,
        EFI_MEMORY_WB or EFI_MEMORY_WP (or)
        BaseAddress is greater than 1MB and
        attribute is not uncached or writeback
        -  EFI_OUT_OF_RESOURCES    If not enough MTRR to program the
        required attribute
        -  EFI_ACCESS_DENIED   If fixed MTRR setting is not aligned to
        required alignment boundary
        -  EFI_SUCCESS         On successful completion of caching

    @note  
  Currently write-protect is not supported for memory ranges above 1MB.

**/
#if defined (CPU_SET_MEMORY_ATTRIBUTES_SWITCH_BACK) && (CPU_SET_MEMORY_ATTRIBUTES_SWITCH_BACK == 1) // TODO: Remove this in latest project 
EFI_STATUS 
EFIAPI
EfiCpuSetMemoryAttributes (
  IN    EFI_CPU_ARCH_PROTOCOL   *This,
  IN    EFI_PHYSICAL_ADDRESS    BaseAddress,
  IN    UINT64                  Length,
  IN    UINT64                  Attributes
)
{
    UINT64              EndAddress = BaseAddress + Length;
    UINT64		SysCfgValue;
    EFI_STATUS          Status;
    CACHE_ATTRIBUTE     Attribute;

    if (!Length || Length & 0xFFF)
        return EFI_UNSUPPORTED; // Must be at least a multiple of 4k
    if (BaseAddress & 0xFFF)
        return EFI_UNSUPPORTED; // Must be 0 or a multiple of 4k

    if (EndAddress > ((UINT64) 1 << 40))
        return EFI_UNSUPPORTED; // Max memory address
    if (EndAddress <= BaseAddress)
        return EFI_UNSUPPORTED; // Check for overflow

	SysCfgValue = ReadMsr(MSR_SYS_CFG);
	if(SysCfgValue & FORCE_TOM2_WB_BIT)
	{
        if ((BaseAddress > ((UINT64) 1 << 32)) && (Attributes & EFI_MEMORY_WB))
            return EFI_SUCCESS;
        if ((EndAddress > ((UINT64) 1 << 32)) && (Attributes & EFI_MEMORY_WB)) //Rare Scenario BaseAddress < 4GB and EndAdress > 4GB
            EndAddress = (0x100000000);
    }
    if (Attributes & EFI_MEMORY_UC)
        Attribute = ATTRIB_UC;
    else if (Attributes & EFI_MEMORY_WC)
        Attribute = ATTRIB_WC;
    else if (Attributes & EFI_MEMORY_WT)
        Attribute = ATTRIB_WT;
    else if (Attributes & EFI_MEMORY_WB)
        Attribute = ATTRIB_WB;
    else if (Attributes & EFI_MEMORY_WP)
        Attribute = ATTRIB_WP;
    else return
        EFI_UNSUPPORTED;

    if (EndAddress > 0x100000 && !(Attribute == ATTRIB_UC || Attribute == ATTRIB_WB))
        return EFI_UNSUPPORTED;

    IsMtrrUpdated = FALSE;
    ReadMtrrs();    // Existing cache types other than UC and WB are changed to UC. They are unsupported.

    if (BaseAddress < 0x100000)
    {
        if ((Status = ProgramFixedMtrrs (BaseAddress, EndAddress, Attribute)) != EFI_SUCCESS)
            return Status;
        if (EndAddress <= 0x100000)
            goto WRITE_MTRRS;
    }

    if (BaseAddress <= 0x100000)
    {
        BaseAddress = 0;    // Since Fixed takes precendence, base can be set to 0 for variable.
//        Length = EndAddress - BaseAddress;    // Recalculate length (NOT USED)
    }

    //Create a memory map of memory regions of WB that are not overlapping.
	CreateMemoryMapWithNewEntry(BaseAddress, EndAddress, Attribute);

    // Get a structure of new MTRRs with overlapping MTRRs if needed.
    Status = GetNewMtrrs();
    if (EFI_ERROR (Status))
        return Status;

WRITE_MTRRS:
    if (IsMtrrUpdated)
    {
        // Write the MTRRs on all CPUs.
        ExecuteFunctionOnRunningCpus (MpData, TRUE, TRUE, WriteMttrsCpu, NULL);
        //WriteMtrrs();
	}
	return EFI_SUCCESS;
}
#endif

#if defined (CPU_SET_MEMORY_ATTRIBUTES_SWITCH_BACK) && (CPU_SET_MEMORY_ATTRIBUTES_SWITCH_BACK == 0) // TODO: Set this to default in latest project 
EFI_STATUS 
EfiCpuSetMemoryAttributes (
    IN    EFI_CPU_ARCH_PROTOCOL   *This,
    IN    EFI_PHYSICAL_ADDRESS    BaseAddress,
    IN    UINT64                  Length,
    IN    UINT64                  Attributes
)
{
    UINT64		                 SysCfgValue;
    UINT64                       TsegValue, TsegBase;
    EFI_STATUS                   Status;
    MTRR_MEMORY_CACHE_TYPE       CacheType;
    UINT64                       EndAddress = BaseAddress + Length;
    

    //
    // If this function is called because GCD SetMemorySpaceAttributes () is called
    // by RefreshGcdMemoryAttributes (), then we are just synchronzing GCD memory 
    // map with MTRR values. So there is no need to modify MTRRs, just return immediately
    // to avoid unnecessary computing.
    //
    //  if (mIsFlushingGCD) {
    //   return EFI_SUCCESS;
    //}
    
    DEBUG((DEBUG_VERBOSE, "EfiCpuSetMemoryAttributes\n"));
    DEBUG((DEBUG_VERBOSE, "BaseAddress = %X\n", BaseAddress));
    DEBUG((DEBUG_VERBOSE, "Length      = %X\n", Length));
    DEBUG((DEBUG_VERBOSE, "Attributes  = %X\n", Attributes));
    
    switch (Attributes) {
        case EFI_MEMORY_UC:
            CacheType = CacheUncacheable;
        break;
        
        case EFI_MEMORY_WC:
            CacheType = CacheWriteCombining;
        break;
        
        case EFI_MEMORY_WT:
            CacheType = CacheWriteThrough;
        break;
        
        case EFI_MEMORY_WP:
            CacheType = CacheWriteProtected;
        break;
        
        case EFI_MEMORY_WB:
            CacheType = CacheWriteBack;
        break;
        
        case EFI_MEMORY_UCE:
        case EFI_MEMORY_RP:
        case EFI_MEMORY_XP:
        case EFI_MEMORY_RUNTIME:
            DEBUG((DEBUG_VERBOSE, "Status = %r\n", EFI_UNSUPPORTED));
            return EFI_UNSUPPORTED;
        default:
            DEBUG((DEBUG_VERBOSE, "Status = %r\n", EFI_INVALID_PARAMETER));
            return EFI_INVALID_PARAMETER;
    }

    if(!PcdGetBool(AmiPcdMtrrNonUcWbEnabled))
    {
        // Block non UC/WB. The MTRR may not enough to descirbe all memory range.
        if((EndAddress > 0x100000) && !((CacheType == CacheUncacheable) || (CacheType == CacheWriteBack)))
        {
            DEBUG((DEBUG_INFO, "Force to block non WB/UC which above 1MB\n"));
            DEBUG((DEBUG_VERBOSE, "Status = %r\n", EFI_UNSUPPORTED));
            return EFI_UNSUPPORTED;
        }
    }
    
    //
    // AMD have a special MSR to set memory attribute between 4G to TOM2.
    //
    SysCfgValue = ReadMsr(MSR_SYS_CFG);
    if(SysCfgValue & FORCE_TOM2_WB_BIT)
    {
        if ((BaseAddress > ((UINT64) 1 << 32)) && (Attributes & EFI_MEMORY_WB))
        {
            DEBUG((DEBUG_VERBOSE, "Status = %r\n", EFI_SUCCESS));
            return EFI_SUCCESS;
        }
        if ((EndAddress > ((UINT64) 1 << 32)) && (Attributes & EFI_MEMORY_WB)) //Rare Scenario BaseAddress < 4GB and EndAdress > 4GB
            EndAddress = (0x100000000);
    }
    
    //
    // AMD have a special MSR for TSEG, check if first when set TSEG range.
    //
    TsegValue = ReadMsr(AMD_MSR_SMM_MASK_HL);
    TsegBase  = ReadMsr(AMD_MSR_SMM_ADDR_HL) & ((UINT64)(BIT48 - BIT17)); // BIT 47 ~ BIT 17
    
    if((BaseAddress == TsegBase) && (Length == TSEG_SIZE) && (TsegBase != 0))
    {
        // SMM TSeg Mask[TValid], Force TSEG memory type range to WB to reduce number of MTRR used.
        if(TsegValue & BIT1)
        {
            DEBUG((DEBUG_INFO, "Force TSEG memory attribute to AmiPcdTsegMtrrAttribute\n"));
            CacheType = (MTRR_MEMORY_CACHE_TYPE)PcdGet8(AmiPcdTsegMtrrAttribute);
        }
    }
    
    
    //
    // call MTRR libary function
    //
    Status = MtrrSetMemoryAttribute(
        BaseAddress,
        Length,
        CacheType
    );
    
    if (!RETURN_ERROR (Status)) 
    {
        //
        // Sync saved MTRR settings
        //
        MtrrGetAllMtrrs (gMtrrTable);
        //Write the MTRRs on all CPUs.
        ExecuteFunctionOnRunningCpus(MpData, TRUE, TRUE, LoadMtrrData, NULL);
    }
    
    DEBUG((DEBUG_VERBOSE, "Status = %r\n", Status));
    return  Status;
}
#endif

/**
    Flushes Data cache for IO DMA Operations. IO DMA operations are fully
    coherent, so EFI_SUCCESS returned. This routine is part of the
    EFI_CPU_ARCH_PROTOCOL.

        
    @param This Pointer to the CPU architecture protocol
    @param Start Start address of cache flush area
    @param Length Length of data to be flushed
    @param FlushType Flush type (writeback invalidate, writeback and invalidate)

         
    @retval EFI_SUCCESS always success

**/

EFI_STATUS
EFIAPI
EfiCpuFlushDataCache (
  IN    EFI_CPU_ARCH_PROTOCOL   *This,
  IN    EFI_PHYSICAL_ADDRESS    Start,
  IN    UINT64                  Length,
  IN    EFI_CPU_FLUSH_TYPE      FlushType
)
{
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

