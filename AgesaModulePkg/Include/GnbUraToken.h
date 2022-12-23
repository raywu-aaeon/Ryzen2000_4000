/* $NoKeywords:$ */
/**
 * @file
 *
 * AGESA gnb file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */
#ifndef _GNBURATOKEN_H_
#define _GNBURATOKEN_H_

/// Template structure for register/field table
typedef struct {
  URA_REGISTER_64B_ENTRY                                        RxSmuIntReq;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuIntToggle;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuServiceIndex;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuIntSts;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuIntAck;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuIntDone;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuAuthSts;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuAuthDone;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuAuthPass;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuFwAuth;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuProtectedMode;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuRcuUcEvents;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuBootSeqDone;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuFwFlags;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuInterruptsEnabled;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuResetCntl;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuRstReg;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuClkCntl;///<
  URA_FIELD_16B_ENTRY                                           BfxSmuCkDisable;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuAuthVector;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuRamStartAddr;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuRomStartAddr;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuIntArgument;///<

} REG_FIELD_TABLE_STRUCT;

#define  IDX_CALC(VarName) (offsetof (REG_FIELD_TABLE_STRUCT, VarName) / 2)
#define  SEL_CALC(VarName) VarName
#define  FIELD_OFFSET(RegName, FieldName)  ((((IDX_CALC(FieldName) - IDX_CALC(RegName) - 1) / 2) <= 15) ? ((IDX_CALC(FieldName) - IDX_CALC(RegName) - 1) / 2) : 0)

#define  TRxSmuIntReq                                           TOKEN_DEF (IDX_CALC (RxSmuIntReq), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuIntToggle                                       TOKEN_DEF (IDX_CALC (BfxSmuIntToggle), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuServiceIndex                                    TOKEN_DEF (IDX_CALC (BfxSmuServiceIndex), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuIntSts                                           TOKEN_DEF (IDX_CALC (RxSmuIntSts), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuIntAck                                          TOKEN_DEF (IDX_CALC (BfxSmuIntAck), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuIntDone                                         TOKEN_DEF (IDX_CALC (BfxSmuIntDone), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuAuthSts                                          TOKEN_DEF (IDX_CALC (RxSmuAuthSts), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuAuthDone                                        TOKEN_DEF (IDX_CALC (BfxSmuAuthDone), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuAuthPass                                        TOKEN_DEF (IDX_CALC (BfxSmuAuthPass), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuFwAuth                                           TOKEN_DEF (IDX_CALC (RxSmuFwAuth), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuProtectedMode                                   TOKEN_DEF (IDX_CALC (BfxSmuProtectedMode), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuRcuUcEvents                                      TOKEN_DEF (IDX_CALC (RxSmuRcuUcEvents), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuBootSeqDone                                     TOKEN_DEF (IDX_CALC (BfxSmuBootSeqDone), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuFwFlags                                          TOKEN_DEF (IDX_CALC (RxSmuFwFlags), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_PROTOCOL_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuInterruptsEnabled                               TOKEN_DEF (IDX_CALC (BfxSmuInterruptsEnabled), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_PROTOCOL_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuResetCntl                                        TOKEN_DEF (IDX_CALC (RxSmuResetCntl), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuRstReg                                          TOKEN_DEF (IDX_CALC (BfxSmuRstReg), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuClkCntl                                          TOKEN_DEF (IDX_CALC (RxSmuClkCntl), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TBfxSmuCkDisable                                       TOKEN_DEF (IDX_CALC (BfxSmuCkDisable), URA_TYPE_FIELD_16, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuAuthVector                                       TOKEN_DEF (IDX_CALC (RxSmuAuthVector), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuRamStartAddr                                     TOKEN_DEF (IDX_CALC (RxSmuRamStartAddr), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuRomStartAddr                                     TOKEN_DEF (IDX_CALC (RxSmuRomStartAddr), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuIntArgument                                      TOKEN_DEF (IDX_CALC (RxSmuIntArgument), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)


/// Template structure for register/field table
typedef struct {
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageId;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageResponse;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument0;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument1;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument2;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument3;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument4;///<
  URA_REGISTER_64B_ENTRY                                        RxSmuMessageArgument5;///<

} REG_FIELD_TABLE_STRUCT_V8;

#define  IDX_CALC_V8(VarName) (offsetof (REG_FIELD_TABLE_STRUCT_V8, VarName) / 2)

#define  TRxSmuMessageId                                        TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageId), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageResponse                                  TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageResponse), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument0                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument0), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument1                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument1), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument2                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument2), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument3                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument3), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument4                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument4), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)
#define  TRxSmuMessageArgument5                                 TOKEN_DEF (IDX_CALC_V8 (RxSmuMessageArgument5), URA_TYPE_REGISTER_64, SEL_CALC (TYPE_GNB_INDIRECT_ACCESS), URA_TOKEN_PARENT_TYPE_64)

#endif


