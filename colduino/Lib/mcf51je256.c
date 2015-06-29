/* Based on CPU DB MCF51JE256_104, version 3.00.012 (RegistersPrg V2.32) */
/* DataSheet : MCF51JE256 Rev. 1 07/2009 */

#include <mcf51je256.h>

/*lint -save -esym(765, *) */


/* * * * *  8-BIT REGISTERS  * * * * * * * * * * * * * * * */
/* NV1FTRIM - macro for reading non volatile register      Nonvolatile MCG Fine Trim; 0x000003FE */
/* Tip for register initialization in the user code:  const byte NV1FTRIM_INIT @0x000003FE = <NV1FTRIM_INITVAL>; */
/* NV1MCGTRM - macro for reading non volatile register     Nonvolatile MCG Trim Register; 0x000003FF */
/* Tip for register initialization in the user code:  const byte NV1MCGTRM_INIT @0x000003FF = <NV1MCGTRM_INITVAL>; */
/* NV1BACKKEY0 - macro for reading non volatile register   Backdoor Comparison Key 0; 0x00000400 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY0_INIT @0x00000400 = <NV1BACKKEY0_INITVAL>; */
/* NV1BACKKEY1 - macro for reading non volatile register   Backdoor Comparison Key 1; 0x00000401 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY1_INIT @0x00000401 = <NV1BACKKEY1_INITVAL>; */
/* NV1BACKKEY2 - macro for reading non volatile register   Backdoor Comparison Key 2; 0x00000402 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY2_INIT @0x00000402 = <NV1BACKKEY2_INITVAL>; */
/* NV1BACKKEY3 - macro for reading non volatile register   Backdoor Comparison Key 3; 0x00000403 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY3_INIT @0x00000403 = <NV1BACKKEY3_INITVAL>; */
/* NV1BACKKEY4 - macro for reading non volatile register   Backdoor Comparison Key 4; 0x00000404 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY4_INIT @0x00000404 = <NV1BACKKEY4_INITVAL>; */
/* NV1BACKKEY5 - macro for reading non volatile register   Backdoor Comparison Key 5; 0x00000405 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY5_INIT @0x00000405 = <NV1BACKKEY5_INITVAL>; */
/* NV1BACKKEY6 - macro for reading non volatile register   Backdoor Comparison Key 6; 0x00000406 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY6_INIT @0x00000406 = <NV1BACKKEY6_INITVAL>; */
/* NV1BACKKEY7 - macro for reading non volatile register   Backdoor Comparison Key 7; 0x00000407 */
/* Tip for register initialization in the user code:  const byte NV1BACKKEY7_INIT @0x00000407 = <NV1BACKKEY7_INITVAL>; */
/* CHKSBYP1 - macro for reading non volatile register      Checksum Bypass Register; 0x0000040A */
/* Tip for register initialization in the user code:  const byte CHKSBYP1_INIT @0x0000040A = <CHKSBYP1_INITVAL>; */
/* Partial_Erase_Semaphore1 - macro for reading non volatile register Flash partial erase semaphore; 0x0000040B */
/* Tip for register initialization in the user code:  const byte Partial_Erase_Semaphore1_INIT @0x0000040B = <Partial_Erase_Semaphore1_INITVAL>; */
/* NV1PROT - macro for reading non volatile register       Nonvolatile Flash Protection Register; 0x0000040D */
/* Tip for register initialization in the user code:  const byte NV1PROT_INIT @0x0000040D = <NV1PROT_INITVAL>; */
/* NV1OPT - macro for reading non volatile register        Nonvolatile Flash Options Register; 0x0000040F */
/* Tip for register initialization in the user code:  const byte NV1OPT_INIT @0x0000040F = <NV1OPT_INITVAL>; */
/* FLASHAS - macro for reading non volatile register       Flash Array Select Register; 0x00000410 */
/* Tip for register initialization in the user code:  const byte FLASHAS_INIT @0x00000410 = <FLASHAS_INITVAL>; */
/* NV2FTRIM - macro for reading non volatile register      Nonvolatile MCG Fine Trim; 0x000203FE */
/* Tip for register initialization in the user code:  const byte NV2FTRIM_INIT @0x000203FE = <NV2FTRIM_INITVAL>; */
/* NV2MCGTRM - macro for reading non volatile register     Nonvolatile MCG Trim Register; 0x000203FF */
/* Tip for register initialization in the user code:  const byte NV2MCGTRM_INIT @0x000203FF = <NV2MCGTRM_INITVAL>; */
/* NV2BACKKEY0 - macro for reading non volatile register   Backdoor Comparison Key 0; 0x00020400 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY0_INIT @0x00020400 = <NV2BACKKEY0_INITVAL>; */
/* NV2BACKKEY1 - macro for reading non volatile register   Backdoor Comparison Key 1; 0x00020401 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY1_INIT @0x00020401 = <NV2BACKKEY1_INITVAL>; */
/* NV2BACKKEY2 - macro for reading non volatile register   Backdoor Comparison Key 2; 0x00020402 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY2_INIT @0x00020402 = <NV2BACKKEY2_INITVAL>; */
/* NV2BACKKEY3 - macro for reading non volatile register   Backdoor Comparison Key 3; 0x00020403 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY3_INIT @0x00020403 = <NV2BACKKEY3_INITVAL>; */
/* NV2BACKKEY4 - macro for reading non volatile register   Backdoor Comparison Key 4; 0x00020404 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY4_INIT @0x00020404 = <NV2BACKKEY4_INITVAL>; */
/* NV2BACKKEY5 - macro for reading non volatile register   Backdoor Comparison Key 5; 0x00020405 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY5_INIT @0x00020405 = <NV2BACKKEY5_INITVAL>; */
/* NV2BACKKEY6 - macro for reading non volatile register   Backdoor Comparison Key 6; 0x00020406 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY6_INIT @0x00020406 = <NV2BACKKEY6_INITVAL>; */
/* NV2BACKKEY7 - macro for reading non volatile register   Backdoor Comparison Key 7; 0x00020407 */
/* Tip for register initialization in the user code:  const byte NV2BACKKEY7_INIT @0x00020407 = <NV2BACKKEY7_INITVAL>; */
/* CHKSBYP2 - macro for reading non volatile register      Checksum Bypass Register; 0x0002040A */
/* Tip for register initialization in the user code:  const byte CHKSBYP2_INIT @0x0002040A = <CHKSBYP2_INITVAL>; */
/* Partial_Erase_Semaphore2 - macro for reading non volatile register Flash partial erase semaphore; 0x0002040B */
/* Tip for register initialization in the user code:  const byte Partial_Erase_Semaphore2_INIT @0x0002040B = <Partial_Erase_Semaphore2_INITVAL>; */
/* NV2PROT - macro for reading non volatile register       Nonvolatile Flash Protection Register; 0x0002040D */
/* Tip for register initialization in the user code:  const byte NV2PROT_INIT @0x0002040D = <NV2PROT_INITVAL>; */
/* NV2OPT - macro for reading non volatile register        Nonvolatile Flash Options Register; 0x0002040F */
/* Tip for register initialization in the user code:  const byte NV2OPT_INIT @0x0002040F = <NV2OPT_INITVAL>; */
volatile PTADSTR _PTAD;                                    /* Port A Data Register; 0xFFFF8000 */
volatile PTADDSTR _PTADD;                                  /* Port A Data Direction Register; 0xFFFF8001 */
volatile PTBDSTR _PTBD;                                    /* Port B Data Register; 0xFFFF8002 */
volatile PTBDDSTR _PTBDD;                                  /* Port B Data Direction Register; 0xFFFF8003 */
volatile PTCDSTR _PTCD;                                    /* Port C Data Register; 0xFFFF8004 */
volatile PTCDDSTR _PTCDD;                                  /* Port C Data Direction Register; 0xFFFF8005 */
volatile PTDDSTR _PTDD;                                    /* Port D Data Register; 0xFFFF8006 */
volatile PTDDDSTR _PTDDD;                                  /* Port D Data Direction Register; 0xFFFF8007 */
volatile DACSSTR _DACS;                                    /* DAC Status Register; 0xFFFF8030 */
volatile DACC0STR _DACC0;                                  /* DAC Control 0 Register; 0xFFFF8031 */
volatile DACC1STR _DACC1;                                  /* DAC Control 1 Register; 0xFFFF8032 */
volatile DACC2STR _DACC2;                                  /* DAC Control 2 Register; 0xFFFF8033 */
volatile PRACMPCSSTR _PRACMPCS;                            /* PRACMP Control and Status Register; 0xFFFF8034 */
volatile PRACMPC0STR _PRACMPC0;                            /* PRACMP Control 0 Register; 0xFFFF8035 */
volatile PRACMPC1STR _PRACMPC1;                            /* PRACMP Control 1 Register; 0xFFFF8036 */
volatile PRACMPC2STR _PRACMPC2;                            /* PRACMP Control 2 Register; 0xFFFF8037 */
volatile MCGC1STR _MCGC1;                                  /* MCG Control Register 1; 0xFFFF8038 */
volatile MCGC2STR _MCGC2;                                  /* MCG Control Register 2; 0xFFFF8039 */
volatile MCGTRMSTR _MCGTRM;                                /* MCG Trim Register; 0xFFFF803A */
volatile MCGSCSTR _MCGSC;                                  /* MCG Status and Control Register; 0xFFFF803B */
volatile MCGC3STR _MCGC3;                                  /* MCG Control Register 3; 0xFFFF803C */
volatile MCGC4STR _MCGC4;                                  /* MCG Control Register 4; 0xFFFF803D */
volatile ADCSC1STR _ADCSC1;                                /* Status and Control Register 1A; 0xFFFF8040 */
volatile ADCCFG1STR _ADCCFG1;                              /* Configuration Register 1; 0xFFFF8048 */
volatile ADCCFG2STR _ADCCFG2;                              /* Configuration Register 2; 0xFFFF8049 */
volatile VREFTRMSTR _VREFTRM;                              /* VREF Trim Register; 0xFFFF805C */
volatile VREFSCSTR _VREFSC;                                /* VREF Control Register; 0xFFFF805D */
volatile IRQSCSTR _IRQSC;                                  /* Interrupt request status and control register; 0xFFFF805F */
volatile IICA1STR _IICA1;                                  /* IIC Address Register; 0xFFFF8060 */
volatile IICFSTR _IICF;                                    /* IIC Frequency Divider Register; 0xFFFF8061 */
volatile IICC1STR _IICC1;                                  /* IIC Control Register 1; 0xFFFF8062 */
volatile IICSSTR _IICS;                                    /* IIC Status Register; 0xFFFF8063 */
volatile IICDSTR _IICD;                                    /* IIC Data I/O Register; 0xFFFF8064 */
volatile IICC2STR _IICC2;                                  /* IIC Control Register 2; 0xFFFF8065 */
volatile IICSMBSTR _IICSMB;                                /* SMBus Control and Status Register; 0xFFFF8066 */
volatile IICA2STR _IICA2;                                  /* IIC Address Register 2; 0xFFFF8067 */
volatile IICFLTSTR _IICFLT;                                /* IIC Filter register; 0xFFFF806A */
volatile KBI1SCSTR _KBI1SC;                                /* KBI1 Status and Control Register; 0xFFFF806C */
volatile KBI1PESTR _KBI1PE;                                /* KBI1 Pin Enable Register; 0xFFFF806D */
volatile KBI1ESSTR _KBI1ES;                                /* KBI1 Edge Select Register; 0xFFFF806E */
volatile SPI1C1STR _SPI1C1;                                /* SPI1 Control Register 1; 0xFFFF8070 */
volatile SPI1C2STR _SPI1C2;                                /* SPI1 Control Register 2; 0xFFFF8071 */
volatile SPI1BRSTR _SPI1BR;                                /* SPI1 Baud Rate Register; 0xFFFF8072 */
volatile SPI1SSTR _SPI1S;                                  /* SPI1 Status Register; 0xFFFF8073 */
volatile SPI1C3STR _SPI1C3;                                /* SPI1 Control Register 3; 0xFFFF8078 */
volatile SPI1CISTR _SPI1CI;                                /* SPI1 Clear Interrupt Register; 0xFFFF8079 */
volatile KBI2SCSTR _KBI2SC;                                /* KBI2 Status and Control Register; 0xFFFF807C */
volatile KBI2PESTR _KBI2PE;                                /* KBI2 Pin Enable Register; 0xFFFF807D */
volatile KBI2ESSTR _KBI2ES;                                /* KBI2 Edge Select Register; 0xFFFF807E */
volatile SRSSTR _SRS;                                      /* System Reset Status Register; 0xFFFF9800 */
volatile SOPT1STR _SOPT1;                                  /* System Options Register 1; 0xFFFF9802 */
volatile SOPT2STR _SOPT2;                                  /* System Options Register 2; 0xFFFF9803 */
volatile SCGC1STR _SCGC1;                                  /* System Clock Gating Control 1 Register; 0xFFFF9808 */
volatile SCGC2STR _SCGC2;                                  /* System Clock Gating Control 2 Register; 0xFFFF9809 */
volatile SCGC3STR _SCGC3;                                  /* System Clock Gating Control 3 Register; 0xFFFF980A */
volatile SOPT3STR _SOPT3;                                  /* System Options 3 Register; 0xFFFF980B */
volatile SOPT4STR _SOPT4;                                  /* System Options 4 Register; 0xFFFF980C */
volatile SIMIPSSTR _SIMIPS;                                /* SIM Internal Peripheral Select Register; 0xFFFF980E */
volatile SIGNATURESTR _SIGNATURE;                          /* SIGNATURE Register; 0xFFFF980F */
volatile CCSCTRLSTR _CCSCTRL;                              /* Clock Check & Select Control; 0xFFFF9810 */
volatile CCSTMR1STR _CCSTMR1;                              /* CCS XOSC1 Timer Register; 0xFFFF9811 */
volatile CCSTMR2STR _CCSTMR2;                              /* CCS XOSC2 Timer Register; 0xFFFF9812 */
volatile CCSTMRIRSTR _CCSTMRIR;                            /* CCS Internal Reference Clock Timer Register; 0xFFFF9813 */
volatile FPROTDSTR _FPROTD;                                /* Flash Protection Disable Register; 0xFFFF9814 */
volatile MFBPC1STR _MFBPC1;                                /* Mini-FlexBus Pin Control 1; 0xFFFF9815 */
volatile MFBPC2STR _MFBPC2;                                /* Mini-FlexBus Pin Control 2; 0xFFFF9816 */
volatile MFBPC3STR _MFBPC3;                                /* Mini-FlexBus Pin Control 3; 0xFFFF9817 */
volatile MFBPC4STR _MFBPC4;                                /* Mini-FlexBus Pin Control 4; 0xFFFF9818 */
volatile SIMCOSTR _SIMCO;                                  /* SIM Clock Set and Select Register; 0xFFFF9819 */
volatile SPMSC1STR _SPMSC1;                                /* System Power Management Status and Control 1 Register; 0xFFFF981C */
volatile SPMSC2STR _SPMSC2;                                /* System Power Management Status and Control 2 Register; 0xFFFF981D */
volatile SPMSC3STR _SPMSC3;                                /* System Power Management Status and Control 3 Register; 0xFFFF981F */
volatile PTEDSTR _PTED;                                    /* Port E Data Register; 0xFFFF9830 */
volatile PTEDDSTR _PTEDD;                                  /* Port E Data Direction Register; 0xFFFF9831 */
volatile PTFDSTR _PTFD;                                    /* Port F Data Register; 0xFFFF9832 */
volatile PTFDDSTR _PTFDD;                                  /* Port F Data Direction Register; 0xFFFF9833 */
volatile SCI2C1STR _SCI2C1;                                /* SCI2 Control Register 1; 0xFFFF983A */
volatile SCI2C2STR _SCI2C2;                                /* SCI2 Control Register 2; 0xFFFF983B */
volatile SCI2S1STR _SCI2S1;                                /* SCI2 Status Register 1; 0xFFFF983C */
volatile SCI2S2STR _SCI2S2;                                /* SCI2 Status Register 2; 0xFFFF983D */
volatile SCI2C3STR _SCI2C3;                                /* SCI2 Control Register 3; 0xFFFF983E */
volatile SCI2DSTR _SCI2D;                                  /* SCI2 Data Register; 0xFFFF983F */
volatile SPI2C1STR _SPI2C1;                                /* SPI2 Control Register 1; 0xFFFF9840 */
volatile SPI2C2STR _SPI2C2;                                /* SPI2 Control Register 2; 0xFFFF9841 */
volatile SPI2BRSTR _SPI2BR;                                /* SPI2 Baud Rate Register; 0xFFFF9842 */
volatile SPI2SSTR _SPI2S;                                  /* SPI2 Status Register; 0xFFFF9843 */
volatile SPI2DSTR _SPI2D;                                  /* SPI2 Data Register; 0xFFFF9845 */
volatile SPI2MSTR _SPI2M;                                  /* SPI2 Match Register; 0xFFFF9847 */
volatile PTGDSTR _PTGD;                                    /* Port G Data Register; 0xFFFF9848 */
volatile PTGDDSTR _PTGDD;                                  /* Port G Data Direction Register; 0xFFFF9849 */
volatile PTAPESTR _PTAPE;                                  /* Port A Pull Enable Register; 0xFFFF9850 */
volatile PTASESTR _PTASE;                                  /* Port A Slew Rate Enable Register; 0xFFFF9851 */
volatile PTADSSTR _PTADS;                                  /* Port A Drive Strength Selection Register; 0xFFFF9852 */
volatile PTAIFESTR _PTAIFE;                                /* Port A Input Filter Enable Register; 0xFFFF9853 */
volatile PTBPESTR _PTBPE;                                  /* Port B Pull Enable Register; 0xFFFF9854 */
volatile PTBSESTR _PTBSE;                                  /* Port B Slew Rate Enable Register; 0xFFFF9855 */
volatile PTBDSSTR _PTBDS;                                  /* Port B Drive Strength Selection Register; 0xFFFF9856 */
volatile PTBIFESTR _PTBIFE;                                /* Port B Input Filter Enable Register; 0xFFFF9857 */
volatile PTCPESTR _PTCPE;                                  /* Port C Pull Enable Register; 0xFFFF9858 */
volatile PTCSESTR _PTCSE;                                  /* Port C Slew Rate Enable Register; 0xFFFF9859 */
volatile PTCDSSTR _PTCDS;                                  /* Port C Drive Strength Selection Register; 0xFFFF985A */
volatile PTCIFESTR _PTCIFE;                                /* Port C Input Filter Enable Register; 0xFFFF985B */
volatile PTDPESTR _PTDPE;                                  /* Port D Pull Enable Register; 0xFFFF985C */
volatile PTDSESTR _PTDSE;                                  /* Port D Slew Rate Enable Register; 0xFFFF985D */
volatile PTDDSSTR _PTDDS;                                  /* Port D Drive Strength Selection Register; 0xFFFF985E */
volatile PTDIFESTR _PTDIFE;                                /* Port D Input Filter Enable Register; 0xFFFF985F */
volatile PTEPESTR _PTEPE;                                  /* Port E Pull Enable Register; 0xFFFF9860 */
volatile PTESESTR _PTESE;                                  /* Port E Slew Rate Enable Register; 0xFFFF9861 */
volatile PTEDSSTR _PTEDS;                                  /* Port E Drive Strength Selection Register; 0xFFFF9862 */
volatile PTEIFESTR _PTEIFE;                                /* Port E Input Filter Enable Register; 0xFFFF9863 */
volatile PTFPESTR _PTFPE;                                  /* Port F Pull Enable Register; 0xFFFF9864 */
volatile PTFSESTR _PTFSE;                                  /* Port F Slew Rate Enable Register; 0xFFFF9865 */
volatile PTFDSSTR _PTFDS;                                  /* Port F Drive Strength Selection Register; 0xFFFF9866 */
volatile PTFIFESTR _PTFIFE;                                /* Port F Input Filter Enable Register; 0xFFFF9867 */
volatile PTGPESTR _PTGPE;                                  /* Port G Pull Enable Register; 0xFFFF9868 */
volatile PTGSESTR _PTGSE;                                  /* Port G Slew Rate Enable Register; 0xFFFF9869 */
volatile PTGDSSTR _PTGDS;                                  /* Port G Drive Strength Selection Register; 0xFFFF986A */
volatile PTGIFESTR _PTGIFE;                                /* Port G Input Filter Enable Register; 0xFFFF986B */
volatile CMTOCSTR _CMTOC;                                  /* CMT Output Control Register; 0xFFFF9874 */
volatile CMTMSCSTR _CMTMSC;                                /* CMT Modulator Status and Control Register; 0xFFFF9875 */
volatile CRCHSTR _CRCH;                                    /* CRC High Register; 0xFFFF9890 */
volatile CRCLSTR _CRCL;                                    /* CRC Low Register; 0xFFFF9891 */
volatile TRANSPOSESTR _TRANSPOSE;                          /* CRC Transpose Register; 0xFFFF9892 */
volatile TODCSTR _TODC;                                    /* TOD Control Register; 0xFFFF989C */
volatile TODSCSTR _TODSC;                                  /* TOD Status and Control Register; 0xFFFF989D */
volatile TODMSTR _TODM;                                    /* TOD Match Register; 0xFFFF989E */
volatile TODCNTSTR _TODCNT;                                /* TOD Counter Register; 0xFFFF989F */
volatile TPM2SCSTR _TPM2SC;                                /* TPM2 Status and Control Register; 0xFFFF98A0 */
volatile TPM2C0SCSTR _TPM2C0SC;                            /* TPM2 Timer Channel 0 Status and Control Register; 0xFFFF98A5 */
volatile TPM2C1SCSTR _TPM2C1SC;                            /* TPM2 Timer Channel 1 Status and Control Register; 0xFFFF98A8 */
volatile TPM2C2SCSTR _TPM2C2SC;                            /* TPM2 Timer Channel 2 Status and Control Register; 0xFFFF98AB */
volatile TPM2C3SCSTR _TPM2C3SC;                            /* TPM2 Timer Channel 3 Status and Control Register; 0xFFFF98AE */
volatile SCI1C1STR _SCI1C1;                                /* SCI1 Control Register 1; 0xFFFF98BA */
volatile SCI1C2STR _SCI1C2;                                /* SCI1 Control Register 2; 0xFFFF98BB */
volatile SCI1S1STR _SCI1S1;                                /* SCI1 Status Register 1; 0xFFFF98BC */
volatile SCI1S2STR _SCI1S2;                                /* SCI1 Status Register 2; 0xFFFF98BD */
volatile SCI1C3STR _SCI1C3;                                /* SCI1 Control Register 3; 0xFFFF98BE */
volatile SCI1DSTR _SCI1D;                                  /* SCI1 Data Register; 0xFFFF98BF */
volatile PDBSCSTR _PDBSC;                                  /* PDB Status and Control Register; 0xFFFF98C0 */
volatile PDBC1STR _PDBC1;                                  /* PDB Control Register 1; 0xFFFF98C1 */
volatile PDBC2STR _PDBC2;                                  /* PDB Control Register 2; 0xFFFF98C2 */
volatile PDBCHENSTR _PDBCHEN;                              /* PDB Channel Enable; 0xFFFF98C3 */
volatile TPM1SCSTR _TPM1SC;                                /* TPM1 Status and Control Register; 0xFFFF98E0 */
volatile TPM1C0SCSTR _TPM1C0SC;                            /* TPM1 Timer Channel 0 Status and Control Register; 0xFFFF98E5 */
volatile TPM1C1SCSTR _TPM1C1SC;                            /* TPM1 Timer Channel 1 Status and Control Register; 0xFFFF98E8 */
volatile TPM1C2SCSTR _TPM1C2SC;                            /* TPM1 Timer Channel 2 Status and Control Register; 0xFFFF98EB */
volatile TPM1C3SCSTR _TPM1C3SC;                            /* TPM1 Timer Channel 3 Status and Control Register; 0xFFFF98EE */
volatile ADCSC2STR _ADCSC2;                                /* Status and Control Register 2; 0xFFFF98FC */
volatile ADCSC3STR _ADCSC3;                                /* Status and Control Register 3; 0xFFFF98FD */
volatile APCTL1STR _APCTL1;                                /* Pin Control 1 Register; 0xFFFF9917 */
volatile APCTL2STR _APCTL2;                                /* Pin Control 2 Register; 0xFFFF9918 */
volatile F1CDIVSTR _F1CDIV;                                /* FLASH Clock Divider Register; 0xFFFF9920 */
volatile F1OPTSTR _F1OPT;                                  /* Flash Options Register; 0xFFFF9921 */
volatile F1CNFGSTR _F1CNFG;                                /* Flash Configuration Register; 0xFFFF9923 */
volatile F1PROTSTR _F1PROT;                                /* Flash Protection Register; 0xFFFF9924 */
volatile F1STATSTR _F1STAT;                                /* Flash Status Register; 0xFFFF9925 */
volatile F1CMDSTR _F1CMD;                                  /* Flash Command Register; 0xFFFF9926 */
volatile F2CDIVSTR _F2CDIV;                                /* FLASH Clock Divider Register; 0xFFFF9930 */
volatile F2OPTSTR _F2OPT;                                  /* Flash Options Register; 0xFFFF9931 */
volatile F2CNFGSTR _F2CNFG;                                /* Flash Configuration Register; 0xFFFF9933 */
volatile F2PROTSTR _F2PROT;                                /* Flash Protection Register; 0xFFFF9934 */
volatile F2STATSTR _F2STAT;                                /* Flash Status Register; 0xFFFF9935 */
volatile F2CMDSTR _F2CMD;                                  /* Flash Command Register; 0xFFFF9936 */
volatile PTHDSTR _PTHD;                                    /* Port H Data Register; 0xFFFF9940 */
volatile PTHDDSTR _PTHDD;                                  /* Port H Data Direction Register; 0xFFFF9941 */
volatile PTJDSTR _PTJD;                                    /* Port J Data Register; 0xFFFF9942 */
volatile PTJDDSTR _PTJDD;                                  /* Port J Data Direction Register; 0xFFFF9943 */
volatile PTHPESTR _PTHPE;                                  /* Port H Pull Enable Register; 0xFFFF9948 */
volatile PTHSESTR _PTHSE;                                  /* Port H Slew Rate Enable Register; 0xFFFF9949 */
volatile PTHDSSTR _PTHDS;                                  /* Port H Drive Strength Selection Register; 0xFFFF994A */
volatile PTHIFESTR _PTHIFE;                                /* Port H Input Filter Enable Register; 0xFFFF994B */
volatile PTJPESTR _PTJPE;                                  /* Port J Pull Enable Register; 0xFFFF994C */
volatile PTJSESTR _PTJSE;                                  /* Port J Slew Rate Enable Register; 0xFFFF994D */
volatile PTJDSSTR _PTJDS;                                  /* Port J Drive Strength Selection Register; 0xFFFF994E */
volatile PTJIFESTR _PTJIFE;                                /* Port J Input Filter Enable Register; 0xFFFF994F */
volatile PER_IDSTR _PER_ID;                                /* Peripherial ID Register; 0xFFFF9A00 */
volatile ID_COMPSTR _ID_COMP;                              /* Peripheral ID Complement Register; 0xFFFF9A04 */
volatile REVSTR _REV;                                      /* Peripheral Revision Register; 0xFFFF9A08 */
volatile ADD_INFOSTR _ADD_INFO;                            /* Peripheral Additional Info Register; 0xFFFF9A0C */
volatile OTG_INT_STATSTR _OTG_INT_STAT;                    /* OTG Interrupt Status Register; 0xFFFF9A10 */
volatile OTG_INT_ENSTR _OTG_INT_EN;                        /* OTG Interrupt Control Register; 0xFFFF9A14 */
volatile OTG_STATSTR _OTG_STAT;                            /* Interrupt Status Register; 0xFFFF9A18 */
volatile OTG_CTRLSTR _OTG_CTRL;                            /* OTG Control Register; 0xFFFF9A1C */
volatile INT_STATSTR _INT_STAT;                            /* Interrupt Status Register; 0xFFFF9A80 */
volatile INT_ENBSTR _INT_ENB;                              /* Interrupt Enable Register; 0xFFFF9A84 */
volatile ERR_STATSTR _ERR_STAT;                            /* Error Interrupt Status Register; 0xFFFF9A88 */
volatile ERR_ENBSTR _ERR_ENB;                              /* Error Interrupt Enable Register; 0xFFFF9A8C */
volatile STATSTR _STAT;                                    /* Status Register; 0xFFFF9A90 */
volatile CTLSTR _CTL;                                      /* Control Register; 0xFFFF9A94 */
volatile ADDRSTR _ADDR;                                    /* Address Register; 0xFFFF9A98 */
volatile BDT_PAGE_01STR _BDT_PAGE_01;                      /* BDT Page Register 1; 0xFFFF9A9C */
volatile FRM_NUMLSTR _FRM_NUML;                            /* Frame Number Register Low; 0xFFFF9AA0 */
volatile FRM_NUMHSTR _FRM_NUMH;                            /* Frame Number Register High; 0xFFFF9AA4 */
volatile TOKENSTR _TOKEN;                                  /* Token Register; 0xFFFF9AA8 */
volatile SOF_THLDSTR _SOF_THLD;                            /* SOF Threshold Register; 0xFFFF9AAC */
volatile BDT_PAGE_02STR _BDT_PAGE_02;                      /* BDT Page Register 2; 0xFFFF9AB0 */
volatile BDT_PAGE_03STR _BDT_PAGE_03;                      /* BDT Page Register 3; 0xFFFF9AB4 */
volatile ENDPT0STR _ENDPT0;                                /* Endpoint Control Register 0; 0xFFFF9AC0 */
volatile ENDPT1STR _ENDPT1;                                /* Endpoint Control Register 1; 0xFFFF9AC4 */
volatile ENDPT2STR _ENDPT2;                                /* Endpoint Control Register 2; 0xFFFF9AC8 */
volatile ENDPT3STR _ENDPT3;                                /* Endpoint Control Register 3; 0xFFFF9ACC */
volatile ENDPT4STR _ENDPT4;                                /* Endpoint Control Register 4; 0xFFFF9AD0 */
volatile ENDPT5STR _ENDPT5;                                /* Endpoint Control Register 5; 0xFFFF9AD4 */
volatile ENDPT6STR _ENDPT6;                                /* Endpoint Control Register 6; 0xFFFF9AD8 */
volatile ENDPT7STR _ENDPT7;                                /* Endpoint Control Register 7; 0xFFFF9ADC */
volatile ENDPT8STR _ENDPT8;                                /* Endpoint Control Register 8; 0xFFFF9AE0 */
volatile ENDPT9STR _ENDPT9;                                /* Endpoint Control Register 9; 0xFFFF9AE4 */
volatile ENDPT10STR _ENDPT10;                              /* Endpoint Control Register 10; 0xFFFF9AE8 */
volatile ENDPT11STR _ENDPT11;                              /* Endpoint Control Register 11; 0xFFFF9AEC */
volatile ENDPT12STR _ENDPT12;                              /* Endpoint Control Register 12; 0xFFFF9AF0 */
volatile ENDPT13STR _ENDPT13;                              /* Endpoint Control Register 13; 0xFFFF9AF4 */
volatile ENDPT14STR _ENDPT14;                              /* Endpoint Control Register 14; 0xFFFF9AF8 */
volatile ENDPT15STR _ENDPT15;                              /* Endpoint Control Register 15; 0xFFFF9AFC */
volatile USB_CTRLSTR _USB_CTRL;                            /* USB Control Register; 0xFFFF9B00 */
volatile USB_OTG_OBSERVESTR _USB_OTG_OBSERVE;              /* USB OTG Observe Register; 0xFFFF9B04 */
volatile USB_OTG_CONTROLSTR _USB_OTG_CONTROL;              /* USB OTG Control Register; 0xFFFF9B08 */
volatile USBTRC0STR _USBTRC0;                              /* USB Transceiver and Regulator Control Register 0; 0xFFFF9B0C */
volatile OTGPINSTR _OTGPIN;                                /* USB OTG Pin Control Register; 0xFFFF9B10 */
volatile INTC_FRCSTR _INTC_FRC;                            /* INTC Force Interrupt Register; 0xFFFFFFD0 */
volatile INTC_PL6P7STR _INTC_PL6P7;                        /* INTC Programmable Level 6, Priority 7 Register; 0xFFFFFFD8 */
volatile INTC_PL6P6STR _INTC_PL6P6;                        /* INTC Programmable Level 6, Priority 6 Register; 0xFFFFFFD9 */
volatile INTC_WCRSTR _INTC_WCR;                            /* INTC Wake-up Control Register; 0xFFFFFFDB */
volatile INTC_SFRCSTR _INTC_SFRC;                          /* INTC Set Interrupt Force Register; 0xFFFFFFDE */
volatile INTC_CFRCSTR _INTC_CFRC;                          /* INTC Clear Interrupt Force Register; 0xFFFFFFDF */
volatile INTC_SWIACKSTR _INTC_SWIACK;                      /* INTC Software IACK Register; 0xFFFFFFE0 */
volatile INTC_LVL1IACKSTR _INTC_LVL1IACK;                  /* INTC Level 1 IACK Register; 0xFFFFFFE4 */
volatile INTC_LVL2IACKSTR _INTC_LVL2IACK;                  /* INTC Level 2 IACK Register; 0xFFFFFFE8 */
volatile INTC_LVL3IACKSTR _INTC_LVL3IACK;                  /* INTC Level 3 IACK Register; 0xFFFFFFEC */
volatile INTC_LVL4IACKSTR _INTC_LVL4IACK;                  /* INTC Level 4 IACK Register; 0xFFFFFFF0 */
volatile INTC_LVL5IACKSTR _INTC_LVL5IACK;                  /* INTC Level 5 IACK Register; 0xFFFFFFF4 */
volatile INTC_LVL6IACKSTR _INTC_LVL6IACK;                  /* INTC Level 6 IACK Register; 0xFFFFFFF8 */
volatile INTC_LVL7IACKSTR _INTC_LVL7IACK;                  /* INTC Level 7 IACK Register; 0xFFFFFFFC */


/* * * * *  16-BIT REGISTERS  * * * * * * * * * * * * * * * */
/* F1CHKS - macro for reading non volatile register        Flash Checksum Register; 0x00000408 */
/* Tip for register initialization in the user code:  const byte F1CHKS_INIT @0x00000408 = <F1CHKS_INITVAL>; */
/* F2CHKS - macro for reading non volatile register        Flash Checksum Register; 0x00020408 */
/* Tip for register initialization in the user code:  const byte F2CHKS_INIT @0x00020408 = <F2CHKS_INITVAL>; */
volatile RGPIO_DIRSTR _RGPIO_DIR;                          /* RGPIO Data Direction Register; 0x00C00000 */
volatile RGPIO_DATASTR _RGPIO_DATA;                        /* RGPIO Data Register; 0x00C00002 */
volatile RGPIO_ENBSTR _RGPIO_ENB;                          /* RGPIO Pin Enable Register; 0x00C00004 */
volatile RGPIO_CLRSTR _RGPIO_CLR;                          /* RGPIO Clear Data Register; 0x00C00006 */
volatile RGPIO_SETSTR _RGPIO_SET;                          /* RGPIO Set Data Register; 0x00C0000A */
volatile RGPIO_TOGSTR _RGPIO_TOG;                          /* RGPIO Toggle Data Register; 0x00C0000E */
volatile DACDAT0STR _DACDAT0;                              /* DAC Data 0 Register; 0xFFFF8010 */
volatile DACDAT1STR _DACDAT1;                              /* DAC Data 1 Register; 0xFFFF8012 */
volatile DACDAT2STR _DACDAT2;                              /* DAC Data 2 Register; 0xFFFF8014 */
volatile DACDAT3STR _DACDAT3;                              /* DAC Data 3 Register; 0xFFFF8016 */
volatile DACDAT4STR _DACDAT4;                              /* DAC Data 4 Register; 0xFFFF8018 */
volatile DACDAT5STR _DACDAT5;                              /* DAC Data 5 Register; 0xFFFF801A */
volatile DACDAT6STR _DACDAT6;                              /* DAC Data 6 Register; 0xFFFF801C */
volatile DACDAT7STR _DACDAT7;                              /* DAC Data 7 Register; 0xFFFF801E */
volatile DACDAT8STR _DACDAT8;                              /* DAC Data 8 Register; 0xFFFF8020 */
volatile DACDAT9STR _DACDAT9;                              /* DAC Data 9 Register; 0xFFFF8022 */
volatile DACDAT10STR _DACDAT10;                            /* DAC Data 10 Register; 0xFFFF8024 */
volatile DACDAT11STR _DACDAT11;                            /* DAC Data 11 Register; 0xFFFF8026 */
volatile DACDAT12STR _DACDAT12;                            /* DAC Data 12 Register; 0xFFFF8028 */
volatile DACDAT13STR _DACDAT13;                            /* DAC Data 13 Register; 0xFFFF802A */
volatile DACDAT14STR _DACDAT14;                            /* DAC Data 14 Register; 0xFFFF802C */
volatile DACDAT15STR _DACDAT15;                            /* DAC Data 15 Register; 0xFFFF802E */
volatile ADCRSTR _ADCR;                                    /* Data Result Register; 0xFFFF804A */
volatile IICSLTSTR _IICSLT;                                /* IIC SCL Low Time Out register; 0xFFFF8068 */
volatile SPI1D16STR _SPI1D16;                              /* SPI1 Data Register; 0xFFFF8074 */
volatile SPI1MSTR _SPI1M;                                  /* SPI1 Match Register; 0xFFFF8076 */
volatile SDIDSTR _SDID;                                    /* System Device Identification Register; 0xFFFF9806 */
volatile SCI2BDSTR _SCI2BD;                                /* SCI2 Baud Rate Register; 0xFFFF9838 */
volatile CMTCG1STR _CMTCG1;                                /* Carrier Generator Data Register 1; 0xFFFF9870 */
volatile CMTCG2STR _CMTCG2;                                /* Carrier Generator Data Register 2; 0xFFFF9872 */
volatile CMTCMD12STR _CMTCMD12;                            /* CMT Modulator Data Register 12; 0xFFFF9876 */
volatile CMTCMD34STR _CMTCMD34;                            /* CMT Modulator Data Register 34; 0xFFFF9878 */
volatile TPM2CNTSTR _TPM2CNT;                              /* TPM2 Timer Counter Register; 0xFFFF98A1 */
volatile TPM2MODSTR _TPM2MOD;                              /* TPM2 Timer Counter Modulo Register; 0xFFFF98A3 */
volatile TPM2C0VSTR _TPM2C0V;                              /* TPM2 Timer Channel 0 Value Register; 0xFFFF98A6 */
volatile TPM2C1VSTR _TPM2C1V;                              /* TPM2 Timer Channel 1 Value Register; 0xFFFF98A9 */
volatile TPM2C2VSTR _TPM2C2V;                              /* TPM2 Timer Channel 2 Value Register; 0xFFFF98AC */
volatile TPM2C3VSTR _TPM2C3V;                              /* TPM2 Timer Channel 3 Value Register; 0xFFFF98AF */
volatile SCI1BDSTR _SCI1BD;                                /* SCI1 Baud Rate Register; 0xFFFF98B8 */
volatile PDBMODSTR _PDBMOD;                                /* PDB Modulus Register; 0xFFFF98C4 */
volatile PDBCNTSTR _PDBCNT;                                /* PDB Counter Register; 0xFFFF98C6 */
volatile PDBIDLYSTR _PDBIDLY;                              /* PDB Interrupt Delay Register; 0xFFFF98C8 */
volatile DACINTSTR _DACINT;                                /* DAC Trigger Interval Register; 0xFFFF98CA */
volatile PDBDLYSTR _PDBDLY;                                /* PDB Delay A Register; 0xFFFF98CC */
volatile TPM1CNTSTR _TPM1CNT;                              /* TPM1 Timer Counter Register; 0xFFFF98E1 */
volatile TPM1MODSTR _TPM1MOD;                              /* TPM1 Timer Counter Modulo Register; 0xFFFF98E3 */
volatile TPM1C0VSTR _TPM1C0V;                              /* TPM1 Timer Channel 0 Value Register; 0xFFFF98E6 */
volatile TPM1C1VSTR _TPM1C1V;                              /* TPM1 Timer Channel 1 Value Register; 0xFFFF98E9 */
volatile TPM1C2VSTR _TPM1C2V;                              /* TPM1 Timer Channel 2 Value Register; 0xFFFF98EC */
volatile TPM1C3VSTR _TPM1C3V;                              /* TPM1 Timer Channel 3 Value Register; 0xFFFF98EF */
volatile ADCCVSTR _ADCCV;                                  /* Compare Value Register; 0xFFFF98F8 */


/* * * * *  32-BIT REGISTERS  * * * * * * * * * * * * * * * */
volatile MBCSAR0STR _MBCSAR0;                              /* Chip Select Address Register 0; 0xFFFFE800 */
volatile MBCSMR0STR _MBCSMR0;                              /* Chip Select Mask Register 0; 0xFFFFE804 */
volatile MBCSCR0STR _MBCSCR0;                              /* Chip Select Control Register 0; 0xFFFFE808 */
volatile MBCSAR1STR _MBCSAR1;                              /* Chip Select Address Register 1; 0xFFFFE80C */
volatile MBCSMR1STR _MBCSMR1;                              /* Chip Select Mask Register 1; 0xFFFFE810 */
volatile MBCSCR1STR _MBCSCR1;                              /* Chip Select Control Register 1; 0xFFFFE814 */

/*lint -restore */

/* EOF */
