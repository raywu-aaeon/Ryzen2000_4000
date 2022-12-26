/** @file
	AaeonDio3Setup.h: DIO setup default definitions
**/

#ifndef BIT0
  #define BIT0 1
#endif

// ==================================================================
// DIO direction default
// ==================================================================
#if (FIRST_DIO_DIR_DEFAULT & BIT0) == 1
  #define DIO_DIR_0_DEFAULT 1
#else
  #define DIO_DIR_0_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 1) & BIT0) == 1
  #define DIO_DIR_1_DEFAULT 1
#else
  #define DIO_DIR_1_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 2) & BIT0) == 1
  #define DIO_DIR_2_DEFAULT 1
#else
  #define DIO_DIR_2_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 3) & BIT0) == 1
  #define DIO_DIR_3_DEFAULT 1
#else
  #define DIO_DIR_3_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 4) & BIT0) == 1
  #define DIO_DIR_4_DEFAULT 1
#else
  #define DIO_DIR_4_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 5) & BIT0) == 1
  #define DIO_DIR_5_DEFAULT 1
#else
  #define DIO_DIR_5_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 6) & BIT0) == 1
  #define DIO_DIR_6_DEFAULT 1
#else
  #define DIO_DIR_6_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 7) & BIT0) == 1
  #define DIO_DIR_7_DEFAULT 1
#else
  #define DIO_DIR_7_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 8) & BIT0) == 1
  #define DIO_DIR_8_DEFAULT 1
#else
  #define DIO_DIR_8_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 9) & BIT0) == 1
  #define DIO_DIR_9_DEFAULT 1
#else
  #define DIO_DIR_9_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 10) & BIT0) == 1
  #define DIO_DIR_10_DEFAULT 1
#else
  #define DIO_DIR_10_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 11) & BIT0) == 1
  #define DIO_DIR_11_DEFAULT 1
#else
  #define DIO_DIR_11_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 12) & BIT0) == 1
  #define DIO_DIR_12_DEFAULT 1
#else
  #define DIO_DIR_12_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 13) & BIT0) == 1
  #define DIO_DIR_13_DEFAULT 1
#else
  #define DIO_DIR_13_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 14) & BIT0) == 1
  #define DIO_DIR_14_DEFAULT 1
#else
  #define DIO_DIR_14_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 15) & BIT0) == 1
  #define DIO_DIR_15_DEFAULT 1
#else
  #define DIO_DIR_15_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 16) & BIT0) == 1
  #define DIO_DIR_16_DEFAULT 1
#else
  #define DIO_DIR_16_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 17) & BIT0) == 1
  #define DIO_DIR_17_DEFAULT 1
#else
  #define DIO_DIR_17_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 18) & BIT0) == 1
  #define DIO_DIR_18_DEFAULT 1
#else
  #define DIO_DIR_18_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 19) & BIT0) == 1
  #define DIO_DIR_19_DEFAULT 1
#else
  #define DIO_DIR_19_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 20) & BIT0) == 1
  #define DIO_DIR_20_DEFAULT 1
#else
  #define DIO_DIR_20_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 21) & BIT0) == 1
  #define DIO_DIR_21_DEFAULT 1
#else
  #define DIO_DIR_21_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 22) & BIT0) == 1
  #define DIO_DIR_22_DEFAULT 1
#else
  #define DIO_DIR_22_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 23) & BIT0) == 1
  #define DIO_DIR_23_DEFAULT 1
#else
  #define DIO_DIR_23_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 24) & BIT0) == 1
  #define DIO_DIR_24_DEFAULT 1
#else
  #define DIO_DIR_24_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 25) & BIT0) == 1
  #define DIO_DIR_25_DEFAULT 1
#else
  #define DIO_DIR_25_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 26) & BIT0) == 1
  #define DIO_DIR_26_DEFAULT 1
#else
  #define DIO_DIR_26_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 27) & BIT0) == 1
  #define DIO_DIR_27_DEFAULT 1
#else
  #define DIO_DIR_27_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 28) & BIT0) == 1
  #define DIO_DIR_28_DEFAULT 1
#else
  #define DIO_DIR_28_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 29) & BIT0) == 1
  #define DIO_DIR_29_DEFAULT 1
#else
  #define DIO_DIR_29_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 30) & BIT0) == 1
  #define DIO_DIR_30_DEFAULT 1
#else
  #define DIO_DIR_30_DEFAULT 0
#endif
#if ((FIRST_DIO_DIR_DEFAULT >> 31) & BIT0) == 1
  #define DIO_DIR_31_DEFAULT 1
#else
  #define DIO_DIR_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((FIRST_DIO_DIR_DEFAULT2 >> 0) & BIT0) == 1
//  #define DIO_DIR_32_DEFAULT 1
//#else
//  #define DIO_DIR_32_DEFAULT 0
//#endif
// ...
#endif

#if (SECOND_DIO_DIR_DEFAULT & BIT0) == 1
  #define SEC_DIO_DIR_0_DEFAULT 1
#else
  #define SEC_DIO_DIR_0_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 1) & BIT0) == 1
  #define SEC_DIO_DIR_1_DEFAULT 1
#else
  #define SEC_DIO_DIR_1_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 2) & BIT0) == 1
  #define SEC_DIO_DIR_2_DEFAULT 1
#else
  #define SEC_DIO_DIR_2_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 3) & BIT0) == 1
  #define SEC_DIO_DIR_3_DEFAULT 1
#else
  #define SEC_DIO_DIR_3_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 4) & BIT0) == 1
  #define SEC_DIO_DIR_4_DEFAULT 1
#else
  #define SEC_DIO_DIR_4_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 5) & BIT0) == 1
  #define SEC_DIO_DIR_5_DEFAULT 1
#else
  #define SEC_DIO_DIR_5_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 6) & BIT0) == 1
  #define SEC_DIO_DIR_6_DEFAULT 1
#else
  #define SEC_DIO_DIR_6_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 7) & BIT0) == 1
  #define SEC_DIO_DIR_7_DEFAULT 1
#else
  #define SEC_DIO_DIR_7_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 8) & BIT0) == 1
  #define SEC_DIO_DIR_8_DEFAULT 1
#else
  #define SEC_DIO_DIR_8_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 9) & BIT0) == 1
  #define SEC_DIO_DIR_9_DEFAULT 1
#else
  #define SEC_DIO_DIR_9_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 10) & BIT0) == 1
  #define SEC_DIO_DIR_10_DEFAULT 1
#else
  #define SEC_DIO_DIR_10_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 11) & BIT0) == 1
  #define SEC_DIO_DIR_11_DEFAULT 1
#else
  #define SEC_DIO_DIR_11_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 12) & BIT0) == 1
  #define SEC_DIO_DIR_12_DEFAULT 1
#else
  #define SEC_DIO_DIR_12_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 13) & BIT0) == 1
  #define SEC_DIO_DIR_13_DEFAULT 1
#else
  #define SEC_DIO_DIR_13_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 14) & BIT0) == 1
  #define SEC_DIO_DIR_14_DEFAULT 1
#else
  #define SEC_DIO_DIR_14_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 15) & BIT0) == 1
  #define SEC_DIO_DIR_15_DEFAULT 1
#else
  #define SEC_DIO_DIR_15_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 16) & BIT0) == 1
  #define SEC_DIO_DIR_16_DEFAULT 1
#else
  #define SEC_DIO_DIR_16_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 17) & BIT0) == 1
  #define SEC_DIO_DIR_17_DEFAULT 1
#else
  #define SEC_DIO_DIR_17_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 18) & BIT0) == 1
  #define SEC_DIO_DIR_18_DEFAULT 1
#else
  #define SEC_DIO_DIR_18_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 19) & BIT0) == 1
  #define SEC_DIO_DIR_19_DEFAULT 1
#else
  #define SEC_DIO_DIR_19_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 20) & BIT0) == 1
  #define SEC_DIO_DIR_20_DEFAULT 1
#else
  #define SEC_DIO_DIR_20_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 21) & BIT0) == 1
  #define SEC_DIO_DIR_21_DEFAULT 1
#else
  #define SEC_DIO_DIR_21_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 22) & BIT0) == 1
  #define SEC_DIO_DIR_22_DEFAULT 1
#else
  #define SEC_DIO_DIR_22_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 23) & BIT0) == 1
  #define SEC_DIO_DIR_23_DEFAULT 1
#else
  #define SEC_DIO_DIR_23_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 24) & BIT0) == 1
  #define SEC_DIO_DIR_24_DEFAULT 1
#else
  #define SEC_DIO_DIR_24_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 25) & BIT0) == 1
  #define SEC_DIO_DIR_25_DEFAULT 1
#else
  #define SEC_DIO_DIR_25_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 26) & BIT0) == 1
  #define SEC_DIO_DIR_26_DEFAULT 1
#else
  #define SEC_DIO_DIR_26_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 27) & BIT0) == 1
  #define SEC_DIO_DIR_27_DEFAULT 1
#else
  #define SEC_DIO_DIR_27_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 28) & BIT0) == 1
  #define SEC_DIO_DIR_28_DEFAULT 1
#else
  #define SEC_DIO_DIR_28_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 29) & BIT0) == 1
  #define SEC_DIO_DIR_29_DEFAULT 1
#else
  #define SEC_DIO_DIR_29_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 30) & BIT0) == 1
  #define SEC_DIO_DIR_30_DEFAULT 1
#else
  #define SEC_DIO_DIR_30_DEFAULT 0
#endif
#if ((SECOND_DIO_DIR_DEFAULT >> 31) & BIT0) == 1
  #define SEC_DIO_DIR_31_DEFAULT 1
#else
  #define SEC_DIO_DIR_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((SECOND_DIO_DIR_DEFAULT2 >> 0) & BIT0) == 1
//  #define SEC_DIO_DIR_32_DEFAULT 1
//#else
//  #define SEC_DIO_DIR_32_DEFAULT 0
//#endif
// ...
#endif

// ==================================================================
// DIO level default
// ==================================================================
#if (FIRST_DIO_LV_DEFAULT & BIT0) == 1
  #define DIO_LV_0_DEFAULT 1
#else
  #define DIO_LV_0_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 1) & BIT0) == 1
  #define DIO_LV_1_DEFAULT 1
#else
  #define DIO_LV_1_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 2) & BIT0) == 1
  #define DIO_LV_2_DEFAULT 1
#else
  #define DIO_LV_2_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 3) & BIT0) == 1
  #define DIO_LV_3_DEFAULT 1
#else
  #define DIO_LV_3_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 4) & BIT0) == 1
  #define DIO_LV_4_DEFAULT 1
#else
  #define DIO_LV_4_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 5) & BIT0) == 1
  #define DIO_LV_5_DEFAULT 1
#else
  #define DIO_LV_5_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 6) & BIT0) == 1
  #define DIO_LV_6_DEFAULT 1
#else
  #define DIO_LV_6_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 7) & BIT0) == 1
  #define DIO_LV_7_DEFAULT 1
#else
  #define DIO_LV_7_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 8) & BIT0) == 1
  #define DIO_LV_8_DEFAULT 1
#else
  #define DIO_LV_8_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 9) & BIT0) == 1
  #define DIO_LV_9_DEFAULT 1
#else
  #define DIO_LV_9_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 10) & BIT0) == 1
  #define DIO_LV_10_DEFAULT 1
#else
  #define DIO_LV_10_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 11) & BIT0) == 1
  #define DIO_LV_11_DEFAULT 1
#else
  #define DIO_LV_11_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 12) & BIT0) == 1
  #define DIO_LV_12_DEFAULT 1
#else
  #define DIO_LV_12_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 13) & BIT0) == 1
  #define DIO_LV_13_DEFAULT 1
#else
  #define DIO_LV_13_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 14) & BIT0) == 1
  #define DIO_LV_14_DEFAULT 1
#else
  #define DIO_LV_14_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 15) & BIT0) == 1
  #define DIO_LV_15_DEFAULT 1
#else
  #define DIO_LV_15_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 16) & BIT0) == 1
  #define DIO_LV_16_DEFAULT 1
#else
  #define DIO_LV_16_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 17) & BIT0) == 1
  #define DIO_LV_17_DEFAULT 1
#else
  #define DIO_LV_17_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 18) & BIT0) == 1
  #define DIO_LV_18_DEFAULT 1
#else
  #define DIO_LV_18_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 19) & BIT0) == 1
  #define DIO_LV_19_DEFAULT 1
#else
  #define DIO_LV_19_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 20) & BIT0) == 1
  #define DIO_LV_20_DEFAULT 1
#else
  #define DIO_LV_20_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 21) & BIT0) == 1
  #define DIO_LV_21_DEFAULT 1
#else
  #define DIO_LV_21_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 22) & BIT0) == 1
  #define DIO_LV_22_DEFAULT 1
#else
  #define DIO_LV_22_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 23) & BIT0) == 1
  #define DIO_LV_23_DEFAULT 1
#else
  #define DIO_LV_23_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 24) & BIT0) == 1
  #define DIO_LV_24_DEFAULT 1
#else
  #define DIO_LV_24_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 25) & BIT0) == 1
  #define DIO_LV_25_DEFAULT 1
#else
  #define DIO_LV_25_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 26) & BIT0) == 1
  #define DIO_LV_26_DEFAULT 1
#else
  #define DIO_LV_26_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 27) & BIT0) == 1
  #define DIO_LV_27_DEFAULT 1
#else
  #define DIO_LV_27_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 28) & BIT0) == 1
  #define DIO_LV_28_DEFAULT 1
#else
  #define DIO_LV_28_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 29) & BIT0) == 1
  #define DIO_LV_29_DEFAULT 1
#else
  #define DIO_LV_29_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 30) & BIT0) == 1
  #define DIO_LV_30_DEFAULT 1
#else
  #define DIO_LV_30_DEFAULT 0
#endif
#if ((FIRST_DIO_LV_DEFAULT >> 31) & BIT0) == 1
  #define DIO_LV_31_DEFAULT 1
#else
  #define DIO_LV_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((FIRST_DIO_LV_DEFAULT2 >> 0) & BIT0) == 1
//  #define DIO_LV_32_DEFAULT 1
//#else
//  #define DIO_LV_32_DEFAULT 0
//#endif
// ...
#endif

#if (SECOND_DIO_LV_DEFAULT & BIT0) == 1
  #define SEC_DIO_LV_0_DEFAULT 1
#else
  #define SEC_DIO_LV_0_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 1) & BIT0) == 1
  #define SEC_DIO_LV_1_DEFAULT 1
#else
  #define SEC_DIO_LV_1_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 2) & BIT0) == 1
  #define SEC_DIO_LV_2_DEFAULT 1
#else
  #define SEC_DIO_LV_2_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 3) & BIT0) == 1
  #define SEC_DIO_LV_3_DEFAULT 1
#else
  #define SEC_DIO_LV_3_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 4) & BIT0) == 1
  #define SEC_DIO_LV_4_DEFAULT 1
#else
  #define SEC_DIO_LV_4_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 5) & BIT0) == 1
  #define SEC_DIO_LV_5_DEFAULT 1
#else
  #define SEC_DIO_LV_5_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 6) & BIT0) == 1
  #define SEC_DIO_LV_6_DEFAULT 1
#else
  #define SEC_DIO_LV_6_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 7) & BIT0) == 1
  #define SEC_DIO_LV_7_DEFAULT 1
#else
  #define SEC_DIO_LV_7_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 8) & BIT0) == 1
  #define SEC_DIO_LV_8_DEFAULT 1
#else
  #define SEC_DIO_LV_8_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 9) & BIT0) == 1
  #define SEC_DIO_LV_9_DEFAULT 1
#else
  #define SEC_DIO_LV_9_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 10) & BIT0) == 1
  #define SEC_DIO_LV_10_DEFAULT 1
#else
  #define SEC_DIO_LV_10_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 11) & BIT0) == 1
  #define SEC_DIO_LV_11_DEFAULT 1
#else
  #define SEC_DIO_LV_11_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 12) & BIT0) == 1
  #define SEC_DIO_LV_12_DEFAULT 1
#else
  #define SEC_DIO_LV_12_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 13) & BIT0) == 1
  #define SEC_DIO_LV_13_DEFAULT 1
#else
  #define SEC_DIO_LV_13_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 14) & BIT0) == 1
  #define SEC_DIO_LV_14_DEFAULT 1
#else
  #define SEC_DIO_LV_14_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 15) & BIT0) == 1
  #define SEC_DIO_LV_15_DEFAULT 1
#else
  #define SEC_DIO_LV_15_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 16) & BIT0) == 1
  #define SEC_DIO_LV_16_DEFAULT 1
#else
  #define SEC_DIO_LV_16_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 17) & BIT0) == 1
  #define SEC_DIO_LV_17_DEFAULT 1
#else
  #define SEC_DIO_LV_17_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 18) & BIT0) == 1
  #define SEC_DIO_LV_18_DEFAULT 1
#else
  #define SEC_DIO_LV_18_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 19) & BIT0) == 1
  #define SEC_DIO_LV_19_DEFAULT 1
#else
  #define SEC_DIO_LV_19_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 20) & BIT0) == 1
  #define SEC_DIO_LV_20_DEFAULT 1
#else
  #define SEC_DIO_LV_20_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 21) & BIT0) == 1
  #define SEC_DIO_LV_21_DEFAULT 1
#else
  #define SEC_DIO_LV_21_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 22) & BIT0) == 1
  #define SEC_DIO_LV_22_DEFAULT 1
#else
  #define SEC_DIO_LV_22_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 23) & BIT0) == 1
  #define SEC_DIO_LV_23_DEFAULT 1
#else
  #define SEC_DIO_LV_23_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 24) & BIT0) == 1
  #define SEC_DIO_LV_24_DEFAULT 1
#else
  #define SEC_DIO_LV_24_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 25) & BIT0) == 1
  #define SEC_DIO_LV_25_DEFAULT 1
#else
  #define SEC_DIO_LV_25_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 26) & BIT0) == 1
  #define SEC_DIO_LV_26_DEFAULT 1
#else
  #define SEC_DIO_LV_26_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 27) & BIT0) == 1
  #define SEC_DIO_LV_27_DEFAULT 1
#else
  #define SEC_DIO_LV_27_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 28) & BIT0) == 1
  #define SEC_DIO_LV_28_DEFAULT 1
#else
  #define SEC_DIO_LV_28_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 29) & BIT0) == 1
  #define SEC_DIO_LV_29_DEFAULT 1
#else
  #define SEC_DIO_LV_29_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 30) & BIT0) == 1
  #define SEC_DIO_LV_30_DEFAULT 1
#else
  #define SEC_DIO_LV_30_DEFAULT 0
#endif
#if ((SECOND_DIO_LV_DEFAULT >> 31) & BIT0) == 1
  #define SEC_DIO_LV_31_DEFAULT 1
#else
  #define SEC_DIO_LV_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((SECOND_DIO_LV_DEFAULT2 >> 0) & BIT0) == 1
//  #define SEC_DIO_LV_32_DEFAULT 1
//#else
//  #define SEC_DIO_LV_32_DEFAULT 0
//#endif
// ...
#endif

// ==================================================================
// DIO Interrupt default
// ==================================================================
#if (FIRST_DIO_INT_DEFAULT & BIT0) == 1
  #define DIO_INT_0_DEFAULT 1
#else
  #define DIO_INT_0_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 1) & BIT0) == 1
  #define DIO_INT_1_DEFAULT 1
#else
  #define DIO_INT_1_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 2) & BIT0) == 1
  #define DIO_INT_2_DEFAULT 1
#else
  #define DIO_INT_2_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 3) & BIT0) == 1
  #define DIO_INT_3_DEFAULT 1
#else
  #define DIO_INT_3_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 4) & BIT0) == 1
  #define DIO_INT_4_DEFAULT 1
#else
  #define DIO_INT_4_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 5) & BIT0) == 1
  #define DIO_INT_5_DEFAULT 1
#else
  #define DIO_INT_5_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 6) & BIT0) == 1
  #define DIO_INT_6_DEFAULT 1
#else
  #define DIO_INT_6_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 7) & BIT0) == 1
  #define DIO_INT_7_DEFAULT 1
#else
  #define DIO_INT_7_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 8) & BIT0) == 1
  #define DIO_INT_8_DEFAULT 1
#else
  #define DIO_INT_8_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 9) & BIT0) == 1
  #define DIO_INT_9_DEFAULT 1
#else
  #define DIO_INT_9_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 10) & BIT0) == 1
  #define DIO_INT_10_DEFAULT 1
#else
  #define DIO_INT_10_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 11) & BIT0) == 1
  #define DIO_INT_11_DEFAULT 1
#else
  #define DIO_INT_11_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 12) & BIT0) == 1
  #define DIO_INT_12_DEFAULT 1
#else
  #define DIO_INT_12_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 13) & BIT0) == 1
  #define DIO_INT_13_DEFAULT 1
#else
  #define DIO_INT_13_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 14) & BIT0) == 1
  #define DIO_INT_14_DEFAULT 1
#else
  #define DIO_INT_14_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 15) & BIT0) == 1
  #define DIO_INT_15_DEFAULT 1
#else
  #define DIO_INT_15_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 16) & BIT0) == 1
  #define DIO_INT_16_DEFAULT 1
#else
  #define DIO_INT_16_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 17) & BIT0) == 1
  #define DIO_INT_17_DEFAULT 1
#else
  #define DIO_INT_17_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 18) & BIT0) == 1
  #define DIO_INT_18_DEFAULT 1
#else
  #define DIO_INT_18_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 19) & BIT0) == 1
  #define DIO_INT_19_DEFAULT 1
#else
  #define DIO_INT_19_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 20) & BIT0) == 1
  #define DIO_INT_20_DEFAULT 1
#else
  #define DIO_INT_20_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 21) & BIT0) == 1
  #define DIO_INT_21_DEFAULT 1
#else
  #define DIO_INT_21_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 22) & BIT0) == 1
  #define DIO_INT_22_DEFAULT 1
#else
  #define DIO_INT_22_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 23) & BIT0) == 1
  #define DIO_INT_23_DEFAULT 1
#else
  #define DIO_INT_23_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 24) & BIT0) == 1
  #define DIO_INT_24_DEFAULT 1
#else
  #define DIO_INT_24_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 25) & BIT0) == 1
  #define DIO_INT_25_DEFAULT 1
#else
  #define DIO_INT_25_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 26) & BIT0) == 1
  #define DIO_INT_26_DEFAULT 1
#else
  #define DIO_INT_26_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 27) & BIT0) == 1
  #define DIO_INT_27_DEFAULT 1
#else
  #define DIO_INT_27_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 28) & BIT0) == 1
  #define DIO_INT_28_DEFAULT 1
#else
  #define DIO_INT_28_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 29) & BIT0) == 1
  #define DIO_INT_29_DEFAULT 1
#else
  #define DIO_INT_29_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 30) & BIT0) == 1
  #define DIO_INT_30_DEFAULT 1
#else
  #define DIO_INT_30_DEFAULT 0
#endif
#if ((FIRST_DIO_INT_DEFAULT >> 31) & BIT0) == 1
  #define DIO_INT_31_DEFAULT 1
#else
  #define DIO_INT_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((FIRST_DIO_INT_DEFAULT2 >> 0) & BIT0) == 1
//  #define DIO_INT_32_DEFAULT 1
//#else
//  #define DIO_INT_32_DEFAULT 0
//#endif
// ...
#endif

#if (SECOND_DIO_INT_DEFAULT & BIT0) == 1
  #define SEC_DIO_INT_0_DEFAULT 1
#else
  #define SEC_DIO_INT_0_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 1) & BIT0) == 1
  #define SEC_DIO_INT_1_DEFAULT 1
#else
  #define SEC_DIO_INT_1_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 2) & BIT0) == 1
  #define SEC_DIO_INT_2_DEFAULT 1
#else
  #define SEC_DIO_INT_2_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 3) & BIT0) == 1
  #define SEC_DIO_INT_3_DEFAULT 1
#else
  #define SEC_DIO_INT_3_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 4) & BIT0) == 1
  #define SEC_DIO_INT_4_DEFAULT 1
#else
  #define SEC_DIO_INT_4_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 5) & BIT0) == 1
  #define SEC_DIO_INT_5_DEFAULT 1
#else
  #define SEC_DIO_INT_5_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 6) & BIT0) == 1
  #define SEC_DIO_INT_6_DEFAULT 1
#else
  #define SEC_DIO_INT_6_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 7) & BIT0) == 1
  #define SEC_DIO_INT_7_DEFAULT 1
#else
  #define SEC_DIO_INT_7_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 8) & BIT0) == 1
  #define SEC_DIO_INT_8_DEFAULT 1
#else
  #define SEC_DIO_INT_8_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 9) & BIT0) == 1
  #define SEC_DIO_INT_9_DEFAULT 1
#else
  #define SEC_DIO_INT_9_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 10) & BIT0) == 1
  #define SEC_DIO_INT_10_DEFAULT 1
#else
  #define SEC_DIO_INT_10_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 11) & BIT0) == 1
  #define SEC_DIO_INT_11_DEFAULT 1
#else
  #define SEC_DIO_INT_11_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 12) & BIT0) == 1
  #define SEC_DIO_INT_12_DEFAULT 1
#else
  #define SEC_DIO_INT_12_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 13) & BIT0) == 1
  #define SEC_DIO_INT_13_DEFAULT 1
#else
  #define SEC_DIO_INT_13_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 14) & BIT0) == 1
  #define SEC_DIO_INT_14_DEFAULT 1
#else
  #define SEC_DIO_INT_14_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 15) & BIT0) == 1
  #define SEC_DIO_INT_15_DEFAULT 1
#else
  #define SEC_DIO_INT_15_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 16) & BIT0) == 1
  #define SEC_DIO_INT_16_DEFAULT 1
#else
  #define SEC_DIO_INT_16_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 17) & BIT0) == 1
  #define SEC_DIO_INT_17_DEFAULT 1
#else
  #define SEC_DIO_INT_17_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 18) & BIT0) == 1
  #define SEC_DIO_INT_18_DEFAULT 1
#else
  #define SEC_DIO_INT_18_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 19) & BIT0) == 1
  #define SEC_DIO_INT_19_DEFAULT 1
#else
  #define SEC_DIO_INT_19_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 20) & BIT0) == 1
  #define SEC_DIO_INT_20_DEFAULT 1
#else
  #define SEC_DIO_INT_20_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 21) & BIT0) == 1
  #define SEC_DIO_INT_21_DEFAULT 1
#else
  #define SEC_DIO_INT_21_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 22) & BIT0) == 1
  #define SEC_DIO_INT_22_DEFAULT 1
#else
  #define SEC_DIO_INT_22_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 23) & BIT0) == 1
  #define SEC_DIO_INT_23_DEFAULT 1
#else
  #define SEC_DIO_INT_23_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 24) & BIT0) == 1
  #define SEC_DIO_INT_24_DEFAULT 1
#else
  #define SEC_DIO_INT_24_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 25) & BIT0) == 1
  #define SEC_DIO_INT_25_DEFAULT 1
#else
  #define SEC_DIO_INT_25_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 26) & BIT0) == 1
  #define SEC_DIO_INT_26_DEFAULT 1
#else
  #define SEC_DIO_INT_26_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 27) & BIT0) == 1
  #define SEC_DIO_INT_27_DEFAULT 1
#else
  #define SEC_DIO_INT_27_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 28) & BIT0) == 1
  #define SEC_DIO_INT_28_DEFAULT 1
#else
  #define SEC_DIO_INT_28_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 29) & BIT0) == 1
  #define SEC_DIO_INT_29_DEFAULT 1
#else
  #define SEC_DIO_INT_29_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 30) & BIT0) == 1
  #define SEC_DIO_INT_30_DEFAULT 1
#else
  #define SEC_DIO_INT_30_DEFAULT 0
#endif
#if ((SECOND_DIO_INT_DEFAULT >> 31) & BIT0) == 1
  #define SEC_DIO_INT_31_DEFAULT 1
#else
  #define SEC_DIO_INT_31_DEFAULT 0
#endif
#if FIRST_DIO_NUMBER > 32
Porting required
//#if ((SECOND_DIO_INT_DEFAULT2 >> 0) & BIT0) == 1
//  #define SEC_DIO_INT_32_DEFAULT 1
//#else
//  #define SEC_DIO_INT_32_DEFAULT 0
//#endif
#endif
