#ifndef _HI_MANAGER_UUID_H_
#define _HI_MANAGER_UUID_H_

#pragma pack (1)
typedef struct {
  UINT32  Segment1;
  UINT16  Segment2;
  UINT16  Segment3;
  UINT16  Segment4;
  UINT8   MAC[6];
} AMT_UUID;
#pragma pack ()

#endif;