
#include <AaeonBiosRobotCommonLib.h>
#include "Token.h"
#include <Library/IoLib.h>

#ifdef PEI_BUILD
#include <Ppi/Stall.h>
EFI_PEI_STALL_PPI    		*gStallPpi = NULL;
EFI_PEI_SERVICES     		**gPeiServices = NULL;
#endif
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

