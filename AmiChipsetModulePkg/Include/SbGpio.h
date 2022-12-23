//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file Gpio.h
    South bridge default GPIO Definition.

**/
//**********************************************************************

#ifndef _SB_GPIO_H              // To Avoid this header get compiled twice
#define _SB_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif

// This is a explanation for the following structure,
// The first value is a 16 bit width for GPIO number.
// The second value is a 16 bit width for GPIO configuration, please refer to
// GPIO.SDL for its definition.

#ifdef GPIO_000
{ 0 , GPIO_000 },
#endif

#ifdef GPIO_001
{ 1 , GPIO_001 },
#endif

#ifdef GPIO_002
{ 2 , GPIO_002 },
#endif

#ifdef GPIO_003
{ 3 , GPIO_003 },
#endif

#ifdef GPIO_004
{ 4 , GPIO_004 },
#endif

#ifdef GPIO_005
{ 5 , GPIO_005 },
#endif

#ifdef GPIO_006
{ 6 , GPIO_006 },
#endif

#ifdef GPIO_007
{ 7 , GPIO_007 },
#endif

#ifdef GPIO_008
{ 8 , GPIO_008 },
#endif

#ifdef GPIO_009
{ 9 , GPIO_009 },
#endif

#ifdef GPIO_010
{ 10 , GPIO_010 },
#endif

#ifdef GPIO_011
{ 11 , GPIO_011 },
#endif

#ifdef GPIO_012
{ 12 , GPIO_012 },
#endif

#ifdef GPIO_013
{ 13 , GPIO_013 },
#endif

#ifdef GPIO_014
{ 14 , GPIO_014 },
#endif

#ifdef GPIO_015
{ 15 , GPIO_015 },
#endif

#ifdef GPIO_016
{ 16 , GPIO_016 },
#endif

#ifdef GPIO_017
{ 17 , GPIO_017 },
#endif

#ifdef GPIO_018
{ 18 , GPIO_018 },
#endif

#ifdef GPIO_019
{ 19 , GPIO_019 },
#endif

#ifdef GPIO_020
{ 20 , GPIO_020 },
#endif

#ifdef GPIO_021
{ 21 , GPIO_021 },
#endif

#ifdef GPIO_022
{ 22 , GPIO_022 },
#endif

#ifdef GPIO_023
{ 23 , GPIO_023 },
#endif

#ifdef GPIO_024
{ 24 , GPIO_024 },
#endif

#ifdef GPIO_025
{ 25 , GPIO_025 },
#endif

#ifdef GPIO_026
{ 26 , GPIO_026 },
#endif

#ifdef GPIO_027
{ 27 , GPIO_027 },
#endif

#ifdef GPIO_028
{ 28 , GPIO_028 },
#endif

#ifdef GPIO_029
{ 29 , GPIO_029 },
#endif

#ifdef GPIO_030
{ 30 , GPIO_030 },
#endif

#ifdef GPIO_031
{ 31 , GPIO_031 },
#endif

#ifdef GPIO_032
{ 32 , GPIO_032 },
#endif

#ifdef GPIO_033
{ 33 , GPIO_033 },
#endif

#ifdef GPIO_034
{ 34 , GPIO_034 },
#endif

#ifdef GPIO_035
{ 35 , GPIO_035 },
#endif

#ifdef GPIO_036
{ 36 , GPIO_036 },
#endif

#ifdef GPIO_037
{ 37 , GPIO_037 },
#endif

#ifdef GPIO_038
{ 38 , GPIO_038 },
#endif

#ifdef GPIO_064
{ 64 , GPIO_064 },
#endif

#ifdef GPIO_065
{ 65 , GPIO_065 },
#endif

#ifdef GPIO_066
{ 66 , GPIO_066 },
#endif

#ifdef GPIO_067
{ 67 , GPIO_067 },
#endif

#ifdef GPIO_068
{ 68 , GPIO_068 },
#endif

#ifdef GPIO_069
{ 69 , GPIO_069 },
#endif

#ifdef GPIO_070
{ 70 , GPIO_070 },
#endif

#ifdef GPIO_071
{ 71 , GPIO_071 },
#endif

#ifdef GPIO_072
{ 72 , GPIO_072 },
#endif

#ifdef GPIO_073
{ 73 , GPIO_073 },
#endif

#ifdef GPIO_076
{ 76 , GPIO_076 },
#endif

#ifdef GPIO_077
{ 77 , GPIO_077 },
#endif

#ifdef GPIO_084
{ 84 , GPIO_084 },
#endif

#ifdef GPIO_085
{ 85 , GPIO_085 },
#endif

#ifdef GPIO_087
{ 87 , GPIO_087 },
#endif

#ifdef GPIO_088
{ 88 , GPIO_088 },
#endif

#ifdef GPIO_089
{ 89 , GPIO_089 },
#endif

#ifdef GPIO_090
{ 90 , GPIO_090 },
#endif

#ifdef GPIO_091
{ 91 , GPIO_091 },
#endif

#ifdef GPIO_092
{ 92 , GPIO_092 },
#endif

#ifdef GPIO_093
{ 93 , GPIO_093 },
#endif

#ifdef GPIO_094
{ 94 , GPIO_094 },
#endif

#ifdef GPIO_095
{ 95 , GPIO_095 },
#endif

#ifdef GPIO_096
{ 96 , GPIO_096 },
#endif

#ifdef GPIO_097
{ 97 , GPIO_097 },
#endif

#ifdef GPIO_098
{ 98 , GPIO_098 },
#endif

#ifdef GPIO_099
{ 99 , GPIO_099 },
#endif

#ifdef GPIO_100
{ 100 , GPIO_100 },
#endif

#ifdef GPIO_101
{ 101 , GPIO_101 },
#endif

#ifdef GPIO_113
{ 113 , GPIO_113 },
#endif

#ifdef GPIO_114
{ 114 , GPIO_114 },
#endif

#ifdef GPIO_115
{ 115 , GPIO_115 },
#endif

#ifdef GPIO_116
{ 116 , GPIO_116 },
#endif

#ifdef GPIO_126
{ 126 , GPIO_126 },
#endif

#ifdef GPIO_129
{ 129 , GPIO_129 },
#endif

#ifdef GPIO_130
{ 130 , GPIO_130 },
#endif

#ifdef GPIO_131
{ 131 , GPIO_131 },
#endif

#ifdef GPIO_132
{ 132 , GPIO_132 },
#endif

#ifdef GPIO_133
{ 132 , GPIO_133 },
#endif

#ifdef GPIO_134
{ 132 , GPIO_134 },
#endif

#ifdef GPIO_135
{ 132 , GPIO_135 },
#endif

#ifdef GPIO_136
{ 132 , GPIO_136 },
#endif

#ifdef GPIO_137
{ 132 , GPIO_137 },
#endif

#ifdef GPIO_138
{ 132 , GPIO_138 },
#endif

#ifdef GPIO_139
{ 132 , GPIO_139 },
#endif

#ifdef GPIO_140
{ 132 , GPIO_140 },
#endif

#ifdef GPIO_141
{ 132 , GPIO_141 },
#endif

#ifdef GPIO_142
{ 132 , GPIO_142 },
#endif

#ifdef GPIO_143
{ 132 , GPIO_143 },
#endif

#ifdef GPIO_144
{ 132 , GPIO_144 },
#endif

#ifdef GPIO_145
{ 132 , GPIO_145 },
#endif

#ifdef GPIO_146
{ 132 , GPIO_146 },
#endif

#ifdef GPIO_147
{ 132 , GPIO_147 },
#endif

#ifdef GPIO_148
{ 132 , GPIO_148 },
#endif

#ifdef GPIO_149
{ 132 , GPIO_149 },
#endif

#ifdef GPIO_150
{ 132 , GPIO_150 },
#endif

#ifdef GPIO_151
{ 132 , GPIO_151 },
#endif

#ifdef GPIO_152
{ 132 , GPIO_152 },
#endif

{0xffff, 0xffff}, // End of the table.


/*
//****************************************************************************;
//                  GPIO_Pins_Descriptions_Table                              ;
//****************************************************************************;
Please refer PPR from AMD's document
//***************************************************************************;
// !!Don't change following equates!!                        ;
//***************************************************************************;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
