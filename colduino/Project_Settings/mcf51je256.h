/* Based on CPU DB MCF51JE256_104, version 3.00.012 (RegistersPrg V2.32) */
/*
** ###################################################################
**     Filename  : mcf51je256.h
**     Processor : MCF51JE256CML
**     FileFormat: V2.32
**     DataSheet : MCF51JE256 Rev. 1 07/2009
**     Compiler  : CodeWarrior compiler
**     Date/Time : 5.10.2010, 14:38
**     Abstract  :
**         This header implements the mapping of I/O devices.
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
**
**     CPU Registers Revisions:
**      - 25.5.2010, V3.00.0:
**              - Changed USB interrupt location from address 0x10C to 0x120.
**              - Removed SOPT5 register from 0xFFFF_980D. This location is reserved for internal testing.
**      - 23.6.2010, V3.00.1:
**              - Corrected position of DPDOWN,DMDOWN bits in the OTGPIN register.
**
**     File-Format-Revisions:
**      - 18.05.2010, V2.32 :
**               - MISRA compliance: U/UL suffixes added to all numbers (_MASK,_BITNUM and addresses)
**
**     Not all general-purpose I/O pins are available on all packages or on all mask sets of a specific
**     derivative device. To avoid extra current drain from floating input pins, the user’s reset
**     initialization routine in the application program must either enable on-chip pull-up devices
**     or change the direction of unconnected pins to outputs so the pins do not float.
** ###################################################################
*/

#ifndef _MCF51JE256_H
#define _MCF51JE256_H

/*lint -save  -e950 -esym(960,18.4) -e46 -esym(961,19.7) Disable MISRA rule (1.1,18.4,6.4,19.7) checking. */
/*lint -save  -e621 Disable MISRA rule (5.1) checking. */
/* Types definition */
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

/* Watchdog reset macro */
#ifndef __RESET_WATCHDOG
#ifdef _lint
  #define __RESET_WATCHDOG()  /* empty */
#else
  #define __RESET_WATCHDOG() (void)(SRS = 0x55U, SRS = 0xAAU)
#endif
#endif /* __RESET_WATCHDOG */

#pragma options align=packed

/**************** interrupt vector numbers ****************/
#define VectorNumber_INITSP             0U
#define VectorNumber_INITPC             1U
#define VectorNumber_Vaccerr            2U
#define VectorNumber_Vadderr            3U
#define VectorNumber_Viinstr            4U
#define VectorNumber_VReserved5         5U
#define VectorNumber_VReserved6         6U
#define VectorNumber_VReserved7         7U
#define VectorNumber_Vprviol            8U
#define VectorNumber_Vtrace             9U
#define VectorNumber_Vunilaop           10U
#define VectorNumber_Vunilfop           11U
#define VectorNumber_Vdbgi              12U
#define VectorNumber_VReserved13        13U
#define VectorNumber_Vferror            14U
#define VectorNumber_VReserved15        15U
#define VectorNumber_VReserved16        16U
#define VectorNumber_VReserved17        17U
#define VectorNumber_VReserved18        18U
#define VectorNumber_VReserved19        19U
#define VectorNumber_VReserved20        20U
#define VectorNumber_VReserved21        21U
#define VectorNumber_VReserved22        22U
#define VectorNumber_VReserved23        23U
#define VectorNumber_Vspuri             24U
#define VectorNumber_VReserved25        25U
#define VectorNumber_VReserved26        26U
#define VectorNumber_VReserved27        27U
#define VectorNumber_VReserved28        28U
#define VectorNumber_VReserved29        29U
#define VectorNumber_VReserved30        30U
#define VectorNumber_VReserved31        31U
#define VectorNumber_Vtrap0             32U
#define VectorNumber_Vtrap1             33U
#define VectorNumber_Vtrap2             34U
#define VectorNumber_Vtrap3             35U
#define VectorNumber_Vtrap4             36U
#define VectorNumber_Vtrap5             37U
#define VectorNumber_Vtrap6             38U
#define VectorNumber_Vtrap7             39U
#define VectorNumber_Vtrap8             40U
#define VectorNumber_Vtrap9             41U
#define VectorNumber_Vtrap10            42U
#define VectorNumber_Vtrap11            43U
#define VectorNumber_Vtrap12            44U
#define VectorNumber_Vtrap13            45U
#define VectorNumber_Vtrap14            46U
#define VectorNumber_Vtrap15            47U
#define VectorNumber_VReserved48        48U
#define VectorNumber_VReserved49        49U
#define VectorNumber_VReserved50        50U
#define VectorNumber_VReserved51        51U
#define VectorNumber_VReserved52        52U
#define VectorNumber_VReserved53        53U
#define VectorNumber_VReserved54        54U
#define VectorNumber_VReserved55        55U
#define VectorNumber_VReserved56        56U
#define VectorNumber_VReserved57        57U
#define VectorNumber_VReserved58        58U
#define VectorNumber_VReserved59        59U
#define VectorNumber_VReserved60        60U
#define VectorNumber_Vunsinstr          61U
#define VectorNumber_VReserved62        62U
#define VectorNumber_VReserved63        63U
#define VectorNumber_Virq               64U
#define VectorNumber_Vlvd               65U
#define VectorNumber_Vlol               66U
#define VectorNumber_VReserved67        67U
#define VectorNumber_Vpdb               68U
#define VectorNumber_Vdac               69U
#define VectorNumber_Vspi1              70U
#define VectorNumber_Vadc               71U
#define VectorNumber_Vusb               72U
#define VectorNumber_Vtpm1ch0           73U
#define VectorNumber_Vtpm1ch1           74U
#define VectorNumber_Vtpm1ch2           75U
#define VectorNumber_Vtpm1ch3           76U
#define VectorNumber_Vtpm1ovf           77U
#define VectorNumber_Vspi2              78U
#define VectorNumber_Vcmt               79U
#define VectorNumber_Vtpm2ch0           80U
#define VectorNumber_Vtpm2ch1           81U
#define VectorNumber_Vtpm2ch2           82U
#define VectorNumber_Vtpm2ch3           83U
#define VectorNumber_Vtpm2ovf           84U
#define VectorNumber_Viic               85U
#define VectorNumber_Vpracmp            86U
#define VectorNumber_Vsci1err           87U
#define VectorNumber_Vsci1rx            88U
#define VectorNumber_Vsci1tx            89U
#define VectorNumber_Vsci2err           90U
#define VectorNumber_Vsci2rx            91U
#define VectorNumber_Vsci2tx            92U
#define VectorNumber_VReserved93        93U
#define VectorNumber_VReserved94        94U
#define VectorNumber_Vkbi1              95U
#define VectorNumber_Vkbi2              96U
#define VectorNumber_Vtod               97U
#define VectorNumber_VReserved98        98U
#define VectorNumber_VReserved99        99U
#define VectorNumber_VReserved100       100U
#define VectorNumber_VReserved101       101U
#define VectorNumber_VReserved102       102U
#define VectorNumber_VL7swi             103U
#define VectorNumber_VL6swi             104U
#define VectorNumber_VL5swi             105U
#define VectorNumber_VL4swi             106U
#define VectorNumber_VL3swi             107U
#define VectorNumber_VL2swi             108U
#define VectorNumber_VL1swi             109U
#define VectorNumber_VReserved110       110U
#define VectorNumber_VReserved111       111U
#define VectorNumber_Vftsr1             112U
#define VectorNumber_Vftsr2             113U
#define VectorNumber_VReserved114       114U

/**************** interrupt vector table ****************/
#define INITSP                          0x0000U
#define INITPC                          0x0004U
#define Vaccerr                         0x0008U
#define Vadderr                         0x000CU
#define Viinstr                         0x0010U
#define VReserved5                      0x0014U
#define VReserved6                      0x0018U
#define VReserved7                      0x001CU
#define Vprviol                         0x0020U
#define Vtrace                          0x0024U
#define Vunilaop                        0x0028U
#define Vunilfop                        0x002CU
#define Vdbgi                           0x0030U
#define VReserved13                     0x0034U
#define Vferror                         0x0038U
#define VReserved15                     0x003CU
#define VReserved16                     0x0040U
#define VReserved17                     0x0044U
#define VReserved18                     0x0048U
#define VReserved19                     0x004CU
#define VReserved20                     0x0050U
#define VReserved21                     0x0054U
#define VReserved22                     0x0058U
#define VReserved23                     0x005CU
#define Vspuri                          0x0060U
#define VReserved25                     0x0064U
#define VReserved26                     0x0068U
#define VReserved27                     0x006CU
#define VReserved28                     0x0070U
#define VReserved29                     0x0074U
#define VReserved30                     0x0078U
#define VReserved31                     0x007CU
#define Vtrap0                          0x0080U
#define Vtrap1                          0x0084U
#define Vtrap2                          0x0088U
#define Vtrap3                          0x008CU
#define Vtrap4                          0x0090U
#define Vtrap5                          0x0094U
#define Vtrap6                          0x0098U
#define Vtrap7                          0x009CU
#define Vtrap8                          0x00A0U
#define Vtrap9                          0x00A4U
#define Vtrap10                         0x00A8U
#define Vtrap11                         0x00ACU
#define Vtrap12                         0x00B0U
#define Vtrap13                         0x00B4U
#define Vtrap14                         0x00B8U
#define Vtrap15                         0x00BCU
#define VReserved48                     0x00C0U
#define VReserved49                     0x00C4U
#define VReserved50                     0x00C8U
#define VReserved51                     0x00CCU
#define VReserved52                     0x00D0U
#define VReserved53                     0x00D4U
#define VReserved54                     0x00D8U
#define VReserved55                     0x00DCU
#define VReserved56                     0x00E0U
#define VReserved57                     0x00E4U
#define VReserved58                     0x00E8U
#define VReserved59                     0x00ECU
#define VReserved60                     0x00F0U
#define Vunsinstr                       0x00F4U
#define VReserved62                     0x00F8U
#define VReserved63                     0x00FCU
#define Virq                            0x0100U
#define Vlvd                            0x0104U
#define Vlol                            0x0108U
#define VReserved67                     0x010CU
#define Vpdb                            0x0110U
#define Vdac                            0x0114U
#define Vspi1                           0x0118U
#define Vadc                            0x011CU
#define Vusb                            0x0120U
#define Vtpm1ch0                        0x0124U
#define Vtpm1ch1                        0x0128U
#define Vtpm1ch2                        0x012CU
#define Vtpm1ch3                        0x0130U
#define Vtpm1ovf                        0x0134U
#define Vspi2                           0x0138U
#define Vcmt                            0x013CU
#define Vtpm2ch0                        0x0140U
#define Vtpm2ch1                        0x0144U
#define Vtpm2ch2                        0x0148U
#define Vtpm2ch3                        0x014CU
#define Vtpm2ovf                        0x0150U
#define Viic                            0x0154U
#define Vpracmp                         0x0158U
#define Vsci1err                        0x015CU
#define Vsci1rx                         0x0160U
#define Vsci1tx                         0x0164U
#define Vsci2err                        0x0168U
#define Vsci2rx                         0x016CU
#define Vsci2tx                         0x0170U
#define VReserved93                     0x0174U
#define VReserved94                     0x0178U
#define Vkbi1                           0x017CU
#define Vkbi2                           0x0180U
#define Vtod                            0x0184U
#define VReserved98                     0x0188U
#define VReserved99                     0x018CU
#define VReserved100                    0x0190U
#define VReserved101                    0x0194U
#define VReserved102                    0x0198U
#define VL7swi                          0x019CU
#define VL6swi                          0x01A0U
#define VL5swi                          0x01A4U
#define VL4swi                          0x01A8U
#define VL3swi                          0x01ACU
#define VL2swi                          0x01B0U
#define VL1swi                          0x01B4U
#define VReserved110                    0x01B8U
#define VReserved111                    0x01BCU
#define Vftsr1                          0x01C0U
#define Vftsr2                          0x01C4U
#define VReserved114                    0x01C8U

/**************** registers I/O map ****************/

/*** NV1FTRIM - Nonvolatile MCG Fine Trim; 0x000003FE ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* MCG Fine Trim */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} NV1FTRIMSTR;
/* Tip for register initialization in the user code:  const byte NV1FTRIM_INIT @0x000003FE = <NV1FTRIM_INITVAL>; */
#define _NV1FTRIM (*(const NV1FTRIMSTR *)0x000003FE)
#define NV1FTRIM                        _NV1FTRIM.Byte
#define NV1FTRIM_FTRIM                  _NV1FTRIM.Bits.FTRIM

#define NV1FTRIM_FTRIM_MASK             1U


/*** NV1MCGTRM - Nonvolatile MCG Trim Register; 0x000003FF ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* MCG Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* MCG Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* MCG Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* MCG Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* MCG Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* MCG Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* MCG Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* MCG Trim Setting, bit 7 */
  } Bits;
} NV1MCGTRMSTR;
/* Tip for register initialization in the user code:  const byte NV1MCGTRM_INIT @0x000003FF = <NV1MCGTRM_INITVAL>; */
#define _NV1MCGTRM (*(const NV1MCGTRMSTR *)0x000003FF)
#define NV1MCGTRM                       _NV1MCGTRM.Byte
#define NV1MCGTRM_TRIM0                 _NV1MCGTRM.Bits.TRIM0
#define NV1MCGTRM_TRIM1                 _NV1MCGTRM.Bits.TRIM1
#define NV1MCGTRM_TRIM2                 _NV1MCGTRM.Bits.TRIM2
#define NV1MCGTRM_TRIM3                 _NV1MCGTRM.Bits.TRIM3
#define NV1MCGTRM_TRIM4                 _NV1MCGTRM.Bits.TRIM4
#define NV1MCGTRM_TRIM5                 _NV1MCGTRM.Bits.TRIM5
#define NV1MCGTRM_TRIM6                 _NV1MCGTRM.Bits.TRIM6
#define NV1MCGTRM_TRIM7                 _NV1MCGTRM.Bits.TRIM7

#define NV1MCGTRM_TRIM0_MASK            1U
#define NV1MCGTRM_TRIM1_MASK            2U
#define NV1MCGTRM_TRIM2_MASK            4U
#define NV1MCGTRM_TRIM3_MASK            8U
#define NV1MCGTRM_TRIM4_MASK            16U
#define NV1MCGTRM_TRIM5_MASK            32U
#define NV1MCGTRM_TRIM6_MASK            64U
#define NV1MCGTRM_TRIM7_MASK            128U


/*** NV1BACKKEY0 - Backdoor Comparison Key 0; 0x00000400 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 7 */
  } Bits;
} NV1BACKKEY0STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY0_INIT @0x00000400 = <NV1BACKKEY0_INITVAL>; */
#define _NV1BACKKEY0 (*(const NV1BACKKEY0STR *)0x00000400)
#define NV1BACKKEY0                     _NV1BACKKEY0.Byte
#define NV1BACKKEY0_KEY0                _NV1BACKKEY0.Bits.KEY0
#define NV1BACKKEY0_KEY1                _NV1BACKKEY0.Bits.KEY1
#define NV1BACKKEY0_KEY2                _NV1BACKKEY0.Bits.KEY2
#define NV1BACKKEY0_KEY3                _NV1BACKKEY0.Bits.KEY3
#define NV1BACKKEY0_KEY4                _NV1BACKKEY0.Bits.KEY4
#define NV1BACKKEY0_KEY5                _NV1BACKKEY0.Bits.KEY5
#define NV1BACKKEY0_KEY6                _NV1BACKKEY0.Bits.KEY6
#define NV1BACKKEY0_KEY7                _NV1BACKKEY0.Bits.KEY7
/* NV1BACKKEY_ARR: Access 8 NV1BACKKEYx registers in an array */
#define NV1BACKKEY_ARR                  ((volatile byte *) &NV1BACKKEY0)

#define NV1BACKKEY0_KEY0_MASK           1U
#define NV1BACKKEY0_KEY1_MASK           2U
#define NV1BACKKEY0_KEY2_MASK           4U
#define NV1BACKKEY0_KEY3_MASK           8U
#define NV1BACKKEY0_KEY4_MASK           16U
#define NV1BACKKEY0_KEY5_MASK           32U
#define NV1BACKKEY0_KEY6_MASK           64U
#define NV1BACKKEY0_KEY7_MASK           128U


/*** NV1BACKKEY1 - Backdoor Comparison Key 1; 0x00000401 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 7 */
  } Bits;
} NV1BACKKEY1STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY1_INIT @0x00000401 = <NV1BACKKEY1_INITVAL>; */
#define _NV1BACKKEY1 (*(const NV1BACKKEY1STR *)0x00000401)
#define NV1BACKKEY1                     _NV1BACKKEY1.Byte
#define NV1BACKKEY1_KEY0                _NV1BACKKEY1.Bits.KEY0
#define NV1BACKKEY1_KEY1                _NV1BACKKEY1.Bits.KEY1
#define NV1BACKKEY1_KEY2                _NV1BACKKEY1.Bits.KEY2
#define NV1BACKKEY1_KEY3                _NV1BACKKEY1.Bits.KEY3
#define NV1BACKKEY1_KEY4                _NV1BACKKEY1.Bits.KEY4
#define NV1BACKKEY1_KEY5                _NV1BACKKEY1.Bits.KEY5
#define NV1BACKKEY1_KEY6                _NV1BACKKEY1.Bits.KEY6
#define NV1BACKKEY1_KEY7                _NV1BACKKEY1.Bits.KEY7

#define NV1BACKKEY1_KEY0_MASK           1U
#define NV1BACKKEY1_KEY1_MASK           2U
#define NV1BACKKEY1_KEY2_MASK           4U
#define NV1BACKKEY1_KEY3_MASK           8U
#define NV1BACKKEY1_KEY4_MASK           16U
#define NV1BACKKEY1_KEY5_MASK           32U
#define NV1BACKKEY1_KEY6_MASK           64U
#define NV1BACKKEY1_KEY7_MASK           128U


/*** NV1BACKKEY2 - Backdoor Comparison Key 2; 0x00000402 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 7 */
  } Bits;
} NV1BACKKEY2STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY2_INIT @0x00000402 = <NV1BACKKEY2_INITVAL>; */
#define _NV1BACKKEY2 (*(const NV1BACKKEY2STR *)0x00000402)
#define NV1BACKKEY2                     _NV1BACKKEY2.Byte
#define NV1BACKKEY2_KEY0                _NV1BACKKEY2.Bits.KEY0
#define NV1BACKKEY2_KEY1                _NV1BACKKEY2.Bits.KEY1
#define NV1BACKKEY2_KEY2                _NV1BACKKEY2.Bits.KEY2
#define NV1BACKKEY2_KEY3                _NV1BACKKEY2.Bits.KEY3
#define NV1BACKKEY2_KEY4                _NV1BACKKEY2.Bits.KEY4
#define NV1BACKKEY2_KEY5                _NV1BACKKEY2.Bits.KEY5
#define NV1BACKKEY2_KEY6                _NV1BACKKEY2.Bits.KEY6
#define NV1BACKKEY2_KEY7                _NV1BACKKEY2.Bits.KEY7

#define NV1BACKKEY2_KEY0_MASK           1U
#define NV1BACKKEY2_KEY1_MASK           2U
#define NV1BACKKEY2_KEY2_MASK           4U
#define NV1BACKKEY2_KEY3_MASK           8U
#define NV1BACKKEY2_KEY4_MASK           16U
#define NV1BACKKEY2_KEY5_MASK           32U
#define NV1BACKKEY2_KEY6_MASK           64U
#define NV1BACKKEY2_KEY7_MASK           128U


/*** NV1BACKKEY3 - Backdoor Comparison Key 3; 0x00000403 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 7 */
  } Bits;
} NV1BACKKEY3STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY3_INIT @0x00000403 = <NV1BACKKEY3_INITVAL>; */
#define _NV1BACKKEY3 (*(const NV1BACKKEY3STR *)0x00000403)
#define NV1BACKKEY3                     _NV1BACKKEY3.Byte
#define NV1BACKKEY3_KEY0                _NV1BACKKEY3.Bits.KEY0
#define NV1BACKKEY3_KEY1                _NV1BACKKEY3.Bits.KEY1
#define NV1BACKKEY3_KEY2                _NV1BACKKEY3.Bits.KEY2
#define NV1BACKKEY3_KEY3                _NV1BACKKEY3.Bits.KEY3
#define NV1BACKKEY3_KEY4                _NV1BACKKEY3.Bits.KEY4
#define NV1BACKKEY3_KEY5                _NV1BACKKEY3.Bits.KEY5
#define NV1BACKKEY3_KEY6                _NV1BACKKEY3.Bits.KEY6
#define NV1BACKKEY3_KEY7                _NV1BACKKEY3.Bits.KEY7

#define NV1BACKKEY3_KEY0_MASK           1U
#define NV1BACKKEY3_KEY1_MASK           2U
#define NV1BACKKEY3_KEY2_MASK           4U
#define NV1BACKKEY3_KEY3_MASK           8U
#define NV1BACKKEY3_KEY4_MASK           16U
#define NV1BACKKEY3_KEY5_MASK           32U
#define NV1BACKKEY3_KEY6_MASK           64U
#define NV1BACKKEY3_KEY7_MASK           128U


/*** NV1BACKKEY4 - Backdoor Comparison Key 4; 0x00000404 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 7 */
  } Bits;
} NV1BACKKEY4STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY4_INIT @0x00000404 = <NV1BACKKEY4_INITVAL>; */
#define _NV1BACKKEY4 (*(const NV1BACKKEY4STR *)0x00000404)
#define NV1BACKKEY4                     _NV1BACKKEY4.Byte
#define NV1BACKKEY4_KEY0                _NV1BACKKEY4.Bits.KEY0
#define NV1BACKKEY4_KEY1                _NV1BACKKEY4.Bits.KEY1
#define NV1BACKKEY4_KEY2                _NV1BACKKEY4.Bits.KEY2
#define NV1BACKKEY4_KEY3                _NV1BACKKEY4.Bits.KEY3
#define NV1BACKKEY4_KEY4                _NV1BACKKEY4.Bits.KEY4
#define NV1BACKKEY4_KEY5                _NV1BACKKEY4.Bits.KEY5
#define NV1BACKKEY4_KEY6                _NV1BACKKEY4.Bits.KEY6
#define NV1BACKKEY4_KEY7                _NV1BACKKEY4.Bits.KEY7

#define NV1BACKKEY4_KEY0_MASK           1U
#define NV1BACKKEY4_KEY1_MASK           2U
#define NV1BACKKEY4_KEY2_MASK           4U
#define NV1BACKKEY4_KEY3_MASK           8U
#define NV1BACKKEY4_KEY4_MASK           16U
#define NV1BACKKEY4_KEY5_MASK           32U
#define NV1BACKKEY4_KEY6_MASK           64U
#define NV1BACKKEY4_KEY7_MASK           128U


/*** NV1BACKKEY5 - Backdoor Comparison Key 5; 0x00000405 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 7 */
  } Bits;
} NV1BACKKEY5STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY5_INIT @0x00000405 = <NV1BACKKEY5_INITVAL>; */
#define _NV1BACKKEY5 (*(const NV1BACKKEY5STR *)0x00000405)
#define NV1BACKKEY5                     _NV1BACKKEY5.Byte
#define NV1BACKKEY5_KEY0                _NV1BACKKEY5.Bits.KEY0
#define NV1BACKKEY5_KEY1                _NV1BACKKEY5.Bits.KEY1
#define NV1BACKKEY5_KEY2                _NV1BACKKEY5.Bits.KEY2
#define NV1BACKKEY5_KEY3                _NV1BACKKEY5.Bits.KEY3
#define NV1BACKKEY5_KEY4                _NV1BACKKEY5.Bits.KEY4
#define NV1BACKKEY5_KEY5                _NV1BACKKEY5.Bits.KEY5
#define NV1BACKKEY5_KEY6                _NV1BACKKEY5.Bits.KEY6
#define NV1BACKKEY5_KEY7                _NV1BACKKEY5.Bits.KEY7

#define NV1BACKKEY5_KEY0_MASK           1U
#define NV1BACKKEY5_KEY1_MASK           2U
#define NV1BACKKEY5_KEY2_MASK           4U
#define NV1BACKKEY5_KEY3_MASK           8U
#define NV1BACKKEY5_KEY4_MASK           16U
#define NV1BACKKEY5_KEY5_MASK           32U
#define NV1BACKKEY5_KEY6_MASK           64U
#define NV1BACKKEY5_KEY7_MASK           128U


/*** NV1BACKKEY6 - Backdoor Comparison Key 6; 0x00000406 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 7 */
  } Bits;
} NV1BACKKEY6STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY6_INIT @0x00000406 = <NV1BACKKEY6_INITVAL>; */
#define _NV1BACKKEY6 (*(const NV1BACKKEY6STR *)0x00000406)
#define NV1BACKKEY6                     _NV1BACKKEY6.Byte
#define NV1BACKKEY6_KEY0                _NV1BACKKEY6.Bits.KEY0
#define NV1BACKKEY6_KEY1                _NV1BACKKEY6.Bits.KEY1
#define NV1BACKKEY6_KEY2                _NV1BACKKEY6.Bits.KEY2
#define NV1BACKKEY6_KEY3                _NV1BACKKEY6.Bits.KEY3
#define NV1BACKKEY6_KEY4                _NV1BACKKEY6.Bits.KEY4
#define NV1BACKKEY6_KEY5                _NV1BACKKEY6.Bits.KEY5
#define NV1BACKKEY6_KEY6                _NV1BACKKEY6.Bits.KEY6
#define NV1BACKKEY6_KEY7                _NV1BACKKEY6.Bits.KEY7

#define NV1BACKKEY6_KEY0_MASK           1U
#define NV1BACKKEY6_KEY1_MASK           2U
#define NV1BACKKEY6_KEY2_MASK           4U
#define NV1BACKKEY6_KEY3_MASK           8U
#define NV1BACKKEY6_KEY4_MASK           16U
#define NV1BACKKEY6_KEY5_MASK           32U
#define NV1BACKKEY6_KEY6_MASK           64U
#define NV1BACKKEY6_KEY7_MASK           128U


/*** NV1BACKKEY7 - Backdoor Comparison Key 7; 0x00000407 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 7 */
  } Bits;
} NV1BACKKEY7STR;
/* Tip for register initialization in the user code:  const byte NV1BACKKEY7_INIT @0x00000407 = <NV1BACKKEY7_INITVAL>; */
#define _NV1BACKKEY7 (*(const NV1BACKKEY7STR *)0x00000407)
#define NV1BACKKEY7                     _NV1BACKKEY7.Byte
#define NV1BACKKEY7_KEY0                _NV1BACKKEY7.Bits.KEY0
#define NV1BACKKEY7_KEY1                _NV1BACKKEY7.Bits.KEY1
#define NV1BACKKEY7_KEY2                _NV1BACKKEY7.Bits.KEY2
#define NV1BACKKEY7_KEY3                _NV1BACKKEY7.Bits.KEY3
#define NV1BACKKEY7_KEY4                _NV1BACKKEY7.Bits.KEY4
#define NV1BACKKEY7_KEY5                _NV1BACKKEY7.Bits.KEY5
#define NV1BACKKEY7_KEY6                _NV1BACKKEY7.Bits.KEY6
#define NV1BACKKEY7_KEY7                _NV1BACKKEY7.Bits.KEY7

#define NV1BACKKEY7_KEY0_MASK           1U
#define NV1BACKKEY7_KEY1_MASK           2U
#define NV1BACKKEY7_KEY2_MASK           4U
#define NV1BACKKEY7_KEY3_MASK           8U
#define NV1BACKKEY7_KEY4_MASK           16U
#define NV1BACKKEY7_KEY5_MASK           32U
#define NV1BACKKEY7_KEY6_MASK           64U
#define NV1BACKKEY7_KEY7_MASK           128U


/*** F1CHKS - Flash Checksum Register; 0x00000408 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** F1CHKSH - Flash Checksum Register High Byte; 0x00000408 ***/
    union {
      byte Byte;
      struct {
        byte CHECKSUM8   :1;                                       /* Flash checksum bit 8 */
        byte CHECKSUM9   :1;                                       /* Flash checksum bit 9 */
        byte CHECKSUM10  :1;                                       /* Flash checksum bit 10 */
        byte CHECKSUM11  :1;                                       /* Flash checksum bit 11 */
        byte CHECKSUM12  :1;                                       /* Flash checksum bit 12 */
        byte CHECKSUM13  :1;                                       /* Flash checksum bit 13 */
        byte CHECKSUM14  :1;                                       /* Flash checksum bit 14 */
        byte CHECKSUM15  :1;                                       /* Flash checksum bit 15 */
      } Bits;
    } F1CHKSHSTR;
    #define F1CHKSH                     _F1CHKS.Overlap_STR.F1CHKSHSTR.Byte
    #define F1CHKSH_CHECKSUM8           _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM8
    #define F1CHKSH_CHECKSUM9           _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM9
    #define F1CHKSH_CHECKSUM10          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM10
    #define F1CHKSH_CHECKSUM11          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM11
    #define F1CHKSH_CHECKSUM12          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM12
    #define F1CHKSH_CHECKSUM13          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM13
    #define F1CHKSH_CHECKSUM14          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM14
    #define F1CHKSH_CHECKSUM15          _F1CHKS.Overlap_STR.F1CHKSHSTR.Bits.CHECKSUM15
    
    #define F1CHKSH_CHECKSUM8_MASK      1U
    #define F1CHKSH_CHECKSUM9_MASK      2U
    #define F1CHKSH_CHECKSUM10_MASK     4U
    #define F1CHKSH_CHECKSUM11_MASK     8U
    #define F1CHKSH_CHECKSUM12_MASK     16U
    #define F1CHKSH_CHECKSUM13_MASK     32U
    #define F1CHKSH_CHECKSUM14_MASK     64U
    #define F1CHKSH_CHECKSUM15_MASK     128U
    

    /*** F1CHKSL - Flash Checksum Register Low Byte; 0x00000409 ***/
    union {
      byte Byte;
      struct {
        byte CHECKSUM0   :1;                                       /* Flash checksum bits, bit 0 */
        byte CHECKSUM1   :1;                                       /* Flash checksum bits, bit 1 */
        byte CHECKSUM2   :1;                                       /* Flash checksum bits, bit 2 */
        byte CHECKSUM3   :1;                                       /* Flash checksum bits, bit 3 */
        byte CHECKSUM4   :1;                                       /* Flash checksum bits, bit 4 */
        byte CHECKSUM5   :1;                                       /* Flash checksum bits, bit 5 */
        byte CHECKSUM6   :1;                                       /* Flash checksum bits, bit 6 */
        byte CHECKSUM7   :1;                                       /* Flash checksum bits, bit 7 */
      } Bits;
    } F1CHKSLSTR;
    #define F1CHKSL                     _F1CHKS.Overlap_STR.F1CHKSLSTR.Byte
    #define F1CHKSL_CHECKSUM0           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM0
    #define F1CHKSL_CHECKSUM1           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM1
    #define F1CHKSL_CHECKSUM2           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM2
    #define F1CHKSL_CHECKSUM3           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM3
    #define F1CHKSL_CHECKSUM4           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM4
    #define F1CHKSL_CHECKSUM5           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM5
    #define F1CHKSL_CHECKSUM6           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM6
    #define F1CHKSL_CHECKSUM7           _F1CHKS.Overlap_STR.F1CHKSLSTR.Bits.CHECKSUM7
    
    #define F1CHKSL_CHECKSUM0_MASK      1U
    #define F1CHKSL_CHECKSUM1_MASK      2U
    #define F1CHKSL_CHECKSUM2_MASK      4U
    #define F1CHKSL_CHECKSUM3_MASK      8U
    #define F1CHKSL_CHECKSUM4_MASK      16U
    #define F1CHKSL_CHECKSUM5_MASK      32U
    #define F1CHKSL_CHECKSUM6_MASK      64U
    #define F1CHKSL_CHECKSUM7_MASK      128U
    
  } Overlap_STR;

  struct {
    word CHECKSUM0   :1;                                       /* Flash checksum bits, bit 0 */
    word CHECKSUM1   :1;                                       /* Flash checksum bits, bit 1 */
    word CHECKSUM2   :1;                                       /* Flash checksum bits, bit 2 */
    word CHECKSUM3   :1;                                       /* Flash checksum bits, bit 3 */
    word CHECKSUM4   :1;                                       /* Flash checksum bits, bit 4 */
    word CHECKSUM5   :1;                                       /* Flash checksum bits, bit 5 */
    word CHECKSUM6   :1;                                       /* Flash checksum bits, bit 6 */
    word CHECKSUM7   :1;                                       /* Flash checksum bits, bit 7 */
    word CHECKSUM8   :1;                                       /* Flash checksum bits, bit 8 */
    word CHECKSUM9   :1;                                       /* Flash checksum bits, bit 9 */
    word CHECKSUM10  :1;                                       /* Flash checksum bits, bit 10 */
    word CHECKSUM11  :1;                                       /* Flash checksum bits, bit 11 */
    word CHECKSUM12  :1;                                       /* Flash checksum bits, bit 12 */
    word CHECKSUM13  :1;                                       /* Flash checksum bits, bit 13 */
    word CHECKSUM14  :1;                                       /* Flash checksum bits, bit 14 */
    word CHECKSUM15  :1;                                       /* Flash checksum bits, bit 15 */
  } Bits;
} F1CHKSSTR;
/* Tip for register initialization in the user code:  const word F1CHKS_INIT @0x00000408 = <F1CHKS_INITVAL>; */
#define _F1CHKS (*(const F1CHKSSTR *)0x00000408)
#define F1CHKS                          _F1CHKS.Word
#define F1CHKS_CHECKSUM0                _F1CHKS.Bits.CHECKSUM0
#define F1CHKS_CHECKSUM1                _F1CHKS.Bits.CHECKSUM1
#define F1CHKS_CHECKSUM2                _F1CHKS.Bits.CHECKSUM2
#define F1CHKS_CHECKSUM3                _F1CHKS.Bits.CHECKSUM3
#define F1CHKS_CHECKSUM4                _F1CHKS.Bits.CHECKSUM4
#define F1CHKS_CHECKSUM5                _F1CHKS.Bits.CHECKSUM5
#define F1CHKS_CHECKSUM6                _F1CHKS.Bits.CHECKSUM6
#define F1CHKS_CHECKSUM7                _F1CHKS.Bits.CHECKSUM7
#define F1CHKS_CHECKSUM8                _F1CHKS.Bits.CHECKSUM8
#define F1CHKS_CHECKSUM9                _F1CHKS.Bits.CHECKSUM9
#define F1CHKS_CHECKSUM10               _F1CHKS.Bits.CHECKSUM10
#define F1CHKS_CHECKSUM11               _F1CHKS.Bits.CHECKSUM11
#define F1CHKS_CHECKSUM12               _F1CHKS.Bits.CHECKSUM12
#define F1CHKS_CHECKSUM13               _F1CHKS.Bits.CHECKSUM13
#define F1CHKS_CHECKSUM14               _F1CHKS.Bits.CHECKSUM14
#define F1CHKS_CHECKSUM15               _F1CHKS.Bits.CHECKSUM15

#define F1CHKS_CHECKSUM0_MASK           1U
#define F1CHKS_CHECKSUM1_MASK           2U
#define F1CHKS_CHECKSUM2_MASK           4U
#define F1CHKS_CHECKSUM3_MASK           8U
#define F1CHKS_CHECKSUM4_MASK           16U
#define F1CHKS_CHECKSUM5_MASK           32U
#define F1CHKS_CHECKSUM6_MASK           64U
#define F1CHKS_CHECKSUM7_MASK           128U
#define F1CHKS_CHECKSUM8_MASK           256U
#define F1CHKS_CHECKSUM9_MASK           512U
#define F1CHKS_CHECKSUM10_MASK          1024U
#define F1CHKS_CHECKSUM11_MASK          2048U
#define F1CHKS_CHECKSUM12_MASK          4096U
#define F1CHKS_CHECKSUM13_MASK          8192U
#define F1CHKS_CHECKSUM14_MASK          16384U
#define F1CHKS_CHECKSUM15_MASK          32768U


/*** CHKSBYP1 - Checksum Bypass Register; 0x0000040A ***/
typedef union {
  byte Byte;
} CHKSBYP1STR;
/* Tip for register initialization in the user code:  const byte CHKSBYP1_INIT @0x0000040A = <CHKSBYP1_INITVAL>; */
#define _CHKSBYP1 (*(const CHKSBYP1STR *)0x0000040A)
#define CHKSBYP1                        _CHKSBYP1.Byte


/*** Partial_Erase_Semaphore1 - Flash partial erase semaphore; 0x0000040B ***/
typedef union {
  byte Byte;
} Partial_Erase_Semaphore1STR;
/* Tip for register initialization in the user code:  const byte Partial_Erase_Semaphore1_INIT @0x0000040B = <Partial_Erase_Semaphore1_INITVAL>; */
#define _Partial_Erase_Semaphore1 (*(const Partial_Erase_Semaphore1STR *)0x0000040B)
#define Partial_Erase_Semaphore1        _Partial_Erase_Semaphore1.Byte


/*** NV1PROT - Nonvolatile Flash Protection Register; 0x0000040D ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} NV1PROTSTR;
/* Tip for register initialization in the user code:  const byte NV1PROT_INIT @0x0000040D = <NV1PROT_INITVAL>; */
#define _NV1PROT (*(const NV1PROTSTR *)0x0000040D)
#define NV1PROT                         _NV1PROT.Byte
#define NV1PROT_FPOPEN                  _NV1PROT.Bits.FPOPEN
#define NV1PROT_FPS0                    _NV1PROT.Bits.FPS0
#define NV1PROT_FPS1                    _NV1PROT.Bits.FPS1
#define NV1PROT_FPS2                    _NV1PROT.Bits.FPS2
#define NV1PROT_FPS3                    _NV1PROT.Bits.FPS3
#define NV1PROT_FPS4                    _NV1PROT.Bits.FPS4
#define NV1PROT_FPS5                    _NV1PROT.Bits.FPS5
#define NV1PROT_FPS6                    _NV1PROT.Bits.FPS6
#define NV1PROT_FPS                     _NV1PROT.MergedBits.grpFPS

#define NV1PROT_FPOPEN_MASK             1U
#define NV1PROT_FPS0_MASK               2U
#define NV1PROT_FPS1_MASK               4U
#define NV1PROT_FPS2_MASK               8U
#define NV1PROT_FPS3_MASK               16U
#define NV1PROT_FPS4_MASK               32U
#define NV1PROT_FPS5_MASK               64U
#define NV1PROT_FPS6_MASK               128U
#define NV1PROT_FPS_MASK                254U
#define NV1PROT_FPS_BITNUM              1U


/*** NV1OPT - Nonvolatile Flash Options Register; 0x0000040F ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} NV1OPTSTR;
/* Tip for register initialization in the user code:  const byte NV1OPT_INIT @0x0000040F = <NV1OPT_INITVAL>; */
#define _NV1OPT (*(const NV1OPTSTR *)0x0000040F)
#define NV1OPT                          _NV1OPT.Byte
#define NV1OPT_SEC0                     _NV1OPT.Bits.SEC0
#define NV1OPT_SEC1                     _NV1OPT.Bits.SEC1
#define NV1OPT_KEYEN0                   _NV1OPT.Bits.KEYEN0
#define NV1OPT_KEYEN1                   _NV1OPT.Bits.KEYEN1
#define NV1OPT_SEC                      _NV1OPT.MergedBits.grpSEC
#define NV1OPT_KEYEN                    _NV1OPT.MergedBits.grpKEYEN

#define NV1OPT_SEC0_MASK                1U
#define NV1OPT_SEC1_MASK                2U
#define NV1OPT_KEYEN0_MASK              64U
#define NV1OPT_KEYEN1_MASK              128U
#define NV1OPT_SEC_MASK                 3U
#define NV1OPT_SEC_BITNUM               0U
#define NV1OPT_KEYEN_MASK               192U
#define NV1OPT_KEYEN_BITNUM             6U


/*** FLASHAS - Flash Array Select Register; 0x00000410 ***/
typedef union {
  byte Byte;
  struct {
    byte ARRAYSEL0   :1;                                       /* Flash array select bit */
    byte ARRAYSEL1   :1;                                       /* Flash array select protection bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpARRAYSEL :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} FLASHASSTR;
/* Tip for register initialization in the user code:  const byte FLASHAS_INIT @0x00000410 = <FLASHAS_INITVAL>; */
#define _FLASHAS (*(const FLASHASSTR *)0x00000410)
#define FLASHAS                         _FLASHAS.Byte
#define FLASHAS_ARRAYSEL0               _FLASHAS.Bits.ARRAYSEL0
#define FLASHAS_ARRAYSEL1               _FLASHAS.Bits.ARRAYSEL1
#define FLASHAS_ARRAYSEL                _FLASHAS.MergedBits.grpARRAYSEL

#define FLASHAS_ARRAYSEL0_MASK          1U
#define FLASHAS_ARRAYSEL1_MASK          2U
#define FLASHAS_ARRAYSEL_MASK           3U
#define FLASHAS_ARRAYSEL_BITNUM         0U


/*** NV2FTRIM - Nonvolatile MCG Fine Trim; 0x000203FE ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* MCG Fine Trim */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} NV2FTRIMSTR;
/* Tip for register initialization in the user code:  const byte NV2FTRIM_INIT @0x000203FE = <NV2FTRIM_INITVAL>; */
#define _NV2FTRIM (*(const NV2FTRIMSTR *)0x000203FE)
#define NV2FTRIM                        _NV2FTRIM.Byte
#define NV2FTRIM_FTRIM                  _NV2FTRIM.Bits.FTRIM

#define NV2FTRIM_FTRIM_MASK             1U


/*** NV2MCGTRM - Nonvolatile MCG Trim Register; 0x000203FF ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* MCG Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* MCG Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* MCG Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* MCG Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* MCG Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* MCG Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* MCG Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* MCG Trim Setting, bit 7 */
  } Bits;
} NV2MCGTRMSTR;
/* Tip for register initialization in the user code:  const byte NV2MCGTRM_INIT @0x000203FF = <NV2MCGTRM_INITVAL>; */
#define _NV2MCGTRM (*(const NV2MCGTRMSTR *)0x000203FF)
#define NV2MCGTRM                       _NV2MCGTRM.Byte
#define NV2MCGTRM_TRIM0                 _NV2MCGTRM.Bits.TRIM0
#define NV2MCGTRM_TRIM1                 _NV2MCGTRM.Bits.TRIM1
#define NV2MCGTRM_TRIM2                 _NV2MCGTRM.Bits.TRIM2
#define NV2MCGTRM_TRIM3                 _NV2MCGTRM.Bits.TRIM3
#define NV2MCGTRM_TRIM4                 _NV2MCGTRM.Bits.TRIM4
#define NV2MCGTRM_TRIM5                 _NV2MCGTRM.Bits.TRIM5
#define NV2MCGTRM_TRIM6                 _NV2MCGTRM.Bits.TRIM6
#define NV2MCGTRM_TRIM7                 _NV2MCGTRM.Bits.TRIM7

#define NV2MCGTRM_TRIM0_MASK            1U
#define NV2MCGTRM_TRIM1_MASK            2U
#define NV2MCGTRM_TRIM2_MASK            4U
#define NV2MCGTRM_TRIM3_MASK            8U
#define NV2MCGTRM_TRIM4_MASK            16U
#define NV2MCGTRM_TRIM5_MASK            32U
#define NV2MCGTRM_TRIM6_MASK            64U
#define NV2MCGTRM_TRIM7_MASK            128U


/*** NV2BACKKEY0 - Backdoor Comparison Key 0; 0x00020400 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 7 */
  } Bits;
} NV2BACKKEY0STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY0_INIT @0x00020400 = <NV2BACKKEY0_INITVAL>; */
#define _NV2BACKKEY0 (*(const NV2BACKKEY0STR *)0x00020400)
#define NV2BACKKEY0                     _NV2BACKKEY0.Byte
#define NV2BACKKEY0_KEY0                _NV2BACKKEY0.Bits.KEY0
#define NV2BACKKEY0_KEY1                _NV2BACKKEY0.Bits.KEY1
#define NV2BACKKEY0_KEY2                _NV2BACKKEY0.Bits.KEY2
#define NV2BACKKEY0_KEY3                _NV2BACKKEY0.Bits.KEY3
#define NV2BACKKEY0_KEY4                _NV2BACKKEY0.Bits.KEY4
#define NV2BACKKEY0_KEY5                _NV2BACKKEY0.Bits.KEY5
#define NV2BACKKEY0_KEY6                _NV2BACKKEY0.Bits.KEY6
#define NV2BACKKEY0_KEY7                _NV2BACKKEY0.Bits.KEY7
/* NV2BACKKEY_ARR: Access 8 NV2BACKKEYx registers in an array */
#define NV2BACKKEY_ARR                  ((volatile byte *) &NV2BACKKEY0)

#define NV2BACKKEY0_KEY0_MASK           1U
#define NV2BACKKEY0_KEY1_MASK           2U
#define NV2BACKKEY0_KEY2_MASK           4U
#define NV2BACKKEY0_KEY3_MASK           8U
#define NV2BACKKEY0_KEY4_MASK           16U
#define NV2BACKKEY0_KEY5_MASK           32U
#define NV2BACKKEY0_KEY6_MASK           64U
#define NV2BACKKEY0_KEY7_MASK           128U


/*** NV2BACKKEY1 - Backdoor Comparison Key 1; 0x00020401 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 7 */
  } Bits;
} NV2BACKKEY1STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY1_INIT @0x00020401 = <NV2BACKKEY1_INITVAL>; */
#define _NV2BACKKEY1 (*(const NV2BACKKEY1STR *)0x00020401)
#define NV2BACKKEY1                     _NV2BACKKEY1.Byte
#define NV2BACKKEY1_KEY0                _NV2BACKKEY1.Bits.KEY0
#define NV2BACKKEY1_KEY1                _NV2BACKKEY1.Bits.KEY1
#define NV2BACKKEY1_KEY2                _NV2BACKKEY1.Bits.KEY2
#define NV2BACKKEY1_KEY3                _NV2BACKKEY1.Bits.KEY3
#define NV2BACKKEY1_KEY4                _NV2BACKKEY1.Bits.KEY4
#define NV2BACKKEY1_KEY5                _NV2BACKKEY1.Bits.KEY5
#define NV2BACKKEY1_KEY6                _NV2BACKKEY1.Bits.KEY6
#define NV2BACKKEY1_KEY7                _NV2BACKKEY1.Bits.KEY7

#define NV2BACKKEY1_KEY0_MASK           1U
#define NV2BACKKEY1_KEY1_MASK           2U
#define NV2BACKKEY1_KEY2_MASK           4U
#define NV2BACKKEY1_KEY3_MASK           8U
#define NV2BACKKEY1_KEY4_MASK           16U
#define NV2BACKKEY1_KEY5_MASK           32U
#define NV2BACKKEY1_KEY6_MASK           64U
#define NV2BACKKEY1_KEY7_MASK           128U


/*** NV2BACKKEY2 - Backdoor Comparison Key 2; 0x00020402 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 7 */
  } Bits;
} NV2BACKKEY2STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY2_INIT @0x00020402 = <NV2BACKKEY2_INITVAL>; */
#define _NV2BACKKEY2 (*(const NV2BACKKEY2STR *)0x00020402)
#define NV2BACKKEY2                     _NV2BACKKEY2.Byte
#define NV2BACKKEY2_KEY0                _NV2BACKKEY2.Bits.KEY0
#define NV2BACKKEY2_KEY1                _NV2BACKKEY2.Bits.KEY1
#define NV2BACKKEY2_KEY2                _NV2BACKKEY2.Bits.KEY2
#define NV2BACKKEY2_KEY3                _NV2BACKKEY2.Bits.KEY3
#define NV2BACKKEY2_KEY4                _NV2BACKKEY2.Bits.KEY4
#define NV2BACKKEY2_KEY5                _NV2BACKKEY2.Bits.KEY5
#define NV2BACKKEY2_KEY6                _NV2BACKKEY2.Bits.KEY6
#define NV2BACKKEY2_KEY7                _NV2BACKKEY2.Bits.KEY7

#define NV2BACKKEY2_KEY0_MASK           1U
#define NV2BACKKEY2_KEY1_MASK           2U
#define NV2BACKKEY2_KEY2_MASK           4U
#define NV2BACKKEY2_KEY3_MASK           8U
#define NV2BACKKEY2_KEY4_MASK           16U
#define NV2BACKKEY2_KEY5_MASK           32U
#define NV2BACKKEY2_KEY6_MASK           64U
#define NV2BACKKEY2_KEY7_MASK           128U


/*** NV2BACKKEY3 - Backdoor Comparison Key 3; 0x00020403 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 7 */
  } Bits;
} NV2BACKKEY3STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY3_INIT @0x00020403 = <NV2BACKKEY3_INITVAL>; */
#define _NV2BACKKEY3 (*(const NV2BACKKEY3STR *)0x00020403)
#define NV2BACKKEY3                     _NV2BACKKEY3.Byte
#define NV2BACKKEY3_KEY0                _NV2BACKKEY3.Bits.KEY0
#define NV2BACKKEY3_KEY1                _NV2BACKKEY3.Bits.KEY1
#define NV2BACKKEY3_KEY2                _NV2BACKKEY3.Bits.KEY2
#define NV2BACKKEY3_KEY3                _NV2BACKKEY3.Bits.KEY3
#define NV2BACKKEY3_KEY4                _NV2BACKKEY3.Bits.KEY4
#define NV2BACKKEY3_KEY5                _NV2BACKKEY3.Bits.KEY5
#define NV2BACKKEY3_KEY6                _NV2BACKKEY3.Bits.KEY6
#define NV2BACKKEY3_KEY7                _NV2BACKKEY3.Bits.KEY7

#define NV2BACKKEY3_KEY0_MASK           1U
#define NV2BACKKEY3_KEY1_MASK           2U
#define NV2BACKKEY3_KEY2_MASK           4U
#define NV2BACKKEY3_KEY3_MASK           8U
#define NV2BACKKEY3_KEY4_MASK           16U
#define NV2BACKKEY3_KEY5_MASK           32U
#define NV2BACKKEY3_KEY6_MASK           64U
#define NV2BACKKEY3_KEY7_MASK           128U


/*** NV2BACKKEY4 - Backdoor Comparison Key 4; 0x00020404 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 7 */
  } Bits;
} NV2BACKKEY4STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY4_INIT @0x00020404 = <NV2BACKKEY4_INITVAL>; */
#define _NV2BACKKEY4 (*(const NV2BACKKEY4STR *)0x00020404)
#define NV2BACKKEY4                     _NV2BACKKEY4.Byte
#define NV2BACKKEY4_KEY0                _NV2BACKKEY4.Bits.KEY0
#define NV2BACKKEY4_KEY1                _NV2BACKKEY4.Bits.KEY1
#define NV2BACKKEY4_KEY2                _NV2BACKKEY4.Bits.KEY2
#define NV2BACKKEY4_KEY3                _NV2BACKKEY4.Bits.KEY3
#define NV2BACKKEY4_KEY4                _NV2BACKKEY4.Bits.KEY4
#define NV2BACKKEY4_KEY5                _NV2BACKKEY4.Bits.KEY5
#define NV2BACKKEY4_KEY6                _NV2BACKKEY4.Bits.KEY6
#define NV2BACKKEY4_KEY7                _NV2BACKKEY4.Bits.KEY7

#define NV2BACKKEY4_KEY0_MASK           1U
#define NV2BACKKEY4_KEY1_MASK           2U
#define NV2BACKKEY4_KEY2_MASK           4U
#define NV2BACKKEY4_KEY3_MASK           8U
#define NV2BACKKEY4_KEY4_MASK           16U
#define NV2BACKKEY4_KEY5_MASK           32U
#define NV2BACKKEY4_KEY6_MASK           64U
#define NV2BACKKEY4_KEY7_MASK           128U


/*** NV2BACKKEY5 - Backdoor Comparison Key 5; 0x00020405 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 7 */
  } Bits;
} NV2BACKKEY5STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY5_INIT @0x00020405 = <NV2BACKKEY5_INITVAL>; */
#define _NV2BACKKEY5 (*(const NV2BACKKEY5STR *)0x00020405)
#define NV2BACKKEY5                     _NV2BACKKEY5.Byte
#define NV2BACKKEY5_KEY0                _NV2BACKKEY5.Bits.KEY0
#define NV2BACKKEY5_KEY1                _NV2BACKKEY5.Bits.KEY1
#define NV2BACKKEY5_KEY2                _NV2BACKKEY5.Bits.KEY2
#define NV2BACKKEY5_KEY3                _NV2BACKKEY5.Bits.KEY3
#define NV2BACKKEY5_KEY4                _NV2BACKKEY5.Bits.KEY4
#define NV2BACKKEY5_KEY5                _NV2BACKKEY5.Bits.KEY5
#define NV2BACKKEY5_KEY6                _NV2BACKKEY5.Bits.KEY6
#define NV2BACKKEY5_KEY7                _NV2BACKKEY5.Bits.KEY7

#define NV2BACKKEY5_KEY0_MASK           1U
#define NV2BACKKEY5_KEY1_MASK           2U
#define NV2BACKKEY5_KEY2_MASK           4U
#define NV2BACKKEY5_KEY3_MASK           8U
#define NV2BACKKEY5_KEY4_MASK           16U
#define NV2BACKKEY5_KEY5_MASK           32U
#define NV2BACKKEY5_KEY6_MASK           64U
#define NV2BACKKEY5_KEY7_MASK           128U


/*** NV2BACKKEY6 - Backdoor Comparison Key 6; 0x00020406 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 7 */
  } Bits;
} NV2BACKKEY6STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY6_INIT @0x00020406 = <NV2BACKKEY6_INITVAL>; */
#define _NV2BACKKEY6 (*(const NV2BACKKEY6STR *)0x00020406)
#define NV2BACKKEY6                     _NV2BACKKEY6.Byte
#define NV2BACKKEY6_KEY0                _NV2BACKKEY6.Bits.KEY0
#define NV2BACKKEY6_KEY1                _NV2BACKKEY6.Bits.KEY1
#define NV2BACKKEY6_KEY2                _NV2BACKKEY6.Bits.KEY2
#define NV2BACKKEY6_KEY3                _NV2BACKKEY6.Bits.KEY3
#define NV2BACKKEY6_KEY4                _NV2BACKKEY6.Bits.KEY4
#define NV2BACKKEY6_KEY5                _NV2BACKKEY6.Bits.KEY5
#define NV2BACKKEY6_KEY6                _NV2BACKKEY6.Bits.KEY6
#define NV2BACKKEY6_KEY7                _NV2BACKKEY6.Bits.KEY7

#define NV2BACKKEY6_KEY0_MASK           1U
#define NV2BACKKEY6_KEY1_MASK           2U
#define NV2BACKKEY6_KEY2_MASK           4U
#define NV2BACKKEY6_KEY3_MASK           8U
#define NV2BACKKEY6_KEY4_MASK           16U
#define NV2BACKKEY6_KEY5_MASK           32U
#define NV2BACKKEY6_KEY6_MASK           64U
#define NV2BACKKEY6_KEY7_MASK           128U


/*** NV2BACKKEY7 - Backdoor Comparison Key 7; 0x00020407 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 7 */
  } Bits;
} NV2BACKKEY7STR;
/* Tip for register initialization in the user code:  const byte NV2BACKKEY7_INIT @0x00020407 = <NV2BACKKEY7_INITVAL>; */
#define _NV2BACKKEY7 (*(const NV2BACKKEY7STR *)0x00020407)
#define NV2BACKKEY7                     _NV2BACKKEY7.Byte
#define NV2BACKKEY7_KEY0                _NV2BACKKEY7.Bits.KEY0
#define NV2BACKKEY7_KEY1                _NV2BACKKEY7.Bits.KEY1
#define NV2BACKKEY7_KEY2                _NV2BACKKEY7.Bits.KEY2
#define NV2BACKKEY7_KEY3                _NV2BACKKEY7.Bits.KEY3
#define NV2BACKKEY7_KEY4                _NV2BACKKEY7.Bits.KEY4
#define NV2BACKKEY7_KEY5                _NV2BACKKEY7.Bits.KEY5
#define NV2BACKKEY7_KEY6                _NV2BACKKEY7.Bits.KEY6
#define NV2BACKKEY7_KEY7                _NV2BACKKEY7.Bits.KEY7

#define NV2BACKKEY7_KEY0_MASK           1U
#define NV2BACKKEY7_KEY1_MASK           2U
#define NV2BACKKEY7_KEY2_MASK           4U
#define NV2BACKKEY7_KEY3_MASK           8U
#define NV2BACKKEY7_KEY4_MASK           16U
#define NV2BACKKEY7_KEY5_MASK           32U
#define NV2BACKKEY7_KEY6_MASK           64U
#define NV2BACKKEY7_KEY7_MASK           128U


/*** F2CHKS - Flash Checksum Register; 0x00020408 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** F2CHKSH - Flash Checksum Register High Byte; 0x00020408 ***/
    union {
      byte Byte;
      struct {
        byte CHECKSUM8   :1;                                       /* Flash checksum bit 8 */
        byte CHECKSUM9   :1;                                       /* Flash checksum bit 9 */
        byte CHECKSUM10  :1;                                       /* Flash checksum bit 10 */
        byte CHECKSUM11  :1;                                       /* Flash checksum bit 11 */
        byte CHECKSUM12  :1;                                       /* Flash checksum bit 12 */
        byte CHECKSUM13  :1;                                       /* Flash checksum bit 13 */
        byte CHECKSUM14  :1;                                       /* Flash checksum bit 14 */
        byte CHECKSUM15  :1;                                       /* Flash checksum bit 15 */
      } Bits;
    } F2CHKSHSTR;
    #define F2CHKSH                     _F2CHKS.Overlap_STR.F2CHKSHSTR.Byte
    #define F2CHKSH_CHECKSUM8           _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM8
    #define F2CHKSH_CHECKSUM9           _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM9
    #define F2CHKSH_CHECKSUM10          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM10
    #define F2CHKSH_CHECKSUM11          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM11
    #define F2CHKSH_CHECKSUM12          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM12
    #define F2CHKSH_CHECKSUM13          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM13
    #define F2CHKSH_CHECKSUM14          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM14
    #define F2CHKSH_CHECKSUM15          _F2CHKS.Overlap_STR.F2CHKSHSTR.Bits.CHECKSUM15
    
    #define F2CHKSH_CHECKSUM8_MASK      1U
    #define F2CHKSH_CHECKSUM9_MASK      2U
    #define F2CHKSH_CHECKSUM10_MASK     4U
    #define F2CHKSH_CHECKSUM11_MASK     8U
    #define F2CHKSH_CHECKSUM12_MASK     16U
    #define F2CHKSH_CHECKSUM13_MASK     32U
    #define F2CHKSH_CHECKSUM14_MASK     64U
    #define F2CHKSH_CHECKSUM15_MASK     128U
    

    /*** F2CHKSL - Flash Checksum Register Low Byte; 0x00020409 ***/
    union {
      byte Byte;
      struct {
        byte CHECKSUM0   :1;                                       /* Flash checksum bits, bit 0 */
        byte CHECKSUM1   :1;                                       /* Flash checksum bits, bit 1 */
        byte CHECKSUM2   :1;                                       /* Flash checksum bits, bit 2 */
        byte CHECKSUM3   :1;                                       /* Flash checksum bits, bit 3 */
        byte CHECKSUM4   :1;                                       /* Flash checksum bits, bit 4 */
        byte CHECKSUM5   :1;                                       /* Flash checksum bits, bit 5 */
        byte CHECKSUM6   :1;                                       /* Flash checksum bits, bit 6 */
        byte CHECKSUM7   :1;                                       /* Flash checksum bits, bit 7 */
      } Bits;
    } F2CHKSLSTR;
    #define F2CHKSL                     _F2CHKS.Overlap_STR.F2CHKSLSTR.Byte
    #define F2CHKSL_CHECKSUM0           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM0
    #define F2CHKSL_CHECKSUM1           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM1
    #define F2CHKSL_CHECKSUM2           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM2
    #define F2CHKSL_CHECKSUM3           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM3
    #define F2CHKSL_CHECKSUM4           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM4
    #define F2CHKSL_CHECKSUM5           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM5
    #define F2CHKSL_CHECKSUM6           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM6
    #define F2CHKSL_CHECKSUM7           _F2CHKS.Overlap_STR.F2CHKSLSTR.Bits.CHECKSUM7
    
    #define F2CHKSL_CHECKSUM0_MASK      1U
    #define F2CHKSL_CHECKSUM1_MASK      2U
    #define F2CHKSL_CHECKSUM2_MASK      4U
    #define F2CHKSL_CHECKSUM3_MASK      8U
    #define F2CHKSL_CHECKSUM4_MASK      16U
    #define F2CHKSL_CHECKSUM5_MASK      32U
    #define F2CHKSL_CHECKSUM6_MASK      64U
    #define F2CHKSL_CHECKSUM7_MASK      128U
    
  } Overlap_STR;

  struct {
    word CHECKSUM0   :1;                                       /* Flash checksum bits, bit 0 */
    word CHECKSUM1   :1;                                       /* Flash checksum bits, bit 1 */
    word CHECKSUM2   :1;                                       /* Flash checksum bits, bit 2 */
    word CHECKSUM3   :1;                                       /* Flash checksum bits, bit 3 */
    word CHECKSUM4   :1;                                       /* Flash checksum bits, bit 4 */
    word CHECKSUM5   :1;                                       /* Flash checksum bits, bit 5 */
    word CHECKSUM6   :1;                                       /* Flash checksum bits, bit 6 */
    word CHECKSUM7   :1;                                       /* Flash checksum bits, bit 7 */
    word CHECKSUM8   :1;                                       /* Flash checksum bits, bit 8 */
    word CHECKSUM9   :1;                                       /* Flash checksum bits, bit 9 */
    word CHECKSUM10  :1;                                       /* Flash checksum bits, bit 10 */
    word CHECKSUM11  :1;                                       /* Flash checksum bits, bit 11 */
    word CHECKSUM12  :1;                                       /* Flash checksum bits, bit 12 */
    word CHECKSUM13  :1;                                       /* Flash checksum bits, bit 13 */
    word CHECKSUM14  :1;                                       /* Flash checksum bits, bit 14 */
    word CHECKSUM15  :1;                                       /* Flash checksum bits, bit 15 */
  } Bits;
} F2CHKSSTR;
/* Tip for register initialization in the user code:  const word F2CHKS_INIT @0x00020408 = <F2CHKS_INITVAL>; */
#define _F2CHKS (*(const F2CHKSSTR *)0x00020408)
#define F2CHKS                          _F2CHKS.Word
#define F2CHKS_CHECKSUM0                _F2CHKS.Bits.CHECKSUM0
#define F2CHKS_CHECKSUM1                _F2CHKS.Bits.CHECKSUM1
#define F2CHKS_CHECKSUM2                _F2CHKS.Bits.CHECKSUM2
#define F2CHKS_CHECKSUM3                _F2CHKS.Bits.CHECKSUM3
#define F2CHKS_CHECKSUM4                _F2CHKS.Bits.CHECKSUM4
#define F2CHKS_CHECKSUM5                _F2CHKS.Bits.CHECKSUM5
#define F2CHKS_CHECKSUM6                _F2CHKS.Bits.CHECKSUM6
#define F2CHKS_CHECKSUM7                _F2CHKS.Bits.CHECKSUM7
#define F2CHKS_CHECKSUM8                _F2CHKS.Bits.CHECKSUM8
#define F2CHKS_CHECKSUM9                _F2CHKS.Bits.CHECKSUM9
#define F2CHKS_CHECKSUM10               _F2CHKS.Bits.CHECKSUM10
#define F2CHKS_CHECKSUM11               _F2CHKS.Bits.CHECKSUM11
#define F2CHKS_CHECKSUM12               _F2CHKS.Bits.CHECKSUM12
#define F2CHKS_CHECKSUM13               _F2CHKS.Bits.CHECKSUM13
#define F2CHKS_CHECKSUM14               _F2CHKS.Bits.CHECKSUM14
#define F2CHKS_CHECKSUM15               _F2CHKS.Bits.CHECKSUM15

#define F2CHKS_CHECKSUM0_MASK           1U
#define F2CHKS_CHECKSUM1_MASK           2U
#define F2CHKS_CHECKSUM2_MASK           4U
#define F2CHKS_CHECKSUM3_MASK           8U
#define F2CHKS_CHECKSUM4_MASK           16U
#define F2CHKS_CHECKSUM5_MASK           32U
#define F2CHKS_CHECKSUM6_MASK           64U
#define F2CHKS_CHECKSUM7_MASK           128U
#define F2CHKS_CHECKSUM8_MASK           256U
#define F2CHKS_CHECKSUM9_MASK           512U
#define F2CHKS_CHECKSUM10_MASK          1024U
#define F2CHKS_CHECKSUM11_MASK          2048U
#define F2CHKS_CHECKSUM12_MASK          4096U
#define F2CHKS_CHECKSUM13_MASK          8192U
#define F2CHKS_CHECKSUM14_MASK          16384U
#define F2CHKS_CHECKSUM15_MASK          32768U


/*** CHKSBYP2 - Checksum Bypass Register; 0x0002040A ***/
typedef union {
  byte Byte;
} CHKSBYP2STR;
/* Tip for register initialization in the user code:  const byte CHKSBYP2_INIT @0x0002040A = <CHKSBYP2_INITVAL>; */
#define _CHKSBYP2 (*(const CHKSBYP2STR *)0x0002040A)
#define CHKSBYP2                        _CHKSBYP2.Byte


/*** Partial_Erase_Semaphore2 - Flash partial erase semaphore; 0x0002040B ***/
typedef union {
  byte Byte;
} Partial_Erase_Semaphore2STR;
/* Tip for register initialization in the user code:  const byte Partial_Erase_Semaphore2_INIT @0x0002040B = <Partial_Erase_Semaphore2_INITVAL>; */
#define _Partial_Erase_Semaphore2 (*(const Partial_Erase_Semaphore2STR *)0x0002040B)
#define Partial_Erase_Semaphore2        _Partial_Erase_Semaphore2.Byte


/*** NV2PROT - Nonvolatile Flash Protection Register; 0x0002040D ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} NV2PROTSTR;
/* Tip for register initialization in the user code:  const byte NV2PROT_INIT @0x0002040D = <NV2PROT_INITVAL>; */
#define _NV2PROT (*(const NV2PROTSTR *)0x0002040D)
#define NV2PROT                         _NV2PROT.Byte
#define NV2PROT_FPOPEN                  _NV2PROT.Bits.FPOPEN
#define NV2PROT_FPS0                    _NV2PROT.Bits.FPS0
#define NV2PROT_FPS1                    _NV2PROT.Bits.FPS1
#define NV2PROT_FPS2                    _NV2PROT.Bits.FPS2
#define NV2PROT_FPS3                    _NV2PROT.Bits.FPS3
#define NV2PROT_FPS4                    _NV2PROT.Bits.FPS4
#define NV2PROT_FPS5                    _NV2PROT.Bits.FPS5
#define NV2PROT_FPS6                    _NV2PROT.Bits.FPS6
#define NV2PROT_FPS                     _NV2PROT.MergedBits.grpFPS

#define NV2PROT_FPOPEN_MASK             1U
#define NV2PROT_FPS0_MASK               2U
#define NV2PROT_FPS1_MASK               4U
#define NV2PROT_FPS2_MASK               8U
#define NV2PROT_FPS3_MASK               16U
#define NV2PROT_FPS4_MASK               32U
#define NV2PROT_FPS5_MASK               64U
#define NV2PROT_FPS6_MASK               128U
#define NV2PROT_FPS_MASK                254U
#define NV2PROT_FPS_BITNUM              1U


/*** NV2OPT - Nonvolatile Flash Options Register; 0x0002040F ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} NV2OPTSTR;
/* Tip for register initialization in the user code:  const byte NV2OPT_INIT @0x0002040F = <NV2OPT_INITVAL>; */
#define _NV2OPT (*(const NV2OPTSTR *)0x0002040F)
#define NV2OPT                          _NV2OPT.Byte
#define NV2OPT_SEC0                     _NV2OPT.Bits.SEC0
#define NV2OPT_SEC1                     _NV2OPT.Bits.SEC1
#define NV2OPT_KEYEN0                   _NV2OPT.Bits.KEYEN0
#define NV2OPT_KEYEN1                   _NV2OPT.Bits.KEYEN1
#define NV2OPT_SEC                      _NV2OPT.MergedBits.grpSEC
#define NV2OPT_KEYEN                    _NV2OPT.MergedBits.grpKEYEN

#define NV2OPT_SEC0_MASK                1U
#define NV2OPT_SEC1_MASK                2U
#define NV2OPT_KEYEN0_MASK              64U
#define NV2OPT_KEYEN1_MASK              128U
#define NV2OPT_SEC_MASK                 3U
#define NV2OPT_SEC_BITNUM               0U
#define NV2OPT_KEYEN_MASK               192U
#define NV2OPT_KEYEN_BITNUM             6U


/*** RGPIO_DIR - RGPIO Data Direction Register; 0x00C00000 ***/
typedef union {
  word Word;
  struct {
    word DIR0        :1;                                       /* RGPIO data direction bit 0 */
    word DIR1        :1;                                       /* RGPIO data direction bit 1 */
    word DIR2        :1;                                       /* RGPIO data direction bit 2 */
    word DIR3        :1;                                       /* RGPIO data direction bit 3 */
    word DIR4        :1;                                       /* RGPIO data direction bit 4 */
    word DIR5        :1;                                       /* RGPIO data direction bit 5 */
    word DIR6        :1;                                       /* RGPIO data direction bit 6 */
    word DIR7        :1;                                       /* RGPIO data direction bit 7 */
    word DIR8        :1;                                       /* RGPIO data direction bit 8 */
    word DIR9        :1;                                       /* RGPIO data direction bit 9 */
    word DIR10       :1;                                       /* RGPIO data direction bit 10 */
    word DIR11       :1;                                       /* RGPIO data direction bit 11 */
    word DIR12       :1;                                       /* RGPIO data direction bit 12 */
    word DIR13       :1;                                       /* RGPIO data direction bit 13 */
    word DIR14       :1;                                       /* RGPIO data direction bit 14 */
    word DIR15       :1;                                       /* RGPIO data direction bit 15 */
  } Bits;
} RGPIO_DIRSTR;
extern volatile RGPIO_DIRSTR _RGPIO_DIR @0x00C00000;
#define RGPIO_DIR                       _RGPIO_DIR.Word
#define RGPIO_DIR_DIR0                  _RGPIO_DIR.Bits.DIR0
#define RGPIO_DIR_DIR1                  _RGPIO_DIR.Bits.DIR1
#define RGPIO_DIR_DIR2                  _RGPIO_DIR.Bits.DIR2
#define RGPIO_DIR_DIR3                  _RGPIO_DIR.Bits.DIR3
#define RGPIO_DIR_DIR4                  _RGPIO_DIR.Bits.DIR4
#define RGPIO_DIR_DIR5                  _RGPIO_DIR.Bits.DIR5
#define RGPIO_DIR_DIR6                  _RGPIO_DIR.Bits.DIR6
#define RGPIO_DIR_DIR7                  _RGPIO_DIR.Bits.DIR7
#define RGPIO_DIR_DIR8                  _RGPIO_DIR.Bits.DIR8
#define RGPIO_DIR_DIR9                  _RGPIO_DIR.Bits.DIR9
#define RGPIO_DIR_DIR10                 _RGPIO_DIR.Bits.DIR10
#define RGPIO_DIR_DIR11                 _RGPIO_DIR.Bits.DIR11
#define RGPIO_DIR_DIR12                 _RGPIO_DIR.Bits.DIR12
#define RGPIO_DIR_DIR13                 _RGPIO_DIR.Bits.DIR13
#define RGPIO_DIR_DIR14                 _RGPIO_DIR.Bits.DIR14
#define RGPIO_DIR_DIR15                 _RGPIO_DIR.Bits.DIR15

#define RGPIO_DIR_DIR0_MASK             1U
#define RGPIO_DIR_DIR1_MASK             2U
#define RGPIO_DIR_DIR2_MASK             4U
#define RGPIO_DIR_DIR3_MASK             8U
#define RGPIO_DIR_DIR4_MASK             16U
#define RGPIO_DIR_DIR5_MASK             32U
#define RGPIO_DIR_DIR6_MASK             64U
#define RGPIO_DIR_DIR7_MASK             128U
#define RGPIO_DIR_DIR8_MASK             256U
#define RGPIO_DIR_DIR9_MASK             512U
#define RGPIO_DIR_DIR10_MASK            1024U
#define RGPIO_DIR_DIR11_MASK            2048U
#define RGPIO_DIR_DIR12_MASK            4096U
#define RGPIO_DIR_DIR13_MASK            8192U
#define RGPIO_DIR_DIR14_MASK            16384U
#define RGPIO_DIR_DIR15_MASK            32768U


/*** RGPIO_DATA - RGPIO Data Register; 0x00C00002 ***/
typedef union {
  word Word;
  struct {
    word DATA0       :1;                                       /* RGPIO data bit 0 */
    word DATA1       :1;                                       /* RGPIO data bit 1 */
    word DATA2       :1;                                       /* RGPIO data bit 2 */
    word DATA3       :1;                                       /* RGPIO data bit 3 */
    word DATA4       :1;                                       /* RGPIO data bit 4 */
    word DATA5       :1;                                       /* RGPIO data bit 5 */
    word DATA6       :1;                                       /* RGPIO data bit 6 */
    word DATA7       :1;                                       /* RGPIO data bit 7 */
    word DATA8       :1;                                       /* RGPIO data bit 8 */
    word DATA9       :1;                                       /* RGPIO data bit 9 */
    word DATA10      :1;                                       /* RGPIO data bit 10 */
    word DATA11      :1;                                       /* RGPIO data bit 11 */
    word DATA12      :1;                                       /* RGPIO data bit 12 */
    word DATA13      :1;                                       /* RGPIO data bit 13 */
    word DATA14      :1;                                       /* RGPIO data bit 14 */
    word DATA15      :1;                                       /* RGPIO data bit 15 */
  } Bits;
} RGPIO_DATASTR;
extern volatile RGPIO_DATASTR _RGPIO_DATA @0x00C00002;
#define RGPIO_DATA                      _RGPIO_DATA.Word
#define RGPIO_DATA_DATA0                _RGPIO_DATA.Bits.DATA0
#define RGPIO_DATA_DATA1                _RGPIO_DATA.Bits.DATA1
#define RGPIO_DATA_DATA2                _RGPIO_DATA.Bits.DATA2
#define RGPIO_DATA_DATA3                _RGPIO_DATA.Bits.DATA3
#define RGPIO_DATA_DATA4                _RGPIO_DATA.Bits.DATA4
#define RGPIO_DATA_DATA5                _RGPIO_DATA.Bits.DATA5
#define RGPIO_DATA_DATA6                _RGPIO_DATA.Bits.DATA6
#define RGPIO_DATA_DATA7                _RGPIO_DATA.Bits.DATA7
#define RGPIO_DATA_DATA8                _RGPIO_DATA.Bits.DATA8
#define RGPIO_DATA_DATA9                _RGPIO_DATA.Bits.DATA9
#define RGPIO_DATA_DATA10               _RGPIO_DATA.Bits.DATA10
#define RGPIO_DATA_DATA11               _RGPIO_DATA.Bits.DATA11
#define RGPIO_DATA_DATA12               _RGPIO_DATA.Bits.DATA12
#define RGPIO_DATA_DATA13               _RGPIO_DATA.Bits.DATA13
#define RGPIO_DATA_DATA14               _RGPIO_DATA.Bits.DATA14
#define RGPIO_DATA_DATA15               _RGPIO_DATA.Bits.DATA15

#define RGPIO_DATA_DATA0_MASK           1U
#define RGPIO_DATA_DATA1_MASK           2U
#define RGPIO_DATA_DATA2_MASK           4U
#define RGPIO_DATA_DATA3_MASK           8U
#define RGPIO_DATA_DATA4_MASK           16U
#define RGPIO_DATA_DATA5_MASK           32U
#define RGPIO_DATA_DATA6_MASK           64U
#define RGPIO_DATA_DATA7_MASK           128U
#define RGPIO_DATA_DATA8_MASK           256U
#define RGPIO_DATA_DATA9_MASK           512U
#define RGPIO_DATA_DATA10_MASK          1024U
#define RGPIO_DATA_DATA11_MASK          2048U
#define RGPIO_DATA_DATA12_MASK          4096U
#define RGPIO_DATA_DATA13_MASK          8192U
#define RGPIO_DATA_DATA14_MASK          16384U
#define RGPIO_DATA_DATA15_MASK          32768U


/*** RGPIO_ENB - RGPIO Pin Enable Register; 0x00C00004 ***/
typedef union {
  word Word;
  struct {
    word ENB0        :1;                                       /* RGPIO enable bit 0 */
    word ENB1        :1;                                       /* RGPIO enable bit 1 */
    word ENB2        :1;                                       /* RGPIO enable bit 2 */
    word ENB3        :1;                                       /* RGPIO enable bit 3 */
    word ENB4        :1;                                       /* RGPIO enable bit 4 */
    word ENB5        :1;                                       /* RGPIO enable bit 5 */
    word ENB6        :1;                                       /* RGPIO enable bit 6 */
    word ENB7        :1;                                       /* RGPIO enable bit 7 */
    word ENB8        :1;                                       /* RGPIO enable bit 8 */
    word ENB9        :1;                                       /* RGPIO enable bit 9 */
    word ENB10       :1;                                       /* RGPIO enable bit 10 */
    word ENB11       :1;                                       /* RGPIO enable bit 11 */
    word ENB12       :1;                                       /* RGPIO enable bit 12 */
    word ENB13       :1;                                       /* RGPIO enable bit 13 */
    word ENB14       :1;                                       /* RGPIO enable bit 14 */
    word ENB15       :1;                                       /* RGPIO enable bit 15 */
  } Bits;
} RGPIO_ENBSTR;
extern volatile RGPIO_ENBSTR _RGPIO_ENB @0x00C00004;
#define RGPIO_ENB                       _RGPIO_ENB.Word
#define RGPIO_ENB_ENB0                  _RGPIO_ENB.Bits.ENB0
#define RGPIO_ENB_ENB1                  _RGPIO_ENB.Bits.ENB1
#define RGPIO_ENB_ENB2                  _RGPIO_ENB.Bits.ENB2
#define RGPIO_ENB_ENB3                  _RGPIO_ENB.Bits.ENB3
#define RGPIO_ENB_ENB4                  _RGPIO_ENB.Bits.ENB4
#define RGPIO_ENB_ENB5                  _RGPIO_ENB.Bits.ENB5
#define RGPIO_ENB_ENB6                  _RGPIO_ENB.Bits.ENB6
#define RGPIO_ENB_ENB7                  _RGPIO_ENB.Bits.ENB7
#define RGPIO_ENB_ENB8                  _RGPIO_ENB.Bits.ENB8
#define RGPIO_ENB_ENB9                  _RGPIO_ENB.Bits.ENB9
#define RGPIO_ENB_ENB10                 _RGPIO_ENB.Bits.ENB10
#define RGPIO_ENB_ENB11                 _RGPIO_ENB.Bits.ENB11
#define RGPIO_ENB_ENB12                 _RGPIO_ENB.Bits.ENB12
#define RGPIO_ENB_ENB13                 _RGPIO_ENB.Bits.ENB13
#define RGPIO_ENB_ENB14                 _RGPIO_ENB.Bits.ENB14
#define RGPIO_ENB_ENB15                 _RGPIO_ENB.Bits.ENB15

#define RGPIO_ENB_ENB0_MASK             1U
#define RGPIO_ENB_ENB1_MASK             2U
#define RGPIO_ENB_ENB2_MASK             4U
#define RGPIO_ENB_ENB3_MASK             8U
#define RGPIO_ENB_ENB4_MASK             16U
#define RGPIO_ENB_ENB5_MASK             32U
#define RGPIO_ENB_ENB6_MASK             64U
#define RGPIO_ENB_ENB7_MASK             128U
#define RGPIO_ENB_ENB8_MASK             256U
#define RGPIO_ENB_ENB9_MASK             512U
#define RGPIO_ENB_ENB10_MASK            1024U
#define RGPIO_ENB_ENB11_MASK            2048U
#define RGPIO_ENB_ENB12_MASK            4096U
#define RGPIO_ENB_ENB13_MASK            8192U
#define RGPIO_ENB_ENB14_MASK            16384U
#define RGPIO_ENB_ENB15_MASK            32768U


/*** RGPIO_CLR - RGPIO Clear Data Register; 0x00C00006 ***/
typedef union {
  word Word;
  struct {
    word CLR0        :1;                                       /* RGPIO clear data bit 0 */
    word CLR1        :1;                                       /* RGPIO clear data bit 1 */
    word CLR2        :1;                                       /* RGPIO clear data bit 2 */
    word CLR3        :1;                                       /* RGPIO clear data bit 3 */
    word CLR4        :1;                                       /* RGPIO clear data bit 4 */
    word CLR5        :1;                                       /* RGPIO clear data bit 5 */
    word CLR6        :1;                                       /* RGPIO clear data bit 6 */
    word CLR7        :1;                                       /* RGPIO clear data bit 7 */
    word CLR8        :1;                                       /* RGPIO clear data bit 8 */
    word CLR9        :1;                                       /* RGPIO clear data bit 9 */
    word CLR10       :1;                                       /* RGPIO clear data bit 10 */
    word CLR11       :1;                                       /* RGPIO clear data bit 11 */
    word CLR12       :1;                                       /* RGPIO clear data bit 12 */
    word CLR13       :1;                                       /* RGPIO clear data bit 13 */
    word CLR14       :1;                                       /* RGPIO clear data bit 14 */
    word CLR15       :1;                                       /* RGPIO clear data bit 15 */
  } Bits;
} RGPIO_CLRSTR;
extern volatile RGPIO_CLRSTR _RGPIO_CLR @0x00C00006;
#define RGPIO_CLR                       _RGPIO_CLR.Word
#define RGPIO_CLR_CLR0                  _RGPIO_CLR.Bits.CLR0
#define RGPIO_CLR_CLR1                  _RGPIO_CLR.Bits.CLR1
#define RGPIO_CLR_CLR2                  _RGPIO_CLR.Bits.CLR2
#define RGPIO_CLR_CLR3                  _RGPIO_CLR.Bits.CLR3
#define RGPIO_CLR_CLR4                  _RGPIO_CLR.Bits.CLR4
#define RGPIO_CLR_CLR5                  _RGPIO_CLR.Bits.CLR5
#define RGPIO_CLR_CLR6                  _RGPIO_CLR.Bits.CLR6
#define RGPIO_CLR_CLR7                  _RGPIO_CLR.Bits.CLR7
#define RGPIO_CLR_CLR8                  _RGPIO_CLR.Bits.CLR8
#define RGPIO_CLR_CLR9                  _RGPIO_CLR.Bits.CLR9
#define RGPIO_CLR_CLR10                 _RGPIO_CLR.Bits.CLR10
#define RGPIO_CLR_CLR11                 _RGPIO_CLR.Bits.CLR11
#define RGPIO_CLR_CLR12                 _RGPIO_CLR.Bits.CLR12
#define RGPIO_CLR_CLR13                 _RGPIO_CLR.Bits.CLR13
#define RGPIO_CLR_CLR14                 _RGPIO_CLR.Bits.CLR14
#define RGPIO_CLR_CLR15                 _RGPIO_CLR.Bits.CLR15

#define RGPIO_CLR_CLR0_MASK             1U
#define RGPIO_CLR_CLR1_MASK             2U
#define RGPIO_CLR_CLR2_MASK             4U
#define RGPIO_CLR_CLR3_MASK             8U
#define RGPIO_CLR_CLR4_MASK             16U
#define RGPIO_CLR_CLR5_MASK             32U
#define RGPIO_CLR_CLR6_MASK             64U
#define RGPIO_CLR_CLR7_MASK             128U
#define RGPIO_CLR_CLR8_MASK             256U
#define RGPIO_CLR_CLR9_MASK             512U
#define RGPIO_CLR_CLR10_MASK            1024U
#define RGPIO_CLR_CLR11_MASK            2048U
#define RGPIO_CLR_CLR12_MASK            4096U
#define RGPIO_CLR_CLR13_MASK            8192U
#define RGPIO_CLR_CLR14_MASK            16384U
#define RGPIO_CLR_CLR15_MASK            32768U


/*** RGPIO_SET - RGPIO Set Data Register; 0x00C0000A ***/
typedef union {
  word Word;
  struct {
    word SET0        :1;                                       /* RGPIO set data bit 0 */
    word SET1        :1;                                       /* RGPIO set data bit 1 */
    word SET2        :1;                                       /* RGPIO set data bit 2 */
    word SET3        :1;                                       /* RGPIO set data bit 3 */
    word SET4        :1;                                       /* RGPIO set data bit 4 */
    word SET5        :1;                                       /* RGPIO set data bit 5 */
    word SET6        :1;                                       /* RGPIO set data bit 6 */
    word SET7        :1;                                       /* RGPIO set data bit 7 */
    word SET8        :1;                                       /* RGPIO set data bit 8 */
    word SET9        :1;                                       /* RGPIO set data bit 9 */
    word SET10       :1;                                       /* RGPIO set data bit 10 */
    word SET11       :1;                                       /* RGPIO set data bit 11 */
    word SET12       :1;                                       /* RGPIO set data bit 12 */
    word SET13       :1;                                       /* RGPIO set data bit 13 */
    word SET14       :1;                                       /* RGPIO set data bit 14 */
    word SET15       :1;                                       /* RGPIO set data bit 15 */
  } Bits;
} RGPIO_SETSTR;
extern volatile RGPIO_SETSTR _RGPIO_SET @0x00C0000A;
#define RGPIO_SET                       _RGPIO_SET.Word
#define RGPIO_SET_SET0                  _RGPIO_SET.Bits.SET0
#define RGPIO_SET_SET1                  _RGPIO_SET.Bits.SET1
#define RGPIO_SET_SET2                  _RGPIO_SET.Bits.SET2
#define RGPIO_SET_SET3                  _RGPIO_SET.Bits.SET3
#define RGPIO_SET_SET4                  _RGPIO_SET.Bits.SET4
#define RGPIO_SET_SET5                  _RGPIO_SET.Bits.SET5
#define RGPIO_SET_SET6                  _RGPIO_SET.Bits.SET6
#define RGPIO_SET_SET7                  _RGPIO_SET.Bits.SET7
#define RGPIO_SET_SET8                  _RGPIO_SET.Bits.SET8
#define RGPIO_SET_SET9                  _RGPIO_SET.Bits.SET9
#define RGPIO_SET_SET10                 _RGPIO_SET.Bits.SET10
#define RGPIO_SET_SET11                 _RGPIO_SET.Bits.SET11
#define RGPIO_SET_SET12                 _RGPIO_SET.Bits.SET12
#define RGPIO_SET_SET13                 _RGPIO_SET.Bits.SET13
#define RGPIO_SET_SET14                 _RGPIO_SET.Bits.SET14
#define RGPIO_SET_SET15                 _RGPIO_SET.Bits.SET15

#define RGPIO_SET_SET0_MASK             1U
#define RGPIO_SET_SET1_MASK             2U
#define RGPIO_SET_SET2_MASK             4U
#define RGPIO_SET_SET3_MASK             8U
#define RGPIO_SET_SET4_MASK             16U
#define RGPIO_SET_SET5_MASK             32U
#define RGPIO_SET_SET6_MASK             64U
#define RGPIO_SET_SET7_MASK             128U
#define RGPIO_SET_SET8_MASK             256U
#define RGPIO_SET_SET9_MASK             512U
#define RGPIO_SET_SET10_MASK            1024U
#define RGPIO_SET_SET11_MASK            2048U
#define RGPIO_SET_SET12_MASK            4096U
#define RGPIO_SET_SET13_MASK            8192U
#define RGPIO_SET_SET14_MASK            16384U
#define RGPIO_SET_SET15_MASK            32768U


/*** RGPIO_TOG - RGPIO Toggle Data Register; 0x00C0000E ***/
typedef union {
  word Word;
  struct {
    word TOG0        :1;                                       /* RGPIO toggle data bit 0 */
    word TOG1        :1;                                       /* RGPIO toggle data bit 1 */
    word TOG2        :1;                                       /* RGPIO toggle data bit 2 */
    word TOG3        :1;                                       /* RGPIO toggle data bit 3 */
    word TOG4        :1;                                       /* RGPIO toggle data bit 4 */
    word TOG5        :1;                                       /* RGPIO toggle data bit 5 */
    word TOG6        :1;                                       /* RGPIO toggle data bit 6 */
    word TOG7        :1;                                       /* RGPIO toggle data bit 7 */
    word TOG8        :1;                                       /* RGPIO toggle data bit 8 */
    word TOG9        :1;                                       /* RGPIO toggle data bit 9 */
    word TOG10       :1;                                       /* RGPIO toggle data bit 10 */
    word TOG11       :1;                                       /* RGPIO toggle data bit 11 */
    word TOG12       :1;                                       /* RGPIO toggle data bit 12 */
    word TOG13       :1;                                       /* RGPIO toggle data bit 13 */
    word TOG14       :1;                                       /* RGPIO toggle data bit 14 */
    word TOG15       :1;                                       /* RGPIO toggle data bit 15 */
  } Bits;
} RGPIO_TOGSTR;
extern volatile RGPIO_TOGSTR _RGPIO_TOG @0x00C0000E;
#define RGPIO_TOG                       _RGPIO_TOG.Word
#define RGPIO_TOG_TOG0                  _RGPIO_TOG.Bits.TOG0
#define RGPIO_TOG_TOG1                  _RGPIO_TOG.Bits.TOG1
#define RGPIO_TOG_TOG2                  _RGPIO_TOG.Bits.TOG2
#define RGPIO_TOG_TOG3                  _RGPIO_TOG.Bits.TOG3
#define RGPIO_TOG_TOG4                  _RGPIO_TOG.Bits.TOG4
#define RGPIO_TOG_TOG5                  _RGPIO_TOG.Bits.TOG5
#define RGPIO_TOG_TOG6                  _RGPIO_TOG.Bits.TOG6
#define RGPIO_TOG_TOG7                  _RGPIO_TOG.Bits.TOG7
#define RGPIO_TOG_TOG8                  _RGPIO_TOG.Bits.TOG8
#define RGPIO_TOG_TOG9                  _RGPIO_TOG.Bits.TOG9
#define RGPIO_TOG_TOG10                 _RGPIO_TOG.Bits.TOG10
#define RGPIO_TOG_TOG11                 _RGPIO_TOG.Bits.TOG11
#define RGPIO_TOG_TOG12                 _RGPIO_TOG.Bits.TOG12
#define RGPIO_TOG_TOG13                 _RGPIO_TOG.Bits.TOG13
#define RGPIO_TOG_TOG14                 _RGPIO_TOG.Bits.TOG14
#define RGPIO_TOG_TOG15                 _RGPIO_TOG.Bits.TOG15

#define RGPIO_TOG_TOG0_MASK             1U
#define RGPIO_TOG_TOG1_MASK             2U
#define RGPIO_TOG_TOG2_MASK             4U
#define RGPIO_TOG_TOG3_MASK             8U
#define RGPIO_TOG_TOG4_MASK             16U
#define RGPIO_TOG_TOG5_MASK             32U
#define RGPIO_TOG_TOG6_MASK             64U
#define RGPIO_TOG_TOG7_MASK             128U
#define RGPIO_TOG_TOG8_MASK             256U
#define RGPIO_TOG_TOG9_MASK             512U
#define RGPIO_TOG_TOG10_MASK            1024U
#define RGPIO_TOG_TOG11_MASK            2048U
#define RGPIO_TOG_TOG12_MASK            4096U
#define RGPIO_TOG_TOG13_MASK            8192U
#define RGPIO_TOG_TOG14_MASK            16384U
#define RGPIO_TOG_TOG15_MASK            32768U


/*** PTAD - Port A Data Register; 0xFFFF8000 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAD0       :1;                                       /* Port A Data Register Bit 0 */
    byte PTAD1       :1;                                       /* Port A Data Register Bit 1 */
    byte PTAD2       :1;                                       /* Port A Data Register Bit 2 */
    byte PTAD3       :1;                                       /* Port A Data Register Bit 3 */
    byte PTAD4       :1;                                       /* Port A Data Register Bit 4 */
    byte PTAD5       :1;                                       /* Port A Data Register Bit 5 */
    byte PTAD6       :1;                                       /* Port A Data Register Bit 6 */
    byte PTAD7       :1;                                       /* Port A Data Register Bit 7 */
  } Bits;
} PTADSTR;
extern volatile PTADSTR _PTAD @0xFFFF8000;
#define PTAD                            _PTAD.Byte
#define PTAD_PTAD0                      _PTAD.Bits.PTAD0
#define PTAD_PTAD1                      _PTAD.Bits.PTAD1
#define PTAD_PTAD2                      _PTAD.Bits.PTAD2
#define PTAD_PTAD3                      _PTAD.Bits.PTAD3
#define PTAD_PTAD4                      _PTAD.Bits.PTAD4
#define PTAD_PTAD5                      _PTAD.Bits.PTAD5
#define PTAD_PTAD6                      _PTAD.Bits.PTAD6
#define PTAD_PTAD7                      _PTAD.Bits.PTAD7

#define PTAD_PTAD0_MASK                 1U
#define PTAD_PTAD1_MASK                 2U
#define PTAD_PTAD2_MASK                 4U
#define PTAD_PTAD3_MASK                 8U
#define PTAD_PTAD4_MASK                 16U
#define PTAD_PTAD5_MASK                 32U
#define PTAD_PTAD6_MASK                 64U
#define PTAD_PTAD7_MASK                 128U


/*** PTADD - Port A Data Direction Register; 0xFFFF8001 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADD0      :1;                                       /* Data Direction for Port A Bit 0 */
    byte PTADD1      :1;                                       /* Data Direction for Port A Bit 1 */
    byte PTADD2      :1;                                       /* Data Direction for Port A Bit 2 */
    byte PTADD3      :1;                                       /* Data Direction for Port A Bit 3 */
    byte PTADD4      :1;                                       /* Data Direction for Port A Bit 4 */
    byte PTADD5      :1;                                       /* Data Direction for Port A Bit 5 */
    byte PTADD6      :1;                                       /* Data Direction for Port A Bit 6 */
    byte PTADD7      :1;                                       /* Data Direction for Port A Bit 7 */
  } Bits;
} PTADDSTR;
extern volatile PTADDSTR _PTADD @0xFFFF8001;
#define PTADD                           _PTADD.Byte
#define PTADD_PTADD0                    _PTADD.Bits.PTADD0
#define PTADD_PTADD1                    _PTADD.Bits.PTADD1
#define PTADD_PTADD2                    _PTADD.Bits.PTADD2
#define PTADD_PTADD3                    _PTADD.Bits.PTADD3
#define PTADD_PTADD4                    _PTADD.Bits.PTADD4
#define PTADD_PTADD5                    _PTADD.Bits.PTADD5
#define PTADD_PTADD6                    _PTADD.Bits.PTADD6
#define PTADD_PTADD7                    _PTADD.Bits.PTADD7

#define PTADD_PTADD0_MASK               1U
#define PTADD_PTADD1_MASK               2U
#define PTADD_PTADD2_MASK               4U
#define PTADD_PTADD3_MASK               8U
#define PTADD_PTADD4_MASK               16U
#define PTADD_PTADD5_MASK               32U
#define PTADD_PTADD6_MASK               64U
#define PTADD_PTADD7_MASK               128U


/*** PTBD - Port B Data Register; 0xFFFF8002 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBD0       :1;                                       /* Port B Data Register Bit 0 */
    byte PTBD1       :1;                                       /* Port B Data Register Bit 1 */
    byte PTBD2       :1;                                       /* Port B Data Register Bit 2 */
    byte PTBD3       :1;                                       /* Port B Data Register Bit 3 */
    byte PTBD4       :1;                                       /* Port B Data Register Bit 4 */
    byte PTBD5       :1;                                       /* Port B Data Register Bit 5 */
    byte PTBD6       :1;                                       /* Port B Data Register Bit 6 */
    byte PTBD7       :1;                                       /* Port B Data Register Bit 7 */
  } Bits;
} PTBDSTR;
extern volatile PTBDSTR _PTBD @0xFFFF8002;
#define PTBD                            _PTBD.Byte
#define PTBD_PTBD0                      _PTBD.Bits.PTBD0
#define PTBD_PTBD1                      _PTBD.Bits.PTBD1
#define PTBD_PTBD2                      _PTBD.Bits.PTBD2
#define PTBD_PTBD3                      _PTBD.Bits.PTBD3
#define PTBD_PTBD4                      _PTBD.Bits.PTBD4
#define PTBD_PTBD5                      _PTBD.Bits.PTBD5
#define PTBD_PTBD6                      _PTBD.Bits.PTBD6
#define PTBD_PTBD7                      _PTBD.Bits.PTBD7

#define PTBD_PTBD0_MASK                 1U
#define PTBD_PTBD1_MASK                 2U
#define PTBD_PTBD2_MASK                 4U
#define PTBD_PTBD3_MASK                 8U
#define PTBD_PTBD4_MASK                 16U
#define PTBD_PTBD5_MASK                 32U
#define PTBD_PTBD6_MASK                 64U
#define PTBD_PTBD7_MASK                 128U


/*** PTBDD - Port B Data Direction Register; 0xFFFF8003 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDD0      :1;                                       /* Data Direction for Port B Bit 0 */
    byte PTBDD1      :1;                                       /* Data Direction for Port B Bit 1 */
    byte PTBDD2      :1;                                       /* Data Direction for Port B Bit 2 */
    byte PTBDD3      :1;                                       /* Data Direction for Port B Bit 3 */
    byte PTBDD4      :1;                                       /* Data Direction for Port B Bit 4 */
    byte PTBDD5      :1;                                       /* Data Direction for Port B Bit 5 */
    byte PTBDD6      :1;                                       /* Data Direction for Port B Bit 6 */
    byte PTBDD7      :1;                                       /* Data Direction for Port B Bit 7 */
  } Bits;
} PTBDDSTR;
extern volatile PTBDDSTR _PTBDD @0xFFFF8003;
#define PTBDD                           _PTBDD.Byte
#define PTBDD_PTBDD0                    _PTBDD.Bits.PTBDD0
#define PTBDD_PTBDD1                    _PTBDD.Bits.PTBDD1
#define PTBDD_PTBDD2                    _PTBDD.Bits.PTBDD2
#define PTBDD_PTBDD3                    _PTBDD.Bits.PTBDD3
#define PTBDD_PTBDD4                    _PTBDD.Bits.PTBDD4
#define PTBDD_PTBDD5                    _PTBDD.Bits.PTBDD5
#define PTBDD_PTBDD6                    _PTBDD.Bits.PTBDD6
#define PTBDD_PTBDD7                    _PTBDD.Bits.PTBDD7

#define PTBDD_PTBDD0_MASK               1U
#define PTBDD_PTBDD1_MASK               2U
#define PTBDD_PTBDD2_MASK               4U
#define PTBDD_PTBDD3_MASK               8U
#define PTBDD_PTBDD4_MASK               16U
#define PTBDD_PTBDD5_MASK               32U
#define PTBDD_PTBDD6_MASK               64U
#define PTBDD_PTBDD7_MASK               128U


/*** PTCD - Port C Data Register; 0xFFFF8004 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCD0       :1;                                       /* Port C Data Register Bit 0 */
    byte PTCD1       :1;                                       /* Port C Data Register Bit 1 */
    byte PTCD2       :1;                                       /* Port C Data Register Bit 2 */
    byte PTCD3       :1;                                       /* Port C Data Register Bit 3 */
    byte PTCD4       :1;                                       /* Port C Data Register Bit 4 */
    byte PTCD5       :1;                                       /* Port C Data Register Bit 5 */
    byte PTCD6       :1;                                       /* Port C Data Register Bit 6 */
    byte PTCD7       :1;                                       /* Port C Data Register Bit 7 */
  } Bits;
} PTCDSTR;
extern volatile PTCDSTR _PTCD @0xFFFF8004;
#define PTCD                            _PTCD.Byte
#define PTCD_PTCD0                      _PTCD.Bits.PTCD0
#define PTCD_PTCD1                      _PTCD.Bits.PTCD1
#define PTCD_PTCD2                      _PTCD.Bits.PTCD2
#define PTCD_PTCD3                      _PTCD.Bits.PTCD3
#define PTCD_PTCD4                      _PTCD.Bits.PTCD4
#define PTCD_PTCD5                      _PTCD.Bits.PTCD5
#define PTCD_PTCD6                      _PTCD.Bits.PTCD6
#define PTCD_PTCD7                      _PTCD.Bits.PTCD7

#define PTCD_PTCD0_MASK                 1U
#define PTCD_PTCD1_MASK                 2U
#define PTCD_PTCD2_MASK                 4U
#define PTCD_PTCD3_MASK                 8U
#define PTCD_PTCD4_MASK                 16U
#define PTCD_PTCD5_MASK                 32U
#define PTCD_PTCD6_MASK                 64U
#define PTCD_PTCD7_MASK                 128U


/*** PTCDD - Port C Data Direction Register; 0xFFFF8005 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDD0      :1;                                       /* Data Direction for Port C Bit 0 */
    byte PTCDD1      :1;                                       /* Data Direction for Port C Bit 1 */
    byte PTCDD2      :1;                                       /* Data Direction for Port C Bit 2 */
    byte PTCDD3      :1;                                       /* Data Direction for Port C Bit 3 */
    byte PTCDD4      :1;                                       /* Data Direction for Port C Bit 4 */
    byte PTCDD5      :1;                                       /* Data Direction for Port C Bit 5 */
    byte PTCDD6      :1;                                       /* Data Direction for Port C Bit 6 */
    byte PTCDD7      :1;                                       /* Data Direction for Port C Bit 7 */
  } Bits;
} PTCDDSTR;
extern volatile PTCDDSTR _PTCDD @0xFFFF8005;
#define PTCDD                           _PTCDD.Byte
#define PTCDD_PTCDD0                    _PTCDD.Bits.PTCDD0
#define PTCDD_PTCDD1                    _PTCDD.Bits.PTCDD1
#define PTCDD_PTCDD2                    _PTCDD.Bits.PTCDD2
#define PTCDD_PTCDD3                    _PTCDD.Bits.PTCDD3
#define PTCDD_PTCDD4                    _PTCDD.Bits.PTCDD4
#define PTCDD_PTCDD5                    _PTCDD.Bits.PTCDD5
#define PTCDD_PTCDD6                    _PTCDD.Bits.PTCDD6
#define PTCDD_PTCDD7                    _PTCDD.Bits.PTCDD7

#define PTCDD_PTCDD0_MASK               1U
#define PTCDD_PTCDD1_MASK               2U
#define PTCDD_PTCDD2_MASK               4U
#define PTCDD_PTCDD3_MASK               8U
#define PTCDD_PTCDD4_MASK               16U
#define PTCDD_PTCDD5_MASK               32U
#define PTCDD_PTCDD6_MASK               64U
#define PTCDD_PTCDD7_MASK               128U


/*** PTDD - Port D Data Register; 0xFFFF8006 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDD0       :1;                                       /* Port D Data Register Bit 0 */
    byte PTDD1       :1;                                       /* Port D Data Register Bit 1 */
    byte PTDD2       :1;                                       /* Port D Data Register Bit 2 */
    byte PTDD3       :1;                                       /* Port D Data Register Bit 3 */
    byte PTDD4       :1;                                       /* Port D Data Register Bit 4 */
    byte PTDD5       :1;                                       /* Port D Data Register Bit 5 */
    byte PTDD6       :1;                                       /* Port D Data Register Bit 6 */
    byte PTDD7       :1;                                       /* Port D Data Register Bit 7 */
  } Bits;
} PTDDSTR;
extern volatile PTDDSTR _PTDD @0xFFFF8006;
#define PTDD                            _PTDD.Byte
#define PTDD_PTDD0                      _PTDD.Bits.PTDD0
#define PTDD_PTDD1                      _PTDD.Bits.PTDD1
#define PTDD_PTDD2                      _PTDD.Bits.PTDD2
#define PTDD_PTDD3                      _PTDD.Bits.PTDD3
#define PTDD_PTDD4                      _PTDD.Bits.PTDD4
#define PTDD_PTDD5                      _PTDD.Bits.PTDD5
#define PTDD_PTDD6                      _PTDD.Bits.PTDD6
#define PTDD_PTDD7                      _PTDD.Bits.PTDD7

#define PTDD_PTDD0_MASK                 1U
#define PTDD_PTDD1_MASK                 2U
#define PTDD_PTDD2_MASK                 4U
#define PTDD_PTDD3_MASK                 8U
#define PTDD_PTDD4_MASK                 16U
#define PTDD_PTDD5_MASK                 32U
#define PTDD_PTDD6_MASK                 64U
#define PTDD_PTDD7_MASK                 128U


/*** PTDDD - Port D Data Direction Register; 0xFFFF8007 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDD0      :1;                                       /* Data Direction for Port D Bit 0 */
    byte PTDDD1      :1;                                       /* Data Direction for Port D Bit 1 */
    byte PTDDD2      :1;                                       /* Data Direction for Port D Bit 2 */
    byte PTDDD3      :1;                                       /* Data Direction for Port D Bit 3 */
    byte PTDDD4      :1;                                       /* Data Direction for Port D Bit 4 */
    byte PTDDD5      :1;                                       /* Data Direction for Port D Bit 5 */
    byte PTDDD6      :1;                                       /* Data Direction for Port D Bit 6 */
    byte PTDDD7      :1;                                       /* Data Direction for Port D Bit 7 */
  } Bits;
} PTDDDSTR;
extern volatile PTDDDSTR _PTDDD @0xFFFF8007;
#define PTDDD                           _PTDDD.Byte
#define PTDDD_PTDDD0                    _PTDDD.Bits.PTDDD0
#define PTDDD_PTDDD1                    _PTDDD.Bits.PTDDD1
#define PTDDD_PTDDD2                    _PTDDD.Bits.PTDDD2
#define PTDDD_PTDDD3                    _PTDDD.Bits.PTDDD3
#define PTDDD_PTDDD4                    _PTDDD.Bits.PTDDD4
#define PTDDD_PTDDD5                    _PTDDD.Bits.PTDDD5
#define PTDDD_PTDDD6                    _PTDDD.Bits.PTDDD6
#define PTDDD_PTDDD7                    _PTDDD.Bits.PTDDD7

#define PTDDD_PTDDD0_MASK               1U
#define PTDDD_PTDDD1_MASK               2U
#define PTDDD_PTDDD2_MASK               4U
#define PTDDD_PTDDD3_MASK               8U
#define PTDDD_PTDDD4_MASK               16U
#define PTDDD_PTDDD5_MASK               32U
#define PTDDD_PTDDD6_MASK               64U
#define PTDDD_PTDDD7_MASK               128U


/*** DACDAT0 - DAC Data 0 Register; 0xFFFF8010 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT0H - DAC Data 0 High Register; 0xFFFF8010 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT08    :1;                                       /* Buffer Data 0 High, bit 8 */
        byte DACDAT09    :1;                                       /* Buffer Data 0 High, bit 9 */
        byte DACDAT010   :1;                                       /* Buffer Data 0 High, bit 10 */
        byte DACDAT011   :1;                                       /* Buffer Data 0 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT0_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT0HSTR;
    #define DACDAT0H                    _DACDAT0.Overlap_STR.DACDAT0HSTR.Byte
    #define DACDAT0H_DACDAT08           _DACDAT0.Overlap_STR.DACDAT0HSTR.Bits.DACDAT08
    #define DACDAT0H_DACDAT09           _DACDAT0.Overlap_STR.DACDAT0HSTR.Bits.DACDAT09
    #define DACDAT0H_DACDAT010          _DACDAT0.Overlap_STR.DACDAT0HSTR.Bits.DACDAT010
    #define DACDAT0H_DACDAT011          _DACDAT0.Overlap_STR.DACDAT0HSTR.Bits.DACDAT011
    #define DACDAT0H_DACDAT0_8          _DACDAT0.Overlap_STR.DACDAT0HSTR.MergedBits.grpDACDAT0_8
    #define DACDAT0H_DACDAT0            DACDAT0H_DACDAT0_8
    
    #define DACDAT0H_DACDAT08_MASK      1U
    #define DACDAT0H_DACDAT09_MASK      2U
    #define DACDAT0H_DACDAT010_MASK     4U
    #define DACDAT0H_DACDAT011_MASK     8U
    #define DACDAT0H_DACDAT0_8_MASK     15U
    #define DACDAT0H_DACDAT0_8_BITNUM   0U
    

    /*** DACDAT0L - DAC Data 0 Low Register; 0xFFFF8011 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT00    :1;                                       /* Buffer Data 0 Low, bit 0 */
        byte DACDAT01    :1;                                       /* Buffer Data 0 Low, bit 1 */
        byte DACDAT02    :1;                                       /* Buffer Data 0 Low, bit 2 */
        byte DACDAT03    :1;                                       /* Buffer Data 0 Low, bit 3 */
        byte DACDAT04    :1;                                       /* Buffer Data 0 Low, bit 4 */
        byte DACDAT05    :1;                                       /* Buffer Data 0 Low, bit 5 */
        byte DACDAT06    :1;                                       /* Buffer Data 0 Low, bit 6 */
        byte DACDAT07    :1;                                       /* Buffer Data 0 Low, bit 7 */
      } Bits;
    } DACDAT0LSTR;
    #define DACDAT0L                    _DACDAT0.Overlap_STR.DACDAT0LSTR.Byte
    #define DACDAT0L_DACDAT00           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT00
    #define DACDAT0L_DACDAT01           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT01
    #define DACDAT0L_DACDAT02           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT02
    #define DACDAT0L_DACDAT03           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT03
    #define DACDAT0L_DACDAT04           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT04
    #define DACDAT0L_DACDAT05           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT05
    #define DACDAT0L_DACDAT06           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT06
    #define DACDAT0L_DACDAT07           _DACDAT0.Overlap_STR.DACDAT0LSTR.Bits.DACDAT07
    
    #define DACDAT0L_DACDAT00_MASK      1U
    #define DACDAT0L_DACDAT01_MASK      2U
    #define DACDAT0L_DACDAT02_MASK      4U
    #define DACDAT0L_DACDAT03_MASK      8U
    #define DACDAT0L_DACDAT04_MASK      16U
    #define DACDAT0L_DACDAT05_MASK      32U
    #define DACDAT0L_DACDAT06_MASK      64U
    #define DACDAT0L_DACDAT07_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT00    :1;                                       /* Buffer Data 0, bit 0 */
    word DACDAT01    :1;                                       /* Buffer Data 0, bit 1 */
    word DACDAT02    :1;                                       /* Buffer Data 0, bit 2 */
    word DACDAT03    :1;                                       /* Buffer Data 0, bit 3 */
    word DACDAT04    :1;                                       /* Buffer Data 0, bit 4 */
    word DACDAT05    :1;                                       /* Buffer Data 0, bit 5 */
    word DACDAT06    :1;                                       /* Buffer Data 0, bit 6 */
    word DACDAT07    :1;                                       /* Buffer Data 0, bit 7 */
    word DACDAT08    :1;                                       /* Buffer Data 0, bit 8 */
    word DACDAT09    :1;                                       /* Buffer Data 0, bit 9 */
    word DACDAT010   :1;                                       /* Buffer Data 0, bit 10 */
    word DACDAT011   :1;                                       /* Buffer Data 0, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT0 :12;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT0STR;
extern volatile DACDAT0STR _DACDAT0 @0xFFFF8010;
#define DACDAT0                         _DACDAT0.Word
#define DACDAT0_DACDAT00                _DACDAT0.Bits.DACDAT00
#define DACDAT0_DACDAT01                _DACDAT0.Bits.DACDAT01
#define DACDAT0_DACDAT02                _DACDAT0.Bits.DACDAT02
#define DACDAT0_DACDAT03                _DACDAT0.Bits.DACDAT03
#define DACDAT0_DACDAT04                _DACDAT0.Bits.DACDAT04
#define DACDAT0_DACDAT05                _DACDAT0.Bits.DACDAT05
#define DACDAT0_DACDAT06                _DACDAT0.Bits.DACDAT06
#define DACDAT0_DACDAT07                _DACDAT0.Bits.DACDAT07
#define DACDAT0_DACDAT08                _DACDAT0.Bits.DACDAT08
#define DACDAT0_DACDAT09                _DACDAT0.Bits.DACDAT09
#define DACDAT0_DACDAT010               _DACDAT0.Bits.DACDAT010
#define DACDAT0_DACDAT011               _DACDAT0.Bits.DACDAT011
/* DACDAT_ARR: Access 16 DACDATx registers in an array */
#define DACDAT_ARR                      ((volatile word *) &DACDAT0)
#define DACDAT0_DACDAT0                 _DACDAT0.MergedBits.grpDACDAT0

#define DACDAT0_DACDAT00_MASK           1U
#define DACDAT0_DACDAT01_MASK           2U
#define DACDAT0_DACDAT02_MASK           4U
#define DACDAT0_DACDAT03_MASK           8U
#define DACDAT0_DACDAT04_MASK           16U
#define DACDAT0_DACDAT05_MASK           32U
#define DACDAT0_DACDAT06_MASK           64U
#define DACDAT0_DACDAT07_MASK           128U
#define DACDAT0_DACDAT08_MASK           256U
#define DACDAT0_DACDAT09_MASK           512U
#define DACDAT0_DACDAT010_MASK          1024U
#define DACDAT0_DACDAT011_MASK          2048U
#define DACDAT0_DACDAT0_MASK            4095U
#define DACDAT0_DACDAT0_BITNUM          0U


/*** DACDAT1 - DAC Data 1 Register; 0xFFFF8012 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT1H - DAC Data 1 High Register; 0xFFFF8012 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT18    :1;                                       /* Buffer Data 1 High, bit 8 */
        byte DACDAT19    :1;                                       /* Buffer Data 1 High, bit 9 */
        byte DACDAT110   :1;                                       /* Buffer Data 1 High, bit 10 */
        byte DACDAT111   :1;                                       /* Buffer Data 1 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_18 :2;
        byte grpDACDAT1_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT1HSTR;
    #define DACDAT1H                    _DACDAT1.Overlap_STR.DACDAT1HSTR.Byte
    #define DACDAT1H_DACDAT18           _DACDAT1.Overlap_STR.DACDAT1HSTR.Bits.DACDAT18
    #define DACDAT1H_DACDAT19           _DACDAT1.Overlap_STR.DACDAT1HSTR.Bits.DACDAT19
    #define DACDAT1H_DACDAT110          _DACDAT1.Overlap_STR.DACDAT1HSTR.Bits.DACDAT110
    #define DACDAT1H_DACDAT111          _DACDAT1.Overlap_STR.DACDAT1HSTR.Bits.DACDAT111
    #define DACDAT1H_DACDAT_18          _DACDAT1.Overlap_STR.DACDAT1HSTR.MergedBits.grpDACDAT_18
    #define DACDAT1H_DACDAT1_10         _DACDAT1.Overlap_STR.DACDAT1HSTR.MergedBits.grpDACDAT1_10
    #define DACDAT1H_DACDAT             DACDAT1H_DACDAT_18
    #define DACDAT1H_DACDAT1            DACDAT1H_DACDAT1_10
    
    #define DACDAT1H_DACDAT18_MASK      1U
    #define DACDAT1H_DACDAT19_MASK      2U
    #define DACDAT1H_DACDAT110_MASK     4U
    #define DACDAT1H_DACDAT111_MASK     8U
    #define DACDAT1H_DACDAT_18_MASK     3U
    #define DACDAT1H_DACDAT_18_BITNUM   0U
    #define DACDAT1H_DACDAT1_10_MASK    12U
    #define DACDAT1H_DACDAT1_10_BITNUM  2U
    

    /*** DACDAT1L - DAC Data 1 Low Register; 0xFFFF8013 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT10_bit :1;                                      /* Buffer Data 1 Low, bit 0 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT11_bit :1;                                      /* Buffer Data 1 Low, bit 1 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT12_bit :1;                                      /* Buffer Data 1 Low, bit 2 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT13_bit :1;                                      /* Buffer Data 1 Low, bit 3 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT14_bit :1;                                      /* Buffer Data 1 Low, bit 4 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT15_bit :1;                                      /* Buffer Data 1 Low, bit 5 */ /*Warning: bit name is duplicated with register name*/
        byte DACDAT16    :1;                                       /* Buffer Data 1 Low, bit 6 */
        byte DACDAT17    :1;                                       /* Buffer Data 1 Low, bit 7 */
      } Bits;
    } DACDAT1LSTR;
    #define DACDAT1L                    _DACDAT1.Overlap_STR.DACDAT1LSTR.Byte
    #define DACDAT1L_DACDAT10           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT10_bit
    #define DACDAT1L_DACDAT11           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT11_bit
    #define DACDAT1L_DACDAT12           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT12_bit
    #define DACDAT1L_DACDAT13           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT13_bit
    #define DACDAT1L_DACDAT14           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT14_bit
    #define DACDAT1L_DACDAT15           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT15_bit
    #define DACDAT1L_DACDAT16           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT16
    #define DACDAT1L_DACDAT17           _DACDAT1.Overlap_STR.DACDAT1LSTR.Bits.DACDAT17
    
    #define DACDAT1L_DACDAT10_MASK      1U
    #define DACDAT1L_DACDAT11_MASK      2U
    #define DACDAT1L_DACDAT12_MASK      4U
    #define DACDAT1L_DACDAT13_MASK      8U
    #define DACDAT1L_DACDAT14_MASK      16U
    #define DACDAT1L_DACDAT15_MASK      32U
    #define DACDAT1L_DACDAT16_MASK      64U
    #define DACDAT1L_DACDAT17_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT10_bit :1;                                      /* Buffer Data 1, bit 0 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT11_bit :1;                                      /* Buffer Data 1, bit 1 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT12_bit :1;                                      /* Buffer Data 1, bit 2 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT13_bit :1;                                      /* Buffer Data 1, bit 3 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT14_bit :1;                                      /* Buffer Data 1, bit 4 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT15_bit :1;                                      /* Buffer Data 1, bit 5 */ /*Warning: bit name is duplicated with register name*/
    word DACDAT16    :1;                                       /* Buffer Data 1, bit 6 */
    word DACDAT17    :1;                                       /* Buffer Data 1, bit 7 */
    word DACDAT18    :1;                                       /* Buffer Data 1, bit 8 */
    word DACDAT19    :1;                                       /* Buffer Data 1, bit 9 */
    word DACDAT110   :1;                                       /* Buffer Data 1, bit 10 */
    word DACDAT111   :1;                                       /* Buffer Data 1, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_10 :10;
    word grpDACDAT1_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT1STR;
extern volatile DACDAT1STR _DACDAT1 @0xFFFF8012;
#define DACDAT1                         _DACDAT1.Word
#define DACDAT1_DACDAT10                _DACDAT1.Bits.DACDAT10_bit
#define DACDAT1_DACDAT11                _DACDAT1.Bits.DACDAT11_bit
#define DACDAT1_DACDAT12                _DACDAT1.Bits.DACDAT12_bit
#define DACDAT1_DACDAT13                _DACDAT1.Bits.DACDAT13_bit
#define DACDAT1_DACDAT14                _DACDAT1.Bits.DACDAT14_bit
#define DACDAT1_DACDAT15                _DACDAT1.Bits.DACDAT15_bit
#define DACDAT1_DACDAT16                _DACDAT1.Bits.DACDAT16
#define DACDAT1_DACDAT17                _DACDAT1.Bits.DACDAT17
#define DACDAT1_DACDAT18                _DACDAT1.Bits.DACDAT18
#define DACDAT1_DACDAT19                _DACDAT1.Bits.DACDAT19
#define DACDAT1_DACDAT110               _DACDAT1.Bits.DACDAT110
#define DACDAT1_DACDAT111               _DACDAT1.Bits.DACDAT111
#define DACDAT1_DACDAT_10               _DACDAT1.MergedBits.grpDACDAT_10
#define DACDAT1_DACDAT1_10              _DACDAT1.MergedBits.grpDACDAT1_10
#define DACDAT1_DACDAT                  DACDAT1_DACDAT_10

#define DACDAT1_DACDAT10_MASK           1U
#define DACDAT1_DACDAT11_MASK           2U
#define DACDAT1_DACDAT12_MASK           4U
#define DACDAT1_DACDAT13_MASK           8U
#define DACDAT1_DACDAT14_MASK           16U
#define DACDAT1_DACDAT15_MASK           32U
#define DACDAT1_DACDAT16_MASK           64U
#define DACDAT1_DACDAT17_MASK           128U
#define DACDAT1_DACDAT18_MASK           256U
#define DACDAT1_DACDAT19_MASK           512U
#define DACDAT1_DACDAT110_MASK          1024U
#define DACDAT1_DACDAT111_MASK          2048U
#define DACDAT1_DACDAT_10_MASK          1023U
#define DACDAT1_DACDAT_10_BITNUM        0U
#define DACDAT1_DACDAT1_10_MASK         3072U
#define DACDAT1_DACDAT1_10_BITNUM       10U


/*** DACDAT2 - DAC Data 2 Register; 0xFFFF8014 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT2H - DAC Data 2 High Register; 0xFFFF8014 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT28    :1;                                       /* Buffer Data 2 High, bit 8 */
        byte DACDAT29    :1;                                       /* Buffer Data 2 High, bit 9 */
        byte DACDAT210   :1;                                       /* Buffer Data 2 High, bit 10 */
        byte DACDAT211   :1;                                       /* Buffer Data 2 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_28 :2;
        byte grpDACDAT2_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT2HSTR;
    #define DACDAT2H                    _DACDAT2.Overlap_STR.DACDAT2HSTR.Byte
    #define DACDAT2H_DACDAT28           _DACDAT2.Overlap_STR.DACDAT2HSTR.Bits.DACDAT28
    #define DACDAT2H_DACDAT29           _DACDAT2.Overlap_STR.DACDAT2HSTR.Bits.DACDAT29
    #define DACDAT2H_DACDAT210          _DACDAT2.Overlap_STR.DACDAT2HSTR.Bits.DACDAT210
    #define DACDAT2H_DACDAT211          _DACDAT2.Overlap_STR.DACDAT2HSTR.Bits.DACDAT211
    #define DACDAT2H_DACDAT_28          _DACDAT2.Overlap_STR.DACDAT2HSTR.MergedBits.grpDACDAT_28
    #define DACDAT2H_DACDAT2_10         _DACDAT2.Overlap_STR.DACDAT2HSTR.MergedBits.grpDACDAT2_10
    #define DACDAT2H_DACDAT             DACDAT2H_DACDAT_28
    #define DACDAT2H_DACDAT2            DACDAT2H_DACDAT2_10
    
    #define DACDAT2H_DACDAT28_MASK      1U
    #define DACDAT2H_DACDAT29_MASK      2U
    #define DACDAT2H_DACDAT210_MASK     4U
    #define DACDAT2H_DACDAT211_MASK     8U
    #define DACDAT2H_DACDAT_28_MASK     3U
    #define DACDAT2H_DACDAT_28_BITNUM   0U
    #define DACDAT2H_DACDAT2_10_MASK    12U
    #define DACDAT2H_DACDAT2_10_BITNUM  2U
    

    /*** DACDAT2L - DAC Data 2 Low Register; 0xFFFF8015 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT20    :1;                                       /* Buffer Data 2 Low, bit 0 */
        byte DACDAT21    :1;                                       /* Buffer Data 2 Low, bit 1 */
        byte DACDAT22    :1;                                       /* Buffer Data 2 Low, bit 2 */
        byte DACDAT23    :1;                                       /* Buffer Data 2 Low, bit 3 */
        byte DACDAT24    :1;                                       /* Buffer Data 2 Low, bit 4 */
        byte DACDAT25    :1;                                       /* Buffer Data 2 Low, bit 5 */
        byte DACDAT26    :1;                                       /* Buffer Data 2 Low, bit 6 */
        byte DACDAT27    :1;                                       /* Buffer Data 2 Low, bit 7 */
      } Bits;
    } DACDAT2LSTR;
    #define DACDAT2L                    _DACDAT2.Overlap_STR.DACDAT2LSTR.Byte
    #define DACDAT2L_DACDAT20           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT20
    #define DACDAT2L_DACDAT21           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT21
    #define DACDAT2L_DACDAT22           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT22
    #define DACDAT2L_DACDAT23           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT23
    #define DACDAT2L_DACDAT24           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT24
    #define DACDAT2L_DACDAT25           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT25
    #define DACDAT2L_DACDAT26           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT26
    #define DACDAT2L_DACDAT27           _DACDAT2.Overlap_STR.DACDAT2LSTR.Bits.DACDAT27
    
    #define DACDAT2L_DACDAT20_MASK      1U
    #define DACDAT2L_DACDAT21_MASK      2U
    #define DACDAT2L_DACDAT22_MASK      4U
    #define DACDAT2L_DACDAT23_MASK      8U
    #define DACDAT2L_DACDAT24_MASK      16U
    #define DACDAT2L_DACDAT25_MASK      32U
    #define DACDAT2L_DACDAT26_MASK      64U
    #define DACDAT2L_DACDAT27_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT20    :1;                                       /* Buffer Data 2, bit 0 */
    word DACDAT21    :1;                                       /* Buffer Data 2, bit 1 */
    word DACDAT22    :1;                                       /* Buffer Data 2, bit 2 */
    word DACDAT23    :1;                                       /* Buffer Data 2, bit 3 */
    word DACDAT24    :1;                                       /* Buffer Data 2, bit 4 */
    word DACDAT25    :1;                                       /* Buffer Data 2, bit 5 */
    word DACDAT26    :1;                                       /* Buffer Data 2, bit 6 */
    word DACDAT27    :1;                                       /* Buffer Data 2, bit 7 */
    word DACDAT28    :1;                                       /* Buffer Data 2, bit 8 */
    word DACDAT29    :1;                                       /* Buffer Data 2, bit 9 */
    word DACDAT210   :1;                                       /* Buffer Data 2, bit 10 */
    word DACDAT211   :1;                                       /* Buffer Data 2, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_20 :10;
    word grpDACDAT2_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT2STR;
extern volatile DACDAT2STR _DACDAT2 @0xFFFF8014;
#define DACDAT2                         _DACDAT2.Word
#define DACDAT2_DACDAT20                _DACDAT2.Bits.DACDAT20
#define DACDAT2_DACDAT21                _DACDAT2.Bits.DACDAT21
#define DACDAT2_DACDAT22                _DACDAT2.Bits.DACDAT22
#define DACDAT2_DACDAT23                _DACDAT2.Bits.DACDAT23
#define DACDAT2_DACDAT24                _DACDAT2.Bits.DACDAT24
#define DACDAT2_DACDAT25                _DACDAT2.Bits.DACDAT25
#define DACDAT2_DACDAT26                _DACDAT2.Bits.DACDAT26
#define DACDAT2_DACDAT27                _DACDAT2.Bits.DACDAT27
#define DACDAT2_DACDAT28                _DACDAT2.Bits.DACDAT28
#define DACDAT2_DACDAT29                _DACDAT2.Bits.DACDAT29
#define DACDAT2_DACDAT210               _DACDAT2.Bits.DACDAT210
#define DACDAT2_DACDAT211               _DACDAT2.Bits.DACDAT211
#define DACDAT2_DACDAT_20               _DACDAT2.MergedBits.grpDACDAT_20
#define DACDAT2_DACDAT2_10              _DACDAT2.MergedBits.grpDACDAT2_10
#define DACDAT2_DACDAT                  DACDAT2_DACDAT_20

#define DACDAT2_DACDAT20_MASK           1U
#define DACDAT2_DACDAT21_MASK           2U
#define DACDAT2_DACDAT22_MASK           4U
#define DACDAT2_DACDAT23_MASK           8U
#define DACDAT2_DACDAT24_MASK           16U
#define DACDAT2_DACDAT25_MASK           32U
#define DACDAT2_DACDAT26_MASK           64U
#define DACDAT2_DACDAT27_MASK           128U
#define DACDAT2_DACDAT28_MASK           256U
#define DACDAT2_DACDAT29_MASK           512U
#define DACDAT2_DACDAT210_MASK          1024U
#define DACDAT2_DACDAT211_MASK          2048U
#define DACDAT2_DACDAT_20_MASK          1023U
#define DACDAT2_DACDAT_20_BITNUM        0U
#define DACDAT2_DACDAT2_10_MASK         3072U
#define DACDAT2_DACDAT2_10_BITNUM       10U


/*** DACDAT3 - DAC Data 3 Register; 0xFFFF8016 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT3H - DAC Data 3 High Register; 0xFFFF8016 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT38    :1;                                       /* Buffer Data 3 High, bit 8 */
        byte DACDAT39    :1;                                       /* Buffer Data 3 High, bit 9 */
        byte DACDAT310   :1;                                       /* Buffer Data 3 High, bit 10 */
        byte DACDAT311   :1;                                       /* Buffer Data 3 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_38 :2;
        byte grpDACDAT3_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT3HSTR;
    #define DACDAT3H                    _DACDAT3.Overlap_STR.DACDAT3HSTR.Byte
    #define DACDAT3H_DACDAT38           _DACDAT3.Overlap_STR.DACDAT3HSTR.Bits.DACDAT38
    #define DACDAT3H_DACDAT39           _DACDAT3.Overlap_STR.DACDAT3HSTR.Bits.DACDAT39
    #define DACDAT3H_DACDAT310          _DACDAT3.Overlap_STR.DACDAT3HSTR.Bits.DACDAT310
    #define DACDAT3H_DACDAT311          _DACDAT3.Overlap_STR.DACDAT3HSTR.Bits.DACDAT311
    #define DACDAT3H_DACDAT_38          _DACDAT3.Overlap_STR.DACDAT3HSTR.MergedBits.grpDACDAT_38
    #define DACDAT3H_DACDAT3_10         _DACDAT3.Overlap_STR.DACDAT3HSTR.MergedBits.grpDACDAT3_10
    #define DACDAT3H_DACDAT             DACDAT3H_DACDAT_38
    #define DACDAT3H_DACDAT3            DACDAT3H_DACDAT3_10
    
    #define DACDAT3H_DACDAT38_MASK      1U
    #define DACDAT3H_DACDAT39_MASK      2U
    #define DACDAT3H_DACDAT310_MASK     4U
    #define DACDAT3H_DACDAT311_MASK     8U
    #define DACDAT3H_DACDAT_38_MASK     3U
    #define DACDAT3H_DACDAT_38_BITNUM   0U
    #define DACDAT3H_DACDAT3_10_MASK    12U
    #define DACDAT3H_DACDAT3_10_BITNUM  2U
    

    /*** DACDAT3L - DAC Data 3 Low Register; 0xFFFF8017 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT30    :1;                                       /* Buffer Data 3 Low, bit 0 */
        byte DACDAT31    :1;                                       /* Buffer Data 3 Low, bit 1 */
        byte DACDAT32    :1;                                       /* Buffer Data 3 Low, bit 2 */
        byte DACDAT33    :1;                                       /* Buffer Data 3 Low, bit 3 */
        byte DACDAT34    :1;                                       /* Buffer Data 3 Low, bit 4 */
        byte DACDAT35    :1;                                       /* Buffer Data 3 Low, bit 5 */
        byte DACDAT36    :1;                                       /* Buffer Data 3 Low, bit 6 */
        byte DACDAT37    :1;                                       /* Buffer Data 3 Low, bit 7 */
      } Bits;
    } DACDAT3LSTR;
    #define DACDAT3L                    _DACDAT3.Overlap_STR.DACDAT3LSTR.Byte
    #define DACDAT3L_DACDAT30           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT30
    #define DACDAT3L_DACDAT31           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT31
    #define DACDAT3L_DACDAT32           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT32
    #define DACDAT3L_DACDAT33           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT33
    #define DACDAT3L_DACDAT34           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT34
    #define DACDAT3L_DACDAT35           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT35
    #define DACDAT3L_DACDAT36           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT36
    #define DACDAT3L_DACDAT37           _DACDAT3.Overlap_STR.DACDAT3LSTR.Bits.DACDAT37
    
    #define DACDAT3L_DACDAT30_MASK      1U
    #define DACDAT3L_DACDAT31_MASK      2U
    #define DACDAT3L_DACDAT32_MASK      4U
    #define DACDAT3L_DACDAT33_MASK      8U
    #define DACDAT3L_DACDAT34_MASK      16U
    #define DACDAT3L_DACDAT35_MASK      32U
    #define DACDAT3L_DACDAT36_MASK      64U
    #define DACDAT3L_DACDAT37_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT30    :1;                                       /* Buffer Data 3, bit 0 */
    word DACDAT31    :1;                                       /* Buffer Data 3, bit 1 */
    word DACDAT32    :1;                                       /* Buffer Data 3, bit 2 */
    word DACDAT33    :1;                                       /* Buffer Data 3, bit 3 */
    word DACDAT34    :1;                                       /* Buffer Data 3, bit 4 */
    word DACDAT35    :1;                                       /* Buffer Data 3, bit 5 */
    word DACDAT36    :1;                                       /* Buffer Data 3, bit 6 */
    word DACDAT37    :1;                                       /* Buffer Data 3, bit 7 */
    word DACDAT38    :1;                                       /* Buffer Data 3, bit 8 */
    word DACDAT39    :1;                                       /* Buffer Data 3, bit 9 */
    word DACDAT310   :1;                                       /* Buffer Data 3, bit 10 */
    word DACDAT311   :1;                                       /* Buffer Data 3, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_30 :10;
    word grpDACDAT3_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT3STR;
extern volatile DACDAT3STR _DACDAT3 @0xFFFF8016;
#define DACDAT3                         _DACDAT3.Word
#define DACDAT3_DACDAT30                _DACDAT3.Bits.DACDAT30
#define DACDAT3_DACDAT31                _DACDAT3.Bits.DACDAT31
#define DACDAT3_DACDAT32                _DACDAT3.Bits.DACDAT32
#define DACDAT3_DACDAT33                _DACDAT3.Bits.DACDAT33
#define DACDAT3_DACDAT34                _DACDAT3.Bits.DACDAT34
#define DACDAT3_DACDAT35                _DACDAT3.Bits.DACDAT35
#define DACDAT3_DACDAT36                _DACDAT3.Bits.DACDAT36
#define DACDAT3_DACDAT37                _DACDAT3.Bits.DACDAT37
#define DACDAT3_DACDAT38                _DACDAT3.Bits.DACDAT38
#define DACDAT3_DACDAT39                _DACDAT3.Bits.DACDAT39
#define DACDAT3_DACDAT310               _DACDAT3.Bits.DACDAT310
#define DACDAT3_DACDAT311               _DACDAT3.Bits.DACDAT311
#define DACDAT3_DACDAT_30               _DACDAT3.MergedBits.grpDACDAT_30
#define DACDAT3_DACDAT3_10              _DACDAT3.MergedBits.grpDACDAT3_10
#define DACDAT3_DACDAT                  DACDAT3_DACDAT_30

#define DACDAT3_DACDAT30_MASK           1U
#define DACDAT3_DACDAT31_MASK           2U
#define DACDAT3_DACDAT32_MASK           4U
#define DACDAT3_DACDAT33_MASK           8U
#define DACDAT3_DACDAT34_MASK           16U
#define DACDAT3_DACDAT35_MASK           32U
#define DACDAT3_DACDAT36_MASK           64U
#define DACDAT3_DACDAT37_MASK           128U
#define DACDAT3_DACDAT38_MASK           256U
#define DACDAT3_DACDAT39_MASK           512U
#define DACDAT3_DACDAT310_MASK          1024U
#define DACDAT3_DACDAT311_MASK          2048U
#define DACDAT3_DACDAT_30_MASK          1023U
#define DACDAT3_DACDAT_30_BITNUM        0U
#define DACDAT3_DACDAT3_10_MASK         3072U
#define DACDAT3_DACDAT3_10_BITNUM       10U


/*** DACDAT4 - DAC Data 4 Register; 0xFFFF8018 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT4H - DAC Data 4 High Register; 0xFFFF8018 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT48    :1;                                       /* Buffer Data 4 High, bit 8 */
        byte DACDAT49    :1;                                       /* Buffer Data 4 High, bit 9 */
        byte DACDAT410   :1;                                       /* Buffer Data 4 High, bit 10 */
        byte DACDAT411   :1;                                       /* Buffer Data 4 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_48 :2;
        byte grpDACDAT4_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT4HSTR;
    #define DACDAT4H                    _DACDAT4.Overlap_STR.DACDAT4HSTR.Byte
    #define DACDAT4H_DACDAT48           _DACDAT4.Overlap_STR.DACDAT4HSTR.Bits.DACDAT48
    #define DACDAT4H_DACDAT49           _DACDAT4.Overlap_STR.DACDAT4HSTR.Bits.DACDAT49
    #define DACDAT4H_DACDAT410          _DACDAT4.Overlap_STR.DACDAT4HSTR.Bits.DACDAT410
    #define DACDAT4H_DACDAT411          _DACDAT4.Overlap_STR.DACDAT4HSTR.Bits.DACDAT411
    #define DACDAT4H_DACDAT_48          _DACDAT4.Overlap_STR.DACDAT4HSTR.MergedBits.grpDACDAT_48
    #define DACDAT4H_DACDAT4_10         _DACDAT4.Overlap_STR.DACDAT4HSTR.MergedBits.grpDACDAT4_10
    #define DACDAT4H_DACDAT             DACDAT4H_DACDAT_48
    #define DACDAT4H_DACDAT4            DACDAT4H_DACDAT4_10
    
    #define DACDAT4H_DACDAT48_MASK      1U
    #define DACDAT4H_DACDAT49_MASK      2U
    #define DACDAT4H_DACDAT410_MASK     4U
    #define DACDAT4H_DACDAT411_MASK     8U
    #define DACDAT4H_DACDAT_48_MASK     3U
    #define DACDAT4H_DACDAT_48_BITNUM   0U
    #define DACDAT4H_DACDAT4_10_MASK    12U
    #define DACDAT4H_DACDAT4_10_BITNUM  2U
    

    /*** DACDAT4L - DAC Data 4 Low Register; 0xFFFF8019 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT40    :1;                                       /* Buffer Data 4 Low, bit 0 */
        byte DACDAT41    :1;                                       /* Buffer Data 4 Low, bit 1 */
        byte DACDAT42    :1;                                       /* Buffer Data 4 Low, bit 2 */
        byte DACDAT43    :1;                                       /* Buffer Data 4 Low, bit 3 */
        byte DACDAT44    :1;                                       /* Buffer Data 4 Low, bit 4 */
        byte DACDAT45    :1;                                       /* Buffer Data 4 Low, bit 5 */
        byte DACDAT46    :1;                                       /* Buffer Data 4 Low, bit 6 */
        byte DACDAT47    :1;                                       /* Buffer Data 4 Low, bit 7 */
      } Bits;
    } DACDAT4LSTR;
    #define DACDAT4L                    _DACDAT4.Overlap_STR.DACDAT4LSTR.Byte
    #define DACDAT4L_DACDAT40           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT40
    #define DACDAT4L_DACDAT41           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT41
    #define DACDAT4L_DACDAT42           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT42
    #define DACDAT4L_DACDAT43           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT43
    #define DACDAT4L_DACDAT44           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT44
    #define DACDAT4L_DACDAT45           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT45
    #define DACDAT4L_DACDAT46           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT46
    #define DACDAT4L_DACDAT47           _DACDAT4.Overlap_STR.DACDAT4LSTR.Bits.DACDAT47
    
    #define DACDAT4L_DACDAT40_MASK      1U
    #define DACDAT4L_DACDAT41_MASK      2U
    #define DACDAT4L_DACDAT42_MASK      4U
    #define DACDAT4L_DACDAT43_MASK      8U
    #define DACDAT4L_DACDAT44_MASK      16U
    #define DACDAT4L_DACDAT45_MASK      32U
    #define DACDAT4L_DACDAT46_MASK      64U
    #define DACDAT4L_DACDAT47_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT40    :1;                                       /* Buffer Data 3, bit 0 */
    word DACDAT41    :1;                                       /* Buffer Data 3, bit 1 */
    word DACDAT42    :1;                                       /* Buffer Data 3, bit 2 */
    word DACDAT43    :1;                                       /* Buffer Data 3, bit 3 */
    word DACDAT44    :1;                                       /* Buffer Data 3, bit 4 */
    word DACDAT45    :1;                                       /* Buffer Data 3, bit 5 */
    word DACDAT46    :1;                                       /* Buffer Data 3, bit 6 */
    word DACDAT47    :1;                                       /* Buffer Data 3, bit 7 */
    word DACDAT48    :1;                                       /* Buffer Data 3, bit 8 */
    word DACDAT49    :1;                                       /* Buffer Data 3, bit 9 */
    word DACDAT410   :1;                                       /* Buffer Data 3, bit 10 */
    word DACDAT411   :1;                                       /* Buffer Data 3, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_40 :10;
    word grpDACDAT4_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT4STR;
extern volatile DACDAT4STR _DACDAT4 @0xFFFF8018;
#define DACDAT4                         _DACDAT4.Word
#define DACDAT4_DACDAT40                _DACDAT4.Bits.DACDAT40
#define DACDAT4_DACDAT41                _DACDAT4.Bits.DACDAT41
#define DACDAT4_DACDAT42                _DACDAT4.Bits.DACDAT42
#define DACDAT4_DACDAT43                _DACDAT4.Bits.DACDAT43
#define DACDAT4_DACDAT44                _DACDAT4.Bits.DACDAT44
#define DACDAT4_DACDAT45                _DACDAT4.Bits.DACDAT45
#define DACDAT4_DACDAT46                _DACDAT4.Bits.DACDAT46
#define DACDAT4_DACDAT47                _DACDAT4.Bits.DACDAT47
#define DACDAT4_DACDAT48                _DACDAT4.Bits.DACDAT48
#define DACDAT4_DACDAT49                _DACDAT4.Bits.DACDAT49
#define DACDAT4_DACDAT410               _DACDAT4.Bits.DACDAT410
#define DACDAT4_DACDAT411               _DACDAT4.Bits.DACDAT411
#define DACDAT4_DACDAT_40               _DACDAT4.MergedBits.grpDACDAT_40
#define DACDAT4_DACDAT4_10              _DACDAT4.MergedBits.grpDACDAT4_10
#define DACDAT4_DACDAT                  DACDAT4_DACDAT_40

#define DACDAT4_DACDAT40_MASK           1U
#define DACDAT4_DACDAT41_MASK           2U
#define DACDAT4_DACDAT42_MASK           4U
#define DACDAT4_DACDAT43_MASK           8U
#define DACDAT4_DACDAT44_MASK           16U
#define DACDAT4_DACDAT45_MASK           32U
#define DACDAT4_DACDAT46_MASK           64U
#define DACDAT4_DACDAT47_MASK           128U
#define DACDAT4_DACDAT48_MASK           256U
#define DACDAT4_DACDAT49_MASK           512U
#define DACDAT4_DACDAT410_MASK          1024U
#define DACDAT4_DACDAT411_MASK          2048U
#define DACDAT4_DACDAT_40_MASK          1023U
#define DACDAT4_DACDAT_40_BITNUM        0U
#define DACDAT4_DACDAT4_10_MASK         3072U
#define DACDAT4_DACDAT4_10_BITNUM       10U


/*** DACDAT5 - DAC Data 5 Register; 0xFFFF801A ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT5H - DAC Data 5 High Register; 0xFFFF801A ***/
    union {
      byte Byte;
      struct {
        byte DACDAT58    :1;                                       /* Buffer Data 5 High, bit 8 */
        byte DACDAT59    :1;                                       /* Buffer Data 5 High, bit 9 */
        byte DACDAT510   :1;                                       /* Buffer Data 5 High, bit 10 */
        byte DACDAT511   :1;                                       /* Buffer Data 5 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_58 :2;
        byte grpDACDAT5_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT5HSTR;
    #define DACDAT5H                    _DACDAT5.Overlap_STR.DACDAT5HSTR.Byte
    #define DACDAT5H_DACDAT58           _DACDAT5.Overlap_STR.DACDAT5HSTR.Bits.DACDAT58
    #define DACDAT5H_DACDAT59           _DACDAT5.Overlap_STR.DACDAT5HSTR.Bits.DACDAT59
    #define DACDAT5H_DACDAT510          _DACDAT5.Overlap_STR.DACDAT5HSTR.Bits.DACDAT510
    #define DACDAT5H_DACDAT511          _DACDAT5.Overlap_STR.DACDAT5HSTR.Bits.DACDAT511
    #define DACDAT5H_DACDAT_58          _DACDAT5.Overlap_STR.DACDAT5HSTR.MergedBits.grpDACDAT_58
    #define DACDAT5H_DACDAT5_10         _DACDAT5.Overlap_STR.DACDAT5HSTR.MergedBits.grpDACDAT5_10
    #define DACDAT5H_DACDAT             DACDAT5H_DACDAT_58
    #define DACDAT5H_DACDAT5            DACDAT5H_DACDAT5_10
    
    #define DACDAT5H_DACDAT58_MASK      1U
    #define DACDAT5H_DACDAT59_MASK      2U
    #define DACDAT5H_DACDAT510_MASK     4U
    #define DACDAT5H_DACDAT511_MASK     8U
    #define DACDAT5H_DACDAT_58_MASK     3U
    #define DACDAT5H_DACDAT_58_BITNUM   0U
    #define DACDAT5H_DACDAT5_10_MASK    12U
    #define DACDAT5H_DACDAT5_10_BITNUM  2U
    

    /*** DACDAT5L - DAC Data 5 Low Register; 0xFFFF801B ***/
    union {
      byte Byte;
      struct {
        byte DACDAT50    :1;                                       /* Buffer Data 5 Low, bit 0 */
        byte DACDAT51    :1;                                       /* Buffer Data 5 Low, bit 1 */
        byte DACDAT52    :1;                                       /* Buffer Data 5 Low, bit 2 */
        byte DACDAT53    :1;                                       /* Buffer Data 5 Low, bit 3 */
        byte DACDAT54    :1;                                       /* Buffer Data 5 Low, bit 4 */
        byte DACDAT55    :1;                                       /* Buffer Data 5 Low, bit 5 */
        byte DACDAT56    :1;                                       /* Buffer Data 5 Low, bit 6 */
        byte DACDAT57    :1;                                       /* Buffer Data 5 Low, bit 7 */
      } Bits;
    } DACDAT5LSTR;
    #define DACDAT5L                    _DACDAT5.Overlap_STR.DACDAT5LSTR.Byte
    #define DACDAT5L_DACDAT50           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT50
    #define DACDAT5L_DACDAT51           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT51
    #define DACDAT5L_DACDAT52           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT52
    #define DACDAT5L_DACDAT53           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT53
    #define DACDAT5L_DACDAT54           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT54
    #define DACDAT5L_DACDAT55           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT55
    #define DACDAT5L_DACDAT56           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT56
    #define DACDAT5L_DACDAT57           _DACDAT5.Overlap_STR.DACDAT5LSTR.Bits.DACDAT57
    
    #define DACDAT5L_DACDAT50_MASK      1U
    #define DACDAT5L_DACDAT51_MASK      2U
    #define DACDAT5L_DACDAT52_MASK      4U
    #define DACDAT5L_DACDAT53_MASK      8U
    #define DACDAT5L_DACDAT54_MASK      16U
    #define DACDAT5L_DACDAT55_MASK      32U
    #define DACDAT5L_DACDAT56_MASK      64U
    #define DACDAT5L_DACDAT57_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT50    :1;                                       /* Buffer Data 5, bit 0 */
    word DACDAT51    :1;                                       /* Buffer Data 5, bit 1 */
    word DACDAT52    :1;                                       /* Buffer Data 5, bit 2 */
    word DACDAT53    :1;                                       /* Buffer Data 5, bit 3 */
    word DACDAT54    :1;                                       /* Buffer Data 5, bit 4 */
    word DACDAT55    :1;                                       /* Buffer Data 5, bit 5 */
    word DACDAT56    :1;                                       /* Buffer Data 5, bit 6 */
    word DACDAT57    :1;                                       /* Buffer Data 5, bit 7 */
    word DACDAT58    :1;                                       /* Buffer Data 5, bit 8 */
    word DACDAT59    :1;                                       /* Buffer Data 5, bit 9 */
    word DACDAT510   :1;                                       /* Buffer Data 5, bit 10 */
    word DACDAT511   :1;                                       /* Buffer Data 5, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_50 :10;
    word grpDACDAT5_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT5STR;
extern volatile DACDAT5STR _DACDAT5 @0xFFFF801A;
#define DACDAT5                         _DACDAT5.Word
#define DACDAT5_DACDAT50                _DACDAT5.Bits.DACDAT50
#define DACDAT5_DACDAT51                _DACDAT5.Bits.DACDAT51
#define DACDAT5_DACDAT52                _DACDAT5.Bits.DACDAT52
#define DACDAT5_DACDAT53                _DACDAT5.Bits.DACDAT53
#define DACDAT5_DACDAT54                _DACDAT5.Bits.DACDAT54
#define DACDAT5_DACDAT55                _DACDAT5.Bits.DACDAT55
#define DACDAT5_DACDAT56                _DACDAT5.Bits.DACDAT56
#define DACDAT5_DACDAT57                _DACDAT5.Bits.DACDAT57
#define DACDAT5_DACDAT58                _DACDAT5.Bits.DACDAT58
#define DACDAT5_DACDAT59                _DACDAT5.Bits.DACDAT59
#define DACDAT5_DACDAT510               _DACDAT5.Bits.DACDAT510
#define DACDAT5_DACDAT511               _DACDAT5.Bits.DACDAT511
#define DACDAT5_DACDAT_50               _DACDAT5.MergedBits.grpDACDAT_50
#define DACDAT5_DACDAT5_10              _DACDAT5.MergedBits.grpDACDAT5_10
#define DACDAT5_DACDAT                  DACDAT5_DACDAT_50

#define DACDAT5_DACDAT50_MASK           1U
#define DACDAT5_DACDAT51_MASK           2U
#define DACDAT5_DACDAT52_MASK           4U
#define DACDAT5_DACDAT53_MASK           8U
#define DACDAT5_DACDAT54_MASK           16U
#define DACDAT5_DACDAT55_MASK           32U
#define DACDAT5_DACDAT56_MASK           64U
#define DACDAT5_DACDAT57_MASK           128U
#define DACDAT5_DACDAT58_MASK           256U
#define DACDAT5_DACDAT59_MASK           512U
#define DACDAT5_DACDAT510_MASK          1024U
#define DACDAT5_DACDAT511_MASK          2048U
#define DACDAT5_DACDAT_50_MASK          1023U
#define DACDAT5_DACDAT_50_BITNUM        0U
#define DACDAT5_DACDAT5_10_MASK         3072U
#define DACDAT5_DACDAT5_10_BITNUM       10U


/*** DACDAT6 - DAC Data 6 Register; 0xFFFF801C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT6H - DAC Data 6 High Register; 0xFFFF801C ***/
    union {
      byte Byte;
      struct {
        byte DACDAT68    :1;                                       /* Buffer Data 6 High, bit 8 */
        byte DACDAT69    :1;                                       /* Buffer Data 6 High, bit 9 */
        byte DACDAT610   :1;                                       /* Buffer Data 6 High, bit 10 */
        byte DACDAT611   :1;                                       /* Buffer Data 6 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_68 :2;
        byte grpDACDAT6_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT6HSTR;
    #define DACDAT6H                    _DACDAT6.Overlap_STR.DACDAT6HSTR.Byte
    #define DACDAT6H_DACDAT68           _DACDAT6.Overlap_STR.DACDAT6HSTR.Bits.DACDAT68
    #define DACDAT6H_DACDAT69           _DACDAT6.Overlap_STR.DACDAT6HSTR.Bits.DACDAT69
    #define DACDAT6H_DACDAT610          _DACDAT6.Overlap_STR.DACDAT6HSTR.Bits.DACDAT610
    #define DACDAT6H_DACDAT611          _DACDAT6.Overlap_STR.DACDAT6HSTR.Bits.DACDAT611
    #define DACDAT6H_DACDAT_68          _DACDAT6.Overlap_STR.DACDAT6HSTR.MergedBits.grpDACDAT_68
    #define DACDAT6H_DACDAT6_10         _DACDAT6.Overlap_STR.DACDAT6HSTR.MergedBits.grpDACDAT6_10
    #define DACDAT6H_DACDAT             DACDAT6H_DACDAT_68
    #define DACDAT6H_DACDAT6            DACDAT6H_DACDAT6_10
    
    #define DACDAT6H_DACDAT68_MASK      1U
    #define DACDAT6H_DACDAT69_MASK      2U
    #define DACDAT6H_DACDAT610_MASK     4U
    #define DACDAT6H_DACDAT611_MASK     8U
    #define DACDAT6H_DACDAT_68_MASK     3U
    #define DACDAT6H_DACDAT_68_BITNUM   0U
    #define DACDAT6H_DACDAT6_10_MASK    12U
    #define DACDAT6H_DACDAT6_10_BITNUM  2U
    

    /*** DACDAT6L - DAC Data 6 Low Register; 0xFFFF801D ***/
    union {
      byte Byte;
      struct {
        byte DACDAT60    :1;                                       /* Buffer Data 6 Low, bit 0 */
        byte DACDAT61    :1;                                       /* Buffer Data 6 Low, bit 1 */
        byte DACDAT62    :1;                                       /* Buffer Data 6 Low, bit 2 */
        byte DACDAT63    :1;                                       /* Buffer Data 6 Low, bit 3 */
        byte DACDAT64    :1;                                       /* Buffer Data 6 Low, bit 4 */
        byte DACDAT65    :1;                                       /* Buffer Data 6 Low, bit 5 */
        byte DACDAT66    :1;                                       /* Buffer Data 6 Low, bit 6 */
        byte DACDAT67    :1;                                       /* Buffer Data 6 Low, bit 7 */
      } Bits;
    } DACDAT6LSTR;
    #define DACDAT6L                    _DACDAT6.Overlap_STR.DACDAT6LSTR.Byte
    #define DACDAT6L_DACDAT60           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT60
    #define DACDAT6L_DACDAT61           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT61
    #define DACDAT6L_DACDAT62           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT62
    #define DACDAT6L_DACDAT63           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT63
    #define DACDAT6L_DACDAT64           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT64
    #define DACDAT6L_DACDAT65           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT65
    #define DACDAT6L_DACDAT66           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT66
    #define DACDAT6L_DACDAT67           _DACDAT6.Overlap_STR.DACDAT6LSTR.Bits.DACDAT67
    
    #define DACDAT6L_DACDAT60_MASK      1U
    #define DACDAT6L_DACDAT61_MASK      2U
    #define DACDAT6L_DACDAT62_MASK      4U
    #define DACDAT6L_DACDAT63_MASK      8U
    #define DACDAT6L_DACDAT64_MASK      16U
    #define DACDAT6L_DACDAT65_MASK      32U
    #define DACDAT6L_DACDAT66_MASK      64U
    #define DACDAT6L_DACDAT67_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT60    :1;                                       /* Buffer Data 6, bit 0 */
    word DACDAT61    :1;                                       /* Buffer Data 6, bit 1 */
    word DACDAT62    :1;                                       /* Buffer Data 6, bit 2 */
    word DACDAT63    :1;                                       /* Buffer Data 6, bit 3 */
    word DACDAT64    :1;                                       /* Buffer Data 6, bit 4 */
    word DACDAT65    :1;                                       /* Buffer Data 6, bit 5 */
    word DACDAT66    :1;                                       /* Buffer Data 6, bit 6 */
    word DACDAT67    :1;                                       /* Buffer Data 6, bit 7 */
    word DACDAT68    :1;                                       /* Buffer Data 6, bit 8 */
    word DACDAT69    :1;                                       /* Buffer Data 6, bit 9 */
    word DACDAT610   :1;                                       /* Buffer Data 6, bit 10 */
    word DACDAT611   :1;                                       /* Buffer Data 6, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_60 :10;
    word grpDACDAT6_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT6STR;
extern volatile DACDAT6STR _DACDAT6 @0xFFFF801C;
#define DACDAT6                         _DACDAT6.Word
#define DACDAT6_DACDAT60                _DACDAT6.Bits.DACDAT60
#define DACDAT6_DACDAT61                _DACDAT6.Bits.DACDAT61
#define DACDAT6_DACDAT62                _DACDAT6.Bits.DACDAT62
#define DACDAT6_DACDAT63                _DACDAT6.Bits.DACDAT63
#define DACDAT6_DACDAT64                _DACDAT6.Bits.DACDAT64
#define DACDAT6_DACDAT65                _DACDAT6.Bits.DACDAT65
#define DACDAT6_DACDAT66                _DACDAT6.Bits.DACDAT66
#define DACDAT6_DACDAT67                _DACDAT6.Bits.DACDAT67
#define DACDAT6_DACDAT68                _DACDAT6.Bits.DACDAT68
#define DACDAT6_DACDAT69                _DACDAT6.Bits.DACDAT69
#define DACDAT6_DACDAT610               _DACDAT6.Bits.DACDAT610
#define DACDAT6_DACDAT611               _DACDAT6.Bits.DACDAT611
#define DACDAT6_DACDAT_60               _DACDAT6.MergedBits.grpDACDAT_60
#define DACDAT6_DACDAT6_10              _DACDAT6.MergedBits.grpDACDAT6_10
#define DACDAT6_DACDAT                  DACDAT6_DACDAT_60

#define DACDAT6_DACDAT60_MASK           1U
#define DACDAT6_DACDAT61_MASK           2U
#define DACDAT6_DACDAT62_MASK           4U
#define DACDAT6_DACDAT63_MASK           8U
#define DACDAT6_DACDAT64_MASK           16U
#define DACDAT6_DACDAT65_MASK           32U
#define DACDAT6_DACDAT66_MASK           64U
#define DACDAT6_DACDAT67_MASK           128U
#define DACDAT6_DACDAT68_MASK           256U
#define DACDAT6_DACDAT69_MASK           512U
#define DACDAT6_DACDAT610_MASK          1024U
#define DACDAT6_DACDAT611_MASK          2048U
#define DACDAT6_DACDAT_60_MASK          1023U
#define DACDAT6_DACDAT_60_BITNUM        0U
#define DACDAT6_DACDAT6_10_MASK         3072U
#define DACDAT6_DACDAT6_10_BITNUM       10U


/*** DACDAT7 - DAC Data 7 Register; 0xFFFF801E ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT7H - DAC Data 7 High Register; 0xFFFF801E ***/
    union {
      byte Byte;
      struct {
        byte DACDAT78    :1;                                       /* Buffer Data 7 High, bit 8 */
        byte DACDAT79    :1;                                       /* Buffer Data 7 High, bit 9 */
        byte DACDAT710   :1;                                       /* Buffer Data 7 High, bit 10 */
        byte DACDAT711   :1;                                       /* Buffer Data 7 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_78 :2;
        byte grpDACDAT7_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT7HSTR;
    #define DACDAT7H                    _DACDAT7.Overlap_STR.DACDAT7HSTR.Byte
    #define DACDAT7H_DACDAT78           _DACDAT7.Overlap_STR.DACDAT7HSTR.Bits.DACDAT78
    #define DACDAT7H_DACDAT79           _DACDAT7.Overlap_STR.DACDAT7HSTR.Bits.DACDAT79
    #define DACDAT7H_DACDAT710          _DACDAT7.Overlap_STR.DACDAT7HSTR.Bits.DACDAT710
    #define DACDAT7H_DACDAT711          _DACDAT7.Overlap_STR.DACDAT7HSTR.Bits.DACDAT711
    #define DACDAT7H_DACDAT_78          _DACDAT7.Overlap_STR.DACDAT7HSTR.MergedBits.grpDACDAT_78
    #define DACDAT7H_DACDAT7_10         _DACDAT7.Overlap_STR.DACDAT7HSTR.MergedBits.grpDACDAT7_10
    #define DACDAT7H_DACDAT             DACDAT7H_DACDAT_78
    #define DACDAT7H_DACDAT7            DACDAT7H_DACDAT7_10
    
    #define DACDAT7H_DACDAT78_MASK      1U
    #define DACDAT7H_DACDAT79_MASK      2U
    #define DACDAT7H_DACDAT710_MASK     4U
    #define DACDAT7H_DACDAT711_MASK     8U
    #define DACDAT7H_DACDAT_78_MASK     3U
    #define DACDAT7H_DACDAT_78_BITNUM   0U
    #define DACDAT7H_DACDAT7_10_MASK    12U
    #define DACDAT7H_DACDAT7_10_BITNUM  2U
    

    /*** DACDAT7L - DAC Data 7 Low Register; 0xFFFF801F ***/
    union {
      byte Byte;
      struct {
        byte DACDAT70    :1;                                       /* Buffer Data 7 Low, bit 0 */
        byte DACDAT71    :1;                                       /* Buffer Data 7 Low, bit 1 */
        byte DACDAT72    :1;                                       /* Buffer Data 7 Low, bit 2 */
        byte DACDAT73    :1;                                       /* Buffer Data 7 Low, bit 3 */
        byte DACDAT74    :1;                                       /* Buffer Data 7 Low, bit 4 */
        byte DACDAT75    :1;                                       /* Buffer Data 7 Low, bit 5 */
        byte DACDAT76    :1;                                       /* Buffer Data 7 Low, bit 6 */
        byte DACDAT77    :1;                                       /* Buffer Data 7 Low, bit 7 */
      } Bits;
    } DACDAT7LSTR;
    #define DACDAT7L                    _DACDAT7.Overlap_STR.DACDAT7LSTR.Byte
    #define DACDAT7L_DACDAT70           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT70
    #define DACDAT7L_DACDAT71           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT71
    #define DACDAT7L_DACDAT72           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT72
    #define DACDAT7L_DACDAT73           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT73
    #define DACDAT7L_DACDAT74           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT74
    #define DACDAT7L_DACDAT75           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT75
    #define DACDAT7L_DACDAT76           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT76
    #define DACDAT7L_DACDAT77           _DACDAT7.Overlap_STR.DACDAT7LSTR.Bits.DACDAT77
    
    #define DACDAT7L_DACDAT70_MASK      1U
    #define DACDAT7L_DACDAT71_MASK      2U
    #define DACDAT7L_DACDAT72_MASK      4U
    #define DACDAT7L_DACDAT73_MASK      8U
    #define DACDAT7L_DACDAT74_MASK      16U
    #define DACDAT7L_DACDAT75_MASK      32U
    #define DACDAT7L_DACDAT76_MASK      64U
    #define DACDAT7L_DACDAT77_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT70    :1;                                       /* Buffer Data 7, bit 0 */
    word DACDAT71    :1;                                       /* Buffer Data 7, bit 1 */
    word DACDAT72    :1;                                       /* Buffer Data 7, bit 2 */
    word DACDAT73    :1;                                       /* Buffer Data 7, bit 3 */
    word DACDAT74    :1;                                       /* Buffer Data 7, bit 4 */
    word DACDAT75    :1;                                       /* Buffer Data 7, bit 5 */
    word DACDAT76    :1;                                       /* Buffer Data 7, bit 6 */
    word DACDAT77    :1;                                       /* Buffer Data 7, bit 7 */
    word DACDAT78    :1;                                       /* Buffer Data 7, bit 8 */
    word DACDAT79    :1;                                       /* Buffer Data 7, bit 9 */
    word DACDAT710   :1;                                       /* Buffer Data 7, bit 10 */
    word DACDAT711   :1;                                       /* Buffer Data 7, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_70 :10;
    word grpDACDAT7_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT7STR;
extern volatile DACDAT7STR _DACDAT7 @0xFFFF801E;
#define DACDAT7                         _DACDAT7.Word
#define DACDAT7_DACDAT70                _DACDAT7.Bits.DACDAT70
#define DACDAT7_DACDAT71                _DACDAT7.Bits.DACDAT71
#define DACDAT7_DACDAT72                _DACDAT7.Bits.DACDAT72
#define DACDAT7_DACDAT73                _DACDAT7.Bits.DACDAT73
#define DACDAT7_DACDAT74                _DACDAT7.Bits.DACDAT74
#define DACDAT7_DACDAT75                _DACDAT7.Bits.DACDAT75
#define DACDAT7_DACDAT76                _DACDAT7.Bits.DACDAT76
#define DACDAT7_DACDAT77                _DACDAT7.Bits.DACDAT77
#define DACDAT7_DACDAT78                _DACDAT7.Bits.DACDAT78
#define DACDAT7_DACDAT79                _DACDAT7.Bits.DACDAT79
#define DACDAT7_DACDAT710               _DACDAT7.Bits.DACDAT710
#define DACDAT7_DACDAT711               _DACDAT7.Bits.DACDAT711
#define DACDAT7_DACDAT_70               _DACDAT7.MergedBits.grpDACDAT_70
#define DACDAT7_DACDAT7_10              _DACDAT7.MergedBits.grpDACDAT7_10
#define DACDAT7_DACDAT                  DACDAT7_DACDAT_70

#define DACDAT7_DACDAT70_MASK           1U
#define DACDAT7_DACDAT71_MASK           2U
#define DACDAT7_DACDAT72_MASK           4U
#define DACDAT7_DACDAT73_MASK           8U
#define DACDAT7_DACDAT74_MASK           16U
#define DACDAT7_DACDAT75_MASK           32U
#define DACDAT7_DACDAT76_MASK           64U
#define DACDAT7_DACDAT77_MASK           128U
#define DACDAT7_DACDAT78_MASK           256U
#define DACDAT7_DACDAT79_MASK           512U
#define DACDAT7_DACDAT710_MASK          1024U
#define DACDAT7_DACDAT711_MASK          2048U
#define DACDAT7_DACDAT_70_MASK          1023U
#define DACDAT7_DACDAT_70_BITNUM        0U
#define DACDAT7_DACDAT7_10_MASK         3072U
#define DACDAT7_DACDAT7_10_BITNUM       10U


/*** DACDAT8 - DAC Data 8 Register; 0xFFFF8020 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT8H - DAC Data 8 High Register; 0xFFFF8020 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT88    :1;                                       /* Buffer Data 8 High, bit 8 */
        byte DACDAT89    :1;                                       /* Buffer Data 8 High, bit 9 */
        byte DACDAT810   :1;                                       /* Buffer Data 8 High, bit 10 */
        byte DACDAT811   :1;                                       /* Buffer Data 8 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_88 :2;
        byte grpDACDAT8_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT8HSTR;
    #define DACDAT8H                    _DACDAT8.Overlap_STR.DACDAT8HSTR.Byte
    #define DACDAT8H_DACDAT88           _DACDAT8.Overlap_STR.DACDAT8HSTR.Bits.DACDAT88
    #define DACDAT8H_DACDAT89           _DACDAT8.Overlap_STR.DACDAT8HSTR.Bits.DACDAT89
    #define DACDAT8H_DACDAT810          _DACDAT8.Overlap_STR.DACDAT8HSTR.Bits.DACDAT810
    #define DACDAT8H_DACDAT811          _DACDAT8.Overlap_STR.DACDAT8HSTR.Bits.DACDAT811
    #define DACDAT8H_DACDAT_88          _DACDAT8.Overlap_STR.DACDAT8HSTR.MergedBits.grpDACDAT_88
    #define DACDAT8H_DACDAT8_10         _DACDAT8.Overlap_STR.DACDAT8HSTR.MergedBits.grpDACDAT8_10
    #define DACDAT8H_DACDAT             DACDAT8H_DACDAT_88
    #define DACDAT8H_DACDAT8            DACDAT8H_DACDAT8_10
    
    #define DACDAT8H_DACDAT88_MASK      1U
    #define DACDAT8H_DACDAT89_MASK      2U
    #define DACDAT8H_DACDAT810_MASK     4U
    #define DACDAT8H_DACDAT811_MASK     8U
    #define DACDAT8H_DACDAT_88_MASK     3U
    #define DACDAT8H_DACDAT_88_BITNUM   0U
    #define DACDAT8H_DACDAT8_10_MASK    12U
    #define DACDAT8H_DACDAT8_10_BITNUM  2U
    

    /*** DACDAT8L - DAC Data 8 Low Register; 0xFFFF8021 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT80    :1;                                       /* Buffer Data 8 Low, bit 0 */
        byte DACDAT81    :1;                                       /* Buffer Data 8 Low, bit 1 */
        byte DACDAT82    :1;                                       /* Buffer Data 8 Low, bit 2 */
        byte DACDAT83    :1;                                       /* Buffer Data 8 Low, bit 3 */
        byte DACDAT84    :1;                                       /* Buffer Data 8 Low, bit 4 */
        byte DACDAT85    :1;                                       /* Buffer Data 8 Low, bit 5 */
        byte DACDAT86    :1;                                       /* Buffer Data 8 Low, bit 6 */
        byte DACDAT87    :1;                                       /* Buffer Data 8 Low, bit 7 */
      } Bits;
    } DACDAT8LSTR;
    #define DACDAT8L                    _DACDAT8.Overlap_STR.DACDAT8LSTR.Byte
    #define DACDAT8L_DACDAT80           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT80
    #define DACDAT8L_DACDAT81           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT81
    #define DACDAT8L_DACDAT82           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT82
    #define DACDAT8L_DACDAT83           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT83
    #define DACDAT8L_DACDAT84           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT84
    #define DACDAT8L_DACDAT85           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT85
    #define DACDAT8L_DACDAT86           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT86
    #define DACDAT8L_DACDAT87           _DACDAT8.Overlap_STR.DACDAT8LSTR.Bits.DACDAT87
    
    #define DACDAT8L_DACDAT80_MASK      1U
    #define DACDAT8L_DACDAT81_MASK      2U
    #define DACDAT8L_DACDAT82_MASK      4U
    #define DACDAT8L_DACDAT83_MASK      8U
    #define DACDAT8L_DACDAT84_MASK      16U
    #define DACDAT8L_DACDAT85_MASK      32U
    #define DACDAT8L_DACDAT86_MASK      64U
    #define DACDAT8L_DACDAT87_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT80    :1;                                       /* Buffer Data 8, bit 0 */
    word DACDAT81    :1;                                       /* Buffer Data 8, bit 1 */
    word DACDAT82    :1;                                       /* Buffer Data 8, bit 2 */
    word DACDAT83    :1;                                       /* Buffer Data 8, bit 3 */
    word DACDAT84    :1;                                       /* Buffer Data 8, bit 4 */
    word DACDAT85    :1;                                       /* Buffer Data 8, bit 5 */
    word DACDAT86    :1;                                       /* Buffer Data 8, bit 6 */
    word DACDAT87    :1;                                       /* Buffer Data 8, bit 7 */
    word DACDAT88    :1;                                       /* Buffer Data 8, bit 8 */
    word DACDAT89    :1;                                       /* Buffer Data 8, bit 9 */
    word DACDAT810   :1;                                       /* Buffer Data 8, bit 10 */
    word DACDAT811   :1;                                       /* Buffer Data 8, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_80 :10;
    word grpDACDAT8_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT8STR;
extern volatile DACDAT8STR _DACDAT8 @0xFFFF8020;
#define DACDAT8                         _DACDAT8.Word
#define DACDAT8_DACDAT80                _DACDAT8.Bits.DACDAT80
#define DACDAT8_DACDAT81                _DACDAT8.Bits.DACDAT81
#define DACDAT8_DACDAT82                _DACDAT8.Bits.DACDAT82
#define DACDAT8_DACDAT83                _DACDAT8.Bits.DACDAT83
#define DACDAT8_DACDAT84                _DACDAT8.Bits.DACDAT84
#define DACDAT8_DACDAT85                _DACDAT8.Bits.DACDAT85
#define DACDAT8_DACDAT86                _DACDAT8.Bits.DACDAT86
#define DACDAT8_DACDAT87                _DACDAT8.Bits.DACDAT87
#define DACDAT8_DACDAT88                _DACDAT8.Bits.DACDAT88
#define DACDAT8_DACDAT89                _DACDAT8.Bits.DACDAT89
#define DACDAT8_DACDAT810               _DACDAT8.Bits.DACDAT810
#define DACDAT8_DACDAT811               _DACDAT8.Bits.DACDAT811
#define DACDAT8_DACDAT_80               _DACDAT8.MergedBits.grpDACDAT_80
#define DACDAT8_DACDAT8_10              _DACDAT8.MergedBits.grpDACDAT8_10
#define DACDAT8_DACDAT                  DACDAT8_DACDAT_80

#define DACDAT8_DACDAT80_MASK           1U
#define DACDAT8_DACDAT81_MASK           2U
#define DACDAT8_DACDAT82_MASK           4U
#define DACDAT8_DACDAT83_MASK           8U
#define DACDAT8_DACDAT84_MASK           16U
#define DACDAT8_DACDAT85_MASK           32U
#define DACDAT8_DACDAT86_MASK           64U
#define DACDAT8_DACDAT87_MASK           128U
#define DACDAT8_DACDAT88_MASK           256U
#define DACDAT8_DACDAT89_MASK           512U
#define DACDAT8_DACDAT810_MASK          1024U
#define DACDAT8_DACDAT811_MASK          2048U
#define DACDAT8_DACDAT_80_MASK          1023U
#define DACDAT8_DACDAT_80_BITNUM        0U
#define DACDAT8_DACDAT8_10_MASK         3072U
#define DACDAT8_DACDAT8_10_BITNUM       10U


/*** DACDAT9 - DAC Data 9 Register; 0xFFFF8022 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT9H - DAC Data 9 High Register; 0xFFFF8022 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT98    :1;                                       /* Buffer Data 9 High, bit 8 */
        byte DACDAT99    :1;                                       /* Buffer Data 9 High, bit 9 */
        byte DACDAT910   :1;                                       /* Buffer Data 9 High, bit 10 */
        byte DACDAT911   :1;                                       /* Buffer Data 9 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT_98 :2;
        byte     :1;
        byte grpDACDAT9_11 :1;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT9HSTR;
    #define DACDAT9H                    _DACDAT9.Overlap_STR.DACDAT9HSTR.Byte
    #define DACDAT9H_DACDAT98           _DACDAT9.Overlap_STR.DACDAT9HSTR.Bits.DACDAT98
    #define DACDAT9H_DACDAT99           _DACDAT9.Overlap_STR.DACDAT9HSTR.Bits.DACDAT99
    #define DACDAT9H_DACDAT910          _DACDAT9.Overlap_STR.DACDAT9HSTR.Bits.DACDAT910
    #define DACDAT9H_DACDAT911          _DACDAT9.Overlap_STR.DACDAT9HSTR.Bits.DACDAT911
    #define DACDAT9H_DACDAT_98          _DACDAT9.Overlap_STR.DACDAT9HSTR.MergedBits.grpDACDAT_98
    #define DACDAT9H_DACDAT             DACDAT9H_DACDAT_98
    
    #define DACDAT9H_DACDAT98_MASK      1U
    #define DACDAT9H_DACDAT99_MASK      2U
    #define DACDAT9H_DACDAT910_MASK     4U
    #define DACDAT9H_DACDAT911_MASK     8U
    #define DACDAT9H_DACDAT_98_MASK     3U
    #define DACDAT9H_DACDAT_98_BITNUM   0U
    

    /*** DACDAT9L - DAC Data 9 Low Register; 0xFFFF8023 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT90    :1;                                       /* Buffer Data 9 Low, bit 0 */
        byte DACDAT91    :1;                                       /* Buffer Data 9 Low, bit 1 */
        byte DACDAT92    :1;                                       /* Buffer Data 9 Low, bit 2 */
        byte DACDAT93    :1;                                       /* Buffer Data 9 Low, bit 3 */
        byte DACDAT94    :1;                                       /* Buffer Data 9 Low, bit 4 */
        byte DACDAT95    :1;                                       /* Buffer Data 9 Low, bit 5 */
        byte DACDAT96    :1;                                       /* Buffer Data 9 Low, bit 6 */
        byte DACDAT97    :1;                                       /* Buffer Data 9 Low, bit 7 */
      } Bits;
    } DACDAT9LSTR;
    #define DACDAT9L                    _DACDAT9.Overlap_STR.DACDAT9LSTR.Byte
    #define DACDAT9L_DACDAT90           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT90
    #define DACDAT9L_DACDAT91           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT91
    #define DACDAT9L_DACDAT92           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT92
    #define DACDAT9L_DACDAT93           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT93
    #define DACDAT9L_DACDAT94           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT94
    #define DACDAT9L_DACDAT95           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT95
    #define DACDAT9L_DACDAT96           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT96
    #define DACDAT9L_DACDAT97           _DACDAT9.Overlap_STR.DACDAT9LSTR.Bits.DACDAT97
    
    #define DACDAT9L_DACDAT90_MASK      1U
    #define DACDAT9L_DACDAT91_MASK      2U
    #define DACDAT9L_DACDAT92_MASK      4U
    #define DACDAT9L_DACDAT93_MASK      8U
    #define DACDAT9L_DACDAT94_MASK      16U
    #define DACDAT9L_DACDAT95_MASK      32U
    #define DACDAT9L_DACDAT96_MASK      64U
    #define DACDAT9L_DACDAT97_MASK      128U
    
  } Overlap_STR;

  struct {
    word DACDAT90    :1;                                       /* Buffer Data 9, bit 0 */
    word DACDAT91    :1;                                       /* Buffer Data 9, bit 1 */
    word DACDAT92    :1;                                       /* Buffer Data 9, bit 2 */
    word DACDAT93    :1;                                       /* Buffer Data 9, bit 3 */
    word DACDAT94    :1;                                       /* Buffer Data 9, bit 4 */
    word DACDAT95    :1;                                       /* Buffer Data 9, bit 5 */
    word DACDAT96    :1;                                       /* Buffer Data 9, bit 6 */
    word DACDAT97    :1;                                       /* Buffer Data 9, bit 7 */
    word DACDAT98    :1;                                       /* Buffer Data 9, bit 8 */
    word DACDAT99    :1;                                       /* Buffer Data 9, bit 9 */
    word DACDAT910   :1;                                       /* Buffer Data 9, bit 10 */
    word DACDAT911   :1;                                       /* Buffer Data 9, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT_90 :10;
    word         :1;
    word grpDACDAT9_11 :1;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT9STR;
extern volatile DACDAT9STR _DACDAT9 @0xFFFF8022;
#define DACDAT9                         _DACDAT9.Word
#define DACDAT9_DACDAT90                _DACDAT9.Bits.DACDAT90
#define DACDAT9_DACDAT91                _DACDAT9.Bits.DACDAT91
#define DACDAT9_DACDAT92                _DACDAT9.Bits.DACDAT92
#define DACDAT9_DACDAT93                _DACDAT9.Bits.DACDAT93
#define DACDAT9_DACDAT94                _DACDAT9.Bits.DACDAT94
#define DACDAT9_DACDAT95                _DACDAT9.Bits.DACDAT95
#define DACDAT9_DACDAT96                _DACDAT9.Bits.DACDAT96
#define DACDAT9_DACDAT97                _DACDAT9.Bits.DACDAT97
#define DACDAT9_DACDAT98                _DACDAT9.Bits.DACDAT98
#define DACDAT9_DACDAT99                _DACDAT9.Bits.DACDAT99
#define DACDAT9_DACDAT910               _DACDAT9.Bits.DACDAT910
#define DACDAT9_DACDAT911               _DACDAT9.Bits.DACDAT911
#define DACDAT9_DACDAT_90               _DACDAT9.MergedBits.grpDACDAT_90
#define DACDAT9_DACDAT                  DACDAT9_DACDAT_90

#define DACDAT9_DACDAT90_MASK           1U
#define DACDAT9_DACDAT91_MASK           2U
#define DACDAT9_DACDAT92_MASK           4U
#define DACDAT9_DACDAT93_MASK           8U
#define DACDAT9_DACDAT94_MASK           16U
#define DACDAT9_DACDAT95_MASK           32U
#define DACDAT9_DACDAT96_MASK           64U
#define DACDAT9_DACDAT97_MASK           128U
#define DACDAT9_DACDAT98_MASK           256U
#define DACDAT9_DACDAT99_MASK           512U
#define DACDAT9_DACDAT910_MASK          1024U
#define DACDAT9_DACDAT911_MASK          2048U
#define DACDAT9_DACDAT_90_MASK          1023U
#define DACDAT9_DACDAT_90_BITNUM        0U


/*** DACDAT10 - DAC Data 10 Register; 0xFFFF8024 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT10H - DAC Data 10 High Register; 0xFFFF8024 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT108   :1;                                       /* Buffer Data 10 High, bit 8 */
        byte DACDAT109   :1;                                       /* Buffer Data 10 High, bit 9 */
        byte DACDAT1010  :1;                                       /* Buffer Data 10 High, bit 10 */
        byte DACDAT1011  :1;                                       /* Buffer Data 10 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT10_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT10HSTR;
    #define DACDAT10H                   _DACDAT10.Overlap_STR.DACDAT10HSTR.Byte
    #define DACDAT10H_DACDAT108         _DACDAT10.Overlap_STR.DACDAT10HSTR.Bits.DACDAT108
    #define DACDAT10H_DACDAT109         _DACDAT10.Overlap_STR.DACDAT10HSTR.Bits.DACDAT109
    #define DACDAT10H_DACDAT1010        _DACDAT10.Overlap_STR.DACDAT10HSTR.Bits.DACDAT1010
    #define DACDAT10H_DACDAT1011        _DACDAT10.Overlap_STR.DACDAT10HSTR.Bits.DACDAT1011
    #define DACDAT10H_DACDAT10_8        _DACDAT10.Overlap_STR.DACDAT10HSTR.MergedBits.grpDACDAT10_8
    #define DACDAT10H_DACDAT10          DACDAT10H_DACDAT10_8
    
    #define DACDAT10H_DACDAT108_MASK    1U
    #define DACDAT10H_DACDAT109_MASK    2U
    #define DACDAT10H_DACDAT1010_MASK   4U
    #define DACDAT10H_DACDAT1011_MASK   8U
    #define DACDAT10H_DACDAT10_8_MASK   15U
    #define DACDAT10H_DACDAT10_8_BITNUM 0U
    

    /*** DACDAT10L - DAC Data 10 Low Register; 0xFFFF8025 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT100   :1;                                       /* Buffer Data 10 Low, bit 0 */
        byte DACDAT101   :1;                                       /* Buffer Data 10 Low, bit 1 */
        byte DACDAT102   :1;                                       /* Buffer Data 10 Low, bit 2 */
        byte DACDAT103   :1;                                       /* Buffer Data 10 Low, bit 3 */
        byte DACDAT104   :1;                                       /* Buffer Data 10 Low, bit 4 */
        byte DACDAT105   :1;                                       /* Buffer Data 10 Low, bit 5 */
        byte DACDAT106   :1;                                       /* Buffer Data 10 Low, bit 6 */
        byte DACDAT107   :1;                                       /* Buffer Data 10 Low, bit 7 */
      } Bits;
    } DACDAT10LSTR;
    #define DACDAT10L                   _DACDAT10.Overlap_STR.DACDAT10LSTR.Byte
    #define DACDAT10L_DACDAT100         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT100
    #define DACDAT10L_DACDAT101         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT101
    #define DACDAT10L_DACDAT102         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT102
    #define DACDAT10L_DACDAT103         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT103
    #define DACDAT10L_DACDAT104         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT104
    #define DACDAT10L_DACDAT105         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT105
    #define DACDAT10L_DACDAT106         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT106
    #define DACDAT10L_DACDAT107         _DACDAT10.Overlap_STR.DACDAT10LSTR.Bits.DACDAT107
    
    #define DACDAT10L_DACDAT100_MASK    1U
    #define DACDAT10L_DACDAT101_MASK    2U
    #define DACDAT10L_DACDAT102_MASK    4U
    #define DACDAT10L_DACDAT103_MASK    8U
    #define DACDAT10L_DACDAT104_MASK    16U
    #define DACDAT10L_DACDAT105_MASK    32U
    #define DACDAT10L_DACDAT106_MASK    64U
    #define DACDAT10L_DACDAT107_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT100   :1;                                       /* Buffer Data 10, bit 0 */
    word DACDAT101   :1;                                       /* Buffer Data 10, bit 1 */
    word DACDAT102   :1;                                       /* Buffer Data 10, bit 2 */
    word DACDAT103   :1;                                       /* Buffer Data 10, bit 3 */
    word DACDAT104   :1;                                       /* Buffer Data 10, bit 4 */
    word DACDAT105   :1;                                       /* Buffer Data 10, bit 5 */
    word DACDAT106   :1;                                       /* Buffer Data 10, bit 6 */
    word DACDAT107   :1;                                       /* Buffer Data 10, bit 7 */
    word DACDAT108   :1;                                       /* Buffer Data 10, bit 8 */
    word DACDAT109   :1;                                       /* Buffer Data 10, bit 9 */
    word DACDAT1010  :1;                                       /* Buffer Data 10, bit 10 */
    word DACDAT1011  :1;                                       /* Buffer Data 10, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT10 :12;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT10STR;
extern volatile DACDAT10STR _DACDAT10 @0xFFFF8024;
#define DACDAT10                        _DACDAT10.Word
#define DACDAT10_DACDAT100              _DACDAT10.Bits.DACDAT100
#define DACDAT10_DACDAT101              _DACDAT10.Bits.DACDAT101
#define DACDAT10_DACDAT102              _DACDAT10.Bits.DACDAT102
#define DACDAT10_DACDAT103              _DACDAT10.Bits.DACDAT103
#define DACDAT10_DACDAT104              _DACDAT10.Bits.DACDAT104
#define DACDAT10_DACDAT105              _DACDAT10.Bits.DACDAT105
#define DACDAT10_DACDAT106              _DACDAT10.Bits.DACDAT106
#define DACDAT10_DACDAT107              _DACDAT10.Bits.DACDAT107
#define DACDAT10_DACDAT108              _DACDAT10.Bits.DACDAT108
#define DACDAT10_DACDAT109              _DACDAT10.Bits.DACDAT109
#define DACDAT10_DACDAT1010             _DACDAT10.Bits.DACDAT1010
#define DACDAT10_DACDAT1011             _DACDAT10.Bits.DACDAT1011
#define DACDAT10_DACDAT10               _DACDAT10.MergedBits.grpDACDAT10

#define DACDAT10_DACDAT100_MASK         1U
#define DACDAT10_DACDAT101_MASK         2U
#define DACDAT10_DACDAT102_MASK         4U
#define DACDAT10_DACDAT103_MASK         8U
#define DACDAT10_DACDAT104_MASK         16U
#define DACDAT10_DACDAT105_MASK         32U
#define DACDAT10_DACDAT106_MASK         64U
#define DACDAT10_DACDAT107_MASK         128U
#define DACDAT10_DACDAT108_MASK         256U
#define DACDAT10_DACDAT109_MASK         512U
#define DACDAT10_DACDAT1010_MASK        1024U
#define DACDAT10_DACDAT1011_MASK        2048U
#define DACDAT10_DACDAT10_MASK          4095U
#define DACDAT10_DACDAT10_BITNUM        0U


/*** DACDAT11 - DAC Data 11 Register; 0xFFFF8026 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT11H - DAC Data 11 High Register; 0xFFFF8026 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT118   :1;                                       /* Buffer Data 11 High, bit 8 */
        byte DACDAT119   :1;                                       /* Buffer Data 11 High, bit 9 */
        byte DACDAT1110  :1;                                       /* Buffer Data 11 High, bit 10 */
        byte DACDAT1111  :1;                                       /* Buffer Data 11 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT1_18 :2;
        byte grpDACDAT11_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT11HSTR;
    #define DACDAT11H                   _DACDAT11.Overlap_STR.DACDAT11HSTR.Byte
    #define DACDAT11H_DACDAT118         _DACDAT11.Overlap_STR.DACDAT11HSTR.Bits.DACDAT118
    #define DACDAT11H_DACDAT119         _DACDAT11.Overlap_STR.DACDAT11HSTR.Bits.DACDAT119
    #define DACDAT11H_DACDAT1110        _DACDAT11.Overlap_STR.DACDAT11HSTR.Bits.DACDAT1110
    #define DACDAT11H_DACDAT1111        _DACDAT11.Overlap_STR.DACDAT11HSTR.Bits.DACDAT1111
    #define DACDAT11H_DACDAT1_18        _DACDAT11.Overlap_STR.DACDAT11HSTR.MergedBits.grpDACDAT1_18
    #define DACDAT11H_DACDAT11_10       _DACDAT11.Overlap_STR.DACDAT11HSTR.MergedBits.grpDACDAT11_10
    #define DACDAT11H_DACDAT1           DACDAT11H_DACDAT1_18
    #define DACDAT11H_DACDAT11          DACDAT11H_DACDAT11_10
    
    #define DACDAT11H_DACDAT118_MASK    1U
    #define DACDAT11H_DACDAT119_MASK    2U
    #define DACDAT11H_DACDAT1110_MASK   4U
    #define DACDAT11H_DACDAT1111_MASK   8U
    #define DACDAT11H_DACDAT1_18_MASK   3U
    #define DACDAT11H_DACDAT1_18_BITNUM 0U
    #define DACDAT11H_DACDAT11_10_MASK  12U
    #define DACDAT11H_DACDAT11_10_BITNUM 2U
    

    /*** DACDAT11L - DAC Data 11 Low Register; 0xFFFF8027 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT110   :1;                                       /* Buffer Data 11 Low, bit 0 */
        byte DACDAT111   :1;                                       /* Buffer Data 11 Low, bit 1 */
        byte DACDAT112   :1;                                       /* Buffer Data 11 Low, bit 2 */
        byte DACDAT113   :1;                                       /* Buffer Data 11 Low, bit 3 */
        byte DACDAT114   :1;                                       /* Buffer Data 11 Low, bit 4 */
        byte DACDAT115   :1;                                       /* Buffer Data 11 Low, bit 5 */
        byte DACDAT116   :1;                                       /* Buffer Data 11 Low, bit 6 */
        byte DACDAT117   :1;                                       /* Buffer Data 11 Low, bit 7 */
      } Bits;
    } DACDAT11LSTR;
    #define DACDAT11L                   _DACDAT11.Overlap_STR.DACDAT11LSTR.Byte
    #define DACDAT11L_DACDAT110         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT110
    #define DACDAT11L_DACDAT111         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT111
    #define DACDAT11L_DACDAT112         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT112
    #define DACDAT11L_DACDAT113         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT113
    #define DACDAT11L_DACDAT114         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT114
    #define DACDAT11L_DACDAT115         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT115
    #define DACDAT11L_DACDAT116         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT116
    #define DACDAT11L_DACDAT117         _DACDAT11.Overlap_STR.DACDAT11LSTR.Bits.DACDAT117
    
    #define DACDAT11L_DACDAT110_MASK    1U
    #define DACDAT11L_DACDAT111_MASK    2U
    #define DACDAT11L_DACDAT112_MASK    4U
    #define DACDAT11L_DACDAT113_MASK    8U
    #define DACDAT11L_DACDAT114_MASK    16U
    #define DACDAT11L_DACDAT115_MASK    32U
    #define DACDAT11L_DACDAT116_MASK    64U
    #define DACDAT11L_DACDAT117_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT110   :1;                                       /* Buffer Data 11, bit 0 */
    word DACDAT111   :1;                                       /* Buffer Data 11, bit 1 */
    word DACDAT112   :1;                                       /* Buffer Data 11, bit 2 */
    word DACDAT113   :1;                                       /* Buffer Data 11, bit 3 */
    word DACDAT114   :1;                                       /* Buffer Data 11, bit 4 */
    word DACDAT115   :1;                                       /* Buffer Data 11, bit 5 */
    word DACDAT116   :1;                                       /* Buffer Data 11, bit 6 */
    word DACDAT117   :1;                                       /* Buffer Data 11, bit 7 */
    word DACDAT118   :1;                                       /* Buffer Data 11, bit 8 */
    word DACDAT119   :1;                                       /* Buffer Data 11, bit 9 */
    word DACDAT1110  :1;                                       /* Buffer Data 11, bit 10 */
    word DACDAT1111  :1;                                       /* Buffer Data 11, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT1_10 :10;
    word grpDACDAT11_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT11STR;
extern volatile DACDAT11STR _DACDAT11 @0xFFFF8026;
#define DACDAT11                        _DACDAT11.Word
#define DACDAT11_DACDAT110              _DACDAT11.Bits.DACDAT110
#define DACDAT11_DACDAT111              _DACDAT11.Bits.DACDAT111
#define DACDAT11_DACDAT112              _DACDAT11.Bits.DACDAT112
#define DACDAT11_DACDAT113              _DACDAT11.Bits.DACDAT113
#define DACDAT11_DACDAT114              _DACDAT11.Bits.DACDAT114
#define DACDAT11_DACDAT115              _DACDAT11.Bits.DACDAT115
#define DACDAT11_DACDAT116              _DACDAT11.Bits.DACDAT116
#define DACDAT11_DACDAT117              _DACDAT11.Bits.DACDAT117
#define DACDAT11_DACDAT118              _DACDAT11.Bits.DACDAT118
#define DACDAT11_DACDAT119              _DACDAT11.Bits.DACDAT119
#define DACDAT11_DACDAT1110             _DACDAT11.Bits.DACDAT1110
#define DACDAT11_DACDAT1111             _DACDAT11.Bits.DACDAT1111
#define DACDAT11_DACDAT1_10             _DACDAT11.MergedBits.grpDACDAT1_10
#define DACDAT11_DACDAT11_10            _DACDAT11.MergedBits.grpDACDAT11_10
#define DACDAT11_DACDAT1                DACDAT11_DACDAT1_10

#define DACDAT11_DACDAT110_MASK         1U
#define DACDAT11_DACDAT111_MASK         2U
#define DACDAT11_DACDAT112_MASK         4U
#define DACDAT11_DACDAT113_MASK         8U
#define DACDAT11_DACDAT114_MASK         16U
#define DACDAT11_DACDAT115_MASK         32U
#define DACDAT11_DACDAT116_MASK         64U
#define DACDAT11_DACDAT117_MASK         128U
#define DACDAT11_DACDAT118_MASK         256U
#define DACDAT11_DACDAT119_MASK         512U
#define DACDAT11_DACDAT1110_MASK        1024U
#define DACDAT11_DACDAT1111_MASK        2048U
#define DACDAT11_DACDAT1_10_MASK        1023U
#define DACDAT11_DACDAT1_10_BITNUM      0U
#define DACDAT11_DACDAT11_10_MASK       3072U
#define DACDAT11_DACDAT11_10_BITNUM     10U


/*** DACDAT12 - DAC Data 12 Register; 0xFFFF8028 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT12H - DAC Data 12 High Register; 0xFFFF8028 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT128   :1;                                       /* Buffer Data 12 High, bit 8 */
        byte DACDAT129   :1;                                       /* Buffer Data 12 High, bit 9 */
        byte DACDAT1210  :1;                                       /* Buffer Data 12 High, bit 10 */
        byte DACDAT1211  :1;                                       /* Buffer Data 12 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT1_28 :2;
        byte grpDACDAT12_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT12HSTR;
    #define DACDAT12H                   _DACDAT12.Overlap_STR.DACDAT12HSTR.Byte
    #define DACDAT12H_DACDAT128         _DACDAT12.Overlap_STR.DACDAT12HSTR.Bits.DACDAT128
    #define DACDAT12H_DACDAT129         _DACDAT12.Overlap_STR.DACDAT12HSTR.Bits.DACDAT129
    #define DACDAT12H_DACDAT1210        _DACDAT12.Overlap_STR.DACDAT12HSTR.Bits.DACDAT1210
    #define DACDAT12H_DACDAT1211        _DACDAT12.Overlap_STR.DACDAT12HSTR.Bits.DACDAT1211
    #define DACDAT12H_DACDAT1_28        _DACDAT12.Overlap_STR.DACDAT12HSTR.MergedBits.grpDACDAT1_28
    #define DACDAT12H_DACDAT12_10       _DACDAT12.Overlap_STR.DACDAT12HSTR.MergedBits.grpDACDAT12_10
    #define DACDAT12H_DACDAT1           DACDAT12H_DACDAT1_28
    #define DACDAT12H_DACDAT12          DACDAT12H_DACDAT12_10
    
    #define DACDAT12H_DACDAT128_MASK    1U
    #define DACDAT12H_DACDAT129_MASK    2U
    #define DACDAT12H_DACDAT1210_MASK   4U
    #define DACDAT12H_DACDAT1211_MASK   8U
    #define DACDAT12H_DACDAT1_28_MASK   3U
    #define DACDAT12H_DACDAT1_28_BITNUM 0U
    #define DACDAT12H_DACDAT12_10_MASK  12U
    #define DACDAT12H_DACDAT12_10_BITNUM 2U
    

    /*** DACDAT12L - DAC Data 12 Low Register; 0xFFFF8029 ***/
    union {
      byte Byte;
      struct {
        byte DACDAT120   :1;                                       /* Buffer Data 12 Low, bit 0 */
        byte DACDAT121   :1;                                       /* Buffer Data 12 Low, bit 1 */
        byte DACDAT122   :1;                                       /* Buffer Data 12 Low, bit 2 */
        byte DACDAT123   :1;                                       /* Buffer Data 12 Low, bit 3 */
        byte DACDAT124   :1;                                       /* Buffer Data 12 Low, bit 4 */
        byte DACDAT125   :1;                                       /* Buffer Data 12 Low, bit 5 */
        byte DACDAT126   :1;                                       /* Buffer Data 12 Low, bit 6 */
        byte DACDAT127   :1;                                       /* Buffer Data 12 Low, bit 7 */
      } Bits;
    } DACDAT12LSTR;
    #define DACDAT12L                   _DACDAT12.Overlap_STR.DACDAT12LSTR.Byte
    #define DACDAT12L_DACDAT120         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT120
    #define DACDAT12L_DACDAT121         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT121
    #define DACDAT12L_DACDAT122         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT122
    #define DACDAT12L_DACDAT123         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT123
    #define DACDAT12L_DACDAT124         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT124
    #define DACDAT12L_DACDAT125         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT125
    #define DACDAT12L_DACDAT126         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT126
    #define DACDAT12L_DACDAT127         _DACDAT12.Overlap_STR.DACDAT12LSTR.Bits.DACDAT127
    
    #define DACDAT12L_DACDAT120_MASK    1U
    #define DACDAT12L_DACDAT121_MASK    2U
    #define DACDAT12L_DACDAT122_MASK    4U
    #define DACDAT12L_DACDAT123_MASK    8U
    #define DACDAT12L_DACDAT124_MASK    16U
    #define DACDAT12L_DACDAT125_MASK    32U
    #define DACDAT12L_DACDAT126_MASK    64U
    #define DACDAT12L_DACDAT127_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT120   :1;                                       /* Buffer Data 12, bit 0 */
    word DACDAT121   :1;                                       /* Buffer Data 12, bit 1 */
    word DACDAT122   :1;                                       /* Buffer Data 12, bit 2 */
    word DACDAT123   :1;                                       /* Buffer Data 12, bit 3 */
    word DACDAT124   :1;                                       /* Buffer Data 12, bit 4 */
    word DACDAT125   :1;                                       /* Buffer Data 12, bit 5 */
    word DACDAT126   :1;                                       /* Buffer Data 12, bit 6 */
    word DACDAT127   :1;                                       /* Buffer Data 12, bit 7 */
    word DACDAT128   :1;                                       /* Buffer Data 12, bit 8 */
    word DACDAT129   :1;                                       /* Buffer Data 12, bit 9 */
    word DACDAT1210  :1;                                       /* Buffer Data 12, bit 10 */
    word DACDAT1211  :1;                                       /* Buffer Data 12, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT1_20 :10;
    word grpDACDAT12_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT12STR;
extern volatile DACDAT12STR _DACDAT12 @0xFFFF8028;
#define DACDAT12                        _DACDAT12.Word
#define DACDAT12_DACDAT120              _DACDAT12.Bits.DACDAT120
#define DACDAT12_DACDAT121              _DACDAT12.Bits.DACDAT121
#define DACDAT12_DACDAT122              _DACDAT12.Bits.DACDAT122
#define DACDAT12_DACDAT123              _DACDAT12.Bits.DACDAT123
#define DACDAT12_DACDAT124              _DACDAT12.Bits.DACDAT124
#define DACDAT12_DACDAT125              _DACDAT12.Bits.DACDAT125
#define DACDAT12_DACDAT126              _DACDAT12.Bits.DACDAT126
#define DACDAT12_DACDAT127              _DACDAT12.Bits.DACDAT127
#define DACDAT12_DACDAT128              _DACDAT12.Bits.DACDAT128
#define DACDAT12_DACDAT129              _DACDAT12.Bits.DACDAT129
#define DACDAT12_DACDAT1210             _DACDAT12.Bits.DACDAT1210
#define DACDAT12_DACDAT1211             _DACDAT12.Bits.DACDAT1211
#define DACDAT12_DACDAT1_20             _DACDAT12.MergedBits.grpDACDAT1_20
#define DACDAT12_DACDAT12_10            _DACDAT12.MergedBits.grpDACDAT12_10
#define DACDAT12_DACDAT1                DACDAT12_DACDAT1_20

#define DACDAT12_DACDAT120_MASK         1U
#define DACDAT12_DACDAT121_MASK         2U
#define DACDAT12_DACDAT122_MASK         4U
#define DACDAT12_DACDAT123_MASK         8U
#define DACDAT12_DACDAT124_MASK         16U
#define DACDAT12_DACDAT125_MASK         32U
#define DACDAT12_DACDAT126_MASK         64U
#define DACDAT12_DACDAT127_MASK         128U
#define DACDAT12_DACDAT128_MASK         256U
#define DACDAT12_DACDAT129_MASK         512U
#define DACDAT12_DACDAT1210_MASK        1024U
#define DACDAT12_DACDAT1211_MASK        2048U
#define DACDAT12_DACDAT1_20_MASK        1023U
#define DACDAT12_DACDAT1_20_BITNUM      0U
#define DACDAT12_DACDAT12_10_MASK       3072U
#define DACDAT12_DACDAT12_10_BITNUM     10U


/*** DACDAT13 - DAC Data 13 Register; 0xFFFF802A ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT13H - DAC Data 13 High Register; 0xFFFF802A ***/
    union {
      byte Byte;
      struct {
        byte DACDAT138   :1;                                       /* Buffer Data 13 High, bit 8 */
        byte DACDAT139   :1;                                       /* Buffer Data 13 High, bit 9 */
        byte DACDAT1310  :1;                                       /* Buffer Data 13 High, bit 10 */
        byte DACDAT1311  :1;                                       /* Buffer Data 13 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT1_38 :2;
        byte grpDACDAT13_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT13HSTR;
    #define DACDAT13H                   _DACDAT13.Overlap_STR.DACDAT13HSTR.Byte
    #define DACDAT13H_DACDAT138         _DACDAT13.Overlap_STR.DACDAT13HSTR.Bits.DACDAT138
    #define DACDAT13H_DACDAT139         _DACDAT13.Overlap_STR.DACDAT13HSTR.Bits.DACDAT139
    #define DACDAT13H_DACDAT1310        _DACDAT13.Overlap_STR.DACDAT13HSTR.Bits.DACDAT1310
    #define DACDAT13H_DACDAT1311        _DACDAT13.Overlap_STR.DACDAT13HSTR.Bits.DACDAT1311
    #define DACDAT13H_DACDAT1_38        _DACDAT13.Overlap_STR.DACDAT13HSTR.MergedBits.grpDACDAT1_38
    #define DACDAT13H_DACDAT13_10       _DACDAT13.Overlap_STR.DACDAT13HSTR.MergedBits.grpDACDAT13_10
    #define DACDAT13H_DACDAT1           DACDAT13H_DACDAT1_38
    #define DACDAT13H_DACDAT13          DACDAT13H_DACDAT13_10
    
    #define DACDAT13H_DACDAT138_MASK    1U
    #define DACDAT13H_DACDAT139_MASK    2U
    #define DACDAT13H_DACDAT1310_MASK   4U
    #define DACDAT13H_DACDAT1311_MASK   8U
    #define DACDAT13H_DACDAT1_38_MASK   3U
    #define DACDAT13H_DACDAT1_38_BITNUM 0U
    #define DACDAT13H_DACDAT13_10_MASK  12U
    #define DACDAT13H_DACDAT13_10_BITNUM 2U
    

    /*** DACDAT13L - DAC Data 13 Low Register; 0xFFFF802B ***/
    union {
      byte Byte;
      struct {
        byte DACDAT130   :1;                                       /* Buffer Data 13 Low, bit 0 */
        byte DACDAT131   :1;                                       /* Buffer Data 13 Low, bit 1 */
        byte DACDAT132   :1;                                       /* Buffer Data 13 Low, bit 2 */
        byte DACDAT133   :1;                                       /* Buffer Data 13 Low, bit 3 */
        byte DACDAT134   :1;                                       /* Buffer Data 13 Low, bit 4 */
        byte DACDAT135   :1;                                       /* Buffer Data 13 Low, bit 5 */
        byte DACDAT136   :1;                                       /* Buffer Data 13 Low, bit 6 */
        byte DACDAT137   :1;                                       /* Buffer Data 13 Low, bit 7 */
      } Bits;
    } DACDAT13LSTR;
    #define DACDAT13L                   _DACDAT13.Overlap_STR.DACDAT13LSTR.Byte
    #define DACDAT13L_DACDAT130         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT130
    #define DACDAT13L_DACDAT131         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT131
    #define DACDAT13L_DACDAT132         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT132
    #define DACDAT13L_DACDAT133         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT133
    #define DACDAT13L_DACDAT134         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT134
    #define DACDAT13L_DACDAT135         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT135
    #define DACDAT13L_DACDAT136         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT136
    #define DACDAT13L_DACDAT137         _DACDAT13.Overlap_STR.DACDAT13LSTR.Bits.DACDAT137
    
    #define DACDAT13L_DACDAT130_MASK    1U
    #define DACDAT13L_DACDAT131_MASK    2U
    #define DACDAT13L_DACDAT132_MASK    4U
    #define DACDAT13L_DACDAT133_MASK    8U
    #define DACDAT13L_DACDAT134_MASK    16U
    #define DACDAT13L_DACDAT135_MASK    32U
    #define DACDAT13L_DACDAT136_MASK    64U
    #define DACDAT13L_DACDAT137_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT130   :1;                                       /* Buffer Data 13, bit 0 */
    word DACDAT131   :1;                                       /* Buffer Data 13, bit 1 */
    word DACDAT132   :1;                                       /* Buffer Data 13, bit 2 */
    word DACDAT133   :1;                                       /* Buffer Data 13, bit 3 */
    word DACDAT134   :1;                                       /* Buffer Data 13, bit 4 */
    word DACDAT135   :1;                                       /* Buffer Data 13, bit 5 */
    word DACDAT136   :1;                                       /* Buffer Data 13, bit 6 */
    word DACDAT137   :1;                                       /* Buffer Data 13, bit 7 */
    word DACDAT138   :1;                                       /* Buffer Data 13, bit 8 */
    word DACDAT139   :1;                                       /* Buffer Data 13, bit 9 */
    word DACDAT1310  :1;                                       /* Buffer Data 13, bit 10 */
    word DACDAT1311  :1;                                       /* Buffer Data 13, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT1_30 :10;
    word grpDACDAT13_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT13STR;
extern volatile DACDAT13STR _DACDAT13 @0xFFFF802A;
#define DACDAT13                        _DACDAT13.Word
#define DACDAT13_DACDAT130              _DACDAT13.Bits.DACDAT130
#define DACDAT13_DACDAT131              _DACDAT13.Bits.DACDAT131
#define DACDAT13_DACDAT132              _DACDAT13.Bits.DACDAT132
#define DACDAT13_DACDAT133              _DACDAT13.Bits.DACDAT133
#define DACDAT13_DACDAT134              _DACDAT13.Bits.DACDAT134
#define DACDAT13_DACDAT135              _DACDAT13.Bits.DACDAT135
#define DACDAT13_DACDAT136              _DACDAT13.Bits.DACDAT136
#define DACDAT13_DACDAT137              _DACDAT13.Bits.DACDAT137
#define DACDAT13_DACDAT138              _DACDAT13.Bits.DACDAT138
#define DACDAT13_DACDAT139              _DACDAT13.Bits.DACDAT139
#define DACDAT13_DACDAT1310             _DACDAT13.Bits.DACDAT1310
#define DACDAT13_DACDAT1311             _DACDAT13.Bits.DACDAT1311
#define DACDAT13_DACDAT1_30             _DACDAT13.MergedBits.grpDACDAT1_30
#define DACDAT13_DACDAT13_10            _DACDAT13.MergedBits.grpDACDAT13_10
#define DACDAT13_DACDAT1                DACDAT13_DACDAT1_30

#define DACDAT13_DACDAT130_MASK         1U
#define DACDAT13_DACDAT131_MASK         2U
#define DACDAT13_DACDAT132_MASK         4U
#define DACDAT13_DACDAT133_MASK         8U
#define DACDAT13_DACDAT134_MASK         16U
#define DACDAT13_DACDAT135_MASK         32U
#define DACDAT13_DACDAT136_MASK         64U
#define DACDAT13_DACDAT137_MASK         128U
#define DACDAT13_DACDAT138_MASK         256U
#define DACDAT13_DACDAT139_MASK         512U
#define DACDAT13_DACDAT1310_MASK        1024U
#define DACDAT13_DACDAT1311_MASK        2048U
#define DACDAT13_DACDAT1_30_MASK        1023U
#define DACDAT13_DACDAT1_30_BITNUM      0U
#define DACDAT13_DACDAT13_10_MASK       3072U
#define DACDAT13_DACDAT13_10_BITNUM     10U


/*** DACDAT14 - DAC Data 14 Register; 0xFFFF802C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT14H - DAC Data 14 High Register; 0xFFFF802C ***/
    union {
      byte Byte;
      struct {
        byte DACDAT148   :1;                                       /* Buffer Data 14 High, bit 8 */
        byte DACDAT149   :1;                                       /* Buffer Data 14 High, bit 9 */
        byte DACDAT1410  :1;                                       /* Buffer Data 14 High, bit 10 */
        byte DACDAT1411  :1;                                       /* Buffer Data 14 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT1_48 :2;
        byte grpDACDAT14_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT14HSTR;
    #define DACDAT14H                   _DACDAT14.Overlap_STR.DACDAT14HSTR.Byte
    #define DACDAT14H_DACDAT148         _DACDAT14.Overlap_STR.DACDAT14HSTR.Bits.DACDAT148
    #define DACDAT14H_DACDAT149         _DACDAT14.Overlap_STR.DACDAT14HSTR.Bits.DACDAT149
    #define DACDAT14H_DACDAT1410        _DACDAT14.Overlap_STR.DACDAT14HSTR.Bits.DACDAT1410
    #define DACDAT14H_DACDAT1411        _DACDAT14.Overlap_STR.DACDAT14HSTR.Bits.DACDAT1411
    #define DACDAT14H_DACDAT1_48        _DACDAT14.Overlap_STR.DACDAT14HSTR.MergedBits.grpDACDAT1_48
    #define DACDAT14H_DACDAT14_10       _DACDAT14.Overlap_STR.DACDAT14HSTR.MergedBits.grpDACDAT14_10
    #define DACDAT14H_DACDAT1           DACDAT14H_DACDAT1_48
    #define DACDAT14H_DACDAT14          DACDAT14H_DACDAT14_10
    
    #define DACDAT14H_DACDAT148_MASK    1U
    #define DACDAT14H_DACDAT149_MASK    2U
    #define DACDAT14H_DACDAT1410_MASK   4U
    #define DACDAT14H_DACDAT1411_MASK   8U
    #define DACDAT14H_DACDAT1_48_MASK   3U
    #define DACDAT14H_DACDAT1_48_BITNUM 0U
    #define DACDAT14H_DACDAT14_10_MASK  12U
    #define DACDAT14H_DACDAT14_10_BITNUM 2U
    

    /*** DACDAT14L - DAC Data 14 Low Register; 0xFFFF802D ***/
    union {
      byte Byte;
      struct {
        byte DACDAT140   :1;                                       /* Buffer Data 14 Low, bit 0 */
        byte DACDAT141   :1;                                       /* Buffer Data 14 Low, bit 1 */
        byte DACDAT142   :1;                                       /* Buffer Data 14 Low, bit 2 */
        byte DACDAT143   :1;                                       /* Buffer Data 14 Low, bit 3 */
        byte DACDAT144   :1;                                       /* Buffer Data 14 Low, bit 4 */
        byte DACDAT145   :1;                                       /* Buffer Data 14 Low, bit 5 */
        byte DACDAT146   :1;                                       /* Buffer Data 14 Low, bit 6 */
        byte DACDAT147   :1;                                       /* Buffer Data 14 Low, bit 7 */
      } Bits;
    } DACDAT14LSTR;
    #define DACDAT14L                   _DACDAT14.Overlap_STR.DACDAT14LSTR.Byte
    #define DACDAT14L_DACDAT140         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT140
    #define DACDAT14L_DACDAT141         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT141
    #define DACDAT14L_DACDAT142         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT142
    #define DACDAT14L_DACDAT143         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT143
    #define DACDAT14L_DACDAT144         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT144
    #define DACDAT14L_DACDAT145         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT145
    #define DACDAT14L_DACDAT146         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT146
    #define DACDAT14L_DACDAT147         _DACDAT14.Overlap_STR.DACDAT14LSTR.Bits.DACDAT147
    
    #define DACDAT14L_DACDAT140_MASK    1U
    #define DACDAT14L_DACDAT141_MASK    2U
    #define DACDAT14L_DACDAT142_MASK    4U
    #define DACDAT14L_DACDAT143_MASK    8U
    #define DACDAT14L_DACDAT144_MASK    16U
    #define DACDAT14L_DACDAT145_MASK    32U
    #define DACDAT14L_DACDAT146_MASK    64U
    #define DACDAT14L_DACDAT147_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT140   :1;                                       /* Buffer Data 14, bit 0 */
    word DACDAT141   :1;                                       /* Buffer Data 14, bit 1 */
    word DACDAT142   :1;                                       /* Buffer Data 14, bit 2 */
    word DACDAT143   :1;                                       /* Buffer Data 14, bit 3 */
    word DACDAT144   :1;                                       /* Buffer Data 14, bit 4 */
    word DACDAT145   :1;                                       /* Buffer Data 14, bit 5 */
    word DACDAT146   :1;                                       /* Buffer Data 14, bit 6 */
    word DACDAT147   :1;                                       /* Buffer Data 14, bit 7 */
    word DACDAT148   :1;                                       /* Buffer Data 14, bit 8 */
    word DACDAT149   :1;                                       /* Buffer Data 14, bit 9 */
    word DACDAT1410  :1;                                       /* Buffer Data 14, bit 10 */
    word DACDAT1411  :1;                                       /* Buffer Data 14, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT1_40 :10;
    word grpDACDAT14_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT14STR;
extern volatile DACDAT14STR _DACDAT14 @0xFFFF802C;
#define DACDAT14                        _DACDAT14.Word
#define DACDAT14_DACDAT140              _DACDAT14.Bits.DACDAT140
#define DACDAT14_DACDAT141              _DACDAT14.Bits.DACDAT141
#define DACDAT14_DACDAT142              _DACDAT14.Bits.DACDAT142
#define DACDAT14_DACDAT143              _DACDAT14.Bits.DACDAT143
#define DACDAT14_DACDAT144              _DACDAT14.Bits.DACDAT144
#define DACDAT14_DACDAT145              _DACDAT14.Bits.DACDAT145
#define DACDAT14_DACDAT146              _DACDAT14.Bits.DACDAT146
#define DACDAT14_DACDAT147              _DACDAT14.Bits.DACDAT147
#define DACDAT14_DACDAT148              _DACDAT14.Bits.DACDAT148
#define DACDAT14_DACDAT149              _DACDAT14.Bits.DACDAT149
#define DACDAT14_DACDAT1410             _DACDAT14.Bits.DACDAT1410
#define DACDAT14_DACDAT1411             _DACDAT14.Bits.DACDAT1411
#define DACDAT14_DACDAT1_40             _DACDAT14.MergedBits.grpDACDAT1_40
#define DACDAT14_DACDAT14_10            _DACDAT14.MergedBits.grpDACDAT14_10
#define DACDAT14_DACDAT1                DACDAT14_DACDAT1_40

#define DACDAT14_DACDAT140_MASK         1U
#define DACDAT14_DACDAT141_MASK         2U
#define DACDAT14_DACDAT142_MASK         4U
#define DACDAT14_DACDAT143_MASK         8U
#define DACDAT14_DACDAT144_MASK         16U
#define DACDAT14_DACDAT145_MASK         32U
#define DACDAT14_DACDAT146_MASK         64U
#define DACDAT14_DACDAT147_MASK         128U
#define DACDAT14_DACDAT148_MASK         256U
#define DACDAT14_DACDAT149_MASK         512U
#define DACDAT14_DACDAT1410_MASK        1024U
#define DACDAT14_DACDAT1411_MASK        2048U
#define DACDAT14_DACDAT1_40_MASK        1023U
#define DACDAT14_DACDAT1_40_BITNUM      0U
#define DACDAT14_DACDAT14_10_MASK       3072U
#define DACDAT14_DACDAT14_10_BITNUM     10U


/*** DACDAT15 - DAC Data 15 Register; 0xFFFF802E ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACDAT15H - DAC Data 15 High Register; 0xFFFF802E ***/
    union {
      byte Byte;
      struct {
        byte DACDAT158   :1;                                       /* Buffer Data 15 High, bit 8 */
        byte DACDAT159   :1;                                       /* Buffer Data 15 High, bit 9 */
        byte DACDAT1510  :1;                                       /* Buffer Data 15 High, bit 10 */
        byte DACDAT1511  :1;                                       /* Buffer Data 15 High, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpDACDAT1_58 :2;
        byte grpDACDAT15_10 :2;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } DACDAT15HSTR;
    #define DACDAT15H                   _DACDAT15.Overlap_STR.DACDAT15HSTR.Byte
    #define DACDAT15H_DACDAT158         _DACDAT15.Overlap_STR.DACDAT15HSTR.Bits.DACDAT158
    #define DACDAT15H_DACDAT159         _DACDAT15.Overlap_STR.DACDAT15HSTR.Bits.DACDAT159
    #define DACDAT15H_DACDAT1510        _DACDAT15.Overlap_STR.DACDAT15HSTR.Bits.DACDAT1510
    #define DACDAT15H_DACDAT1511        _DACDAT15.Overlap_STR.DACDAT15HSTR.Bits.DACDAT1511
    #define DACDAT15H_DACDAT1_58        _DACDAT15.Overlap_STR.DACDAT15HSTR.MergedBits.grpDACDAT1_58
    #define DACDAT15H_DACDAT15_10       _DACDAT15.Overlap_STR.DACDAT15HSTR.MergedBits.grpDACDAT15_10
    #define DACDAT15H_DACDAT1           DACDAT15H_DACDAT1_58
    #define DACDAT15H_DACDAT15          DACDAT15H_DACDAT15_10
    
    #define DACDAT15H_DACDAT158_MASK    1U
    #define DACDAT15H_DACDAT159_MASK    2U
    #define DACDAT15H_DACDAT1510_MASK   4U
    #define DACDAT15H_DACDAT1511_MASK   8U
    #define DACDAT15H_DACDAT1_58_MASK   3U
    #define DACDAT15H_DACDAT1_58_BITNUM 0U
    #define DACDAT15H_DACDAT15_10_MASK  12U
    #define DACDAT15H_DACDAT15_10_BITNUM 2U
    

    /*** DACDAT15L - DAC Data 15 Low Register; 0xFFFF802F ***/
    union {
      byte Byte;
      struct {
        byte DACDAT150   :1;                                       /* Buffer Data 15 Low, bit 0 */
        byte DACDAT151   :1;                                       /* Buffer Data 15 Low, bit 1 */
        byte DACDAT152   :1;                                       /* Buffer Data 15 Low, bit 2 */
        byte DACDAT153   :1;                                       /* Buffer Data 15 Low, bit 3 */
        byte DACDAT154   :1;                                       /* Buffer Data 15 Low, bit 4 */
        byte DACDAT155   :1;                                       /* Buffer Data 15 Low, bit 5 */
        byte DACDAT156   :1;                                       /* Buffer Data 15 Low, bit 6 */
        byte DACDAT157   :1;                                       /* Buffer Data 15 Low, bit 7 */
      } Bits;
    } DACDAT15LSTR;
    #define DACDAT15L                   _DACDAT15.Overlap_STR.DACDAT15LSTR.Byte
    #define DACDAT15L_DACDAT150         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT150
    #define DACDAT15L_DACDAT151         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT151
    #define DACDAT15L_DACDAT152         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT152
    #define DACDAT15L_DACDAT153         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT153
    #define DACDAT15L_DACDAT154         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT154
    #define DACDAT15L_DACDAT155         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT155
    #define DACDAT15L_DACDAT156         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT156
    #define DACDAT15L_DACDAT157         _DACDAT15.Overlap_STR.DACDAT15LSTR.Bits.DACDAT157
    
    #define DACDAT15L_DACDAT150_MASK    1U
    #define DACDAT15L_DACDAT151_MASK    2U
    #define DACDAT15L_DACDAT152_MASK    4U
    #define DACDAT15L_DACDAT153_MASK    8U
    #define DACDAT15L_DACDAT154_MASK    16U
    #define DACDAT15L_DACDAT155_MASK    32U
    #define DACDAT15L_DACDAT156_MASK    64U
    #define DACDAT15L_DACDAT157_MASK    128U
    
  } Overlap_STR;

  struct {
    word DACDAT150   :1;                                       /* Buffer Data 15, bit 0 */
    word DACDAT151   :1;                                       /* Buffer Data 15, bit 1 */
    word DACDAT152   :1;                                       /* Buffer Data 15, bit 2 */
    word DACDAT153   :1;                                       /* Buffer Data 15, bit 3 */
    word DACDAT154   :1;                                       /* Buffer Data 15, bit 4 */
    word DACDAT155   :1;                                       /* Buffer Data 15, bit 5 */
    word DACDAT156   :1;                                       /* Buffer Data 15, bit 6 */
    word DACDAT157   :1;                                       /* Buffer Data 15, bit 7 */
    word DACDAT158   :1;                                       /* Buffer Data 15, bit 8 */
    word DACDAT159   :1;                                       /* Buffer Data 15, bit 9 */
    word DACDAT1510  :1;                                       /* Buffer Data 15, bit 10 */
    word DACDAT1511  :1;                                       /* Buffer Data 15, bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpDACDAT1_50 :10;
    word grpDACDAT15_10 :2;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} DACDAT15STR;
extern volatile DACDAT15STR _DACDAT15 @0xFFFF802E;
#define DACDAT15                        _DACDAT15.Word
#define DACDAT15_DACDAT150              _DACDAT15.Bits.DACDAT150
#define DACDAT15_DACDAT151              _DACDAT15.Bits.DACDAT151
#define DACDAT15_DACDAT152              _DACDAT15.Bits.DACDAT152
#define DACDAT15_DACDAT153              _DACDAT15.Bits.DACDAT153
#define DACDAT15_DACDAT154              _DACDAT15.Bits.DACDAT154
#define DACDAT15_DACDAT155              _DACDAT15.Bits.DACDAT155
#define DACDAT15_DACDAT156              _DACDAT15.Bits.DACDAT156
#define DACDAT15_DACDAT157              _DACDAT15.Bits.DACDAT157
#define DACDAT15_DACDAT158              _DACDAT15.Bits.DACDAT158
#define DACDAT15_DACDAT159              _DACDAT15.Bits.DACDAT159
#define DACDAT15_DACDAT1510             _DACDAT15.Bits.DACDAT1510
#define DACDAT15_DACDAT1511             _DACDAT15.Bits.DACDAT1511
#define DACDAT15_DACDAT1_50             _DACDAT15.MergedBits.grpDACDAT1_50
#define DACDAT15_DACDAT15_10            _DACDAT15.MergedBits.grpDACDAT15_10
#define DACDAT15_DACDAT1                DACDAT15_DACDAT1_50

#define DACDAT15_DACDAT150_MASK         1U
#define DACDAT15_DACDAT151_MASK         2U
#define DACDAT15_DACDAT152_MASK         4U
#define DACDAT15_DACDAT153_MASK         8U
#define DACDAT15_DACDAT154_MASK         16U
#define DACDAT15_DACDAT155_MASK         32U
#define DACDAT15_DACDAT156_MASK         64U
#define DACDAT15_DACDAT157_MASK         128U
#define DACDAT15_DACDAT158_MASK         256U
#define DACDAT15_DACDAT159_MASK         512U
#define DACDAT15_DACDAT1510_MASK        1024U
#define DACDAT15_DACDAT1511_MASK        2048U
#define DACDAT15_DACDAT1_50_MASK        1023U
#define DACDAT15_DACDAT1_50_BITNUM      0U
#define DACDAT15_DACDAT15_10_MASK       3072U
#define DACDAT15_DACDAT15_10_BITNUM     10U


/*** DACS - DAC Status Register; 0xFFFF8030 ***/
typedef union {
  byte Byte;
  struct {
    byte DACRPB      :1;                                       /* DAC buffer read pointer bottom position flag */
    byte DACRPT      :1;                                       /* DAC buffer read pointer top position flag */
    byte DACWM       :1;                                       /* DAC buffer watermark flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} DACSSTR;
extern volatile DACSSTR _DACS @0xFFFF8030;
#define DACS                            _DACS.Byte
#define DACS_DACRPB                     _DACS.Bits.DACRPB
#define DACS_DACRPT                     _DACS.Bits.DACRPT
#define DACS_DACWM                      _DACS.Bits.DACWM

#define DACS_DACRPB_MASK                1U
#define DACS_DACRPT_MASK                2U
#define DACS_DACWM_MASK                 4U


/*** DACC0 - DAC Control 0 Register; 0xFFFF8031 ***/
typedef union {
  byte Byte;
  struct {
    byte DACBIE      :1;                                       /* DAC buffer read pointer bottom flag interrupt enable */
    byte DACTIE      :1;                                       /* DAC buffer read pointer top flag interrupt enable */
    byte DACWIE      :1;                                       /* DAC buffer watermark interrupt enable */
    byte LPEN        :1;                                       /* DAC low power control */
    byte DACSTRG     :1;                                       /* DAC software trigger - active high */
    byte DACTSEL     :1;                                       /* DAC trigger select */
    byte DACRFS      :1;                                       /* DAC Reference Select */
    byte DACEN       :1;                                       /* DAC enable - The DACEN bit starts the Programmable Reference Generator operation */
  } Bits;
} DACC0STR;
extern volatile DACC0STR _DACC0 @0xFFFF8031;
#define DACC0                           _DACC0.Byte
#define DACC0_DACBIE                    _DACC0.Bits.DACBIE
#define DACC0_DACTIE                    _DACC0.Bits.DACTIE
#define DACC0_DACWIE                    _DACC0.Bits.DACWIE
#define DACC0_LPEN                      _DACC0.Bits.LPEN
#define DACC0_DACSTRG                   _DACC0.Bits.DACSTRG
#define DACC0_DACTSEL                   _DACC0.Bits.DACTSEL
#define DACC0_DACRFS                    _DACC0.Bits.DACRFS
#define DACC0_DACEN                     _DACC0.Bits.DACEN
/* DACC_ARR: Access 3 DACCx registers in an array */
#define DACC_ARR                        ((volatile byte *) &DACC0)

#define DACC0_DACBIE_MASK               1U
#define DACC0_DACTIE_MASK               2U
#define DACC0_DACWIE_MASK               4U
#define DACC0_LPEN_MASK                 8U
#define DACC0_DACSTRG_MASK              16U
#define DACC0_DACTSEL_MASK              32U
#define DACC0_DACRFS_MASK               64U
#define DACC0_DACEN_MASK                128U


/*** DACC1 - DAC Control 1 Register; 0xFFFF8032 ***/
typedef union {
  byte Byte;
  struct {
    byte DACBFE      :1;                                       /* DAC Buffer Enable */
    byte DACBFMD0    :1;                                       /* DAC Buffer Work Mode Select, bit 0 */
    byte DACBFMD1    :1;                                       /* DAC Buffer Work Mode Select, bit 1 */
    byte DACBFWM0    :1;                                       /* DAC Buffer Watermark Select, bit 0 */
    byte DACBFWM1    :1;                                       /* DAC Buffer Watermark Select, bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte         :1;
    byte grpDACBFMD :2;
    byte grpDACBFWM :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DACC1STR;
extern volatile DACC1STR _DACC1 @0xFFFF8032;
#define DACC1                           _DACC1.Byte
#define DACC1_DACBFE                    _DACC1.Bits.DACBFE
#define DACC1_DACBFMD0                  _DACC1.Bits.DACBFMD0
#define DACC1_DACBFMD1                  _DACC1.Bits.DACBFMD1
#define DACC1_DACBFWM0                  _DACC1.Bits.DACBFWM0
#define DACC1_DACBFWM1                  _DACC1.Bits.DACBFWM1
#define DACC1_DACBFMD                   _DACC1.MergedBits.grpDACBFMD
#define DACC1_DACBFWM                   _DACC1.MergedBits.grpDACBFWM

#define DACC1_DACBFE_MASK               1U
#define DACC1_DACBFMD0_MASK             2U
#define DACC1_DACBFMD1_MASK             4U
#define DACC1_DACBFWM0_MASK             8U
#define DACC1_DACBFWM1_MASK             16U
#define DACC1_DACBFMD_MASK              6U
#define DACC1_DACBFMD_BITNUM            1U
#define DACC1_DACBFWM_MASK              24U
#define DACC1_DACBFWM_BITNUM            3U


/*** DACC2 - DAC Control 2 Register; 0xFFFF8033 ***/
typedef union {
  byte Byte;
  struct {
    byte DACBFUP     :4;                                       /* DAC Buffer Upper Limit */
    byte DACBFRP     :4;                                       /* DAC Buffer Read Pointer */
  } Bits;
} DACC2STR;
extern volatile DACC2STR _DACC2 @0xFFFF8033;
#define DACC2                           _DACC2.Byte
#define DACC2_DACBFUP                   _DACC2.Bits.DACBFUP
#define DACC2_DACBFRP                   _DACC2.Bits.DACBFRP

#define DACC2_DACBFUP_MASK              15U
#define DACC2_DACBFUP_BITNUM            0U
#define DACC2_DACBFRP_MASK              240U
#define DACC2_DACBFRP_BITNUM            4U


/*** PRACMPCS - PRACMP Control and Status Register; 0xFFFF8034 ***/
typedef union {
  byte Byte;
  struct {
    byte ACIEN       :1;                                       /* ACMP Interrupt Enable */
    byte ACINTS0     :1;                                       /* ACMP Interrupt Select, bit 0 */
    byte ACINTS1     :1;                                       /* ACMP Interrupt Select, bit 1 */
    byte ACMPO       :1;                                       /* ACMP Output Bit */
    byte ACOPE       :1;                                       /* ACMP Output Pin Enable */
    byte             :1; 
    byte ACMPF       :1;                                       /* ACMP Interrupt Flag */
    byte ACEN        :1;                                       /* ACMP Module Enable */
  } Bits;
  struct {
    byte         :1;
    byte grpACINTS :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} PRACMPCSSTR;
extern volatile PRACMPCSSTR _PRACMPCS @0xFFFF8034;
#define PRACMPCS                        _PRACMPCS.Byte
#define PRACMPCS_ACIEN                  _PRACMPCS.Bits.ACIEN
#define PRACMPCS_ACINTS0                _PRACMPCS.Bits.ACINTS0
#define PRACMPCS_ACINTS1                _PRACMPCS.Bits.ACINTS1
#define PRACMPCS_ACMPO                  _PRACMPCS.Bits.ACMPO
#define PRACMPCS_ACOPE                  _PRACMPCS.Bits.ACOPE
#define PRACMPCS_ACMPF                  _PRACMPCS.Bits.ACMPF
#define PRACMPCS_ACEN                   _PRACMPCS.Bits.ACEN
#define PRACMPCS_ACINTS                 _PRACMPCS.MergedBits.grpACINTS

#define PRACMPCS_ACIEN_MASK             1U
#define PRACMPCS_ACINTS0_MASK           2U
#define PRACMPCS_ACINTS1_MASK           4U
#define PRACMPCS_ACMPO_MASK             8U
#define PRACMPCS_ACOPE_MASK             16U
#define PRACMPCS_ACMPF_MASK             64U
#define PRACMPCS_ACEN_MASK              128U
#define PRACMPCS_ACINTS_MASK            6U
#define PRACMPCS_ACINTS_BITNUM          1U


/*** PRACMPC0 - PRACMP Control 0 Register; 0xFFFF8035 ***/
typedef union {
  byte Byte;
  struct {
    byte ACNSEL0     :1;                                       /* ACMP Negative Input Select, bit 0 */
    byte ACNSEL1     :1;                                       /* ACMP Negative Input Select, bit 1 */
    byte ACNSEL2     :1;                                       /* ACMP Negative Input Select, bit 2 */
    byte             :1; 
    byte ACPSEL0     :1;                                       /* ACMP Positive Input Select, bit 0 */
    byte ACPSEL1     :1;                                       /* ACMP Positive Input Select, bit 1 */
    byte ACPSEL2     :1;                                       /* ACMP Positive Input Select, bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpACNSEL :3;
    byte         :1;
    byte grpACPSEL :3;
    byte         :1;
  } MergedBits;
} PRACMPC0STR;
extern volatile PRACMPC0STR _PRACMPC0 @0xFFFF8035;
#define PRACMPC0                        _PRACMPC0.Byte
#define PRACMPC0_ACNSEL0                _PRACMPC0.Bits.ACNSEL0
#define PRACMPC0_ACNSEL1                _PRACMPC0.Bits.ACNSEL1
#define PRACMPC0_ACNSEL2                _PRACMPC0.Bits.ACNSEL2
#define PRACMPC0_ACPSEL0                _PRACMPC0.Bits.ACPSEL0
#define PRACMPC0_ACPSEL1                _PRACMPC0.Bits.ACPSEL1
#define PRACMPC0_ACPSEL2                _PRACMPC0.Bits.ACPSEL2
/* PRACMPC_ARR: Access 3 PRACMPCx registers in an array */
#define PRACMPC_ARR                     ((volatile byte *) &PRACMPC0)
#define PRACMPC0_ACNSEL                 _PRACMPC0.MergedBits.grpACNSEL
#define PRACMPC0_ACPSEL                 _PRACMPC0.MergedBits.grpACPSEL

#define PRACMPC0_ACNSEL0_MASK           1U
#define PRACMPC0_ACNSEL1_MASK           2U
#define PRACMPC0_ACNSEL2_MASK           4U
#define PRACMPC0_ACPSEL0_MASK           16U
#define PRACMPC0_ACPSEL1_MASK           32U
#define PRACMPC0_ACPSEL2_MASK           64U
#define PRACMPC0_ACNSEL_MASK            7U
#define PRACMPC0_ACNSEL_BITNUM          0U
#define PRACMPC0_ACPSEL_MASK            112U
#define PRACMPC0_ACPSEL_BITNUM          4U


/*** PRACMPC1 - PRACMP Control 1 Register; 0xFFFF8036 ***/
typedef union {
  byte Byte;
  struct {
    byte PRGOS0      :1;                                       /* Programmable Reference Generator Output Selection, bit 0 */
    byte PRGOS1      :1;                                       /* Programmable Reference Generator Output Selection, bit 1 */
    byte PRGOS2      :1;                                       /* Programmable Reference Generator Output Selection, bit 2 */
    byte PRGOS3      :1;                                       /* Programmable Reference Generator Output Selection, bit 3 */
    byte PRGOS4      :1;                                       /* Programmable Reference Generator Output Selection, bit 4 */
    byte             :1; 
    byte PRGINS      :1;                                       /* Programmable Reference Generator Input Selection */
    byte PRGEN       :1;                                       /* Programmable Reference Generator Enable */
  } Bits;
  struct {
    byte grpPRGOS :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} PRACMPC1STR;
extern volatile PRACMPC1STR _PRACMPC1 @0xFFFF8036;
#define PRACMPC1                        _PRACMPC1.Byte
#define PRACMPC1_PRGOS0                 _PRACMPC1.Bits.PRGOS0
#define PRACMPC1_PRGOS1                 _PRACMPC1.Bits.PRGOS1
#define PRACMPC1_PRGOS2                 _PRACMPC1.Bits.PRGOS2
#define PRACMPC1_PRGOS3                 _PRACMPC1.Bits.PRGOS3
#define PRACMPC1_PRGOS4                 _PRACMPC1.Bits.PRGOS4
#define PRACMPC1_PRGINS                 _PRACMPC1.Bits.PRGINS
#define PRACMPC1_PRGEN                  _PRACMPC1.Bits.PRGEN
#define PRACMPC1_PRGOS                  _PRACMPC1.MergedBits.grpPRGOS

#define PRACMPC1_PRGOS0_MASK            1U
#define PRACMPC1_PRGOS1_MASK            2U
#define PRACMPC1_PRGOS2_MASK            4U
#define PRACMPC1_PRGOS3_MASK            8U
#define PRACMPC1_PRGOS4_MASK            16U
#define PRACMPC1_PRGINS_MASK            64U
#define PRACMPC1_PRGEN_MASK             128U
#define PRACMPC1_PRGOS_MASK             31U
#define PRACMPC1_PRGOS_BITNUM           0U


/*** PRACMPC2 - PRACMP Control 2 Register; 0xFFFF8037 ***/
typedef union {
  byte Byte;
  struct {
    byte ACIPE0      :1;                                       /* ACMP Input Pin 0 Enable - ACIPE0 is used to control the PRACMP external pin 0 as analog input */
    byte ACIPE1      :1;                                       /* ACMP Input Pin 1 Enable - ACIPE1 is used to control the PRACMP external pin 1 as analog input */
    byte ACIPE2      :1;                                       /* ACMP Input Pin 2 Enable - ACIPE2 is used to control the PRACMP external pin 2 as analog input */
    byte ACIPE3      :1;                                       /* ACMP Input Pin 3 Enable - ACIPE3 is used to control the PRACMP external pin 3 as analog input */
    byte ACIPE4      :1;                                       /* ACMP Input Pin 4 Enable - ACIPE4 is used to control the PRACMP external pin 4 as analog input */
    byte ACIPE5      :1;                                       /* ACMP Input Pin 5 Enable - ACIPE5 is used to control the PRACMP external pin 5 as analog input */
    byte ACIPE6      :1;                                       /* ACMP Input Pin 6 Enable - ACIPE6 is used to control the PRACMP external pin 6 as analog input */
    byte             :1; 
  } Bits;
  struct {
    byte grpACIPE :7;
    byte         :1;
  } MergedBits;
} PRACMPC2STR;
extern volatile PRACMPC2STR _PRACMPC2 @0xFFFF8037;
#define PRACMPC2                        _PRACMPC2.Byte
#define PRACMPC2_ACIPE0                 _PRACMPC2.Bits.ACIPE0
#define PRACMPC2_ACIPE1                 _PRACMPC2.Bits.ACIPE1
#define PRACMPC2_ACIPE2                 _PRACMPC2.Bits.ACIPE2
#define PRACMPC2_ACIPE3                 _PRACMPC2.Bits.ACIPE3
#define PRACMPC2_ACIPE4                 _PRACMPC2.Bits.ACIPE4
#define PRACMPC2_ACIPE5                 _PRACMPC2.Bits.ACIPE5
#define PRACMPC2_ACIPE6                 _PRACMPC2.Bits.ACIPE6
#define PRACMPC2_ACIPE                  _PRACMPC2.MergedBits.grpACIPE

#define PRACMPC2_ACIPE0_MASK            1U
#define PRACMPC2_ACIPE1_MASK            2U
#define PRACMPC2_ACIPE2_MASK            4U
#define PRACMPC2_ACIPE3_MASK            8U
#define PRACMPC2_ACIPE4_MASK            16U
#define PRACMPC2_ACIPE5_MASK            32U
#define PRACMPC2_ACIPE6_MASK            64U
#define PRACMPC2_ACIPE_MASK             127U
#define PRACMPC2_ACIPE_BITNUM           0U


/*** MCGC1 - MCG Control Register 1; 0xFFFF8038 ***/
typedef union {
  byte Byte;
  struct {
    byte IREFSTEN    :1;                                       /* Internal Reference Stop Enable */
    byte IRCLKEN     :1;                                       /* Internal Reference Clock Enable */
    byte IREFS       :1;                                       /* Internal Reference Select */
    byte RDIV0       :1;                                       /* Reference Divider, bit 0 */
    byte RDIV1       :1;                                       /* Reference Divider, bit 1 */
    byte RDIV2       :1;                                       /* Reference Divider, bit 2 */
    byte CLKS0       :1;                                       /* Clock Source Select, bit 0 */
    byte CLKS1       :1;                                       /* Clock Source Select, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpRDIV :3;
    byte grpCLKS :2;
  } MergedBits;
} MCGC1STR;
extern volatile MCGC1STR _MCGC1 @0xFFFF8038;
#define MCGC1                           _MCGC1.Byte
#define MCGC1_IREFSTEN                  _MCGC1.Bits.IREFSTEN
#define MCGC1_IRCLKEN                   _MCGC1.Bits.IRCLKEN
#define MCGC1_IREFS                     _MCGC1.Bits.IREFS
#define MCGC1_RDIV0                     _MCGC1.Bits.RDIV0
#define MCGC1_RDIV1                     _MCGC1.Bits.RDIV1
#define MCGC1_RDIV2                     _MCGC1.Bits.RDIV2
#define MCGC1_CLKS0                     _MCGC1.Bits.CLKS0
#define MCGC1_CLKS1                     _MCGC1.Bits.CLKS1
#define MCGC1_RDIV                      _MCGC1.MergedBits.grpRDIV
#define MCGC1_CLKS                      _MCGC1.MergedBits.grpCLKS

#define MCGC1_IREFSTEN_MASK             1U
#define MCGC1_IRCLKEN_MASK              2U
#define MCGC1_IREFS_MASK                4U
#define MCGC1_RDIV0_MASK                8U
#define MCGC1_RDIV1_MASK                16U
#define MCGC1_RDIV2_MASK                32U
#define MCGC1_CLKS0_MASK                64U
#define MCGC1_CLKS1_MASK                128U
#define MCGC1_RDIV_MASK                 56U
#define MCGC1_RDIV_BITNUM               3U
#define MCGC1_CLKS_MASK                 192U
#define MCGC1_CLKS_BITNUM               6U


/*** MCGC2 - MCG Control Register 2; 0xFFFF8039 ***/
typedef union {
  byte Byte;
  struct {
    byte EREFSTEN    :1;                                       /* External Reference Stop Enable */
    byte ERCLKEN     :1;                                       /* External Reference Enable */
    byte EREFS       :1;                                       /* External Reference Select */
    byte LP          :1;                                       /* Low Power Select */
    byte HGO         :1;                                       /* High Gain Oscillator Select */
    byte RANGE       :1;                                       /* Frequency Range Select */
    byte BDIV0       :1;                                       /* Bus Frequency Divider, bit 0 */
    byte BDIV1       :1;                                       /* Bus Frequency Divider, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpBDIV :2;
  } MergedBits;
} MCGC2STR;
extern volatile MCGC2STR _MCGC2 @0xFFFF8039;
#define MCGC2                           _MCGC2.Byte
#define MCGC2_EREFSTEN                  _MCGC2.Bits.EREFSTEN
#define MCGC2_ERCLKEN                   _MCGC2.Bits.ERCLKEN
#define MCGC2_EREFS                     _MCGC2.Bits.EREFS
#define MCGC2_LP                        _MCGC2.Bits.LP
#define MCGC2_HGO                       _MCGC2.Bits.HGO
#define MCGC2_RANGE                     _MCGC2.Bits.RANGE
#define MCGC2_BDIV0                     _MCGC2.Bits.BDIV0
#define MCGC2_BDIV1                     _MCGC2.Bits.BDIV1
#define MCGC2_BDIV                      _MCGC2.MergedBits.grpBDIV

#define MCGC2_EREFSTEN_MASK             1U
#define MCGC2_ERCLKEN_MASK              2U
#define MCGC2_EREFS_MASK                4U
#define MCGC2_LP_MASK                   8U
#define MCGC2_HGO_MASK                  16U
#define MCGC2_RANGE_MASK                32U
#define MCGC2_BDIV0_MASK                64U
#define MCGC2_BDIV1_MASK                128U
#define MCGC2_BDIV_MASK                 192U
#define MCGC2_BDIV_BITNUM               6U


/*** MCGTRM - MCG Trim Register; 0xFFFF803A ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* MCG Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* MCG Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* MCG Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* MCG Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* MCG Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* MCG Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* MCG Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* MCG Trim Setting, bit 7 */
  } Bits;
} MCGTRMSTR;
extern volatile MCGTRMSTR _MCGTRM @0xFFFF803A;
#define MCGTRM                          _MCGTRM.Byte
#define MCGTRM_TRIM0                    _MCGTRM.Bits.TRIM0
#define MCGTRM_TRIM1                    _MCGTRM.Bits.TRIM1
#define MCGTRM_TRIM2                    _MCGTRM.Bits.TRIM2
#define MCGTRM_TRIM3                    _MCGTRM.Bits.TRIM3
#define MCGTRM_TRIM4                    _MCGTRM.Bits.TRIM4
#define MCGTRM_TRIM5                    _MCGTRM.Bits.TRIM5
#define MCGTRM_TRIM6                    _MCGTRM.Bits.TRIM6
#define MCGTRM_TRIM7                    _MCGTRM.Bits.TRIM7

#define MCGTRM_TRIM0_MASK               1U
#define MCGTRM_TRIM1_MASK               2U
#define MCGTRM_TRIM2_MASK               4U
#define MCGTRM_TRIM3_MASK               8U
#define MCGTRM_TRIM4_MASK               16U
#define MCGTRM_TRIM5_MASK               32U
#define MCGTRM_TRIM6_MASK               64U
#define MCGTRM_TRIM7_MASK               128U


/*** MCGSC - MCG Status and Control Register; 0xFFFF803B ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* MCG Fine Trim */
    byte OSCINIT     :1;                                       /* OSC Initialization */
    byte CLKST0      :1;                                       /* Clock Mode Status, bit 0 */
    byte CLKST1      :1;                                       /* Clock Mode Status, bit 1 */
    byte IREFST      :1;                                       /* Internal Reference Status */
    byte PLLST       :1;                                       /* PLL Select Status */
    byte LOCK        :1;                                       /* Lock Status */
    byte LOLS        :1;                                       /* Loss of Lock Status */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpCLKST :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} MCGSCSTR;
extern volatile MCGSCSTR _MCGSC @0xFFFF803B;
#define MCGSC                           _MCGSC.Byte
#define MCGSC_FTRIM                     _MCGSC.Bits.FTRIM
#define MCGSC_OSCINIT                   _MCGSC.Bits.OSCINIT
#define MCGSC_CLKST0                    _MCGSC.Bits.CLKST0
#define MCGSC_CLKST1                    _MCGSC.Bits.CLKST1
#define MCGSC_IREFST                    _MCGSC.Bits.IREFST
#define MCGSC_PLLST                     _MCGSC.Bits.PLLST
#define MCGSC_LOCK                      _MCGSC.Bits.LOCK
#define MCGSC_LOLS                      _MCGSC.Bits.LOLS
#define MCGSC_CLKST                     _MCGSC.MergedBits.grpCLKST

#define MCGSC_FTRIM_MASK                1U
#define MCGSC_OSCINIT_MASK              2U
#define MCGSC_CLKST0_MASK               4U
#define MCGSC_CLKST1_MASK               8U
#define MCGSC_IREFST_MASK               16U
#define MCGSC_PLLST_MASK                32U
#define MCGSC_LOCK_MASK                 64U
#define MCGSC_LOLS_MASK                 128U
#define MCGSC_CLKST_MASK                12U
#define MCGSC_CLKST_BITNUM              2U


/*** MCGC3 - MCG Control Register 3; 0xFFFF803C ***/
typedef union {
  byte Byte;
  struct {
    byte VDIV0       :1;                                       /* VCO Divider, bit 0 */
    byte VDIV1       :1;                                       /* VCO Divider, bit 1 */
    byte VDIV2       :1;                                       /* VCO Divider, bit 2 */
    byte VDIV3       :1;                                       /* VCO Divider, bit 3 */
    byte DIV32       :1;                                       /* Divide-by-32 Enable */
    byte CME         :1;                                       /* Clock Monitor Enable */
    byte PLLS        :1;                                       /* PLL Select */
    byte LOLIE       :1;                                       /* Loss of Lock Interrupt Enable */
  } Bits;
  struct {
    byte grpVDIV :4;
    byte grpDIV_32 :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} MCGC3STR;
extern volatile MCGC3STR _MCGC3 @0xFFFF803C;
#define MCGC3                           _MCGC3.Byte
#define MCGC3_VDIV0                     _MCGC3.Bits.VDIV0
#define MCGC3_VDIV1                     _MCGC3.Bits.VDIV1
#define MCGC3_VDIV2                     _MCGC3.Bits.VDIV2
#define MCGC3_VDIV3                     _MCGC3.Bits.VDIV3
#define MCGC3_DIV32                     _MCGC3.Bits.DIV32
#define MCGC3_CME                       _MCGC3.Bits.CME
#define MCGC3_PLLS                      _MCGC3.Bits.PLLS
#define MCGC3_LOLIE                     _MCGC3.Bits.LOLIE
#define MCGC3_VDIV                      _MCGC3.MergedBits.grpVDIV

#define MCGC3_VDIV0_MASK                1U
#define MCGC3_VDIV1_MASK                2U
#define MCGC3_VDIV2_MASK                4U
#define MCGC3_VDIV3_MASK                8U
#define MCGC3_DIV32_MASK                16U
#define MCGC3_CME_MASK                  32U
#define MCGC3_PLLS_MASK                 64U
#define MCGC3_LOLIE_MASK                128U
#define MCGC3_VDIV_MASK                 15U
#define MCGC3_VDIV_BITNUM               0U


/*** MCGC4 - MCG Control Register 4; 0xFFFF803D ***/
typedef union {
  byte Byte;
  struct {
    byte DRST_DRS0   :1;                                       /* DCO Range Status / DCO Range Select, bit 0 */
    byte DRST_DRS1   :1;                                       /* DCO Range Status / DCO Range Select, bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte DMX32       :1;                                       /* DCO Maximum frequency with 32.768 kHz reference */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpDRST_DRS :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpDMX_32 :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} MCGC4STR;
extern volatile MCGC4STR _MCGC4 @0xFFFF803D;
#define MCGC4                           _MCGC4.Byte
#define MCGC4_DRST_DRS0                 _MCGC4.Bits.DRST_DRS0
#define MCGC4_DRST_DRS1                 _MCGC4.Bits.DRST_DRS1
#define MCGC4_DMX32                     _MCGC4.Bits.DMX32
#define MCGC4_DRST_DRS                  _MCGC4.MergedBits.grpDRST_DRS

#define MCGC4_DRST_DRS0_MASK            1U
#define MCGC4_DRST_DRS1_MASK            2U
#define MCGC4_DMX32_MASK                32U
#define MCGC4_DRST_DRS_MASK             3U
#define MCGC4_DRST_DRS_BITNUM           0U


/*** ADCSC1 - Status and Control Register 1A; 0xFFFF8040 ***/
typedef union {
  byte Byte;
  struct {
    byte ADCH0       :1;                                       /* Input Channel Select Bit 0 */
    byte ADCH1       :1;                                       /* Input Channel Select Bit 1 */
    byte ADCH2       :1;                                       /* Input Channel Select Bit 2 */
    byte ADCH3       :1;                                       /* Input Channel Select Bit 3 */
    byte ADCH4       :1;                                       /* Input Channel Select Bit 4 */
    byte DIFF        :1;                                       /* Differential Mode Enable - selects between single-ended and differential conversion on selected channel */
    byte AIEN        :1;                                       /* Interrupt Enable - AIEN enables conversion complete interrupts. When COCO becomes set while the respective AIEN is high, an interrupt is asserted */
    byte COCO        :1;                                       /* Conversion Complete Flag */
  } Bits;
  struct {
    byte grpADCH :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ADCSC1STR;
extern volatile ADCSC1STR _ADCSC1 @0xFFFF8040;
#define ADCSC1                          _ADCSC1.Byte
#define ADCSC1_ADCH0                    _ADCSC1.Bits.ADCH0
#define ADCSC1_ADCH1                    _ADCSC1.Bits.ADCH1
#define ADCSC1_ADCH2                    _ADCSC1.Bits.ADCH2
#define ADCSC1_ADCH3                    _ADCSC1.Bits.ADCH3
#define ADCSC1_ADCH4                    _ADCSC1.Bits.ADCH4
#define ADCSC1_DIFF                     _ADCSC1.Bits.DIFF
#define ADCSC1_AIEN                     _ADCSC1.Bits.AIEN
#define ADCSC1_COCO                     _ADCSC1.Bits.COCO
#define ADCSC1_ADCH                     _ADCSC1.MergedBits.grpADCH

#define ADCSC1_ADCH0_MASK               1U
#define ADCSC1_ADCH1_MASK               2U
#define ADCSC1_ADCH2_MASK               4U
#define ADCSC1_ADCH3_MASK               8U
#define ADCSC1_ADCH4_MASK               16U
#define ADCSC1_DIFF_MASK                32U
#define ADCSC1_AIEN_MASK                64U
#define ADCSC1_COCO_MASK                128U
#define ADCSC1_ADCH_MASK                31U
#define ADCSC1_ADCH_BITNUM              0U


/*** ADCCFG1 - Configuration Register 1; 0xFFFF8048 ***/
typedef union {
  byte Byte;
  struct {
    byte ADICLK0     :1;                                       /* Input Clock Select Bit 0 */
    byte ADICLK1     :1;                                       /* Input Clock Select Bit 1 */
    byte MODE0       :1;                                       /* Conversion Mode Selection Bit 0 */
    byte MODE1       :1;                                       /* Conversion Mode Selection Bit 1 */
    byte ADLSMP      :1;                                       /* Long Sample Time Configuration */
    byte ADIV0       :1;                                       /* Clock Divide Select Bit 0 */
    byte ADIV1       :1;                                       /* Clock Divide Select Bit 1 */
    byte ADLPC       :1;                                       /* Low Power Configuration */
  } Bits;
  struct {
    byte grpADICLK :2;
    byte grpMODE :2;
    byte         :1;
    byte grpADIV :2;
    byte         :1;
  } MergedBits;
} ADCCFG1STR;
extern volatile ADCCFG1STR _ADCCFG1 @0xFFFF8048;
#define ADCCFG1                         _ADCCFG1.Byte
#define ADCCFG1_ADICLK0                 _ADCCFG1.Bits.ADICLK0
#define ADCCFG1_ADICLK1                 _ADCCFG1.Bits.ADICLK1
#define ADCCFG1_MODE0                   _ADCCFG1.Bits.MODE0
#define ADCCFG1_MODE1                   _ADCCFG1.Bits.MODE1
#define ADCCFG1_ADLSMP                  _ADCCFG1.Bits.ADLSMP
#define ADCCFG1_ADIV0                   _ADCCFG1.Bits.ADIV0
#define ADCCFG1_ADIV1                   _ADCCFG1.Bits.ADIV1
#define ADCCFG1_ADLPC                   _ADCCFG1.Bits.ADLPC
#define ADCCFG1_ADICLK                  _ADCCFG1.MergedBits.grpADICLK
#define ADCCFG1_MODE                    _ADCCFG1.MergedBits.grpMODE
#define ADCCFG1_ADIV                    _ADCCFG1.MergedBits.grpADIV

#define ADCCFG1_ADICLK0_MASK            1U
#define ADCCFG1_ADICLK1_MASK            2U
#define ADCCFG1_MODE0_MASK              4U
#define ADCCFG1_MODE1_MASK              8U
#define ADCCFG1_ADLSMP_MASK             16U
#define ADCCFG1_ADIV0_MASK              32U
#define ADCCFG1_ADIV1_MASK              64U
#define ADCCFG1_ADLPC_MASK              128U
#define ADCCFG1_ADICLK_MASK             3U
#define ADCCFG1_ADICLK_BITNUM           0U
#define ADCCFG1_MODE_MASK               12U
#define ADCCFG1_MODE_BITNUM             2U
#define ADCCFG1_ADIV_MASK               96U
#define ADCCFG1_ADIV_BITNUM             5U


/*** ADCCFG2 - Configuration Register 2; 0xFFFF8049 ***/
typedef union {
  byte Byte;
  struct {
    byte ADLSTS0     :1;                                       /* Long Sample Time Select Bit 0 */
    byte ADLSTS1     :1;                                       /* Long Sample Time Select Bit 1 */
    byte ADHSC       :1;                                       /* High Speed Configuration */
    byte ADACKEN     :1;                                       /* Asynchronous Clock Output Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpADLSTS :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ADCCFG2STR;
extern volatile ADCCFG2STR _ADCCFG2 @0xFFFF8049;
#define ADCCFG2                         _ADCCFG2.Byte
#define ADCCFG2_ADLSTS0                 _ADCCFG2.Bits.ADLSTS0
#define ADCCFG2_ADLSTS1                 _ADCCFG2.Bits.ADLSTS1
#define ADCCFG2_ADHSC                   _ADCCFG2.Bits.ADHSC
#define ADCCFG2_ADACKEN                 _ADCCFG2.Bits.ADACKEN
#define ADCCFG2_ADLSTS                  _ADCCFG2.MergedBits.grpADLSTS

#define ADCCFG2_ADLSTS0_MASK            1U
#define ADCCFG2_ADLSTS1_MASK            2U
#define ADCCFG2_ADHSC_MASK              4U
#define ADCCFG2_ADACKEN_MASK            8U
#define ADCCFG2_ADLSTS_MASK             3U
#define ADCCFG2_ADLSTS_BITNUM           0U


/*** ADCR - Data Result Register; 0xFFFF804A ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCRH - Data Result High Register; 0xFFFF804A ***/
    union {
      byte Byte;
      struct {
        byte D8          :1;                                       /* ADC Result Data Bit 8 */
        byte D9          :1;                                       /* ADC Result Data Bit 9 */
        byte D10         :1;                                       /* ADC Result Data Bit 10 */
        byte D11         :1;                                       /* ADC Result Data Bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpD_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCRHSTR;
    #define ADCRH                       _ADCR.Overlap_STR.ADCRHSTR.Byte
    #define ADCRH_D8                    _ADCR.Overlap_STR.ADCRHSTR.Bits.D8
    #define ADCRH_D9                    _ADCR.Overlap_STR.ADCRHSTR.Bits.D9
    #define ADCRH_D10                   _ADCR.Overlap_STR.ADCRHSTR.Bits.D10
    #define ADCRH_D11                   _ADCR.Overlap_STR.ADCRHSTR.Bits.D11
    #define ADCRH_D_8                   _ADCR.Overlap_STR.ADCRHSTR.MergedBits.grpD_8
    #define ADCRH_D                     ADCRH_D_8
    
    #define ADCRH_D8_MASK               1U
    #define ADCRH_D9_MASK               2U
    #define ADCRH_D10_MASK              4U
    #define ADCRH_D11_MASK              8U
    #define ADCRH_D_8_MASK              15U
    #define ADCRH_D_8_BITNUM            0U
    

    /*** ADCRL - Data Result Low Register; 0xFFFF804B ***/
    union {
      byte Byte;
      struct {
        byte D0          :1;                                       /* ADC Result Data Bit 0 */
        byte D1          :1;                                       /* ADC Result Data Bit 1 */
        byte D2          :1;                                       /* ADC Result Data Bit 2 */
        byte D3          :1;                                       /* ADC Result Data Bit 3 */
        byte D4          :1;                                       /* ADC Result Data Bit 4 */
        byte D5          :1;                                       /* ADC Result Data Bit 5 */
        byte D6          :1;                                       /* ADC Result Data Bit 6 */
        byte D7          :1;                                       /* ADC Result Data Bit 7 */
      } Bits;
    } ADCRLSTR;
    #define ADCRL                       _ADCR.Overlap_STR.ADCRLSTR.Byte
    #define ADCRL_D0                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D0
    #define ADCRL_D1                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D1
    #define ADCRL_D2                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D2
    #define ADCRL_D3                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D3
    #define ADCRL_D4                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D4
    #define ADCRL_D5                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D5
    #define ADCRL_D6                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D6
    #define ADCRL_D7                    _ADCR.Overlap_STR.ADCRLSTR.Bits.D7
    
    #define ADCRL_D0_MASK               1U
    #define ADCRL_D1_MASK               2U
    #define ADCRL_D2_MASK               4U
    #define ADCRL_D3_MASK               8U
    #define ADCRL_D4_MASK               16U
    #define ADCRL_D5_MASK               32U
    #define ADCRL_D6_MASK               64U
    #define ADCRL_D7_MASK               128U
    
  } Overlap_STR;

  struct {
    word D0          :1;                                       /* ADC Result Data Bit 0 */
    word D1          :1;                                       /* ADC Result Data Bit 1 */
    word D2          :1;                                       /* ADC Result Data Bit 2 */
    word D3          :1;                                       /* ADC Result Data Bit 3 */
    word D4          :1;                                       /* ADC Result Data Bit 4 */
    word D5          :1;                                       /* ADC Result Data Bit 5 */
    word D6          :1;                                       /* ADC Result Data Bit 6 */
    word D7          :1;                                       /* ADC Result Data Bit 7 */
    word D8          :1;                                       /* ADC Result Data Bit 8 */
    word D9          :1;                                       /* ADC Result Data Bit 9 */
    word D10         :1;                                       /* ADC Result Data Bit 10 */
    word D11         :1;                                       /* ADC Result Data Bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpD    :12;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} ADCRSTR;
extern volatile ADCRSTR _ADCR @0xFFFF804A;
#define ADCR                            _ADCR.Word
#define ADCR_D0                         _ADCR.Bits.D0
#define ADCR_D1                         _ADCR.Bits.D1
#define ADCR_D2                         _ADCR.Bits.D2
#define ADCR_D3                         _ADCR.Bits.D3
#define ADCR_D4                         _ADCR.Bits.D4
#define ADCR_D5                         _ADCR.Bits.D5
#define ADCR_D6                         _ADCR.Bits.D6
#define ADCR_D7                         _ADCR.Bits.D7
#define ADCR_D8                         _ADCR.Bits.D8
#define ADCR_D9                         _ADCR.Bits.D9
#define ADCR_D10                        _ADCR.Bits.D10
#define ADCR_D11                        _ADCR.Bits.D11
#define ADCR_D                          _ADCR.MergedBits.grpD

#define ADCR_D0_MASK                    1U
#define ADCR_D1_MASK                    2U
#define ADCR_D2_MASK                    4U
#define ADCR_D3_MASK                    8U
#define ADCR_D4_MASK                    16U
#define ADCR_D5_MASK                    32U
#define ADCR_D6_MASK                    64U
#define ADCR_D7_MASK                    128U
#define ADCR_D8_MASK                    256U
#define ADCR_D9_MASK                    512U
#define ADCR_D10_MASK                   1024U
#define ADCR_D11_MASK                   2048U
#define ADCR_D_MASK                     4095U
#define ADCR_D_BITNUM                   0U


/*** VREFTRM - VREF Trim Register; 0xFFFF805C ***/
typedef union {
  byte Byte;
  struct {
    byte TRM0        :1;                                       /* Trim Bits, bit 0 */
    byte TRM1        :1;                                       /* Trim Bits, bit 1 */
    byte TRM2        :1;                                       /* Trim Bits, bit 2 */
    byte TRM3        :1;                                       /* Trim Bits, bit 3 */
    byte TRM4        :1;                                       /* Trim Bits, bit 4 */
    byte TRM5        :1;                                       /* Trim Bits, bit 5 */
    byte TRM6        :1;                                       /* Trim Bits, bit 6 */
    byte TRM7        :1;                                       /* Trim Bits, bit 7 */
  } Bits;
} VREFTRMSTR;
extern volatile VREFTRMSTR _VREFTRM @0xFFFF805C;
#define VREFTRM                         _VREFTRM.Byte
#define VREFTRM_TRM0                    _VREFTRM.Bits.TRM0
#define VREFTRM_TRM1                    _VREFTRM.Bits.TRM1
#define VREFTRM_TRM2                    _VREFTRM.Bits.TRM2
#define VREFTRM_TRM3                    _VREFTRM.Bits.TRM3
#define VREFTRM_TRM4                    _VREFTRM.Bits.TRM4
#define VREFTRM_TRM5                    _VREFTRM.Bits.TRM5
#define VREFTRM_TRM6                    _VREFTRM.Bits.TRM6
#define VREFTRM_TRM7                    _VREFTRM.Bits.TRM7

#define VREFTRM_TRM0_MASK               1U
#define VREFTRM_TRM1_MASK               2U
#define VREFTRM_TRM2_MASK               4U
#define VREFTRM_TRM3_MASK               8U
#define VREFTRM_TRM4_MASK               16U
#define VREFTRM_TRM5_MASK               32U
#define VREFTRM_TRM6_MASK               64U
#define VREFTRM_TRM7_MASK               128U


/*** VREFSC - VREF Control Register; 0xFFFF805D ***/
typedef union {
  byte Byte;
  struct {
    byte MODE0       :1;                                       /* Mode selection, bit 0 */
    byte MODE1       :1;                                       /* Mode selection, bit 1 */
    byte VREFST      :1;                                       /* Internal Voltage Reference Stable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte VREFEN      :1;                                       /* Internal Voltage Reference Enable */
  } Bits;
  struct {
    byte grpMODE :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} VREFSCSTR;
extern volatile VREFSCSTR _VREFSC @0xFFFF805D;
#define VREFSC                          _VREFSC.Byte
#define VREFSC_MODE0                    _VREFSC.Bits.MODE0
#define VREFSC_MODE1                    _VREFSC.Bits.MODE1
#define VREFSC_VREFST                   _VREFSC.Bits.VREFST
#define VREFSC_VREFEN                   _VREFSC.Bits.VREFEN
#define VREFSC_MODE                     _VREFSC.MergedBits.grpMODE

#define VREFSC_MODE0_MASK               1U
#define VREFSC_MODE1_MASK               2U
#define VREFSC_VREFST_MASK              4U
#define VREFSC_VREFEN_MASK              128U
#define VREFSC_MODE_MASK                3U
#define VREFSC_MODE_BITNUM              0U


/*** IRQSC - Interrupt request status and control register; 0xFFFF805F ***/
typedef union {
  byte Byte;
  struct {
    byte IRQMOD      :1;                                       /* IRQ Detection Mode */
    byte IRQIE       :1;                                       /* IRQ Interrupt Enable */
    byte IRQACK      :1;                                       /* IRQ Acknowledge */
    byte IRQF        :1;                                       /* IRQ Flag */
    byte IRQPE       :1;                                       /* IRQ Pin Enable */
    byte IRQEDG      :1;                                       /* IRQ Edge Select */
    byte IRQPDD      :1;                                       /* IRQ Pull Device Disable */
    byte             :1; 
  } Bits;
} IRQSCSTR;
extern volatile IRQSCSTR _IRQSC @0xFFFF805F;
#define IRQSC                           _IRQSC.Byte
#define IRQSC_IRQMOD                    _IRQSC.Bits.IRQMOD
#define IRQSC_IRQIE                     _IRQSC.Bits.IRQIE
#define IRQSC_IRQACK                    _IRQSC.Bits.IRQACK
#define IRQSC_IRQF                      _IRQSC.Bits.IRQF
#define IRQSC_IRQPE                     _IRQSC.Bits.IRQPE
#define IRQSC_IRQEDG                    _IRQSC.Bits.IRQEDG
#define IRQSC_IRQPDD                    _IRQSC.Bits.IRQPDD

#define IRQSC_IRQMOD_MASK               1U
#define IRQSC_IRQIE_MASK                2U
#define IRQSC_IRQACK_MASK               4U
#define IRQSC_IRQF_MASK                 8U
#define IRQSC_IRQPE_MASK                16U
#define IRQSC_IRQEDG_MASK               32U
#define IRQSC_IRQPDD_MASK               64U


/*** IICA1 - IIC Address Register; 0xFFFF8060 ***/
typedef union {
  byte Byte;
  union { /* Several registers at the same address */
    /*** IICA1 - IIC Address Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte AD1         :1;                                       /* Slave Address Bit 1 */
        byte AD2         :1;                                       /* Slave Address Bit 2 */
        byte AD3         :1;                                       /* Slave Address Bit 3 */
        byte AD4         :1;                                       /* Slave Address Bit 4 */
        byte AD5         :1;                                       /* Slave Address Bit 5 */
        byte AD6         :1;                                       /* Slave Address Bit 6 */
        byte AD7         :1;                                       /* Slave Address Bit 7 */
      } Bits;
      struct {
        byte     :1;
        byte grpAD_1 :7;
      } MergedBits;
    } IICA1STR;
    #define IICA1                       _IICA1.Byte
    #define IICA1_AD1                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD1
    #define IICA1_AD2                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD2
    #define IICA1_AD3                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD3
    #define IICA1_AD4                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD4
    #define IICA1_AD5                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD5
    #define IICA1_AD6                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD6
    #define IICA1_AD7                   _IICA1.SameAddr_STR.IICA1STR.Bits.AD7
    #define IICA1_AD_1                  _IICA1.SameAddr_STR.IICA1STR.MergedBits.grpAD_1
    #define IICA1_AD                    IICA1_AD_1
    
    #define IICA1_AD1_MASK              2U
    #define IICA1_AD2_MASK              4U
    #define IICA1_AD3_MASK              8U
    #define IICA1_AD4_MASK              16U
    #define IICA1_AD5_MASK              32U
    #define IICA1_AD6_MASK              64U
    #define IICA1_AD7_MASK              128U
    #define IICA1_AD_1_MASK             254U
    #define IICA1_AD_1_BITNUM           1U
    
    /*** IICA - IIC Address Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte AD1         :1;                                       /* Slave Address Bit 1 */
        byte AD2         :1;                                       /* Slave Address Bit 2 */
        byte AD3         :1;                                       /* Slave Address Bit 3 */
        byte AD4         :1;                                       /* Slave Address Bit 4 */
        byte AD5         :1;                                       /* Slave Address Bit 5 */
        byte AD6         :1;                                       /* Slave Address Bit 6 */
        byte AD7         :1;                                       /* Slave Address Bit 7 */
      } Bits;
      struct {
        byte     :1;
        byte grpAD_1 :7;
      } MergedBits;
    } IICASTR;
    #define IICA                        _IICA1.Byte
    #define IICA_AD1                    _IICA1.SameAddr_STR.IICASTR.Bits.AD1
    #define IICA_AD2                    _IICA1.SameAddr_STR.IICASTR.Bits.AD2
    #define IICA_AD3                    _IICA1.SameAddr_STR.IICASTR.Bits.AD3
    #define IICA_AD4                    _IICA1.SameAddr_STR.IICASTR.Bits.AD4
    #define IICA_AD5                    _IICA1.SameAddr_STR.IICASTR.Bits.AD5
    #define IICA_AD6                    _IICA1.SameAddr_STR.IICASTR.Bits.AD6
    #define IICA_AD7                    _IICA1.SameAddr_STR.IICASTR.Bits.AD7
    #define IICA_AD_1                   _IICA1.SameAddr_STR.IICASTR.MergedBits.grpAD_1
    #define IICA_AD                     IICA_AD_1
    
    #define IICA_AD1_MASK               2U
    #define IICA_AD2_MASK               4U
    #define IICA_AD3_MASK               8U
    #define IICA_AD4_MASK               16U
    #define IICA_AD5_MASK               32U
    #define IICA_AD6_MASK               64U
    #define IICA_AD7_MASK               128U
    #define IICA_AD_1_MASK              254U
    #define IICA_AD_1_BITNUM            1U
    
  } SameAddr_STR; /*Several registers at the same address */

} IICA1STR;
extern volatile IICA1STR _IICA1 @0xFFFF8060;


/*** IICF - IIC Frequency Divider Register; 0xFFFF8061 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IICFSTR;
extern volatile IICFSTR _IICF @0xFFFF8061;
#define IICF                            _IICF.Byte
#define IICF_ICR0                       _IICF.Bits.ICR0
#define IICF_ICR1                       _IICF.Bits.ICR1
#define IICF_ICR2                       _IICF.Bits.ICR2
#define IICF_ICR3                       _IICF.Bits.ICR3
#define IICF_ICR4                       _IICF.Bits.ICR4
#define IICF_ICR5                       _IICF.Bits.ICR5
#define IICF_MULT0                      _IICF.Bits.MULT0
#define IICF_MULT1                      _IICF.Bits.MULT1
#define IICF_ICR                        _IICF.MergedBits.grpICR
#define IICF_MULT                       _IICF.MergedBits.grpMULT

#define IICF_ICR0_MASK                  1U
#define IICF_ICR1_MASK                  2U
#define IICF_ICR2_MASK                  4U
#define IICF_ICR3_MASK                  8U
#define IICF_ICR4_MASK                  16U
#define IICF_ICR5_MASK                  32U
#define IICF_MULT0_MASK                 64U
#define IICF_MULT1_MASK                 128U
#define IICF_ICR_MASK                   63U
#define IICF_ICR_BITNUM                 0U
#define IICF_MULT_MASK                  192U
#define IICF_MULT_BITNUM                6U


/*** IICC1 - IIC Control Register 1; 0xFFFF8062 ***/
typedef union {
  byte Byte;
  union { /* Several registers at the same address */
    /*** IICC1 - IIC Control Register 1; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IICC1STR;
    #define IICC1                       _IICC1.Byte
    #define IICC1_RSTA                  _IICC1.SameAddr_STR.IICC1STR.Bits.RSTA
    #define IICC1_TXAK                  _IICC1.SameAddr_STR.IICC1STR.Bits.TXAK
    #define IICC1_TX                    _IICC1.SameAddr_STR.IICC1STR.Bits.TX
    #define IICC1_MST                   _IICC1.SameAddr_STR.IICC1STR.Bits.MST
    #define IICC1_IICIE                 _IICC1.SameAddr_STR.IICC1STR.Bits.IICIE
    #define IICC1_IICEN                 _IICC1.SameAddr_STR.IICC1STR.Bits.IICEN
    
    #define IICC1_RSTA_MASK             4U
    #define IICC1_TXAK_MASK             8U
    #define IICC1_TX_MASK               16U
    #define IICC1_MST_MASK              32U
    #define IICC1_IICIE_MASK            64U
    #define IICC1_IICEN_MASK            128U
    
    /*** IICC - IIC Control Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IICCSTR;
    #define IICC                        _IICC1.Byte
    #define IICC_RSTA                   _IICC1.SameAddr_STR.IICCSTR.Bits.RSTA
    #define IICC_TXAK                   _IICC1.SameAddr_STR.IICCSTR.Bits.TXAK
    #define IICC_TX                     _IICC1.SameAddr_STR.IICCSTR.Bits.TX
    #define IICC_MST                    _IICC1.SameAddr_STR.IICCSTR.Bits.MST
    #define IICC_IICIE                  _IICC1.SameAddr_STR.IICCSTR.Bits.IICIE
    #define IICC_IICEN                  _IICC1.SameAddr_STR.IICCSTR.Bits.IICEN
    
    #define IICC_RSTA_MASK              4U
    #define IICC_TXAK_MASK              8U
    #define IICC_TX_MASK                16U
    #define IICC_MST_MASK               32U
    #define IICC_IICIE_MASK             64U
    #define IICC_IICEN_MASK             128U
    
  } SameAddr_STR; /*Several registers at the same address */

} IICC1STR;
extern volatile IICC1STR _IICC1 @0xFFFF8062;


/*** IICS - IIC Status Register; 0xFFFF8063 ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1; 
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy */
    byte IAAS        :1;                                       /* Addressed as a Slave */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IICSSTR;
extern volatile IICSSTR _IICS @0xFFFF8063;
#define IICS                            _IICS.Byte
#define IICS_RXAK                       _IICS.Bits.RXAK
#define IICS_IICIF                      _IICS.Bits.IICIF
#define IICS_SRW                        _IICS.Bits.SRW
#define IICS_ARBL                       _IICS.Bits.ARBL
#define IICS_BUSY                       _IICS.Bits.BUSY
#define IICS_IAAS                       _IICS.Bits.IAAS
#define IICS_TCF                        _IICS.Bits.TCF

#define IICS_RXAK_MASK                  1U
#define IICS_IICIF_MASK                 2U
#define IICS_SRW_MASK                   4U
#define IICS_ARBL_MASK                  16U
#define IICS_BUSY_MASK                  32U
#define IICS_IAAS_MASK                  64U
#define IICS_TCF_MASK                   128U


/*** IICD - IIC Data I/O Register; 0xFFFF8064 ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IICDSTR;
extern volatile IICDSTR _IICD @0xFFFF8064;
#define IICD                            _IICD.Byte
#define IICD_DATA0                      _IICD.Bits.DATA0
#define IICD_DATA1                      _IICD.Bits.DATA1
#define IICD_DATA2                      _IICD.Bits.DATA2
#define IICD_DATA3                      _IICD.Bits.DATA3
#define IICD_DATA4                      _IICD.Bits.DATA4
#define IICD_DATA5                      _IICD.Bits.DATA5
#define IICD_DATA6                      _IICD.Bits.DATA6
#define IICD_DATA7                      _IICD.Bits.DATA7

#define IICD_DATA0_MASK                 1U
#define IICD_DATA1_MASK                 2U
#define IICD_DATA2_MASK                 4U
#define IICD_DATA3_MASK                 8U
#define IICD_DATA4_MASK                 16U
#define IICD_DATA5_MASK                 32U
#define IICD_DATA6_MASK                 64U
#define IICD_DATA7_MASK                 128U


/*** IICC2 - IIC Control Register 2; 0xFFFF8065 ***/
typedef union {
  byte Byte;
  struct {
    byte AD8         :1;                                       /* Slave Address Bit 8 */
    byte AD9         :1;                                       /* Slave Address Bit 9 */
    byte AD10        :1;                                       /* Slave Address Bit 10 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ADEXT       :1;                                       /* Address Extension */
    byte GCAEN       :1;                                       /* General Call Address Enable */
  } Bits;
  struct {
    byte grpAD_8 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} IICC2STR;
extern volatile IICC2STR _IICC2 @0xFFFF8065;
#define IICC2                           _IICC2.Byte
#define IICC2_AD8                       _IICC2.Bits.AD8
#define IICC2_AD9                       _IICC2.Bits.AD9
#define IICC2_AD10                      _IICC2.Bits.AD10
#define IICC2_ADEXT                     _IICC2.Bits.ADEXT
#define IICC2_GCAEN                     _IICC2.Bits.GCAEN
#define IICC2_AD_8                      _IICC2.MergedBits.grpAD_8
#define IICC2_AD                        IICC2_AD_8

#define IICC2_AD8_MASK                  1U
#define IICC2_AD9_MASK                  2U
#define IICC2_AD10_MASK                 4U
#define IICC2_ADEXT_MASK                64U
#define IICC2_GCAEN_MASK                128U
#define IICC2_AD_8_MASK                 7U
#define IICC2_AD_8_BITNUM               0U


/*** IICSMB - SMBus Control and Status Register; 0xFFFF8066 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte SHTF        :1;                                       /* SCL High Timeout Flag */
    byte SLTF        :1;                                       /* SCL Low Timeout Flag */
    byte TCKSEL      :1;                                       /* Time Out Counter Clock Select */
    byte SIICAEN     :1;                                       /* Second IIC Address Enable */
    byte ALERTEN     :1;                                       /* SMBus Alert Response Address Enable */
    byte FACK        :1;                                       /* Fast NACK/ACK enable */
  } Bits;
} IICSMBSTR;
extern volatile IICSMBSTR _IICSMB @0xFFFF8066;
#define IICSMB                          _IICSMB.Byte
#define IICSMB_SHTF                     _IICSMB.Bits.SHTF
#define IICSMB_SLTF                     _IICSMB.Bits.SLTF
#define IICSMB_TCKSEL                   _IICSMB.Bits.TCKSEL
#define IICSMB_SIICAEN                  _IICSMB.Bits.SIICAEN
#define IICSMB_ALERTEN                  _IICSMB.Bits.ALERTEN
#define IICSMB_FACK                     _IICSMB.Bits.FACK

#define IICSMB_SHTF_MASK                4U
#define IICSMB_SLTF_MASK                8U
#define IICSMB_TCKSEL_MASK              16U
#define IICSMB_SIICAEN_MASK             32U
#define IICSMB_ALERTEN_MASK             64U
#define IICSMB_FACK_MASK                128U


/*** IICA2 - IIC Address Register 2; 0xFFFF8067 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte SAD1        :1;                                       /* SMBus Address Bit 1 */
    byte SAD2        :1;                                       /* SMBus Address Bit 2 */
    byte SAD3        :1;                                       /* SMBus Address Bit 3 */
    byte SAD4        :1;                                       /* SMBus Address Bit 4 */
    byte SAD5        :1;                                       /* SMBus Address Bit 5 */
    byte SAD6        :1;                                       /* SMBus Address Bit 6 */
    byte SAD7        :1;                                       /* SMBus Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpSAD_1 :7;
  } MergedBits;
} IICA2STR;
extern volatile IICA2STR _IICA2 @0xFFFF8067;
#define IICA2                           _IICA2.Byte
#define IICA2_SAD1                      _IICA2.Bits.SAD1
#define IICA2_SAD2                      _IICA2.Bits.SAD2
#define IICA2_SAD3                      _IICA2.Bits.SAD3
#define IICA2_SAD4                      _IICA2.Bits.SAD4
#define IICA2_SAD5                      _IICA2.Bits.SAD5
#define IICA2_SAD6                      _IICA2.Bits.SAD6
#define IICA2_SAD7                      _IICA2.Bits.SAD7
#define IICA2_SAD_1                     _IICA2.MergedBits.grpSAD_1
#define IICA2_SAD                       IICA2_SAD_1

#define IICA2_SAD1_MASK                 2U
#define IICA2_SAD2_MASK                 4U
#define IICA2_SAD3_MASK                 8U
#define IICA2_SAD4_MASK                 16U
#define IICA2_SAD5_MASK                 32U
#define IICA2_SAD6_MASK                 64U
#define IICA2_SAD7_MASK                 128U
#define IICA2_SAD_1_MASK                254U
#define IICA2_SAD_1_BITNUM              1U


/*** IICSLT - IIC SCL Low Time Out register; 0xFFFF8068 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** IICSLTH - IIC SCL Low Time Out register - High byte; 0xFFFF8068 ***/
    union {
      byte Byte;
      struct {
        byte SSLT8       :1;                                       /* SCL Low Time Out Bit 8 */
        byte SSLT9       :1;                                       /* SCL Low Time Out Bit 9 */
        byte SSLT10      :1;                                       /* SCL Low Time Out Bit 10 */
        byte SSLT11      :1;                                       /* SCL Low Time Out Bit 11 */
        byte SSLT12      :1;                                       /* SCL Low Time Out Bit 12 */
        byte SSLT13      :1;                                       /* SCL Low Time Out Bit 13 */
        byte SSLT14      :1;                                       /* SCL Low Time Out Bit 14 */
        byte SSLT15      :1;                                       /* SCL Low Time Out Bit 15 */
      } Bits;
    } IICSLTHSTR;
    #define IICSLTH                     _IICSLT.Overlap_STR.IICSLTHSTR.Byte
    #define IICSLTH_SSLT8               _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT8
    #define IICSLTH_SSLT9               _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT9
    #define IICSLTH_SSLT10              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT10
    #define IICSLTH_SSLT11              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT11
    #define IICSLTH_SSLT12              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT12
    #define IICSLTH_SSLT13              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT13
    #define IICSLTH_SSLT14              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT14
    #define IICSLTH_SSLT15              _IICSLT.Overlap_STR.IICSLTHSTR.Bits.SSLT15
    
    #define IICSLTH_SSLT8_MASK          1U
    #define IICSLTH_SSLT9_MASK          2U
    #define IICSLTH_SSLT10_MASK         4U
    #define IICSLTH_SSLT11_MASK         8U
    #define IICSLTH_SSLT12_MASK         16U
    #define IICSLTH_SSLT13_MASK         32U
    #define IICSLTH_SSLT14_MASK         64U
    #define IICSLTH_SSLT15_MASK         128U
    

    /*** IICSLTL - IIC SCL Low Time Out register - Low byte; 0xFFFF8069 ***/
    union {
      byte Byte;
      struct {
        byte SSLT0       :1;                                       /* SCL Low Time Out Bits, bit 0 */
        byte SSLT1       :1;                                       /* SCL Low Time Out Bits, bit 1 */
        byte SSLT2       :1;                                       /* SCL Low Time Out Bits, bit 2 */
        byte SSLT3       :1;                                       /* SCL Low Time Out Bits, bit 3 */
        byte SSLT4       :1;                                       /* SCL Low Time Out Bits, bit 4 */
        byte SSLT5       :1;                                       /* SCL Low Time Out Bits, bit 5 */
        byte SSLT6       :1;                                       /* SCL Low Time Out Bits, bit 6 */
        byte SSLT7       :1;                                       /* SCL Low Time Out Bits, bit 7 */
      } Bits;
    } IICSLTLSTR;
    #define IICSLTL                     _IICSLT.Overlap_STR.IICSLTLSTR.Byte
    #define IICSLTL_SSLT0               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT0
    #define IICSLTL_SSLT1               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT1
    #define IICSLTL_SSLT2               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT2
    #define IICSLTL_SSLT3               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT3
    #define IICSLTL_SSLT4               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT4
    #define IICSLTL_SSLT5               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT5
    #define IICSLTL_SSLT6               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT6
    #define IICSLTL_SSLT7               _IICSLT.Overlap_STR.IICSLTLSTR.Bits.SSLT7
    
    #define IICSLTL_SSLT0_MASK          1U
    #define IICSLTL_SSLT1_MASK          2U
    #define IICSLTL_SSLT2_MASK          4U
    #define IICSLTL_SSLT3_MASK          8U
    #define IICSLTL_SSLT4_MASK          16U
    #define IICSLTL_SSLT5_MASK          32U
    #define IICSLTL_SSLT6_MASK          64U
    #define IICSLTL_SSLT7_MASK          128U
    
  } Overlap_STR;

  struct {
    word SSLT0       :1;                                       /* SCL Low Time Out Bits, bit 0 */
    word SSLT1       :1;                                       /* SCL Low Time Out Bits, bit 1 */
    word SSLT2       :1;                                       /* SCL Low Time Out Bits, bit 2 */
    word SSLT3       :1;                                       /* SCL Low Time Out Bits, bit 3 */
    word SSLT4       :1;                                       /* SCL Low Time Out Bits, bit 4 */
    word SSLT5       :1;                                       /* SCL Low Time Out Bits, bit 5 */
    word SSLT6       :1;                                       /* SCL Low Time Out Bits, bit 6 */
    word SSLT7       :1;                                       /* SCL Low Time Out Bits, bit 7 */
    word SSLT8       :1;                                       /* SCL Low Time Out Bits, bit 8 */
    word SSLT9       :1;                                       /* SCL Low Time Out Bits, bit 9 */
    word SSLT10      :1;                                       /* SCL Low Time Out Bits, bit 10 */
    word SSLT11      :1;                                       /* SCL Low Time Out Bits, bit 11 */
    word SSLT12      :1;                                       /* SCL Low Time Out Bits, bit 12 */
    word SSLT13      :1;                                       /* SCL Low Time Out Bits, bit 13 */
    word SSLT14      :1;                                       /* SCL Low Time Out Bits, bit 14 */
    word SSLT15      :1;                                       /* SCL Low Time Out Bits, bit 15 */
  } Bits;
} IICSLTSTR;
extern volatile IICSLTSTR _IICSLT @0xFFFF8068;
#define IICSLT                          _IICSLT.Word
#define IICSLT_SSLT0                    _IICSLT.Bits.SSLT0
#define IICSLT_SSLT1                    _IICSLT.Bits.SSLT1
#define IICSLT_SSLT2                    _IICSLT.Bits.SSLT2
#define IICSLT_SSLT3                    _IICSLT.Bits.SSLT3
#define IICSLT_SSLT4                    _IICSLT.Bits.SSLT4
#define IICSLT_SSLT5                    _IICSLT.Bits.SSLT5
#define IICSLT_SSLT6                    _IICSLT.Bits.SSLT6
#define IICSLT_SSLT7                    _IICSLT.Bits.SSLT7
#define IICSLT_SSLT8                    _IICSLT.Bits.SSLT8
#define IICSLT_SSLT9                    _IICSLT.Bits.SSLT9
#define IICSLT_SSLT10                   _IICSLT.Bits.SSLT10
#define IICSLT_SSLT11                   _IICSLT.Bits.SSLT11
#define IICSLT_SSLT12                   _IICSLT.Bits.SSLT12
#define IICSLT_SSLT13                   _IICSLT.Bits.SSLT13
#define IICSLT_SSLT14                   _IICSLT.Bits.SSLT14
#define IICSLT_SSLT15                   _IICSLT.Bits.SSLT15

#define IICSLT_SSLT0_MASK               1U
#define IICSLT_SSLT1_MASK               2U
#define IICSLT_SSLT2_MASK               4U
#define IICSLT_SSLT3_MASK               8U
#define IICSLT_SSLT4_MASK               16U
#define IICSLT_SSLT5_MASK               32U
#define IICSLT_SSLT6_MASK               64U
#define IICSLT_SSLT7_MASK               128U
#define IICSLT_SSLT8_MASK               256U
#define IICSLT_SSLT9_MASK               512U
#define IICSLT_SSLT10_MASK              1024U
#define IICSLT_SSLT11_MASK              2048U
#define IICSLT_SSLT12_MASK              4096U
#define IICSLT_SSLT13_MASK              8192U
#define IICSLT_SSLT14_MASK              16384U
#define IICSLT_SSLT15_MASK              32768U


/*** IICFLT - IIC Filter register; 0xFFFF806A ***/
typedef union {
  byte Byte;
  struct {
    byte FLT0        :1;                                       /* Filter value bit 0 */
    byte FLT1        :1;                                       /* Filter value bit 1 */
    byte FLT2        :1;                                       /* Filter value bit 2 */
    byte FLT3        :1;                                       /* Filter value bit 3 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpFLT  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} IICFLTSTR;
extern volatile IICFLTSTR _IICFLT @0xFFFF806A;
#define IICFLT                          _IICFLT.Byte
#define IICFLT_FLT0                     _IICFLT.Bits.FLT0
#define IICFLT_FLT1                     _IICFLT.Bits.FLT1
#define IICFLT_FLT2                     _IICFLT.Bits.FLT2
#define IICFLT_FLT3                     _IICFLT.Bits.FLT3
#define IICFLT_FLT                      _IICFLT.MergedBits.grpFLT

#define IICFLT_FLT0_MASK                1U
#define IICFLT_FLT1_MASK                2U
#define IICFLT_FLT2_MASK                4U
#define IICFLT_FLT3_MASK                8U
#define IICFLT_FLT_MASK                 15U
#define IICFLT_FLT_BITNUM               0U


/*** KBI1SC - KBI1 Status and Control Register; 0xFFFF806C ***/
typedef union {
  byte Byte;
  struct {
    byte KBI1MOD     :1;                                       /* Keyboard Detection Mode */
    byte KB1IE       :1;                                       /* Keyboard Interrupt Enable */
    byte KB1ACK      :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KB1F        :1;                                       /* Keyboard Interrupt Flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} KBI1SCSTR;
extern volatile KBI1SCSTR _KBI1SC @0xFFFF806C;
#define KBI1SC                          _KBI1SC.Byte
#define KBI1SC_KBI1MOD                  _KBI1SC.Bits.KBI1MOD
#define KBI1SC_KB1IE                    _KBI1SC.Bits.KB1IE
#define KBI1SC_KB1ACK                   _KBI1SC.Bits.KB1ACK
#define KBI1SC_KB1F                     _KBI1SC.Bits.KB1F

#define KBI1SC_KBI1MOD_MASK             1U
#define KBI1SC_KB1IE_MASK               2U
#define KBI1SC_KB1ACK_MASK              4U
#define KBI1SC_KB1F_MASK                8U


/*** KBI1PE - KBI1 Pin Enable Register; 0xFFFF806D ***/
typedef union {
  byte Byte;
  struct {
    byte KBI1PE0     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 0 */
    byte KBI1PE1     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 1 */
    byte KBI1PE2     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 2 */
    byte KBI1PE3     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 3 */
    byte KBI1PE4     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 4 */
    byte KBI1PE5     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 5 */
    byte KBI1PE6     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 6 */
    byte KBI1PE7     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 7 */
  } Bits;
} KBI1PESTR;
extern volatile KBI1PESTR _KBI1PE @0xFFFF806D;
#define KBI1PE                          _KBI1PE.Byte
#define KBI1PE_KBI1PE0                  _KBI1PE.Bits.KBI1PE0
#define KBI1PE_KBI1PE1                  _KBI1PE.Bits.KBI1PE1
#define KBI1PE_KBI1PE2                  _KBI1PE.Bits.KBI1PE2
#define KBI1PE_KBI1PE3                  _KBI1PE.Bits.KBI1PE3
#define KBI1PE_KBI1PE4                  _KBI1PE.Bits.KBI1PE4
#define KBI1PE_KBI1PE5                  _KBI1PE.Bits.KBI1PE5
#define KBI1PE_KBI1PE6                  _KBI1PE.Bits.KBI1PE6
#define KBI1PE_KBI1PE7                  _KBI1PE.Bits.KBI1PE7

#define KBI1PE_KBI1PE0_MASK             1U
#define KBI1PE_KBI1PE1_MASK             2U
#define KBI1PE_KBI1PE2_MASK             4U
#define KBI1PE_KBI1PE3_MASK             8U
#define KBI1PE_KBI1PE4_MASK             16U
#define KBI1PE_KBI1PE5_MASK             32U
#define KBI1PE_KBI1PE6_MASK             64U
#define KBI1PE_KBI1PE7_MASK             128U


/*** KBI1ES - KBI1 Edge Select Register; 0xFFFF806E ***/
typedef union {
  byte Byte;
  struct {
    byte KB1EDG0     :1;                                       /* Keyboard Edge Select Bit 0 */
    byte KB1EDG1     :1;                                       /* Keyboard Edge Select Bit 1 */
    byte KB1EDG2     :1;                                       /* Keyboard Edge Select Bit 2 */
    byte KB1EDG3     :1;                                       /* Keyboard Edge Select Bit 3 */
    byte KB1EDG4     :1;                                       /* Keyboard Edge Select Bit 4 */
    byte KB1EDG5     :1;                                       /* Keyboard Edge Select Bit 5 */
    byte KB1EDG6     :1;                                       /* Keyboard Edge Select Bit 6 */
    byte KB1EDG7     :1;                                       /* Keyboard Edge Select Bit 7 */
  } Bits;
} KBI1ESSTR;
extern volatile KBI1ESSTR _KBI1ES @0xFFFF806E;
#define KBI1ES                          _KBI1ES.Byte
#define KBI1ES_KB1EDG0                  _KBI1ES.Bits.KB1EDG0
#define KBI1ES_KB1EDG1                  _KBI1ES.Bits.KB1EDG1
#define KBI1ES_KB1EDG2                  _KBI1ES.Bits.KB1EDG2
#define KBI1ES_KB1EDG3                  _KBI1ES.Bits.KB1EDG3
#define KBI1ES_KB1EDG4                  _KBI1ES.Bits.KB1EDG4
#define KBI1ES_KB1EDG5                  _KBI1ES.Bits.KB1EDG5
#define KBI1ES_KB1EDG6                  _KBI1ES.Bits.KB1EDG6
#define KBI1ES_KB1EDG7                  _KBI1ES.Bits.KB1EDG7

#define KBI1ES_KB1EDG0_MASK             1U
#define KBI1ES_KB1EDG1_MASK             2U
#define KBI1ES_KB1EDG2_MASK             4U
#define KBI1ES_KB1EDG3_MASK             8U
#define KBI1ES_KB1EDG4_MASK             16U
#define KBI1ES_KB1EDG5_MASK             32U
#define KBI1ES_KB1EDG6_MASK             64U
#define KBI1ES_KB1EDG7_MASK             128U


/*** SPI1C1 - SPI1 Control Register 1; 0xFFFF8070 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (Shifter Direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI System Enable */
    byte SPIE        :1;                                       /* SPI Interrupt Enable (for SPRF and MODF) */
  } Bits;
} SPI1C1STR;
extern volatile SPI1C1STR _SPI1C1 @0xFFFF8070;
#define SPI1C1                          _SPI1C1.Byte
#define SPI1C1_LSBFE                    _SPI1C1.Bits.LSBFE
#define SPI1C1_SSOE                     _SPI1C1.Bits.SSOE
#define SPI1C1_CPHA                     _SPI1C1.Bits.CPHA
#define SPI1C1_CPOL                     _SPI1C1.Bits.CPOL
#define SPI1C1_MSTR                     _SPI1C1.Bits.MSTR
#define SPI1C1_SPTIE                    _SPI1C1.Bits.SPTIE
#define SPI1C1_SPE                      _SPI1C1.Bits.SPE
#define SPI1C1_SPIE                     _SPI1C1.Bits.SPIE

#define SPI1C1_LSBFE_MASK               1U
#define SPI1C1_SSOE_MASK                2U
#define SPI1C1_CPHA_MASK                4U
#define SPI1C1_CPOL_MASK                8U
#define SPI1C1_MSTR_MASK                16U
#define SPI1C1_SPTIE_MASK               32U
#define SPI1C1_SPE_MASK                 64U
#define SPI1C1_SPIE_MASK                128U


/*** SPI1C2 - SPI1 Control Register 2; 0xFFFF8071 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte SPIMODE     :1;                                       /* SPI 8- or 16-bit Mode Select */
    byte SPMIE       :1;                                       /* SPI Match Interrupt Enable */
  } Bits;
} SPI1C2STR;
extern volatile SPI1C2STR _SPI1C2 @0xFFFF8071;
#define SPI1C2                          _SPI1C2.Byte
#define SPI1C2_SPC0                     _SPI1C2.Bits.SPC0
#define SPI1C2_SPISWAI                  _SPI1C2.Bits.SPISWAI
#define SPI1C2_BIDIROE                  _SPI1C2.Bits.BIDIROE
#define SPI1C2_MODFEN                   _SPI1C2.Bits.MODFEN
#define SPI1C2_SPIMODE                  _SPI1C2.Bits.SPIMODE
#define SPI1C2_SPMIE                    _SPI1C2.Bits.SPMIE

#define SPI1C2_SPC0_MASK                1U
#define SPI1C2_SPISWAI_MASK             2U
#define SPI1C2_BIDIROE_MASK             8U
#define SPI1C2_MODFEN_MASK              16U
#define SPI1C2_SPIMODE_MASK             64U
#define SPI1C2_SPMIE_MASK               128U


/*** SPI1BR - SPI1 Baud Rate Register; 0xFFFF8072 ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI Baud Rate Divisor Bit 2 */
    byte SPR3        :1;                                       /* SPI Baud Rate Divisor Bit 3 */
    byte SPPR0       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :4;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI1BRSTR;
extern volatile SPI1BRSTR _SPI1BR @0xFFFF8072;
#define SPI1BR                          _SPI1BR.Byte
#define SPI1BR_SPR0                     _SPI1BR.Bits.SPR0
#define SPI1BR_SPR1                     _SPI1BR.Bits.SPR1
#define SPI1BR_SPR2                     _SPI1BR.Bits.SPR2
#define SPI1BR_SPR3                     _SPI1BR.Bits.SPR3
#define SPI1BR_SPPR0                    _SPI1BR.Bits.SPPR0
#define SPI1BR_SPPR1                    _SPI1BR.Bits.SPPR1
#define SPI1BR_SPPR2                    _SPI1BR.Bits.SPPR2
#define SPI1BR_SPR                      _SPI1BR.MergedBits.grpSPR
#define SPI1BR_SPPR                     _SPI1BR.MergedBits.grpSPPR

#define SPI1BR_SPR0_MASK                1U
#define SPI1BR_SPR1_MASK                2U
#define SPI1BR_SPR2_MASK                4U
#define SPI1BR_SPR3_MASK                8U
#define SPI1BR_SPPR0_MASK               16U
#define SPI1BR_SPPR1_MASK               32U
#define SPI1BR_SPPR2_MASK               64U
#define SPI1BR_SPR_MASK                 15U
#define SPI1BR_SPR_BITNUM               0U
#define SPI1BR_SPPR_MASK                112U
#define SPI1BR_SPPR_BITNUM              4U


/*** SPI1S - SPI1 Status Register; 0xFFFF8073 ***/
typedef union {
  byte Byte;
  struct {
    byte RFIFOEF     :1;                                       /* SPI Read FIFO Empty Flag */
    byte TXFULLF     :1;                                       /* SPI Transmit FIFO Full Flag */
    byte TNEAREF     :1;                                       /* SPI Transmit FIFO Nearly Empty Flag */
    byte RNFULLF     :1;                                       /* SPI Receive FIFO Nearly Full Flag */
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI Transmit Buffer Empty Flag */
    byte SPMF        :1;                                       /* SPI Match Flag */
    byte SPRF        :1;                                       /* SPI Read Buffer Full Flag */
  } Bits;
} SPI1SSTR;
extern volatile SPI1SSTR _SPI1S @0xFFFF8073;
#define SPI1S                           _SPI1S.Byte
#define SPI1S_RFIFOEF                   _SPI1S.Bits.RFIFOEF
#define SPI1S_TXFULLF                   _SPI1S.Bits.TXFULLF
#define SPI1S_TNEAREF                   _SPI1S.Bits.TNEAREF
#define SPI1S_RNFULLF                   _SPI1S.Bits.RNFULLF
#define SPI1S_MODF                      _SPI1S.Bits.MODF
#define SPI1S_SPTEF                     _SPI1S.Bits.SPTEF
#define SPI1S_SPMF                      _SPI1S.Bits.SPMF
#define SPI1S_SPRF                      _SPI1S.Bits.SPRF

#define SPI1S_RFIFOEF_MASK              1U
#define SPI1S_TXFULLF_MASK              2U
#define SPI1S_TNEAREF_MASK              4U
#define SPI1S_RNFULLF_MASK              8U
#define SPI1S_MODF_MASK                 16U
#define SPI1S_SPTEF_MASK                32U
#define SPI1S_SPMF_MASK                 64U
#define SPI1S_SPRF_MASK                 128U


/*** SPI1D16 - SPI1 Data Register; 0xFFFF8074 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SPI1DH - SPI1 Data Register High; 0xFFFF8074 ***/
    union {
      byte Byte;
    } SPI1DHSTR;
    #define SPI1DH                      _SPI1D16.Overlap_STR.SPI1DHSTR.Byte
    

    /*** SPI1DL - SPI1 Data Register Low; 0xFFFF8075 ***/
    union {
      byte Byte;
      union { /* Several registers at the same address */
        /*** SPI1DL - SPI1 Data Register Low; Several registers at the same address ***/
        #define SPI1DL                  _SPI1D16.Overlap_STR.SPI1DLSTR.Byte
        
        /*** SPI1D - SPI1 Data Register Low; Several registers at the same address ***/
        union {
          struct {
            byte Bit0        :1;                                       /* SPI Data Bit 0 */
            byte Bit1        :1;                                       /* SPI Data Bit 1 */
            byte Bit2        :1;                                       /* SPI Data Bit 2 */
            byte Bit3        :1;                                       /* SPI Data Bit 3 */
            byte Bit4        :1;                                       /* SPI Data Bit 4 */
            byte Bit5        :1;                                       /* SPI Data Bit 5 */
            byte Bit6        :1;                                       /* SPI Data Bit 6 */
            byte Bit7        :1;                                       /* SPI Data Bit 7 */
          } Bits;
        } SPI1DSTR;
        #define SPI1D                   _SPI1D16.Overlap_STR.SPI1DLSTR.Byte
        #define SPI1D_Bit0              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit0
        #define SPI1D_Bit1              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit1
        #define SPI1D_Bit2              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit2
        #define SPI1D_Bit3              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit3
        #define SPI1D_Bit4              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit4
        #define SPI1D_Bit5              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit5
        #define SPI1D_Bit6              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit6
        #define SPI1D_Bit7              _SPI1D16.Overlap_STR.SPI1DLSTR.SameAddr_STR.SPI1DSTR.Bits.Bit7
        
        #define SPI1D_Bit0_MASK         1U
        #define SPI1D_Bit1_MASK         2U
        #define SPI1D_Bit2_MASK         4U
        #define SPI1D_Bit3_MASK         8U
        #define SPI1D_Bit4_MASK         16U
        #define SPI1D_Bit5_MASK         32U
        #define SPI1D_Bit6_MASK         64U
        #define SPI1D_Bit7_MASK         128U
        
      } SameAddr_STR; /*Several registers at the same address */
    
    } SPI1DLSTR;
    
  } Overlap_STR;

} SPI1D16STR;
extern volatile SPI1D16STR _SPI1D16 @0xFFFF8074;
#define SPI1D16                         _SPI1D16.Word


/*** SPI1M - SPI1 Match Register; 0xFFFF8076 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SPI1MH - SPI1 Match Register High; 0xFFFF8076 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* SPI Match Value Bit 8 */
        byte Bit9        :1;                                       /* SPI Match Value Bit 9 */
        byte Bit10       :1;                                       /* SPI Match Value Bit 10 */
        byte Bit11       :1;                                       /* SPI Match Value Bit 11 */
        byte Bit12       :1;                                       /* SPI Match Value Bit 12 */
        byte Bit13       :1;                                       /* SPI Match Value Bit 13 */
        byte Bit14       :1;                                       /* SPI Match Value Bit 14 */
        byte Bit15       :1;                                       /* SPI Match Value Bit 15 */
      } Bits;
    } SPI1MHSTR;
    #define SPI1MH                      _SPI1M.Overlap_STR.SPI1MHSTR.Byte
    #define SPI1MH_Bit8                 _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit8
    #define SPI1MH_Bit9                 _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit9
    #define SPI1MH_Bit10                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit10
    #define SPI1MH_Bit11                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit11
    #define SPI1MH_Bit12                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit12
    #define SPI1MH_Bit13                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit13
    #define SPI1MH_Bit14                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit14
    #define SPI1MH_Bit15                _SPI1M.Overlap_STR.SPI1MHSTR.Bits.Bit15
    
    #define SPI1MH_Bit8_MASK            1U
    #define SPI1MH_Bit9_MASK            2U
    #define SPI1MH_Bit10_MASK           4U
    #define SPI1MH_Bit11_MASK           8U
    #define SPI1MH_Bit12_MASK           16U
    #define SPI1MH_Bit13_MASK           32U
    #define SPI1MH_Bit14_MASK           64U
    #define SPI1MH_Bit15_MASK           128U
    

    /*** SPI1ML - SPI1 Match Register Low; 0xFFFF8077 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* SPI Match Value Bit 0 */
        byte Bit1        :1;                                       /* SPI Match Value Bit 1 */
        byte Bit2        :1;                                       /* SPI Match Value Bit 2 */
        byte Bit3        :1;                                       /* SPI Match Value Bit 3 */
        byte Bit4        :1;                                       /* SPI Match Value Bit 4 */
        byte Bit5        :1;                                       /* SPI Match Value Bit 5 */
        byte Bit6        :1;                                       /* SPI Match Value Bit 6 */
        byte Bit7        :1;                                       /* SPI Match Value Bit 7 */
      } Bits;
    } SPI1MLSTR;
    #define SPI1ML                      _SPI1M.Overlap_STR.SPI1MLSTR.Byte
    #define SPI1ML_Bit0                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit0
    #define SPI1ML_Bit1                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit1
    #define SPI1ML_Bit2                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit2
    #define SPI1ML_Bit3                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit3
    #define SPI1ML_Bit4                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit4
    #define SPI1ML_Bit5                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit5
    #define SPI1ML_Bit6                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit6
    #define SPI1ML_Bit7                 _SPI1M.Overlap_STR.SPI1MLSTR.Bits.Bit7
    
    #define SPI1ML_Bit0_MASK            1U
    #define SPI1ML_Bit1_MASK            2U
    #define SPI1ML_Bit2_MASK            4U
    #define SPI1ML_Bit3_MASK            8U
    #define SPI1ML_Bit4_MASK            16U
    #define SPI1ML_Bit5_MASK            32U
    #define SPI1ML_Bit6_MASK            64U
    #define SPI1ML_Bit7_MASK            128U
    
  } Overlap_STR;

  struct {
    word Bit0        :1;                                       /* SPI Match Value Bit 0 */
    word Bit1        :1;                                       /* SPI Match Value Bit 1 */
    word Bit2        :1;                                       /* SPI Match Value Bit 2 */
    word Bit3        :1;                                       /* SPI Match Value Bit 3 */
    word Bit4        :1;                                       /* SPI Match Value Bit 4 */
    word Bit5        :1;                                       /* SPI Match Value Bit 5 */
    word Bit6        :1;                                       /* SPI Match Value Bit 6 */
    word Bit7        :1;                                       /* SPI Match Value Bit 7 */
    word Bit8        :1;                                       /* SPI Match Value Bit 8 */
    word Bit9        :1;                                       /* SPI Match Value Bit 9 */
    word Bit10       :1;                                       /* SPI Match Value Bit 10 */
    word Bit11       :1;                                       /* SPI Match Value Bit 11 */
    word Bit12       :1;                                       /* SPI Match Value Bit 12 */
    word Bit13       :1;                                       /* SPI Match Value Bit 13 */
    word Bit14       :1;                                       /* SPI Match Value Bit 14 */
    word Bit15       :1;                                       /* SPI Match Value Bit 15 */
  } Bits;
} SPI1MSTR;
extern volatile SPI1MSTR _SPI1M @0xFFFF8076;
#define SPI1M                           _SPI1M.Word
#define SPI1M_Bit0                      _SPI1M.Bits.Bit0
#define SPI1M_Bit1                      _SPI1M.Bits.Bit1
#define SPI1M_Bit2                      _SPI1M.Bits.Bit2
#define SPI1M_Bit3                      _SPI1M.Bits.Bit3
#define SPI1M_Bit4                      _SPI1M.Bits.Bit4
#define SPI1M_Bit5                      _SPI1M.Bits.Bit5
#define SPI1M_Bit6                      _SPI1M.Bits.Bit6
#define SPI1M_Bit7                      _SPI1M.Bits.Bit7
#define SPI1M_Bit8                      _SPI1M.Bits.Bit8
#define SPI1M_Bit9                      _SPI1M.Bits.Bit9
#define SPI1M_Bit10                     _SPI1M.Bits.Bit10
#define SPI1M_Bit11                     _SPI1M.Bits.Bit11
#define SPI1M_Bit12                     _SPI1M.Bits.Bit12
#define SPI1M_Bit13                     _SPI1M.Bits.Bit13
#define SPI1M_Bit14                     _SPI1M.Bits.Bit14
#define SPI1M_Bit15                     _SPI1M.Bits.Bit15

#define SPI1M_Bit0_MASK                 1U
#define SPI1M_Bit1_MASK                 2U
#define SPI1M_Bit2_MASK                 4U
#define SPI1M_Bit3_MASK                 8U
#define SPI1M_Bit4_MASK                 16U
#define SPI1M_Bit5_MASK                 32U
#define SPI1M_Bit6_MASK                 64U
#define SPI1M_Bit7_MASK                 128U
#define SPI1M_Bit8_MASK                 256U
#define SPI1M_Bit9_MASK                 512U
#define SPI1M_Bit10_MASK                1024U
#define SPI1M_Bit11_MASK                2048U
#define SPI1M_Bit12_MASK                4096U
#define SPI1M_Bit13_MASK                8192U
#define SPI1M_Bit14_MASK                16384U
#define SPI1M_Bit15_MASK                32768U


/*** SPI1C3 - SPI1 Control Register 3; 0xFFFF8078 ***/
typedef union {
  byte Byte;
  struct {
    byte FIFOMODE    :1;                                       /* SPI FIFO Mode Enable */
    byte RNFULLIEN   :1;                                       /* Receive FIFO Nearly Full Interrupt Enable. This is an additional interrupt on the SPI and will only interrupt the CPU if SPIE in the SPIxC1 register is also set. This bit is ignored and has no function if FIFOMODE=0 */
    byte TNEARIEN    :1;                                       /* Transmit FIFO Nearly Empty Interrupt Enable. This is an additional interrupt on the SPI and will only interrupt the CPU if SPTIE in the <br/>SPIxC1 register is also set. This bit is ignored and has no function if FIFOMODE=0 */
    byte INTCLR      :1;                                       /* Interrupt Clearing Mechanism Select - This bit selects the mechanism by which SPRF, SPTEF, TNEAREF, RNFULLF interrupts gets cleared */
    byte RNFULLF_MARK :1;                                      /* Receive FIFO Nearly Full Water Mark - This bit selects the mark for which RNFULLF flag is asserted */
    byte TNEAREF_MARK :1;                                      /* Transmit FIFO Nearly Empty Water Mark - This bit selects the mark after which TNEAREF flag is asserted */
    byte             :1; 
    byte             :1; 
  } Bits;
} SPI1C3STR;
extern volatile SPI1C3STR _SPI1C3 @0xFFFF8078;
#define SPI1C3                          _SPI1C3.Byte
#define SPI1C3_FIFOMODE                 _SPI1C3.Bits.FIFOMODE
#define SPI1C3_RNFULLIEN                _SPI1C3.Bits.RNFULLIEN
#define SPI1C3_TNEARIEN                 _SPI1C3.Bits.TNEARIEN
#define SPI1C3_INTCLR                   _SPI1C3.Bits.INTCLR
#define SPI1C3_RNFULLF_MARK             _SPI1C3.Bits.RNFULLF_MARK
#define SPI1C3_TNEAREF_MARK             _SPI1C3.Bits.TNEAREF_MARK

#define SPI1C3_FIFOMODE_MASK            1U
#define SPI1C3_RNFULLIEN_MASK           2U
#define SPI1C3_TNEARIEN_MASK            4U
#define SPI1C3_INTCLR_MASK              8U
#define SPI1C3_RNFULLF_MARK_MASK        16U
#define SPI1C3_TNEAREF_MARK_MASK        32U


/*** SPI1CI - SPI1 Clear Interrupt Register; 0xFFFF8079 ***/
typedef union {
  byte Byte;
  struct {
    byte SPRFCI      :1;                                       /* Receive FIFO Full Flag Clear Interrupt Bit - Write of 1 clears the TNEAREF interrupt provided SPIxC3[3] is set */
    byte SPTEFCI     :1;                                       /* Transmit FIFO Empty Flag Clear Interrupt Bit - Write of 1 clears the SPTEF interrupt provided SPIxC3[3] SPTEFCI is set */
    byte RNFULLFCI   :1;                                       /* Receive FIFO Nearly Full Flag Clear Interrupt - Write of 1 clears the RNFULLF interrupt provided SPIxC3[3] is set */
    byte TNEAREFCI   :1;                                       /* Transmit FIFO Nearly Empty Flag Clear Interrupt Bit - Write of 1 clears the TNEAREF interrupt provided SPIxC3[3] is set */
    byte RXFOF       :1;                                       /* RX FIFO Overflow Flag - This Flag indicates that RX FIFO overflow condition has occured */
    byte TXFOF       :1;                                       /* TX FIFO Overflow Flag - This Flag indicates that TX FIFO overflow condition has occured */
    byte RXFERR      :1;                                       /* Receive FIFO Error Flag - This flag indicates that RX FIFO error occured because entries in fifo goes above 8 */
    byte TXFERR      :1;                                       /* Transmit FIFO ErrorFlag - This flag indicates that TX FIFO error occured because entries in fifo goes above 8 */
  } Bits;
} SPI1CISTR;
extern volatile SPI1CISTR _SPI1CI @0xFFFF8079;
#define SPI1CI                          _SPI1CI.Byte
#define SPI1CI_SPRFCI                   _SPI1CI.Bits.SPRFCI
#define SPI1CI_SPTEFCI                  _SPI1CI.Bits.SPTEFCI
#define SPI1CI_RNFULLFCI                _SPI1CI.Bits.RNFULLFCI
#define SPI1CI_TNEAREFCI                _SPI1CI.Bits.TNEAREFCI
#define SPI1CI_RXFOF                    _SPI1CI.Bits.RXFOF
#define SPI1CI_TXFOF                    _SPI1CI.Bits.TXFOF
#define SPI1CI_RXFERR                   _SPI1CI.Bits.RXFERR
#define SPI1CI_TXFERR                   _SPI1CI.Bits.TXFERR

#define SPI1CI_SPRFCI_MASK              1U
#define SPI1CI_SPTEFCI_MASK             2U
#define SPI1CI_RNFULLFCI_MASK           4U
#define SPI1CI_TNEAREFCI_MASK           8U
#define SPI1CI_RXFOF_MASK               16U
#define SPI1CI_TXFOF_MASK               32U
#define SPI1CI_RXFERR_MASK              64U
#define SPI1CI_TXFERR_MASK              128U


/*** KBI2SC - KBI2 Status and Control Register; 0xFFFF807C ***/
typedef union {
  byte Byte;
  struct {
    byte KBI2MOD     :1;                                       /* Keyboard Detection Mode */
    byte KB2IE       :1;                                       /* Keyboard Interrupt Enable */
    byte KB2ACK      :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KB2F        :1;                                       /* Keyboard Interrupt Flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} KBI2SCSTR;
extern volatile KBI2SCSTR _KBI2SC @0xFFFF807C;
#define KBI2SC                          _KBI2SC.Byte
#define KBI2SC_KBI2MOD                  _KBI2SC.Bits.KBI2MOD
#define KBI2SC_KB2IE                    _KBI2SC.Bits.KB2IE
#define KBI2SC_KB2ACK                   _KBI2SC.Bits.KB2ACK
#define KBI2SC_KB2F                     _KBI2SC.Bits.KB2F

#define KBI2SC_KBI2MOD_MASK             1U
#define KBI2SC_KB2IE_MASK               2U
#define KBI2SC_KB2ACK_MASK              4U
#define KBI2SC_KB2F_MASK                8U


/*** KBI2PE - KBI2 Pin Enable Register; 0xFFFF807D ***/
typedef union {
  byte Byte;
  struct {
    byte KBI2PE0     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 0 */
    byte KBI2PE1     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 1 */
    byte KBI2PE2     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 2 */
    byte KBI2PE3     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 3 */
    byte KBI2PE4     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 4 */
    byte KBI2PE5     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 5 */
    byte KBI2PE6     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 6 */
    byte KBI2PE7     :1;                                       /* Keyboard Pin Enable for KBI Port Bit 7 */
  } Bits;
} KBI2PESTR;
extern volatile KBI2PESTR _KBI2PE @0xFFFF807D;
#define KBI2PE                          _KBI2PE.Byte
#define KBI2PE_KBI2PE0                  _KBI2PE.Bits.KBI2PE0
#define KBI2PE_KBI2PE1                  _KBI2PE.Bits.KBI2PE1
#define KBI2PE_KBI2PE2                  _KBI2PE.Bits.KBI2PE2
#define KBI2PE_KBI2PE3                  _KBI2PE.Bits.KBI2PE3
#define KBI2PE_KBI2PE4                  _KBI2PE.Bits.KBI2PE4
#define KBI2PE_KBI2PE5                  _KBI2PE.Bits.KBI2PE5
#define KBI2PE_KBI2PE6                  _KBI2PE.Bits.KBI2PE6
#define KBI2PE_KBI2PE7                  _KBI2PE.Bits.KBI2PE7

#define KBI2PE_KBI2PE0_MASK             1U
#define KBI2PE_KBI2PE1_MASK             2U
#define KBI2PE_KBI2PE2_MASK             4U
#define KBI2PE_KBI2PE3_MASK             8U
#define KBI2PE_KBI2PE4_MASK             16U
#define KBI2PE_KBI2PE5_MASK             32U
#define KBI2PE_KBI2PE6_MASK             64U
#define KBI2PE_KBI2PE7_MASK             128U


/*** KBI2ES - KBI2 Edge Select Register; 0xFFFF807E ***/
typedef union {
  byte Byte;
  struct {
    byte KB2EDG0     :1;                                       /* Keyboard Edge Select Bit 0 */
    byte KB2EDG1     :1;                                       /* Keyboard Edge Select Bit 1 */
    byte KB2EDG2     :1;                                       /* Keyboard Edge Select Bit 2 */
    byte KB2EDG3     :1;                                       /* Keyboard Edge Select Bit 3 */
    byte KB2EDG4     :1;                                       /* Keyboard Edge Select Bit 4 */
    byte KB2EDG5     :1;                                       /* Keyboard Edge Select Bit 5 */
    byte KB2EDG6     :1;                                       /* Keyboard Edge Select Bit 6 */
    byte KB2EDG7     :1;                                       /* Keyboard Edge Select Bit 7 */
  } Bits;
} KBI2ESSTR;
extern volatile KBI2ESSTR _KBI2ES @0xFFFF807E;
#define KBI2ES                          _KBI2ES.Byte
#define KBI2ES_KB2EDG0                  _KBI2ES.Bits.KB2EDG0
#define KBI2ES_KB2EDG1                  _KBI2ES.Bits.KB2EDG1
#define KBI2ES_KB2EDG2                  _KBI2ES.Bits.KB2EDG2
#define KBI2ES_KB2EDG3                  _KBI2ES.Bits.KB2EDG3
#define KBI2ES_KB2EDG4                  _KBI2ES.Bits.KB2EDG4
#define KBI2ES_KB2EDG5                  _KBI2ES.Bits.KB2EDG5
#define KBI2ES_KB2EDG6                  _KBI2ES.Bits.KB2EDG6
#define KBI2ES_KB2EDG7                  _KBI2ES.Bits.KB2EDG7

#define KBI2ES_KB2EDG0_MASK             1U
#define KBI2ES_KB2EDG1_MASK             2U
#define KBI2ES_KB2EDG2_MASK             4U
#define KBI2ES_KB2EDG3_MASK             8U
#define KBI2ES_KB2EDG4_MASK             16U
#define KBI2ES_KB2EDG5_MASK             32U
#define KBI2ES_KB2EDG6_MASK             64U
#define KBI2ES_KB2EDG7_MASK             128U


/*** SRS - System Reset Status Register; 0xFFFF9800 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte LVD         :1;                                       /* Low Voltage Detect */
    byte LOC         :1;                                       /* Loss-of-Clock Reset */
    byte ILAD        :1;                                       /* Illegal Address */
    byte ILOP        :1;                                       /* Illegal Opcode */
    byte COP         :1;                                       /* Computer Operating Properly (COP) Watchdog */
    byte PIN         :1;                                       /* External Reset Pin */
    byte POR         :1;                                       /* Power-On Reset */
  } Bits;
} SRSSTR;
extern volatile SRSSTR _SRS @0xFFFF9800;
#define SRS                             _SRS.Byte
#define SRS_LVD                         _SRS.Bits.LVD
#define SRS_LOC                         _SRS.Bits.LOC
#define SRS_ILAD                        _SRS.Bits.ILAD
#define SRS_ILOP                        _SRS.Bits.ILOP
#define SRS_COP                         _SRS.Bits.COP
#define SRS_PIN                         _SRS.Bits.PIN
#define SRS_POR                         _SRS.Bits.POR

#define SRS_LVD_MASK                    2U
#define SRS_LOC_MASK                    4U
#define SRS_ILAD_MASK                   8U
#define SRS_ILOP_MASK                   16U
#define SRS_COP_MASK                    32U
#define SRS_PIN_MASK                    64U
#define SRS_POR_MASK                    128U


/*** SOPT1 - System Options Register 1; 0xFFFF9802 ***/
typedef union {
  byte Byte;
  struct {
    byte RSTPE       :1;                                       /* RESET Pin Enable */
    byte BKGDPE      :1;                                       /* Background Debug Mode Pin Enable */
    byte MBSL        :1;                                       /* MiniFlex Bus Security Level */
    byte BLMSS       :1;                                       /* Boot Loader Mode Select Status */
    byte WAITE       :1;                                       /* WAIT Mode Enable */
    byte STOPE       :1;                                       /* Stop Mode Enable */
    byte COPT0       :1;                                       /* COP Watchdog Timeout, bit 0 */
    byte COPT1       :1;                                       /* COP Watchdog Timeout, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCOPT :2;
  } MergedBits;
} SOPT1STR;
extern volatile SOPT1STR _SOPT1 @0xFFFF9802;
#define SOPT1                           _SOPT1.Byte
#define SOPT1_RSTPE                     _SOPT1.Bits.RSTPE
#define SOPT1_BKGDPE                    _SOPT1.Bits.BKGDPE
#define SOPT1_MBSL                      _SOPT1.Bits.MBSL
#define SOPT1_BLMSS                     _SOPT1.Bits.BLMSS
#define SOPT1_WAITE                     _SOPT1.Bits.WAITE
#define SOPT1_STOPE                     _SOPT1.Bits.STOPE
#define SOPT1_COPT0                     _SOPT1.Bits.COPT0
#define SOPT1_COPT1                     _SOPT1.Bits.COPT1
#define SOPT1_COPT                      _SOPT1.MergedBits.grpCOPT

#define SOPT1_RSTPE_MASK                1U
#define SOPT1_BKGDPE_MASK               2U
#define SOPT1_MBSL_MASK                 4U
#define SOPT1_BLMSS_MASK                8U
#define SOPT1_WAITE_MASK                16U
#define SOPT1_STOPE_MASK                32U
#define SOPT1_COPT0_MASK                64U
#define SOPT1_COPT1_MASK                128U
#define SOPT1_COPT_MASK                 192U
#define SOPT1_COPT_BITNUM               6U


/*** SOPT2 - System Options Register 2; 0xFFFF9803 ***/
typedef union {
  byte Byte;
  struct {
    byte ACIC        :1;                                       /* Analog Comparator to Input Capture Enable */
    byte             :1; 
    byte             :1; 
    byte CMT_CLK_SEL :1;                                       /* CMT Clock Select */
    byte CLKOUT_EN   :1;                                       /* Clock Output Enable */
    byte USB_BIGEND  :1;                                       /* USB Big Endian */
    byte COPW        :1;                                       /* COP Window */
    byte COPCLKS     :1;                                       /* COP Watchdog Clock Select */
  } Bits;
} SOPT2STR;
extern volatile SOPT2STR _SOPT2 @0xFFFF9803;
#define SOPT2                           _SOPT2.Byte
#define SOPT2_ACIC                      _SOPT2.Bits.ACIC
#define SOPT2_CMT_CLK_SEL               _SOPT2.Bits.CMT_CLK_SEL
#define SOPT2_CLKOUT_EN                 _SOPT2.Bits.CLKOUT_EN
#define SOPT2_USB_BIGEND                _SOPT2.Bits.USB_BIGEND
#define SOPT2_COPW                      _SOPT2.Bits.COPW
#define SOPT2_COPCLKS                   _SOPT2.Bits.COPCLKS

#define SOPT2_ACIC_MASK                 1U
#define SOPT2_CMT_CLK_SEL_MASK          8U
#define SOPT2_CLKOUT_EN_MASK            16U
#define SOPT2_USB_BIGEND_MASK           32U
#define SOPT2_COPW_MASK                 64U
#define SOPT2_COPCLKS_MASK              128U


/*** SDID - System Device Identification Register; 0xFFFF9806 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SDIDH - System Device Identification Register High; 0xFFFF9806 ***/
    union {
      byte Byte;
      struct {
        byte ID8         :1;                                       /* Part Identification Number, bit 8 */
        byte ID9         :1;                                       /* Part Identification Number, bit 9 */
        byte ID10        :1;                                       /* Part Identification Number, bit 10 */
        byte ID11        :1;                                       /* Part Identification Number, bit 11 */
        byte REV0        :1;                                       /* Revision Number, bit 0 */
        byte REV1        :1;                                       /* Revision Number, bit 1 */
        byte REV2        :1;                                       /* Revision Number, bit 2 */
        byte REV3        :1;                                       /* Revision Number, bit 3 */
      } Bits;
      struct {
        byte grpID_8 :4;
        byte grpREV :4;
      } MergedBits;
    } SDIDHSTR;
    #define SDIDH                       _SDID.Overlap_STR.SDIDHSTR.Byte
    #define SDIDH_ID8                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID8
    #define SDIDH_ID9                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID9
    #define SDIDH_ID10                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID10
    #define SDIDH_ID11                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID11
    #define SDIDH_REV0                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV0
    #define SDIDH_REV1                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV1
    #define SDIDH_REV2                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV2
    #define SDIDH_REV3                  _SDID.Overlap_STR.SDIDHSTR.Bits.REV3
    #define SDIDH_ID_8                  _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpID_8
    #define SDIDH_REV                   _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpREV
    #define SDIDH_ID                    SDIDH_ID_8
    
    #define SDIDH_ID8_MASK              1U
    #define SDIDH_ID9_MASK              2U
    #define SDIDH_ID10_MASK             4U
    #define SDIDH_ID11_MASK             8U
    #define SDIDH_REV0_MASK             16U
    #define SDIDH_REV1_MASK             32U
    #define SDIDH_REV2_MASK             64U
    #define SDIDH_REV3_MASK             128U
    #define SDIDH_ID_8_MASK             15U
    #define SDIDH_ID_8_BITNUM           0U
    #define SDIDH_REV_MASK              240U
    #define SDIDH_REV_BITNUM            4U
    

    /*** SDIDL - System Device Identification Register Low; 0xFFFF9807 ***/
    union {
      byte Byte;
      struct {
        byte ID0         :1;                                       /* Part Identification Number, bit 0 */
        byte ID1         :1;                                       /* Part Identification Number, bit 1 */
        byte ID2         :1;                                       /* Part Identification Number, bit 2 */
        byte ID3         :1;                                       /* Part Identification Number, bit 3 */
        byte ID4         :1;                                       /* Part Identification Number, bit 4 */
        byte ID5         :1;                                       /* Part Identification Number, bit 5 */
        byte ID6         :1;                                       /* Part Identification Number, bit 6 */
        byte ID7         :1;                                       /* Part Identification Number, bit 7 */
      } Bits;
    } SDIDLSTR;
    #define SDIDL                       _SDID.Overlap_STR.SDIDLSTR.Byte
    #define SDIDL_ID0                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID0
    #define SDIDL_ID1                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID1
    #define SDIDL_ID2                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID2
    #define SDIDL_ID3                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID3
    #define SDIDL_ID4                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID4
    #define SDIDL_ID5                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID5
    #define SDIDL_ID6                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID6
    #define SDIDL_ID7                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID7
    
    #define SDIDL_ID0_MASK              1U
    #define SDIDL_ID1_MASK              2U
    #define SDIDL_ID2_MASK              4U
    #define SDIDL_ID3_MASK              8U
    #define SDIDL_ID4_MASK              16U
    #define SDIDL_ID5_MASK              32U
    #define SDIDL_ID6_MASK              64U
    #define SDIDL_ID7_MASK              128U
    
  } Overlap_STR;

  struct {
    word ID0         :1;                                       /* Part Identification Number, bit 0 */
    word ID1         :1;                                       /* Part Identification Number, bit 1 */
    word ID2         :1;                                       /* Part Identification Number, bit 2 */
    word ID3         :1;                                       /* Part Identification Number, bit 3 */
    word ID4         :1;                                       /* Part Identification Number, bit 4 */
    word ID5         :1;                                       /* Part Identification Number, bit 5 */
    word ID6         :1;                                       /* Part Identification Number, bit 6 */
    word ID7         :1;                                       /* Part Identification Number, bit 7 */
    word ID8         :1;                                       /* Part Identification Number, bit 8 */
    word ID9         :1;                                       /* Part Identification Number, bit 9 */
    word ID10        :1;                                       /* Part Identification Number, bit 10 */
    word ID11        :1;                                       /* Part Identification Number, bit 11 */
    word REV0        :1;                                       /* Revision Number */
    word REV1        :1;                                       /* Revision Number, bit 1 */
    word REV2        :1;                                       /* Revision Number, bit 2 */
    word REV3        :1;                                       /* Revision Number, bit 3 */
  } Bits;
  struct {
    word grpID   :12;
    word grpREV  :4;
  } MergedBits;
} SDIDSTR;
extern volatile SDIDSTR _SDID @0xFFFF9806;
#define SDID                            _SDID.Word
#define SDID_ID0                        _SDID.Bits.ID0
#define SDID_ID1                        _SDID.Bits.ID1
#define SDID_ID2                        _SDID.Bits.ID2
#define SDID_ID3                        _SDID.Bits.ID3
#define SDID_ID4                        _SDID.Bits.ID4
#define SDID_ID5                        _SDID.Bits.ID5
#define SDID_ID6                        _SDID.Bits.ID6
#define SDID_ID7                        _SDID.Bits.ID7
#define SDID_ID8                        _SDID.Bits.ID8
#define SDID_ID9                        _SDID.Bits.ID9
#define SDID_ID10                       _SDID.Bits.ID10
#define SDID_ID11                       _SDID.Bits.ID11
#define SDID_REV0                       _SDID.Bits.REV0
#define SDID_REV1                       _SDID.Bits.REV1
#define SDID_REV2                       _SDID.Bits.REV2
#define SDID_REV3                       _SDID.Bits.REV3
#define SDID_ID                         _SDID.MergedBits.grpID
#define SDID_REV                        _SDID.MergedBits.grpREV

#define SDID_ID0_MASK                   1U
#define SDID_ID1_MASK                   2U
#define SDID_ID2_MASK                   4U
#define SDID_ID3_MASK                   8U
#define SDID_ID4_MASK                   16U
#define SDID_ID5_MASK                   32U
#define SDID_ID6_MASK                   64U
#define SDID_ID7_MASK                   128U
#define SDID_ID8_MASK                   256U
#define SDID_ID9_MASK                   512U
#define SDID_ID10_MASK                  1024U
#define SDID_ID11_MASK                  2048U
#define SDID_REV0_MASK                  4096U
#define SDID_REV1_MASK                  8192U
#define SDID_REV2_MASK                  16384U
#define SDID_REV3_MASK                  32768U
#define SDID_ID_MASK                    4095U
#define SDID_ID_BITNUM                  0U
#define SDID_REV_MASK                   61440U
#define SDID_REV_BITNUM                 12U


/*** SCGC1 - System Clock Gating Control 1 Register; 0xFFFF9808 ***/
typedef union {
  byte Byte;
  struct {
    byte SCI1        :1;                                       /* SCI1 Clock Gate Control */
    byte SCI2        :1;                                       /* SCI2 Clock Gate Control */
    byte IIC         :1;                                       /* IIC Clock Gate Control */
    byte DAC         :1;                                       /* DAC Clock Gate Control */
    byte ADC         :1;                                       /* ADC Clock Gate Control */
    byte TPM1        :1;                                       /* TPM1 Clock Gate Control */
    byte TPM2        :1;                                       /* TPM2 Clock Gate Control */
    byte CMT         :1;                                       /* CMT Clock Gate Control */
  } Bits;
  struct {
    byte grpSCI_1 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpTPM_1 :2;
    byte         :1;
  } MergedBits;
} SCGC1STR;
extern volatile SCGC1STR _SCGC1 @0xFFFF9808;
#define SCGC1                           _SCGC1.Byte
#define SCGC1_SCI1                      _SCGC1.Bits.SCI1
#define SCGC1_SCI2                      _SCGC1.Bits.SCI2
#define SCGC1_IIC                       _SCGC1.Bits.IIC
#define SCGC1_DAC                       _SCGC1.Bits.DAC
#define SCGC1_ADC                       _SCGC1.Bits.ADC
#define SCGC1_TPM1                      _SCGC1.Bits.TPM1
#define SCGC1_TPM2                      _SCGC1.Bits.TPM2
#define SCGC1_CMT                       _SCGC1.Bits.CMT
#define SCGC1_SCI_1                     _SCGC1.MergedBits.grpSCI_1
#define SCGC1_TPM_1                     _SCGC1.MergedBits.grpTPM_1
#define SCGC1_SCI                       SCGC1_SCI_1
#define SCGC1_TPM                       SCGC1_TPM_1

#define SCGC1_SCI1_MASK                 1U
#define SCGC1_SCI2_MASK                 2U
#define SCGC1_IIC_MASK                  4U
#define SCGC1_DAC_MASK                  8U
#define SCGC1_ADC_MASK                  16U
#define SCGC1_TPM1_MASK                 32U
#define SCGC1_TPM2_MASK                 64U
#define SCGC1_CMT_MASK                  128U
#define SCGC1_SCI_1_MASK                3U
#define SCGC1_SCI_1_BITNUM              0U
#define SCGC1_TPM_1_MASK                96U
#define SCGC1_TPM_1_BITNUM              5U


/*** SCGC2 - System Clock Gating Control 2 Register; 0xFFFF9809 ***/
typedef union {
  byte Byte;
  struct {
    byte SPI1        :1;                                       /* SPI1 Clock Gate Control */
    byte SPI2        :1;                                       /* SPI2 Clock Gate Control */
    byte MFB         :1;                                       /* MFB Clock Gate Control */
    byte PRACMP      :1;                                       /* PRACMP Clock Gate Control */
    byte KBI         :1;                                       /* KBI Clock Gate Control */
    byte IRQ         :1;                                       /* IRQ Clock Gate Control */
    byte PDB         :1;                                       /* PDB Register Clock Gate Control */
    byte USB         :1;                                       /* USB Clock Gate Control */
  } Bits;
  struct {
    byte grpSPI_1 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SCGC2STR;
extern volatile SCGC2STR _SCGC2 @0xFFFF9809;
#define SCGC2                           _SCGC2.Byte
#define SCGC2_SPI1                      _SCGC2.Bits.SPI1
#define SCGC2_SPI2                      _SCGC2.Bits.SPI2
#define SCGC2_MFB                       _SCGC2.Bits.MFB
#define SCGC2_PRACMP                    _SCGC2.Bits.PRACMP
#define SCGC2_KBI                       _SCGC2.Bits.KBI
#define SCGC2_IRQ                       _SCGC2.Bits.IRQ
#define SCGC2_PDB                       _SCGC2.Bits.PDB
#define SCGC2_USB                       _SCGC2.Bits.USB
#define SCGC2_SPI_1                     _SCGC2.MergedBits.grpSPI_1
#define SCGC2_SPI                       SCGC2_SPI_1

#define SCGC2_SPI1_MASK                 1U
#define SCGC2_SPI2_MASK                 2U
#define SCGC2_MFB_MASK                  4U
#define SCGC2_PRACMP_MASK               8U
#define SCGC2_KBI_MASK                  16U
#define SCGC2_IRQ_MASK                  32U
#define SCGC2_PDB_MASK                  64U
#define SCGC2_USB_MASK                  128U
#define SCGC2_SPI_1_MASK                3U
#define SCGC2_SPI_1_BITNUM              0U


/*** SCGC3 - System Clock Gating Control 3 Register; 0xFFFF980A ***/
typedef union {
  byte Byte;
  struct {
    byte GPOA1       :1;                                       /* GPOA1 Clock Gate Control */
    byte GPOA2       :1;                                       /* GPOA2 Clock Gate Control */
    byte TRIAMP1     :1;                                       /* TRIAMP1 Clock Gate Control */
    byte TRIAMP2     :1;                                       /* TRIAMP2 Clock Gate Control */
    byte FLS1        :1;                                       /* FLS1 Clock Gate Control */
    byte FLS2        :1;                                       /* FLS2 Clock Gate Control */
    byte CRC         :1;                                       /* CRC Clock Gate Control */
    byte VREF        :1;                                       /* VREF Clock Gate Control */
  } Bits;
  struct {
    byte grpGPOA_1 :2;
    byte grpTRIAMP_1 :2;
    byte grpFLS_1 :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} SCGC3STR;
extern volatile SCGC3STR _SCGC3 @0xFFFF980A;
#define SCGC3                           _SCGC3.Byte
#define SCGC3_GPOA1                     _SCGC3.Bits.GPOA1
#define SCGC3_GPOA2                     _SCGC3.Bits.GPOA2
#define SCGC3_TRIAMP1                   _SCGC3.Bits.TRIAMP1
#define SCGC3_TRIAMP2                   _SCGC3.Bits.TRIAMP2
#define SCGC3_FLS1                      _SCGC3.Bits.FLS1
#define SCGC3_FLS2                      _SCGC3.Bits.FLS2
#define SCGC3_CRC                       _SCGC3.Bits.CRC
#define SCGC3_VREF                      _SCGC3.Bits.VREF
#define SCGC3_GPOA_1                    _SCGC3.MergedBits.grpGPOA_1
#define SCGC3_TRIAMP_1                  _SCGC3.MergedBits.grpTRIAMP_1
#define SCGC3_FLS_1                     _SCGC3.MergedBits.grpFLS_1
#define SCGC3_GPOA                      SCGC3_GPOA_1
#define SCGC3_TRIAMP                    SCGC3_TRIAMP_1
#define SCGC3_FLS                       SCGC3_FLS_1

#define SCGC3_GPOA1_MASK                1U
#define SCGC3_GPOA2_MASK                2U
#define SCGC3_TRIAMP1_MASK              4U
#define SCGC3_TRIAMP2_MASK              8U
#define SCGC3_FLS1_MASK                 16U
#define SCGC3_FLS2_MASK                 32U
#define SCGC3_CRC_MASK                  64U
#define SCGC3_VREF_MASK                 128U
#define SCGC3_GPOA_1_MASK               3U
#define SCGC3_GPOA_1_BITNUM             0U
#define SCGC3_TRIAMP_1_MASK             12U
#define SCGC3_TRIAMP_1_BITNUM           2U
#define SCGC3_FLS_1_MASK                48U
#define SCGC3_FLS_1_BITNUM              4U


/*** SOPT3 - System Options 3 Register; 0xFFFF980B ***/
typedef union {
  byte Byte;
  struct {
    byte CMT_PAD     :1;                                       /* CMT pad drive strength */
    byte SCI1_PAD    :1;                                       /* SCI_PAD pad drive strength */
    byte ARRAYSEL    :1;                                       /* Array Select */
    byte MB_DATA     :1;                                       /* Mini-FlexBus Data bus configuration */
    byte USBPS       :1;                                       /* USB Pin Select */
    byte IICPS       :1;                                       /* IIC Pin Select */
    byte SCI1PS      :1;                                       /* SCI1 Pin Select */
    byte SCI2PS      :1;                                       /* SCI2 Pin Select */
  } Bits;
} SOPT3STR;
extern volatile SOPT3STR _SOPT3 @0xFFFF980B;
#define SOPT3                           _SOPT3.Byte
#define SOPT3_CMT_PAD                   _SOPT3.Bits.CMT_PAD
#define SOPT3_SCI1_PAD                  _SOPT3.Bits.SCI1_PAD
#define SOPT3_ARRAYSEL                  _SOPT3.Bits.ARRAYSEL
#define SOPT3_MB_DATA                   _SOPT3.Bits.MB_DATA
#define SOPT3_USBPS                     _SOPT3.Bits.USBPS
#define SOPT3_IICPS                     _SOPT3.Bits.IICPS
#define SOPT3_SCI1PS                    _SOPT3.Bits.SCI1PS
#define SOPT3_SCI2PS                    _SOPT3.Bits.SCI2PS

#define SOPT3_CMT_PAD_MASK              1U
#define SOPT3_SCI1_PAD_MASK             2U
#define SOPT3_ARRAYSEL_MASK             4U
#define SOPT3_MB_DATA_MASK              8U
#define SOPT3_USBPS_MASK                16U
#define SOPT3_IICPS_MASK                32U
#define SOPT3_SCI1PS_MASK               64U
#define SOPT3_SCI2PS_MASK               128U


/*** SOPT4 - System Options 4 Register; 0xFFFF980C ***/
typedef union {
  byte Byte;
  struct {
    byte IRODSE      :1;                                       /* Drive Strength Control Enable for IRO pin */
    byte IROSRE      :1;                                       /* Output Slew Rate Control Enable for IRO pin */
    byte FBAD12DSE   :1;                                       /* Drive Strength Control Enable for pin where address wire 12 of ?ex bus locate */
    byte FBAD12SRE   :1;                                       /* Output Slew Rate Control Enable for pin where address wire 12 of ?ex bus locate */
    byte FBAD12PUE   :1;                                       /* Pull-Up Enable for pin where address wire 12 of ?ex bus locate */
    byte FBAD12FE    :1;                                       /* Input Filter Enable for pin where address wire 12 of ?ex bus locate */
    byte FBALEEN     :1;                                       /* Mini-FlexBus Address Latch Enable bit */
    byte             :1; 
  } Bits;
} SOPT4STR;
extern volatile SOPT4STR _SOPT4 @0xFFFF980C;
#define SOPT4                           _SOPT4.Byte
#define SOPT4_IRODSE                    _SOPT4.Bits.IRODSE
#define SOPT4_IROSRE                    _SOPT4.Bits.IROSRE
#define SOPT4_FBAD12DSE                 _SOPT4.Bits.FBAD12DSE
#define SOPT4_FBAD12SRE                 _SOPT4.Bits.FBAD12SRE
#define SOPT4_FBAD12PUE                 _SOPT4.Bits.FBAD12PUE
#define SOPT4_FBAD12FE                  _SOPT4.Bits.FBAD12FE
#define SOPT4_FBALEEN                   _SOPT4.Bits.FBALEEN

#define SOPT4_IRODSE_MASK               1U
#define SOPT4_IROSRE_MASK               2U
#define SOPT4_FBAD12DSE_MASK            4U
#define SOPT4_FBAD12SRE_MASK            8U
#define SOPT4_FBAD12PUE_MASK            16U
#define SOPT4_FBAD12FE_MASK             32U
#define SOPT4_FBALEEN_MASK              64U


/*** SIMIPS - SIM Internal Peripheral Select Register; 0xFFFF980E ***/
typedef union {
  byte Byte;
  struct {
    byte MODTX1      :1;                                       /* Modulate TX1 */
    byte             :1; 
    byte MTBASE10    :1;                                       /* SCI1 TX Modulation Time Base Select, bit 0 */
    byte MTBASE11    :1;                                       /* SCI1 TX Modulation Time Base Select, bit 1 */
    byte             :1; 
    byte             :1; 
    byte RX1IN       :1;                                       /* SCI1 RX Input Pin Select */
    byte ADCTRS      :1;                                       /* ADC HWTRG Select */
  } Bits;
  struct {
    byte grpMODTX_1 :1;
    byte         :1;
    byte grpMTBASE1 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SIMIPSSTR;
extern volatile SIMIPSSTR _SIMIPS @0xFFFF980E;
#define SIMIPS                          _SIMIPS.Byte
#define SIMIPS_MODTX1                   _SIMIPS.Bits.MODTX1
#define SIMIPS_MTBASE10                 _SIMIPS.Bits.MTBASE10
#define SIMIPS_MTBASE11                 _SIMIPS.Bits.MTBASE11
#define SIMIPS_RX1IN                    _SIMIPS.Bits.RX1IN
#define SIMIPS_ADCTRS                   _SIMIPS.Bits.ADCTRS
#define SIMIPS_MTBASE1                  _SIMIPS.MergedBits.grpMTBASE1

#define SIMIPS_MODTX1_MASK              1U
#define SIMIPS_MTBASE10_MASK            4U
#define SIMIPS_MTBASE11_MASK            8U
#define SIMIPS_RX1IN_MASK               64U
#define SIMIPS_ADCTRS_MASK              128U
#define SIMIPS_MTBASE1_MASK             12U
#define SIMIPS_MTBASE1_BITNUM           2U


/*** SIGNATURE - SIGNATURE Register; 0xFFFF980F ***/
typedef union {
  byte Byte;
} SIGNATURESTR;
extern volatile SIGNATURESTR _SIGNATURE @0xFFFF980F;
#define SIGNATURE                       _SIGNATURE.Byte


/*** CCSCTRL - Clock Check & Select Control; 0xFFFF9810 ***/
typedef union {
  byte Byte;
  struct {
    byte SEL         :1;                                       /* External Clock Select */
    byte TEST        :1;                                       /* TEST */
    byte EN          :1;                                       /* Enable clock for CCS */
    byte EREFS1      :1;                                       /* External Reference Select */
    byte OSCINIT1    :1;                                       /* Oscillator Initialization */
    byte ERCLKEN1    :1;                                       /* External Clock Enable */
    byte HGO1        :1;                                       /* High-Gain Oscillator Select */
    byte RANGE1      :1;                                       /* Frequency Range Select */
  } Bits;
} CCSCTRLSTR;
extern volatile CCSCTRLSTR _CCSCTRL @0xFFFF9810;
#define CCSCTRL                         _CCSCTRL.Byte
#define CCSCTRL_SEL                     _CCSCTRL.Bits.SEL
#define CCSCTRL_TEST                    _CCSCTRL.Bits.TEST
#define CCSCTRL_EN                      _CCSCTRL.Bits.EN
#define CCSCTRL_EREFS1                  _CCSCTRL.Bits.EREFS1
#define CCSCTRL_OSCINIT1                _CCSCTRL.Bits.OSCINIT1
#define CCSCTRL_ERCLKEN1                _CCSCTRL.Bits.ERCLKEN1
#define CCSCTRL_HGO1                    _CCSCTRL.Bits.HGO1
#define CCSCTRL_RANGE1                  _CCSCTRL.Bits.RANGE1

#define CCSCTRL_SEL_MASK                1U
#define CCSCTRL_TEST_MASK               2U
#define CCSCTRL_EN_MASK                 4U
#define CCSCTRL_EREFS1_MASK             8U
#define CCSCTRL_OSCINIT1_MASK           16U
#define CCSCTRL_ERCLKEN1_MASK           32U
#define CCSCTRL_HGO1_MASK               64U
#define CCSCTRL_RANGE1_MASK             128U


/*** CCSTMR1 - CCS XOSC1 Timer Register; 0xFFFF9811 ***/
typedef union {
  byte Byte;
  struct {
    byte CNT10       :1;                                       /* CNT1, bit 0 */
    byte CNT11       :1;                                       /* CNT1, bit 1 */
    byte CNT12       :1;                                       /* CNT1, bit 2 */
    byte CNT13       :1;                                       /* CNT1, bit 3 */
    byte CNT14       :1;                                       /* CNT1, bit 4 */
    byte CNT15       :1;                                       /* CNT1, bit 5 */
    byte CNT16       :1;                                       /* CNT1, bit 6 */
    byte CNT17       :1;                                       /* CNT1, bit 7 */
  } Bits;
} CCSTMR1STR;
extern volatile CCSTMR1STR _CCSTMR1 @0xFFFF9811;
#define CCSTMR1                         _CCSTMR1.Byte
#define CCSTMR1_CNT10                   _CCSTMR1.Bits.CNT10
#define CCSTMR1_CNT11                   _CCSTMR1.Bits.CNT11
#define CCSTMR1_CNT12                   _CCSTMR1.Bits.CNT12
#define CCSTMR1_CNT13                   _CCSTMR1.Bits.CNT13
#define CCSTMR1_CNT14                   _CCSTMR1.Bits.CNT14
#define CCSTMR1_CNT15                   _CCSTMR1.Bits.CNT15
#define CCSTMR1_CNT16                   _CCSTMR1.Bits.CNT16
#define CCSTMR1_CNT17                   _CCSTMR1.Bits.CNT17

#define CCSTMR1_CNT10_MASK              1U
#define CCSTMR1_CNT11_MASK              2U
#define CCSTMR1_CNT12_MASK              4U
#define CCSTMR1_CNT13_MASK              8U
#define CCSTMR1_CNT14_MASK              16U
#define CCSTMR1_CNT15_MASK              32U
#define CCSTMR1_CNT16_MASK              64U
#define CCSTMR1_CNT17_MASK              128U


/*** CCSTMR2 - CCS XOSC2 Timer Register; 0xFFFF9812 ***/
typedef union {
  byte Byte;
  struct {
    byte CNT20       :1;                                       /* CNT2, bit 0 */
    byte CNT21       :1;                                       /* CNT2, bit 1 */
    byte CNT22       :1;                                       /* CNT2, bit 2 */
    byte CNT23       :1;                                       /* CNT2, bit 3 */
    byte CNT24       :1;                                       /* CNT2, bit 4 */
    byte CNT25       :1;                                       /* CNT2, bit 5 */
    byte CNT26       :1;                                       /* CNT2, bit 6 */
    byte CNT27       :1;                                       /* CNT2, bit 7 */
  } Bits;
} CCSTMR2STR;
extern volatile CCSTMR2STR _CCSTMR2 @0xFFFF9812;
#define CCSTMR2                         _CCSTMR2.Byte
#define CCSTMR2_CNT20                   _CCSTMR2.Bits.CNT20
#define CCSTMR2_CNT21                   _CCSTMR2.Bits.CNT21
#define CCSTMR2_CNT22                   _CCSTMR2.Bits.CNT22
#define CCSTMR2_CNT23                   _CCSTMR2.Bits.CNT23
#define CCSTMR2_CNT24                   _CCSTMR2.Bits.CNT24
#define CCSTMR2_CNT25                   _CCSTMR2.Bits.CNT25
#define CCSTMR2_CNT26                   _CCSTMR2.Bits.CNT26
#define CCSTMR2_CNT27                   _CCSTMR2.Bits.CNT27

#define CCSTMR2_CNT20_MASK              1U
#define CCSTMR2_CNT21_MASK              2U
#define CCSTMR2_CNT22_MASK              4U
#define CCSTMR2_CNT23_MASK              8U
#define CCSTMR2_CNT24_MASK              16U
#define CCSTMR2_CNT25_MASK              32U
#define CCSTMR2_CNT26_MASK              64U
#define CCSTMR2_CNT27_MASK              128U


/*** CCSTMRIR - CCS Internal Reference Clock Timer Register; 0xFFFF9813 ***/
typedef union {
  byte Byte;
  struct {
    byte CNTIR0      :1;                                       /* CNTIR, bit 0 */
    byte CNTIR1      :1;                                       /* CNTIR, bit 1 */
    byte CNTIR2      :1;                                       /* CNTIR, bit 2 */
    byte CNTIR3      :1;                                       /* CNTIR, bit 3 */
    byte CNTIR4      :1;                                       /* CNTIR, bit 4 */
    byte CNTIR5      :1;                                       /* CNTIR, bit 5 */
    byte CNTIR6      :1;                                       /* CNTIR, bit 6 */
    byte CNTIR7      :1;                                       /* CNTIR, bit 7 */
  } Bits;
} CCSTMRIRSTR;
extern volatile CCSTMRIRSTR _CCSTMRIR @0xFFFF9813;
#define CCSTMRIR                        _CCSTMRIR.Byte
#define CCSTMRIR_CNTIR0                 _CCSTMRIR.Bits.CNTIR0
#define CCSTMRIR_CNTIR1                 _CCSTMRIR.Bits.CNTIR1
#define CCSTMRIR_CNTIR2                 _CCSTMRIR.Bits.CNTIR2
#define CCSTMRIR_CNTIR3                 _CCSTMRIR.Bits.CNTIR3
#define CCSTMRIR_CNTIR4                 _CCSTMRIR.Bits.CNTIR4
#define CCSTMRIR_CNTIR5                 _CCSTMRIR.Bits.CNTIR5
#define CCSTMRIR_CNTIR6                 _CCSTMRIR.Bits.CNTIR6
#define CCSTMRIR_CNTIR7                 _CCSTMRIR.Bits.CNTIR7

#define CCSTMRIR_CNTIR0_MASK            1U
#define CCSTMRIR_CNTIR1_MASK            2U
#define CCSTMRIR_CNTIR2_MASK            4U
#define CCSTMRIR_CNTIR3_MASK            8U
#define CCSTMRIR_CNTIR4_MASK            16U
#define CCSTMRIR_CNTIR5_MASK            32U
#define CCSTMRIR_CNTIR6_MASK            64U
#define CCSTMRIR_CNTIR7_MASK            128U


/*** FPROTD - Flash Protection Disable Register; 0xFFFF9814 ***/
typedef union {
  byte Byte;
  struct {
    byte FPDIS       :1;                                       /* Disable Flash protection */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} FPROTDSTR;
extern volatile FPROTDSTR _FPROTD @0xFFFF9814;
#define FPROTD                          _FPROTD.Byte
#define FPROTD_FPDIS                    _FPROTD.Bits.FPDIS

#define FPROTD_FPDIS_MASK               1U


/*** MFBPC1 - Mini-FlexBus Pin Control 1; 0xFFFF9815 ***/
typedef union {
  byte Byte;
  struct {
    byte MFBPEN_AD0  :1;                                       /* MiniFlex bus pin control for FB_AD0 */
    byte MFBPEN_AD1  :1;                                       /* MiniFlex bus pin control for FB_AD1 */
    byte MFBPEN_AD2  :1;                                       /* MiniFlex bus pin control for FB_AD2 */
    byte MFBPEN_AD3  :1;                                       /* MiniFlex bus pin control for FB_AD3 */
    byte MFBPEN_AD4  :1;                                       /* MiniFlex bus pin control for FB_AD4 */
    byte MFBPEN_AD5  :1;                                       /* MiniFlex bus pin control for FB_AD5 */
    byte MFBPEN_AD6  :1;                                       /* MiniFlex bus pin control for FB_AD6 */
    byte MFBPEN_AD7  :1;                                       /* MiniFlex bus pin control for FB_AD7 */
  } Bits;
} MFBPC1STR;
extern volatile MFBPC1STR _MFBPC1 @0xFFFF9815;
#define MFBPC1                          _MFBPC1.Byte
#define MFBPC1_MFBPEN_AD0               _MFBPC1.Bits.MFBPEN_AD0
#define MFBPC1_MFBPEN_AD1               _MFBPC1.Bits.MFBPEN_AD1
#define MFBPC1_MFBPEN_AD2               _MFBPC1.Bits.MFBPEN_AD2
#define MFBPC1_MFBPEN_AD3               _MFBPC1.Bits.MFBPEN_AD3
#define MFBPC1_MFBPEN_AD4               _MFBPC1.Bits.MFBPEN_AD4
#define MFBPC1_MFBPEN_AD5               _MFBPC1.Bits.MFBPEN_AD5
#define MFBPC1_MFBPEN_AD6               _MFBPC1.Bits.MFBPEN_AD6
#define MFBPC1_MFBPEN_AD7               _MFBPC1.Bits.MFBPEN_AD7

#define MFBPC1_MFBPEN_AD0_MASK          1U
#define MFBPC1_MFBPEN_AD1_MASK          2U
#define MFBPC1_MFBPEN_AD2_MASK          4U
#define MFBPC1_MFBPEN_AD3_MASK          8U
#define MFBPC1_MFBPEN_AD4_MASK          16U
#define MFBPC1_MFBPEN_AD5_MASK          32U
#define MFBPC1_MFBPEN_AD6_MASK          64U
#define MFBPC1_MFBPEN_AD7_MASK          128U


/*** MFBPC2 - Mini-FlexBus Pin Control 2; 0xFFFF9816 ***/
typedef union {
  byte Byte;
  struct {
    byte MFBPEN_AD8  :1;                                       /* MiniFlex bus pin control for FB_AD8 */
    byte MFBPEN_AD9  :1;                                       /* MiniFlex bus pin control for FB_AD9 */
    byte MFBPEN_AD10 :1;                                       /* MiniFlex bus pin control for FB_AD10 */
    byte MFBPEN_AD11 :1;                                       /* MiniFlex bus pin control for FB_AD11 */
    byte MFBPEN_AD12 :1;                                       /* MiniFlex bus pin control for FB_AD12 */
    byte MFBPEN_AD13 :1;                                       /* MiniFlex bus pin control for FB_AD13 */
    byte MFBPEN_AD14 :1;                                       /* MiniFlex bus pin control for FB_AD14 */
    byte MFBPEN_AD15 :1;                                       /* MiniFlex bus pin control for FB_AD15 */
  } Bits;
} MFBPC2STR;
extern volatile MFBPC2STR _MFBPC2 @0xFFFF9816;
#define MFBPC2                          _MFBPC2.Byte
#define MFBPC2_MFBPEN_AD8               _MFBPC2.Bits.MFBPEN_AD8
#define MFBPC2_MFBPEN_AD9               _MFBPC2.Bits.MFBPEN_AD9
#define MFBPC2_MFBPEN_AD10              _MFBPC2.Bits.MFBPEN_AD10
#define MFBPC2_MFBPEN_AD11              _MFBPC2.Bits.MFBPEN_AD11
#define MFBPC2_MFBPEN_AD12              _MFBPC2.Bits.MFBPEN_AD12
#define MFBPC2_MFBPEN_AD13              _MFBPC2.Bits.MFBPEN_AD13
#define MFBPC2_MFBPEN_AD14              _MFBPC2.Bits.MFBPEN_AD14
#define MFBPC2_MFBPEN_AD15              _MFBPC2.Bits.MFBPEN_AD15

#define MFBPC2_MFBPEN_AD8_MASK          1U
#define MFBPC2_MFBPEN_AD9_MASK          2U
#define MFBPC2_MFBPEN_AD10_MASK         4U
#define MFBPC2_MFBPEN_AD11_MASK         8U
#define MFBPC2_MFBPEN_AD12_MASK         16U
#define MFBPC2_MFBPEN_AD13_MASK         32U
#define MFBPC2_MFBPEN_AD14_MASK         64U
#define MFBPC2_MFBPEN_AD15_MASK         128U


/*** MFBPC3 - Mini-FlexBus Pin Control 3; 0xFFFF9817 ***/
typedef union {
  byte Byte;
  struct {
    byte MFBPEN_AD16 :1;                                       /* MiniFlex bus pin control for FB_AD16 */
    byte MFBPEN_AD17 :1;                                       /* MiniFlex bus pin control for FB_AD17 */
    byte MFBPEN_AD18 :1;                                       /* MiniFlex bus pin control for FB_AD18 */
    byte MFBPEN_AD19 :1;                                       /* MiniFlex bus pin control for FB_AD19 */
    byte MFBPEN_D0   :1;                                       /* MiniFlex bus pin control for FB_D0 */
    byte MFBPEN_D1   :1;                                       /* MiniFlex bus pin control for FB_D1 */
    byte MFBPEN_D2   :1;                                       /* MiniFlex bus pin control for FB_D2 */
    byte MFBPEN_D3   :1;                                       /* MiniFlex bus pin control for FB_D3 */
  } Bits;
  struct {
    byte grpMFBPEN_AD_16 :4;
    byte grpMFBPEN_D :4;
  } MergedBits;
} MFBPC3STR;
extern volatile MFBPC3STR _MFBPC3 @0xFFFF9817;
#define MFBPC3                          _MFBPC3.Byte
#define MFBPC3_MFBPEN_AD16              _MFBPC3.Bits.MFBPEN_AD16
#define MFBPC3_MFBPEN_AD17              _MFBPC3.Bits.MFBPEN_AD17
#define MFBPC3_MFBPEN_AD18              _MFBPC3.Bits.MFBPEN_AD18
#define MFBPC3_MFBPEN_AD19              _MFBPC3.Bits.MFBPEN_AD19
#define MFBPC3_MFBPEN_D0                _MFBPC3.Bits.MFBPEN_D0
#define MFBPC3_MFBPEN_D1                _MFBPC3.Bits.MFBPEN_D1
#define MFBPC3_MFBPEN_D2                _MFBPC3.Bits.MFBPEN_D2
#define MFBPC3_MFBPEN_D3                _MFBPC3.Bits.MFBPEN_D3
#define MFBPC3_MFBPEN_AD_16             _MFBPC3.MergedBits.grpMFBPEN_AD_16
#define MFBPC3_MFBPEN_D                 _MFBPC3.MergedBits.grpMFBPEN_D
#define MFBPC3_MFBPEN_AD                MFBPC3_MFBPEN_AD_16

#define MFBPC3_MFBPEN_AD16_MASK         1U
#define MFBPC3_MFBPEN_AD17_MASK         2U
#define MFBPC3_MFBPEN_AD18_MASK         4U
#define MFBPC3_MFBPEN_AD19_MASK         8U
#define MFBPC3_MFBPEN_D0_MASK           16U
#define MFBPC3_MFBPEN_D1_MASK           32U
#define MFBPC3_MFBPEN_D2_MASK           64U
#define MFBPC3_MFBPEN_D3_MASK           128U
#define MFBPC3_MFBPEN_AD_16_MASK        15U
#define MFBPC3_MFBPEN_AD_16_BITNUM      0U
#define MFBPC3_MFBPEN_D_MASK            240U
#define MFBPC3_MFBPEN_D_BITNUM          4U


/*** MFBPC4 - Mini-FlexBus Pin Control 4; 0xFFFF9818 ***/
typedef union {
  byte Byte;
  struct {
    byte MFBPEN_D4   :1;                                       /* MiniFlex bus pin control for FB_D4 */
    byte MFBPEN_D5   :1;                                       /* MiniFlex bus pin control for FB_D5 */
    byte MFBPEN_D6   :1;                                       /* MiniFlex bus pin control for FB_D6 */
    byte MFBPEN_D7   :1;                                       /* MiniFlex bus pin control for FB_D7 */
    byte EN_RW       :1;                                       /* MiniFlex bus pin control for FB_RW_b */
    byte EN_OE       :1;                                       /* MiniFlex bus pin control for FB_OE_b */
    byte EN_CS0      :1;                                       /* MiniFlex bus pin control for FB_CS0 */
    byte EN_CS1      :1;                                       /* MiniFlex bus pin control for FB_CS1/FB_ALE */
  } Bits;
  struct {
    byte grpMFBPEN_D_4 :4;
    byte         :1;
    byte         :1;
    byte grpEN_CS :2;
  } MergedBits;
} MFBPC4STR;
extern volatile MFBPC4STR _MFBPC4 @0xFFFF9818;
#define MFBPC4                          _MFBPC4.Byte
#define MFBPC4_MFBPEN_D4                _MFBPC4.Bits.MFBPEN_D4
#define MFBPC4_MFBPEN_D5                _MFBPC4.Bits.MFBPEN_D5
#define MFBPC4_MFBPEN_D6                _MFBPC4.Bits.MFBPEN_D6
#define MFBPC4_MFBPEN_D7                _MFBPC4.Bits.MFBPEN_D7
#define MFBPC4_EN_RW                    _MFBPC4.Bits.EN_RW
#define MFBPC4_EN_OE                    _MFBPC4.Bits.EN_OE
#define MFBPC4_EN_CS0                   _MFBPC4.Bits.EN_CS0
#define MFBPC4_EN_CS1                   _MFBPC4.Bits.EN_CS1
#define MFBPC4_MFBPEN_D_4               _MFBPC4.MergedBits.grpMFBPEN_D_4
#define MFBPC4_EN_CS                    _MFBPC4.MergedBits.grpEN_CS
#define MFBPC4_MFBPEN_D                 MFBPC4_MFBPEN_D_4

#define MFBPC4_MFBPEN_D4_MASK           1U
#define MFBPC4_MFBPEN_D5_MASK           2U
#define MFBPC4_MFBPEN_D6_MASK           4U
#define MFBPC4_MFBPEN_D7_MASK           8U
#define MFBPC4_EN_RW_MASK               16U
#define MFBPC4_EN_OE_MASK               32U
#define MFBPC4_EN_CS0_MASK              64U
#define MFBPC4_EN_CS1_MASK              128U
#define MFBPC4_MFBPEN_D_4_MASK          15U
#define MFBPC4_MFBPEN_D_4_BITNUM        0U
#define MFBPC4_EN_CS_MASK               192U
#define MFBPC4_EN_CS_BITNUM             6U


/*** SIMCO - SIM Clock Set and Select Register; 0xFFFF9819 ***/
typedef union {
  byte Byte;
  struct {
    byte CS0         :1;                                       /* CLKOUT Select, bit 0 */
    byte CS1         :1;                                       /* CLKOUT Select, bit 1 */
    byte CS2         :1;                                       /* CLKOUT Select, bit 2 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpCS   :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SIMCOSTR;
extern volatile SIMCOSTR _SIMCO @0xFFFF9819;
#define SIMCO                           _SIMCO.Byte
#define SIMCO_CS0                       _SIMCO.Bits.CS0
#define SIMCO_CS1                       _SIMCO.Bits.CS1
#define SIMCO_CS2                       _SIMCO.Bits.CS2
#define SIMCO_CS                        _SIMCO.MergedBits.grpCS

#define SIMCO_CS0_MASK                  1U
#define SIMCO_CS1_MASK                  2U
#define SIMCO_CS2_MASK                  4U
#define SIMCO_CS_MASK                   7U
#define SIMCO_CS_BITNUM                 0U


/*** SPMSC1 - System Power Management Status and Control 1 Register; 0xFFFF981C ***/
typedef union {
  byte Byte;
  struct {
    byte BGBE        :1;                                       /* Bandgap Buffer Enable */
    byte             :1; 
    byte LVDE        :1;                                       /* Low-Voltage Detect Enable */
    byte LVDSE       :1;                                       /* Low-Voltage Detect Stop Enable */
    byte LVDRE       :1;                                       /* Low-Voltage Detect Reset Enable */
    byte LVDIE       :1;                                       /* Low-Voltage Detect Interrupt Enable */
    byte LVDACK      :1;                                       /* Low-Voltage Detect Acknowledge */
    byte LVDF        :1;                                       /* Low-Voltage Detect Flag */
  } Bits;
} SPMSC1STR;
extern volatile SPMSC1STR _SPMSC1 @0xFFFF981C;
#define SPMSC1                          _SPMSC1.Byte
#define SPMSC1_BGBE                     _SPMSC1.Bits.BGBE
#define SPMSC1_LVDE                     _SPMSC1.Bits.LVDE
#define SPMSC1_LVDSE                    _SPMSC1.Bits.LVDSE
#define SPMSC1_LVDRE                    _SPMSC1.Bits.LVDRE
#define SPMSC1_LVDIE                    _SPMSC1.Bits.LVDIE
#define SPMSC1_LVDACK                   _SPMSC1.Bits.LVDACK
#define SPMSC1_LVDF                     _SPMSC1.Bits.LVDF

#define SPMSC1_BGBE_MASK                1U
#define SPMSC1_LVDE_MASK                4U
#define SPMSC1_LVDSE_MASK               8U
#define SPMSC1_LVDRE_MASK               16U
#define SPMSC1_LVDIE_MASK               32U
#define SPMSC1_LVDACK_MASK              64U
#define SPMSC1_LVDF_MASK                128U


/*** SPMSC2 - System Power Management Status and Control 2 Register; 0xFFFF981D ***/
typedef union {
  byte Byte;
  struct {
    byte PPDC        :1;                                       /* Partial Power Down Control */
    byte PPDE        :1;                                       /* Partial Power-Down Enable */
    byte PPDACK      :1;                                       /* Partial Power Down Acknowledge */
    byte PPDF        :1;                                       /* Partial Power Down Flag */
    byte             :1; 
    byte LPWUI       :1;                                       /* Low Power Wake Up on Interrupt */
    byte LPRS        :1;                                       /* Low Power Regulator Status */
    byte LPR         :1;                                       /* Low Power Regulator Control */
  } Bits;
} SPMSC2STR;
extern volatile SPMSC2STR _SPMSC2 @0xFFFF981D;
#define SPMSC2                          _SPMSC2.Byte
#define SPMSC2_PPDC                     _SPMSC2.Bits.PPDC
#define SPMSC2_PPDE                     _SPMSC2.Bits.PPDE
#define SPMSC2_PPDACK                   _SPMSC2.Bits.PPDACK
#define SPMSC2_PPDF                     _SPMSC2.Bits.PPDF
#define SPMSC2_LPWUI                    _SPMSC2.Bits.LPWUI
#define SPMSC2_LPRS                     _SPMSC2.Bits.LPRS
#define SPMSC2_LPR                      _SPMSC2.Bits.LPR

#define SPMSC2_PPDC_MASK                1U
#define SPMSC2_PPDE_MASK                2U
#define SPMSC2_PPDACK_MASK              4U
#define SPMSC2_PPDF_MASK                8U
#define SPMSC2_LPWUI_MASK               32U
#define SPMSC2_LPRS_MASK                64U
#define SPMSC2_LPR_MASK                 128U


/*** SPMSC3 - System Power Management Status and Control 3 Register; 0xFFFF981F ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte LVWIE       :1;                                       /* Low-Voltage Warning Interrupt Enable */
    byte LVWV        :1;                                       /* Low-Voltage Warning Voltage Select */
    byte LVDV        :1;                                       /* Low-Voltage Detect Voltage Select */
    byte LVWACK      :1;                                       /* Low-Voltage Warning Acknowledge */
    byte LVWF        :1;                                       /* Low-Voltage Warning Flag */
  } Bits;
} SPMSC3STR;
extern volatile SPMSC3STR _SPMSC3 @0xFFFF981F;
#define SPMSC3                          _SPMSC3.Byte
#define SPMSC3_LVWIE                    _SPMSC3.Bits.LVWIE
#define SPMSC3_LVWV                     _SPMSC3.Bits.LVWV
#define SPMSC3_LVDV                     _SPMSC3.Bits.LVDV
#define SPMSC3_LVWACK                   _SPMSC3.Bits.LVWACK
#define SPMSC3_LVWF                     _SPMSC3.Bits.LVWF

#define SPMSC3_LVWIE_MASK               8U
#define SPMSC3_LVWV_MASK                16U
#define SPMSC3_LVDV_MASK                32U
#define SPMSC3_LVWACK_MASK              64U
#define SPMSC3_LVWF_MASK                128U


/*** PTED - Port E Data Register; 0xFFFF9830 ***/
typedef union {
  byte Byte;
  struct {
    byte PTED0       :1;                                       /* Port E Data Register Bit 0 */
    byte PTED1       :1;                                       /* Port E Data Register Bit 1 */
    byte PTED2       :1;                                       /* Port E Data Register Bit 2 */
    byte PTED3       :1;                                       /* Port E Data Register Bit 3 */
    byte PTED4       :1;                                       /* Port E Data Register Bit 4 */
    byte PTED5       :1;                                       /* Port E Data Register Bit 5 */
    byte PTED6       :1;                                       /* Port E Data Register Bit 6 */
    byte PTED7       :1;                                       /* Port E Data Register Bit 7 */
  } Bits;
} PTEDSTR;
extern volatile PTEDSTR _PTED @0xFFFF9830;
#define PTED                            _PTED.Byte
#define PTED_PTED0                      _PTED.Bits.PTED0
#define PTED_PTED1                      _PTED.Bits.PTED1
#define PTED_PTED2                      _PTED.Bits.PTED2
#define PTED_PTED3                      _PTED.Bits.PTED3
#define PTED_PTED4                      _PTED.Bits.PTED4
#define PTED_PTED5                      _PTED.Bits.PTED5
#define PTED_PTED6                      _PTED.Bits.PTED6
#define PTED_PTED7                      _PTED.Bits.PTED7

#define PTED_PTED0_MASK                 1U
#define PTED_PTED1_MASK                 2U
#define PTED_PTED2_MASK                 4U
#define PTED_PTED3_MASK                 8U
#define PTED_PTED4_MASK                 16U
#define PTED_PTED5_MASK                 32U
#define PTED_PTED6_MASK                 64U
#define PTED_PTED7_MASK                 128U


/*** PTEDD - Port E Data Direction Register; 0xFFFF9831 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDD0      :1;                                       /* Data Direction for Port E Bit 0 */
    byte PTEDD1      :1;                                       /* Data Direction for Port E Bit 1 */
    byte PTEDD2      :1;                                       /* Data Direction for Port E Bit 2 */
    byte PTEDD3      :1;                                       /* Data Direction for Port E Bit 3 */
    byte             :1; 
    byte PTEDD5      :1;                                       /* Data Direction for Port E Bit 5 */
    byte PTEDD6      :1;                                       /* Data Direction for Port E Bit 6 */
    byte PTEDD7      :1;                                       /* Data Direction for Port E Bit 7 */
  } Bits;
  struct {
    byte grpPTEDD :4;
    byte         :1;
    byte grpPTEDD_5 :3;
  } MergedBits;
} PTEDDSTR;
extern volatile PTEDDSTR _PTEDD @0xFFFF9831;
#define PTEDD                           _PTEDD.Byte
#define PTEDD_PTEDD0                    _PTEDD.Bits.PTEDD0
#define PTEDD_PTEDD1                    _PTEDD.Bits.PTEDD1
#define PTEDD_PTEDD2                    _PTEDD.Bits.PTEDD2
#define PTEDD_PTEDD3                    _PTEDD.Bits.PTEDD3
#define PTEDD_PTEDD5                    _PTEDD.Bits.PTEDD5
#define PTEDD_PTEDD6                    _PTEDD.Bits.PTEDD6
#define PTEDD_PTEDD7                    _PTEDD.Bits.PTEDD7
#define PTEDD_PTEDD                     _PTEDD.MergedBits.grpPTEDD
#define PTEDD_PTEDD_5                   _PTEDD.MergedBits.grpPTEDD_5

#define PTEDD_PTEDD0_MASK               1U
#define PTEDD_PTEDD1_MASK               2U
#define PTEDD_PTEDD2_MASK               4U
#define PTEDD_PTEDD3_MASK               8U
#define PTEDD_PTEDD5_MASK               32U
#define PTEDD_PTEDD6_MASK               64U
#define PTEDD_PTEDD7_MASK               128U
#define PTEDD_PTEDD_MASK                15U
#define PTEDD_PTEDD_BITNUM              0U
#define PTEDD_PTEDD_5_MASK              224U
#define PTEDD_PTEDD_5_BITNUM            5U


/*** PTFD - Port F Data Register; 0xFFFF9832 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFD0       :1;                                       /* Port F Data Register Bit 0 */
    byte PTFD1       :1;                                       /* Port F Data Register Bit 1 */
    byte PTFD2       :1;                                       /* Port F Data Register Bit 2 */
    byte PTFD3       :1;                                       /* Port F Data Register Bit 3 */
    byte PTFD4       :1;                                       /* Port F Data Register Bit 4 */
    byte PTFD5       :1;                                       /* Port F Data Register Bit 5 */
    byte PTFD6       :1;                                       /* Port F Data Register Bit 6 */
    byte PTFD7       :1;                                       /* Port F Data Register Bit 7 */
  } Bits;
} PTFDSTR;
extern volatile PTFDSTR _PTFD @0xFFFF9832;
#define PTFD                            _PTFD.Byte
#define PTFD_PTFD0                      _PTFD.Bits.PTFD0
#define PTFD_PTFD1                      _PTFD.Bits.PTFD1
#define PTFD_PTFD2                      _PTFD.Bits.PTFD2
#define PTFD_PTFD3                      _PTFD.Bits.PTFD3
#define PTFD_PTFD4                      _PTFD.Bits.PTFD4
#define PTFD_PTFD5                      _PTFD.Bits.PTFD5
#define PTFD_PTFD6                      _PTFD.Bits.PTFD6
#define PTFD_PTFD7                      _PTFD.Bits.PTFD7

#define PTFD_PTFD0_MASK                 1U
#define PTFD_PTFD1_MASK                 2U
#define PTFD_PTFD2_MASK                 4U
#define PTFD_PTFD3_MASK                 8U
#define PTFD_PTFD4_MASK                 16U
#define PTFD_PTFD5_MASK                 32U
#define PTFD_PTFD6_MASK                 64U
#define PTFD_PTFD7_MASK                 128U


/*** PTFDD - Port F Data Direction Register; 0xFFFF9833 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDD0      :1;                                       /* Data Direction for Port F Bit 0 */
    byte PTFDD1      :1;                                       /* Data Direction for Port F Bit 1 */
    byte PTFDD2      :1;                                       /* Data Direction for Port F Bit 2 */
    byte PTFDD3      :1;                                       /* Data Direction for Port F Bit 3 */
    byte PTFDD4      :1;                                       /* Data Direction for Port F Bit 4 */
    byte PTFDD5      :1;                                       /* Data Direction for Port F Bit 5 */
    byte PTFDD6      :1;                                       /* Data Direction for Port F Bit 6 */
    byte PTFDD7      :1;                                       /* Data Direction for Port F Bit 7 */
  } Bits;
} PTFDDSTR;
extern volatile PTFDDSTR _PTFDD @0xFFFF9833;
#define PTFDD                           _PTFDD.Byte
#define PTFDD_PTFDD0                    _PTFDD.Bits.PTFDD0
#define PTFDD_PTFDD1                    _PTFDD.Bits.PTFDD1
#define PTFDD_PTFDD2                    _PTFDD.Bits.PTFDD2
#define PTFDD_PTFDD3                    _PTFDD.Bits.PTFDD3
#define PTFDD_PTFDD4                    _PTFDD.Bits.PTFDD4
#define PTFDD_PTFDD5                    _PTFDD.Bits.PTFDD5
#define PTFDD_PTFDD6                    _PTFDD.Bits.PTFDD6
#define PTFDD_PTFDD7                    _PTFDD.Bits.PTFDD7

#define PTFDD_PTFDD0_MASK               1U
#define PTFDD_PTFDD1_MASK               2U
#define PTFDD_PTFDD2_MASK               4U
#define PTFDD_PTFDD3_MASK               8U
#define PTFDD_PTFDD4_MASK               16U
#define PTFDD_PTFDD5_MASK               32U
#define PTFDD_PTFDD6_MASK               64U
#define PTFDD_PTFDD7_MASK               128U


/*** SCI2BD - SCI2 Baud Rate Register; 0xFFFF9838 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI2BDH - SCI2 Baud Rate Register High; 0xFFFF9838 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
        byte LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI2BDHSTR;
    #define SCI2BDH                     _SCI2BD.Overlap_STR.SCI2BDHSTR.Byte
    #define SCI2BDH_SBR8                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR8
    #define SCI2BDH_SBR9                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR9
    #define SCI2BDH_SBR10               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR10
    #define SCI2BDH_SBR11               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR11
    #define SCI2BDH_SBR12               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR12
    #define SCI2BDH_RXEDGIE             _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.RXEDGIE
    #define SCI2BDH_LBKDIE              _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.LBKDIE
    #define SCI2BDH_SBR_8               _SCI2BD.Overlap_STR.SCI2BDHSTR.MergedBits.grpSBR_8
    #define SCI2BDH_SBR                 SCI2BDH_SBR_8
    
    #define SCI2BDH_SBR8_MASK           1U
    #define SCI2BDH_SBR9_MASK           2U
    #define SCI2BDH_SBR10_MASK          4U
    #define SCI2BDH_SBR11_MASK          8U
    #define SCI2BDH_SBR12_MASK          16U
    #define SCI2BDH_RXEDGIE_MASK        64U
    #define SCI2BDH_LBKDIE_MASK         128U
    #define SCI2BDH_SBR_8_MASK          31U
    #define SCI2BDH_SBR_8_BITNUM        0U
    

    /*** SCI2BDL - SCI2 Baud Rate Register Low; 0xFFFF9839 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI2BDLSTR;
    #define SCI2BDL                     _SCI2BD.Overlap_STR.SCI2BDLSTR.Byte
    #define SCI2BDL_SBR0                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR0
    #define SCI2BDL_SBR1                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR1
    #define SCI2BDL_SBR2                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR2
    #define SCI2BDL_SBR3                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR3
    #define SCI2BDL_SBR4                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR4
    #define SCI2BDL_SBR5                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR5
    #define SCI2BDL_SBR6                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR6
    #define SCI2BDL_SBR7                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR7
    
    #define SCI2BDL_SBR0_MASK           1U
    #define SCI2BDL_SBR1_MASK           2U
    #define SCI2BDL_SBR2_MASK           4U
    #define SCI2BDL_SBR3_MASK           8U
    #define SCI2BDL_SBR4_MASK           16U
    #define SCI2BDL_SBR5_MASK           32U
    #define SCI2BDL_SBR6_MASK           64U
    #define SCI2BDL_SBR7_MASK           128U
    
  } Overlap_STR;

  struct {
    word SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
    word SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
    word SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
    word SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
    word SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
    word SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
    word SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
    word SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
    word SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
    word SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
    word SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
    word SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
    word SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
    word             :1; 
    word RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
    word LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
  } Bits;
  struct {
    word grpSBR  :13;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} SCI2BDSTR;
extern volatile SCI2BDSTR _SCI2BD @0xFFFF9838;
#define SCI2BD                          _SCI2BD.Word
#define SCI2BD_SBR0                     _SCI2BD.Bits.SBR0
#define SCI2BD_SBR1                     _SCI2BD.Bits.SBR1
#define SCI2BD_SBR2                     _SCI2BD.Bits.SBR2
#define SCI2BD_SBR3                     _SCI2BD.Bits.SBR3
#define SCI2BD_SBR4                     _SCI2BD.Bits.SBR4
#define SCI2BD_SBR5                     _SCI2BD.Bits.SBR5
#define SCI2BD_SBR6                     _SCI2BD.Bits.SBR6
#define SCI2BD_SBR7                     _SCI2BD.Bits.SBR7
#define SCI2BD_SBR8                     _SCI2BD.Bits.SBR8
#define SCI2BD_SBR9                     _SCI2BD.Bits.SBR9
#define SCI2BD_SBR10                    _SCI2BD.Bits.SBR10
#define SCI2BD_SBR11                    _SCI2BD.Bits.SBR11
#define SCI2BD_SBR12                    _SCI2BD.Bits.SBR12
#define SCI2BD_RXEDGIE                  _SCI2BD.Bits.RXEDGIE
#define SCI2BD_LBKDIE                   _SCI2BD.Bits.LBKDIE
#define SCI2BD_SBR                      _SCI2BD.MergedBits.grpSBR

#define SCI2BD_SBR0_MASK                1U
#define SCI2BD_SBR1_MASK                2U
#define SCI2BD_SBR2_MASK                4U
#define SCI2BD_SBR3_MASK                8U
#define SCI2BD_SBR4_MASK                16U
#define SCI2BD_SBR5_MASK                32U
#define SCI2BD_SBR6_MASK                64U
#define SCI2BD_SBR7_MASK                128U
#define SCI2BD_SBR8_MASK                256U
#define SCI2BD_SBR9_MASK                512U
#define SCI2BD_SBR10_MASK               1024U
#define SCI2BD_SBR11_MASK               2048U
#define SCI2BD_SBR12_MASK               4096U
#define SCI2BD_RXEDGIE_MASK             16384U
#define SCI2BD_LBKDIE_MASK              32768U
#define SCI2BD_SBR_MASK                 8191U
#define SCI2BD_SBR_BITNUM               0U


/*** SCI2C1 - SCI2 Control Register 1; 0xFFFF983A ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI2C1STR;
extern volatile SCI2C1STR _SCI2C1 @0xFFFF983A;
#define SCI2C1                          _SCI2C1.Byte
#define SCI2C1_PT                       _SCI2C1.Bits.PT
#define SCI2C1_PE                       _SCI2C1.Bits.PE
#define SCI2C1_ILT                      _SCI2C1.Bits.ILT
#define SCI2C1_WAKE                     _SCI2C1.Bits.WAKE
#define SCI2C1_M                        _SCI2C1.Bits.M
#define SCI2C1_RSRC                     _SCI2C1.Bits.RSRC
#define SCI2C1_SCISWAI                  _SCI2C1.Bits.SCISWAI
#define SCI2C1_LOOPS                    _SCI2C1.Bits.LOOPS

#define SCI2C1_PT_MASK                  1U
#define SCI2C1_PE_MASK                  2U
#define SCI2C1_ILT_MASK                 4U
#define SCI2C1_WAKE_MASK                8U
#define SCI2C1_M_MASK                   16U
#define SCI2C1_RSRC_MASK                32U
#define SCI2C1_SCISWAI_MASK             64U
#define SCI2C1_LOOPS_MASK               128U


/*** SCI2C2 - SCI2 Control Register 2; 0xFFFF983B ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI2C2STR;
extern volatile SCI2C2STR _SCI2C2 @0xFFFF983B;
#define SCI2C2                          _SCI2C2.Byte
#define SCI2C2_SBK                      _SCI2C2.Bits.SBK
#define SCI2C2_RWU                      _SCI2C2.Bits.RWU
#define SCI2C2_RE                       _SCI2C2.Bits.RE
#define SCI2C2_TE                       _SCI2C2.Bits.TE
#define SCI2C2_ILIE                     _SCI2C2.Bits.ILIE
#define SCI2C2_RIE                      _SCI2C2.Bits.RIE
#define SCI2C2_TCIE                     _SCI2C2.Bits.TCIE
#define SCI2C2_TIE                      _SCI2C2.Bits.TIE

#define SCI2C2_SBK_MASK                 1U
#define SCI2C2_RWU_MASK                 2U
#define SCI2C2_RE_MASK                  4U
#define SCI2C2_TE_MASK                  8U
#define SCI2C2_ILIE_MASK                16U
#define SCI2C2_RIE_MASK                 32U
#define SCI2C2_TCIE_MASK                64U
#define SCI2C2_TIE_MASK                 128U


/*** SCI2S1 - SCI2 Status Register 1; 0xFFFF983C ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI2S1STR;
extern volatile SCI2S1STR _SCI2S1 @0xFFFF983C;
#define SCI2S1                          _SCI2S1.Byte
#define SCI2S1_PF                       _SCI2S1.Bits.PF
#define SCI2S1_FE                       _SCI2S1.Bits.FE
#define SCI2S1_NF                       _SCI2S1.Bits.NF
#define SCI2S1_OR                       _SCI2S1.Bits.OR
#define SCI2S1_IDLE                     _SCI2S1.Bits.IDLE
#define SCI2S1_RDRF                     _SCI2S1.Bits.RDRF
#define SCI2S1_TC                       _SCI2S1.Bits.TC
#define SCI2S1_TDRE                     _SCI2S1.Bits.TDRE

#define SCI2S1_PF_MASK                  1U
#define SCI2S1_FE_MASK                  2U
#define SCI2S1_NF_MASK                  4U
#define SCI2S1_OR_MASK                  8U
#define SCI2S1_IDLE_MASK                16U
#define SCI2S1_RDRF_MASK                32U
#define SCI2S1_TC_MASK                  64U
#define SCI2S1_TDRE_MASK                128U


/*** SCI2S2 - SCI2 Status Register 2; 0xFFFF983D ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte LBKDE       :1;                                       /* LIN Break Detection Enable */
    byte BRK13       :1;                                       /* Break Character Generation Length */
    byte RWUID       :1;                                       /* Receive Wake Up Idle Detect */
    byte RXINV       :1;                                       /* Receive Data Inversion */
    byte             :1; 
    byte RXEDGIF     :1;                                       /* RxD Pin Active Edge Interrupt Flag */
    byte LBKDIF      :1;                                       /* LIN Break Detect Interrupt Flag */
  } Bits;
} SCI2S2STR;
extern volatile SCI2S2STR _SCI2S2 @0xFFFF983D;
#define SCI2S2                          _SCI2S2.Byte
#define SCI2S2_RAF                      _SCI2S2.Bits.RAF
#define SCI2S2_LBKDE                    _SCI2S2.Bits.LBKDE
#define SCI2S2_BRK13                    _SCI2S2.Bits.BRK13
#define SCI2S2_RWUID                    _SCI2S2.Bits.RWUID
#define SCI2S2_RXINV                    _SCI2S2.Bits.RXINV
#define SCI2S2_RXEDGIF                  _SCI2S2.Bits.RXEDGIF
#define SCI2S2_LBKDIF                   _SCI2S2.Bits.LBKDIF

#define SCI2S2_RAF_MASK                 1U
#define SCI2S2_LBKDE_MASK               2U
#define SCI2S2_BRK13_MASK               4U
#define SCI2S2_RWUID_MASK               8U
#define SCI2S2_RXINV_MASK               16U
#define SCI2S2_RXEDGIF_MASK             64U
#define SCI2S2_LBKDIF_MASK              128U


/*** SCI2C3 - SCI2 Control Register 3; 0xFFFF983E ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI2C3STR;
extern volatile SCI2C3STR _SCI2C3 @0xFFFF983E;
#define SCI2C3                          _SCI2C3.Byte
#define SCI2C3_PEIE                     _SCI2C3.Bits.PEIE
#define SCI2C3_FEIE                     _SCI2C3.Bits.FEIE
#define SCI2C3_NEIE                     _SCI2C3.Bits.NEIE
#define SCI2C3_ORIE                     _SCI2C3.Bits.ORIE
#define SCI2C3_TXINV                    _SCI2C3.Bits.TXINV
#define SCI2C3_TXDIR                    _SCI2C3.Bits.TXDIR
#define SCI2C3_T8                       _SCI2C3.Bits.T8
#define SCI2C3_R8                       _SCI2C3.Bits.R8

#define SCI2C3_PEIE_MASK                1U
#define SCI2C3_FEIE_MASK                2U
#define SCI2C3_NEIE_MASK                4U
#define SCI2C3_ORIE_MASK                8U
#define SCI2C3_TXINV_MASK               16U
#define SCI2C3_TXDIR_MASK               32U
#define SCI2C3_T8_MASK                  64U
#define SCI2C3_R8_MASK                  128U


/*** SCI2D - SCI2 Data Register; 0xFFFF983F ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI2DSTR;
extern volatile SCI2DSTR _SCI2D @0xFFFF983F;
#define SCI2D                           _SCI2D.Byte
#define SCI2D_R0_T0                     _SCI2D.Bits.R0_T0
#define SCI2D_R1_T1                     _SCI2D.Bits.R1_T1
#define SCI2D_R2_T2                     _SCI2D.Bits.R2_T2
#define SCI2D_R3_T3                     _SCI2D.Bits.R3_T3
#define SCI2D_R4_T4                     _SCI2D.Bits.R4_T4
#define SCI2D_R5_T5                     _SCI2D.Bits.R5_T5
#define SCI2D_R6_T6                     _SCI2D.Bits.R6_T6
#define SCI2D_R7_T7                     _SCI2D.Bits.R7_T7

#define SCI2D_R0_T0_MASK                1U
#define SCI2D_R1_T1_MASK                2U
#define SCI2D_R2_T2_MASK                4U
#define SCI2D_R3_T3_MASK                8U
#define SCI2D_R4_T4_MASK                16U
#define SCI2D_R5_T5_MASK                32U
#define SCI2D_R6_T6_MASK                64U
#define SCI2D_R7_T7_MASK                128U


/*** SPI2C1 - SPI2 Control Register 1; 0xFFFF9840 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (Shifter Direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI System Enable */
    byte SPIE        :1;                                       /* SPI Interrupt Enable (for SPRF and MODF) */
  } Bits;
} SPI2C1STR;
extern volatile SPI2C1STR _SPI2C1 @0xFFFF9840;
#define SPI2C1                          _SPI2C1.Byte
#define SPI2C1_LSBFE                    _SPI2C1.Bits.LSBFE
#define SPI2C1_SSOE                     _SPI2C1.Bits.SSOE
#define SPI2C1_CPHA                     _SPI2C1.Bits.CPHA
#define SPI2C1_CPOL                     _SPI2C1.Bits.CPOL
#define SPI2C1_MSTR                     _SPI2C1.Bits.MSTR
#define SPI2C1_SPTIE                    _SPI2C1.Bits.SPTIE
#define SPI2C1_SPE                      _SPI2C1.Bits.SPE
#define SPI2C1_SPIE                     _SPI2C1.Bits.SPIE

#define SPI2C1_LSBFE_MASK               1U
#define SPI2C1_SSOE_MASK                2U
#define SPI2C1_CPHA_MASK                4U
#define SPI2C1_CPOL_MASK                8U
#define SPI2C1_MSTR_MASK                16U
#define SPI2C1_SPTIE_MASK               32U
#define SPI2C1_SPE_MASK                 64U
#define SPI2C1_SPIE_MASK                128U


/*** SPI2C2 - SPI2 Control Register 2; 0xFFFF9841 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte             :1; 
    byte SPMIE       :1;                                       /* SPI Match Interrupt Enable */
  } Bits;
} SPI2C2STR;
extern volatile SPI2C2STR _SPI2C2 @0xFFFF9841;
#define SPI2C2                          _SPI2C2.Byte
#define SPI2C2_SPC0                     _SPI2C2.Bits.SPC0
#define SPI2C2_SPISWAI                  _SPI2C2.Bits.SPISWAI
#define SPI2C2_BIDIROE                  _SPI2C2.Bits.BIDIROE
#define SPI2C2_MODFEN                   _SPI2C2.Bits.MODFEN
#define SPI2C2_SPMIE                    _SPI2C2.Bits.SPMIE

#define SPI2C2_SPC0_MASK                1U
#define SPI2C2_SPISWAI_MASK             2U
#define SPI2C2_BIDIROE_MASK             8U
#define SPI2C2_MODFEN_MASK              16U
#define SPI2C2_SPMIE_MASK               128U


/*** SPI2BR - SPI2 Baud Rate Register; 0xFFFF9842 ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI Baud Rate Divisor Bit 2 */
    byte SPR3        :1;                                       /* SPI Baud Rate Divisor Bit 3 */
    byte SPPR0       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :4;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI2BRSTR;
extern volatile SPI2BRSTR _SPI2BR @0xFFFF9842;
#define SPI2BR                          _SPI2BR.Byte
#define SPI2BR_SPR0                     _SPI2BR.Bits.SPR0
#define SPI2BR_SPR1                     _SPI2BR.Bits.SPR1
#define SPI2BR_SPR2                     _SPI2BR.Bits.SPR2
#define SPI2BR_SPR3                     _SPI2BR.Bits.SPR3
#define SPI2BR_SPPR0                    _SPI2BR.Bits.SPPR0
#define SPI2BR_SPPR1                    _SPI2BR.Bits.SPPR1
#define SPI2BR_SPPR2                    _SPI2BR.Bits.SPPR2
#define SPI2BR_SPR                      _SPI2BR.MergedBits.grpSPR
#define SPI2BR_SPPR                     _SPI2BR.MergedBits.grpSPPR

#define SPI2BR_SPR0_MASK                1U
#define SPI2BR_SPR1_MASK                2U
#define SPI2BR_SPR2_MASK                4U
#define SPI2BR_SPR3_MASK                8U
#define SPI2BR_SPPR0_MASK               16U
#define SPI2BR_SPPR1_MASK               32U
#define SPI2BR_SPPR2_MASK               64U
#define SPI2BR_SPR_MASK                 15U
#define SPI2BR_SPR_BITNUM               0U
#define SPI2BR_SPPR_MASK                112U
#define SPI2BR_SPPR_BITNUM              4U


/*** SPI2S - SPI2 Status Register; 0xFFFF9843 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI Transmit Buffer Empty Flag */
    byte SPMF        :1;                                       /* SPI Match Flag */
    byte SPRF        :1;                                       /* SPI Read Buffer Full Flag */
  } Bits;
} SPI2SSTR;
extern volatile SPI2SSTR _SPI2S @0xFFFF9843;
#define SPI2S                           _SPI2S.Byte
#define SPI2S_MODF                      _SPI2S.Bits.MODF
#define SPI2S_SPTEF                     _SPI2S.Bits.SPTEF
#define SPI2S_SPMF                      _SPI2S.Bits.SPMF
#define SPI2S_SPRF                      _SPI2S.Bits.SPRF

#define SPI2S_MODF_MASK                 16U
#define SPI2S_SPTEF_MASK                32U
#define SPI2S_SPMF_MASK                 64U
#define SPI2S_SPRF_MASK                 128U


/*** SPI2D - SPI2 Data Register; 0xFFFF9845 ***/
typedef union {
  byte Byte;
} SPI2DSTR;
extern volatile SPI2DSTR _SPI2D @0xFFFF9845;
#define SPI2D                           _SPI2D.Byte


/*** SPI2M - SPI2 Match Register; 0xFFFF9847 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit0        :1;                                       /* SPI Match Value Bit 0 */
    byte Bit1        :1;                                       /* SPI Match Value Bit 1 */
    byte Bit2        :1;                                       /* SPI Match Value Bit 2 */
    byte Bit3        :1;                                       /* SPI Match Value Bit 3 */
    byte Bit4        :1;                                       /* SPI Match Value Bit 4 */
    byte Bit5        :1;                                       /* SPI Match Value Bit 5 */
    byte Bit6        :1;                                       /* SPI Match Value Bit 6 */
    byte Bit7        :1;                                       /* SPI Match Value Bit 7 */
  } Bits;
} SPI2MSTR;
extern volatile SPI2MSTR _SPI2M @0xFFFF9847;
#define SPI2M                           _SPI2M.Byte
#define SPI2M_Bit0                      _SPI2M.Bits.Bit0
#define SPI2M_Bit1                      _SPI2M.Bits.Bit1
#define SPI2M_Bit2                      _SPI2M.Bits.Bit2
#define SPI2M_Bit3                      _SPI2M.Bits.Bit3
#define SPI2M_Bit4                      _SPI2M.Bits.Bit4
#define SPI2M_Bit5                      _SPI2M.Bits.Bit5
#define SPI2M_Bit6                      _SPI2M.Bits.Bit6
#define SPI2M_Bit7                      _SPI2M.Bits.Bit7

#define SPI2M_Bit0_MASK                 1U
#define SPI2M_Bit1_MASK                 2U
#define SPI2M_Bit2_MASK                 4U
#define SPI2M_Bit3_MASK                 8U
#define SPI2M_Bit4_MASK                 16U
#define SPI2M_Bit5_MASK                 32U
#define SPI2M_Bit6_MASK                 64U
#define SPI2M_Bit7_MASK                 128U


/*** PTGD - Port G Data Register; 0xFFFF9848 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGD0       :1;                                       /* Port G Data Register Bit 0 */
    byte PTGD1       :1;                                       /* Port G Data Register Bit 1 */
    byte PTGD2       :1;                                       /* Port G Data Register Bit 2 */
    byte PTGD3       :1;                                       /* Port G Data Register Bit 3 */
    byte PTGD4       :1;                                       /* Port G Data Register Bit 4 */
    byte PTGD5       :1;                                       /* Port G Data Register Bit 5 */
    byte PTGD6       :1;                                       /* Port G Data Register Bit 6 */
    byte PTGD7       :1;                                       /* Port G Data Register Bit 7 */
  } Bits;
} PTGDSTR;
extern volatile PTGDSTR _PTGD @0xFFFF9848;
#define PTGD                            _PTGD.Byte
#define PTGD_PTGD0                      _PTGD.Bits.PTGD0
#define PTGD_PTGD1                      _PTGD.Bits.PTGD1
#define PTGD_PTGD2                      _PTGD.Bits.PTGD2
#define PTGD_PTGD3                      _PTGD.Bits.PTGD3
#define PTGD_PTGD4                      _PTGD.Bits.PTGD4
#define PTGD_PTGD5                      _PTGD.Bits.PTGD5
#define PTGD_PTGD6                      _PTGD.Bits.PTGD6
#define PTGD_PTGD7                      _PTGD.Bits.PTGD7

#define PTGD_PTGD0_MASK                 1U
#define PTGD_PTGD1_MASK                 2U
#define PTGD_PTGD2_MASK                 4U
#define PTGD_PTGD3_MASK                 8U
#define PTGD_PTGD4_MASK                 16U
#define PTGD_PTGD5_MASK                 32U
#define PTGD_PTGD6_MASK                 64U
#define PTGD_PTGD7_MASK                 128U


/*** PTGDD - Port G Data Direction Register; 0xFFFF9849 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDD0      :1;                                       /* Data Direction for Port G Bit 0 */
    byte PTGDD1      :1;                                       /* Data Direction for Port G Bit 1 */
    byte PTGDD2      :1;                                       /* Data Direction for Port G Bit 2 */
    byte PTGDD3      :1;                                       /* Data Direction for Port G Bit 3 */
    byte PTGDD4      :1;                                       /* Data Direction for Port G Bit 4 */
    byte PTGDD5      :1;                                       /* Data Direction for Port G Bit 5 */
    byte PTGDD6      :1;                                       /* Data Direction for Port G Bit 6 */
    byte PTGDD7      :1;                                       /* Data Direction for Port G Bit 7 */
  } Bits;
} PTGDDSTR;
extern volatile PTGDDSTR _PTGDD @0xFFFF9849;
#define PTGDD                           _PTGDD.Byte
#define PTGDD_PTGDD0                    _PTGDD.Bits.PTGDD0
#define PTGDD_PTGDD1                    _PTGDD.Bits.PTGDD1
#define PTGDD_PTGDD2                    _PTGDD.Bits.PTGDD2
#define PTGDD_PTGDD3                    _PTGDD.Bits.PTGDD3
#define PTGDD_PTGDD4                    _PTGDD.Bits.PTGDD4
#define PTGDD_PTGDD5                    _PTGDD.Bits.PTGDD5
#define PTGDD_PTGDD6                    _PTGDD.Bits.PTGDD6
#define PTGDD_PTGDD7                    _PTGDD.Bits.PTGDD7

#define PTGDD_PTGDD0_MASK               1U
#define PTGDD_PTGDD1_MASK               2U
#define PTGDD_PTGDD2_MASK               4U
#define PTGDD_PTGDD3_MASK               8U
#define PTGDD_PTGDD4_MASK               16U
#define PTGDD_PTGDD5_MASK               32U
#define PTGDD_PTGDD6_MASK               64U
#define PTGDD_PTGDD7_MASK               128U


/*** PTAPE - Port A Pull Enable Register; 0xFFFF9850 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAPE0      :1;                                       /* Internal Pull Enable for Port A Bit 0 */
    byte PTAPE1      :1;                                       /* Internal Pull Enable for Port A Bit 1 */
    byte PTAPE2      :1;                                       /* Internal Pull Enable for Port A Bit 2 */
    byte PTAPE3      :1;                                       /* Internal Pull Enable for Port A Bit 3 */
    byte PTAPE4      :1;                                       /* Internal Pull Enable for Port A Bit 4 */
    byte PTAPE5      :1;                                       /* Internal Pull Enable for Port A Bit 5 */
    byte PTAPE6      :1;                                       /* Internal Pull Enable for Port A Bit 6 */
    byte PTAPE7      :1;                                       /* Internal Pull Enable for Port A Bit 7 */
  } Bits;
} PTAPESTR;
extern volatile PTAPESTR _PTAPE @0xFFFF9850;
#define PTAPE                           _PTAPE.Byte
#define PTAPE_PTAPE0                    _PTAPE.Bits.PTAPE0
#define PTAPE_PTAPE1                    _PTAPE.Bits.PTAPE1
#define PTAPE_PTAPE2                    _PTAPE.Bits.PTAPE2
#define PTAPE_PTAPE3                    _PTAPE.Bits.PTAPE3
#define PTAPE_PTAPE4                    _PTAPE.Bits.PTAPE4
#define PTAPE_PTAPE5                    _PTAPE.Bits.PTAPE5
#define PTAPE_PTAPE6                    _PTAPE.Bits.PTAPE6
#define PTAPE_PTAPE7                    _PTAPE.Bits.PTAPE7

#define PTAPE_PTAPE0_MASK               1U
#define PTAPE_PTAPE1_MASK               2U
#define PTAPE_PTAPE2_MASK               4U
#define PTAPE_PTAPE3_MASK               8U
#define PTAPE_PTAPE4_MASK               16U
#define PTAPE_PTAPE5_MASK               32U
#define PTAPE_PTAPE6_MASK               64U
#define PTAPE_PTAPE7_MASK               128U


/*** PTASE - Port A Slew Rate Enable Register; 0xFFFF9851 ***/
typedef union {
  byte Byte;
  struct {
    byte PTASE0      :1;                                       /* Output Slew Rate Enable for Port A Bit 0 */
    byte PTASE1      :1;                                       /* Output Slew Rate Enable for Port A Bit 1 */
    byte PTASE2      :1;                                       /* Output Slew Rate Enable for Port A Bit 2 */
    byte PTASE3      :1;                                       /* Output Slew Rate Enable for Port A Bit 3 */
    byte PTASE4      :1;                                       /* Output Slew Rate Enable for Port A Bit 4 */
    byte PTASE5      :1;                                       /* Output Slew Rate Enable for Port A Bit 5 */
    byte PTASE6      :1;                                       /* Output Slew Rate Enable for Port A Bit 6 */
    byte PTASE7      :1;                                       /* Output Slew Rate Enable for Port A Bit 7 */
  } Bits;
} PTASESTR;
extern volatile PTASESTR _PTASE @0xFFFF9851;
#define PTASE                           _PTASE.Byte
#define PTASE_PTASE0                    _PTASE.Bits.PTASE0
#define PTASE_PTASE1                    _PTASE.Bits.PTASE1
#define PTASE_PTASE2                    _PTASE.Bits.PTASE2
#define PTASE_PTASE3                    _PTASE.Bits.PTASE3
#define PTASE_PTASE4                    _PTASE.Bits.PTASE4
#define PTASE_PTASE5                    _PTASE.Bits.PTASE5
#define PTASE_PTASE6                    _PTASE.Bits.PTASE6
#define PTASE_PTASE7                    _PTASE.Bits.PTASE7

#define PTASE_PTASE0_MASK               1U
#define PTASE_PTASE1_MASK               2U
#define PTASE_PTASE2_MASK               4U
#define PTASE_PTASE3_MASK               8U
#define PTASE_PTASE4_MASK               16U
#define PTASE_PTASE5_MASK               32U
#define PTASE_PTASE6_MASK               64U
#define PTASE_PTASE7_MASK               128U


/*** PTADS - Port A Drive Strength Selection Register; 0xFFFF9852 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADS0      :1;                                       /* Output Drive Strength Selection for Port A Bit 0 */
    byte PTADS1      :1;                                       /* Output Drive Strength Selection for Port A Bit 1 */
    byte PTADS2      :1;                                       /* Output Drive Strength Selection for Port A Bit 2 */
    byte PTADS3      :1;                                       /* Output Drive Strength Selection for Port A Bit 3 */
    byte PTADS4      :1;                                       /* Output Drive Strength Selection for Port A Bit 4 */
    byte PTADS5      :1;                                       /* Output Drive Strength Selection for Port A Bit 5 */
    byte PTADS6      :1;                                       /* Output Drive Strength Selection for Port A Bit 6 */
    byte PTADS7      :1;                                       /* Output Drive Strength Selection for Port A Bit 7 */
  } Bits;
} PTADSSTR;
extern volatile PTADSSTR _PTADS @0xFFFF9852;
#define PTADS                           _PTADS.Byte
#define PTADS_PTADS0                    _PTADS.Bits.PTADS0
#define PTADS_PTADS1                    _PTADS.Bits.PTADS1
#define PTADS_PTADS2                    _PTADS.Bits.PTADS2
#define PTADS_PTADS3                    _PTADS.Bits.PTADS3
#define PTADS_PTADS4                    _PTADS.Bits.PTADS4
#define PTADS_PTADS5                    _PTADS.Bits.PTADS5
#define PTADS_PTADS6                    _PTADS.Bits.PTADS6
#define PTADS_PTADS7                    _PTADS.Bits.PTADS7

#define PTADS_PTADS0_MASK               1U
#define PTADS_PTADS1_MASK               2U
#define PTADS_PTADS2_MASK               4U
#define PTADS_PTADS3_MASK               8U
#define PTADS_PTADS4_MASK               16U
#define PTADS_PTADS5_MASK               32U
#define PTADS_PTADS6_MASK               64U
#define PTADS_PTADS7_MASK               128U


/*** PTAIFE - Port A Input Filter Enable Register; 0xFFFF9853 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAIFE0     :1;                                       /* Port A Input Filter Enable Bit 0 */
    byte PTAIFE1     :1;                                       /* Port A Input Filter Enable Bit 1 */
    byte PTAIFE2     :1;                                       /* Port A Input Filter Enable Bit 2 */
    byte PTAIFE3     :1;                                       /* Port A Input Filter Enable Bit 3 */
    byte PTAIFE4     :1;                                       /* Port A Input Filter Enable Bit 4 */
    byte PTAIFE5     :1;                                       /* Port A Input Filter Enable Bit 5 */
    byte PTAIFE6     :1;                                       /* Port A Input Filter Enable Bit 6 */
    byte PTAIFE7     :1;                                       /* Port A Input Filter Enable Bit 7 */
  } Bits;
} PTAIFESTR;
extern volatile PTAIFESTR _PTAIFE @0xFFFF9853;
#define PTAIFE                          _PTAIFE.Byte
#define PTAIFE_PTAIFE0                  _PTAIFE.Bits.PTAIFE0
#define PTAIFE_PTAIFE1                  _PTAIFE.Bits.PTAIFE1
#define PTAIFE_PTAIFE2                  _PTAIFE.Bits.PTAIFE2
#define PTAIFE_PTAIFE3                  _PTAIFE.Bits.PTAIFE3
#define PTAIFE_PTAIFE4                  _PTAIFE.Bits.PTAIFE4
#define PTAIFE_PTAIFE5                  _PTAIFE.Bits.PTAIFE5
#define PTAIFE_PTAIFE6                  _PTAIFE.Bits.PTAIFE6
#define PTAIFE_PTAIFE7                  _PTAIFE.Bits.PTAIFE7

#define PTAIFE_PTAIFE0_MASK             1U
#define PTAIFE_PTAIFE1_MASK             2U
#define PTAIFE_PTAIFE2_MASK             4U
#define PTAIFE_PTAIFE3_MASK             8U
#define PTAIFE_PTAIFE4_MASK             16U
#define PTAIFE_PTAIFE5_MASK             32U
#define PTAIFE_PTAIFE6_MASK             64U
#define PTAIFE_PTAIFE7_MASK             128U


/*** PTBPE - Port B Pull Enable Register; 0xFFFF9854 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBPE0      :1;                                       /* Internal Pull Enable for Port B Bit 0 */
    byte PTBPE1      :1;                                       /* Internal Pull Enable for Port B Bit 1 */
    byte PTBPE2      :1;                                       /* Internal Pull Enable for Port B Bit 2 */
    byte PTBPE3      :1;                                       /* Internal Pull Enable for Port B Bit 3 */
    byte PTBPE4      :1;                                       /* Internal Pull Enable for Port B Bit 4 */
    byte PTBPE5      :1;                                       /* Internal Pull Enable for Port B Bit 5 */
    byte PTBPE6      :1;                                       /* Internal Pull Enable for Port B Bit 6 */
    byte PTBPE7      :1;                                       /* Internal Pull Enable for Port B Bit 7 */
  } Bits;
} PTBPESTR;
extern volatile PTBPESTR _PTBPE @0xFFFF9854;
#define PTBPE                           _PTBPE.Byte
#define PTBPE_PTBPE0                    _PTBPE.Bits.PTBPE0
#define PTBPE_PTBPE1                    _PTBPE.Bits.PTBPE1
#define PTBPE_PTBPE2                    _PTBPE.Bits.PTBPE2
#define PTBPE_PTBPE3                    _PTBPE.Bits.PTBPE3
#define PTBPE_PTBPE4                    _PTBPE.Bits.PTBPE4
#define PTBPE_PTBPE5                    _PTBPE.Bits.PTBPE5
#define PTBPE_PTBPE6                    _PTBPE.Bits.PTBPE6
#define PTBPE_PTBPE7                    _PTBPE.Bits.PTBPE7

#define PTBPE_PTBPE0_MASK               1U
#define PTBPE_PTBPE1_MASK               2U
#define PTBPE_PTBPE2_MASK               4U
#define PTBPE_PTBPE3_MASK               8U
#define PTBPE_PTBPE4_MASK               16U
#define PTBPE_PTBPE5_MASK               32U
#define PTBPE_PTBPE6_MASK               64U
#define PTBPE_PTBPE7_MASK               128U


/*** PTBSE - Port B Slew Rate Enable Register; 0xFFFF9855 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBSE0      :1;                                       /* Output Slew Rate Enable for Port B Bit 0 */
    byte PTBSE1      :1;                                       /* Output Slew Rate Enable for Port B Bit 1 */
    byte PTBSE2      :1;                                       /* Output Slew Rate Enable for Port B Bit 2 */
    byte PTBSE3      :1;                                       /* Output Slew Rate Enable for Port B Bit 3 */
    byte PTBSE4      :1;                                       /* Output Slew Rate Enable for Port B Bit 4 */
    byte PTBSE5      :1;                                       /* Output Slew Rate Enable for Port B Bit 5 */
    byte PTBSE6      :1;                                       /* Output Slew Rate Enable for Port B Bit 6 */
    byte PTBSE7      :1;                                       /* Output Slew Rate Enable for Port B Bit 7 */
  } Bits;
} PTBSESTR;
extern volatile PTBSESTR _PTBSE @0xFFFF9855;
#define PTBSE                           _PTBSE.Byte
#define PTBSE_PTBSE0                    _PTBSE.Bits.PTBSE0
#define PTBSE_PTBSE1                    _PTBSE.Bits.PTBSE1
#define PTBSE_PTBSE2                    _PTBSE.Bits.PTBSE2
#define PTBSE_PTBSE3                    _PTBSE.Bits.PTBSE3
#define PTBSE_PTBSE4                    _PTBSE.Bits.PTBSE4
#define PTBSE_PTBSE5                    _PTBSE.Bits.PTBSE5
#define PTBSE_PTBSE6                    _PTBSE.Bits.PTBSE6
#define PTBSE_PTBSE7                    _PTBSE.Bits.PTBSE7

#define PTBSE_PTBSE0_MASK               1U
#define PTBSE_PTBSE1_MASK               2U
#define PTBSE_PTBSE2_MASK               4U
#define PTBSE_PTBSE3_MASK               8U
#define PTBSE_PTBSE4_MASK               16U
#define PTBSE_PTBSE5_MASK               32U
#define PTBSE_PTBSE6_MASK               64U
#define PTBSE_PTBSE7_MASK               128U


/*** PTBDS - Port B Drive Strength Selection Register; 0xFFFF9856 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDS0      :1;                                       /* Output Drive Strength Selection for Port B Bit 0 */
    byte PTBDS1      :1;                                       /* Output Drive Strength Selection for Port B Bit 1 */
    byte PTBDS2      :1;                                       /* Output Drive Strength Selection for Port B Bit 2 */
    byte PTBDS3      :1;                                       /* Output Drive Strength Selection for Port B Bit 3 */
    byte PTBDS4      :1;                                       /* Output Drive Strength Selection for Port B Bit 4 */
    byte PTBDS5      :1;                                       /* Output Drive Strength Selection for Port B Bit 5 */
    byte PTBDS6      :1;                                       /* Output Drive Strength Selection for Port B Bit 6 */
    byte PTBDS7      :1;                                       /* Output Drive Strength Selection for Port B Bit 7 */
  } Bits;
} PTBDSSTR;
extern volatile PTBDSSTR _PTBDS @0xFFFF9856;
#define PTBDS                           _PTBDS.Byte
#define PTBDS_PTBDS0                    _PTBDS.Bits.PTBDS0
#define PTBDS_PTBDS1                    _PTBDS.Bits.PTBDS1
#define PTBDS_PTBDS2                    _PTBDS.Bits.PTBDS2
#define PTBDS_PTBDS3                    _PTBDS.Bits.PTBDS3
#define PTBDS_PTBDS4                    _PTBDS.Bits.PTBDS4
#define PTBDS_PTBDS5                    _PTBDS.Bits.PTBDS5
#define PTBDS_PTBDS6                    _PTBDS.Bits.PTBDS6
#define PTBDS_PTBDS7                    _PTBDS.Bits.PTBDS7

#define PTBDS_PTBDS0_MASK               1U
#define PTBDS_PTBDS1_MASK               2U
#define PTBDS_PTBDS2_MASK               4U
#define PTBDS_PTBDS3_MASK               8U
#define PTBDS_PTBDS4_MASK               16U
#define PTBDS_PTBDS5_MASK               32U
#define PTBDS_PTBDS6_MASK               64U
#define PTBDS_PTBDS7_MASK               128U


/*** PTBIFE - Port B Input Filter Enable Register; 0xFFFF9857 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBIFE0     :1;                                       /* Port B Input Filter Enable Bit 0 */
    byte PTBIFE1     :1;                                       /* Port B Input Filter Enable Bit 1 */
    byte PTBIFE2     :1;                                       /* Port B Input Filter Enable Bit 2 */
    byte PTBIFE3     :1;                                       /* Port B Input Filter Enable Bit 3 */
    byte PTBIFE4     :1;                                       /* Port B Input Filter Enable Bit 4 */
    byte PTBIFE5     :1;                                       /* Port B Input Filter Enable Bit 5 */
    byte PTBIFE6     :1;                                       /* Port B Input Filter Enable Bit 6 */
    byte PTBIFE7     :1;                                       /* Port B Input Filter Enable Bit 7 */
  } Bits;
} PTBIFESTR;
extern volatile PTBIFESTR _PTBIFE @0xFFFF9857;
#define PTBIFE                          _PTBIFE.Byte
#define PTBIFE_PTBIFE0                  _PTBIFE.Bits.PTBIFE0
#define PTBIFE_PTBIFE1                  _PTBIFE.Bits.PTBIFE1
#define PTBIFE_PTBIFE2                  _PTBIFE.Bits.PTBIFE2
#define PTBIFE_PTBIFE3                  _PTBIFE.Bits.PTBIFE3
#define PTBIFE_PTBIFE4                  _PTBIFE.Bits.PTBIFE4
#define PTBIFE_PTBIFE5                  _PTBIFE.Bits.PTBIFE5
#define PTBIFE_PTBIFE6                  _PTBIFE.Bits.PTBIFE6
#define PTBIFE_PTBIFE7                  _PTBIFE.Bits.PTBIFE7

#define PTBIFE_PTBIFE0_MASK             1U
#define PTBIFE_PTBIFE1_MASK             2U
#define PTBIFE_PTBIFE2_MASK             4U
#define PTBIFE_PTBIFE3_MASK             8U
#define PTBIFE_PTBIFE4_MASK             16U
#define PTBIFE_PTBIFE5_MASK             32U
#define PTBIFE_PTBIFE6_MASK             64U
#define PTBIFE_PTBIFE7_MASK             128U


/*** PTCPE - Port C Pull Enable Register; 0xFFFF9858 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCPE0      :1;                                       /* Internal Pull Enable for Port C Bit 0 */
    byte PTCPE1      :1;                                       /* Internal Pull Enable for Port C Bit 1 */
    byte PTCPE2      :1;                                       /* Internal Pull Enable for Port C Bit 2 */
    byte PTCPE3      :1;                                       /* Internal Pull Enable for Port C Bit 3 */
    byte PTCPE4      :1;                                       /* Internal Pull Enable for Port C Bit 4 */
    byte PTCPE5      :1;                                       /* Internal Pull Enable for Port C Bit 5 */
    byte PTCPE6      :1;                                       /* Internal Pull Enable for Port C Bit 6 */
    byte PTCPE7      :1;                                       /* Internal Pull Enable for Port C Bit 7 */
  } Bits;
} PTCPESTR;
extern volatile PTCPESTR _PTCPE @0xFFFF9858;
#define PTCPE                           _PTCPE.Byte
#define PTCPE_PTCPE0                    _PTCPE.Bits.PTCPE0
#define PTCPE_PTCPE1                    _PTCPE.Bits.PTCPE1
#define PTCPE_PTCPE2                    _PTCPE.Bits.PTCPE2
#define PTCPE_PTCPE3                    _PTCPE.Bits.PTCPE3
#define PTCPE_PTCPE4                    _PTCPE.Bits.PTCPE4
#define PTCPE_PTCPE5                    _PTCPE.Bits.PTCPE5
#define PTCPE_PTCPE6                    _PTCPE.Bits.PTCPE6
#define PTCPE_PTCPE7                    _PTCPE.Bits.PTCPE7

#define PTCPE_PTCPE0_MASK               1U
#define PTCPE_PTCPE1_MASK               2U
#define PTCPE_PTCPE2_MASK               4U
#define PTCPE_PTCPE3_MASK               8U
#define PTCPE_PTCPE4_MASK               16U
#define PTCPE_PTCPE5_MASK               32U
#define PTCPE_PTCPE6_MASK               64U
#define PTCPE_PTCPE7_MASK               128U


/*** PTCSE - Port C Slew Rate Enable Register; 0xFFFF9859 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCSE0      :1;                                       /* Output Slew Rate Enable for Port C Bit 0 */
    byte PTCSE1      :1;                                       /* Output Slew Rate Enable for Port C Bit 1 */
    byte PTCSE2      :1;                                       /* Output Slew Rate Enable for Port C Bit 2 */
    byte PTCSE3      :1;                                       /* Output Slew Rate Enable for Port C Bit 3 */
    byte PTCSE4      :1;                                       /* Output Slew Rate Enable for Port C Bit 4 */
    byte PTCSE5      :1;                                       /* Output Slew Rate Enable for Port C Bit 5 */
    byte PTCSE6      :1;                                       /* Output Slew Rate Enable for Port C Bit 6 */
    byte PTCSE7      :1;                                       /* Output Slew Rate Enable for Port C Bit 7 */
  } Bits;
} PTCSESTR;
extern volatile PTCSESTR _PTCSE @0xFFFF9859;
#define PTCSE                           _PTCSE.Byte
#define PTCSE_PTCSE0                    _PTCSE.Bits.PTCSE0
#define PTCSE_PTCSE1                    _PTCSE.Bits.PTCSE1
#define PTCSE_PTCSE2                    _PTCSE.Bits.PTCSE2
#define PTCSE_PTCSE3                    _PTCSE.Bits.PTCSE3
#define PTCSE_PTCSE4                    _PTCSE.Bits.PTCSE4
#define PTCSE_PTCSE5                    _PTCSE.Bits.PTCSE5
#define PTCSE_PTCSE6                    _PTCSE.Bits.PTCSE6
#define PTCSE_PTCSE7                    _PTCSE.Bits.PTCSE7

#define PTCSE_PTCSE0_MASK               1U
#define PTCSE_PTCSE1_MASK               2U
#define PTCSE_PTCSE2_MASK               4U
#define PTCSE_PTCSE3_MASK               8U
#define PTCSE_PTCSE4_MASK               16U
#define PTCSE_PTCSE5_MASK               32U
#define PTCSE_PTCSE6_MASK               64U
#define PTCSE_PTCSE7_MASK               128U


/*** PTCDS - Port C Drive Strength Selection Register; 0xFFFF985A ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDS0      :1;                                       /* Output Drive Strength Selection for Port C Bit 0 */
    byte PTCDS1      :1;                                       /* Output Drive Strength Selection for Port C Bit 1 */
    byte PTCDS2      :1;                                       /* Output Drive Strength Selection for Port C Bit 2 */
    byte PTCDS3      :1;                                       /* Output Drive Strength Selection for Port C Bit 3 */
    byte PTCDS4      :1;                                       /* Output Drive Strength Selection for Port C Bit 4 */
    byte PTCDS5      :1;                                       /* Output Drive Strength Selection for Port C Bit 5 */
    byte PTCDS6      :1;                                       /* Output Drive Strength Selection for Port C Bit 6 */
    byte PTCDS7      :1;                                       /* Output Drive Strength Selection for Port C Bit 7 */
  } Bits;
} PTCDSSTR;
extern volatile PTCDSSTR _PTCDS @0xFFFF985A;
#define PTCDS                           _PTCDS.Byte
#define PTCDS_PTCDS0                    _PTCDS.Bits.PTCDS0
#define PTCDS_PTCDS1                    _PTCDS.Bits.PTCDS1
#define PTCDS_PTCDS2                    _PTCDS.Bits.PTCDS2
#define PTCDS_PTCDS3                    _PTCDS.Bits.PTCDS3
#define PTCDS_PTCDS4                    _PTCDS.Bits.PTCDS4
#define PTCDS_PTCDS5                    _PTCDS.Bits.PTCDS5
#define PTCDS_PTCDS6                    _PTCDS.Bits.PTCDS6
#define PTCDS_PTCDS7                    _PTCDS.Bits.PTCDS7

#define PTCDS_PTCDS0_MASK               1U
#define PTCDS_PTCDS1_MASK               2U
#define PTCDS_PTCDS2_MASK               4U
#define PTCDS_PTCDS3_MASK               8U
#define PTCDS_PTCDS4_MASK               16U
#define PTCDS_PTCDS5_MASK               32U
#define PTCDS_PTCDS6_MASK               64U
#define PTCDS_PTCDS7_MASK               128U


/*** PTCIFE - Port C Input Filter Enable Register; 0xFFFF985B ***/
typedef union {
  byte Byte;
  struct {
    byte PTCIFE0     :1;                                       /* Port C Input Filter Enable Bit 0 */
    byte PTCIFE1     :1;                                       /* Port C Input Filter Enable Bit 1 */
    byte PTCIFE2     :1;                                       /* Port C Input Filter Enable Bit 2 */
    byte PTCIFE3     :1;                                       /* Port C Input Filter Enable Bit 3 */
    byte PTCIFE4     :1;                                       /* Port C Input Filter Enable Bit 4 */
    byte PTCIFE5     :1;                                       /* Port C Input Filter Enable Bit 5 */
    byte PTCIFE6     :1;                                       /* Port C Input Filter Enable Bit 6 */
    byte PTCIFE7     :1;                                       /* Port C Input Filter Enable Bit 7 */
  } Bits;
} PTCIFESTR;
extern volatile PTCIFESTR _PTCIFE @0xFFFF985B;
#define PTCIFE                          _PTCIFE.Byte
#define PTCIFE_PTCIFE0                  _PTCIFE.Bits.PTCIFE0
#define PTCIFE_PTCIFE1                  _PTCIFE.Bits.PTCIFE1
#define PTCIFE_PTCIFE2                  _PTCIFE.Bits.PTCIFE2
#define PTCIFE_PTCIFE3                  _PTCIFE.Bits.PTCIFE3
#define PTCIFE_PTCIFE4                  _PTCIFE.Bits.PTCIFE4
#define PTCIFE_PTCIFE5                  _PTCIFE.Bits.PTCIFE5
#define PTCIFE_PTCIFE6                  _PTCIFE.Bits.PTCIFE6
#define PTCIFE_PTCIFE7                  _PTCIFE.Bits.PTCIFE7

#define PTCIFE_PTCIFE0_MASK             1U
#define PTCIFE_PTCIFE1_MASK             2U
#define PTCIFE_PTCIFE2_MASK             4U
#define PTCIFE_PTCIFE3_MASK             8U
#define PTCIFE_PTCIFE4_MASK             16U
#define PTCIFE_PTCIFE5_MASK             32U
#define PTCIFE_PTCIFE6_MASK             64U
#define PTCIFE_PTCIFE7_MASK             128U


/*** PTDPE - Port D Pull Enable Register; 0xFFFF985C ***/
typedef union {
  byte Byte;
  struct {
    byte PTDPE0      :1;                                       /* Internal Pull Enable for Port D Bit 0 */
    byte PTDPE1      :1;                                       /* Internal Pull Enable for Port D Bit 1 */
    byte PTDPE2      :1;                                       /* Internal Pull Enable for Port D Bit 2 */
    byte PTDPE3      :1;                                       /* Internal Pull Enable for Port D Bit 3 */
    byte PTDPE4      :1;                                       /* Internal Pull Enable for Port D Bit 4 */
    byte PTDPE5      :1;                                       /* Internal Pull Enable for Port D Bit 5 */
    byte PTDPE6      :1;                                       /* Internal Pull Enable for Port D Bit 6 */
    byte PTDPE7      :1;                                       /* Internal Pull Enable for Port D Bit 7 */
  } Bits;
} PTDPESTR;
extern volatile PTDPESTR _PTDPE @0xFFFF985C;
#define PTDPE                           _PTDPE.Byte
#define PTDPE_PTDPE0                    _PTDPE.Bits.PTDPE0
#define PTDPE_PTDPE1                    _PTDPE.Bits.PTDPE1
#define PTDPE_PTDPE2                    _PTDPE.Bits.PTDPE2
#define PTDPE_PTDPE3                    _PTDPE.Bits.PTDPE3
#define PTDPE_PTDPE4                    _PTDPE.Bits.PTDPE4
#define PTDPE_PTDPE5                    _PTDPE.Bits.PTDPE5
#define PTDPE_PTDPE6                    _PTDPE.Bits.PTDPE6
#define PTDPE_PTDPE7                    _PTDPE.Bits.PTDPE7

#define PTDPE_PTDPE0_MASK               1U
#define PTDPE_PTDPE1_MASK               2U
#define PTDPE_PTDPE2_MASK               4U
#define PTDPE_PTDPE3_MASK               8U
#define PTDPE_PTDPE4_MASK               16U
#define PTDPE_PTDPE5_MASK               32U
#define PTDPE_PTDPE6_MASK               64U
#define PTDPE_PTDPE7_MASK               128U


/*** PTDSE - Port D Slew Rate Enable Register; 0xFFFF985D ***/
typedef union {
  byte Byte;
  struct {
    byte PTDSE0      :1;                                       /* Output Slew Rate Enable for Port D Bit 0 */
    byte PTDSE1      :1;                                       /* Output Slew Rate Enable for Port D Bit 1 */
    byte PTDSE2      :1;                                       /* Output Slew Rate Enable for Port D Bit 2 */
    byte PTDSE3      :1;                                       /* Output Slew Rate Enable for Port D Bit 3 */
    byte PTDSE4      :1;                                       /* Output Slew Rate Enable for Port D Bit 4 */
    byte PTDSE5      :1;                                       /* Output Slew Rate Enable for Port D Bit 5 */
    byte PTDSE6      :1;                                       /* Output Slew Rate Enable for Port D Bit 6 */
    byte PTDSE7      :1;                                       /* Output Slew Rate Enable for Port D Bit 7 */
  } Bits;
} PTDSESTR;
extern volatile PTDSESTR _PTDSE @0xFFFF985D;
#define PTDSE                           _PTDSE.Byte
#define PTDSE_PTDSE0                    _PTDSE.Bits.PTDSE0
#define PTDSE_PTDSE1                    _PTDSE.Bits.PTDSE1
#define PTDSE_PTDSE2                    _PTDSE.Bits.PTDSE2
#define PTDSE_PTDSE3                    _PTDSE.Bits.PTDSE3
#define PTDSE_PTDSE4                    _PTDSE.Bits.PTDSE4
#define PTDSE_PTDSE5                    _PTDSE.Bits.PTDSE5
#define PTDSE_PTDSE6                    _PTDSE.Bits.PTDSE6
#define PTDSE_PTDSE7                    _PTDSE.Bits.PTDSE7

#define PTDSE_PTDSE0_MASK               1U
#define PTDSE_PTDSE1_MASK               2U
#define PTDSE_PTDSE2_MASK               4U
#define PTDSE_PTDSE3_MASK               8U
#define PTDSE_PTDSE4_MASK               16U
#define PTDSE_PTDSE5_MASK               32U
#define PTDSE_PTDSE6_MASK               64U
#define PTDSE_PTDSE7_MASK               128U


/*** PTDDS - Port D Drive Strength Selection Register; 0xFFFF985E ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDS0      :1;                                       /* Output Drive Strength Selection for Port D Bit 0 */
    byte PTDDS1      :1;                                       /* Output Drive Strength Selection for Port D Bit 1 */
    byte PTDDS2      :1;                                       /* Output Drive Strength Selection for Port D Bit 2 */
    byte PTDDS3      :1;                                       /* Output Drive Strength Selection for Port D Bit 3 */
    byte PTDDS4      :1;                                       /* Output Drive Strength Selection for Port D Bit 4 */
    byte PTDDS5      :1;                                       /* Output Drive Strength Selection for Port D Bit 5 */
    byte PTDDS6      :1;                                       /* Output Drive Strength Selection for Port D Bit 6 */
    byte PTDDS7      :1;                                       /* Output Drive Strength Selection for Port D Bit 7 */
  } Bits;
} PTDDSSTR;
extern volatile PTDDSSTR _PTDDS @0xFFFF985E;
#define PTDDS                           _PTDDS.Byte
#define PTDDS_PTDDS0                    _PTDDS.Bits.PTDDS0
#define PTDDS_PTDDS1                    _PTDDS.Bits.PTDDS1
#define PTDDS_PTDDS2                    _PTDDS.Bits.PTDDS2
#define PTDDS_PTDDS3                    _PTDDS.Bits.PTDDS3
#define PTDDS_PTDDS4                    _PTDDS.Bits.PTDDS4
#define PTDDS_PTDDS5                    _PTDDS.Bits.PTDDS5
#define PTDDS_PTDDS6                    _PTDDS.Bits.PTDDS6
#define PTDDS_PTDDS7                    _PTDDS.Bits.PTDDS7

#define PTDDS_PTDDS0_MASK               1U
#define PTDDS_PTDDS1_MASK               2U
#define PTDDS_PTDDS2_MASK               4U
#define PTDDS_PTDDS3_MASK               8U
#define PTDDS_PTDDS4_MASK               16U
#define PTDDS_PTDDS5_MASK               32U
#define PTDDS_PTDDS6_MASK               64U
#define PTDDS_PTDDS7_MASK               128U


/*** PTDIFE - Port D Input Filter Enable Register; 0xFFFF985F ***/
typedef union {
  byte Byte;
  struct {
    byte PTDIFE0     :1;                                       /* Port D Input Filter Enable Bit 0 */
    byte PTDIFE1     :1;                                       /* Port D Input Filter Enable Bit 1 */
    byte PTDIFE2     :1;                                       /* Port D Input Filter Enable Bit 2 */
    byte PTDIFE3     :1;                                       /* Port D Input Filter Enable Bit 3 */
    byte PTDIFE4     :1;                                       /* Port D Input Filter Enable Bit 4 */
    byte PTDIFE5     :1;                                       /* Port D Input Filter Enable Bit 5 */
    byte PTDIFE6     :1;                                       /* Port D Input Filter Enable Bit 6 */
    byte PTDIFE7     :1;                                       /* Port D Input Filter Enable Bit 7 */
  } Bits;
} PTDIFESTR;
extern volatile PTDIFESTR _PTDIFE @0xFFFF985F;
#define PTDIFE                          _PTDIFE.Byte
#define PTDIFE_PTDIFE0                  _PTDIFE.Bits.PTDIFE0
#define PTDIFE_PTDIFE1                  _PTDIFE.Bits.PTDIFE1
#define PTDIFE_PTDIFE2                  _PTDIFE.Bits.PTDIFE2
#define PTDIFE_PTDIFE3                  _PTDIFE.Bits.PTDIFE3
#define PTDIFE_PTDIFE4                  _PTDIFE.Bits.PTDIFE4
#define PTDIFE_PTDIFE5                  _PTDIFE.Bits.PTDIFE5
#define PTDIFE_PTDIFE6                  _PTDIFE.Bits.PTDIFE6
#define PTDIFE_PTDIFE7                  _PTDIFE.Bits.PTDIFE7

#define PTDIFE_PTDIFE0_MASK             1U
#define PTDIFE_PTDIFE1_MASK             2U
#define PTDIFE_PTDIFE2_MASK             4U
#define PTDIFE_PTDIFE3_MASK             8U
#define PTDIFE_PTDIFE4_MASK             16U
#define PTDIFE_PTDIFE5_MASK             32U
#define PTDIFE_PTDIFE6_MASK             64U
#define PTDIFE_PTDIFE7_MASK             128U


/*** PTEPE - Port E Pull Enable Register; 0xFFFF9860 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEPE0      :1;                                       /* Internal Pull Enable for Port E Bit 0 */
    byte PTEPE1      :1;                                       /* Internal Pull Enable for Port E Bit 1 */
    byte PTEPE2      :1;                                       /* Internal Pull Enable for Port E Bit 2 */
    byte PTEPE3      :1;                                       /* Internal Pull Enable for Port E Bit 3 */
    byte PTEPE4      :1;                                       /* Internal Pull Enable for Port E Bit 4 */
    byte PTEPE5      :1;                                       /* Internal Pull Enable for Port E Bit 5 */
    byte PTEPE6      :1;                                       /* Internal Pull Enable for Port E Bit 6 */
    byte PTEPE7      :1;                                       /* Internal Pull Enable for Port E Bit 7 */
  } Bits;
} PTEPESTR;
extern volatile PTEPESTR _PTEPE @0xFFFF9860;
#define PTEPE                           _PTEPE.Byte
#define PTEPE_PTEPE0                    _PTEPE.Bits.PTEPE0
#define PTEPE_PTEPE1                    _PTEPE.Bits.PTEPE1
#define PTEPE_PTEPE2                    _PTEPE.Bits.PTEPE2
#define PTEPE_PTEPE3                    _PTEPE.Bits.PTEPE3
#define PTEPE_PTEPE4                    _PTEPE.Bits.PTEPE4
#define PTEPE_PTEPE5                    _PTEPE.Bits.PTEPE5
#define PTEPE_PTEPE6                    _PTEPE.Bits.PTEPE6
#define PTEPE_PTEPE7                    _PTEPE.Bits.PTEPE7

#define PTEPE_PTEPE0_MASK               1U
#define PTEPE_PTEPE1_MASK               2U
#define PTEPE_PTEPE2_MASK               4U
#define PTEPE_PTEPE3_MASK               8U
#define PTEPE_PTEPE4_MASK               16U
#define PTEPE_PTEPE5_MASK               32U
#define PTEPE_PTEPE6_MASK               64U
#define PTEPE_PTEPE7_MASK               128U


/*** PTESE - Port E Slew Rate Enable Register; 0xFFFF9861 ***/
typedef union {
  byte Byte;
  struct {
    byte PTESE0      :1;                                       /* Output Slew Rate Enable for Port E Bit 0 */
    byte PTESE1      :1;                                       /* Output Slew Rate Enable for Port E Bit 1 */
    byte PTESE2      :1;                                       /* Output Slew Rate Enable for Port E Bit 2 */
    byte PTESE3      :1;                                       /* Output Slew Rate Enable for Port E Bit 3 */
    byte PTESE4      :1;                                       /* Output Slew Rate Enable for Port E Bit 4 */
    byte PTESE5      :1;                                       /* Output Slew Rate Enable for Port E Bit 5 */
    byte PTESE6      :1;                                       /* Output Slew Rate Enable for Port E Bit 6 */
    byte PTESE7      :1;                                       /* Output Slew Rate Enable for Port E Bit 7 */
  } Bits;
} PTESESTR;
extern volatile PTESESTR _PTESE @0xFFFF9861;
#define PTESE                           _PTESE.Byte
#define PTESE_PTESE0                    _PTESE.Bits.PTESE0
#define PTESE_PTESE1                    _PTESE.Bits.PTESE1
#define PTESE_PTESE2                    _PTESE.Bits.PTESE2
#define PTESE_PTESE3                    _PTESE.Bits.PTESE3
#define PTESE_PTESE4                    _PTESE.Bits.PTESE4
#define PTESE_PTESE5                    _PTESE.Bits.PTESE5
#define PTESE_PTESE6                    _PTESE.Bits.PTESE6
#define PTESE_PTESE7                    _PTESE.Bits.PTESE7

#define PTESE_PTESE0_MASK               1U
#define PTESE_PTESE1_MASK               2U
#define PTESE_PTESE2_MASK               4U
#define PTESE_PTESE3_MASK               8U
#define PTESE_PTESE4_MASK               16U
#define PTESE_PTESE5_MASK               32U
#define PTESE_PTESE6_MASK               64U
#define PTESE_PTESE7_MASK               128U


/*** PTEDS - Port E Drive Strength Selection Register; 0xFFFF9862 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDS0      :1;                                       /* Output Drive Strength Selection for Port E Bit 0 */
    byte PTEDS1      :1;                                       /* Output Drive Strength Selection for Port E Bit 1 */
    byte PTEDS2      :1;                                       /* Output Drive Strength Selection for Port E Bit 2 */
    byte PTEDS3      :1;                                       /* Output Drive Strength Selection for Port E Bit 3 */
    byte PTEDS4      :1;                                       /* Output Drive Strength Selection for Port E Bit 4 */
    byte PTEDS5      :1;                                       /* Output Drive Strength Selection for Port E Bit 5 */
    byte PTEDS6      :1;                                       /* Output Drive Strength Selection for Port E Bit 6 */
    byte PTEDS7      :1;                                       /* Output Drive Strength Selection for Port E Bit 7 */
  } Bits;
} PTEDSSTR;
extern volatile PTEDSSTR _PTEDS @0xFFFF9862;
#define PTEDS                           _PTEDS.Byte
#define PTEDS_PTEDS0                    _PTEDS.Bits.PTEDS0
#define PTEDS_PTEDS1                    _PTEDS.Bits.PTEDS1
#define PTEDS_PTEDS2                    _PTEDS.Bits.PTEDS2
#define PTEDS_PTEDS3                    _PTEDS.Bits.PTEDS3
#define PTEDS_PTEDS4                    _PTEDS.Bits.PTEDS4
#define PTEDS_PTEDS5                    _PTEDS.Bits.PTEDS5
#define PTEDS_PTEDS6                    _PTEDS.Bits.PTEDS6
#define PTEDS_PTEDS7                    _PTEDS.Bits.PTEDS7

#define PTEDS_PTEDS0_MASK               1U
#define PTEDS_PTEDS1_MASK               2U
#define PTEDS_PTEDS2_MASK               4U
#define PTEDS_PTEDS3_MASK               8U
#define PTEDS_PTEDS4_MASK               16U
#define PTEDS_PTEDS5_MASK               32U
#define PTEDS_PTEDS6_MASK               64U
#define PTEDS_PTEDS7_MASK               128U


/*** PTEIFE - Port E Input Filter Enable Register; 0xFFFF9863 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEIFE0     :1;                                       /* Port E Input Filter Enable Bit 0 */
    byte PTEIFE1     :1;                                       /* Port E Input Filter Enable Bit 1 */
    byte PTEIFE2     :1;                                       /* Port E Input Filter Enable Bit 2 */
    byte PTEIFE3     :1;                                       /* Port E Input Filter Enable Bit 3 */
    byte PTEIFE4     :1;                                       /* Port E Input Filter Enable Bit 4 */
    byte PTEIFE5     :1;                                       /* Port E Input Filter Enable Bit 5 */
    byte PTEIFE6     :1;                                       /* Port E Input Filter Enable Bit 6 */
    byte PTEIFE7     :1;                                       /* Port E Input Filter Enable Bit 7 */
  } Bits;
} PTEIFESTR;
extern volatile PTEIFESTR _PTEIFE @0xFFFF9863;
#define PTEIFE                          _PTEIFE.Byte
#define PTEIFE_PTEIFE0                  _PTEIFE.Bits.PTEIFE0
#define PTEIFE_PTEIFE1                  _PTEIFE.Bits.PTEIFE1
#define PTEIFE_PTEIFE2                  _PTEIFE.Bits.PTEIFE2
#define PTEIFE_PTEIFE3                  _PTEIFE.Bits.PTEIFE3
#define PTEIFE_PTEIFE4                  _PTEIFE.Bits.PTEIFE4
#define PTEIFE_PTEIFE5                  _PTEIFE.Bits.PTEIFE5
#define PTEIFE_PTEIFE6                  _PTEIFE.Bits.PTEIFE6
#define PTEIFE_PTEIFE7                  _PTEIFE.Bits.PTEIFE7

#define PTEIFE_PTEIFE0_MASK             1U
#define PTEIFE_PTEIFE1_MASK             2U
#define PTEIFE_PTEIFE2_MASK             4U
#define PTEIFE_PTEIFE3_MASK             8U
#define PTEIFE_PTEIFE4_MASK             16U
#define PTEIFE_PTEIFE5_MASK             32U
#define PTEIFE_PTEIFE6_MASK             64U
#define PTEIFE_PTEIFE7_MASK             128U


/*** PTFPE - Port F Pull Enable Register; 0xFFFF9864 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFPE0      :1;                                       /* Internal Pull Enable for Port F Bit 0 */
    byte PTFPE1      :1;                                       /* Internal Pull Enable for Port F Bit 1 */
    byte PTFPE2      :1;                                       /* Internal Pull Enable for Port F Bit 2 */
    byte PTFPE3      :1;                                       /* Internal Pull Enable for Port F Bit 3 */
    byte PTFPE4      :1;                                       /* Internal Pull Enable for Port F Bit 4 */
    byte PTFPE5      :1;                                       /* Internal Pull Enable for Port F Bit 5 */
    byte PTFPE6      :1;                                       /* Internal Pull Enable for Port F Bit 6 */
    byte PTFPE7      :1;                                       /* Internal Pull Enable for Port F Bit 7 */
  } Bits;
} PTFPESTR;
extern volatile PTFPESTR _PTFPE @0xFFFF9864;
#define PTFPE                           _PTFPE.Byte
#define PTFPE_PTFPE0                    _PTFPE.Bits.PTFPE0
#define PTFPE_PTFPE1                    _PTFPE.Bits.PTFPE1
#define PTFPE_PTFPE2                    _PTFPE.Bits.PTFPE2
#define PTFPE_PTFPE3                    _PTFPE.Bits.PTFPE3
#define PTFPE_PTFPE4                    _PTFPE.Bits.PTFPE4
#define PTFPE_PTFPE5                    _PTFPE.Bits.PTFPE5
#define PTFPE_PTFPE6                    _PTFPE.Bits.PTFPE6
#define PTFPE_PTFPE7                    _PTFPE.Bits.PTFPE7

#define PTFPE_PTFPE0_MASK               1U
#define PTFPE_PTFPE1_MASK               2U
#define PTFPE_PTFPE2_MASK               4U
#define PTFPE_PTFPE3_MASK               8U
#define PTFPE_PTFPE4_MASK               16U
#define PTFPE_PTFPE5_MASK               32U
#define PTFPE_PTFPE6_MASK               64U
#define PTFPE_PTFPE7_MASK               128U


/*** PTFSE - Port F Slew Rate Enable Register; 0xFFFF9865 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFSE0      :1;                                       /* Output Slew Rate Enable for Port F Bit 0 */
    byte PTFSE1      :1;                                       /* Output Slew Rate Enable for Port F Bit 1 */
    byte PTFSE2      :1;                                       /* Output Slew Rate Enable for Port F Bit 2 */
    byte PTFSE3      :1;                                       /* Output Slew Rate Enable for Port F Bit 3 */
    byte PTFSE4      :1;                                       /* Output Slew Rate Enable for Port F Bit 4 */
    byte PTFSE5      :1;                                       /* Output Slew Rate Enable for Port F Bit 5 */
    byte PTFSE6      :1;                                       /* Output Slew Rate Enable for Port F Bit 6 */
    byte PTFSE7      :1;                                       /* Output Slew Rate Enable for Port F Bit 7 */
  } Bits;
} PTFSESTR;
extern volatile PTFSESTR _PTFSE @0xFFFF9865;
#define PTFSE                           _PTFSE.Byte
#define PTFSE_PTFSE0                    _PTFSE.Bits.PTFSE0
#define PTFSE_PTFSE1                    _PTFSE.Bits.PTFSE1
#define PTFSE_PTFSE2                    _PTFSE.Bits.PTFSE2
#define PTFSE_PTFSE3                    _PTFSE.Bits.PTFSE3
#define PTFSE_PTFSE4                    _PTFSE.Bits.PTFSE4
#define PTFSE_PTFSE5                    _PTFSE.Bits.PTFSE5
#define PTFSE_PTFSE6                    _PTFSE.Bits.PTFSE6
#define PTFSE_PTFSE7                    _PTFSE.Bits.PTFSE7

#define PTFSE_PTFSE0_MASK               1U
#define PTFSE_PTFSE1_MASK               2U
#define PTFSE_PTFSE2_MASK               4U
#define PTFSE_PTFSE3_MASK               8U
#define PTFSE_PTFSE4_MASK               16U
#define PTFSE_PTFSE5_MASK               32U
#define PTFSE_PTFSE6_MASK               64U
#define PTFSE_PTFSE7_MASK               128U


/*** PTFDS - Port F Drive Strength Selection Register; 0xFFFF9866 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDS0      :1;                                       /* Output Drive Strength Selection for Port F Bit 0 */
    byte PTFDS1      :1;                                       /* Output Drive Strength Selection for Port F Bit 1 */
    byte PTFDS2      :1;                                       /* Output Drive Strength Selection for Port F Bit 2 */
    byte PTFDS3      :1;                                       /* Output Drive Strength Selection for Port F Bit 3 */
    byte PTFDS4      :1;                                       /* Output Drive Strength Selection for Port F Bit 4 */
    byte PTFDS5      :1;                                       /* Output Drive Strength Selection for Port F Bit 5 */
    byte PTFDS6      :1;                                       /* Output Drive Strength Selection for Port F Bit 6 */
    byte PTFDS7      :1;                                       /* Output Drive Strength Selection for Port F Bit 7 */
  } Bits;
} PTFDSSTR;
extern volatile PTFDSSTR _PTFDS @0xFFFF9866;
#define PTFDS                           _PTFDS.Byte
#define PTFDS_PTFDS0                    _PTFDS.Bits.PTFDS0
#define PTFDS_PTFDS1                    _PTFDS.Bits.PTFDS1
#define PTFDS_PTFDS2                    _PTFDS.Bits.PTFDS2
#define PTFDS_PTFDS3                    _PTFDS.Bits.PTFDS3
#define PTFDS_PTFDS4                    _PTFDS.Bits.PTFDS4
#define PTFDS_PTFDS5                    _PTFDS.Bits.PTFDS5
#define PTFDS_PTFDS6                    _PTFDS.Bits.PTFDS6
#define PTFDS_PTFDS7                    _PTFDS.Bits.PTFDS7

#define PTFDS_PTFDS0_MASK               1U
#define PTFDS_PTFDS1_MASK               2U
#define PTFDS_PTFDS2_MASK               4U
#define PTFDS_PTFDS3_MASK               8U
#define PTFDS_PTFDS4_MASK               16U
#define PTFDS_PTFDS5_MASK               32U
#define PTFDS_PTFDS6_MASK               64U
#define PTFDS_PTFDS7_MASK               128U


/*** PTFIFE - Port F Input Filter Enable Register; 0xFFFF9867 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFIFE0     :1;                                       /* Port F Input Filter Enable Bit 0 */
    byte PTFIFE1     :1;                                       /* Port F Input Filter Enable Bit 1 */
    byte PTFIFE2     :1;                                       /* Port F Input Filter Enable Bit 2 */
    byte PTFIFE3     :1;                                       /* Port F Input Filter Enable Bit 3 */
    byte PTFIFE4     :1;                                       /* Port F Input Filter Enable Bit 4 */
    byte PTFIFE5     :1;                                       /* Port F Input Filter Enable Bit 5 */
    byte PTFIFE6     :1;                                       /* Port F Input Filter Enable Bit 6 */
    byte PTFIFE7     :1;                                       /* Port F Input Filter Enable Bit 7 */
  } Bits;
} PTFIFESTR;
extern volatile PTFIFESTR _PTFIFE @0xFFFF9867;
#define PTFIFE                          _PTFIFE.Byte
#define PTFIFE_PTFIFE0                  _PTFIFE.Bits.PTFIFE0
#define PTFIFE_PTFIFE1                  _PTFIFE.Bits.PTFIFE1
#define PTFIFE_PTFIFE2                  _PTFIFE.Bits.PTFIFE2
#define PTFIFE_PTFIFE3                  _PTFIFE.Bits.PTFIFE3
#define PTFIFE_PTFIFE4                  _PTFIFE.Bits.PTFIFE4
#define PTFIFE_PTFIFE5                  _PTFIFE.Bits.PTFIFE5
#define PTFIFE_PTFIFE6                  _PTFIFE.Bits.PTFIFE6
#define PTFIFE_PTFIFE7                  _PTFIFE.Bits.PTFIFE7

#define PTFIFE_PTFIFE0_MASK             1U
#define PTFIFE_PTFIFE1_MASK             2U
#define PTFIFE_PTFIFE2_MASK             4U
#define PTFIFE_PTFIFE3_MASK             8U
#define PTFIFE_PTFIFE4_MASK             16U
#define PTFIFE_PTFIFE5_MASK             32U
#define PTFIFE_PTFIFE6_MASK             64U
#define PTFIFE_PTFIFE7_MASK             128U


/*** PTGPE - Port G Pull Enable Register; 0xFFFF9868 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGPE0      :1;                                       /* Internal Pull Enable for Port G Bit 0 */
    byte PTGPE1      :1;                                       /* Internal Pull Enable for Port G Bit 1 */
    byte PTGPE2      :1;                                       /* Internal Pull Enable for Port G Bit 2 */
    byte PTGPE3      :1;                                       /* Internal Pull Enable for Port G Bit 3 */
    byte PTGPE4      :1;                                       /* Internal Pull Enable for Port G Bit 4 */
    byte PTGPE5      :1;                                       /* Internal Pull Enable for Port G Bit 5 */
    byte PTGPE6      :1;                                       /* Internal Pull Enable for Port G Bit 6 */
    byte PTGPE7      :1;                                       /* Internal Pull Enable for Port G Bit 7 */
  } Bits;
} PTGPESTR;
extern volatile PTGPESTR _PTGPE @0xFFFF9868;
#define PTGPE                           _PTGPE.Byte
#define PTGPE_PTGPE0                    _PTGPE.Bits.PTGPE0
#define PTGPE_PTGPE1                    _PTGPE.Bits.PTGPE1
#define PTGPE_PTGPE2                    _PTGPE.Bits.PTGPE2
#define PTGPE_PTGPE3                    _PTGPE.Bits.PTGPE3
#define PTGPE_PTGPE4                    _PTGPE.Bits.PTGPE4
#define PTGPE_PTGPE5                    _PTGPE.Bits.PTGPE5
#define PTGPE_PTGPE6                    _PTGPE.Bits.PTGPE6
#define PTGPE_PTGPE7                    _PTGPE.Bits.PTGPE7

#define PTGPE_PTGPE0_MASK               1U
#define PTGPE_PTGPE1_MASK               2U
#define PTGPE_PTGPE2_MASK               4U
#define PTGPE_PTGPE3_MASK               8U
#define PTGPE_PTGPE4_MASK               16U
#define PTGPE_PTGPE5_MASK               32U
#define PTGPE_PTGPE6_MASK               64U
#define PTGPE_PTGPE7_MASK               128U


/*** PTGSE - Port G Slew Rate Enable Register; 0xFFFF9869 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGSE0      :1;                                       /* Output Slew Rate Enable for Port G Bit 0 */
    byte PTGSE1      :1;                                       /* Output Slew Rate Enable for Port G Bit 1 */
    byte PTGSE2      :1;                                       /* Output Slew Rate Enable for Port G Bit 2 */
    byte PTGSE3      :1;                                       /* Output Slew Rate Enable for Port G Bit 3 */
    byte PTGSE4      :1;                                       /* Output Slew Rate Enable for Port G Bit 4 */
    byte PTGSE5      :1;                                       /* Output Slew Rate Enable for Port G Bit 5 */
    byte PTGSE6      :1;                                       /* Output Slew Rate Enable for Port G Bit 6 */
    byte PTGSE7      :1;                                       /* Output Slew Rate Enable for Port G Bit 7 */
  } Bits;
} PTGSESTR;
extern volatile PTGSESTR _PTGSE @0xFFFF9869;
#define PTGSE                           _PTGSE.Byte
#define PTGSE_PTGSE0                    _PTGSE.Bits.PTGSE0
#define PTGSE_PTGSE1                    _PTGSE.Bits.PTGSE1
#define PTGSE_PTGSE2                    _PTGSE.Bits.PTGSE2
#define PTGSE_PTGSE3                    _PTGSE.Bits.PTGSE3
#define PTGSE_PTGSE4                    _PTGSE.Bits.PTGSE4
#define PTGSE_PTGSE5                    _PTGSE.Bits.PTGSE5
#define PTGSE_PTGSE6                    _PTGSE.Bits.PTGSE6
#define PTGSE_PTGSE7                    _PTGSE.Bits.PTGSE7

#define PTGSE_PTGSE0_MASK               1U
#define PTGSE_PTGSE1_MASK               2U
#define PTGSE_PTGSE2_MASK               4U
#define PTGSE_PTGSE3_MASK               8U
#define PTGSE_PTGSE4_MASK               16U
#define PTGSE_PTGSE5_MASK               32U
#define PTGSE_PTGSE6_MASK               64U
#define PTGSE_PTGSE7_MASK               128U


/*** PTGDS - Port G Drive Strength Selection Register; 0xFFFF986A ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDS0      :1;                                       /* Output Drive Strength Selection for Port G Bit 0 */
    byte PTGDS1      :1;                                       /* Output Drive Strength Selection for Port G Bit 1 */
    byte PTGDS2      :1;                                       /* Output Drive Strength Selection for Port G Bit 2 */
    byte PTGDS3      :1;                                       /* Output Drive Strength Selection for Port G Bit 3 */
    byte PTGDS4      :1;                                       /* Output Drive Strength Selection for Port G Bit 4 */
    byte PTGDS5      :1;                                       /* Output Drive Strength Selection for Port G Bit 5 */
    byte PTGDS6      :1;                                       /* Output Drive Strength Selection for Port G Bit 6 */
    byte PTGDS7      :1;                                       /* Output Drive Strength Selection for Port G Bit 7 */
  } Bits;
} PTGDSSTR;
extern volatile PTGDSSTR _PTGDS @0xFFFF986A;
#define PTGDS                           _PTGDS.Byte
#define PTGDS_PTGDS0                    _PTGDS.Bits.PTGDS0
#define PTGDS_PTGDS1                    _PTGDS.Bits.PTGDS1
#define PTGDS_PTGDS2                    _PTGDS.Bits.PTGDS2
#define PTGDS_PTGDS3                    _PTGDS.Bits.PTGDS3
#define PTGDS_PTGDS4                    _PTGDS.Bits.PTGDS4
#define PTGDS_PTGDS5                    _PTGDS.Bits.PTGDS5
#define PTGDS_PTGDS6                    _PTGDS.Bits.PTGDS6
#define PTGDS_PTGDS7                    _PTGDS.Bits.PTGDS7

#define PTGDS_PTGDS0_MASK               1U
#define PTGDS_PTGDS1_MASK               2U
#define PTGDS_PTGDS2_MASK               4U
#define PTGDS_PTGDS3_MASK               8U
#define PTGDS_PTGDS4_MASK               16U
#define PTGDS_PTGDS5_MASK               32U
#define PTGDS_PTGDS6_MASK               64U
#define PTGDS_PTGDS7_MASK               128U


/*** PTGIFE - Port G Input Filter Enable Register; 0xFFFF986B ***/
typedef union {
  byte Byte;
  struct {
    byte PTGIFE0     :1;                                       /* Port G Input Filter Enable Bit 0 */
    byte PTGIFE1     :1;                                       /* Port G Input Filter Enable Bit 1 */
    byte PTGIFE2     :1;                                       /* Port G Input Filter Enable Bit 2 */
    byte PTGIFE3     :1;                                       /* Port G Input Filter Enable Bit 3 */
    byte PTGIFE4     :1;                                       /* Port G Input Filter Enable Bit 4 */
    byte PTGIFE5     :1;                                       /* Port G Input Filter Enable Bit 5 */
    byte PTGIFE6     :1;                                       /* Port G Input Filter Enable Bit 6 */
    byte PTGIFE7     :1;                                       /* Port G Input Filter Enable Bit 7 */
  } Bits;
} PTGIFESTR;
extern volatile PTGIFESTR _PTGIFE @0xFFFF986B;
#define PTGIFE                          _PTGIFE.Byte
#define PTGIFE_PTGIFE0                  _PTGIFE.Bits.PTGIFE0
#define PTGIFE_PTGIFE1                  _PTGIFE.Bits.PTGIFE1
#define PTGIFE_PTGIFE2                  _PTGIFE.Bits.PTGIFE2
#define PTGIFE_PTGIFE3                  _PTGIFE.Bits.PTGIFE3
#define PTGIFE_PTGIFE4                  _PTGIFE.Bits.PTGIFE4
#define PTGIFE_PTGIFE5                  _PTGIFE.Bits.PTGIFE5
#define PTGIFE_PTGIFE6                  _PTGIFE.Bits.PTGIFE6
#define PTGIFE_PTGIFE7                  _PTGIFE.Bits.PTGIFE7

#define PTGIFE_PTGIFE0_MASK             1U
#define PTGIFE_PTGIFE1_MASK             2U
#define PTGIFE_PTGIFE2_MASK             4U
#define PTGIFE_PTGIFE3_MASK             8U
#define PTGIFE_PTGIFE4_MASK             16U
#define PTGIFE_PTGIFE5_MASK             32U
#define PTGIFE_PTGIFE6_MASK             64U
#define PTGIFE_PTGIFE7_MASK             128U


/*** CMTCG1 - Carrier Generator Data Register 1; 0xFFFF9870 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** CMTCGH1 - CMT Carrier Generator Data Register 1 High Byte; 0xFFFF9870 ***/
    union {
      byte Byte;
    } CMTCGH1STR;
    #define CMTCGH1                     _CMTCG1.Overlap_STR.CMTCGH1STR.Byte
    

    /*** CMTCGL1 - CMT Carrier Generator Data Register 1 Low Byte; 0xFFFF9871 ***/
    union {
      byte Byte;
    } CMTCGL1STR;
    #define CMTCGL1                     _CMTCG1.Overlap_STR.CMTCGL1STR.Byte
    
  } Overlap_STR;

  struct {
    word PL0         :1;                                       /* Primary Carrier Low Time Data Value Bit 0 */
    word PL1         :1;                                       /* Primary Carrier Low Time Data Value Bit 1 */
    word PL2         :1;                                       /* Primary Carrier Low Time Data Value Bit 2 */
    word PL3         :1;                                       /* Primary Carrier Low Time Data Value Bit 3 */
    word PL4         :1;                                       /* Primary Carrier Low Time Data Value Bit 4 */
    word PL5         :1;                                       /* Primary Carrier Low Time Data Value Bit 5 */
    word PL6         :1;                                       /* Primary Carrier Low Time Data Value Bit 6 */
    word PL7         :1;                                       /* Primary Carrier Low Time Data Value Bit 0 */
    word PH0         :1;                                       /* Primary Carrier High Time Data Value Bit 0 */
    word PH1         :1;                                       /* Primary Carrier High Time Data Value Bit 1 */
    word PH2         :1;                                       /* Primary Carrier High Time Data Value Bit 2 */
    word PH3         :1;                                       /* Primary Carrier High Time Data Value Bit 3 */
    word PH4         :1;                                       /* Primary Carrier High Time Data Value Bit 4 */
    word PH5         :1;                                       /* Primary Carrier High Time Data Value Bit 5 */
    word PH6         :1;                                       /* Primary Carrier High Time Data Value Bit 6 */
    word PH7         :1;                                       /* Primary Carrier High Time Data Value Bit 7 */
  } Bits;
  struct {
    word grpPL   :8;
    word grpPH   :8;
  } MergedBits;
} CMTCG1STR;
extern volatile CMTCG1STR _CMTCG1 @0xFFFF9870;
#define CMTCG1                          _CMTCG1.Word
#define CMTCG1_PL0                      _CMTCG1.Bits.PL0
#define CMTCG1_PL1                      _CMTCG1.Bits.PL1
#define CMTCG1_PL2                      _CMTCG1.Bits.PL2
#define CMTCG1_PL3                      _CMTCG1.Bits.PL3
#define CMTCG1_PL4                      _CMTCG1.Bits.PL4
#define CMTCG1_PL5                      _CMTCG1.Bits.PL5
#define CMTCG1_PL6                      _CMTCG1.Bits.PL6
#define CMTCG1_PL7                      _CMTCG1.Bits.PL7
#define CMTCG1_PH0                      _CMTCG1.Bits.PH0
#define CMTCG1_PH1                      _CMTCG1.Bits.PH1
#define CMTCG1_PH2                      _CMTCG1.Bits.PH2
#define CMTCG1_PH3                      _CMTCG1.Bits.PH3
#define CMTCG1_PH4                      _CMTCG1.Bits.PH4
#define CMTCG1_PH5                      _CMTCG1.Bits.PH5
#define CMTCG1_PH6                      _CMTCG1.Bits.PH6
#define CMTCG1_PH7                      _CMTCG1.Bits.PH7
#define CMTCG1_PL                       _CMTCG1.MergedBits.grpPL
#define CMTCG1_PH                       _CMTCG1.MergedBits.grpPH

#define CMTCG1_PL0_MASK                 1U
#define CMTCG1_PL1_MASK                 2U
#define CMTCG1_PL2_MASK                 4U
#define CMTCG1_PL3_MASK                 8U
#define CMTCG1_PL4_MASK                 16U
#define CMTCG1_PL5_MASK                 32U
#define CMTCG1_PL6_MASK                 64U
#define CMTCG1_PL7_MASK                 128U
#define CMTCG1_PH0_MASK                 256U
#define CMTCG1_PH1_MASK                 512U
#define CMTCG1_PH2_MASK                 1024U
#define CMTCG1_PH3_MASK                 2048U
#define CMTCG1_PH4_MASK                 4096U
#define CMTCG1_PH5_MASK                 8192U
#define CMTCG1_PH6_MASK                 16384U
#define CMTCG1_PH7_MASK                 32768U
#define CMTCG1_PL_MASK                  255U
#define CMTCG1_PL_BITNUM                0U
#define CMTCG1_PH_MASK                  65280U
#define CMTCG1_PH_BITNUM                8U


/*** CMTCG2 - Carrier Generator Data Register 2; 0xFFFF9872 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** CMTCGH2 - CMT Carrier Generator Data Register 2 High Byte; 0xFFFF9872 ***/
    union {
      byte Byte;
    } CMTCGH2STR;
    #define CMTCGH2                     _CMTCG2.Overlap_STR.CMTCGH2STR.Byte
    

    /*** CMTCGL2 - CMT Carrier Generator Data Register 2 Low Byte; 0xFFFF9873 ***/
    union {
      byte Byte;
    } CMTCGL2STR;
    #define CMTCGL2                     _CMTCG2.Overlap_STR.CMTCGL2STR.Byte
    
  } Overlap_STR;

  struct {
    word SL0         :1;                                       /* Secondary Carrier Low Time Data Value Bit 0 */
    word SL1         :1;                                       /* Secondary Carrier Low Time Data Value Bit 1 */
    word SL2         :1;                                       /* Secondary Carrier Low Time Data Value Bit 2 */
    word SL3         :1;                                       /* Secondary Carrier Low Time Data Value Bit 3 */
    word SL4         :1;                                       /* Secondary Carrier Low Time Data Value Bit 4 */
    word SL5         :1;                                       /* Secondary Carrier Low Time Data Value Bit 5 */
    word SL6         :1;                                       /* Secondary Carrier Low Time Data Value Bit 6 */
    word SL7         :1;                                       /* Secondary Carrier Low Time Data Value Bit 7 */
    word SH0         :1;                                       /* Secondary Carrier High Time Data Value Bit 0 */
    word SH1         :1;                                       /* Secondary Carrier High Time Data Value Bit 1 */
    word SH2         :1;                                       /* Secondary Carrier High Time Data Value Bit 2 */
    word SH3         :1;                                       /* Secondary Carrier High Time Data Value Bit 3 */
    word SH4         :1;                                       /* Secondary Carrier High Time Data Value Bit 4 */
    word SH5         :1;                                       /* Secondary Carrier High Time Data Value Bit 5 */
    word SH6         :1;                                       /* Secondary Carrier High Time Data Value Bit 6 */
    word SH7         :1;                                       /* Secondary Carrier High Time Data Value Bit 7 */
  } Bits;
  struct {
    word grpSL   :8;
    word grpSH   :8;
  } MergedBits;
} CMTCG2STR;
extern volatile CMTCG2STR _CMTCG2 @0xFFFF9872;
#define CMTCG2                          _CMTCG2.Word
#define CMTCG2_SL0                      _CMTCG2.Bits.SL0
#define CMTCG2_SL1                      _CMTCG2.Bits.SL1
#define CMTCG2_SL2                      _CMTCG2.Bits.SL2
#define CMTCG2_SL3                      _CMTCG2.Bits.SL3
#define CMTCG2_SL4                      _CMTCG2.Bits.SL4
#define CMTCG2_SL5                      _CMTCG2.Bits.SL5
#define CMTCG2_SL6                      _CMTCG2.Bits.SL6
#define CMTCG2_SL7                      _CMTCG2.Bits.SL7
#define CMTCG2_SH0                      _CMTCG2.Bits.SH0
#define CMTCG2_SH1                      _CMTCG2.Bits.SH1
#define CMTCG2_SH2                      _CMTCG2.Bits.SH2
#define CMTCG2_SH3                      _CMTCG2.Bits.SH3
#define CMTCG2_SH4                      _CMTCG2.Bits.SH4
#define CMTCG2_SH5                      _CMTCG2.Bits.SH5
#define CMTCG2_SH6                      _CMTCG2.Bits.SH6
#define CMTCG2_SH7                      _CMTCG2.Bits.SH7
#define CMTCG2_SL                       _CMTCG2.MergedBits.grpSL
#define CMTCG2_SH                       _CMTCG2.MergedBits.grpSH

#define CMTCG2_SL0_MASK                 1U
#define CMTCG2_SL1_MASK                 2U
#define CMTCG2_SL2_MASK                 4U
#define CMTCG2_SL3_MASK                 8U
#define CMTCG2_SL4_MASK                 16U
#define CMTCG2_SL5_MASK                 32U
#define CMTCG2_SL6_MASK                 64U
#define CMTCG2_SL7_MASK                 128U
#define CMTCG2_SH0_MASK                 256U
#define CMTCG2_SH1_MASK                 512U
#define CMTCG2_SH2_MASK                 1024U
#define CMTCG2_SH3_MASK                 2048U
#define CMTCG2_SH4_MASK                 4096U
#define CMTCG2_SH5_MASK                 8192U
#define CMTCG2_SH6_MASK                 16384U
#define CMTCG2_SH7_MASK                 32768U
#define CMTCG2_SL_MASK                  255U
#define CMTCG2_SL_BITNUM                0U
#define CMTCG2_SH_MASK                  65280U
#define CMTCG2_SH_BITNUM                8U


/*** CMTOC - CMT Output Control Register; 0xFFFF9874 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte IROPEN      :1;                                       /* IRO pin enable */
    byte CMTPOL      :1;                                       /* CMT output polarity */
    byte IROL        :1;                                       /* IRO latch control */
  } Bits;
} CMTOCSTR;
extern volatile CMTOCSTR _CMTOC @0xFFFF9874;
#define CMTOC                           _CMTOC.Byte
#define CMTOC_IROPEN                    _CMTOC.Bits.IROPEN
#define CMTOC_CMTPOL                    _CMTOC.Bits.CMTPOL
#define CMTOC_IROL                      _CMTOC.Bits.IROL

#define CMTOC_IROPEN_MASK               32U
#define CMTOC_CMTPOL_MASK               64U
#define CMTOC_IROL_MASK                 128U


/*** CMTMSC - CMT Modulator Status and Control Register; 0xFFFF9875 ***/
typedef union {
  byte Byte;
  struct {
    byte MCGEN       :1;                                       /* Modulator and Carrier Generator Enable */
    byte EOCIE       :1;                                       /* End of Cycle Interrupt Enable */
    byte FSK         :1;                                       /* FSK Mode Select */
    byte BASE        :1;                                       /* Baseband Mode Enable */
    byte EXSPC       :1;                                       /* Extended Space Enable */
    byte CMTDIV0     :1;                                       /* CMT Clock Divide Prescaler Bit 0 */
    byte CMTDIV1     :1;                                       /* CMT Clock Divide Prescaler Bit 1 */
    byte EOCF        :1;                                       /* End of Cycle Status Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpCMTDIV :2;
    byte         :1;
  } MergedBits;
} CMTMSCSTR;
extern volatile CMTMSCSTR _CMTMSC @0xFFFF9875;
#define CMTMSC                          _CMTMSC.Byte
#define CMTMSC_MCGEN                    _CMTMSC.Bits.MCGEN
#define CMTMSC_EOCIE                    _CMTMSC.Bits.EOCIE
#define CMTMSC_FSK                      _CMTMSC.Bits.FSK
#define CMTMSC_BASE                     _CMTMSC.Bits.BASE
#define CMTMSC_EXSPC                    _CMTMSC.Bits.EXSPC
#define CMTMSC_CMTDIV0                  _CMTMSC.Bits.CMTDIV0
#define CMTMSC_CMTDIV1                  _CMTMSC.Bits.CMTDIV1
#define CMTMSC_EOCF                     _CMTMSC.Bits.EOCF
#define CMTMSC_CMTDIV                   _CMTMSC.MergedBits.grpCMTDIV

#define CMTMSC_MCGEN_MASK               1U
#define CMTMSC_EOCIE_MASK               2U
#define CMTMSC_FSK_MASK                 4U
#define CMTMSC_BASE_MASK                8U
#define CMTMSC_EXSPC_MASK               16U
#define CMTMSC_CMTDIV0_MASK             32U
#define CMTMSC_CMTDIV1_MASK             64U
#define CMTMSC_EOCF_MASK                128U
#define CMTMSC_CMTDIV_MASK              96U
#define CMTMSC_CMTDIV_BITNUM            5U


/*** CMTCMD12 - CMT Modulator Data Register 12; 0xFFFF9876 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** CMTCMD1 - CMT Modulator Data Register 1; 0xFFFF9876 ***/
    union {
      byte Byte;
    } CMTCMD1STR;
    #define CMTCMD1                     _CMTCMD12.Overlap_STR.CMTCMD1STR.Byte
    

    /*** CMTCMD2 - CMT Modulator Data Register 2; 0xFFFF9877 ***/
    union {
      byte Byte;
      struct {
        byte MB0         :1;                                       /* Data Value Bit 0 */
        byte MB1         :1;                                       /* Data Value Bit 1 */
        byte MB2         :1;                                       /* Data Value Bit 2 */
        byte MB3         :1;                                       /* Data Value Bit 3 */
        byte MB4         :1;                                       /* Data Value Bit 4 */
        byte MB5         :1;                                       /* Data Value Bit 5 */
        byte MB6         :1;                                       /* Data Value Bit 6 */
        byte MB7         :1;                                       /* Data Value Bit 7 */
      } Bits;
    } CMTCMD2STR;
    #define CMTCMD2                     _CMTCMD12.Overlap_STR.CMTCMD2STR.Byte
    #define CMTCMD2_MB0                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB0
    #define CMTCMD2_MB1                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB1
    #define CMTCMD2_MB2                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB2
    #define CMTCMD2_MB3                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB3
    #define CMTCMD2_MB4                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB4
    #define CMTCMD2_MB5                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB5
    #define CMTCMD2_MB6                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB6
    #define CMTCMD2_MB7                 _CMTCMD12.Overlap_STR.CMTCMD2STR.Bits.MB7
    
    #define CMTCMD2_MB0_MASK            1U
    #define CMTCMD2_MB1_MASK            2U
    #define CMTCMD2_MB2_MASK            4U
    #define CMTCMD2_MB3_MASK            8U
    #define CMTCMD2_MB4_MASK            16U
    #define CMTCMD2_MB5_MASK            32U
    #define CMTCMD2_MB6_MASK            64U
    #define CMTCMD2_MB7_MASK            128U
    
  } Overlap_STR;

  struct {
    word MB0         :1;                                       /* Data Value Bit 0 */
    word MB1         :1;                                       /* Data Value Bit 1 */
    word MB2         :1;                                       /* Data Value Bit 2 */
    word MB3         :1;                                       /* Data Value Bit 3 */
    word MB4         :1;                                       /* Data Value Bit 4 */
    word MB5         :1;                                       /* Data Value Bit 5 */
    word MB6         :1;                                       /* Data Value Bit 6 */
    word MB7         :1;                                       /* Data Value Bit 7 */
    word MB8         :1;                                       /* Data Value Bit 8 */
    word MB9         :1;                                       /* Data Value Bit 9 */
    word MB10        :1;                                       /* Data Value Bit 10 */
    word MB11        :1;                                       /* Data Value Bit 11 */
    word MB12        :1;                                       /* Data Value Bit 12 */
    word MB13        :1;                                       /* Data Value Bit 13 */
    word MB14        :1;                                       /* Data Value Bit 14 */
    word MB15        :1;                                       /* Data Value Bit 15 */
  } Bits;
} CMTCMD12STR;
extern volatile CMTCMD12STR _CMTCMD12 @0xFFFF9876;
#define CMTCMD12                        _CMTCMD12.Word
#define CMTCMD12_MB0                    _CMTCMD12.Bits.MB0
#define CMTCMD12_MB1                    _CMTCMD12.Bits.MB1
#define CMTCMD12_MB2                    _CMTCMD12.Bits.MB2
#define CMTCMD12_MB3                    _CMTCMD12.Bits.MB3
#define CMTCMD12_MB4                    _CMTCMD12.Bits.MB4
#define CMTCMD12_MB5                    _CMTCMD12.Bits.MB5
#define CMTCMD12_MB6                    _CMTCMD12.Bits.MB6
#define CMTCMD12_MB7                    _CMTCMD12.Bits.MB7
#define CMTCMD12_MB8                    _CMTCMD12.Bits.MB8
#define CMTCMD12_MB9                    _CMTCMD12.Bits.MB9
#define CMTCMD12_MB10                   _CMTCMD12.Bits.MB10
#define CMTCMD12_MB11                   _CMTCMD12.Bits.MB11
#define CMTCMD12_MB12                   _CMTCMD12.Bits.MB12
#define CMTCMD12_MB13                   _CMTCMD12.Bits.MB13
#define CMTCMD12_MB14                   _CMTCMD12.Bits.MB14
#define CMTCMD12_MB15                   _CMTCMD12.Bits.MB15

#define CMTCMD12_MB0_MASK               1U
#define CMTCMD12_MB1_MASK               2U
#define CMTCMD12_MB2_MASK               4U
#define CMTCMD12_MB3_MASK               8U
#define CMTCMD12_MB4_MASK               16U
#define CMTCMD12_MB5_MASK               32U
#define CMTCMD12_MB6_MASK               64U
#define CMTCMD12_MB7_MASK               128U
#define CMTCMD12_MB8_MASK               256U
#define CMTCMD12_MB9_MASK               512U
#define CMTCMD12_MB10_MASK              1024U
#define CMTCMD12_MB11_MASK              2048U
#define CMTCMD12_MB12_MASK              4096U
#define CMTCMD12_MB13_MASK              8192U
#define CMTCMD12_MB14_MASK              16384U
#define CMTCMD12_MB15_MASK              32768U


/*** CMTCMD34 - CMT Modulator Data Register 34; 0xFFFF9878 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** CMTCMD3 - CMT Modulator Data Register 3; 0xFFFF9878 ***/
    union {
      byte Byte;
    } CMTCMD3STR;
    #define CMTCMD3                     _CMTCMD34.Overlap_STR.CMTCMD3STR.Byte
    

    /*** CMTCMD4 - CMT Modulator Data Register 4; 0xFFFF9879 ***/
    union {
      byte Byte;
      struct {
        byte SB0         :1;                                       /* Data Value Bit 0 */
        byte SB1         :1;                                       /* Data Value Bit 1 */
        byte SB2         :1;                                       /* Data Value Bit 2 */
        byte SB3         :1;                                       /* Data Value Bit 3 */
        byte SB4         :1;                                       /* Data Value Bit 4 */
        byte SB5         :1;                                       /* Data Value Bit 5 */
        byte SB6         :1;                                       /* Data Value Bit 6 */
        byte SB7         :1;                                       /* Data Value Bit 7 */
      } Bits;
    } CMTCMD4STR;
    #define CMTCMD4                     _CMTCMD34.Overlap_STR.CMTCMD4STR.Byte
    #define CMTCMD4_SB0                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB0
    #define CMTCMD4_SB1                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB1
    #define CMTCMD4_SB2                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB2
    #define CMTCMD4_SB3                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB3
    #define CMTCMD4_SB4                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB4
    #define CMTCMD4_SB5                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB5
    #define CMTCMD4_SB6                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB6
    #define CMTCMD4_SB7                 _CMTCMD34.Overlap_STR.CMTCMD4STR.Bits.SB7
    
    #define CMTCMD4_SB0_MASK            1U
    #define CMTCMD4_SB1_MASK            2U
    #define CMTCMD4_SB2_MASK            4U
    #define CMTCMD4_SB3_MASK            8U
    #define CMTCMD4_SB4_MASK            16U
    #define CMTCMD4_SB5_MASK            32U
    #define CMTCMD4_SB6_MASK            64U
    #define CMTCMD4_SB7_MASK            128U
    
  } Overlap_STR;

  struct {
    word SB0         :1;                                       /* Data Value Bit 0 */
    word SB1         :1;                                       /* Data Value Bit 1 */
    word SB2         :1;                                       /* Data Value Bit 2 */
    word SB3         :1;                                       /* Data Value Bit 3 */
    word SB4         :1;                                       /* Data Value Bit 4 */
    word SB5         :1;                                       /* Data Value Bit 5 */
    word SB6         :1;                                       /* Data Value Bit 6 */
    word SB7         :1;                                       /* Data Value Bit 7 */
    word SB8         :1;                                       /* Data Value Bit 8 */
    word SB9         :1;                                       /* Data Value Bit 9 */
    word SB10        :1;                                       /* Data Value Bit 10 */
    word SB11        :1;                                       /* Data Value Bit 11 */
    word SB12        :1;                                       /* Data Value Bit 12 */
    word SB13        :1;                                       /* Data Value Bit 13 */
    word SB14        :1;                                       /* Data Value Bit 14 */
    word SB15        :1;                                       /* Data Value Bit 15 */
  } Bits;
} CMTCMD34STR;
extern volatile CMTCMD34STR _CMTCMD34 @0xFFFF9878;
#define CMTCMD34                        _CMTCMD34.Word
#define CMTCMD34_SB0                    _CMTCMD34.Bits.SB0
#define CMTCMD34_SB1                    _CMTCMD34.Bits.SB1
#define CMTCMD34_SB2                    _CMTCMD34.Bits.SB2
#define CMTCMD34_SB3                    _CMTCMD34.Bits.SB3
#define CMTCMD34_SB4                    _CMTCMD34.Bits.SB4
#define CMTCMD34_SB5                    _CMTCMD34.Bits.SB5
#define CMTCMD34_SB6                    _CMTCMD34.Bits.SB6
#define CMTCMD34_SB7                    _CMTCMD34.Bits.SB7
#define CMTCMD34_SB8                    _CMTCMD34.Bits.SB8
#define CMTCMD34_SB9                    _CMTCMD34.Bits.SB9
#define CMTCMD34_SB10                   _CMTCMD34.Bits.SB10
#define CMTCMD34_SB11                   _CMTCMD34.Bits.SB11
#define CMTCMD34_SB12                   _CMTCMD34.Bits.SB12
#define CMTCMD34_SB13                   _CMTCMD34.Bits.SB13
#define CMTCMD34_SB14                   _CMTCMD34.Bits.SB14
#define CMTCMD34_SB15                   _CMTCMD34.Bits.SB15

#define CMTCMD34_SB0_MASK               1U
#define CMTCMD34_SB1_MASK               2U
#define CMTCMD34_SB2_MASK               4U
#define CMTCMD34_SB3_MASK               8U
#define CMTCMD34_SB4_MASK               16U
#define CMTCMD34_SB5_MASK               32U
#define CMTCMD34_SB6_MASK               64U
#define CMTCMD34_SB7_MASK               128U
#define CMTCMD34_SB8_MASK               256U
#define CMTCMD34_SB9_MASK               512U
#define CMTCMD34_SB10_MASK              1024U
#define CMTCMD34_SB11_MASK              2048U
#define CMTCMD34_SB12_MASK              4096U
#define CMTCMD34_SB13_MASK              8192U
#define CMTCMD34_SB14_MASK              16384U
#define CMTCMD34_SB15_MASK              32768U


/*** CRCH - CRC High Register; 0xFFFF9890 ***/
typedef union {
  byte Byte;
  struct {
    byte BIT8        :1;                                       /* High byte of CRC register ,bit 8 */
    byte BIT9        :1;                                       /* High byte of CRC register ,bit 9 */
    byte BIT10       :1;                                       /* High byte of CRC register ,bit 10 */
    byte BIT11       :1;                                       /* High byte of CRC register ,bit 11 */
    byte BIT12       :1;                                       /* High byte of CRC register ,bit 12 */
    byte BIT13       :1;                                       /* High byte of CRC register ,bit 13 */
    byte BIT14       :1;                                       /* High byte of CRC register ,bit 14 */
    byte BIT15       :1;                                       /* High byte of CRC register ,bit 15 */
  } Bits;
} CRCHSTR;
extern volatile CRCHSTR _CRCH @0xFFFF9890;
#define CRCH                            _CRCH.Byte
#define CRCH_BIT8                       _CRCH.Bits.BIT8
#define CRCH_BIT9                       _CRCH.Bits.BIT9
#define CRCH_BIT10                      _CRCH.Bits.BIT10
#define CRCH_BIT11                      _CRCH.Bits.BIT11
#define CRCH_BIT12                      _CRCH.Bits.BIT12
#define CRCH_BIT13                      _CRCH.Bits.BIT13
#define CRCH_BIT14                      _CRCH.Bits.BIT14
#define CRCH_BIT15                      _CRCH.Bits.BIT15

#define CRCH_BIT8_MASK                  1U
#define CRCH_BIT9_MASK                  2U
#define CRCH_BIT10_MASK                 4U
#define CRCH_BIT11_MASK                 8U
#define CRCH_BIT12_MASK                 16U
#define CRCH_BIT13_MASK                 32U
#define CRCH_BIT14_MASK                 64U
#define CRCH_BIT15_MASK                 128U


/*** CRCL - CRC Low Register; 0xFFFF9891 ***/
typedef union {
  byte Byte;
  struct {
    byte BIT0        :1;                                       /* Low byte of CRC register, bit 0 */
    byte BIT1        :1;                                       /* Low byte of CRC register, bit 1 */
    byte BIT2        :1;                                       /* Low byte of CRC register, bit 2 */
    byte BIT3        :1;                                       /* Low byte of CRC register, bit 3 */
    byte BIT4        :1;                                       /* Low byte of CRC register, bit 4 */
    byte BIT5        :1;                                       /* Low byte of CRC register, bit 5 */
    byte BIT6        :1;                                       /* Low byte of CRC register, bit 6 */
    byte BIT7        :1;                                       /* Low byte of CRC register, bit 7 */
  } Bits;
} CRCLSTR;
extern volatile CRCLSTR _CRCL @0xFFFF9891;
#define CRCL                            _CRCL.Byte
#define CRCL_BIT0                       _CRCL.Bits.BIT0
#define CRCL_BIT1                       _CRCL.Bits.BIT1
#define CRCL_BIT2                       _CRCL.Bits.BIT2
#define CRCL_BIT3                       _CRCL.Bits.BIT3
#define CRCL_BIT4                       _CRCL.Bits.BIT4
#define CRCL_BIT5                       _CRCL.Bits.BIT5
#define CRCL_BIT6                       _CRCL.Bits.BIT6
#define CRCL_BIT7                       _CRCL.Bits.BIT7

#define CRCL_BIT0_MASK                  1U
#define CRCL_BIT1_MASK                  2U
#define CRCL_BIT2_MASK                  4U
#define CRCL_BIT3_MASK                  8U
#define CRCL_BIT4_MASK                  16U
#define CRCL_BIT5_MASK                  32U
#define CRCL_BIT6_MASK                  64U
#define CRCL_BIT7_MASK                  128U


/*** TRANSPOSE - CRC Transpose Register; 0xFFFF9892 ***/
typedef union {
  byte Byte;
  struct {
    byte BIT0        :1;                                       /* CRC transpose register, bit 0 */
    byte BIT1        :1;                                       /* CRC transpose register, bit 1 */
    byte BIT2        :1;                                       /* CRC transpose register, bit 2 */
    byte BIT3        :1;                                       /* CRC transpose register, bit 3 */
    byte BIT4        :1;                                       /* CRC transpose register, bit 4 */
    byte BIT5        :1;                                       /* CRC transpose register, bit 5 */
    byte BIT6        :1;                                       /* CRC transpose register, bit 6 */
    byte BIT7        :1;                                       /* CRC transpose register, bit 7 */
  } Bits;
} TRANSPOSESTR;
extern volatile TRANSPOSESTR _TRANSPOSE @0xFFFF9892;
#define TRANSPOSE                       _TRANSPOSE.Byte
#define TRANSPOSE_BIT0                  _TRANSPOSE.Bits.BIT0
#define TRANSPOSE_BIT1                  _TRANSPOSE.Bits.BIT1
#define TRANSPOSE_BIT2                  _TRANSPOSE.Bits.BIT2
#define TRANSPOSE_BIT3                  _TRANSPOSE.Bits.BIT3
#define TRANSPOSE_BIT4                  _TRANSPOSE.Bits.BIT4
#define TRANSPOSE_BIT5                  _TRANSPOSE.Bits.BIT5
#define TRANSPOSE_BIT6                  _TRANSPOSE.Bits.BIT6
#define TRANSPOSE_BIT7                  _TRANSPOSE.Bits.BIT7

#define TRANSPOSE_BIT0_MASK             1U
#define TRANSPOSE_BIT1_MASK             2U
#define TRANSPOSE_BIT2_MASK             4U
#define TRANSPOSE_BIT3_MASK             8U
#define TRANSPOSE_BIT4_MASK             16U
#define TRANSPOSE_BIT5_MASK             32U
#define TRANSPOSE_BIT6_MASK             64U
#define TRANSPOSE_BIT7_MASK             128U


/*** TODC - TOD Control Register; 0xFFFF989C ***/
typedef union {
  byte Byte;
  struct {
    byte TODPS0      :1;                                       /* TOD Prescaler Bits, bit 0 */
    byte TODPS1      :1;                                       /* TOD Prescaler Bits, bit 1 */
    byte TODPS2      :1;                                       /* TOD Prescaler Bits, bit 2 */
    byte TODCLKEN    :1;                                       /* TOD Clock Enable */
    byte TODR        :1;                                       /* TOD Reset */
    byte TODCLKS0    :1;                                       /* TOD Clock Source, bit 0 */
    byte TODCLKS1    :1;                                       /* TOD Clock Source, bit 1 */
    byte TODEN       :1;                                       /* Time of Day Enable */
  } Bits;
  struct {
    byte grpTODPS :3;
    byte         :1;
    byte         :1;
    byte grpTODCLKS :2;
    byte         :1;
  } MergedBits;
} TODCSTR;
extern volatile TODCSTR _TODC @0xFFFF989C;
#define TODC                            _TODC.Byte
#define TODC_TODPS0                     _TODC.Bits.TODPS0
#define TODC_TODPS1                     _TODC.Bits.TODPS1
#define TODC_TODPS2                     _TODC.Bits.TODPS2
#define TODC_TODCLKEN                   _TODC.Bits.TODCLKEN
#define TODC_TODR                       _TODC.Bits.TODR
#define TODC_TODCLKS0                   _TODC.Bits.TODCLKS0
#define TODC_TODCLKS1                   _TODC.Bits.TODCLKS1
#define TODC_TODEN                      _TODC.Bits.TODEN
#define TODC_TODPS                      _TODC.MergedBits.grpTODPS
#define TODC_TODCLKS                    _TODC.MergedBits.grpTODCLKS

#define TODC_TODPS0_MASK                1U
#define TODC_TODPS1_MASK                2U
#define TODC_TODPS2_MASK                4U
#define TODC_TODCLKEN_MASK              8U
#define TODC_TODR_MASK                  16U
#define TODC_TODCLKS0_MASK              32U
#define TODC_TODCLKS1_MASK              64U
#define TODC_TODEN_MASK                 128U
#define TODC_TODPS_MASK                 7U
#define TODC_TODPS_BITNUM               0U
#define TODC_TODCLKS_MASK               96U
#define TODC_TODCLKS_BITNUM             5U


/*** TODSC - TOD Status and Control Register; 0xFFFF989D ***/
typedef union {
  byte Byte;
  struct {
    byte MTCHWC      :1;                                       /* Match Write Complete */
    byte MTCHEN      :1;                                       /* Match Function Enable */
    byte MTCHIE      :1;                                       /* Match Interrupt Enable */
    byte SECIE       :1;                                       /* Second Interrupt Enable */
    byte QSECIE      :1;                                       /* Quarter-Second Interrupt Enable */
    byte MTCHF       :1;                                       /* Match Interrupt Flag */
    byte SECF        :1;                                       /* Second Interrupt Flag */
    byte QSECF       :1;                                       /* Quarter-Second Interrupt Flag */
  } Bits;
} TODSCSTR;
extern volatile TODSCSTR _TODSC @0xFFFF989D;
#define TODSC                           _TODSC.Byte
#define TODSC_MTCHWC                    _TODSC.Bits.MTCHWC
#define TODSC_MTCHEN                    _TODSC.Bits.MTCHEN
#define TODSC_MTCHIE                    _TODSC.Bits.MTCHIE
#define TODSC_SECIE                     _TODSC.Bits.SECIE
#define TODSC_QSECIE                    _TODSC.Bits.QSECIE
#define TODSC_MTCHF                     _TODSC.Bits.MTCHF
#define TODSC_SECF                      _TODSC.Bits.SECF
#define TODSC_QSECF                     _TODSC.Bits.QSECF

#define TODSC_MTCHWC_MASK               1U
#define TODSC_MTCHEN_MASK               2U
#define TODSC_MTCHIE_MASK               4U
#define TODSC_SECIE_MASK                8U
#define TODSC_QSECIE_MASK               16U
#define TODSC_MTCHF_MASK                32U
#define TODSC_SECF_MASK                 64U
#define TODSC_QSECF_MASK                128U


/*** TODM - TOD Match Register; 0xFFFF989E ***/
typedef union {
  byte Byte;
  struct {
    byte MQSEC0      :1;                                       /* Match Quarter-Second Bits, bit 0 */
    byte MQSEC1      :1;                                       /* Match Quarter-Second Bits, bit 1 */
    byte TODM0       :1;                                       /* TOD Match Value, bit 0 */
    byte TODM1       :1;                                       /* TOD Match Value, bit 1 */
    byte TODM2       :1;                                       /* TOD Match Value, bit 2 */
    byte TODM3       :1;                                       /* TOD Match Value, bit 3 */
    byte TODM4       :1;                                       /* TOD Match Value, bit 4 */
    byte TODM5       :1;                                       /* TOD Match Value, bit 5 */
  } Bits;
  struct {
    byte grpMQSEC :2;
    byte grpTODM :6;
  } MergedBits;
} TODMSTR;
extern volatile TODMSTR _TODM @0xFFFF989E;
#define TODM                            _TODM.Byte
#define TODM_MQSEC0                     _TODM.Bits.MQSEC0
#define TODM_MQSEC1                     _TODM.Bits.MQSEC1
#define TODM_TODM0                      _TODM.Bits.TODM0
#define TODM_TODM1                      _TODM.Bits.TODM1
#define TODM_TODM2                      _TODM.Bits.TODM2
#define TODM_TODM3                      _TODM.Bits.TODM3
#define TODM_TODM4                      _TODM.Bits.TODM4
#define TODM_TODM5                      _TODM.Bits.TODM5
#define TODM_MQSEC                      _TODM.MergedBits.grpMQSEC
#define TODM_TODM                       _TODM.MergedBits.grpTODM

#define TODM_MQSEC0_MASK                1U
#define TODM_MQSEC1_MASK                2U
#define TODM_TODM0_MASK                 4U
#define TODM_TODM1_MASK                 8U
#define TODM_TODM2_MASK                 16U
#define TODM_TODM3_MASK                 32U
#define TODM_TODM4_MASK                 64U
#define TODM_TODM5_MASK                 128U
#define TODM_MQSEC_MASK                 3U
#define TODM_MQSEC_BITNUM               0U
#define TODM_TODM_MASK                  252U
#define TODM_TODM_BITNUM                2U


/*** TODCNT - TOD Counter Register; 0xFFFF989F ***/
typedef union {
  byte Byte;
} TODCNTSTR;
extern volatile TODCNTSTR _TODCNT @0xFFFF989F;
#define TODCNT                          _TODCNT.Byte


/*** TPM2SC - TPM2 Status and Control Register; 0xFFFF98A0 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2SCSTR;
extern volatile TPM2SCSTR _TPM2SC @0xFFFF98A0;
#define TPM2SC                          _TPM2SC.Byte
#define TPM2SC_PS0                      _TPM2SC.Bits.PS0
#define TPM2SC_PS1                      _TPM2SC.Bits.PS1
#define TPM2SC_PS2                      _TPM2SC.Bits.PS2
#define TPM2SC_CLKSA                    _TPM2SC.Bits.CLKSA
#define TPM2SC_CLKSB                    _TPM2SC.Bits.CLKSB
#define TPM2SC_CPWMS                    _TPM2SC.Bits.CPWMS
#define TPM2SC_TOIE                     _TPM2SC.Bits.TOIE
#define TPM2SC_TOF                      _TPM2SC.Bits.TOF
#define TPM2SC_PS                       _TPM2SC.MergedBits.grpPS
#define TPM2SC_CLKSx                    _TPM2SC.MergedBits.grpCLKSx

#define TPM2SC_PS0_MASK                 1U
#define TPM2SC_PS1_MASK                 2U
#define TPM2SC_PS2_MASK                 4U
#define TPM2SC_CLKSA_MASK               8U
#define TPM2SC_CLKSB_MASK               16U
#define TPM2SC_CPWMS_MASK               32U
#define TPM2SC_TOIE_MASK                64U
#define TPM2SC_TOF_MASK                 128U
#define TPM2SC_PS_MASK                  7U
#define TPM2SC_PS_BITNUM                0U
#define TPM2SC_CLKSx_MASK               24U
#define TPM2SC_CLKSx_BITNUM             3U


/*** TPM2CNT - TPM2 Timer Counter Register; 0xFFFF98A1 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2CNTH - TPM2 Timer Counter Register High; 0xFFFF98A1 ***/
    union {
      byte Byte;
    } TPM2CNTHSTR;
    #define TPM2CNTH                    _TPM2CNT.Overlap_STR.TPM2CNTHSTR.Byte
    

    /*** TPM2CNTL - TPM2 Timer Counter Register Low; 0xFFFF98A2 ***/
    union {
      byte Byte;
    } TPM2CNTLSTR;
    #define TPM2CNTL                    _TPM2CNT.Overlap_STR.TPM2CNTLSTR.Byte
    
  } Overlap_STR;

} TPM2CNTSTR;
extern volatile TPM2CNTSTR _TPM2CNT @0xFFFF98A1;
#define TPM2CNT                         _TPM2CNT.Word


/*** TPM2MOD - TPM2 Timer Counter Modulo Register; 0xFFFF98A3 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2MODH - TPM2 Timer Counter Modulo Register High; 0xFFFF98A3 ***/
    union {
      byte Byte;
    } TPM2MODHSTR;
    #define TPM2MODH                    _TPM2MOD.Overlap_STR.TPM2MODHSTR.Byte
    

    /*** TPM2MODL - TPM2 Timer Counter Modulo Register Low; 0xFFFF98A4 ***/
    union {
      byte Byte;
    } TPM2MODLSTR;
    #define TPM2MODL                    _TPM2MOD.Overlap_STR.TPM2MODLSTR.Byte
    
  } Overlap_STR;

} TPM2MODSTR;
extern volatile TPM2MODSTR _TPM2MOD @0xFFFF98A3;
#define TPM2MOD                         _TPM2MOD.Word


/*** TPM2C0SC - TPM2 Timer Channel 0 Status and Control Register; 0xFFFF98A5 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C0SCSTR;
extern volatile TPM2C0SCSTR _TPM2C0SC @0xFFFF98A5;
#define TPM2C0SC                        _TPM2C0SC.Byte
#define TPM2C0SC_ELS0A                  _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELS0B                  _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MS0A                   _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MS0B                   _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CH0IE                  _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CH0F                   _TPM2C0SC.Bits.CH0F
#define TPM2C0SC_ELS0x                  _TPM2C0SC.MergedBits.grpELS0x
#define TPM2C0SC_MS0x                   _TPM2C0SC.MergedBits.grpMS0x

#define TPM2C0SC_ELS0A_MASK             4U
#define TPM2C0SC_ELS0B_MASK             8U
#define TPM2C0SC_MS0A_MASK              16U
#define TPM2C0SC_MS0B_MASK              32U
#define TPM2C0SC_CH0IE_MASK             64U
#define TPM2C0SC_CH0F_MASK              128U
#define TPM2C0SC_ELS0x_MASK             12U
#define TPM2C0SC_ELS0x_BITNUM           2U
#define TPM2C0SC_MS0x_MASK              48U
#define TPM2C0SC_MS0x_BITNUM            4U


/*** TPM2C0V - TPM2 Timer Channel 0 Value Register; 0xFFFF98A6 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C0VH - TPM2 Timer Channel 0 Value Register High; 0xFFFF98A6 ***/
    union {
      byte Byte;
    } TPM2C0VHSTR;
    #define TPM2C0VH                    _TPM2C0V.Overlap_STR.TPM2C0VHSTR.Byte
    

    /*** TPM2C0VL - TPM2 Timer Channel 0 Value Register Low; 0xFFFF98A7 ***/
    union {
      byte Byte;
    } TPM2C0VLSTR;
    #define TPM2C0VL                    _TPM2C0V.Overlap_STR.TPM2C0VLSTR.Byte
    
  } Overlap_STR;

} TPM2C0VSTR;
extern volatile TPM2C0VSTR _TPM2C0V @0xFFFF98A6;
#define TPM2C0V                         _TPM2C0V.Word


/*** TPM2C1SC - TPM2 Timer Channel 1 Status and Control Register; 0xFFFF98A8 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C1SCSTR;
extern volatile TPM2C1SCSTR _TPM2C1SC @0xFFFF98A8;
#define TPM2C1SC                        _TPM2C1SC.Byte
#define TPM2C1SC_ELS1A                  _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELS1B                  _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MS1A                   _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MS1B                   _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CH1IE                  _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CH1F                   _TPM2C1SC.Bits.CH1F
#define TPM2C1SC_ELS1x                  _TPM2C1SC.MergedBits.grpELS1x
#define TPM2C1SC_MS1x                   _TPM2C1SC.MergedBits.grpMS1x

#define TPM2C1SC_ELS1A_MASK             4U
#define TPM2C1SC_ELS1B_MASK             8U
#define TPM2C1SC_MS1A_MASK              16U
#define TPM2C1SC_MS1B_MASK              32U
#define TPM2C1SC_CH1IE_MASK             64U
#define TPM2C1SC_CH1F_MASK              128U
#define TPM2C1SC_ELS1x_MASK             12U
#define TPM2C1SC_ELS1x_BITNUM           2U
#define TPM2C1SC_MS1x_MASK              48U
#define TPM2C1SC_MS1x_BITNUM            4U


/*** TPM2C1V - TPM2 Timer Channel 1 Value Register; 0xFFFF98A9 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C1VH - TPM2 Timer Channel 1 Value Register High; 0xFFFF98A9 ***/
    union {
      byte Byte;
    } TPM2C1VHSTR;
    #define TPM2C1VH                    _TPM2C1V.Overlap_STR.TPM2C1VHSTR.Byte
    

    /*** TPM2C1VL - TPM2 Timer Channel 1 Value Register Low; 0xFFFF98AA ***/
    union {
      byte Byte;
    } TPM2C1VLSTR;
    #define TPM2C1VL                    _TPM2C1V.Overlap_STR.TPM2C1VLSTR.Byte
    
  } Overlap_STR;

} TPM2C1VSTR;
extern volatile TPM2C1VSTR _TPM2C1V @0xFFFF98A9;
#define TPM2C1V                         _TPM2C1V.Word


/*** TPM2C2SC - TPM2 Timer Channel 2 Status and Control Register; 0xFFFF98AB ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C2SCSTR;
extern volatile TPM2C2SCSTR _TPM2C2SC @0xFFFF98AB;
#define TPM2C2SC                        _TPM2C2SC.Byte
#define TPM2C2SC_ELS2A                  _TPM2C2SC.Bits.ELS2A
#define TPM2C2SC_ELS2B                  _TPM2C2SC.Bits.ELS2B
#define TPM2C2SC_MS2A                   _TPM2C2SC.Bits.MS2A
#define TPM2C2SC_MS2B                   _TPM2C2SC.Bits.MS2B
#define TPM2C2SC_CH2IE                  _TPM2C2SC.Bits.CH2IE
#define TPM2C2SC_CH2F                   _TPM2C2SC.Bits.CH2F
#define TPM2C2SC_ELS2x                  _TPM2C2SC.MergedBits.grpELS2x
#define TPM2C2SC_MS2x                   _TPM2C2SC.MergedBits.grpMS2x

#define TPM2C2SC_ELS2A_MASK             4U
#define TPM2C2SC_ELS2B_MASK             8U
#define TPM2C2SC_MS2A_MASK              16U
#define TPM2C2SC_MS2B_MASK              32U
#define TPM2C2SC_CH2IE_MASK             64U
#define TPM2C2SC_CH2F_MASK              128U
#define TPM2C2SC_ELS2x_MASK             12U
#define TPM2C2SC_ELS2x_BITNUM           2U
#define TPM2C2SC_MS2x_MASK              48U
#define TPM2C2SC_MS2x_BITNUM            4U


/*** TPM2C2V - TPM2 Timer Channel 2 Value Register; 0xFFFF98AC ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C2VH - TPM2 Timer Channel 2 Value Register High; 0xFFFF98AC ***/
    union {
      byte Byte;
    } TPM2C2VHSTR;
    #define TPM2C2VH                    _TPM2C2V.Overlap_STR.TPM2C2VHSTR.Byte
    

    /*** TPM2C2VL - TPM2 Timer Channel 2 Value Register Low; 0xFFFF98AD ***/
    union {
      byte Byte;
    } TPM2C2VLSTR;
    #define TPM2C2VL                    _TPM2C2V.Overlap_STR.TPM2C2VLSTR.Byte
    
  } Overlap_STR;

} TPM2C2VSTR;
extern volatile TPM2C2VSTR _TPM2C2V @0xFFFF98AC;
#define TPM2C2V                         _TPM2C2V.Word


/*** TPM2C3SC - TPM2 Timer Channel 3 Status and Control Register; 0xFFFF98AE ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS3A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS3B       :1;                                       /* Edge/Level Select Bit B */
    byte MS3A        :1;                                       /* Mode Select A for TPM Channel 3 */
    byte MS3B        :1;                                       /* Mode Select B for TPM Channel 3 */
    byte CH3IE       :1;                                       /* Channel 3 Interrupt Enable */
    byte CH3F        :1;                                       /* Channel 3 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS3x :2;
    byte grpMS3x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C3SCSTR;
extern volatile TPM2C3SCSTR _TPM2C3SC @0xFFFF98AE;
#define TPM2C3SC                        _TPM2C3SC.Byte
#define TPM2C3SC_ELS3A                  _TPM2C3SC.Bits.ELS3A
#define TPM2C3SC_ELS3B                  _TPM2C3SC.Bits.ELS3B
#define TPM2C3SC_MS3A                   _TPM2C3SC.Bits.MS3A
#define TPM2C3SC_MS3B                   _TPM2C3SC.Bits.MS3B
#define TPM2C3SC_CH3IE                  _TPM2C3SC.Bits.CH3IE
#define TPM2C3SC_CH3F                   _TPM2C3SC.Bits.CH3F
#define TPM2C3SC_ELS3x                  _TPM2C3SC.MergedBits.grpELS3x
#define TPM2C3SC_MS3x                   _TPM2C3SC.MergedBits.grpMS3x

#define TPM2C3SC_ELS3A_MASK             4U
#define TPM2C3SC_ELS3B_MASK             8U
#define TPM2C3SC_MS3A_MASK              16U
#define TPM2C3SC_MS3B_MASK              32U
#define TPM2C3SC_CH3IE_MASK             64U
#define TPM2C3SC_CH3F_MASK              128U
#define TPM2C3SC_ELS3x_MASK             12U
#define TPM2C3SC_ELS3x_BITNUM           2U
#define TPM2C3SC_MS3x_MASK              48U
#define TPM2C3SC_MS3x_BITNUM            4U


/*** TPM2C3V - TPM2 Timer Channel 3 Value Register; 0xFFFF98AF ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C3VH - TPM2 Timer Channel 3 Value Register High; 0xFFFF98AF ***/
    union {
      byte Byte;
    } TPM2C3VHSTR;
    #define TPM2C3VH                    _TPM2C3V.Overlap_STR.TPM2C3VHSTR.Byte
    

    /*** TPM2C3VL - TPM2 Timer Channel 3 Value Register Low; 0xFFFF98B0 ***/
    union {
      byte Byte;
    } TPM2C3VLSTR;
    #define TPM2C3VL                    _TPM2C3V.Overlap_STR.TPM2C3VLSTR.Byte
    
  } Overlap_STR;

} TPM2C3VSTR;
extern volatile TPM2C3VSTR _TPM2C3V @0xFFFF98AF;
#define TPM2C3V                         _TPM2C3V.Word


/*** SCI1BD - SCI1 Baud Rate Register; 0xFFFF98B8 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI1BDH - SCI1 Baud Rate Register High; 0xFFFF98B8 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
        byte LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI1BDHSTR;
    #define SCI1BDH                     _SCI1BD.Overlap_STR.SCI1BDHSTR.Byte
    #define SCI1BDH_SBR8                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR8
    #define SCI1BDH_SBR9                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR9
    #define SCI1BDH_SBR10               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR10
    #define SCI1BDH_SBR11               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR11
    #define SCI1BDH_SBR12               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR12
    #define SCI1BDH_RXEDGIE             _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.RXEDGIE
    #define SCI1BDH_LBKDIE              _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.LBKDIE
    #define SCI1BDH_SBR_8               _SCI1BD.Overlap_STR.SCI1BDHSTR.MergedBits.grpSBR_8
    #define SCI1BDH_SBR                 SCI1BDH_SBR_8
    
    #define SCI1BDH_SBR8_MASK           1U
    #define SCI1BDH_SBR9_MASK           2U
    #define SCI1BDH_SBR10_MASK          4U
    #define SCI1BDH_SBR11_MASK          8U
    #define SCI1BDH_SBR12_MASK          16U
    #define SCI1BDH_RXEDGIE_MASK        64U
    #define SCI1BDH_LBKDIE_MASK         128U
    #define SCI1BDH_SBR_8_MASK          31U
    #define SCI1BDH_SBR_8_BITNUM        0U
    

    /*** SCI1BDL - SCI1 Baud Rate Register Low; 0xFFFF98B9 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI1BDLSTR;
    #define SCI1BDL                     _SCI1BD.Overlap_STR.SCI1BDLSTR.Byte
    #define SCI1BDL_SBR0                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR0
    #define SCI1BDL_SBR1                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR1
    #define SCI1BDL_SBR2                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR2
    #define SCI1BDL_SBR3                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR3
    #define SCI1BDL_SBR4                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR4
    #define SCI1BDL_SBR5                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR5
    #define SCI1BDL_SBR6                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR6
    #define SCI1BDL_SBR7                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR7
    
    #define SCI1BDL_SBR0_MASK           1U
    #define SCI1BDL_SBR1_MASK           2U
    #define SCI1BDL_SBR2_MASK           4U
    #define SCI1BDL_SBR3_MASK           8U
    #define SCI1BDL_SBR4_MASK           16U
    #define SCI1BDL_SBR5_MASK           32U
    #define SCI1BDL_SBR6_MASK           64U
    #define SCI1BDL_SBR7_MASK           128U
    
  } Overlap_STR;

  struct {
    word SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
    word SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
    word SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
    word SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
    word SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
    word SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
    word SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
    word SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
    word SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
    word SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
    word SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
    word SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
    word SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
    word             :1; 
    word RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
    word LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
  } Bits;
  struct {
    word grpSBR  :13;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} SCI1BDSTR;
extern volatile SCI1BDSTR _SCI1BD @0xFFFF98B8;
#define SCI1BD                          _SCI1BD.Word
#define SCI1BD_SBR0                     _SCI1BD.Bits.SBR0
#define SCI1BD_SBR1                     _SCI1BD.Bits.SBR1
#define SCI1BD_SBR2                     _SCI1BD.Bits.SBR2
#define SCI1BD_SBR3                     _SCI1BD.Bits.SBR3
#define SCI1BD_SBR4                     _SCI1BD.Bits.SBR4
#define SCI1BD_SBR5                     _SCI1BD.Bits.SBR5
#define SCI1BD_SBR6                     _SCI1BD.Bits.SBR6
#define SCI1BD_SBR7                     _SCI1BD.Bits.SBR7
#define SCI1BD_SBR8                     _SCI1BD.Bits.SBR8
#define SCI1BD_SBR9                     _SCI1BD.Bits.SBR9
#define SCI1BD_SBR10                    _SCI1BD.Bits.SBR10
#define SCI1BD_SBR11                    _SCI1BD.Bits.SBR11
#define SCI1BD_SBR12                    _SCI1BD.Bits.SBR12
#define SCI1BD_RXEDGIE                  _SCI1BD.Bits.RXEDGIE
#define SCI1BD_LBKDIE                   _SCI1BD.Bits.LBKDIE
#define SCI1BD_SBR                      _SCI1BD.MergedBits.grpSBR

#define SCI1BD_SBR0_MASK                1U
#define SCI1BD_SBR1_MASK                2U
#define SCI1BD_SBR2_MASK                4U
#define SCI1BD_SBR3_MASK                8U
#define SCI1BD_SBR4_MASK                16U
#define SCI1BD_SBR5_MASK                32U
#define SCI1BD_SBR6_MASK                64U
#define SCI1BD_SBR7_MASK                128U
#define SCI1BD_SBR8_MASK                256U
#define SCI1BD_SBR9_MASK                512U
#define SCI1BD_SBR10_MASK               1024U
#define SCI1BD_SBR11_MASK               2048U
#define SCI1BD_SBR12_MASK               4096U
#define SCI1BD_RXEDGIE_MASK             16384U
#define SCI1BD_LBKDIE_MASK              32768U
#define SCI1BD_SBR_MASK                 8191U
#define SCI1BD_SBR_BITNUM               0U


/*** SCI1C1 - SCI1 Control Register 1; 0xFFFF98BA ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI1C1STR;
extern volatile SCI1C1STR _SCI1C1 @0xFFFF98BA;
#define SCI1C1                          _SCI1C1.Byte
#define SCI1C1_PT                       _SCI1C1.Bits.PT
#define SCI1C1_PE                       _SCI1C1.Bits.PE
#define SCI1C1_ILT                      _SCI1C1.Bits.ILT
#define SCI1C1_WAKE                     _SCI1C1.Bits.WAKE
#define SCI1C1_M                        _SCI1C1.Bits.M
#define SCI1C1_RSRC                     _SCI1C1.Bits.RSRC
#define SCI1C1_SCISWAI                  _SCI1C1.Bits.SCISWAI
#define SCI1C1_LOOPS                    _SCI1C1.Bits.LOOPS

#define SCI1C1_PT_MASK                  1U
#define SCI1C1_PE_MASK                  2U
#define SCI1C1_ILT_MASK                 4U
#define SCI1C1_WAKE_MASK                8U
#define SCI1C1_M_MASK                   16U
#define SCI1C1_RSRC_MASK                32U
#define SCI1C1_SCISWAI_MASK             64U
#define SCI1C1_LOOPS_MASK               128U


/*** SCI1C2 - SCI1 Control Register 2; 0xFFFF98BB ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI1C2STR;
extern volatile SCI1C2STR _SCI1C2 @0xFFFF98BB;
#define SCI1C2                          _SCI1C2.Byte
#define SCI1C2_SBK                      _SCI1C2.Bits.SBK
#define SCI1C2_RWU                      _SCI1C2.Bits.RWU
#define SCI1C2_RE                       _SCI1C2.Bits.RE
#define SCI1C2_TE                       _SCI1C2.Bits.TE
#define SCI1C2_ILIE                     _SCI1C2.Bits.ILIE
#define SCI1C2_RIE                      _SCI1C2.Bits.RIE
#define SCI1C2_TCIE                     _SCI1C2.Bits.TCIE
#define SCI1C2_TIE                      _SCI1C2.Bits.TIE

#define SCI1C2_SBK_MASK                 1U
#define SCI1C2_RWU_MASK                 2U
#define SCI1C2_RE_MASK                  4U
#define SCI1C2_TE_MASK                  8U
#define SCI1C2_ILIE_MASK                16U
#define SCI1C2_RIE_MASK                 32U
#define SCI1C2_TCIE_MASK                64U
#define SCI1C2_TIE_MASK                 128U


/*** SCI1S1 - SCI1 Status Register 1; 0xFFFF98BC ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI1S1STR;
extern volatile SCI1S1STR _SCI1S1 @0xFFFF98BC;
#define SCI1S1                          _SCI1S1.Byte
#define SCI1S1_PF                       _SCI1S1.Bits.PF
#define SCI1S1_FE                       _SCI1S1.Bits.FE
#define SCI1S1_NF                       _SCI1S1.Bits.NF
#define SCI1S1_OR                       _SCI1S1.Bits.OR
#define SCI1S1_IDLE                     _SCI1S1.Bits.IDLE
#define SCI1S1_RDRF                     _SCI1S1.Bits.RDRF
#define SCI1S1_TC                       _SCI1S1.Bits.TC
#define SCI1S1_TDRE                     _SCI1S1.Bits.TDRE

#define SCI1S1_PF_MASK                  1U
#define SCI1S1_FE_MASK                  2U
#define SCI1S1_NF_MASK                  4U
#define SCI1S1_OR_MASK                  8U
#define SCI1S1_IDLE_MASK                16U
#define SCI1S1_RDRF_MASK                32U
#define SCI1S1_TC_MASK                  64U
#define SCI1S1_TDRE_MASK                128U


/*** SCI1S2 - SCI1 Status Register 2; 0xFFFF98BD ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte LBKDE       :1;                                       /* LIN Break Detection Enable */
    byte BRK13       :1;                                       /* Break Character Generation Length */
    byte RWUID       :1;                                       /* Receive Wake Up Idle Detect */
    byte RXINV       :1;                                       /* Receive Data Inversion */
    byte             :1; 
    byte RXEDGIF     :1;                                       /* RxD Pin Active Edge Interrupt Flag */
    byte LBKDIF      :1;                                       /* LIN Break Detect Interrupt Flag */
  } Bits;
} SCI1S2STR;
extern volatile SCI1S2STR _SCI1S2 @0xFFFF98BD;
#define SCI1S2                          _SCI1S2.Byte
#define SCI1S2_RAF                      _SCI1S2.Bits.RAF
#define SCI1S2_LBKDE                    _SCI1S2.Bits.LBKDE
#define SCI1S2_BRK13                    _SCI1S2.Bits.BRK13
#define SCI1S2_RWUID                    _SCI1S2.Bits.RWUID
#define SCI1S2_RXINV                    _SCI1S2.Bits.RXINV
#define SCI1S2_RXEDGIF                  _SCI1S2.Bits.RXEDGIF
#define SCI1S2_LBKDIF                   _SCI1S2.Bits.LBKDIF

#define SCI1S2_RAF_MASK                 1U
#define SCI1S2_LBKDE_MASK               2U
#define SCI1S2_BRK13_MASK               4U
#define SCI1S2_RWUID_MASK               8U
#define SCI1S2_RXINV_MASK               16U
#define SCI1S2_RXEDGIF_MASK             64U
#define SCI1S2_LBKDIF_MASK              128U


/*** SCI1C3 - SCI1 Control Register 3; 0xFFFF98BE ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI1C3STR;
extern volatile SCI1C3STR _SCI1C3 @0xFFFF98BE;
#define SCI1C3                          _SCI1C3.Byte
#define SCI1C3_PEIE                     _SCI1C3.Bits.PEIE
#define SCI1C3_FEIE                     _SCI1C3.Bits.FEIE
#define SCI1C3_NEIE                     _SCI1C3.Bits.NEIE
#define SCI1C3_ORIE                     _SCI1C3.Bits.ORIE
#define SCI1C3_TXINV                    _SCI1C3.Bits.TXINV
#define SCI1C3_TXDIR                    _SCI1C3.Bits.TXDIR
#define SCI1C3_T8                       _SCI1C3.Bits.T8
#define SCI1C3_R8                       _SCI1C3.Bits.R8

#define SCI1C3_PEIE_MASK                1U
#define SCI1C3_FEIE_MASK                2U
#define SCI1C3_NEIE_MASK                4U
#define SCI1C3_ORIE_MASK                8U
#define SCI1C3_TXINV_MASK               16U
#define SCI1C3_TXDIR_MASK               32U
#define SCI1C3_T8_MASK                  64U
#define SCI1C3_R8_MASK                  128U


/*** SCI1D - SCI1 Data Register; 0xFFFF98BF ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI1DSTR;
extern volatile SCI1DSTR _SCI1D @0xFFFF98BF;
#define SCI1D                           _SCI1D.Byte
#define SCI1D_R0_T0                     _SCI1D.Bits.R0_T0
#define SCI1D_R1_T1                     _SCI1D.Bits.R1_T1
#define SCI1D_R2_T2                     _SCI1D.Bits.R2_T2
#define SCI1D_R3_T3                     _SCI1D.Bits.R3_T3
#define SCI1D_R4_T4                     _SCI1D.Bits.R4_T4
#define SCI1D_R5_T5                     _SCI1D.Bits.R5_T5
#define SCI1D_R6_T6                     _SCI1D.Bits.R6_T6
#define SCI1D_R7_T7                     _SCI1D.Bits.R7_T7

#define SCI1D_R0_T0_MASK                1U
#define SCI1D_R1_T1_MASK                2U
#define SCI1D_R2_T2_MASK                4U
#define SCI1D_R3_T3_MASK                8U
#define SCI1D_R4_T4_MASK                16U
#define SCI1D_R5_T5_MASK                32U
#define SCI1D_R6_T6_MASK                64U
#define SCI1D_R7_T7_MASK                128U


/*** PDBSC - PDB Status and Control Register; 0xFFFF98C0 ***/
typedef union {
  byte Byte;
  struct {
    byte LDOK        :1;                                       /* Load OK */
    byte DACTOE      :1;                                       /* DAC Trigger Output Enable */
    byte TOS0        :1;                                       /* Trigger Output Select, bit 0 */
    byte TOS1        :1;                                       /* Trigger Output Select, bit 1 */
    byte LDMOD       :1;                                       /* Load Mode Select */
    byte PDBIE       :1;                                       /* PDB Interrupt Enable */
    byte PDBIF       :1;                                       /* PDB Interrupt Flag */
    byte PDBEN       :1;                                       /* PDB module Enable */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpTOS  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} PDBSCSTR;
extern volatile PDBSCSTR _PDBSC @0xFFFF98C0;
#define PDBSC                           _PDBSC.Byte
#define PDBSC_LDOK                      _PDBSC.Bits.LDOK
#define PDBSC_DACTOE                    _PDBSC.Bits.DACTOE
#define PDBSC_TOS0                      _PDBSC.Bits.TOS0
#define PDBSC_TOS1                      _PDBSC.Bits.TOS1
#define PDBSC_LDMOD                     _PDBSC.Bits.LDMOD
#define PDBSC_PDBIE                     _PDBSC.Bits.PDBIE
#define PDBSC_PDBIF                     _PDBSC.Bits.PDBIF
#define PDBSC_PDBEN                     _PDBSC.Bits.PDBEN
#define PDBSC_TOS                       _PDBSC.MergedBits.grpTOS

#define PDBSC_LDOK_MASK                 1U
#define PDBSC_DACTOE_MASK               2U
#define PDBSC_TOS0_MASK                 4U
#define PDBSC_TOS1_MASK                 8U
#define PDBSC_LDMOD_MASK                16U
#define PDBSC_PDBIE_MASK                32U
#define PDBSC_PDBIF_MASK                64U
#define PDBSC_PDBEN_MASK                128U
#define PDBSC_TOS_MASK                  12U
#define PDBSC_TOS_BITNUM                2U


/*** PDBC1 - PDB Control Register 1; 0xFFFF98C1 ***/
typedef union {
  byte Byte;
  struct {
    byte MULT        :1;                                       /* Multiply prescaler bit */
    byte CONT        :1;                                       /* Continuous Mode Enable */
    byte TRIGSEL0    :1;                                       /* Input Trigger Select, bit 0 */
    byte TRIGSEL1    :1;                                       /* Input Trigger Select, bit 1 */
    byte TRIGSEL2    :1;                                       /* Input Trigger Select, bit 2 */
    byte PRESCALER0  :1;                                       /* Clock Prescaler Select, bit 0 */
    byte PRESCALER1  :1;                                       /* Clock Prescaler Select, bit 1 */
    byte PRESCALER2  :1;                                       /* Clock Prescaler Select, bit 2 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpTRIGSEL :3;
    byte grpPRESCALER :3;
  } MergedBits;
} PDBC1STR;
extern volatile PDBC1STR _PDBC1 @0xFFFF98C1;
#define PDBC1                           _PDBC1.Byte
#define PDBC1_MULT                      _PDBC1.Bits.MULT
#define PDBC1_CONT                      _PDBC1.Bits.CONT
#define PDBC1_TRIGSEL0                  _PDBC1.Bits.TRIGSEL0
#define PDBC1_TRIGSEL1                  _PDBC1.Bits.TRIGSEL1
#define PDBC1_TRIGSEL2                  _PDBC1.Bits.TRIGSEL2
#define PDBC1_PRESCALER0                _PDBC1.Bits.PRESCALER0
#define PDBC1_PRESCALER1                _PDBC1.Bits.PRESCALER1
#define PDBC1_PRESCALER2                _PDBC1.Bits.PRESCALER2
#define PDBC1_TRIGSEL                   _PDBC1.MergedBits.grpTRIGSEL
#define PDBC1_PRESCALER                 _PDBC1.MergedBits.grpPRESCALER

#define PDBC1_MULT_MASK                 1U
#define PDBC1_CONT_MASK                 2U
#define PDBC1_TRIGSEL0_MASK             4U
#define PDBC1_TRIGSEL1_MASK             8U
#define PDBC1_TRIGSEL2_MASK             16U
#define PDBC1_PRESCALER0_MASK           32U
#define PDBC1_PRESCALER1_MASK           64U
#define PDBC1_PRESCALER2_MASK           128U
#define PDBC1_TRIGSEL_MASK              28U
#define PDBC1_TRIGSEL_BITNUM            2U
#define PDBC1_PRESCALER_MASK            224U
#define PDBC1_PRESCALER_BITNUM          5U


/*** PDBC2 - PDB Control Register 2; 0xFFFF98C2 ***/
typedef union {
  byte Byte;
  struct {
    byte SWTRIG      :1;                                       /* SoftwareTrigger */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} PDBC2STR;
extern volatile PDBC2STR _PDBC2 @0xFFFF98C2;
#define PDBC2                           _PDBC2.Byte
#define PDBC2_SWTRIG                    _PDBC2.Bits.SWTRIG

#define PDBC2_SWTRIG_MASK               1U


/*** PDBCHEN - PDB Channel Enable; 0xFFFF98C3 ***/
typedef union {
  byte Byte;
  struct {
    byte CHEN0       :1;                                       /* PDB channel enable, bit 0 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} PDBCHENSTR;
extern volatile PDBCHENSTR _PDBCHEN @0xFFFF98C3;
#define PDBCHEN                         _PDBCHEN.Byte
#define PDBCHEN_CHEN0                   _PDBCHEN.Bits.CHEN0

#define PDBCHEN_CHEN0_MASK              1U


/*** PDBMOD - PDB Modulus Register; 0xFFFF98C4 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PDBMODH - PDB Modulus Register High; 0xFFFF98C4 ***/
    union {
      byte Byte;
    } PDBMODHSTR;
    #define PDBMODH                     _PDBMOD.Overlap_STR.PDBMODHSTR.Byte
    

    /*** PDBMODL - PDB Modulus Register Low; 0xFFFF98C5 ***/
    union {
      byte Byte;
    } PDBMODLSTR;
    #define PDBMODL                     _PDBMOD.Overlap_STR.PDBMODLSTR.Byte
    
  } Overlap_STR;

} PDBMODSTR;
extern volatile PDBMODSTR _PDBMOD @0xFFFF98C4;
#define PDBMOD                          _PDBMOD.Word


/*** PDBCNT - PDB Counter Register; 0xFFFF98C6 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PDBCNTH - PDB Counter Register High; 0xFFFF98C6 ***/
    union {
      byte Byte;
    } PDBCNTHSTR;
    #define PDBCNTH                     _PDBCNT.Overlap_STR.PDBCNTHSTR.Byte
    

    /*** PDBCNTL - PDB Counter Register Low; 0xFFFF98C7 ***/
    union {
      byte Byte;
    } PDBCNTLSTR;
    #define PDBCNTL                     _PDBCNT.Overlap_STR.PDBCNTLSTR.Byte
    
  } Overlap_STR;

} PDBCNTSTR;
extern volatile PDBCNTSTR _PDBCNT @0xFFFF98C6;
#define PDBCNT                          _PDBCNT.Word


/*** PDBIDLY - PDB Interrupt Delay Register; 0xFFFF98C8 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PDBIDLYH - PDB Interrupt Delay Register High; 0xFFFF98C8 ***/
    union {
      byte Byte;
      struct {
        byte IDELAY8     :1;                                       /* Interrupt Delay, bit 8 */
        byte IDELAY9     :1;                                       /* Interrupt Delay, bit 9 */
        byte IDELAY10    :1;                                       /* Interrupt Delay, bit 10 */
        byte IDELAY11    :1;                                       /* Interrupt Delay, bit 11 */
        byte IDELAY12    :1;                                       /* Interrupt Delay, bit 12 */
        byte IDELAY13    :1;                                       /* Interrupt Delay, bit 13 */
        byte IDELAY14    :1;                                       /* Interrupt Delay, bit 14 */
        byte IDELAY15    :1;                                       /* Interrupt Delay, bit 15 */
      } Bits;
    } PDBIDLYHSTR;
    #define PDBIDLYH                    _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Byte
    #define PDBIDLYH_IDELAY8            _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY8
    #define PDBIDLYH_IDELAY9            _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY9
    #define PDBIDLYH_IDELAY10           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY10
    #define PDBIDLYH_IDELAY11           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY11
    #define PDBIDLYH_IDELAY12           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY12
    #define PDBIDLYH_IDELAY13           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY13
    #define PDBIDLYH_IDELAY14           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY14
    #define PDBIDLYH_IDELAY15           _PDBIDLY.Overlap_STR.PDBIDLYHSTR.Bits.IDELAY15
    
    #define PDBIDLYH_IDELAY8_MASK       1U
    #define PDBIDLYH_IDELAY9_MASK       2U
    #define PDBIDLYH_IDELAY10_MASK      4U
    #define PDBIDLYH_IDELAY11_MASK      8U
    #define PDBIDLYH_IDELAY12_MASK      16U
    #define PDBIDLYH_IDELAY13_MASK      32U
    #define PDBIDLYH_IDELAY14_MASK      64U
    #define PDBIDLYH_IDELAY15_MASK      128U
    

    /*** PDBIDLYL - PDB Interrupt Delay Register Low; 0xFFFF98C9 ***/
    union {
      byte Byte;
      struct {
        byte IDELAY0     :1;                                       /* Interrupt Delay, bit 0 */
        byte IDELAY1     :1;                                       /* Interrupt Delay, bit 1 */
        byte IDELAY2     :1;                                       /* Interrupt Delay, bit 2 */
        byte IDELAY3     :1;                                       /* Interrupt Delay, bit 3 */
        byte IDELAY4     :1;                                       /* Interrupt Delay, bit 4 */
        byte IDELAY5     :1;                                       /* Interrupt Delay, bit 5 */
        byte IDELAY6     :1;                                       /* Interrupt Delay, bit 6 */
        byte IDELAY7     :1;                                       /* Interrupt Delay, bit 7 */
      } Bits;
    } PDBIDLYLSTR;
    #define PDBIDLYL                    _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Byte
    #define PDBIDLYL_IDELAY0            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY0
    #define PDBIDLYL_IDELAY1            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY1
    #define PDBIDLYL_IDELAY2            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY2
    #define PDBIDLYL_IDELAY3            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY3
    #define PDBIDLYL_IDELAY4            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY4
    #define PDBIDLYL_IDELAY5            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY5
    #define PDBIDLYL_IDELAY6            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY6
    #define PDBIDLYL_IDELAY7            _PDBIDLY.Overlap_STR.PDBIDLYLSTR.Bits.IDELAY7
    
    #define PDBIDLYL_IDELAY0_MASK       1U
    #define PDBIDLYL_IDELAY1_MASK       2U
    #define PDBIDLYL_IDELAY2_MASK       4U
    #define PDBIDLYL_IDELAY3_MASK       8U
    #define PDBIDLYL_IDELAY4_MASK       16U
    #define PDBIDLYL_IDELAY5_MASK       32U
    #define PDBIDLYL_IDELAY6_MASK       64U
    #define PDBIDLYL_IDELAY7_MASK       128U
    
  } Overlap_STR;

  struct {
    word IDELAY0     :1;                                       /* Interrupt Delay, bit 0 */
    word IDELAY1     :1;                                       /* Interrupt Delay, bit 1 */
    word IDELAY2     :1;                                       /* Interrupt Delay, bit 2 */
    word IDELAY3     :1;                                       /* Interrupt Delay, bit 3 */
    word IDELAY4     :1;                                       /* Interrupt Delay, bit 4 */
    word IDELAY5     :1;                                       /* Interrupt Delay, bit 5 */
    word IDELAY6     :1;                                       /* Interrupt Delay, bit 6 */
    word IDELAY7     :1;                                       /* Interrupt Delay, bit 7 */
    word IDELAY8     :1;                                       /* Interrupt Delay, bit 8 */
    word IDELAY9     :1;                                       /* Interrupt Delay, bit 9 */
    word IDELAY10    :1;                                       /* Interrupt Delay, bit 10 */
    word IDELAY11    :1;                                       /* Interrupt Delay, bit 11 */
    word IDELAY12    :1;                                       /* Interrupt Delay, bit 12 */
    word IDELAY13    :1;                                       /* Interrupt Delay, bit 13 */
    word IDELAY14    :1;                                       /* Interrupt Delay, bit 14 */
    word IDELAY15    :1;                                       /* Interrupt Delay, bit 15 */
  } Bits;
} PDBIDLYSTR;
extern volatile PDBIDLYSTR _PDBIDLY @0xFFFF98C8;
#define PDBIDLY                         _PDBIDLY.Word
#define PDBIDLY_IDELAY0                 _PDBIDLY.Bits.IDELAY0
#define PDBIDLY_IDELAY1                 _PDBIDLY.Bits.IDELAY1
#define PDBIDLY_IDELAY2                 _PDBIDLY.Bits.IDELAY2
#define PDBIDLY_IDELAY3                 _PDBIDLY.Bits.IDELAY3
#define PDBIDLY_IDELAY4                 _PDBIDLY.Bits.IDELAY4
#define PDBIDLY_IDELAY5                 _PDBIDLY.Bits.IDELAY5
#define PDBIDLY_IDELAY6                 _PDBIDLY.Bits.IDELAY6
#define PDBIDLY_IDELAY7                 _PDBIDLY.Bits.IDELAY7
#define PDBIDLY_IDELAY8                 _PDBIDLY.Bits.IDELAY8
#define PDBIDLY_IDELAY9                 _PDBIDLY.Bits.IDELAY9
#define PDBIDLY_IDELAY10                _PDBIDLY.Bits.IDELAY10
#define PDBIDLY_IDELAY11                _PDBIDLY.Bits.IDELAY11
#define PDBIDLY_IDELAY12                _PDBIDLY.Bits.IDELAY12
#define PDBIDLY_IDELAY13                _PDBIDLY.Bits.IDELAY13
#define PDBIDLY_IDELAY14                _PDBIDLY.Bits.IDELAY14
#define PDBIDLY_IDELAY15                _PDBIDLY.Bits.IDELAY15

#define PDBIDLY_IDELAY0_MASK            1U
#define PDBIDLY_IDELAY1_MASK            2U
#define PDBIDLY_IDELAY2_MASK            4U
#define PDBIDLY_IDELAY3_MASK            8U
#define PDBIDLY_IDELAY4_MASK            16U
#define PDBIDLY_IDELAY5_MASK            32U
#define PDBIDLY_IDELAY6_MASK            64U
#define PDBIDLY_IDELAY7_MASK            128U
#define PDBIDLY_IDELAY8_MASK            256U
#define PDBIDLY_IDELAY9_MASK            512U
#define PDBIDLY_IDELAY10_MASK           1024U
#define PDBIDLY_IDELAY11_MASK           2048U
#define PDBIDLY_IDELAY12_MASK           4096U
#define PDBIDLY_IDELAY13_MASK           8192U
#define PDBIDLY_IDELAY14_MASK           16384U
#define PDBIDLY_IDELAY15_MASK           32768U


/*** DACINT - DAC Trigger Interval Register; 0xFFFF98CA ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DACINTH - DAC Trigger Interval Register High; 0xFFFF98CA ***/
    union {
      byte Byte;
      struct {
        byte DACINT8     :1;                                       /* DAC Interval, bit 8 */
        byte DACINT9     :1;                                       /* DAC Interval, bit 9 */
        byte DACINT10    :1;                                       /* DAC Interval, bit 10 */
        byte DACINT11    :1;                                       /* DAC Interval, bit 11 */
        byte DACINT12    :1;                                       /* DAC Interval, bit 12 */
        byte DACINT13    :1;                                       /* DAC Interval, bit 13 */
        byte DACINT14    :1;                                       /* DAC Interval, bit 14 */
        byte DACINT15    :1;                                       /* DAC Interval, bit 15 */
      } Bits;
    } DACINTHSTR;
    #define DACINTH                     _DACINT.Overlap_STR.DACINTHSTR.Byte
    #define DACINTH_DACINT8             _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT8
    #define DACINTH_DACINT9             _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT9
    #define DACINTH_DACINT10            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT10
    #define DACINTH_DACINT11            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT11
    #define DACINTH_DACINT12            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT12
    #define DACINTH_DACINT13            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT13
    #define DACINTH_DACINT14            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT14
    #define DACINTH_DACINT15            _DACINT.Overlap_STR.DACINTHSTR.Bits.DACINT15
    
    #define DACINTH_DACINT8_MASK        1U
    #define DACINTH_DACINT9_MASK        2U
    #define DACINTH_DACINT10_MASK       4U
    #define DACINTH_DACINT11_MASK       8U
    #define DACINTH_DACINT12_MASK       16U
    #define DACINTH_DACINT13_MASK       32U
    #define DACINTH_DACINT14_MASK       64U
    #define DACINTH_DACINT15_MASK       128U
    

    /*** DACINTL - DAC Trigger Interval Register Low; 0xFFFF98CB ***/
    union {
      byte Byte;
      struct {
        byte DACINT0     :1;                                       /* DAC Interval, bit 0 */
        byte DACINT1     :1;                                       /* DAC Interval, bit 1 */
        byte DACINT2     :1;                                       /* DAC Interval, bit 2 */
        byte DACINT3     :1;                                       /* DAC Interval, bit 3 */
        byte DACINT4     :1;                                       /* DAC Interval, bit 4 */
        byte DACINT5     :1;                                       /* DAC Interval, bit 5 */
        byte DACINT6     :1;                                       /* DAC Interval, bit 6 */
        byte DACINT7     :1;                                       /* DAC Interval, bit 7 */
      } Bits;
    } DACINTLSTR;
    #define DACINTL                     _DACINT.Overlap_STR.DACINTLSTR.Byte
    #define DACINTL_DACINT0             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT0
    #define DACINTL_DACINT1             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT1
    #define DACINTL_DACINT2             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT2
    #define DACINTL_DACINT3             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT3
    #define DACINTL_DACINT4             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT4
    #define DACINTL_DACINT5             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT5
    #define DACINTL_DACINT6             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT6
    #define DACINTL_DACINT7             _DACINT.Overlap_STR.DACINTLSTR.Bits.DACINT7
    
    #define DACINTL_DACINT0_MASK        1U
    #define DACINTL_DACINT1_MASK        2U
    #define DACINTL_DACINT2_MASK        4U
    #define DACINTL_DACINT3_MASK        8U
    #define DACINTL_DACINT4_MASK        16U
    #define DACINTL_DACINT5_MASK        32U
    #define DACINTL_DACINT6_MASK        64U
    #define DACINTL_DACINT7_MASK        128U
    
  } Overlap_STR;

} DACINTSTR;
extern volatile DACINTSTR _DACINT @0xFFFF98CA;
#define DACINT                          _DACINT.Word


/*** PDBDLY - PDB Delay A Register; 0xFFFF98CC ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** PDBDLYH - PDB Delay A Register High; 0xFFFF98CC ***/
    union {
      byte Byte;
      struct {
        byte DELAY8      :1;                                       /* Delay, bit 8 */
        byte DELAY9      :1;                                       /* Delay, bit 9 */
        byte DELAY10     :1;                                       /* Delay, bit 10 */
        byte DELAY11     :1;                                       /* Delay, bit 11 */
        byte DELAY12     :1;                                       /* Delay, bit 12 */
        byte DELAY13     :1;                                       /* Delay, bit 13 */
        byte DELAY14     :1;                                       /* Delay, bit 14 */
        byte DELAY15     :1;                                       /* Delay, bit 15 */
      } Bits;
    } PDBDLYHSTR;
    #define PDBDLYH                     _PDBDLY.Overlap_STR.PDBDLYHSTR.Byte
    #define PDBDLYH_DELAY8              _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY8
    #define PDBDLYH_DELAY9              _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY9
    #define PDBDLYH_DELAY10             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY10
    #define PDBDLYH_DELAY11             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY11
    #define PDBDLYH_DELAY12             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY12
    #define PDBDLYH_DELAY13             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY13
    #define PDBDLYH_DELAY14             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY14
    #define PDBDLYH_DELAY15             _PDBDLY.Overlap_STR.PDBDLYHSTR.Bits.DELAY15
    
    #define PDBDLYH_DELAY8_MASK         1U
    #define PDBDLYH_DELAY9_MASK         2U
    #define PDBDLYH_DELAY10_MASK        4U
    #define PDBDLYH_DELAY11_MASK        8U
    #define PDBDLYH_DELAY12_MASK        16U
    #define PDBDLYH_DELAY13_MASK        32U
    #define PDBDLYH_DELAY14_MASK        64U
    #define PDBDLYH_DELAY15_MASK        128U
    

    /*** PDBDLYL - PDB Delay A Register Low; 0xFFFF98CD ***/
    union {
      byte Byte;
      struct {
        byte DELAY0      :1;                                       /* Delay, bit 0 */
        byte DELAY1      :1;                                       /* Delay, bit 1 */
        byte DELAY2      :1;                                       /* Delay, bit 2 */
        byte DELAY3      :1;                                       /* Delay, bit 3 */
        byte DELAY4      :1;                                       /* Delay, bit 4 */
        byte DELAY5      :1;                                       /* Delay, bit 5 */
        byte DELAY6      :1;                                       /* Delay, bit 6 */
        byte DELAY7      :1;                                       /* Delay, bit 7 */
      } Bits;
    } PDBDLYLSTR;
    #define PDBDLYL                     _PDBDLY.Overlap_STR.PDBDLYLSTR.Byte
    #define PDBDLYL_DELAY0              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY0
    #define PDBDLYL_DELAY1              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY1
    #define PDBDLYL_DELAY2              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY2
    #define PDBDLYL_DELAY3              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY3
    #define PDBDLYL_DELAY4              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY4
    #define PDBDLYL_DELAY5              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY5
    #define PDBDLYL_DELAY6              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY6
    #define PDBDLYL_DELAY7              _PDBDLY.Overlap_STR.PDBDLYLSTR.Bits.DELAY7
    
    #define PDBDLYL_DELAY0_MASK         1U
    #define PDBDLYL_DELAY1_MASK         2U
    #define PDBDLYL_DELAY2_MASK         4U
    #define PDBDLYL_DELAY3_MASK         8U
    #define PDBDLYL_DELAY4_MASK         16U
    #define PDBDLYL_DELAY5_MASK         32U
    #define PDBDLYL_DELAY6_MASK         64U
    #define PDBDLYL_DELAY7_MASK         128U
    
  } Overlap_STR;

  struct {
    word DELAY0      :1;                                       /* Delay, bit 0 */
    word DELAY1      :1;                                       /* Delay, bit 1 */
    word DELAY2      :1;                                       /* Delay, bit 2 */
    word DELAY3      :1;                                       /* Delay, bit 3 */
    word DELAY4      :1;                                       /* Delay, bit 4 */
    word DELAY5      :1;                                       /* Delay, bit 5 */
    word DELAY6      :1;                                       /* Delay, bit 6 */
    word DELAY7      :1;                                       /* Delay, bit 7 */
    word DELAY8      :1;                                       /* Delay, bit 8 */
    word DELAY9      :1;                                       /* Delay, bit 9 */
    word DELAY10     :1;                                       /* Delay, bit 10 */
    word DELAY11     :1;                                       /* Delay, bit 11 */
    word DELAY12     :1;                                       /* Delay, bit 12 */
    word DELAY13     :1;                                       /* Delay, bit 13 */
    word DELAY14     :1;                                       /* Delay, bit 14 */
    word DELAY15     :1;                                       /* Delay, bit 15 */
  } Bits;
} PDBDLYSTR;
extern volatile PDBDLYSTR _PDBDLY @0xFFFF98CC;
#define PDBDLY                          _PDBDLY.Word
#define PDBDLY_DELAY0                   _PDBDLY.Bits.DELAY0
#define PDBDLY_DELAY1                   _PDBDLY.Bits.DELAY1
#define PDBDLY_DELAY2                   _PDBDLY.Bits.DELAY2
#define PDBDLY_DELAY3                   _PDBDLY.Bits.DELAY3
#define PDBDLY_DELAY4                   _PDBDLY.Bits.DELAY4
#define PDBDLY_DELAY5                   _PDBDLY.Bits.DELAY5
#define PDBDLY_DELAY6                   _PDBDLY.Bits.DELAY6
#define PDBDLY_DELAY7                   _PDBDLY.Bits.DELAY7
#define PDBDLY_DELAY8                   _PDBDLY.Bits.DELAY8
#define PDBDLY_DELAY9                   _PDBDLY.Bits.DELAY9
#define PDBDLY_DELAY10                  _PDBDLY.Bits.DELAY10
#define PDBDLY_DELAY11                  _PDBDLY.Bits.DELAY11
#define PDBDLY_DELAY12                  _PDBDLY.Bits.DELAY12
#define PDBDLY_DELAY13                  _PDBDLY.Bits.DELAY13
#define PDBDLY_DELAY14                  _PDBDLY.Bits.DELAY14
#define PDBDLY_DELAY15                  _PDBDLY.Bits.DELAY15

#define PDBDLY_DELAY0_MASK              1U
#define PDBDLY_DELAY1_MASK              2U
#define PDBDLY_DELAY2_MASK              4U
#define PDBDLY_DELAY3_MASK              8U
#define PDBDLY_DELAY4_MASK              16U
#define PDBDLY_DELAY5_MASK              32U
#define PDBDLY_DELAY6_MASK              64U
#define PDBDLY_DELAY7_MASK              128U
#define PDBDLY_DELAY8_MASK              256U
#define PDBDLY_DELAY9_MASK              512U
#define PDBDLY_DELAY10_MASK             1024U
#define PDBDLY_DELAY11_MASK             2048U
#define PDBDLY_DELAY12_MASK             4096U
#define PDBDLY_DELAY13_MASK             8192U
#define PDBDLY_DELAY14_MASK             16384U
#define PDBDLY_DELAY15_MASK             32768U


/*** TPM1SC - TPM1 Status and Control Register; 0xFFFF98E0 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1SCSTR;
extern volatile TPM1SCSTR _TPM1SC @0xFFFF98E0;
#define TPM1SC                          _TPM1SC.Byte
#define TPM1SC_PS0                      _TPM1SC.Bits.PS0
#define TPM1SC_PS1                      _TPM1SC.Bits.PS1
#define TPM1SC_PS2                      _TPM1SC.Bits.PS2
#define TPM1SC_CLKSA                    _TPM1SC.Bits.CLKSA
#define TPM1SC_CLKSB                    _TPM1SC.Bits.CLKSB
#define TPM1SC_CPWMS                    _TPM1SC.Bits.CPWMS
#define TPM1SC_TOIE                     _TPM1SC.Bits.TOIE
#define TPM1SC_TOF                      _TPM1SC.Bits.TOF
#define TPM1SC_PS                       _TPM1SC.MergedBits.grpPS
#define TPM1SC_CLKSx                    _TPM1SC.MergedBits.grpCLKSx

#define TPM1SC_PS0_MASK                 1U
#define TPM1SC_PS1_MASK                 2U
#define TPM1SC_PS2_MASK                 4U
#define TPM1SC_CLKSA_MASK               8U
#define TPM1SC_CLKSB_MASK               16U
#define TPM1SC_CPWMS_MASK               32U
#define TPM1SC_TOIE_MASK                64U
#define TPM1SC_TOF_MASK                 128U
#define TPM1SC_PS_MASK                  7U
#define TPM1SC_PS_BITNUM                0U
#define TPM1SC_CLKSx_MASK               24U
#define TPM1SC_CLKSx_BITNUM             3U


/*** TPM1CNT - TPM1 Timer Counter Register; 0xFFFF98E1 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1CNTH - TPM1 Timer Counter Register High; 0xFFFF98E1 ***/
    union {
      byte Byte;
    } TPM1CNTHSTR;
    #define TPM1CNTH                    _TPM1CNT.Overlap_STR.TPM1CNTHSTR.Byte
    

    /*** TPM1CNTL - TPM1 Timer Counter Register Low; 0xFFFF98E2 ***/
    union {
      byte Byte;
    } TPM1CNTLSTR;
    #define TPM1CNTL                    _TPM1CNT.Overlap_STR.TPM1CNTLSTR.Byte
    
  } Overlap_STR;

} TPM1CNTSTR;
extern volatile TPM1CNTSTR _TPM1CNT @0xFFFF98E1;
#define TPM1CNT                         _TPM1CNT.Word


/*** TPM1MOD - TPM1 Timer Counter Modulo Register; 0xFFFF98E3 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1MODH - TPM1 Timer Counter Modulo Register High; 0xFFFF98E3 ***/
    union {
      byte Byte;
    } TPM1MODHSTR;
    #define TPM1MODH                    _TPM1MOD.Overlap_STR.TPM1MODHSTR.Byte
    

    /*** TPM1MODL - TPM1 Timer Counter Modulo Register Low; 0xFFFF98E4 ***/
    union {
      byte Byte;
    } TPM1MODLSTR;
    #define TPM1MODL                    _TPM1MOD.Overlap_STR.TPM1MODLSTR.Byte
    
  } Overlap_STR;

} TPM1MODSTR;
extern volatile TPM1MODSTR _TPM1MOD @0xFFFF98E3;
#define TPM1MOD                         _TPM1MOD.Word


/*** TPM1C0SC - TPM1 Timer Channel 0 Status and Control Register; 0xFFFF98E5 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C0SCSTR;
extern volatile TPM1C0SCSTR _TPM1C0SC @0xFFFF98E5;
#define TPM1C0SC                        _TPM1C0SC.Byte
#define TPM1C0SC_ELS0A                  _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELS0B                  _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MS0A                   _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MS0B                   _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CH0IE                  _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CH0F                   _TPM1C0SC.Bits.CH0F
#define TPM1C0SC_ELS0x                  _TPM1C0SC.MergedBits.grpELS0x
#define TPM1C0SC_MS0x                   _TPM1C0SC.MergedBits.grpMS0x

#define TPM1C0SC_ELS0A_MASK             4U
#define TPM1C0SC_ELS0B_MASK             8U
#define TPM1C0SC_MS0A_MASK              16U
#define TPM1C0SC_MS0B_MASK              32U
#define TPM1C0SC_CH0IE_MASK             64U
#define TPM1C0SC_CH0F_MASK              128U
#define TPM1C0SC_ELS0x_MASK             12U
#define TPM1C0SC_ELS0x_BITNUM           2U
#define TPM1C0SC_MS0x_MASK              48U
#define TPM1C0SC_MS0x_BITNUM            4U


/*** TPM1C0V - TPM1 Timer Channel 0 Value Register; 0xFFFF98E6 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C0VH - TPM1 Timer Channel 0 Value Register High; 0xFFFF98E6 ***/
    union {
      byte Byte;
    } TPM1C0VHSTR;
    #define TPM1C0VH                    _TPM1C0V.Overlap_STR.TPM1C0VHSTR.Byte
    

    /*** TPM1C0VL - TPM1 Timer Channel 0 Value Register Low; 0xFFFF98E7 ***/
    union {
      byte Byte;
    } TPM1C0VLSTR;
    #define TPM1C0VL                    _TPM1C0V.Overlap_STR.TPM1C0VLSTR.Byte
    
  } Overlap_STR;

} TPM1C0VSTR;
extern volatile TPM1C0VSTR _TPM1C0V @0xFFFF98E6;
#define TPM1C0V                         _TPM1C0V.Word


/*** TPM1C1SC - TPM1 Timer Channel 1 Status and Control Register; 0xFFFF98E8 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C1SCSTR;
extern volatile TPM1C1SCSTR _TPM1C1SC @0xFFFF98E8;
#define TPM1C1SC                        _TPM1C1SC.Byte
#define TPM1C1SC_ELS1A                  _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELS1B                  _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MS1A                   _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MS1B                   _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CH1IE                  _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CH1F                   _TPM1C1SC.Bits.CH1F
#define TPM1C1SC_ELS1x                  _TPM1C1SC.MergedBits.grpELS1x
#define TPM1C1SC_MS1x                   _TPM1C1SC.MergedBits.grpMS1x

#define TPM1C1SC_ELS1A_MASK             4U
#define TPM1C1SC_ELS1B_MASK             8U
#define TPM1C1SC_MS1A_MASK              16U
#define TPM1C1SC_MS1B_MASK              32U
#define TPM1C1SC_CH1IE_MASK             64U
#define TPM1C1SC_CH1F_MASK              128U
#define TPM1C1SC_ELS1x_MASK             12U
#define TPM1C1SC_ELS1x_BITNUM           2U
#define TPM1C1SC_MS1x_MASK              48U
#define TPM1C1SC_MS1x_BITNUM            4U


/*** TPM1C1V - TPM1 Timer Channel 1 Value Register; 0xFFFF98E9 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C1VH - TPM1 Timer Channel 1 Value Register High; 0xFFFF98E9 ***/
    union {
      byte Byte;
    } TPM1C1VHSTR;
    #define TPM1C1VH                    _TPM1C1V.Overlap_STR.TPM1C1VHSTR.Byte
    

    /*** TPM1C1VL - TPM1 Timer Channel 1 Value Register Low; 0xFFFF98EA ***/
    union {
      byte Byte;
    } TPM1C1VLSTR;
    #define TPM1C1VL                    _TPM1C1V.Overlap_STR.TPM1C1VLSTR.Byte
    
  } Overlap_STR;

} TPM1C1VSTR;
extern volatile TPM1C1VSTR _TPM1C1V @0xFFFF98E9;
#define TPM1C1V                         _TPM1C1V.Word


/*** TPM1C2SC - TPM1 Timer Channel 2 Status and Control Register; 0xFFFF98EB ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C2SCSTR;
extern volatile TPM1C2SCSTR _TPM1C2SC @0xFFFF98EB;
#define TPM1C2SC                        _TPM1C2SC.Byte
#define TPM1C2SC_ELS2A                  _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELS2B                  _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MS2A                   _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MS2B                   _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CH2IE                  _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CH2F                   _TPM1C2SC.Bits.CH2F
#define TPM1C2SC_ELS2x                  _TPM1C2SC.MergedBits.grpELS2x
#define TPM1C2SC_MS2x                   _TPM1C2SC.MergedBits.grpMS2x

#define TPM1C2SC_ELS2A_MASK             4U
#define TPM1C2SC_ELS2B_MASK             8U
#define TPM1C2SC_MS2A_MASK              16U
#define TPM1C2SC_MS2B_MASK              32U
#define TPM1C2SC_CH2IE_MASK             64U
#define TPM1C2SC_CH2F_MASK              128U
#define TPM1C2SC_ELS2x_MASK             12U
#define TPM1C2SC_ELS2x_BITNUM           2U
#define TPM1C2SC_MS2x_MASK              48U
#define TPM1C2SC_MS2x_BITNUM            4U


/*** TPM1C2V - TPM1 Timer Channel 2 Value Register; 0xFFFF98EC ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C2VH - TPM1 Timer Channel 2 Value Register High; 0xFFFF98EC ***/
    union {
      byte Byte;
    } TPM1C2VHSTR;
    #define TPM1C2VH                    _TPM1C2V.Overlap_STR.TPM1C2VHSTR.Byte
    

    /*** TPM1C2VL - TPM1 Timer Channel 2 Value Register Low; 0xFFFF98ED ***/
    union {
      byte Byte;
    } TPM1C2VLSTR;
    #define TPM1C2VL                    _TPM1C2V.Overlap_STR.TPM1C2VLSTR.Byte
    
  } Overlap_STR;

} TPM1C2VSTR;
extern volatile TPM1C2VSTR _TPM1C2V @0xFFFF98EC;
#define TPM1C2V                         _TPM1C2V.Word


/*** TPM1C3SC - TPM1 Timer Channel 3 Status and Control Register; 0xFFFF98EE ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS3A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS3B       :1;                                       /* Edge/Level Select Bit B */
    byte MS3A        :1;                                       /* Mode Select A for TPM Channel 3 */
    byte MS3B        :1;                                       /* Mode Select B for TPM Channel 3 */
    byte CH3IE       :1;                                       /* Channel 3 Interrupt Enable */
    byte CH3F        :1;                                       /* Channel 3 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS3x :2;
    byte grpMS3x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C3SCSTR;
extern volatile TPM1C3SCSTR _TPM1C3SC @0xFFFF98EE;
#define TPM1C3SC                        _TPM1C3SC.Byte
#define TPM1C3SC_ELS3A                  _TPM1C3SC.Bits.ELS3A
#define TPM1C3SC_ELS3B                  _TPM1C3SC.Bits.ELS3B
#define TPM1C3SC_MS3A                   _TPM1C3SC.Bits.MS3A
#define TPM1C3SC_MS3B                   _TPM1C3SC.Bits.MS3B
#define TPM1C3SC_CH3IE                  _TPM1C3SC.Bits.CH3IE
#define TPM1C3SC_CH3F                   _TPM1C3SC.Bits.CH3F
#define TPM1C3SC_ELS3x                  _TPM1C3SC.MergedBits.grpELS3x
#define TPM1C3SC_MS3x                   _TPM1C3SC.MergedBits.grpMS3x

#define TPM1C3SC_ELS3A_MASK             4U
#define TPM1C3SC_ELS3B_MASK             8U
#define TPM1C3SC_MS3A_MASK              16U
#define TPM1C3SC_MS3B_MASK              32U
#define TPM1C3SC_CH3IE_MASK             64U
#define TPM1C3SC_CH3F_MASK              128U
#define TPM1C3SC_ELS3x_MASK             12U
#define TPM1C3SC_ELS3x_BITNUM           2U
#define TPM1C3SC_MS3x_MASK              48U
#define TPM1C3SC_MS3x_BITNUM            4U


/*** TPM1C3V - TPM1 Timer Channel 3 Value Register; 0xFFFF98EF ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C3VH - TPM1 Timer Channel 3 Value Register High; 0xFFFF98EF ***/
    union {
      byte Byte;
    } TPM1C3VHSTR;
    #define TPM1C3VH                    _TPM1C3V.Overlap_STR.TPM1C3VHSTR.Byte
    

    /*** TPM1C3VL - TPM1 Timer Channel 3 Value Register Low; 0xFFFF98F0 ***/
    union {
      byte Byte;
    } TPM1C3VLSTR;
    #define TPM1C3VL                    _TPM1C3V.Overlap_STR.TPM1C3VLSTR.Byte
    
  } Overlap_STR;

} TPM1C3VSTR;
extern volatile TPM1C3VSTR _TPM1C3V @0xFFFF98EF;
#define TPM1C3V                         _TPM1C3V.Word


/*** ADCCV - Compare Value Register; 0xFFFF98F8 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCCVH - Compare Value High Register; 0xFFFF98F8 ***/
    union {
      byte Byte;
      struct {
        byte CV8         :1;                                       /* Compare Function Value Bit 8 */
        byte CV9         :1;                                       /* Compare Function Value Bit 9 */
        byte CV10        :1;                                       /* Compare Function Value Bit 10 */
        byte CV11        :1;                                       /* Compare Function Value Bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpCV_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCCVHSTR;
    #define ADCCVH                      _ADCCV.Overlap_STR.ADCCVHSTR.Byte
    #define ADCCVH_CV8                  _ADCCV.Overlap_STR.ADCCVHSTR.Bits.CV8
    #define ADCCVH_CV9                  _ADCCV.Overlap_STR.ADCCVHSTR.Bits.CV9
    #define ADCCVH_CV10                 _ADCCV.Overlap_STR.ADCCVHSTR.Bits.CV10
    #define ADCCVH_CV11                 _ADCCV.Overlap_STR.ADCCVHSTR.Bits.CV11
    #define ADCCVH_CV_8                 _ADCCV.Overlap_STR.ADCCVHSTR.MergedBits.grpCV_8
    #define ADCCVH_CV                   ADCCVH_CV_8
    
    #define ADCCVH_CV8_MASK             1U
    #define ADCCVH_CV9_MASK             2U
    #define ADCCVH_CV10_MASK            4U
    #define ADCCVH_CV11_MASK            8U
    #define ADCCVH_CV_8_MASK            15U
    #define ADCCVH_CV_8_BITNUM          0U
    

    /*** ADCCVL - Compare Value Low Register; 0xFFFF98F9 ***/
    union {
      byte Byte;
      struct {
        byte CV0         :1;                                       /* Compare Function Value 0 */
        byte CV1         :1;                                       /* Compare Function Value 1 */
        byte CV2         :1;                                       /* Compare Function Value 2 */
        byte CV3         :1;                                       /* Compare Function Value 3 */
        byte CV4         :1;                                       /* Compare Function Value 4 */
        byte CV5         :1;                                       /* Compare Function Value 5 */
        byte CV6         :1;                                       /* Compare Function Value 6 */
        byte CV7         :1;                                       /* Compare Function Value 7 */
      } Bits;
    } ADCCVLSTR;
    #define ADCCVL                      _ADCCV.Overlap_STR.ADCCVLSTR.Byte
    #define ADCCVL_CV0                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV0
    #define ADCCVL_CV1                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV1
    #define ADCCVL_CV2                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV2
    #define ADCCVL_CV3                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV3
    #define ADCCVL_CV4                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV4
    #define ADCCVL_CV5                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV5
    #define ADCCVL_CV6                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV6
    #define ADCCVL_CV7                  _ADCCV.Overlap_STR.ADCCVLSTR.Bits.CV7
    
    #define ADCCVL_CV0_MASK             1U
    #define ADCCVL_CV1_MASK             2U
    #define ADCCVL_CV2_MASK             4U
    #define ADCCVL_CV3_MASK             8U
    #define ADCCVL_CV4_MASK             16U
    #define ADCCVL_CV5_MASK             32U
    #define ADCCVL_CV6_MASK             64U
    #define ADCCVL_CV7_MASK             128U
    
  } Overlap_STR;

  struct {
    word CV0         :1;                                       /* Compare Function Value Bit 0 */
    word CV1         :1;                                       /* Compare Function Value Bit 1 */
    word CV2         :1;                                       /* Compare Function Value Bit 2 */
    word CV3         :1;                                       /* Compare Function Value Bit 3 */
    word CV4         :1;                                       /* Compare Function Value Bit 4 */
    word CV5         :1;                                       /* Compare Function Value Bit 5 */
    word CV6         :1;                                       /* Compare Function Value Bit 6 */
    word CV7         :1;                                       /* Compare Function Value Bit 7 */
    word CV8         :1;                                       /* Compare Function Value Bit 8 */
    word CV9         :1;                                       /* Compare Function Value Bit 9 */
    word CV10        :1;                                       /* Compare Function Value Bit 10 */
    word CV11        :1;                                       /* Compare Function Value Bit 11 */
    word             :1; 
    word             :1; 
    word             :1; 
    word             :1; 
  } Bits;
  struct {
    word grpCV   :12;
    word         :1;
    word         :1;
    word         :1;
    word         :1;
  } MergedBits;
} ADCCVSTR;
extern volatile ADCCVSTR _ADCCV @0xFFFF98F8;
#define ADCCV                           _ADCCV.Word
#define ADCCV_CV0                       _ADCCV.Bits.CV0
#define ADCCV_CV1                       _ADCCV.Bits.CV1
#define ADCCV_CV2                       _ADCCV.Bits.CV2
#define ADCCV_CV3                       _ADCCV.Bits.CV3
#define ADCCV_CV4                       _ADCCV.Bits.CV4
#define ADCCV_CV5                       _ADCCV.Bits.CV5
#define ADCCV_CV6                       _ADCCV.Bits.CV6
#define ADCCV_CV7                       _ADCCV.Bits.CV7
#define ADCCV_CV8                       _ADCCV.Bits.CV8
#define ADCCV_CV9                       _ADCCV.Bits.CV9
#define ADCCV_CV10                      _ADCCV.Bits.CV10
#define ADCCV_CV11                      _ADCCV.Bits.CV11
#define ADCCV_CV                        _ADCCV.MergedBits.grpCV

#define ADCCV_CV0_MASK                  1U
#define ADCCV_CV1_MASK                  2U
#define ADCCV_CV2_MASK                  4U
#define ADCCV_CV3_MASK                  8U
#define ADCCV_CV4_MASK                  16U
#define ADCCV_CV5_MASK                  32U
#define ADCCV_CV6_MASK                  64U
#define ADCCV_CV7_MASK                  128U
#define ADCCV_CV8_MASK                  256U
#define ADCCV_CV9_MASK                  512U
#define ADCCV_CV10_MASK                 1024U
#define ADCCV_CV11_MASK                 2048U
#define ADCCV_CV_MASK                   4095U
#define ADCCV_CV_BITNUM                 0U


/*** ADCSC2 - Status and Control Register 2; 0xFFFF98FC ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ACFGT       :1;                                       /* Compare Function Greater Than Enable */
    byte ACFE        :1;                                       /* Compare Function Enable - ACFE is used to enable the compare function */
    byte ADTRG       :1;                                       /* Conversion Trigger Select-ADTRG is used to select the type of trigger to be used for initiating a conversion */
    byte ADACT       :1;                                       /* Conversion Active - ADACT indicates that a conversion is in progress. ADACT is set when a conversion is initiated and cleared when a conversion is completed or aborted */
  } Bits;
} ADCSC2STR;
extern volatile ADCSC2STR _ADCSC2 @0xFFFF98FC;
#define ADCSC2                          _ADCSC2.Byte
#define ADCSC2_ACFGT                    _ADCSC2.Bits.ACFGT
#define ADCSC2_ACFE                     _ADCSC2.Bits.ACFE
#define ADCSC2_ADTRG                    _ADCSC2.Bits.ADTRG
#define ADCSC2_ADACT                    _ADCSC2.Bits.ADACT

#define ADCSC2_ACFGT_MASK               16U
#define ADCSC2_ACFE_MASK                32U
#define ADCSC2_ADTRG_MASK               64U
#define ADCSC2_ADACT_MASK               128U


/*** ADCSC3 - Status and Control Register 3; 0xFFFF98FD ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ADCO        :1;                                       /* Continuous Conversion Enable - ADCO enables continuous conversions */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} ADCSC3STR;
extern volatile ADCSC3STR _ADCSC3 @0xFFFF98FD;
#define ADCSC3                          _ADCSC3.Byte
#define ADCSC3_ADCO                     _ADCSC3.Bits.ADCO

#define ADCSC3_ADCO_MASK                8U


/*** APCTL1 - Pin Control 1 Register; 0xFFFF9917 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC0       :1;                                       /* ADC Pin Control 0 - ADPC0 is used to control the pin associated with channel AD0 */
    byte ADPC1       :1;                                       /* ADC Pin Control 1 - ADPC1 is used to control the pin associated with channel AD1 */
    byte ADPC2       :1;                                       /* ADC Pin Control 2 - ADPC2 is used to control the pin associated with channel AD2 */
    byte ADPC3       :1;                                       /* ADC Pin Control 3 - ADPC3 is used to control the pin associated with channel AD3 */
    byte ADPC4       :1;                                       /* ADC Pin Control 4 - ADPC4 is used to control the pin associated with channel AD4 */
    byte ADPC5       :1;                                       /* ADC Pin Control 5 - ADPC5 is used to control the pin associated with channel AD5 */
    byte ADPC6       :1;                                       /* ADC Pin Control 6 - ADPC6 is used to control the pin associated with channel AD6 */
    byte ADPC7       :1;                                       /* ADC Pin Control 7 - ADPC7 is used to control the pin associated with channel AD7 */
  } Bits;
} APCTL1STR;
extern volatile APCTL1STR _APCTL1 @0xFFFF9917;
#define APCTL1                          _APCTL1.Byte
#define APCTL1_ADPC0                    _APCTL1.Bits.ADPC0
#define APCTL1_ADPC1                    _APCTL1.Bits.ADPC1
#define APCTL1_ADPC2                    _APCTL1.Bits.ADPC2
#define APCTL1_ADPC3                    _APCTL1.Bits.ADPC3
#define APCTL1_ADPC4                    _APCTL1.Bits.ADPC4
#define APCTL1_ADPC5                    _APCTL1.Bits.ADPC5
#define APCTL1_ADPC6                    _APCTL1.Bits.ADPC6
#define APCTL1_ADPC7                    _APCTL1.Bits.ADPC7

#define APCTL1_ADPC0_MASK               1U
#define APCTL1_ADPC1_MASK               2U
#define APCTL1_ADPC2_MASK               4U
#define APCTL1_ADPC3_MASK               8U
#define APCTL1_ADPC4_MASK               16U
#define APCTL1_ADPC5_MASK               32U
#define APCTL1_ADPC6_MASK               64U
#define APCTL1_ADPC7_MASK               128U


/*** APCTL2 - Pin Control 2 Register; 0xFFFF9918 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC8       :1;                                       /* ADC Pin Control 8 - ADPC8 is used to control the pin associated with channel AD8 */
    byte ADPC9       :1;                                       /* ADC Pin Control 9 - ADPC9 is used to control the pin associated with channel AD9 */
    byte ADPC10      :1;                                       /* ADC Pin Control 10 - ADPC10 is used to control the pin associated with channel AD10 */
    byte ADPC11      :1;                                       /* ADC Pin Control 11 - ADPC11 is used to control the pin associated with channel AD11 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpADPC_8 :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} APCTL2STR;
extern volatile APCTL2STR _APCTL2 @0xFFFF9918;
#define APCTL2                          _APCTL2.Byte
#define APCTL2_ADPC8                    _APCTL2.Bits.ADPC8
#define APCTL2_ADPC9                    _APCTL2.Bits.ADPC9
#define APCTL2_ADPC10                   _APCTL2.Bits.ADPC10
#define APCTL2_ADPC11                   _APCTL2.Bits.ADPC11
#define APCTL2_ADPC_8                   _APCTL2.MergedBits.grpADPC_8
#define APCTL2_ADPC                     APCTL2_ADPC_8

#define APCTL2_ADPC8_MASK               1U
#define APCTL2_ADPC9_MASK               2U
#define APCTL2_ADPC10_MASK              4U
#define APCTL2_ADPC11_MASK              8U
#define APCTL2_ADPC_8_MASK              15U
#define APCTL2_ADPC_8_BITNUM            0U


/*** F1CDIV - FLASH Clock Divider Register; 0xFFFF9920 ***/
typedef union {
  byte Byte;
  struct {
    byte FDIV0       :1;                                       /* Divisor for FLASH Clock Divider, bit 0 */
    byte FDIV1       :1;                                       /* Divisor for FLASH Clock Divider, bit 1 */
    byte FDIV2       :1;                                       /* Divisor for FLASH Clock Divider, bit 2 */
    byte FDIV3       :1;                                       /* Divisor for FLASH Clock Divider, bit 3 */
    byte FDIV4       :1;                                       /* Divisor for FLASH Clock Divider, bit 4 */
    byte FDIV5       :1;                                       /* Divisor for FLASH Clock Divider, bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte FDIVLD      :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpFDIV :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} F1CDIVSTR;
extern volatile F1CDIVSTR _F1CDIV @0xFFFF9920;
#define F1CDIV                          _F1CDIV.Byte
#define F1CDIV_FDIV0                    _F1CDIV.Bits.FDIV0
#define F1CDIV_FDIV1                    _F1CDIV.Bits.FDIV1
#define F1CDIV_FDIV2                    _F1CDIV.Bits.FDIV2
#define F1CDIV_FDIV3                    _F1CDIV.Bits.FDIV3
#define F1CDIV_FDIV4                    _F1CDIV.Bits.FDIV4
#define F1CDIV_FDIV5                    _F1CDIV.Bits.FDIV5
#define F1CDIV_PRDIV8                   _F1CDIV.Bits.PRDIV8
#define F1CDIV_FDIVLD                   _F1CDIV.Bits.FDIVLD
#define F1CDIV_FDIV                     _F1CDIV.MergedBits.grpFDIV

#define F1CDIV_FDIV0_MASK               1U
#define F1CDIV_FDIV1_MASK               2U
#define F1CDIV_FDIV2_MASK               4U
#define F1CDIV_FDIV3_MASK               8U
#define F1CDIV_FDIV4_MASK               16U
#define F1CDIV_FDIV5_MASK               32U
#define F1CDIV_PRDIV8_MASK              64U
#define F1CDIV_FDIVLD_MASK              128U
#define F1CDIV_FDIV_MASK                63U
#define F1CDIV_FDIV_BITNUM              0U


/*** F1OPT - Flash Options Register; 0xFFFF9921 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} F1OPTSTR;
extern volatile F1OPTSTR _F1OPT @0xFFFF9921;
#define F1OPT                           _F1OPT.Byte
#define F1OPT_SEC0                      _F1OPT.Bits.SEC0
#define F1OPT_SEC1                      _F1OPT.Bits.SEC1
#define F1OPT_KEYEN0                    _F1OPT.Bits.KEYEN0
#define F1OPT_KEYEN1                    _F1OPT.Bits.KEYEN1
#define F1OPT_SEC                       _F1OPT.MergedBits.grpSEC
#define F1OPT_KEYEN                     _F1OPT.MergedBits.grpKEYEN

#define F1OPT_SEC0_MASK                 1U
#define F1OPT_SEC1_MASK                 2U
#define F1OPT_KEYEN0_MASK               64U
#define F1OPT_KEYEN1_MASK               128U
#define F1OPT_SEC_MASK                  3U
#define F1OPT_SEC_BITNUM                0U
#define F1OPT_KEYEN_MASK                192U
#define F1OPT_KEYEN_BITNUM              6U


/*** F1CNFG - Flash Configuration Register; 0xFFFF9923 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYACC      :1;                                       /* Enable Security Key Writing */
    byte CCIE        :1;                                       /* Command Complete Interrupt Enable */
    byte CBEIE       :1;                                       /* Command Buffer Empty Interrupt Enable */
  } Bits;
} F1CNFGSTR;
extern volatile F1CNFGSTR _F1CNFG @0xFFFF9923;
#define F1CNFG                          _F1CNFG.Byte
#define F1CNFG_KEYACC                   _F1CNFG.Bits.KEYACC
#define F1CNFG_CCIE                     _F1CNFG.Bits.CCIE
#define F1CNFG_CBEIE                    _F1CNFG.Bits.CBEIE

#define F1CNFG_KEYACC_MASK              32U
#define F1CNFG_CCIE_MASK                64U
#define F1CNFG_CBEIE_MASK               128U


/*** F1PROT - Flash Protection Register; 0xFFFF9924 ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} F1PROTSTR;
extern volatile F1PROTSTR _F1PROT @0xFFFF9924;
#define F1PROT                          _F1PROT.Byte
#define F1PROT_FPOPEN                   _F1PROT.Bits.FPOPEN
#define F1PROT_FPS0                     _F1PROT.Bits.FPS0
#define F1PROT_FPS1                     _F1PROT.Bits.FPS1
#define F1PROT_FPS2                     _F1PROT.Bits.FPS2
#define F1PROT_FPS3                     _F1PROT.Bits.FPS3
#define F1PROT_FPS4                     _F1PROT.Bits.FPS4
#define F1PROT_FPS5                     _F1PROT.Bits.FPS5
#define F1PROT_FPS6                     _F1PROT.Bits.FPS6
#define F1PROT_FPS                      _F1PROT.MergedBits.grpFPS

#define F1PROT_FPOPEN_MASK              1U
#define F1PROT_FPS0_MASK                2U
#define F1PROT_FPS1_MASK                4U
#define F1PROT_FPS2_MASK                8U
#define F1PROT_FPS3_MASK                16U
#define F1PROT_FPS4_MASK                32U
#define F1PROT_FPS5_MASK                64U
#define F1PROT_FPS6_MASK                128U
#define F1PROT_FPS_MASK                 254U
#define F1PROT_FPS_BITNUM               1U


/*** F1STAT - Flash Status Register; 0xFFFF9925 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte FBLANK      :1;                                       /* FLASH Flag Indicating the Erase Verify Operation Status */
    byte             :1; 
    byte FACCERR     :1;                                       /* FLASH Access Error Flag */
    byte FPVIOL      :1;                                       /* FLASH Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Interrupt Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} F1STATSTR;
extern volatile F1STATSTR _F1STAT @0xFFFF9925;
#define F1STAT                          _F1STAT.Byte
#define F1STAT_FBLANK                   _F1STAT.Bits.FBLANK
#define F1STAT_FACCERR                  _F1STAT.Bits.FACCERR
#define F1STAT_FPVIOL                   _F1STAT.Bits.FPVIOL
#define F1STAT_FCCF                     _F1STAT.Bits.FCCF
#define F1STAT_FCBEF                    _F1STAT.Bits.FCBEF

#define F1STAT_FBLANK_MASK              4U
#define F1STAT_FACCERR_MASK             16U
#define F1STAT_FPVIOL_MASK              32U
#define F1STAT_FCCF_MASK                64U
#define F1STAT_FCBEF_MASK               128U


/*** F1CMD - Flash Command Register; 0xFFFF9926 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* Flash Command, bit 0 */
    byte FCMD1       :1;                                       /* Flash Command, bit 1 */
    byte FCMD2       :1;                                       /* Flash Command, bit 2 */
    byte FCMD3       :1;                                       /* Flash Command, bit 3 */
    byte FCMD4       :1;                                       /* Flash Command, bit 4 */
    byte FCMD5       :1;                                       /* Flash Command, bit 5 */
    byte FCMD6       :1;                                       /* Flash Command, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpFCMD :7;
    byte         :1;
  } MergedBits;
} F1CMDSTR;
extern volatile F1CMDSTR _F1CMD @0xFFFF9926;
#define F1CMD                           _F1CMD.Byte
#define F1CMD_FCMD0                     _F1CMD.Bits.FCMD0
#define F1CMD_FCMD1                     _F1CMD.Bits.FCMD1
#define F1CMD_FCMD2                     _F1CMD.Bits.FCMD2
#define F1CMD_FCMD3                     _F1CMD.Bits.FCMD3
#define F1CMD_FCMD4                     _F1CMD.Bits.FCMD4
#define F1CMD_FCMD5                     _F1CMD.Bits.FCMD5
#define F1CMD_FCMD6                     _F1CMD.Bits.FCMD6
#define F1CMD_FCMD                      _F1CMD.MergedBits.grpFCMD

#define F1CMD_FCMD0_MASK                1U
#define F1CMD_FCMD1_MASK                2U
#define F1CMD_FCMD2_MASK                4U
#define F1CMD_FCMD3_MASK                8U
#define F1CMD_FCMD4_MASK                16U
#define F1CMD_FCMD5_MASK                32U
#define F1CMD_FCMD6_MASK                64U
#define F1CMD_FCMD_MASK                 127U
#define F1CMD_FCMD_BITNUM               0U


/*** F2CDIV - FLASH Clock Divider Register; 0xFFFF9930 ***/
typedef union {
  byte Byte;
  struct {
    byte FDIV0       :1;                                       /* Divisor for FLASH Clock Divider, bit 0 */
    byte FDIV1       :1;                                       /* Divisor for FLASH Clock Divider, bit 1 */
    byte FDIV2       :1;                                       /* Divisor for FLASH Clock Divider, bit 2 */
    byte FDIV3       :1;                                       /* Divisor for FLASH Clock Divider, bit 3 */
    byte FDIV4       :1;                                       /* Divisor for FLASH Clock Divider, bit 4 */
    byte FDIV5       :1;                                       /* Divisor for FLASH Clock Divider, bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte FDIVLD      :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpFDIV :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} F2CDIVSTR;
extern volatile F2CDIVSTR _F2CDIV @0xFFFF9930;
#define F2CDIV                          _F2CDIV.Byte
#define F2CDIV_FDIV0                    _F2CDIV.Bits.FDIV0
#define F2CDIV_FDIV1                    _F2CDIV.Bits.FDIV1
#define F2CDIV_FDIV2                    _F2CDIV.Bits.FDIV2
#define F2CDIV_FDIV3                    _F2CDIV.Bits.FDIV3
#define F2CDIV_FDIV4                    _F2CDIV.Bits.FDIV4
#define F2CDIV_FDIV5                    _F2CDIV.Bits.FDIV5
#define F2CDIV_PRDIV8                   _F2CDIV.Bits.PRDIV8
#define F2CDIV_FDIVLD                   _F2CDIV.Bits.FDIVLD
#define F2CDIV_FDIV                     _F2CDIV.MergedBits.grpFDIV

#define F2CDIV_FDIV0_MASK               1U
#define F2CDIV_FDIV1_MASK               2U
#define F2CDIV_FDIV2_MASK               4U
#define F2CDIV_FDIV3_MASK               8U
#define F2CDIV_FDIV4_MASK               16U
#define F2CDIV_FDIV5_MASK               32U
#define F2CDIV_PRDIV8_MASK              64U
#define F2CDIV_FDIVLD_MASK              128U
#define F2CDIV_FDIV_MASK                63U
#define F2CDIV_FDIV_BITNUM              0U


/*** F2OPT - Flash Options Register; 0xFFFF9931 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} F2OPTSTR;
extern volatile F2OPTSTR _F2OPT @0xFFFF9931;
#define F2OPT                           _F2OPT.Byte
#define F2OPT_SEC0                      _F2OPT.Bits.SEC0
#define F2OPT_SEC1                      _F2OPT.Bits.SEC1
#define F2OPT_KEYEN0                    _F2OPT.Bits.KEYEN0
#define F2OPT_KEYEN1                    _F2OPT.Bits.KEYEN1
#define F2OPT_SEC                       _F2OPT.MergedBits.grpSEC
#define F2OPT_KEYEN                     _F2OPT.MergedBits.grpKEYEN

#define F2OPT_SEC0_MASK                 1U
#define F2OPT_SEC1_MASK                 2U
#define F2OPT_KEYEN0_MASK               64U
#define F2OPT_KEYEN1_MASK               128U
#define F2OPT_SEC_MASK                  3U
#define F2OPT_SEC_BITNUM                0U
#define F2OPT_KEYEN_MASK                192U
#define F2OPT_KEYEN_BITNUM              6U


/*** F2CNFG - Flash Configuration Register; 0xFFFF9933 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYACC      :1;                                       /* Enable Security Key Writing */
    byte CCIE        :1;                                       /* Command Complete Interrupt Enable */
    byte CBEIE       :1;                                       /* Command Buffer Empty Interrupt Enable */
  } Bits;
} F2CNFGSTR;
extern volatile F2CNFGSTR _F2CNFG @0xFFFF9933;
#define F2CNFG                          _F2CNFG.Byte
#define F2CNFG_KEYACC                   _F2CNFG.Bits.KEYACC
#define F2CNFG_CCIE                     _F2CNFG.Bits.CCIE
#define F2CNFG_CBEIE                    _F2CNFG.Bits.CBEIE

#define F2CNFG_KEYACC_MASK              32U
#define F2CNFG_CCIE_MASK                64U
#define F2CNFG_CBEIE_MASK               128U


/*** F2PROT - Flash Protection Register; 0xFFFF9934 ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} F2PROTSTR;
extern volatile F2PROTSTR _F2PROT @0xFFFF9934;
#define F2PROT                          _F2PROT.Byte
#define F2PROT_FPOPEN                   _F2PROT.Bits.FPOPEN
#define F2PROT_FPS0                     _F2PROT.Bits.FPS0
#define F2PROT_FPS1                     _F2PROT.Bits.FPS1
#define F2PROT_FPS2                     _F2PROT.Bits.FPS2
#define F2PROT_FPS3                     _F2PROT.Bits.FPS3
#define F2PROT_FPS4                     _F2PROT.Bits.FPS4
#define F2PROT_FPS5                     _F2PROT.Bits.FPS5
#define F2PROT_FPS6                     _F2PROT.Bits.FPS6
#define F2PROT_FPS                      _F2PROT.MergedBits.grpFPS

#define F2PROT_FPOPEN_MASK              1U
#define F2PROT_FPS0_MASK                2U
#define F2PROT_FPS1_MASK                4U
#define F2PROT_FPS2_MASK                8U
#define F2PROT_FPS3_MASK                16U
#define F2PROT_FPS4_MASK                32U
#define F2PROT_FPS5_MASK                64U
#define F2PROT_FPS6_MASK                128U
#define F2PROT_FPS_MASK                 254U
#define F2PROT_FPS_BITNUM               1U


/*** F2STAT - Flash Status Register; 0xFFFF9935 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte FBLANK      :1;                                       /* FLASH Flag Indicating the Erase Verify Operation Status */
    byte             :1; 
    byte FACCERR     :1;                                       /* FLASH Access Error Flag */
    byte FPVIOL      :1;                                       /* FLASH Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Interrupt Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} F2STATSTR;
extern volatile F2STATSTR _F2STAT @0xFFFF9935;
#define F2STAT                          _F2STAT.Byte
#define F2STAT_FBLANK                   _F2STAT.Bits.FBLANK
#define F2STAT_FACCERR                  _F2STAT.Bits.FACCERR
#define F2STAT_FPVIOL                   _F2STAT.Bits.FPVIOL
#define F2STAT_FCCF                     _F2STAT.Bits.FCCF
#define F2STAT_FCBEF                    _F2STAT.Bits.FCBEF

#define F2STAT_FBLANK_MASK              4U
#define F2STAT_FACCERR_MASK             16U
#define F2STAT_FPVIOL_MASK              32U
#define F2STAT_FCCF_MASK                64U
#define F2STAT_FCBEF_MASK               128U


/*** F2CMD - Flash Command Register; 0xFFFF9936 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* Flash Command, bit 0 */
    byte FCMD1       :1;                                       /* Flash Command, bit 1 */
    byte FCMD2       :1;                                       /* Flash Command, bit 2 */
    byte FCMD3       :1;                                       /* Flash Command, bit 3 */
    byte FCMD4       :1;                                       /* Flash Command, bit 4 */
    byte FCMD5       :1;                                       /* Flash Command, bit 5 */
    byte FCMD6       :1;                                       /* Flash Command, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpFCMD :7;
    byte         :1;
  } MergedBits;
} F2CMDSTR;
extern volatile F2CMDSTR _F2CMD @0xFFFF9936;
#define F2CMD                           _F2CMD.Byte
#define F2CMD_FCMD0                     _F2CMD.Bits.FCMD0
#define F2CMD_FCMD1                     _F2CMD.Bits.FCMD1
#define F2CMD_FCMD2                     _F2CMD.Bits.FCMD2
#define F2CMD_FCMD3                     _F2CMD.Bits.FCMD3
#define F2CMD_FCMD4                     _F2CMD.Bits.FCMD4
#define F2CMD_FCMD5                     _F2CMD.Bits.FCMD5
#define F2CMD_FCMD6                     _F2CMD.Bits.FCMD6
#define F2CMD_FCMD                      _F2CMD.MergedBits.grpFCMD

#define F2CMD_FCMD0_MASK                1U
#define F2CMD_FCMD1_MASK                2U
#define F2CMD_FCMD2_MASK                4U
#define F2CMD_FCMD3_MASK                8U
#define F2CMD_FCMD4_MASK                16U
#define F2CMD_FCMD5_MASK                32U
#define F2CMD_FCMD6_MASK                64U
#define F2CMD_FCMD_MASK                 127U
#define F2CMD_FCMD_BITNUM               0U


/*** PTHD - Port H Data Register; 0xFFFF9940 ***/
typedef union {
  byte Byte;
  struct {
    byte PTHD0       :1;                                       /* Port H Data Register Bit 0 */
    byte PTHD1       :1;                                       /* Port H Data Register Bit 1 */
    byte PTHD2       :1;                                       /* Port H Data Register Bit 2 */
    byte PTHD3       :1;                                       /* Port H Data Register Bit 3 */
    byte PTHD4       :1;                                       /* Port H Data Register Bit 4 */
    byte PTHD5       :1;                                       /* Port H Data Register Bit 5 */
    byte PTHD6       :1;                                       /* Port H Data Register Bit 6 */
    byte PTHD7       :1;                                       /* Port H Data Register Bit 7 */
  } Bits;
} PTHDSTR;
extern volatile PTHDSTR _PTHD @0xFFFF9940;
#define PTHD                            _PTHD.Byte
#define PTHD_PTHD0                      _PTHD.Bits.PTHD0
#define PTHD_PTHD1                      _PTHD.Bits.PTHD1
#define PTHD_PTHD2                      _PTHD.Bits.PTHD2
#define PTHD_PTHD3                      _PTHD.Bits.PTHD3
#define PTHD_PTHD4                      _PTHD.Bits.PTHD4
#define PTHD_PTHD5                      _PTHD.Bits.PTHD5
#define PTHD_PTHD6                      _PTHD.Bits.PTHD6
#define PTHD_PTHD7                      _PTHD.Bits.PTHD7

#define PTHD_PTHD0_MASK                 1U
#define PTHD_PTHD1_MASK                 2U
#define PTHD_PTHD2_MASK                 4U
#define PTHD_PTHD3_MASK                 8U
#define PTHD_PTHD4_MASK                 16U
#define PTHD_PTHD5_MASK                 32U
#define PTHD_PTHD6_MASK                 64U
#define PTHD_PTHD7_MASK                 128U


/*** PTHDD - Port H Data Direction Register; 0xFFFF9941 ***/
typedef union {
  byte Byte;
  struct {
    byte PTHDD0      :1;                                       /* Data Direction for Port H Bit 0 */
    byte PTHDD1      :1;                                       /* Data Direction for Port H Bit 1 */
    byte PTHDD2      :1;                                       /* Data Direction for Port H Bit 2 */
    byte PTHDD3      :1;                                       /* Data Direction for Port H Bit 3 */
    byte PTHDD4      :1;                                       /* Data Direction for Port H Bit 4 */
    byte PTHDD5      :1;                                       /* Data Direction for Port H Bit 5 */
    byte PTHDD6      :1;                                       /* Data Direction for Port H Bit 6 */
    byte PTHDD7      :1;                                       /* Data Direction for Port H Bit 7 */
  } Bits;
} PTHDDSTR;
extern volatile PTHDDSTR _PTHDD @0xFFFF9941;
#define PTHDD                           _PTHDD.Byte
#define PTHDD_PTHDD0                    _PTHDD.Bits.PTHDD0
#define PTHDD_PTHDD1                    _PTHDD.Bits.PTHDD1
#define PTHDD_PTHDD2                    _PTHDD.Bits.PTHDD2
#define PTHDD_PTHDD3                    _PTHDD.Bits.PTHDD3
#define PTHDD_PTHDD4                    _PTHDD.Bits.PTHDD4
#define PTHDD_PTHDD5                    _PTHDD.Bits.PTHDD5
#define PTHDD_PTHDD6                    _PTHDD.Bits.PTHDD6
#define PTHDD_PTHDD7                    _PTHDD.Bits.PTHDD7

#define PTHDD_PTHDD0_MASK               1U
#define PTHDD_PTHDD1_MASK               2U
#define PTHDD_PTHDD2_MASK               4U
#define PTHDD_PTHDD3_MASK               8U
#define PTHDD_PTHDD4_MASK               16U
#define PTHDD_PTHDD5_MASK               32U
#define PTHDD_PTHDD6_MASK               64U
#define PTHDD_PTHDD7_MASK               128U


/*** PTJD - Port J Data Register; 0xFFFF9942 ***/
typedef union {
  byte Byte;
  struct {
    byte PTJD0       :1;                                       /* Port J Data Register Bit 0 */
    byte PTJD1       :1;                                       /* Port J Data Register Bit 1 */
    byte PTJD2       :1;                                       /* Port J Data Register Bit 2 */
    byte PTJD3       :1;                                       /* Port J Data Register Bit 3 */
    byte PTJD4       :1;                                       /* Port J Data Register Bit 4 */
    byte PTJD5       :1;                                       /* Port J Data Register Bit 5 */
    byte PTJD6       :1;                                       /* Port J Data Register Bit 6 */
    byte PTJD7       :1;                                       /* Port J Data Register Bit 7 */
  } Bits;
} PTJDSTR;
extern volatile PTJDSTR _PTJD @0xFFFF9942;
#define PTJD                            _PTJD.Byte
#define PTJD_PTJD0                      _PTJD.Bits.PTJD0
#define PTJD_PTJD1                      _PTJD.Bits.PTJD1
#define PTJD_PTJD2                      _PTJD.Bits.PTJD2
#define PTJD_PTJD3                      _PTJD.Bits.PTJD3
#define PTJD_PTJD4                      _PTJD.Bits.PTJD4
#define PTJD_PTJD5                      _PTJD.Bits.PTJD5
#define PTJD_PTJD6                      _PTJD.Bits.PTJD6
#define PTJD_PTJD7                      _PTJD.Bits.PTJD7

#define PTJD_PTJD0_MASK                 1U
#define PTJD_PTJD1_MASK                 2U
#define PTJD_PTJD2_MASK                 4U
#define PTJD_PTJD3_MASK                 8U
#define PTJD_PTJD4_MASK                 16U
#define PTJD_PTJD5_MASK                 32U
#define PTJD_PTJD6_MASK                 64U
#define PTJD_PTJD7_MASK                 128U


/*** PTJDD - Port J Data Direction Register; 0xFFFF9943 ***/
typedef union {
  byte Byte;
  struct {
    byte PTJDD0      :1;                                       /* Data Direction for Port J Bit 0 */
    byte PTJDD1      :1;                                       /* Data Direction for Port J Bit 1 */
    byte PTJDD2      :1;                                       /* Data Direction for Port J Bit 2 */
    byte PTJDD3      :1;                                       /* Data Direction for Port J Bit 3 */
    byte PTJDD4      :1;                                       /* Data Direction for Port J Bit 4 */
    byte PTJDD5      :1;                                       /* Data Direction for Port J Bit 5 */
    byte PTJDD6      :1;                                       /* Data Direction for Port J Bit 6 */
    byte PTJDD7      :1;                                       /* Data Direction for Port J Bit 7 */
  } Bits;
} PTJDDSTR;
extern volatile PTJDDSTR _PTJDD @0xFFFF9943;
#define PTJDD                           _PTJDD.Byte
#define PTJDD_PTJDD0                    _PTJDD.Bits.PTJDD0
#define PTJDD_PTJDD1                    _PTJDD.Bits.PTJDD1
#define PTJDD_PTJDD2                    _PTJDD.Bits.PTJDD2
#define PTJDD_PTJDD3                    _PTJDD.Bits.PTJDD3
#define PTJDD_PTJDD4                    _PTJDD.Bits.PTJDD4
#define PTJDD_PTJDD5                    _PTJDD.Bits.PTJDD5
#define PTJDD_PTJDD6                    _PTJDD.Bits.PTJDD6
#define PTJDD_PTJDD7                    _PTJDD.Bits.PTJDD7

#define PTJDD_PTJDD0_MASK               1U
#define PTJDD_PTJDD1_MASK               2U
#define PTJDD_PTJDD2_MASK               4U
#define PTJDD_PTJDD3_MASK               8U
#define PTJDD_PTJDD4_MASK               16U
#define PTJDD_PTJDD5_MASK               32U
#define PTJDD_PTJDD6_MASK               64U
#define PTJDD_PTJDD7_MASK               128U


/*** PTHPE - Port H Pull Enable Register; 0xFFFF9948 ***/
typedef union {
  byte Byte;
  struct {
    byte PTHPE0      :1;                                       /* Internal Pull Enable for Port H Bit 0 */
    byte PTHPE1      :1;                                       /* Internal Pull Enable for Port H Bit 1 */
    byte PTHPE2      :1;                                       /* Internal Pull Enable for Port H Bit 2 */
    byte PTHPE3      :1;                                       /* Internal Pull Enable for Port H Bit 3 */
    byte PTHPE4      :1;                                       /* Internal Pull Enable for Port H Bit 4 */
    byte PTHPE5      :1;                                       /* Internal Pull Enable for Port H Bit 5 */
    byte PTHPE6      :1;                                       /* Internal Pull Enable for Port H Bit 6 */
    byte PTHPE7      :1;                                       /* Internal Pull Enable for Port H Bit 7 */
  } Bits;
} PTHPESTR;
extern volatile PTHPESTR _PTHPE @0xFFFF9948;
#define PTHPE                           _PTHPE.Byte
#define PTHPE_PTHPE0                    _PTHPE.Bits.PTHPE0
#define PTHPE_PTHPE1                    _PTHPE.Bits.PTHPE1
#define PTHPE_PTHPE2                    _PTHPE.Bits.PTHPE2
#define PTHPE_PTHPE3                    _PTHPE.Bits.PTHPE3
#define PTHPE_PTHPE4                    _PTHPE.Bits.PTHPE4
#define PTHPE_PTHPE5                    _PTHPE.Bits.PTHPE5
#define PTHPE_PTHPE6                    _PTHPE.Bits.PTHPE6
#define PTHPE_PTHPE7                    _PTHPE.Bits.PTHPE7

#define PTHPE_PTHPE0_MASK               1U
#define PTHPE_PTHPE1_MASK               2U
#define PTHPE_PTHPE2_MASK               4U
#define PTHPE_PTHPE3_MASK               8U
#define PTHPE_PTHPE4_MASK               16U
#define PTHPE_PTHPE5_MASK               32U
#define PTHPE_PTHPE6_MASK               64U
#define PTHPE_PTHPE7_MASK               128U


/*** PTHSE - Port H Slew Rate Enable Register; 0xFFFF9949 ***/
typedef union {
  byte Byte;
  struct {
    byte PTHSE0      :1;                                       /* Output Slew Rate Enable for Port H Bit 0 */
    byte PTHSE1      :1;                                       /* Output Slew Rate Enable for Port H Bit 1 */
    byte PTHSE2      :1;                                       /* Output Slew Rate Enable for Port H Bit 2 */
    byte PTHSE3      :1;                                       /* Output Slew Rate Enable for Port H Bit 3 */
    byte PTHSE4      :1;                                       /* Output Slew Rate Enable for Port H Bit 4 */
    byte PTHSE5      :1;                                       /* Output Slew Rate Enable for Port H Bit 5 */
    byte PTHSE6      :1;                                       /* Output Slew Rate Enable for Port H Bit 6 */
    byte PTHSE7      :1;                                       /* Output Slew Rate Enable for Port H Bit 7 */
  } Bits;
} PTHSESTR;
extern volatile PTHSESTR _PTHSE @0xFFFF9949;
#define PTHSE                           _PTHSE.Byte
#define PTHSE_PTHSE0                    _PTHSE.Bits.PTHSE0
#define PTHSE_PTHSE1                    _PTHSE.Bits.PTHSE1
#define PTHSE_PTHSE2                    _PTHSE.Bits.PTHSE2
#define PTHSE_PTHSE3                    _PTHSE.Bits.PTHSE3
#define PTHSE_PTHSE4                    _PTHSE.Bits.PTHSE4
#define PTHSE_PTHSE5                    _PTHSE.Bits.PTHSE5
#define PTHSE_PTHSE6                    _PTHSE.Bits.PTHSE6
#define PTHSE_PTHSE7                    _PTHSE.Bits.PTHSE7

#define PTHSE_PTHSE0_MASK               1U
#define PTHSE_PTHSE1_MASK               2U
#define PTHSE_PTHSE2_MASK               4U
#define PTHSE_PTHSE3_MASK               8U
#define PTHSE_PTHSE4_MASK               16U
#define PTHSE_PTHSE5_MASK               32U
#define PTHSE_PTHSE6_MASK               64U
#define PTHSE_PTHSE7_MASK               128U


/*** PTHDS - Port H Drive Strength Selection Register; 0xFFFF994A ***/
typedef union {
  byte Byte;
  struct {
    byte PTHDS0      :1;                                       /* Output Drive Strength Selection for Port H Bit 0 */
    byte PTHDS1      :1;                                       /* Output Drive Strength Selection for Port H Bit 1 */
    byte PTHDS2      :1;                                       /* Output Drive Strength Selection for Port H Bit 2 */
    byte PTHDS3      :1;                                       /* Output Drive Strength Selection for Port H Bit 3 */
    byte PTHDS4      :1;                                       /* Output Drive Strength Selection for Port H Bit 4 */
    byte PTHDS5      :1;                                       /* Output Drive Strength Selection for Port H Bit 5 */
    byte PTHDS6      :1;                                       /* Output Drive Strength Selection for Port H Bit 6 */
    byte PTHDS7      :1;                                       /* Output Drive Strength Selection for Port H Bit 7 */
  } Bits;
} PTHDSSTR;
extern volatile PTHDSSTR _PTHDS @0xFFFF994A;
#define PTHDS                           _PTHDS.Byte
#define PTHDS_PTHDS0                    _PTHDS.Bits.PTHDS0
#define PTHDS_PTHDS1                    _PTHDS.Bits.PTHDS1
#define PTHDS_PTHDS2                    _PTHDS.Bits.PTHDS2
#define PTHDS_PTHDS3                    _PTHDS.Bits.PTHDS3
#define PTHDS_PTHDS4                    _PTHDS.Bits.PTHDS4
#define PTHDS_PTHDS5                    _PTHDS.Bits.PTHDS5
#define PTHDS_PTHDS6                    _PTHDS.Bits.PTHDS6
#define PTHDS_PTHDS7                    _PTHDS.Bits.PTHDS7

#define PTHDS_PTHDS0_MASK               1U
#define PTHDS_PTHDS1_MASK               2U
#define PTHDS_PTHDS2_MASK               4U
#define PTHDS_PTHDS3_MASK               8U
#define PTHDS_PTHDS4_MASK               16U
#define PTHDS_PTHDS5_MASK               32U
#define PTHDS_PTHDS6_MASK               64U
#define PTHDS_PTHDS7_MASK               128U


/*** PTHIFE - Port H Input Filter Enable Register; 0xFFFF994B ***/
typedef union {
  byte Byte;
  struct {
    byte PTHIFE0     :1;                                       /* Port H Input Filter Enable Bit 0 */
    byte PTHIFE1     :1;                                       /* Port H Input Filter Enable Bit 1 */
    byte PTHIFE2     :1;                                       /* Port H Input Filter Enable Bit 2 */
    byte PTHIFE3     :1;                                       /* Port H Input Filter Enable Bit 3 */
    byte PTHIFE4     :1;                                       /* Port H Input Filter Enable Bit 4 */
    byte PTHIFE5     :1;                                       /* Port H Input Filter Enable Bit 5 */
    byte PTHIFE6     :1;                                       /* Port H Input Filter Enable Bit 6 */
    byte PTHIFE7     :1;                                       /* Port H Input Filter Enable Bit 7 */
  } Bits;
} PTHIFESTR;
extern volatile PTHIFESTR _PTHIFE @0xFFFF994B;
#define PTHIFE                          _PTHIFE.Byte
#define PTHIFE_PTHIFE0                  _PTHIFE.Bits.PTHIFE0
#define PTHIFE_PTHIFE1                  _PTHIFE.Bits.PTHIFE1
#define PTHIFE_PTHIFE2                  _PTHIFE.Bits.PTHIFE2
#define PTHIFE_PTHIFE3                  _PTHIFE.Bits.PTHIFE3
#define PTHIFE_PTHIFE4                  _PTHIFE.Bits.PTHIFE4
#define PTHIFE_PTHIFE5                  _PTHIFE.Bits.PTHIFE5
#define PTHIFE_PTHIFE6                  _PTHIFE.Bits.PTHIFE6
#define PTHIFE_PTHIFE7                  _PTHIFE.Bits.PTHIFE7

#define PTHIFE_PTHIFE0_MASK             1U
#define PTHIFE_PTHIFE1_MASK             2U
#define PTHIFE_PTHIFE2_MASK             4U
#define PTHIFE_PTHIFE3_MASK             8U
#define PTHIFE_PTHIFE4_MASK             16U
#define PTHIFE_PTHIFE5_MASK             32U
#define PTHIFE_PTHIFE6_MASK             64U
#define PTHIFE_PTHIFE7_MASK             128U


/*** PTJPE - Port J Pull Enable Register; 0xFFFF994C ***/
typedef union {
  byte Byte;
  struct {
    byte PTJPE0      :1;                                       /* Internal Pull Enable for Port J Bit 0 */
    byte PTJPE1      :1;                                       /* Internal Pull Enable for Port J Bit 1 */
    byte PTJPE2      :1;                                       /* Internal Pull Enable for Port J Bit 2 */
    byte PTJPE3      :1;                                       /* Internal Pull Enable for Port J Bit 3 */
    byte PTJPE4      :1;                                       /* Internal Pull Enable for Port J Bit 4 */
    byte PTJPE5      :1;                                       /* Internal Pull Enable for Port J Bit 5 */
    byte PTJPE6      :1;                                       /* Internal Pull Enable for Port J Bit 6 */
    byte PTJPE7      :1;                                       /* Internal Pull Enable for Port J Bit 7 */
  } Bits;
} PTJPESTR;
extern volatile PTJPESTR _PTJPE @0xFFFF994C;
#define PTJPE                           _PTJPE.Byte
#define PTJPE_PTJPE0                    _PTJPE.Bits.PTJPE0
#define PTJPE_PTJPE1                    _PTJPE.Bits.PTJPE1
#define PTJPE_PTJPE2                    _PTJPE.Bits.PTJPE2
#define PTJPE_PTJPE3                    _PTJPE.Bits.PTJPE3
#define PTJPE_PTJPE4                    _PTJPE.Bits.PTJPE4
#define PTJPE_PTJPE5                    _PTJPE.Bits.PTJPE5
#define PTJPE_PTJPE6                    _PTJPE.Bits.PTJPE6
#define PTJPE_PTJPE7                    _PTJPE.Bits.PTJPE7

#define PTJPE_PTJPE0_MASK               1U
#define PTJPE_PTJPE1_MASK               2U
#define PTJPE_PTJPE2_MASK               4U
#define PTJPE_PTJPE3_MASK               8U
#define PTJPE_PTJPE4_MASK               16U
#define PTJPE_PTJPE5_MASK               32U
#define PTJPE_PTJPE6_MASK               64U
#define PTJPE_PTJPE7_MASK               128U


/*** PTJSE - Port J Slew Rate Enable Register; 0xFFFF994D ***/
typedef union {
  byte Byte;
  struct {
    byte PTJSE0      :1;                                       /* Output Slew Rate Enable for Port J Bit 0 */
    byte PTJSE1      :1;                                       /* Output Slew Rate Enable for Port J Bit 1 */
    byte PTJSE2      :1;                                       /* Output Slew Rate Enable for Port J Bit 2 */
    byte PTJSE3      :1;                                       /* Output Slew Rate Enable for Port J Bit 3 */
    byte PTJSE4      :1;                                       /* Output Slew Rate Enable for Port J Bit 4 */
    byte PTJSE5      :1;                                       /* Output Slew Rate Enable for Port J Bit 5 */
    byte PTJSE6      :1;                                       /* Output Slew Rate Enable for Port J Bit 6 */
    byte PTJSE7      :1;                                       /* Output Slew Rate Enable for Port J Bit 7 */
  } Bits;
} PTJSESTR;
extern volatile PTJSESTR _PTJSE @0xFFFF994D;
#define PTJSE                           _PTJSE.Byte
#define PTJSE_PTJSE0                    _PTJSE.Bits.PTJSE0
#define PTJSE_PTJSE1                    _PTJSE.Bits.PTJSE1
#define PTJSE_PTJSE2                    _PTJSE.Bits.PTJSE2
#define PTJSE_PTJSE3                    _PTJSE.Bits.PTJSE3
#define PTJSE_PTJSE4                    _PTJSE.Bits.PTJSE4
#define PTJSE_PTJSE5                    _PTJSE.Bits.PTJSE5
#define PTJSE_PTJSE6                    _PTJSE.Bits.PTJSE6
#define PTJSE_PTJSE7                    _PTJSE.Bits.PTJSE7

#define PTJSE_PTJSE0_MASK               1U
#define PTJSE_PTJSE1_MASK               2U
#define PTJSE_PTJSE2_MASK               4U
#define PTJSE_PTJSE3_MASK               8U
#define PTJSE_PTJSE4_MASK               16U
#define PTJSE_PTJSE5_MASK               32U
#define PTJSE_PTJSE6_MASK               64U
#define PTJSE_PTJSE7_MASK               128U


/*** PTJDS - Port J Drive Strength Selection Register; 0xFFFF994E ***/
typedef union {
  byte Byte;
  struct {
    byte PTJDS0      :1;                                       /* Output Drive Strength Selection for Port J Bit 0 */
    byte PTJDS1      :1;                                       /* Output Drive Strength Selection for Port J Bit 1 */
    byte PTJDS2      :1;                                       /* Output Drive Strength Selection for Port J Bit 2 */
    byte PTJDS3      :1;                                       /* Output Drive Strength Selection for Port J Bit 3 */
    byte PTJDS4      :1;                                       /* Output Drive Strength Selection for Port J Bit 4 */
    byte PTJDS5      :1;                                       /* Output Drive Strength Selection for Port J Bit 5 */
    byte PTJDS6      :1;                                       /* Output Drive Strength Selection for Port J Bit 6 */
    byte PTJDS7      :1;                                       /* Output Drive Strength Selection for Port J Bit 7 */
  } Bits;
} PTJDSSTR;
extern volatile PTJDSSTR _PTJDS @0xFFFF994E;
#define PTJDS                           _PTJDS.Byte
#define PTJDS_PTJDS0                    _PTJDS.Bits.PTJDS0
#define PTJDS_PTJDS1                    _PTJDS.Bits.PTJDS1
#define PTJDS_PTJDS2                    _PTJDS.Bits.PTJDS2
#define PTJDS_PTJDS3                    _PTJDS.Bits.PTJDS3
#define PTJDS_PTJDS4                    _PTJDS.Bits.PTJDS4
#define PTJDS_PTJDS5                    _PTJDS.Bits.PTJDS5
#define PTJDS_PTJDS6                    _PTJDS.Bits.PTJDS6
#define PTJDS_PTJDS7                    _PTJDS.Bits.PTJDS7

#define PTJDS_PTJDS0_MASK               1U
#define PTJDS_PTJDS1_MASK               2U
#define PTJDS_PTJDS2_MASK               4U
#define PTJDS_PTJDS3_MASK               8U
#define PTJDS_PTJDS4_MASK               16U
#define PTJDS_PTJDS5_MASK               32U
#define PTJDS_PTJDS6_MASK               64U
#define PTJDS_PTJDS7_MASK               128U


/*** PTJIFE - Port J Input Filter Enable Register; 0xFFFF994F ***/
typedef union {
  byte Byte;
  struct {
    byte PTJIFE0     :1;                                       /* Port J Input Filter Enable Bit 0 */
    byte PTJIFE1     :1;                                       /* Port J Input Filter Enable Bit 1 */
    byte PTJIFE2     :1;                                       /* Port J Input Filter Enable Bit 2 */
    byte PTJIFE3     :1;                                       /* Port J Input Filter Enable Bit 3 */
    byte PTJIFE4     :1;                                       /* Port J Input Filter Enable Bit 4 */
    byte PTJIFE5     :1;                                       /* Port J Input Filter Enable Bit 5 */
    byte PTJIFE6     :1;                                       /* Port J Input Filter Enable Bit 6 */
    byte PTJIFE7     :1;                                       /* Port J Input Filter Enable Bit 7 */
  } Bits;
} PTJIFESTR;
extern volatile PTJIFESTR _PTJIFE @0xFFFF994F;
#define PTJIFE                          _PTJIFE.Byte
#define PTJIFE_PTJIFE0                  _PTJIFE.Bits.PTJIFE0
#define PTJIFE_PTJIFE1                  _PTJIFE.Bits.PTJIFE1
#define PTJIFE_PTJIFE2                  _PTJIFE.Bits.PTJIFE2
#define PTJIFE_PTJIFE3                  _PTJIFE.Bits.PTJIFE3
#define PTJIFE_PTJIFE4                  _PTJIFE.Bits.PTJIFE4
#define PTJIFE_PTJIFE5                  _PTJIFE.Bits.PTJIFE5
#define PTJIFE_PTJIFE6                  _PTJIFE.Bits.PTJIFE6
#define PTJIFE_PTJIFE7                  _PTJIFE.Bits.PTJIFE7

#define PTJIFE_PTJIFE0_MASK             1U
#define PTJIFE_PTJIFE1_MASK             2U
#define PTJIFE_PTJIFE2_MASK             4U
#define PTJIFE_PTJIFE3_MASK             8U
#define PTJIFE_PTJIFE4_MASK             16U
#define PTJIFE_PTJIFE5_MASK             32U
#define PTJIFE_PTJIFE6_MASK             64U
#define PTJIFE_PTJIFE7_MASK             128U


/*** PER_ID - Peripherial ID Register; 0xFFFF9A00 ***/
typedef union {
  byte Byte;
  struct {
    byte ID0         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 0 */
    byte ID1         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 1 */
    byte ID2         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 2 */
    byte ID3         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 3 */
    byte ID4         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 4 */
    byte ID5         :1;                                       /* Peripheral identification bits. These bits will always read 0x04 (00_0100), bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpID   :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} PER_IDSTR;
extern volatile PER_IDSTR _PER_ID @0xFFFF9A00;
#define PER_ID                          _PER_ID.Byte
#define PER_ID_ID0                      _PER_ID.Bits.ID0
#define PER_ID_ID1                      _PER_ID.Bits.ID1
#define PER_ID_ID2                      _PER_ID.Bits.ID2
#define PER_ID_ID3                      _PER_ID.Bits.ID3
#define PER_ID_ID4                      _PER_ID.Bits.ID4
#define PER_ID_ID5                      _PER_ID.Bits.ID5
#define PER_ID_ID                       _PER_ID.MergedBits.grpID

#define PER_ID_ID0_MASK                 1U
#define PER_ID_ID1_MASK                 2U
#define PER_ID_ID2_MASK                 4U
#define PER_ID_ID3_MASK                 8U
#define PER_ID_ID4_MASK                 16U
#define PER_ID_ID5_MASK                 32U
#define PER_ID_ID_MASK                  63U
#define PER_ID_ID_BITNUM                0U


/*** ID_COMP - Peripheral ID Complement Register; 0xFFFF9A04 ***/
typedef union {
  byte Byte;
  struct {
    byte NID0        :1;                                       /* Ones complement of peripheral identification bits, bit 0 */
    byte NID1        :1;                                       /* Ones complement of peripheral identification bits, bit 1 */
    byte NID2        :1;                                       /* Ones complement of peripheral identification bits, bit 2 */
    byte NID3        :1;                                       /* Ones complement of peripheral identification bits, bit 3 */
    byte NID4        :1;                                       /* Ones complement of peripheral identification bits, bit 4 */
    byte NID5        :1;                                       /* Ones complement of peripheral identification bits, bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpNID  :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} ID_COMPSTR;
extern volatile ID_COMPSTR _ID_COMP @0xFFFF9A04;
#define ID_COMP                         _ID_COMP.Byte
#define ID_COMP_NID0                    _ID_COMP.Bits.NID0
#define ID_COMP_NID1                    _ID_COMP.Bits.NID1
#define ID_COMP_NID2                    _ID_COMP.Bits.NID2
#define ID_COMP_NID3                    _ID_COMP.Bits.NID3
#define ID_COMP_NID4                    _ID_COMP.Bits.NID4
#define ID_COMP_NID5                    _ID_COMP.Bits.NID5
#define ID_COMP_NID                     _ID_COMP.MergedBits.grpNID

#define ID_COMP_NID0_MASK               1U
#define ID_COMP_NID1_MASK               2U
#define ID_COMP_NID2_MASK               4U
#define ID_COMP_NID3_MASK               8U
#define ID_COMP_NID4_MASK               16U
#define ID_COMP_NID5_MASK               32U
#define ID_COMP_NID_MASK                63U
#define ID_COMP_NID_BITNUM              0U


/*** REV - Peripheral Revision Register; 0xFFFF9A08 ***/
typedef union {
  byte Byte;
} REVSTR;
extern volatile REVSTR _REV @0xFFFF9A08;
#define REV                             _REV.Byte


/*** ADD_INFO - Peripheral Additional Info Register; 0xFFFF9A0C ***/
typedef union {
  byte Byte;
  struct {
    byte IEHOST      :1;                                       /* This bit will be set if host mode is enabled */
    byte             :1; 
    byte             :1; 
    byte IRQ_NUM0    :1;                                       /* Assigned Interrupt Request Number, bit 0 */
    byte IRQ_NUM1    :1;                                       /* Assigned Interrupt Request Number, bit 1 */
    byte IRQ_NUM2    :1;                                       /* Assigned Interrupt Request Number, bit 2 */
    byte IRQ_NUM3    :1;                                       /* Assigned Interrupt Request Number, bit 3 */
    byte IRQ_NUM4    :1;                                       /* Assigned Interrupt Request Number, bit 4 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpIRQ_NUM :5;
  } MergedBits;
} ADD_INFOSTR;
extern volatile ADD_INFOSTR _ADD_INFO @0xFFFF9A0C;
#define ADD_INFO                        _ADD_INFO.Byte
#define ADD_INFO_IEHOST                 _ADD_INFO.Bits.IEHOST
#define ADD_INFO_IRQ_NUM0               _ADD_INFO.Bits.IRQ_NUM0
#define ADD_INFO_IRQ_NUM1               _ADD_INFO.Bits.IRQ_NUM1
#define ADD_INFO_IRQ_NUM2               _ADD_INFO.Bits.IRQ_NUM2
#define ADD_INFO_IRQ_NUM3               _ADD_INFO.Bits.IRQ_NUM3
#define ADD_INFO_IRQ_NUM4               _ADD_INFO.Bits.IRQ_NUM4
#define ADD_INFO_IRQ_NUM                _ADD_INFO.MergedBits.grpIRQ_NUM

#define ADD_INFO_IEHOST_MASK            1U
#define ADD_INFO_IRQ_NUM0_MASK          8U
#define ADD_INFO_IRQ_NUM1_MASK          16U
#define ADD_INFO_IRQ_NUM2_MASK          32U
#define ADD_INFO_IRQ_NUM3_MASK          64U
#define ADD_INFO_IRQ_NUM4_MASK          128U
#define ADD_INFO_IRQ_NUM_MASK           248U
#define ADD_INFO_IRQ_NUM_BITNUM         3U


/*** OTG_INT_STAT - OTG Interrupt Status Register; 0xFFFF9A10 ***/
typedef union {
  byte Byte;
  struct {
    byte A_VBUS_CHG  :1;                                       /* This bit is set when a change in VBUS is detected on an &quot;A&quot; device */
    byte             :1; 
    byte B_SESS_CHG  :1;                                       /* This bit is set when a change in VBUS is detected on a &quot;B&quot; device */
    byte SESS_VLD_CHG :1;                                      /* This bit is set when a change in VBUS is detected indicating a session valid or a session no longer valid */
    byte             :1; 
    byte LINE_STATE_CHG :1;                                    /* This bit is set when the USB line state changes. The interrupt associated with this bit can be used to detect Reset, Resume, Connect, and Data Line Pulse signals */
    byte ONE_MSEC    :1;                                       /* This bit is set when the 1 millisecond timer expires. This bit stays asserted until clered by software. The interrupt must be serviced every millisecond to avoid losing 1msec counts */
    byte ID_CHG      :1;                                       /* This bit is set when a change in the ID Signal from the USB connector is sensed */
  } Bits;
} OTG_INT_STATSTR;
extern volatile OTG_INT_STATSTR _OTG_INT_STAT @0xFFFF9A10;
#define OTG_INT_STAT                    _OTG_INT_STAT.Byte
#define OTG_INT_STAT_A_VBUS_CHG         _OTG_INT_STAT.Bits.A_VBUS_CHG
#define OTG_INT_STAT_B_SESS_CHG         _OTG_INT_STAT.Bits.B_SESS_CHG
#define OTG_INT_STAT_SESS_VLD_CHG       _OTG_INT_STAT.Bits.SESS_VLD_CHG
#define OTG_INT_STAT_LINE_STATE_CHG     _OTG_INT_STAT.Bits.LINE_STATE_CHG
#define OTG_INT_STAT_ONE_MSEC           _OTG_INT_STAT.Bits.ONE_MSEC
#define OTG_INT_STAT_ID_CHG             _OTG_INT_STAT.Bits.ID_CHG

#define OTG_INT_STAT_A_VBUS_CHG_MASK    1U
#define OTG_INT_STAT_B_SESS_CHG_MASK    4U
#define OTG_INT_STAT_SESS_VLD_CHG_MASK  8U
#define OTG_INT_STAT_LINE_STATE_CHG_MASK 32U
#define OTG_INT_STAT_ONE_MSEC_MASK      64U
#define OTG_INT_STAT_ID_CHG_MASK        128U


/*** OTG_INT_EN - OTG Interrupt Control Register; 0xFFFF9A14 ***/
typedef union {
  byte Byte;
  struct {
    byte A_VBUS_EN   :1;                                       /* &quot;A&quot; VBUS Valid interrupt enable */
    byte             :1; 
    byte B_SESS_EN   :1;                                       /* &quot;B&quot; Session END interrupt enable */
    byte SESS_VLD_EN :1;                                       /* Session valid interrupt enable */
    byte             :1; 
    byte LINE_STATE_EN :1;                                     /* Line State change interrupt enable */
    byte ONE_MSEC_EN :1;                                       /* 1 millisecond interrupt enable */
    byte ID_EN       :1;                                       /* ID interrupt enable */
  } Bits;
} OTG_INT_ENSTR;
extern volatile OTG_INT_ENSTR _OTG_INT_EN @0xFFFF9A14;
#define OTG_INT_EN                      _OTG_INT_EN.Byte
#define OTG_INT_EN_A_VBUS_EN            _OTG_INT_EN.Bits.A_VBUS_EN
#define OTG_INT_EN_B_SESS_EN            _OTG_INT_EN.Bits.B_SESS_EN
#define OTG_INT_EN_SESS_VLD_EN          _OTG_INT_EN.Bits.SESS_VLD_EN
#define OTG_INT_EN_LINE_STATE_EN        _OTG_INT_EN.Bits.LINE_STATE_EN
#define OTG_INT_EN_ONE_MSEC_EN          _OTG_INT_EN.Bits.ONE_MSEC_EN
#define OTG_INT_EN_ID_EN                _OTG_INT_EN.Bits.ID_EN

#define OTG_INT_EN_A_VBUS_EN_MASK       1U
#define OTG_INT_EN_B_SESS_EN_MASK       4U
#define OTG_INT_EN_SESS_VLD_EN_MASK     8U
#define OTG_INT_EN_LINE_STATE_EN_MASK   32U
#define OTG_INT_EN_ONE_MSEC_EN_MASK     64U
#define OTG_INT_EN_ID_EN_MASK           128U


/*** OTG_STAT - Interrupt Status Register; 0xFFFF9A18 ***/
typedef union {
  byte Byte;
  struct {
    byte A_VBUS_VLD  :1;                                       /* &quot;A&quot; VBUS Valid */
    byte             :1; 
    byte B_SESS_END  :1;                                       /* &quot;B&quot; Session END */
    byte SESS_VLD    :1;                                       /* Session Valid */
    byte             :1; 
    byte LINE_STATE_STABLE :1;                                 /* This bit indicates that the internal signals which control the LINE_STATE_CHG bit (bit 5) of the OTG_INT_STAT register have been stable for at least 1 millisecond */
    byte ONE_MSEC_EN :1;                                       /* This bit is reserved for the 1msec count, but it is not useful to software */
    byte ID          :1;                                       /* Indicates the current state of the ID pin on the USB connector */
  } Bits;
} OTG_STATSTR;
extern volatile OTG_STATSTR _OTG_STAT @0xFFFF9A18;
#define OTG_STAT                        _OTG_STAT.Byte
#define OTG_STAT_A_VBUS_VLD             _OTG_STAT.Bits.A_VBUS_VLD
#define OTG_STAT_B_SESS_END             _OTG_STAT.Bits.B_SESS_END
#define OTG_STAT_SESS_VLD               _OTG_STAT.Bits.SESS_VLD
#define OTG_STAT_LINE_STATE_STABLE      _OTG_STAT.Bits.LINE_STATE_STABLE
#define OTG_STAT_ONE_MSEC_EN            _OTG_STAT.Bits.ONE_MSEC_EN
#define OTG_STAT_ID                     _OTG_STAT.Bits.ID

#define OTG_STAT_A_VBUS_VLD_MASK        1U
#define OTG_STAT_B_SESS_END_MASK        4U
#define OTG_STAT_SESS_VLD_MASK          8U
#define OTG_STAT_LINE_STATE_STABLE_MASK 32U
#define OTG_STAT_ONE_MSEC_EN_MASK       64U
#define OTG_STAT_ID_MASK                128U


/*** OTG_CTRL - OTG Control Register; 0xFFFF9A1C ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte OTG_EN      :1;                                       /* On-The-Go pull-up/pull-down resistor enable */
    byte             :1; 
    byte DM_LOW      :1;                                       /* D- Data Line pull-down resistor enable. This bit should always be enabled together with bit 5 (DP_LOW) */
    byte DP_LOW      :1;                                       /* D+ Data Line pull-down resistor enable. This bit should always be enabled together with bit 4 (DM_LOW) */
    byte             :1; 
    byte DP_HIGH     :1;                                       /* D+ Data Line pull-up resistor enable */
  } Bits;
} OTG_CTRLSTR;
extern volatile OTG_CTRLSTR _OTG_CTRL @0xFFFF9A1C;
#define OTG_CTRL                        _OTG_CTRL.Byte
#define OTG_CTRL_OTG_EN                 _OTG_CTRL.Bits.OTG_EN
#define OTG_CTRL_DM_LOW                 _OTG_CTRL.Bits.DM_LOW
#define OTG_CTRL_DP_LOW                 _OTG_CTRL.Bits.DP_LOW
#define OTG_CTRL_DP_HIGH                _OTG_CTRL.Bits.DP_HIGH

#define OTG_CTRL_OTG_EN_MASK            4U
#define OTG_CTRL_DM_LOW_MASK            16U
#define OTG_CTRL_DP_LOW_MASK            32U
#define OTG_CTRL_DP_HIGH_MASK           128U


/*** INT_STAT - Interrupt Status Register; 0xFFFF9A80 ***/
typedef union {
  byte Byte;
  struct {
    byte USB_RST     :1;                                       /* This bit is set when the USB Module has decoded a valid USB reset */
    byte ERROR       :1;                                       /* This bit is set when any of the error conditions within the ERR_STAT register occur. The ColdFire core must then read the ERR_STAT register to determine the source of the error */
    byte SOF_TOK     :1;                                       /* This bit is set when the USB Module receives a Start Of Frame (SOF) token. In Host mode this bit is set when the SOF threshold is reached, so that software can prepare for the next SOF */
    byte TOK_DNE     :1;                                       /* This bit is set when the current token being processed has completed */
    byte SLEEP       :1;                                       /* This bit is set when the USB Module detects a constant idle on the USB bus for 3 milliseconds. The sleep timer is reset by activity on the USB bus */
    byte RESUME      :1;                                       /* This bit is set depending upon the DP/DM signals, and can be used to signal remote wake-up signaling on the USB bus. When not in suspend mode this interrupt should be disabled */
    byte ATTACH      :1;                                       /* Attach Interrupt. This bit is set when the USB Module detects an attach of a USB device. This signal is only valid if HOST_MODE_EN is true. This interrupt signifies that a peripheral is now present and must be configured */
    byte STALL       :1;                                       /* Stall Interrupt. In Target mode this bit is asserted when a STALL handshake is sent by the SIE. In Host mode this bit is set when the USB Module detects a STALL acknowledge during the handshake phase of a USB transaction */
  } Bits;
} INT_STATSTR;
extern volatile INT_STATSTR _INT_STAT @0xFFFF9A80;
#define INT_STAT                        _INT_STAT.Byte
#define INT_STAT_USB_RST                _INT_STAT.Bits.USB_RST
#define INT_STAT_ERROR                  _INT_STAT.Bits.ERROR
#define INT_STAT_SOF_TOK                _INT_STAT.Bits.SOF_TOK
#define INT_STAT_TOK_DNE                _INT_STAT.Bits.TOK_DNE
#define INT_STAT_SLEEP                  _INT_STAT.Bits.SLEEP
#define INT_STAT_RESUME                 _INT_STAT.Bits.RESUME
#define INT_STAT_ATTACH                 _INT_STAT.Bits.ATTACH
#define INT_STAT_STALL                  _INT_STAT.Bits.STALL

#define INT_STAT_USB_RST_MASK           1U
#define INT_STAT_ERROR_MASK             2U
#define INT_STAT_SOF_TOK_MASK           4U
#define INT_STAT_TOK_DNE_MASK           8U
#define INT_STAT_SLEEP_MASK             16U
#define INT_STAT_RESUME_MASK            32U
#define INT_STAT_ATTACH_MASK            64U
#define INT_STAT_STALL_MASK             128U


/*** INT_ENB - Interrupt Enable Register; 0xFFFF9A84 ***/
typedef union {
  byte Byte;
  struct {
    byte USB_RST_EN  :1;                                       /* USB_RST Interrupt Enable */
    byte ERROR_EN    :1;                                       /* ERROR Interrupt Enable */
    byte SOF_TOK_EN  :1;                                       /* SOF_TOK Interrupt Enable */
    byte TOK_DNE_EN  :1;                                       /* TOK_DNE Interrupt Enable */
    byte SLEEP_EN    :1;                                       /* SLEEP Interrupt Enable */
    byte RESUME_EN   :1;                                       /* RESUME Interrupt Enable */
    byte ATTACH_EN   :1;                                       /* ATTACH Interrupt Enable */
    byte STALL_EN    :1;                                       /* STALL Interrupt Enable */
  } Bits;
} INT_ENBSTR;
extern volatile INT_ENBSTR _INT_ENB @0xFFFF9A84;
#define INT_ENB                         _INT_ENB.Byte
#define INT_ENB_USB_RST_EN              _INT_ENB.Bits.USB_RST_EN
#define INT_ENB_ERROR_EN                _INT_ENB.Bits.ERROR_EN
#define INT_ENB_SOF_TOK_EN              _INT_ENB.Bits.SOF_TOK_EN
#define INT_ENB_TOK_DNE_EN              _INT_ENB.Bits.TOK_DNE_EN
#define INT_ENB_SLEEP_EN                _INT_ENB.Bits.SLEEP_EN
#define INT_ENB_RESUME_EN               _INT_ENB.Bits.RESUME_EN
#define INT_ENB_ATTACH_EN               _INT_ENB.Bits.ATTACH_EN
#define INT_ENB_STALL_EN                _INT_ENB.Bits.STALL_EN

#define INT_ENB_USB_RST_EN_MASK         1U
#define INT_ENB_ERROR_EN_MASK           2U
#define INT_ENB_SOF_TOK_EN_MASK         4U
#define INT_ENB_TOK_DNE_EN_MASK         8U
#define INT_ENB_SLEEP_EN_MASK           16U
#define INT_ENB_RESUME_EN_MASK          32U
#define INT_ENB_ATTACH_EN_MASK          64U
#define INT_ENB_STALL_EN_MASK           128U


/*** ERR_STAT - Error Interrupt Status Register; 0xFFFF9A88 ***/
typedef union {
  byte Byte;
  struct {
    byte PID_ERR     :1;                                       /* This bit is set when the PID check field fails */
    byte CRC5_EOF    :1;                                       /* When the USB Module is operating in Peripheral mode (HOST_MODE_EN=0) this interrupt will detect CRC5 errors in the token packets generated by the host. When the USB Module is operating in Host mode (HOST_MODE_EN=1) this interupt will detect End Of Frame (EOF) error conditions */
    byte CRC16       :1;                                       /* This bit is set when a data packet is rejected due to a CRC16 error */
    byte DFN8        :1;                                       /* This bit is set if the dta field received was not 8 bits in length. USB Specification 1.0 requires that data fields be an integral number of bytes. If the data field was not an integral number of bytes this bit will be set */
    byte BTO_ERR     :1;                                       /* This bit is set when a bus turnaround timeout error occurs */
    byte DMA_ERR     :1;                                       /* This bit is set if the USB Module has requested a DMA access to read a new BDT but has not been given the bus before it needs to receive or transmit data */
    byte             :1; 
    byte BTS_ERR     :1;                                       /* This bit is set when a bit stuff error is detected. If set the corresponding packet will be rejected due to the error */
  } Bits;
} ERR_STATSTR;
extern volatile ERR_STATSTR _ERR_STAT @0xFFFF9A88;
#define ERR_STAT                        _ERR_STAT.Byte
#define ERR_STAT_PID_ERR                _ERR_STAT.Bits.PID_ERR
#define ERR_STAT_CRC5_EOF               _ERR_STAT.Bits.CRC5_EOF
#define ERR_STAT_CRC16                  _ERR_STAT.Bits.CRC16
#define ERR_STAT_DFN8                   _ERR_STAT.Bits.DFN8
#define ERR_STAT_BTO_ERR                _ERR_STAT.Bits.BTO_ERR
#define ERR_STAT_DMA_ERR                _ERR_STAT.Bits.DMA_ERR
#define ERR_STAT_BTS_ERR                _ERR_STAT.Bits.BTS_ERR

#define ERR_STAT_PID_ERR_MASK           1U
#define ERR_STAT_CRC5_EOF_MASK          2U
#define ERR_STAT_CRC16_MASK             4U
#define ERR_STAT_DFN8_MASK              8U
#define ERR_STAT_BTO_ERR_MASK           16U
#define ERR_STAT_DMA_ERR_MASK           32U
#define ERR_STAT_BTS_ERR_MASK           128U


/*** ERR_ENB - Error Interrupt Enable Register; 0xFFFF9A8C ***/
typedef union {
  byte Byte;
  struct {
    byte PID_ERR_EN  :1;                                       /* PID_ERR Interrupt Enable */
    byte CRC5_EOF_EN :1;                                       /* CRC5/EOF Interrupt Enable */
    byte CRC16_EN    :1;                                       /* CRC16 Interrupt Enable */
    byte DFN8_EN     :1;                                       /* DFN8 Interrupt Enable */
    byte BTO_ERR_EN  :1;                                       /* BTO_ERR Interrupt Enable */
    byte DMA_ERR_EN  :1;                                       /* DMA_ERR Interrupt Enable */
    byte             :1; 
    byte BTS_ERR_EN  :1;                                       /* BTS_ERR Interrupt Enable */
  } Bits;
} ERR_ENBSTR;
extern volatile ERR_ENBSTR _ERR_ENB @0xFFFF9A8C;
#define ERR_ENB                         _ERR_ENB.Byte
#define ERR_ENB_PID_ERR_EN              _ERR_ENB.Bits.PID_ERR_EN
#define ERR_ENB_CRC5_EOF_EN             _ERR_ENB.Bits.CRC5_EOF_EN
#define ERR_ENB_CRC16_EN                _ERR_ENB.Bits.CRC16_EN
#define ERR_ENB_DFN8_EN                 _ERR_ENB.Bits.DFN8_EN
#define ERR_ENB_BTO_ERR_EN              _ERR_ENB.Bits.BTO_ERR_EN
#define ERR_ENB_DMA_ERR_EN              _ERR_ENB.Bits.DMA_ERR_EN
#define ERR_ENB_BTS_ERR_EN              _ERR_ENB.Bits.BTS_ERR_EN

#define ERR_ENB_PID_ERR_EN_MASK         1U
#define ERR_ENB_CRC5_EOF_EN_MASK        2U
#define ERR_ENB_CRC16_EN_MASK           4U
#define ERR_ENB_DFN8_EN_MASK            8U
#define ERR_ENB_BTO_ERR_EN_MASK         16U
#define ERR_ENB_DMA_ERR_EN_MASK         32U
#define ERR_ENB_BTS_ERR_EN_MASK         128U


/*** STAT - Status Register; 0xFFFF9A90 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ODD         :1;                                       /* This bit is set if the last Buffer Descriptor updated was in the odd bank of the BDT */
    byte TX          :1;                                       /* Transmit Indicator */
    byte ENDP0       :1;                                       /* ENDP field, bit 0 */
    byte ENDP1       :1;                                       /* ENDP field, bit 1 */
    byte ENDP2       :1;                                       /* ENDP field, bit 2 */
    byte ENDP3       :1;                                       /* ENDP field, bit 3 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpENDP :4;
  } MergedBits;
} STATSTR;
extern volatile STATSTR _STAT @0xFFFF9A90;
#define STAT                            _STAT.Byte
#define STAT_ODD                        _STAT.Bits.ODD
#define STAT_TX                         _STAT.Bits.TX
#define STAT_ENDP0                      _STAT.Bits.ENDP0
#define STAT_ENDP1                      _STAT.Bits.ENDP1
#define STAT_ENDP2                      _STAT.Bits.ENDP2
#define STAT_ENDP3                      _STAT.Bits.ENDP3
#define STAT_ENDP                       _STAT.MergedBits.grpENDP

#define STAT_ODD_MASK                   4U
#define STAT_TX_MASK                    8U
#define STAT_ENDP0_MASK                 16U
#define STAT_ENDP1_MASK                 32U
#define STAT_ENDP2_MASK                 64U
#define STAT_ENDP3_MASK                 128U
#define STAT_ENDP_MASK                  240U
#define STAT_ENDP_BITNUM                4U


/*** CTL - Control Register; 0xFFFF9A94 ***/
typedef union {
  byte Byte;
  struct {
    byte USB_EN_SOF_EN :1;                                     /* USB Enable. Setting this bit causes the SIE to reset all of its ODD bits to the BDTs. Thus, setting this bit will reset much of the logic in the SIE. when host mode is enabled clearing this bit will cause the SIE to stop sending SOF tokens */
    byte ODD_RST     :1;                                       /* Setting this bit to 1 will reset all the BDT ODD ping/pong bits to 0, which then specifies the EVEN BDT bank */
    byte RESUME      :1;                                       /* When set to 1 this bit enables the USB Module to execute resume signaling */
    byte HOST_MODE_EN :1;                                      /* When set to 1, this bit enables the USB Module to operate in Host mode. In Host mode the USB Module will perform USB transactions under the programmed control of the host processor */
    byte RESET       :1;                                       /* Setting this bit enables the USB Module to generate USB reset signaling */
    byte TXSUSPEND_TOKENBUSY :1;                               /* When the USB Module is in Host mode TOKEN_BUSY is set when the USB Module is busy executing a USB token and no more token commands should be written to the Token Register. In Target mode TXD_SUSPEND is set when the SIE has disabled packet transmission and reception */
    byte SE0         :1;                                       /* Live USB Single Ended Zero signal */
    byte JSTATE      :1;                                       /* Live USB differential receiver JSTATE signal. The polarity of this signal is affected bythe current state of LS_EN */
  } Bits;
} CTLSTR;
extern volatile CTLSTR _CTL @0xFFFF9A94;
#define CTL                             _CTL.Byte
#define CTL_USB_EN_SOF_EN               _CTL.Bits.USB_EN_SOF_EN
#define CTL_ODD_RST                     _CTL.Bits.ODD_RST
#define CTL_RESUME                      _CTL.Bits.RESUME
#define CTL_HOST_MODE_EN                _CTL.Bits.HOST_MODE_EN
#define CTL_RESET                       _CTL.Bits.RESET
#define CTL_TXSUSPEND_TOKENBUSY         _CTL.Bits.TXSUSPEND_TOKENBUSY
#define CTL_SE0                         _CTL.Bits.SE0
#define CTL_JSTATE                      _CTL.Bits.JSTATE

#define CTL_USB_EN_SOF_EN_MASK          1U
#define CTL_ODD_RST_MASK                2U
#define CTL_RESUME_MASK                 4U
#define CTL_HOST_MODE_EN_MASK           8U
#define CTL_RESET_MASK                  16U
#define CTL_TXSUSPEND_TOKENBUSY_MASK    32U
#define CTL_SE0_MASK                    64U
#define CTL_JSTATE_MASK                 128U


/*** ADDR - Address Register; 0xFFFF9A98 ***/
typedef union {
  byte Byte;
  struct {
    byte ADDR0       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 0 */
    byte ADDR1       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 1 */
    byte ADDR2       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 2 */
    byte ADDR3       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 3 */
    byte ADDR4       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 4 */
    byte ADDR5       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 5 */
    byte ADDR6       :1;                                       /* USB address. This 7-bit value defines the USB address that the USB Module will decode in peripheral mode, or transmit when in host mode, bit 6 */
    byte LS_EN       :1;                                       /* Low Speed Enable bit. This bit uniforms the USB Module that the next token command written to the token register must be performed at low speed. This will enable the USB Module to perform the necessary preamble required for low-speed data transmissions */
  } Bits;
  struct {
    byte grpADDR :7;
    byte         :1;
  } MergedBits;
} ADDRSTR;
extern volatile ADDRSTR _ADDR @0xFFFF9A98;
#define ADDR                            _ADDR.Byte
#define ADDR_ADDR0                      _ADDR.Bits.ADDR0
#define ADDR_ADDR1                      _ADDR.Bits.ADDR1
#define ADDR_ADDR2                      _ADDR.Bits.ADDR2
#define ADDR_ADDR3                      _ADDR.Bits.ADDR3
#define ADDR_ADDR4                      _ADDR.Bits.ADDR4
#define ADDR_ADDR5                      _ADDR.Bits.ADDR5
#define ADDR_ADDR6                      _ADDR.Bits.ADDR6
#define ADDR_LS_EN                      _ADDR.Bits.LS_EN
#define ADDR_ADDR                       _ADDR.MergedBits.grpADDR

#define ADDR_ADDR0_MASK                 1U
#define ADDR_ADDR1_MASK                 2U
#define ADDR_ADDR2_MASK                 4U
#define ADDR_ADDR3_MASK                 8U
#define ADDR_ADDR4_MASK                 16U
#define ADDR_ADDR5_MASK                 32U
#define ADDR_ADDR6_MASK                 64U
#define ADDR_LS_EN_MASK                 128U
#define ADDR_ADDR_MASK                  127U
#define ADDR_ADDR_BITNUM                0U


/*** BDT_PAGE_01 - BDT Page Register 1; 0xFFFF9A9C ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte BDT_BA9     :1;                                       /* BDT base address bit 9 */
    byte BDT_BA10    :1;                                       /* BDT base address bit 10 */
    byte BDT_BA11    :1;                                       /* BDT base address bit 11 */
    byte BDT_BA12    :1;                                       /* BDT base address bit 12 */
    byte BDT_BA13    :1;                                       /* BDT base address bit 13 */
    byte BDT_BA14    :1;                                       /* BDT base address bit 14 */
    byte BDT_BA15    :1;                                       /* BDT base address bit 15 */
  } Bits;
  struct {
    byte         :1;
    byte grpBDT_BA_9 :7;
  } MergedBits;
} BDT_PAGE_01STR;
extern volatile BDT_PAGE_01STR _BDT_PAGE_01 @0xFFFF9A9C;
#define BDT_PAGE_01                     _BDT_PAGE_01.Byte
#define BDT_PAGE_01_BDT_BA9             _BDT_PAGE_01.Bits.BDT_BA9
#define BDT_PAGE_01_BDT_BA10            _BDT_PAGE_01.Bits.BDT_BA10
#define BDT_PAGE_01_BDT_BA11            _BDT_PAGE_01.Bits.BDT_BA11
#define BDT_PAGE_01_BDT_BA12            _BDT_PAGE_01.Bits.BDT_BA12
#define BDT_PAGE_01_BDT_BA13            _BDT_PAGE_01.Bits.BDT_BA13
#define BDT_PAGE_01_BDT_BA14            _BDT_PAGE_01.Bits.BDT_BA14
#define BDT_PAGE_01_BDT_BA15            _BDT_PAGE_01.Bits.BDT_BA15
#define BDT_PAGE_01_BDT_BA_9            _BDT_PAGE_01.MergedBits.grpBDT_BA_9
#define BDT_PAGE_01_BDT_BA              BDT_PAGE_01_BDT_BA_9

#define BDT_PAGE_01_BDT_BA9_MASK        2U
#define BDT_PAGE_01_BDT_BA10_MASK       4U
#define BDT_PAGE_01_BDT_BA11_MASK       8U
#define BDT_PAGE_01_BDT_BA12_MASK       16U
#define BDT_PAGE_01_BDT_BA13_MASK       32U
#define BDT_PAGE_01_BDT_BA14_MASK       64U
#define BDT_PAGE_01_BDT_BA15_MASK       128U
#define BDT_PAGE_01_BDT_BA_9_MASK       254U
#define BDT_PAGE_01_BDT_BA_9_BITNUM     1U


/*** FRM_NUML - Frame Number Register Low; 0xFFFF9AA0 ***/
typedef union {
  byte Byte;
  struct {
    byte FRM0        :1;                                       /* Frame number bit 0 */
    byte FRM1        :1;                                       /* Frame number bit 1 */
    byte FRM2        :1;                                       /* Frame number bit 2 */
    byte FRM3        :1;                                       /* Frame number bit 3 */
    byte FRM4        :1;                                       /* Frame number bit 4 */
    byte FRM5        :1;                                       /* Frame number bit 5 */
    byte FRM6        :1;                                       /* Frame number bit 6 */
    byte FRM7        :1;                                       /* Frame number bit 7 */
  } Bits;
} FRM_NUMLSTR;
extern volatile FRM_NUMLSTR _FRM_NUML @0xFFFF9AA0;
#define FRM_NUML                        _FRM_NUML.Byte
#define FRM_NUML_FRM0                   _FRM_NUML.Bits.FRM0
#define FRM_NUML_FRM1                   _FRM_NUML.Bits.FRM1
#define FRM_NUML_FRM2                   _FRM_NUML.Bits.FRM2
#define FRM_NUML_FRM3                   _FRM_NUML.Bits.FRM3
#define FRM_NUML_FRM4                   _FRM_NUML.Bits.FRM4
#define FRM_NUML_FRM5                   _FRM_NUML.Bits.FRM5
#define FRM_NUML_FRM6                   _FRM_NUML.Bits.FRM6
#define FRM_NUML_FRM7                   _FRM_NUML.Bits.FRM7

#define FRM_NUML_FRM0_MASK              1U
#define FRM_NUML_FRM1_MASK              2U
#define FRM_NUML_FRM2_MASK              4U
#define FRM_NUML_FRM3_MASK              8U
#define FRM_NUML_FRM4_MASK              16U
#define FRM_NUML_FRM5_MASK              32U
#define FRM_NUML_FRM6_MASK              64U
#define FRM_NUML_FRM7_MASK              128U


/*** FRM_NUMH - Frame Number Register High; 0xFFFF9AA4 ***/
typedef union {
  byte Byte;
  struct {
    byte FRM8        :1;                                       /* Frame number bit 8 */
    byte FRM9        :1;                                       /* Frame number bit 9 */
    byte FRM10       :1;                                       /* Frame number bit 10 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpFRM_8 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} FRM_NUMHSTR;
extern volatile FRM_NUMHSTR _FRM_NUMH @0xFFFF9AA4;
#define FRM_NUMH                        _FRM_NUMH.Byte
#define FRM_NUMH_FRM8                   _FRM_NUMH.Bits.FRM8
#define FRM_NUMH_FRM9                   _FRM_NUMH.Bits.FRM9
#define FRM_NUMH_FRM10                  _FRM_NUMH.Bits.FRM10
#define FRM_NUMH_FRM_8                  _FRM_NUMH.MergedBits.grpFRM_8
#define FRM_NUMH_FRM                    FRM_NUMH_FRM_8

#define FRM_NUMH_FRM8_MASK              1U
#define FRM_NUMH_FRM9_MASK              2U
#define FRM_NUMH_FRM10_MASK             4U
#define FRM_NUMH_FRM_8_MASK             7U
#define FRM_NUMH_FRM_8_BITNUM           0U


/*** TOKEN - Token Register; 0xFFFF9AA8 ***/
typedef union {
  byte Byte;
  struct {
    byte TOKEN_ENDPT0 :1;                                      /* Endpoint address for the token command, bit 0 */
    byte TOKEN_ENDPT1 :1;                                      /* Endpoint address for the token command, bit 1 */
    byte TOKEN_ENDPT2 :1;                                      /* Endpoint address for the token command, bit 2 */
    byte TOKEN_ENDPT3 :1;                                      /* Endpoint address for the token command, bit 3 */
    byte TOKEN_PID0  :1;                                       /* Token type, bit 0 */
    byte TOKEN_PID1  :1;                                       /* Token type, bit 1 */
    byte TOKEN_PID2  :1;                                       /* Token type, bit 2 */
    byte TOKEN_PID3  :1;                                       /* Token type, bit 3 */
  } Bits;
  struct {
    byte grpTOKEN_ENDPT :4;
    byte grpTOKEN_PID :4;
  } MergedBits;
} TOKENSTR;
extern volatile TOKENSTR _TOKEN @0xFFFF9AA8;
#define TOKEN                           _TOKEN.Byte
#define TOKEN_TOKEN_ENDPT0              _TOKEN.Bits.TOKEN_ENDPT0
#define TOKEN_TOKEN_ENDPT1              _TOKEN.Bits.TOKEN_ENDPT1
#define TOKEN_TOKEN_ENDPT2              _TOKEN.Bits.TOKEN_ENDPT2
#define TOKEN_TOKEN_ENDPT3              _TOKEN.Bits.TOKEN_ENDPT3
#define TOKEN_TOKEN_PID0                _TOKEN.Bits.TOKEN_PID0
#define TOKEN_TOKEN_PID1                _TOKEN.Bits.TOKEN_PID1
#define TOKEN_TOKEN_PID2                _TOKEN.Bits.TOKEN_PID2
#define TOKEN_TOKEN_PID3                _TOKEN.Bits.TOKEN_PID3
#define TOKEN_TOKEN_ENDPT               _TOKEN.MergedBits.grpTOKEN_ENDPT
#define TOKEN_TOKEN_PID                 _TOKEN.MergedBits.grpTOKEN_PID

#define TOKEN_TOKEN_ENDPT0_MASK         1U
#define TOKEN_TOKEN_ENDPT1_MASK         2U
#define TOKEN_TOKEN_ENDPT2_MASK         4U
#define TOKEN_TOKEN_ENDPT3_MASK         8U
#define TOKEN_TOKEN_PID0_MASK           16U
#define TOKEN_TOKEN_PID1_MASK           32U
#define TOKEN_TOKEN_PID2_MASK           64U
#define TOKEN_TOKEN_PID3_MASK           128U
#define TOKEN_TOKEN_ENDPT_MASK          15U
#define TOKEN_TOKEN_ENDPT_BITNUM        0U
#define TOKEN_TOKEN_PID_MASK            240U
#define TOKEN_TOKEN_PID_BITNUM          4U


/*** SOF_THLD - SOF Threshold Register; 0xFFFF9AAC ***/
typedef union {
  byte Byte;
  struct {
    byte CNT0        :1;                                       /* SOF count threshold, bit 0 */
    byte CNT1        :1;                                       /* SOF count threshold, bit 1 */
    byte CNT2        :1;                                       /* SOF count threshold, bit 2 */
    byte CNT3        :1;                                       /* SOF count threshold, bit 3 */
    byte CNT4        :1;                                       /* SOF count threshold, bit 4 */
    byte CNT5        :1;                                       /* SOF count threshold, bit 5 */
    byte CNT6        :1;                                       /* SOF count threshold, bit 6 */
    byte CNT7        :1;                                       /* SOF count threshold, bit 7 */
  } Bits;
} SOF_THLDSTR;
extern volatile SOF_THLDSTR _SOF_THLD @0xFFFF9AAC;
#define SOF_THLD                        _SOF_THLD.Byte
#define SOF_THLD_CNT0                   _SOF_THLD.Bits.CNT0
#define SOF_THLD_CNT1                   _SOF_THLD.Bits.CNT1
#define SOF_THLD_CNT2                   _SOF_THLD.Bits.CNT2
#define SOF_THLD_CNT3                   _SOF_THLD.Bits.CNT3
#define SOF_THLD_CNT4                   _SOF_THLD.Bits.CNT4
#define SOF_THLD_CNT5                   _SOF_THLD.Bits.CNT5
#define SOF_THLD_CNT6                   _SOF_THLD.Bits.CNT6
#define SOF_THLD_CNT7                   _SOF_THLD.Bits.CNT7

#define SOF_THLD_CNT0_MASK              1U
#define SOF_THLD_CNT1_MASK              2U
#define SOF_THLD_CNT2_MASK              4U
#define SOF_THLD_CNT3_MASK              8U
#define SOF_THLD_CNT4_MASK              16U
#define SOF_THLD_CNT5_MASK              32U
#define SOF_THLD_CNT6_MASK              64U
#define SOF_THLD_CNT7_MASK              128U


/*** BDT_PAGE_02 - BDT Page Register 2; 0xFFFF9AB0 ***/
typedef union {
  byte Byte;
  struct {
    byte BDT_BA16    :1;                                       /* BDT base address bit 16 */
    byte BDT_BA17    :1;                                       /* BDT base address bit 17 */
    byte BDT_BA18    :1;                                       /* BDT base address bit 18 */
    byte BDT_BA19    :1;                                       /* BDT base address bit 19 */
    byte BDT_BA20    :1;                                       /* BDT base address bit 20 */
    byte BDT_BA21    :1;                                       /* BDT base address bit 21 */
    byte BDT_BA22    :1;                                       /* BDT base address bit 22 */
    byte BDT_BA23    :1;                                       /* BDT base address bit 23 */
  } Bits;
} BDT_PAGE_02STR;
extern volatile BDT_PAGE_02STR _BDT_PAGE_02 @0xFFFF9AB0;
#define BDT_PAGE_02                     _BDT_PAGE_02.Byte
#define BDT_PAGE_02_BDT_BA16            _BDT_PAGE_02.Bits.BDT_BA16
#define BDT_PAGE_02_BDT_BA17            _BDT_PAGE_02.Bits.BDT_BA17
#define BDT_PAGE_02_BDT_BA18            _BDT_PAGE_02.Bits.BDT_BA18
#define BDT_PAGE_02_BDT_BA19            _BDT_PAGE_02.Bits.BDT_BA19
#define BDT_PAGE_02_BDT_BA20            _BDT_PAGE_02.Bits.BDT_BA20
#define BDT_PAGE_02_BDT_BA21            _BDT_PAGE_02.Bits.BDT_BA21
#define BDT_PAGE_02_BDT_BA22            _BDT_PAGE_02.Bits.BDT_BA22
#define BDT_PAGE_02_BDT_BA23            _BDT_PAGE_02.Bits.BDT_BA23

#define BDT_PAGE_02_BDT_BA16_MASK       1U
#define BDT_PAGE_02_BDT_BA17_MASK       2U
#define BDT_PAGE_02_BDT_BA18_MASK       4U
#define BDT_PAGE_02_BDT_BA19_MASK       8U
#define BDT_PAGE_02_BDT_BA20_MASK       16U
#define BDT_PAGE_02_BDT_BA21_MASK       32U
#define BDT_PAGE_02_BDT_BA22_MASK       64U
#define BDT_PAGE_02_BDT_BA23_MASK       128U


/*** BDT_PAGE_03 - BDT Page Register 3; 0xFFFF9AB4 ***/
typedef union {
  byte Byte;
  struct {
    byte BDT_BA24    :1;                                       /* BDT base address bit 24 */
    byte BDT_BA25    :1;                                       /* BDT base address bit 25 */
    byte BDT_BA26    :1;                                       /* BDT base address bit 26 */
    byte BDT_BA27    :1;                                       /* BDT base address bit 27 */
    byte BDT_BA28    :1;                                       /* BDT base address bit 28 */
    byte BDT_BA29    :1;                                       /* BDT base address bit 29 */
    byte BDT_BA30    :1;                                       /* BDT base address bit 30 */
    byte BDT_BA31    :1;                                       /* BDT base address bit 31 */
  } Bits;
} BDT_PAGE_03STR;
extern volatile BDT_PAGE_03STR _BDT_PAGE_03 @0xFFFF9AB4;
#define BDT_PAGE_03                     _BDT_PAGE_03.Byte
#define BDT_PAGE_03_BDT_BA24            _BDT_PAGE_03.Bits.BDT_BA24
#define BDT_PAGE_03_BDT_BA25            _BDT_PAGE_03.Bits.BDT_BA25
#define BDT_PAGE_03_BDT_BA26            _BDT_PAGE_03.Bits.BDT_BA26
#define BDT_PAGE_03_BDT_BA27            _BDT_PAGE_03.Bits.BDT_BA27
#define BDT_PAGE_03_BDT_BA28            _BDT_PAGE_03.Bits.BDT_BA28
#define BDT_PAGE_03_BDT_BA29            _BDT_PAGE_03.Bits.BDT_BA29
#define BDT_PAGE_03_BDT_BA30            _BDT_PAGE_03.Bits.BDT_BA30
#define BDT_PAGE_03_BDT_BA31            _BDT_PAGE_03.Bits.BDT_BA31

#define BDT_PAGE_03_BDT_BA24_MASK       1U
#define BDT_PAGE_03_BDT_BA25_MASK       2U
#define BDT_PAGE_03_BDT_BA26_MASK       4U
#define BDT_PAGE_03_BDT_BA27_MASK       8U
#define BDT_PAGE_03_BDT_BA28_MASK       16U
#define BDT_PAGE_03_BDT_BA29_MASK       32U
#define BDT_PAGE_03_BDT_BA30_MASK       64U
#define BDT_PAGE_03_BDT_BA31_MASK       128U


/*** ENDPT0 - Endpoint Control Register 0; 0xFFFF9AC0 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* This is a Host mode only bit and is only present in the control register for endpoint 0 (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* This is a Host mode only bit and is only present in the control register for endpoint 0 (ENDPT0) */
  } Bits;
} ENDPT0STR;
extern volatile ENDPT0STR _ENDPT0 @0xFFFF9AC0;
#define ENDPT0                          _ENDPT0.Byte
#define ENDPT0_EP_HSHK                  _ENDPT0.Bits.EP_HSHK
#define ENDPT0_EP_STALL                 _ENDPT0.Bits.EP_STALL
#define ENDPT0_EP_TX_EN                 _ENDPT0.Bits.EP_TX_EN
#define ENDPT0_EP_RX_EN                 _ENDPT0.Bits.EP_RX_EN
#define ENDPT0_EP_CTL_DIS               _ENDPT0.Bits.EP_CTL_DIS
#define ENDPT0_RETRY_DIS                _ENDPT0.Bits.RETRY_DIS
#define ENDPT0_HOST_WO_HUB              _ENDPT0.Bits.HOST_WO_HUB

#define ENDPT0_EP_HSHK_MASK             1U
#define ENDPT0_EP_STALL_MASK            2U
#define ENDPT0_EP_TX_EN_MASK            4U
#define ENDPT0_EP_RX_EN_MASK            8U
#define ENDPT0_EP_CTL_DIS_MASK          16U
#define ENDPT0_RETRY_DIS_MASK           64U
#define ENDPT0_HOST_WO_HUB_MASK         128U


/*** ENDPT1 - Endpoint Control Register 1; 0xFFFF9AC4 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT1STR;
extern volatile ENDPT1STR _ENDPT1 @0xFFFF9AC4;
#define ENDPT1                          _ENDPT1.Byte
#define ENDPT1_EP_HSHK                  _ENDPT1.Bits.EP_HSHK
#define ENDPT1_EP_STALL                 _ENDPT1.Bits.EP_STALL
#define ENDPT1_EP_TX_EN                 _ENDPT1.Bits.EP_TX_EN
#define ENDPT1_EP_RX_EN                 _ENDPT1.Bits.EP_RX_EN
#define ENDPT1_EP_CTL_DIS               _ENDPT1.Bits.EP_CTL_DIS
#define ENDPT1_RETRY_DIS                _ENDPT1.Bits.RETRY_DIS
#define ENDPT1_HOST_WO_HUB              _ENDPT1.Bits.HOST_WO_HUB

#define ENDPT1_EP_HSHK_MASK             1U
#define ENDPT1_EP_STALL_MASK            2U
#define ENDPT1_EP_TX_EN_MASK            4U
#define ENDPT1_EP_RX_EN_MASK            8U
#define ENDPT1_EP_CTL_DIS_MASK          16U
#define ENDPT1_RETRY_DIS_MASK           64U
#define ENDPT1_HOST_WO_HUB_MASK         128U


/*** ENDPT2 - Endpoint Control Register 2; 0xFFFF9AC8 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT2STR;
extern volatile ENDPT2STR _ENDPT2 @0xFFFF9AC8;
#define ENDPT2                          _ENDPT2.Byte
#define ENDPT2_EP_HSHK                  _ENDPT2.Bits.EP_HSHK
#define ENDPT2_EP_STALL                 _ENDPT2.Bits.EP_STALL
#define ENDPT2_EP_TX_EN                 _ENDPT2.Bits.EP_TX_EN
#define ENDPT2_EP_RX_EN                 _ENDPT2.Bits.EP_RX_EN
#define ENDPT2_EP_CTL_DIS               _ENDPT2.Bits.EP_CTL_DIS
#define ENDPT2_RETRY_DIS                _ENDPT2.Bits.RETRY_DIS
#define ENDPT2_HOST_WO_HUB              _ENDPT2.Bits.HOST_WO_HUB

#define ENDPT2_EP_HSHK_MASK             1U
#define ENDPT2_EP_STALL_MASK            2U
#define ENDPT2_EP_TX_EN_MASK            4U
#define ENDPT2_EP_RX_EN_MASK            8U
#define ENDPT2_EP_CTL_DIS_MASK          16U
#define ENDPT2_RETRY_DIS_MASK           64U
#define ENDPT2_HOST_WO_HUB_MASK         128U


/*** ENDPT3 - Endpoint Control Register 3; 0xFFFF9ACC ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT3STR;
extern volatile ENDPT3STR _ENDPT3 @0xFFFF9ACC;
#define ENDPT3                          _ENDPT3.Byte
#define ENDPT3_EP_HSHK                  _ENDPT3.Bits.EP_HSHK
#define ENDPT3_EP_STALL                 _ENDPT3.Bits.EP_STALL
#define ENDPT3_EP_TX_EN                 _ENDPT3.Bits.EP_TX_EN
#define ENDPT3_EP_RX_EN                 _ENDPT3.Bits.EP_RX_EN
#define ENDPT3_EP_CTL_DIS               _ENDPT3.Bits.EP_CTL_DIS
#define ENDPT3_RETRY_DIS                _ENDPT3.Bits.RETRY_DIS
#define ENDPT3_HOST_WO_HUB              _ENDPT3.Bits.HOST_WO_HUB

#define ENDPT3_EP_HSHK_MASK             1U
#define ENDPT3_EP_STALL_MASK            2U
#define ENDPT3_EP_TX_EN_MASK            4U
#define ENDPT3_EP_RX_EN_MASK            8U
#define ENDPT3_EP_CTL_DIS_MASK          16U
#define ENDPT3_RETRY_DIS_MASK           64U
#define ENDPT3_HOST_WO_HUB_MASK         128U


/*** ENDPT4 - Endpoint Control Register 4; 0xFFFF9AD0 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT4STR;
extern volatile ENDPT4STR _ENDPT4 @0xFFFF9AD0;
#define ENDPT4                          _ENDPT4.Byte
#define ENDPT4_EP_HSHK                  _ENDPT4.Bits.EP_HSHK
#define ENDPT4_EP_STALL                 _ENDPT4.Bits.EP_STALL
#define ENDPT4_EP_TX_EN                 _ENDPT4.Bits.EP_TX_EN
#define ENDPT4_EP_RX_EN                 _ENDPT4.Bits.EP_RX_EN
#define ENDPT4_EP_CTL_DIS               _ENDPT4.Bits.EP_CTL_DIS
#define ENDPT4_RETRY_DIS                _ENDPT4.Bits.RETRY_DIS
#define ENDPT4_HOST_WO_HUB              _ENDPT4.Bits.HOST_WO_HUB

#define ENDPT4_EP_HSHK_MASK             1U
#define ENDPT4_EP_STALL_MASK            2U
#define ENDPT4_EP_TX_EN_MASK            4U
#define ENDPT4_EP_RX_EN_MASK            8U
#define ENDPT4_EP_CTL_DIS_MASK          16U
#define ENDPT4_RETRY_DIS_MASK           64U
#define ENDPT4_HOST_WO_HUB_MASK         128U


/*** ENDPT5 - Endpoint Control Register 5; 0xFFFF9AD4 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT5STR;
extern volatile ENDPT5STR _ENDPT5 @0xFFFF9AD4;
#define ENDPT5                          _ENDPT5.Byte
#define ENDPT5_EP_HSHK                  _ENDPT5.Bits.EP_HSHK
#define ENDPT5_EP_STALL                 _ENDPT5.Bits.EP_STALL
#define ENDPT5_EP_TX_EN                 _ENDPT5.Bits.EP_TX_EN
#define ENDPT5_EP_RX_EN                 _ENDPT5.Bits.EP_RX_EN
#define ENDPT5_EP_CTL_DIS               _ENDPT5.Bits.EP_CTL_DIS
#define ENDPT5_RETRY_DIS                _ENDPT5.Bits.RETRY_DIS
#define ENDPT5_HOST_WO_HUB              _ENDPT5.Bits.HOST_WO_HUB

#define ENDPT5_EP_HSHK_MASK             1U
#define ENDPT5_EP_STALL_MASK            2U
#define ENDPT5_EP_TX_EN_MASK            4U
#define ENDPT5_EP_RX_EN_MASK            8U
#define ENDPT5_EP_CTL_DIS_MASK          16U
#define ENDPT5_RETRY_DIS_MASK           64U
#define ENDPT5_HOST_WO_HUB_MASK         128U


/*** ENDPT6 - Endpoint Control Register 6; 0xFFFF9AD8 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT6STR;
extern volatile ENDPT6STR _ENDPT6 @0xFFFF9AD8;
#define ENDPT6                          _ENDPT6.Byte
#define ENDPT6_EP_HSHK                  _ENDPT6.Bits.EP_HSHK
#define ENDPT6_EP_STALL                 _ENDPT6.Bits.EP_STALL
#define ENDPT6_EP_TX_EN                 _ENDPT6.Bits.EP_TX_EN
#define ENDPT6_EP_RX_EN                 _ENDPT6.Bits.EP_RX_EN
#define ENDPT6_EP_CTL_DIS               _ENDPT6.Bits.EP_CTL_DIS
#define ENDPT6_RETRY_DIS                _ENDPT6.Bits.RETRY_DIS
#define ENDPT6_HOST_WO_HUB              _ENDPT6.Bits.HOST_WO_HUB

#define ENDPT6_EP_HSHK_MASK             1U
#define ENDPT6_EP_STALL_MASK            2U
#define ENDPT6_EP_TX_EN_MASK            4U
#define ENDPT6_EP_RX_EN_MASK            8U
#define ENDPT6_EP_CTL_DIS_MASK          16U
#define ENDPT6_RETRY_DIS_MASK           64U
#define ENDPT6_HOST_WO_HUB_MASK         128U


/*** ENDPT7 - Endpoint Control Register 7; 0xFFFF9ADC ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT7STR;
extern volatile ENDPT7STR _ENDPT7 @0xFFFF9ADC;
#define ENDPT7                          _ENDPT7.Byte
#define ENDPT7_EP_HSHK                  _ENDPT7.Bits.EP_HSHK
#define ENDPT7_EP_STALL                 _ENDPT7.Bits.EP_STALL
#define ENDPT7_EP_TX_EN                 _ENDPT7.Bits.EP_TX_EN
#define ENDPT7_EP_RX_EN                 _ENDPT7.Bits.EP_RX_EN
#define ENDPT7_EP_CTL_DIS               _ENDPT7.Bits.EP_CTL_DIS
#define ENDPT7_RETRY_DIS                _ENDPT7.Bits.RETRY_DIS
#define ENDPT7_HOST_WO_HUB              _ENDPT7.Bits.HOST_WO_HUB

#define ENDPT7_EP_HSHK_MASK             1U
#define ENDPT7_EP_STALL_MASK            2U
#define ENDPT7_EP_TX_EN_MASK            4U
#define ENDPT7_EP_RX_EN_MASK            8U
#define ENDPT7_EP_CTL_DIS_MASK          16U
#define ENDPT7_RETRY_DIS_MASK           64U
#define ENDPT7_HOST_WO_HUB_MASK         128U


/*** ENDPT8 - Endpoint Control Register 8; 0xFFFF9AE0 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT8STR;
extern volatile ENDPT8STR _ENDPT8 @0xFFFF9AE0;
#define ENDPT8                          _ENDPT8.Byte
#define ENDPT8_EP_HSHK                  _ENDPT8.Bits.EP_HSHK
#define ENDPT8_EP_STALL                 _ENDPT8.Bits.EP_STALL
#define ENDPT8_EP_TX_EN                 _ENDPT8.Bits.EP_TX_EN
#define ENDPT8_EP_RX_EN                 _ENDPT8.Bits.EP_RX_EN
#define ENDPT8_EP_CTL_DIS               _ENDPT8.Bits.EP_CTL_DIS
#define ENDPT8_RETRY_DIS                _ENDPT8.Bits.RETRY_DIS
#define ENDPT8_HOST_WO_HUB              _ENDPT8.Bits.HOST_WO_HUB

#define ENDPT8_EP_HSHK_MASK             1U
#define ENDPT8_EP_STALL_MASK            2U
#define ENDPT8_EP_TX_EN_MASK            4U
#define ENDPT8_EP_RX_EN_MASK            8U
#define ENDPT8_EP_CTL_DIS_MASK          16U
#define ENDPT8_RETRY_DIS_MASK           64U
#define ENDPT8_HOST_WO_HUB_MASK         128U


/*** ENDPT9 - Endpoint Control Register 9; 0xFFFF9AE4 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT9STR;
extern volatile ENDPT9STR _ENDPT9 @0xFFFF9AE4;
#define ENDPT9                          _ENDPT9.Byte
#define ENDPT9_EP_HSHK                  _ENDPT9.Bits.EP_HSHK
#define ENDPT9_EP_STALL                 _ENDPT9.Bits.EP_STALL
#define ENDPT9_EP_TX_EN                 _ENDPT9.Bits.EP_TX_EN
#define ENDPT9_EP_RX_EN                 _ENDPT9.Bits.EP_RX_EN
#define ENDPT9_EP_CTL_DIS               _ENDPT9.Bits.EP_CTL_DIS
#define ENDPT9_RETRY_DIS                _ENDPT9.Bits.RETRY_DIS
#define ENDPT9_HOST_WO_HUB              _ENDPT9.Bits.HOST_WO_HUB

#define ENDPT9_EP_HSHK_MASK             1U
#define ENDPT9_EP_STALL_MASK            2U
#define ENDPT9_EP_TX_EN_MASK            4U
#define ENDPT9_EP_RX_EN_MASK            8U
#define ENDPT9_EP_CTL_DIS_MASK          16U
#define ENDPT9_RETRY_DIS_MASK           64U
#define ENDPT9_HOST_WO_HUB_MASK         128U


/*** ENDPT10 - Endpoint Control Register 10; 0xFFFF9AE8 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT10STR;
extern volatile ENDPT10STR _ENDPT10 @0xFFFF9AE8;
#define ENDPT10                         _ENDPT10.Byte
#define ENDPT10_EP_HSHK                 _ENDPT10.Bits.EP_HSHK
#define ENDPT10_EP_STALL                _ENDPT10.Bits.EP_STALL
#define ENDPT10_EP_TX_EN                _ENDPT10.Bits.EP_TX_EN
#define ENDPT10_EP_RX_EN                _ENDPT10.Bits.EP_RX_EN
#define ENDPT10_EP_CTL_DIS              _ENDPT10.Bits.EP_CTL_DIS
#define ENDPT10_RETRY_DIS               _ENDPT10.Bits.RETRY_DIS
#define ENDPT10_HOST_WO_HUB             _ENDPT10.Bits.HOST_WO_HUB

#define ENDPT10_EP_HSHK_MASK            1U
#define ENDPT10_EP_STALL_MASK           2U
#define ENDPT10_EP_TX_EN_MASK           4U
#define ENDPT10_EP_RX_EN_MASK           8U
#define ENDPT10_EP_CTL_DIS_MASK         16U
#define ENDPT10_RETRY_DIS_MASK          64U
#define ENDPT10_HOST_WO_HUB_MASK        128U


/*** ENDPT11 - Endpoint Control Register 11; 0xFFFF9AEC ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT11STR;
extern volatile ENDPT11STR _ENDPT11 @0xFFFF9AEC;
#define ENDPT11                         _ENDPT11.Byte
#define ENDPT11_EP_HSHK                 _ENDPT11.Bits.EP_HSHK
#define ENDPT11_EP_STALL                _ENDPT11.Bits.EP_STALL
#define ENDPT11_EP_TX_EN                _ENDPT11.Bits.EP_TX_EN
#define ENDPT11_EP_RX_EN                _ENDPT11.Bits.EP_RX_EN
#define ENDPT11_EP_CTL_DIS              _ENDPT11.Bits.EP_CTL_DIS
#define ENDPT11_RETRY_DIS               _ENDPT11.Bits.RETRY_DIS
#define ENDPT11_HOST_WO_HUB             _ENDPT11.Bits.HOST_WO_HUB

#define ENDPT11_EP_HSHK_MASK            1U
#define ENDPT11_EP_STALL_MASK           2U
#define ENDPT11_EP_TX_EN_MASK           4U
#define ENDPT11_EP_RX_EN_MASK           8U
#define ENDPT11_EP_CTL_DIS_MASK         16U
#define ENDPT11_RETRY_DIS_MASK          64U
#define ENDPT11_HOST_WO_HUB_MASK        128U


/*** ENDPT12 - Endpoint Control Register 12; 0xFFFF9AF0 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT12STR;
extern volatile ENDPT12STR _ENDPT12 @0xFFFF9AF0;
#define ENDPT12                         _ENDPT12.Byte
#define ENDPT12_EP_HSHK                 _ENDPT12.Bits.EP_HSHK
#define ENDPT12_EP_STALL                _ENDPT12.Bits.EP_STALL
#define ENDPT12_EP_TX_EN                _ENDPT12.Bits.EP_TX_EN
#define ENDPT12_EP_RX_EN                _ENDPT12.Bits.EP_RX_EN
#define ENDPT12_EP_CTL_DIS              _ENDPT12.Bits.EP_CTL_DIS
#define ENDPT12_RETRY_DIS               _ENDPT12.Bits.RETRY_DIS
#define ENDPT12_HOST_WO_HUB             _ENDPT12.Bits.HOST_WO_HUB

#define ENDPT12_EP_HSHK_MASK            1U
#define ENDPT12_EP_STALL_MASK           2U
#define ENDPT12_EP_TX_EN_MASK           4U
#define ENDPT12_EP_RX_EN_MASK           8U
#define ENDPT12_EP_CTL_DIS_MASK         16U
#define ENDPT12_RETRY_DIS_MASK          64U
#define ENDPT12_HOST_WO_HUB_MASK        128U


/*** ENDPT13 - Endpoint Control Register 13; 0xFFFF9AF4 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT13STR;
extern volatile ENDPT13STR _ENDPT13 @0xFFFF9AF4;
#define ENDPT13                         _ENDPT13.Byte
#define ENDPT13_EP_HSHK                 _ENDPT13.Bits.EP_HSHK
#define ENDPT13_EP_STALL                _ENDPT13.Bits.EP_STALL
#define ENDPT13_EP_TX_EN                _ENDPT13.Bits.EP_TX_EN
#define ENDPT13_EP_RX_EN                _ENDPT13.Bits.EP_RX_EN
#define ENDPT13_EP_CTL_DIS              _ENDPT13.Bits.EP_CTL_DIS
#define ENDPT13_RETRY_DIS               _ENDPT13.Bits.RETRY_DIS
#define ENDPT13_HOST_WO_HUB             _ENDPT13.Bits.HOST_WO_HUB

#define ENDPT13_EP_HSHK_MASK            1U
#define ENDPT13_EP_STALL_MASK           2U
#define ENDPT13_EP_TX_EN_MASK           4U
#define ENDPT13_EP_RX_EN_MASK           8U
#define ENDPT13_EP_CTL_DIS_MASK         16U
#define ENDPT13_RETRY_DIS_MASK          64U
#define ENDPT13_HOST_WO_HUB_MASK        128U


/*** ENDPT14 - Endpoint Control Register 14; 0xFFFF9AF8 ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT14STR;
extern volatile ENDPT14STR _ENDPT14 @0xFFFF9AF8;
#define ENDPT14                         _ENDPT14.Byte
#define ENDPT14_EP_HSHK                 _ENDPT14.Bits.EP_HSHK
#define ENDPT14_EP_STALL                _ENDPT14.Bits.EP_STALL
#define ENDPT14_EP_TX_EN                _ENDPT14.Bits.EP_TX_EN
#define ENDPT14_EP_RX_EN                _ENDPT14.Bits.EP_RX_EN
#define ENDPT14_EP_CTL_DIS              _ENDPT14.Bits.EP_CTL_DIS
#define ENDPT14_RETRY_DIS               _ENDPT14.Bits.RETRY_DIS
#define ENDPT14_HOST_WO_HUB             _ENDPT14.Bits.HOST_WO_HUB

#define ENDPT14_EP_HSHK_MASK            1U
#define ENDPT14_EP_STALL_MASK           2U
#define ENDPT14_EP_TX_EN_MASK           4U
#define ENDPT14_EP_RX_EN_MASK           8U
#define ENDPT14_EP_CTL_DIS_MASK         16U
#define ENDPT14_RETRY_DIS_MASK          64U
#define ENDPT14_HOST_WO_HUB_MASK        128U


/*** ENDPT15 - Endpoint Control Register 15; 0xFFFF9AFC ***/
typedef union {
  byte Byte;
  struct {
    byte EP_HSHK     :1;                                       /* When set this bet enables an endpoint to perform handshaking during a transaction to this endpoint. This bit will generally be set unless the endpoint is Isochronous */
    byte EP_STALL    :1;                                       /* When set this bit indicates that the endpoint is stalled */
    byte EP_TX_EN    :1;                                       /* This bit, when set, enables the endpoint for TX transfers */
    byte EP_RX_EN    :1;                                       /* This bit, when set, enables the endpoint for RX transfers */
    byte EP_CTL_DIS  :1;                                       /* This bit, when set, disables control (SETUP) transfers. When cleared, control transfers are enabled. This applies if and only if the EP_RX_EN and EP_TX_EN bits are also set */
    byte             :1; 
    byte RETRY_DIS   :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
    byte HOST_WO_HUB :1;                                       /* Not available. Present only in endpoint 0 control register (ENDPT0) */
  } Bits;
} ENDPT15STR;
extern volatile ENDPT15STR _ENDPT15 @0xFFFF9AFC;
#define ENDPT15                         _ENDPT15.Byte
#define ENDPT15_EP_HSHK                 _ENDPT15.Bits.EP_HSHK
#define ENDPT15_EP_STALL                _ENDPT15.Bits.EP_STALL
#define ENDPT15_EP_TX_EN                _ENDPT15.Bits.EP_TX_EN
#define ENDPT15_EP_RX_EN                _ENDPT15.Bits.EP_RX_EN
#define ENDPT15_EP_CTL_DIS              _ENDPT15.Bits.EP_CTL_DIS
#define ENDPT15_RETRY_DIS               _ENDPT15.Bits.RETRY_DIS
#define ENDPT15_HOST_WO_HUB             _ENDPT15.Bits.HOST_WO_HUB

#define ENDPT15_EP_HSHK_MASK            1U
#define ENDPT15_EP_STALL_MASK           2U
#define ENDPT15_EP_TX_EN_MASK           4U
#define ENDPT15_EP_RX_EN_MASK           8U
#define ENDPT15_EP_CTL_DIS_MASK         16U
#define ENDPT15_RETRY_DIS_MASK          64U
#define ENDPT15_HOST_WO_HUB_MASK        128U


/*** USB_CTRL - USB Control Register; 0xFFFF9B00 ***/
typedef union {
  byte Byte;
  struct {
    byte CLK_SRC0    :1;                                       /* Determines the clock source for the USB 48 MHZ clock, bit 0 */
    byte CLK_SRC1    :1;                                       /* Determines the clock source for the USB 48 MHZ clock, bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte PDE         :1;                                       /* Enables the non-functional weak pulldowns on the USB transceiver */
    byte SUSP        :1;                                       /* Places the USB transceiver into the suspend state */
  } Bits;
  struct {
    byte grpCLK_SRC :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} USB_CTRLSTR;
extern volatile USB_CTRLSTR _USB_CTRL @0xFFFF9B00;
#define USB_CTRL                        _USB_CTRL.Byte
#define USB_CTRL_CLK_SRC0               _USB_CTRL.Bits.CLK_SRC0
#define USB_CTRL_CLK_SRC1               _USB_CTRL.Bits.CLK_SRC1
#define USB_CTRL_PDE                    _USB_CTRL.Bits.PDE
#define USB_CTRL_SUSP                   _USB_CTRL.Bits.SUSP
#define USB_CTRL_CLK_SRC                _USB_CTRL.MergedBits.grpCLK_SRC

#define USB_CTRL_CLK_SRC0_MASK          1U
#define USB_CTRL_CLK_SRC1_MASK          2U
#define USB_CTRL_PDE_MASK               64U
#define USB_CTRL_SUSP_MASK              128U
#define USB_CTRL_CLK_SRC_MASK           3U
#define USB_CTRL_CLK_SRC_BITNUM         0U


/*** USB_OTG_OBSERVE - USB OTG Observe Register; 0xFFFF9B04 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte DM_PD       :1;                                       /* Provides observability of the D- Pull Down signal output from the USB OTG module. Useful when interfacing to an external OTG control module via a serial interface */
    byte             :1; 
    byte DP_PD       :1;                                       /* Provides observability of the D+ Pull Down signal output from the USB OTG module. Useful when interfacing to an external OTG control module via a serial interface */
    byte DP_PU       :1;                                       /* Provides observability of the D+ Pull Up signal output from the USB OTG module. This bit is useful when interfacing to anexternal OTG control module via a serial interface. Useful when interfacing to an external OTG control module via a serial interface */
  } Bits;
} USB_OTG_OBSERVESTR;
extern volatile USB_OTG_OBSERVESTR _USB_OTG_OBSERVE @0xFFFF9B04;
#define USB_OTG_OBSERVE                 _USB_OTG_OBSERVE.Byte
#define USB_OTG_OBSERVE_DM_PD           _USB_OTG_OBSERVE.Bits.DM_PD
#define USB_OTG_OBSERVE_DP_PD           _USB_OTG_OBSERVE.Bits.DP_PD
#define USB_OTG_OBSERVE_DP_PU           _USB_OTG_OBSERVE.Bits.DP_PU

#define USB_OTG_OBSERVE_DM_PD_MASK      16U
#define USB_OTG_OBSERVE_DP_PD_MASK      64U
#define USB_OTG_OBSERVE_DP_PU_MASK      128U


/*** USB_OTG_CONTROL - USB OTG Control Register; 0xFFFF9B08 ***/
typedef union {
  byte Byte;
  struct {
    byte SESSEND     :1;                                       /* Provides observability of the Session End signal output from the USB OTG module. Useful when interfacing to an external OTG control module via a serial interface */
    byte SESSVLD     :1;                                       /* Provides observability of the Session Valid signal output from the USB OTG module. Useful when interfacing to an external OTG control module via a serial interface */
    byte VBUSVLD     :1;                                       /* Provides control of the VBUS Valid signal into the USB OTG module if a pin has not been configured for this function. Useful when interfacing to an external OTG control module via a serial interface */
    byte ID          :1;                                       /* Provides control of the USB ID signal into the USB OTG module if a pin has not been configured for this function. Useful when interfacing to an external OTG control module via a serial interface */
    byte DPPULLUP_NONOTG :1;                                   /* Provides control of the DP PULLUP in the USB OTG module, if USB is configured in non-OTG device mode */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} USB_OTG_CONTROLSTR;
extern volatile USB_OTG_CONTROLSTR _USB_OTG_CONTROL @0xFFFF9B08;
#define USB_OTG_CONTROL                 _USB_OTG_CONTROL.Byte
#define USB_OTG_CONTROL_SESSEND         _USB_OTG_CONTROL.Bits.SESSEND
#define USB_OTG_CONTROL_SESSVLD         _USB_OTG_CONTROL.Bits.SESSVLD
#define USB_OTG_CONTROL_VBUSVLD         _USB_OTG_CONTROL.Bits.VBUSVLD
#define USB_OTG_CONTROL_ID              _USB_OTG_CONTROL.Bits.ID
#define USB_OTG_CONTROL_DPPULLUP_NONOTG _USB_OTG_CONTROL.Bits.DPPULLUP_NONOTG

#define USB_OTG_CONTROL_SESSEND_MASK    1U
#define USB_OTG_CONTROL_SESSVLD_MASK    2U
#define USB_OTG_CONTROL_VBUSVLD_MASK    4U
#define USB_OTG_CONTROL_ID_MASK         8U
#define USB_OTG_CONTROL_DPPULLUP_NONOTG_MASK 16U


/*** USBTRC0 - USB Transceiver and Regulator Control Register 0; 0xFFFF9B0C ***/
typedef union {
  byte Byte;
  struct {
    byte USB_RESUME_INT :1;                                    /* USB Asynchronous Interrupt */
    byte             :1; 
    byte USBVREN     :1;                                       /* USB voltage regulator enable */
    byte             :1; 
    byte             :1; 
    byte USBRESMEN   :1;                                       /* Allows the USB module to send an asynchronous wakeup event upon detection of resume signaling on the USB bus */
    byte USBPU       :1;                                       /* Pull-up resistor on the USBDP line */
    byte USBRESET    :1;                                       /* Generates a hard reset to the USB module */
  } Bits;
} USBTRC0STR;
extern volatile USBTRC0STR _USBTRC0 @0xFFFF9B0C;
#define USBTRC0                         _USBTRC0.Byte
#define USBTRC0_USB_RESUME_INT          _USBTRC0.Bits.USB_RESUME_INT
#define USBTRC0_USBVREN                 _USBTRC0.Bits.USBVREN
#define USBTRC0_USBRESMEN               _USBTRC0.Bits.USBRESMEN
#define USBTRC0_USBPU                   _USBTRC0.Bits.USBPU
#define USBTRC0_USBRESET                _USBTRC0.Bits.USBRESET

#define USBTRC0_USB_RESUME_INT_MASK     1U
#define USBTRC0_USBVREN_MASK            4U
#define USBTRC0_USBRESMEN_MASK          32U
#define USBTRC0_USBPU_MASK              64U
#define USBTRC0_USBRESET_MASK           128U


/*** OTGPIN - USB OTG Pin Control Register; 0xFFFF9B10 ***/
typedef union {
  byte Byte;
  struct {
    byte SESSVLD     :1;                                       /* Session Valid Pin Enable */
    byte SESSEND     :1;                                       /* Session End Pin Enable */
    byte VBUSVLD     :1;                                       /* Valid Pin Enable */
    byte PULLUP      :1;                                       /* Pull-up Pin Enable */
    byte DMDOWN      :1;                                       /* DMDOWN Pin Enable */
    byte DPDOWN      :1;                                       /* DPDOWN Pin Enable */
    byte USBID       :1;                                       /* USB_ID Pin Enable */
    byte             :1; 
  } Bits;
} OTGPINSTR;
extern volatile OTGPINSTR _OTGPIN @0xFFFF9B10;
#define OTGPIN                          _OTGPIN.Byte
#define OTGPIN_SESSVLD                  _OTGPIN.Bits.SESSVLD
#define OTGPIN_SESSEND                  _OTGPIN.Bits.SESSEND
#define OTGPIN_VBUSVLD                  _OTGPIN.Bits.VBUSVLD
#define OTGPIN_PULLUP                   _OTGPIN.Bits.PULLUP
#define OTGPIN_DMDOWN                   _OTGPIN.Bits.DMDOWN
#define OTGPIN_DPDOWN                   _OTGPIN.Bits.DPDOWN
#define OTGPIN_USBID                    _OTGPIN.Bits.USBID

#define OTGPIN_SESSVLD_MASK             1U
#define OTGPIN_SESSEND_MASK             2U
#define OTGPIN_VBUSVLD_MASK             4U
#define OTGPIN_PULLUP_MASK              8U
#define OTGPIN_DMDOWN_MASK              16U
#define OTGPIN_DPDOWN_MASK              32U
#define OTGPIN_USBID_MASK               64U


/*** MBCSAR0 - Chip Select Address Register 0; 0xFFFFE800 ***/
typedef union {
  dword Dword;
  struct {
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword BA0        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 0 */
    dword BA1        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 1 */
    dword BA2        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 2 */
    dword BA3        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 3 */
    dword BA4        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 4 */
    dword BA5        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 5 */
    dword BA6        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 6 */
    dword BA7        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 7 */
    dword BA8        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 8 */
    dword BA9        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 9 */
    dword BA10       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 10 */
    dword BA11       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 11 */
    dword BA12       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 12 */
    dword BA13       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 13 */
    dword BA14       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 14 */
    dword BA15       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS0. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 15 */
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpBA  :16;
  } MergedBits;
} MBCSAR0STR;
extern volatile MBCSAR0STR _MBCSAR0 @0xFFFFE800;
#define MBCSAR0                         _MBCSAR0.Dword
#define MBCSAR0_BA0                     _MBCSAR0.Bits.BA0
#define MBCSAR0_BA1                     _MBCSAR0.Bits.BA1
#define MBCSAR0_BA2                     _MBCSAR0.Bits.BA2
#define MBCSAR0_BA3                     _MBCSAR0.Bits.BA3
#define MBCSAR0_BA4                     _MBCSAR0.Bits.BA4
#define MBCSAR0_BA5                     _MBCSAR0.Bits.BA5
#define MBCSAR0_BA6                     _MBCSAR0.Bits.BA6
#define MBCSAR0_BA7                     _MBCSAR0.Bits.BA7
#define MBCSAR0_BA8                     _MBCSAR0.Bits.BA8
#define MBCSAR0_BA9                     _MBCSAR0.Bits.BA9
#define MBCSAR0_BA10                    _MBCSAR0.Bits.BA10
#define MBCSAR0_BA11                    _MBCSAR0.Bits.BA11
#define MBCSAR0_BA12                    _MBCSAR0.Bits.BA12
#define MBCSAR0_BA13                    _MBCSAR0.Bits.BA13
#define MBCSAR0_BA14                    _MBCSAR0.Bits.BA14
#define MBCSAR0_BA15                    _MBCSAR0.Bits.BA15
#define MBCSAR0_BA                      _MBCSAR0.MergedBits.grpBA

#define MBCSAR0_BA0_MASK                65536UL
#define MBCSAR0_BA1_MASK                131072UL
#define MBCSAR0_BA2_MASK                262144UL
#define MBCSAR0_BA3_MASK                524288UL
#define MBCSAR0_BA4_MASK                1048576UL
#define MBCSAR0_BA5_MASK                2097152UL
#define MBCSAR0_BA6_MASK                4194304UL
#define MBCSAR0_BA7_MASK                8388608UL
#define MBCSAR0_BA8_MASK                16777216UL
#define MBCSAR0_BA9_MASK                33554432UL
#define MBCSAR0_BA10_MASK               67108864UL
#define MBCSAR0_BA11_MASK               134217728UL
#define MBCSAR0_BA12_MASK               268435456UL
#define MBCSAR0_BA13_MASK               536870912UL
#define MBCSAR0_BA14_MASK               1073741824UL
#define MBCSAR0_BA15_MASK               2147483648UL
#define MBCSAR0_BA_MASK                 4294901760U
#define MBCSAR0_BA_BITNUM               16U


/*** MBCSMR0 - Chip Select Mask Register 0; 0xFFFFE804 ***/
typedef union {
  dword Dword;
  struct {
    dword V          :1;                                       /* Valid bit. Indicates whether the corresponding CSAR, CSMR, and CSCR contents are valid. Programmed chip selects do not assert until V is set (except for CS0, which acts as the global chip select). Reset clears each CSMRn[V] */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword WP         :1;                                       /* Write protect. Controls write accesses to the address range in the corresponding CSAR. Attempting to write to the range of addresses for which CSAR0[WP] = 1 results in the appropriate chip select not being selected. No exception occurs */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword BAM0       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 0 */
    dword BAM1       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 1 */
    dword BAM2       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 2 */
    dword BAM3       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 3 */
    dword BAM4       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 4 */
    dword BAM5       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 5 */
    dword BAM6       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 6 */
    dword BAM7       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 7 */
    dword BAM8       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 8 */
    dword BAM9       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 9 */
    dword BAM10      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 10 */
    dword BAM11      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 11 */
    dword BAM12      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 12 */
    dword BAM13      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 13 */
    dword BAM14      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 14 */
    dword BAM15      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 15 */
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpBAM :16;
  } MergedBits;
} MBCSMR0STR;
extern volatile MBCSMR0STR _MBCSMR0 @0xFFFFE804;
#define MBCSMR0                         _MBCSMR0.Dword
#define MBCSMR0_V                       _MBCSMR0.Bits.V
#define MBCSMR0_WP                      _MBCSMR0.Bits.WP
#define MBCSMR0_BAM0                    _MBCSMR0.Bits.BAM0
#define MBCSMR0_BAM1                    _MBCSMR0.Bits.BAM1
#define MBCSMR0_BAM2                    _MBCSMR0.Bits.BAM2
#define MBCSMR0_BAM3                    _MBCSMR0.Bits.BAM3
#define MBCSMR0_BAM4                    _MBCSMR0.Bits.BAM4
#define MBCSMR0_BAM5                    _MBCSMR0.Bits.BAM5
#define MBCSMR0_BAM6                    _MBCSMR0.Bits.BAM6
#define MBCSMR0_BAM7                    _MBCSMR0.Bits.BAM7
#define MBCSMR0_BAM8                    _MBCSMR0.Bits.BAM8
#define MBCSMR0_BAM9                    _MBCSMR0.Bits.BAM9
#define MBCSMR0_BAM10                   _MBCSMR0.Bits.BAM10
#define MBCSMR0_BAM11                   _MBCSMR0.Bits.BAM11
#define MBCSMR0_BAM12                   _MBCSMR0.Bits.BAM12
#define MBCSMR0_BAM13                   _MBCSMR0.Bits.BAM13
#define MBCSMR0_BAM14                   _MBCSMR0.Bits.BAM14
#define MBCSMR0_BAM15                   _MBCSMR0.Bits.BAM15
#define MBCSMR0_BAM                     _MBCSMR0.MergedBits.grpBAM

#define MBCSMR0_V_MASK                  1UL
#define MBCSMR0_WP_MASK                 256UL
#define MBCSMR0_BAM0_MASK               65536UL
#define MBCSMR0_BAM1_MASK               131072UL
#define MBCSMR0_BAM2_MASK               262144UL
#define MBCSMR0_BAM3_MASK               524288UL
#define MBCSMR0_BAM4_MASK               1048576UL
#define MBCSMR0_BAM5_MASK               2097152UL
#define MBCSMR0_BAM6_MASK               4194304UL
#define MBCSMR0_BAM7_MASK               8388608UL
#define MBCSMR0_BAM8_MASK               16777216UL
#define MBCSMR0_BAM9_MASK               33554432UL
#define MBCSMR0_BAM10_MASK              67108864UL
#define MBCSMR0_BAM11_MASK              134217728UL
#define MBCSMR0_BAM12_MASK              268435456UL
#define MBCSMR0_BAM13_MASK              536870912UL
#define MBCSMR0_BAM14_MASK              1073741824UL
#define MBCSMR0_BAM15_MASK              2147483648UL
#define MBCSMR0_BAM_MASK                4294901760U
#define MBCSMR0_BAM_BITNUM              16U


/*** MBCSCR0 - Chip Select Control Register 0; 0xFFFFE808 ***/
typedef union {
  dword Dword;
  struct {
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword PS0        :1;                                       /* Port size. Specifies the width of the data associated with each chip select. It determines where data is driven during write cycles and where data is sampled during read cycles, bit 0 */
    dword PS1        :1;                                       /* Port size. Specifies the width of the data associated with each chip select. It determines where data is driven during write cycles and where data is sampled during read cycles, bit 1 */
    dword AA         :1;                                       /* Auto-acknowledge enable. Determines the assertion of the internal transfer acknowledge for accesses specified by the chip select address. Note that if AA = 1 for a corresponding CSn and the external system asserts an external TA before the wait-state countdown asserts the internal TA, the cycle is terminated. Burst cycles increment the address bus between each internal termination */
    dword MUX        :1;                                       /* Multiplexed mode */
    dword WS0        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 0 */
    dword WS1        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 1 */
    dword WS2        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 2 */
    dword WS3        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 3 */
    dword WS4        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 4 */
    dword WS5        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 5 */
    dword WRAH0      :1;                                       /* Write address hold or deselect, bit 0 */
    dword WRAH1      :1;                                       /* Write address hold or deselect, bit 1 */
    dword RDAH0      :1;                                       /* Read address hold or deselect, bit 0 */
    dword RDAH1      :1;                                       /* Read address hold or deselect, bit 1 */
    dword ASET0      :1;                                       /* Address setup, bit 0 */
    dword ASET1      :1;                                       /* Address setup, bit 1 */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpPS  :2;
    dword grpAx  :1;
    dword        :1;
    dword grpWS  :6;
    dword grpWRAH :2;
    dword grpRDAH :2;
    dword grpASET :2;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
  } MergedBits;
} MBCSCR0STR;
extern volatile MBCSCR0STR _MBCSCR0 @0xFFFFE808;
#define MBCSCR0                         _MBCSCR0.Dword
#define MBCSCR0_PS0                     _MBCSCR0.Bits.PS0
#define MBCSCR0_PS1                     _MBCSCR0.Bits.PS1
#define MBCSCR0_AA                      _MBCSCR0.Bits.AA
#define MBCSCR0_MUX                     _MBCSCR0.Bits.MUX
#define MBCSCR0_WS0                     _MBCSCR0.Bits.WS0
#define MBCSCR0_WS1                     _MBCSCR0.Bits.WS1
#define MBCSCR0_WS2                     _MBCSCR0.Bits.WS2
#define MBCSCR0_WS3                     _MBCSCR0.Bits.WS3
#define MBCSCR0_WS4                     _MBCSCR0.Bits.WS4
#define MBCSCR0_WS5                     _MBCSCR0.Bits.WS5
#define MBCSCR0_WRAH0                   _MBCSCR0.Bits.WRAH0
#define MBCSCR0_WRAH1                   _MBCSCR0.Bits.WRAH1
#define MBCSCR0_RDAH0                   _MBCSCR0.Bits.RDAH0
#define MBCSCR0_RDAH1                   _MBCSCR0.Bits.RDAH1
#define MBCSCR0_ASET0                   _MBCSCR0.Bits.ASET0
#define MBCSCR0_ASET1                   _MBCSCR0.Bits.ASET1
#define MBCSCR0_PS                      _MBCSCR0.MergedBits.grpPS
#define MBCSCR0_WS                      _MBCSCR0.MergedBits.grpWS
#define MBCSCR0_WRAH                    _MBCSCR0.MergedBits.grpWRAH
#define MBCSCR0_RDAH                    _MBCSCR0.MergedBits.grpRDAH
#define MBCSCR0_ASET                    _MBCSCR0.MergedBits.grpASET

#define MBCSCR0_PS0_MASK                64UL
#define MBCSCR0_PS1_MASK                128UL
#define MBCSCR0_AA_MASK                 256UL
#define MBCSCR0_MUX_MASK                512UL
#define MBCSCR0_WS0_MASK                1024UL
#define MBCSCR0_WS1_MASK                2048UL
#define MBCSCR0_WS2_MASK                4096UL
#define MBCSCR0_WS3_MASK                8192UL
#define MBCSCR0_WS4_MASK                16384UL
#define MBCSCR0_WS5_MASK                32768UL
#define MBCSCR0_WRAH0_MASK              65536UL
#define MBCSCR0_WRAH1_MASK              131072UL
#define MBCSCR0_RDAH0_MASK              262144UL
#define MBCSCR0_RDAH1_MASK              524288UL
#define MBCSCR0_ASET0_MASK              1048576UL
#define MBCSCR0_ASET1_MASK              2097152UL
#define MBCSCR0_PS_MASK                 192U
#define MBCSCR0_PS_BITNUM               6U
#define MBCSCR0_WS_MASK                 64512U
#define MBCSCR0_WS_BITNUM               10U
#define MBCSCR0_WRAH_MASK               196608U
#define MBCSCR0_WRAH_BITNUM             16U
#define MBCSCR0_RDAH_MASK               786432U
#define MBCSCR0_RDAH_BITNUM             18U
#define MBCSCR0_ASET_MASK               3145728U
#define MBCSCR0_ASET_BITNUM             20U


/*** MBCSAR1 - Chip Select Address Register 1; 0xFFFFE80C ***/
typedef union {
  dword Dword;
  struct {
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword BA0        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 0 */
    dword BA1        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 1 */
    dword BA2        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 2 */
    dword BA3        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 3 */
    dword BA4        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 4 */
    dword BA5        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 5 */
    dword BA6        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 6 */
    dword BA7        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 7 */
    dword BA8        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 8 */
    dword BA9        :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 9 */
    dword BA10       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 10 */
    dword BA11       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 11 */
    dword BA12       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 12 */
    dword BA13       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 13 */
    dword BA14       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 14 */
    dword BA15       :1;                                       /* Base address. Defines the base address for memory dedicated to chip select CS1. BA is compared to bits 31-16 on the internal address bus to determine if chip select memory is being accessed, bit 15 */
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpBA  :16;
  } MergedBits;
} MBCSAR1STR;
extern volatile MBCSAR1STR _MBCSAR1 @0xFFFFE80C;
#define MBCSAR1                         _MBCSAR1.Dword
#define MBCSAR1_BA0                     _MBCSAR1.Bits.BA0
#define MBCSAR1_BA1                     _MBCSAR1.Bits.BA1
#define MBCSAR1_BA2                     _MBCSAR1.Bits.BA2
#define MBCSAR1_BA3                     _MBCSAR1.Bits.BA3
#define MBCSAR1_BA4                     _MBCSAR1.Bits.BA4
#define MBCSAR1_BA5                     _MBCSAR1.Bits.BA5
#define MBCSAR1_BA6                     _MBCSAR1.Bits.BA6
#define MBCSAR1_BA7                     _MBCSAR1.Bits.BA7
#define MBCSAR1_BA8                     _MBCSAR1.Bits.BA8
#define MBCSAR1_BA9                     _MBCSAR1.Bits.BA9
#define MBCSAR1_BA10                    _MBCSAR1.Bits.BA10
#define MBCSAR1_BA11                    _MBCSAR1.Bits.BA11
#define MBCSAR1_BA12                    _MBCSAR1.Bits.BA12
#define MBCSAR1_BA13                    _MBCSAR1.Bits.BA13
#define MBCSAR1_BA14                    _MBCSAR1.Bits.BA14
#define MBCSAR1_BA15                    _MBCSAR1.Bits.BA15
#define MBCSAR1_BA                      _MBCSAR1.MergedBits.grpBA

#define MBCSAR1_BA0_MASK                65536UL
#define MBCSAR1_BA1_MASK                131072UL
#define MBCSAR1_BA2_MASK                262144UL
#define MBCSAR1_BA3_MASK                524288UL
#define MBCSAR1_BA4_MASK                1048576UL
#define MBCSAR1_BA5_MASK                2097152UL
#define MBCSAR1_BA6_MASK                4194304UL
#define MBCSAR1_BA7_MASK                8388608UL
#define MBCSAR1_BA8_MASK                16777216UL
#define MBCSAR1_BA9_MASK                33554432UL
#define MBCSAR1_BA10_MASK               67108864UL
#define MBCSAR1_BA11_MASK               134217728UL
#define MBCSAR1_BA12_MASK               268435456UL
#define MBCSAR1_BA13_MASK               536870912UL
#define MBCSAR1_BA14_MASK               1073741824UL
#define MBCSAR1_BA15_MASK               2147483648UL
#define MBCSAR1_BA_MASK                 4294901760U
#define MBCSAR1_BA_BITNUM               16U


/*** MBCSMR1 - Chip Select Mask Register 1; 0xFFFFE810 ***/
typedef union {
  dword Dword;
  struct {
    dword V          :1;                                       /* Valid bit. Indicates whether the corresponding CSAR, CSMR, and CSCR contents are valid. Programmed chip selects do not assert until V is set. Reset clears each CSMRn[V] */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword WP         :1;                                       /* Write protect. Controls write accesses to the address range in the corresponding CSAR. Attempting to write to the range of addresses for which CSAR0[WP] = 1 results  results in a bus error termination of the internal cycle and no external <br/>cycle */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword BAM0       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 0 */
    dword BAM1       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 1 */
    dword BAM2       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 2 */
    dword BAM3       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 3 */
    dword BAM4       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 4 */
    dword BAM5       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 5 */
    dword BAM6       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 6 */
    dword BAM7       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 7 */
    dword BAM8       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 8 */
    dword BAM9       :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 9 */
    dword BAM10      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 10 */
    dword BAM11      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 11 */
    dword BAM12      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 12 */
    dword BAM13      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 13 */
    dword BAM14      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 14 */
    dword BAM15      :1;                                       /* Base address mask. Defines the chip select block by masking address bits. Setting a BAM bit causes the corresponding CSAR bit to be ignored in the decode, bit 15 */
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpBAM :16;
  } MergedBits;
} MBCSMR1STR;
extern volatile MBCSMR1STR _MBCSMR1 @0xFFFFE810;
#define MBCSMR1                         _MBCSMR1.Dword
#define MBCSMR1_V                       _MBCSMR1.Bits.V
#define MBCSMR1_WP                      _MBCSMR1.Bits.WP
#define MBCSMR1_BAM0                    _MBCSMR1.Bits.BAM0
#define MBCSMR1_BAM1                    _MBCSMR1.Bits.BAM1
#define MBCSMR1_BAM2                    _MBCSMR1.Bits.BAM2
#define MBCSMR1_BAM3                    _MBCSMR1.Bits.BAM3
#define MBCSMR1_BAM4                    _MBCSMR1.Bits.BAM4
#define MBCSMR1_BAM5                    _MBCSMR1.Bits.BAM5
#define MBCSMR1_BAM6                    _MBCSMR1.Bits.BAM6
#define MBCSMR1_BAM7                    _MBCSMR1.Bits.BAM7
#define MBCSMR1_BAM8                    _MBCSMR1.Bits.BAM8
#define MBCSMR1_BAM9                    _MBCSMR1.Bits.BAM9
#define MBCSMR1_BAM10                   _MBCSMR1.Bits.BAM10
#define MBCSMR1_BAM11                   _MBCSMR1.Bits.BAM11
#define MBCSMR1_BAM12                   _MBCSMR1.Bits.BAM12
#define MBCSMR1_BAM13                   _MBCSMR1.Bits.BAM13
#define MBCSMR1_BAM14                   _MBCSMR1.Bits.BAM14
#define MBCSMR1_BAM15                   _MBCSMR1.Bits.BAM15
#define MBCSMR1_BAM                     _MBCSMR1.MergedBits.grpBAM

#define MBCSMR1_V_MASK                  1UL
#define MBCSMR1_WP_MASK                 256UL
#define MBCSMR1_BAM0_MASK               65536UL
#define MBCSMR1_BAM1_MASK               131072UL
#define MBCSMR1_BAM2_MASK               262144UL
#define MBCSMR1_BAM3_MASK               524288UL
#define MBCSMR1_BAM4_MASK               1048576UL
#define MBCSMR1_BAM5_MASK               2097152UL
#define MBCSMR1_BAM6_MASK               4194304UL
#define MBCSMR1_BAM7_MASK               8388608UL
#define MBCSMR1_BAM8_MASK               16777216UL
#define MBCSMR1_BAM9_MASK               33554432UL
#define MBCSMR1_BAM10_MASK              67108864UL
#define MBCSMR1_BAM11_MASK              134217728UL
#define MBCSMR1_BAM12_MASK              268435456UL
#define MBCSMR1_BAM13_MASK              536870912UL
#define MBCSMR1_BAM14_MASK              1073741824UL
#define MBCSMR1_BAM15_MASK              2147483648UL
#define MBCSMR1_BAM_MASK                4294901760U
#define MBCSMR1_BAM_BITNUM              16U


/*** MBCSCR1 - Chip Select Control Register 1; 0xFFFFE814 ***/
typedef union {
  dword Dword;
  struct {
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword PS0        :1;                                       /* Port size. Specifies the width of the data associated with each chip select. It determines where data is driven during write cycles and where data is sampled during read cycles, bit 0 */
    dword PS1        :1;                                       /* Port size. Specifies the width of the data associated with each chip select. It determines where data is driven during write cycles and where data is sampled during read cycles, bit 1 */
    dword AA         :1;                                       /* Auto-acknowledge enable. Determines the assertion of the internal transfer acknowledge for accesses specified by the chip select address. Note that if AA = 1 for a corresponding CSn and the external system asserts an external TA before the wait-state countdown asserts the internal TA, the cycle is terminated. Burst cycles increment the address bus between each internal termination */
    dword MUX        :1;                                       /* Multiplexed mode */
    dword WS0        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 0 */
    dword WS1        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 1 */
    dword WS2        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 2 */
    dword WS3        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 3 */
    dword WS4        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 4 */
    dword WS5        :1;                                       /* Wait states. The number of wait states inserted after FB_CSn asserts and before an internal transfer acknowledge<br/>is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states), bit 5 */
    dword WRAH0      :1;                                       /* Write address hold or deselect, bit 0 */
    dword WRAH1      :1;                                       /* Write address hold or deselect, bit 1 */
    dword RDAH0      :1;                                       /* Read address hold or deselect, bit 0 */
    dword RDAH1      :1;                                       /* Read address hold or deselect, bit 1 */
    dword ASET0      :1;                                       /* Address setup, bit 0 */
    dword ASET1      :1;                                       /* Address setup, bit 1 */
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
    dword            :1; 
  } Bits;
  struct {
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword grpPS  :2;
    dword grpAx  :1;
    dword        :1;
    dword grpWS  :6;
    dword grpWRAH :2;
    dword grpRDAH :2;
    dword grpASET :2;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
    dword        :1;
  } MergedBits;
} MBCSCR1STR;
extern volatile MBCSCR1STR _MBCSCR1 @0xFFFFE814;
#define MBCSCR1                         _MBCSCR1.Dword
#define MBCSCR1_PS0                     _MBCSCR1.Bits.PS0
#define MBCSCR1_PS1                     _MBCSCR1.Bits.PS1
#define MBCSCR1_AA                      _MBCSCR1.Bits.AA
#define MBCSCR1_MUX                     _MBCSCR1.Bits.MUX
#define MBCSCR1_WS0                     _MBCSCR1.Bits.WS0
#define MBCSCR1_WS1                     _MBCSCR1.Bits.WS1
#define MBCSCR1_WS2                     _MBCSCR1.Bits.WS2
#define MBCSCR1_WS3                     _MBCSCR1.Bits.WS3
#define MBCSCR1_WS4                     _MBCSCR1.Bits.WS4
#define MBCSCR1_WS5                     _MBCSCR1.Bits.WS5
#define MBCSCR1_WRAH0                   _MBCSCR1.Bits.WRAH0
#define MBCSCR1_WRAH1                   _MBCSCR1.Bits.WRAH1
#define MBCSCR1_RDAH0                   _MBCSCR1.Bits.RDAH0
#define MBCSCR1_RDAH1                   _MBCSCR1.Bits.RDAH1
#define MBCSCR1_ASET0                   _MBCSCR1.Bits.ASET0
#define MBCSCR1_ASET1                   _MBCSCR1.Bits.ASET1
#define MBCSCR1_PS                      _MBCSCR1.MergedBits.grpPS
#define MBCSCR1_WS                      _MBCSCR1.MergedBits.grpWS
#define MBCSCR1_WRAH                    _MBCSCR1.MergedBits.grpWRAH
#define MBCSCR1_RDAH                    _MBCSCR1.MergedBits.grpRDAH
#define MBCSCR1_ASET                    _MBCSCR1.MergedBits.grpASET

#define MBCSCR1_PS0_MASK                64UL
#define MBCSCR1_PS1_MASK                128UL
#define MBCSCR1_AA_MASK                 256UL
#define MBCSCR1_MUX_MASK                512UL
#define MBCSCR1_WS0_MASK                1024UL
#define MBCSCR1_WS1_MASK                2048UL
#define MBCSCR1_WS2_MASK                4096UL
#define MBCSCR1_WS3_MASK                8192UL
#define MBCSCR1_WS4_MASK                16384UL
#define MBCSCR1_WS5_MASK                32768UL
#define MBCSCR1_WRAH0_MASK              65536UL
#define MBCSCR1_WRAH1_MASK              131072UL
#define MBCSCR1_RDAH0_MASK              262144UL
#define MBCSCR1_RDAH1_MASK              524288UL
#define MBCSCR1_ASET0_MASK              1048576UL
#define MBCSCR1_ASET1_MASK              2097152UL
#define MBCSCR1_PS_MASK                 192U
#define MBCSCR1_PS_BITNUM               6U
#define MBCSCR1_WS_MASK                 64512U
#define MBCSCR1_WS_BITNUM               10U
#define MBCSCR1_WRAH_MASK               196608U
#define MBCSCR1_WRAH_BITNUM             16U
#define MBCSCR1_RDAH_MASK               786432U
#define MBCSCR1_RDAH_BITNUM             18U
#define MBCSCR1_ASET_MASK               3145728U
#define MBCSCR1_ASET_BITNUM             20U


/*** INTC_FRC - INTC Force Interrupt Register; 0xFFFFFFD0 ***/
typedef union {
  byte Byte;
  struct {
    byte LVL7        :1;                                       /* Force Level 7 interrupt */
    byte LVL6        :1;                                       /* Force Level 6 interrupt */
    byte LVL5        :1;                                       /* Force Level 5 interrupt */
    byte LVL4        :1;                                       /* Force Level 4 interrupt */
    byte LVL3        :1;                                       /* Force Level 3 interrupt */
    byte LVL2        :1;                                       /* Force Level 2 interrupt */
    byte LVL1        :1;                                       /* Force Level 1 interrupt */
    byte             :1; 
  } Bits;
} INTC_FRCSTR;
extern volatile INTC_FRCSTR _INTC_FRC @0xFFFFFFD0;
#define INTC_FRC                        _INTC_FRC.Byte
#define INTC_FRC_LVL7                   _INTC_FRC.Bits.LVL7
#define INTC_FRC_LVL6                   _INTC_FRC.Bits.LVL6
#define INTC_FRC_LVL5                   _INTC_FRC.Bits.LVL5
#define INTC_FRC_LVL4                   _INTC_FRC.Bits.LVL4
#define INTC_FRC_LVL3                   _INTC_FRC.Bits.LVL3
#define INTC_FRC_LVL2                   _INTC_FRC.Bits.LVL2
#define INTC_FRC_LVL1                   _INTC_FRC.Bits.LVL1

#define INTC_FRC_LVL7_MASK              1U
#define INTC_FRC_LVL6_MASK              2U
#define INTC_FRC_LVL5_MASK              4U
#define INTC_FRC_LVL4_MASK              8U
#define INTC_FRC_LVL3_MASK              16U
#define INTC_FRC_LVL2_MASK              32U
#define INTC_FRC_LVL1_MASK              64U


/*** INTC_PL6P7 - INTC Programmable Level 6, Priority 7 Register; 0xFFFFFFD8 ***/
typedef union {
  byte Byte;
  struct {
    byte REQN0       :1;                                       /* Request number, bit 0 */
    byte REQN1       :1;                                       /* Request number, bit 1 */
    byte REQN2       :1;                                       /* Request number, bit 2 */
    byte REQN3       :1;                                       /* Request number, bit 3 */
    byte REQN4       :1;                                       /* Request number, bit 4 */
    byte REQN5       :1;                                       /* Request number, bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpREQN :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} INTC_PL6P7STR;
extern volatile INTC_PL6P7STR _INTC_PL6P7 @0xFFFFFFD8;
#define INTC_PL6P7                      _INTC_PL6P7.Byte
#define INTC_PL6P7_REQN0                _INTC_PL6P7.Bits.REQN0
#define INTC_PL6P7_REQN1                _INTC_PL6P7.Bits.REQN1
#define INTC_PL6P7_REQN2                _INTC_PL6P7.Bits.REQN2
#define INTC_PL6P7_REQN3                _INTC_PL6P7.Bits.REQN3
#define INTC_PL6P7_REQN4                _INTC_PL6P7.Bits.REQN4
#define INTC_PL6P7_REQN5                _INTC_PL6P7.Bits.REQN5
#define INTC_PL6P7_REQN                 _INTC_PL6P7.MergedBits.grpREQN

#define INTC_PL6P7_REQN0_MASK           1U
#define INTC_PL6P7_REQN1_MASK           2U
#define INTC_PL6P7_REQN2_MASK           4U
#define INTC_PL6P7_REQN3_MASK           8U
#define INTC_PL6P7_REQN4_MASK           16U
#define INTC_PL6P7_REQN5_MASK           32U
#define INTC_PL6P7_REQN_MASK            63U
#define INTC_PL6P7_REQN_BITNUM          0U


/*** INTC_PL6P6 - INTC Programmable Level 6, Priority 6 Register; 0xFFFFFFD9 ***/
typedef union {
  byte Byte;
  struct {
    byte REQN0       :1;                                       /* Request number, bit 0 */
    byte REQN1       :1;                                       /* Request number, bit 1 */
    byte REQN2       :1;                                       /* Request number, bit 2 */
    byte REQN3       :1;                                       /* Request number, bit 3 */
    byte REQN4       :1;                                       /* Request number, bit 4 */
    byte REQN5       :1;                                       /* Request number, bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpREQN :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} INTC_PL6P6STR;
extern volatile INTC_PL6P6STR _INTC_PL6P6 @0xFFFFFFD9;
#define INTC_PL6P6                      _INTC_PL6P6.Byte
#define INTC_PL6P6_REQN0                _INTC_PL6P6.Bits.REQN0
#define INTC_PL6P6_REQN1                _INTC_PL6P6.Bits.REQN1
#define INTC_PL6P6_REQN2                _INTC_PL6P6.Bits.REQN2
#define INTC_PL6P6_REQN3                _INTC_PL6P6.Bits.REQN3
#define INTC_PL6P6_REQN4                _INTC_PL6P6.Bits.REQN4
#define INTC_PL6P6_REQN5                _INTC_PL6P6.Bits.REQN5
#define INTC_PL6P6_REQN                 _INTC_PL6P6.MergedBits.grpREQN

#define INTC_PL6P6_REQN0_MASK           1U
#define INTC_PL6P6_REQN1_MASK           2U
#define INTC_PL6P6_REQN2_MASK           4U
#define INTC_PL6P6_REQN3_MASK           8U
#define INTC_PL6P6_REQN4_MASK           16U
#define INTC_PL6P6_REQN5_MASK           32U
#define INTC_PL6P6_REQN_MASK            63U
#define INTC_PL6P6_REQN_BITNUM          0U


/*** INTC_WCR - INTC Wake-up Control Register; 0xFFFFFFDB ***/
typedef union {
  byte Byte;
  struct {
    byte MASK0       :1;                                       /* Interrupt mask level, bit 0 */
    byte MASK1       :1;                                       /* Interrupt mask level, bit 1 */
    byte MASK2       :1;                                       /* Interrupt mask level, bit 2 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ENB         :1;                                       /* Enable */
  } Bits;
  struct {
    byte grpMASK :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} INTC_WCRSTR;
extern volatile INTC_WCRSTR _INTC_WCR @0xFFFFFFDB;
#define INTC_WCR                        _INTC_WCR.Byte
#define INTC_WCR_MASK0                  _INTC_WCR.Bits.MASK0
#define INTC_WCR_MASK1                  _INTC_WCR.Bits.MASK1
#define INTC_WCR_MASK2                  _INTC_WCR.Bits.MASK2
#define INTC_WCR_ENB                    _INTC_WCR.Bits.ENB
#define INTC_WCR_MASK                   _INTC_WCR.MergedBits.grpMASK

#define INTC_WCR_MASK0_MASK             1U
#define INTC_WCR_MASK1_MASK             2U
#define INTC_WCR_MASK2_MASK             4U
#define INTC_WCR_ENB_MASK               128U
#define INTC_WCR_MASK_MASK              7U
#define INTC_WCR_MASK_BITNUM            0U


/*** INTC_SFRC - INTC Set Interrupt Force Register; 0xFFFFFFDE ***/
typedef union {
  byte Byte;
  struct {
    byte SET0        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 0 */
    byte SET1        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 1 */
    byte SET2        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 2 */
    byte SET3        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 3 */
    byte SET4        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 4 */
    byte SET5        :1;                                       /* Sets corresponding bits in the INTC_FRC register, bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpSET  :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} INTC_SFRCSTR;
extern volatile INTC_SFRCSTR _INTC_SFRC @0xFFFFFFDE;
#define INTC_SFRC                       _INTC_SFRC.Byte
#define INTC_SFRC_SET0                  _INTC_SFRC.Bits.SET0
#define INTC_SFRC_SET1                  _INTC_SFRC.Bits.SET1
#define INTC_SFRC_SET2                  _INTC_SFRC.Bits.SET2
#define INTC_SFRC_SET3                  _INTC_SFRC.Bits.SET3
#define INTC_SFRC_SET4                  _INTC_SFRC.Bits.SET4
#define INTC_SFRC_SET5                  _INTC_SFRC.Bits.SET5
#define INTC_SFRC_SET                   _INTC_SFRC.MergedBits.grpSET

#define INTC_SFRC_SET0_MASK             1U
#define INTC_SFRC_SET1_MASK             2U
#define INTC_SFRC_SET2_MASK             4U
#define INTC_SFRC_SET3_MASK             8U
#define INTC_SFRC_SET4_MASK             16U
#define INTC_SFRC_SET5_MASK             32U
#define INTC_SFRC_SET_MASK              63U
#define INTC_SFRC_SET_BITNUM            0U


/*** INTC_CFRC - INTC Clear Interrupt Force Register; 0xFFFFFFDF ***/
typedef union {
  byte Byte;
  struct {
    byte CLR0        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 0 */
    byte CLR1        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 1 */
    byte CLR2        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 2 */
    byte CLR3        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 3 */
    byte CLR4        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 4 */
    byte CLR5        :1;                                       /* Clears corresponding bits in the INTC_FRC register, bit 5 */
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpCLR  :6;
    byte         :1;
    byte         :1;
  } MergedBits;
} INTC_CFRCSTR;
extern volatile INTC_CFRCSTR _INTC_CFRC @0xFFFFFFDF;
#define INTC_CFRC                       _INTC_CFRC.Byte
#define INTC_CFRC_CLR0                  _INTC_CFRC.Bits.CLR0
#define INTC_CFRC_CLR1                  _INTC_CFRC.Bits.CLR1
#define INTC_CFRC_CLR2                  _INTC_CFRC.Bits.CLR2
#define INTC_CFRC_CLR3                  _INTC_CFRC.Bits.CLR3
#define INTC_CFRC_CLR4                  _INTC_CFRC.Bits.CLR4
#define INTC_CFRC_CLR5                  _INTC_CFRC.Bits.CLR5
#define INTC_CFRC_CLR                   _INTC_CFRC.MergedBits.grpCLR

#define INTC_CFRC_CLR0_MASK             1U
#define INTC_CFRC_CLR1_MASK             2U
#define INTC_CFRC_CLR2_MASK             4U
#define INTC_CFRC_CLR3_MASK             8U
#define INTC_CFRC_CLR4_MASK             16U
#define INTC_CFRC_CLR5_MASK             32U
#define INTC_CFRC_CLR_MASK              63U
#define INTC_CFRC_CLR_BITNUM            0U


/*** INTC_SWIACK - INTC Software IACK Register; 0xFFFFFFE0 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_SWIACKSTR;
extern volatile INTC_SWIACKSTR _INTC_SWIACK @0xFFFFFFE0;
#define INTC_SWIACK                     _INTC_SWIACK.Byte
#define INTC_SWIACK_VECN0               _INTC_SWIACK.Bits.VECN0
#define INTC_SWIACK_VECN1               _INTC_SWIACK.Bits.VECN1
#define INTC_SWIACK_VECN2               _INTC_SWIACK.Bits.VECN2
#define INTC_SWIACK_VECN3               _INTC_SWIACK.Bits.VECN3
#define INTC_SWIACK_VECN4               _INTC_SWIACK.Bits.VECN4
#define INTC_SWIACK_VECN5               _INTC_SWIACK.Bits.VECN5
#define INTC_SWIACK_VECN6               _INTC_SWIACK.Bits.VECN6
#define INTC_SWIACK_VECN                _INTC_SWIACK.MergedBits.grpVECN

#define INTC_SWIACK_VECN0_MASK          1U
#define INTC_SWIACK_VECN1_MASK          2U
#define INTC_SWIACK_VECN2_MASK          4U
#define INTC_SWIACK_VECN3_MASK          8U
#define INTC_SWIACK_VECN4_MASK          16U
#define INTC_SWIACK_VECN5_MASK          32U
#define INTC_SWIACK_VECN6_MASK          64U
#define INTC_SWIACK_VECN_MASK           127U
#define INTC_SWIACK_VECN_BITNUM         0U


/*** INTC_LVL1IACK - INTC Level 1 IACK Register; 0xFFFFFFE4 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL1IACKSTR;
extern volatile INTC_LVL1IACKSTR _INTC_LVL1IACK @0xFFFFFFE4;
#define INTC_LVL1IACK                   _INTC_LVL1IACK.Byte
#define INTC_LVL1IACK_VECN0             _INTC_LVL1IACK.Bits.VECN0
#define INTC_LVL1IACK_VECN1             _INTC_LVL1IACK.Bits.VECN1
#define INTC_LVL1IACK_VECN2             _INTC_LVL1IACK.Bits.VECN2
#define INTC_LVL1IACK_VECN3             _INTC_LVL1IACK.Bits.VECN3
#define INTC_LVL1IACK_VECN4             _INTC_LVL1IACK.Bits.VECN4
#define INTC_LVL1IACK_VECN5             _INTC_LVL1IACK.Bits.VECN5
#define INTC_LVL1IACK_VECN6             _INTC_LVL1IACK.Bits.VECN6
#define INTC_LVL1IACK_VECN              _INTC_LVL1IACK.MergedBits.grpVECN

#define INTC_LVL1IACK_VECN0_MASK        1U
#define INTC_LVL1IACK_VECN1_MASK        2U
#define INTC_LVL1IACK_VECN2_MASK        4U
#define INTC_LVL1IACK_VECN3_MASK        8U
#define INTC_LVL1IACK_VECN4_MASK        16U
#define INTC_LVL1IACK_VECN5_MASK        32U
#define INTC_LVL1IACK_VECN6_MASK        64U
#define INTC_LVL1IACK_VECN_MASK         127U
#define INTC_LVL1IACK_VECN_BITNUM       0U


/*** INTC_LVL2IACK - INTC Level 2 IACK Register; 0xFFFFFFE8 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL2IACKSTR;
extern volatile INTC_LVL2IACKSTR _INTC_LVL2IACK @0xFFFFFFE8;
#define INTC_LVL2IACK                   _INTC_LVL2IACK.Byte
#define INTC_LVL2IACK_VECN0             _INTC_LVL2IACK.Bits.VECN0
#define INTC_LVL2IACK_VECN1             _INTC_LVL2IACK.Bits.VECN1
#define INTC_LVL2IACK_VECN2             _INTC_LVL2IACK.Bits.VECN2
#define INTC_LVL2IACK_VECN3             _INTC_LVL2IACK.Bits.VECN3
#define INTC_LVL2IACK_VECN4             _INTC_LVL2IACK.Bits.VECN4
#define INTC_LVL2IACK_VECN5             _INTC_LVL2IACK.Bits.VECN5
#define INTC_LVL2IACK_VECN6             _INTC_LVL2IACK.Bits.VECN6
#define INTC_LVL2IACK_VECN              _INTC_LVL2IACK.MergedBits.grpVECN

#define INTC_LVL2IACK_VECN0_MASK        1U
#define INTC_LVL2IACK_VECN1_MASK        2U
#define INTC_LVL2IACK_VECN2_MASK        4U
#define INTC_LVL2IACK_VECN3_MASK        8U
#define INTC_LVL2IACK_VECN4_MASK        16U
#define INTC_LVL2IACK_VECN5_MASK        32U
#define INTC_LVL2IACK_VECN6_MASK        64U
#define INTC_LVL2IACK_VECN_MASK         127U
#define INTC_LVL2IACK_VECN_BITNUM       0U


/*** INTC_LVL3IACK - INTC Level 3 IACK Register; 0xFFFFFFEC ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL3IACKSTR;
extern volatile INTC_LVL3IACKSTR _INTC_LVL3IACK @0xFFFFFFEC;
#define INTC_LVL3IACK                   _INTC_LVL3IACK.Byte
#define INTC_LVL3IACK_VECN0             _INTC_LVL3IACK.Bits.VECN0
#define INTC_LVL3IACK_VECN1             _INTC_LVL3IACK.Bits.VECN1
#define INTC_LVL3IACK_VECN2             _INTC_LVL3IACK.Bits.VECN2
#define INTC_LVL3IACK_VECN3             _INTC_LVL3IACK.Bits.VECN3
#define INTC_LVL3IACK_VECN4             _INTC_LVL3IACK.Bits.VECN4
#define INTC_LVL3IACK_VECN5             _INTC_LVL3IACK.Bits.VECN5
#define INTC_LVL3IACK_VECN6             _INTC_LVL3IACK.Bits.VECN6
#define INTC_LVL3IACK_VECN              _INTC_LVL3IACK.MergedBits.grpVECN

#define INTC_LVL3IACK_VECN0_MASK        1U
#define INTC_LVL3IACK_VECN1_MASK        2U
#define INTC_LVL3IACK_VECN2_MASK        4U
#define INTC_LVL3IACK_VECN3_MASK        8U
#define INTC_LVL3IACK_VECN4_MASK        16U
#define INTC_LVL3IACK_VECN5_MASK        32U
#define INTC_LVL3IACK_VECN6_MASK        64U
#define INTC_LVL3IACK_VECN_MASK         127U
#define INTC_LVL3IACK_VECN_BITNUM       0U


/*** INTC_LVL4IACK - INTC Level 4 IACK Register; 0xFFFFFFF0 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL4IACKSTR;
extern volatile INTC_LVL4IACKSTR _INTC_LVL4IACK @0xFFFFFFF0;
#define INTC_LVL4IACK                   _INTC_LVL4IACK.Byte
#define INTC_LVL4IACK_VECN0             _INTC_LVL4IACK.Bits.VECN0
#define INTC_LVL4IACK_VECN1             _INTC_LVL4IACK.Bits.VECN1
#define INTC_LVL4IACK_VECN2             _INTC_LVL4IACK.Bits.VECN2
#define INTC_LVL4IACK_VECN3             _INTC_LVL4IACK.Bits.VECN3
#define INTC_LVL4IACK_VECN4             _INTC_LVL4IACK.Bits.VECN4
#define INTC_LVL4IACK_VECN5             _INTC_LVL4IACK.Bits.VECN5
#define INTC_LVL4IACK_VECN6             _INTC_LVL4IACK.Bits.VECN6
#define INTC_LVL4IACK_VECN              _INTC_LVL4IACK.MergedBits.grpVECN

#define INTC_LVL4IACK_VECN0_MASK        1U
#define INTC_LVL4IACK_VECN1_MASK        2U
#define INTC_LVL4IACK_VECN2_MASK        4U
#define INTC_LVL4IACK_VECN3_MASK        8U
#define INTC_LVL4IACK_VECN4_MASK        16U
#define INTC_LVL4IACK_VECN5_MASK        32U
#define INTC_LVL4IACK_VECN6_MASK        64U
#define INTC_LVL4IACK_VECN_MASK         127U
#define INTC_LVL4IACK_VECN_BITNUM       0U


/*** INTC_LVL5IACK - INTC Level 5 IACK Register; 0xFFFFFFF4 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL5IACKSTR;
extern volatile INTC_LVL5IACKSTR _INTC_LVL5IACK @0xFFFFFFF4;
#define INTC_LVL5IACK                   _INTC_LVL5IACK.Byte
#define INTC_LVL5IACK_VECN0             _INTC_LVL5IACK.Bits.VECN0
#define INTC_LVL5IACK_VECN1             _INTC_LVL5IACK.Bits.VECN1
#define INTC_LVL5IACK_VECN2             _INTC_LVL5IACK.Bits.VECN2
#define INTC_LVL5IACK_VECN3             _INTC_LVL5IACK.Bits.VECN3
#define INTC_LVL5IACK_VECN4             _INTC_LVL5IACK.Bits.VECN4
#define INTC_LVL5IACK_VECN5             _INTC_LVL5IACK.Bits.VECN5
#define INTC_LVL5IACK_VECN6             _INTC_LVL5IACK.Bits.VECN6
#define INTC_LVL5IACK_VECN              _INTC_LVL5IACK.MergedBits.grpVECN

#define INTC_LVL5IACK_VECN0_MASK        1U
#define INTC_LVL5IACK_VECN1_MASK        2U
#define INTC_LVL5IACK_VECN2_MASK        4U
#define INTC_LVL5IACK_VECN3_MASK        8U
#define INTC_LVL5IACK_VECN4_MASK        16U
#define INTC_LVL5IACK_VECN5_MASK        32U
#define INTC_LVL5IACK_VECN6_MASK        64U
#define INTC_LVL5IACK_VECN_MASK         127U
#define INTC_LVL5IACK_VECN_BITNUM       0U


/*** INTC_LVL6IACK - INTC Level 6 IACK Register; 0xFFFFFFF8 ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL6IACKSTR;
extern volatile INTC_LVL6IACKSTR _INTC_LVL6IACK @0xFFFFFFF8;
#define INTC_LVL6IACK                   _INTC_LVL6IACK.Byte
#define INTC_LVL6IACK_VECN0             _INTC_LVL6IACK.Bits.VECN0
#define INTC_LVL6IACK_VECN1             _INTC_LVL6IACK.Bits.VECN1
#define INTC_LVL6IACK_VECN2             _INTC_LVL6IACK.Bits.VECN2
#define INTC_LVL6IACK_VECN3             _INTC_LVL6IACK.Bits.VECN3
#define INTC_LVL6IACK_VECN4             _INTC_LVL6IACK.Bits.VECN4
#define INTC_LVL6IACK_VECN5             _INTC_LVL6IACK.Bits.VECN5
#define INTC_LVL6IACK_VECN6             _INTC_LVL6IACK.Bits.VECN6
#define INTC_LVL6IACK_VECN              _INTC_LVL6IACK.MergedBits.grpVECN

#define INTC_LVL6IACK_VECN0_MASK        1U
#define INTC_LVL6IACK_VECN1_MASK        2U
#define INTC_LVL6IACK_VECN2_MASK        4U
#define INTC_LVL6IACK_VECN3_MASK        8U
#define INTC_LVL6IACK_VECN4_MASK        16U
#define INTC_LVL6IACK_VECN5_MASK        32U
#define INTC_LVL6IACK_VECN6_MASK        64U
#define INTC_LVL6IACK_VECN_MASK         127U
#define INTC_LVL6IACK_VECN_BITNUM       0U


/*** INTC_LVL7IACK - INTC Level 7 IACK Register; 0xFFFFFFFC ***/
typedef union {
  byte Byte;
  struct {
    byte VECN0       :1;                                       /* Vector number, bit 0 */
    byte VECN1       :1;                                       /* Vector number, bit 1 */
    byte VECN2       :1;                                       /* Vector number, bit 2 */
    byte VECN3       :1;                                       /* Vector number, bit 3 */
    byte VECN4       :1;                                       /* Vector number, bit 4 */
    byte VECN5       :1;                                       /* Vector number, bit 5 */
    byte VECN6       :1;                                       /* Vector number, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpVECN :7;
    byte         :1;
  } MergedBits;
} INTC_LVL7IACKSTR;
extern volatile INTC_LVL7IACKSTR _INTC_LVL7IACK @0xFFFFFFFC;
#define INTC_LVL7IACK                   _INTC_LVL7IACK.Byte
#define INTC_LVL7IACK_VECN0             _INTC_LVL7IACK.Bits.VECN0
#define INTC_LVL7IACK_VECN1             _INTC_LVL7IACK.Bits.VECN1
#define INTC_LVL7IACK_VECN2             _INTC_LVL7IACK.Bits.VECN2
#define INTC_LVL7IACK_VECN3             _INTC_LVL7IACK.Bits.VECN3
#define INTC_LVL7IACK_VECN4             _INTC_LVL7IACK.Bits.VECN4
#define INTC_LVL7IACK_VECN5             _INTC_LVL7IACK.Bits.VECN5
#define INTC_LVL7IACK_VECN6             _INTC_LVL7IACK.Bits.VECN6
#define INTC_LVL7IACK_VECN              _INTC_LVL7IACK.MergedBits.grpVECN

#define INTC_LVL7IACK_VECN0_MASK        1U
#define INTC_LVL7IACK_VECN1_MASK        2U
#define INTC_LVL7IACK_VECN2_MASK        4U
#define INTC_LVL7IACK_VECN3_MASK        8U
#define INTC_LVL7IACK_VECN4_MASK        16U
#define INTC_LVL7IACK_VECN5_MASK        32U
#define INTC_LVL7IACK_VECN6_MASK        64U
#define INTC_LVL7IACK_VECN_MASK         127U
#define INTC_LVL7IACK_VECN_BITNUM       0U



/***********************************************/
/**   D E P R E C I A T E D   S Y M B O L S   **/
/***********************************************/
/* --------------------------------------------------------------------------- */
/* The following symbols were removed, because they were invalid or irrelevant */
/* --------------------------------------------------------------------------- */



/* **** 3.6.2010 14:25:10 */

#/*** SOPT5 - System Options Register 5; 0xFFFF980D ***/
typedef union {
  byte Byte;
  struct {
    byte PMC_LVD_TRIM0 :1;                                     /* PMC LVD TRIM, bit 0 */
    byte PMC_LVD_TRIM1 :1;                                     /* PMC LVD TRIM, bit 1 */
    byte PMC_LVD_TRIM2 :1;                                     /* PMC LVD TRIM, bit 2 */
    byte PMC_LVD_TRIM3 :1;                                     /* PMC LVD TRIM, bit 3 */
    byte PMC_LVD_TRIM4 :1;                                     /* PMC LVD TRIM, bit 4 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpPMC_LVD_TRIM :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SOPT5STR;
extern volatile SOPT5STR _SOPT5 @0xFFFF980D;
#define SOPT5                           _SOPT5.Byte
#define SOPT5_PMC_LVD_TRIM0             _SOPT5.Bits.PMC_LVD_TRIM0
#define SOPT5_PMC_LVD_TRIM1             _SOPT5.Bits.PMC_LVD_TRIM1
#define SOPT5_PMC_LVD_TRIM2             _SOPT5.Bits.PMC_LVD_TRIM2
#define SOPT5_PMC_LVD_TRIM3             _SOPT5.Bits.PMC_LVD_TRIM3
#define SOPT5_PMC_LVD_TRIM4             _SOPT5.Bits.PMC_LVD_TRIM4
#define SOPT5_PMC_LVD_TRIM              _SOPT5.MergedBits.grpPMC_LVD_TRIM

#define SOPT5_PMC_LVD_TRIM0_MASK        1
#define SOPT5_PMC_LVD_TRIM1_MASK        2
#define SOPT5_PMC_LVD_TRIM2_MASK        4
#define SOPT5_PMC_LVD_TRIM3_MASK        8
#define SOPT5_PMC_LVD_TRIM4_MASK        16
#define SOPT5_PMC_LVD_TRIM_MASK         31
#define SOPT5_PMC_LVD_TRIM_BITNUM       0

#define VectorNumber_VReserved72            This_symb_has_been_depreciated
#define VReserved72                         This_symb_has_been_depreciated
#pragma options align=reset

#endif
/*lint -restore Enable MISRA rule (5.1) checking. */
/*lint -restore  +esym(961,18.4) +esym(961,19.7) Enable MISRA rule (1.1,18.4,6.4,19.7) checking. */
