#ifndef _SioLdnDefaultDisable_H_
#define _SioLdnDefaultDisable_H_


typedef struct {
	CHAR16*      LdnName;  //LdnName refert to build/GSIOSETUPVAR.H
	BOOLEAN	     Enable;  //True-->Default Enable
	                      //FALSE-->Default Disable.
} AAEON_LDN_Default;

typedef struct {
	UINT8   PatchFlag;
} AAEON_SIOD4PATCH_DATA;

#endif