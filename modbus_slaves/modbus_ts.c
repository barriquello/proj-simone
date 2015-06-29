/* 
 * 
 * Brief: MODBUS Slave Treetech TS
 * 
 * Slave Address 1 
 * Serial comm: 8-None-2 @ 19200 baud
 * 
 * Taxa de transmissão: 9600, 19200 ou 38400 bps
 * Bits de dados: 8
 * Bits de parada: 2
 * Paridade: Nenhuma
 * 
 * 
 * */
#include "BRTOS.h"
#include "modbus_ts.h"

#define Parametro_RL1 	(1<<0)
#define Parametro_RL2 	(1<<1)
#define Parametro_RL3 	(1<<2)
#define Parametro_RL4 	(1<<3)


/* Holding registers */
const INT16U Parametro_ALMO = 1;  /* alarme por temperatura do óleo */
const INT16U Parametro_DSLO = 2;  /* desligamento por temperatura do óleo */
const INT16U Parametro_RDSO = 3;  /* retardo para o desligamento por temperatura do óleo */
const INT16U Parametro_ALME = 4;  /* alarme por temperatura do enrolamento */
const INT16U Parametro_DSLE = 5;  /* desligamento por temperatura do enrolamento */
const INT16U Parametro_RDSE = 6;  /* retardo para o desligamento por temperatura do enrolamento*/
const INT16U Parametro_IDI 	= 7;  /* seleção do idioma para as legendas */ 
const INT16U Parametro_RTDS = 8;  /* seleciona quantos sensores de temperatura Pt100 */
const INT16U Parametro_DISP = 9;  /* seleciona o modo de exibição do display */
const INT16U Parametro_ALO 	= 10; /* seleciona um relé para atuar na ocorrência de alarme por temperatura do óleo */
const INT16U Parametro_DSO 	= 11; /* seleciona um relé para atuar na ocorrência de desligamento por temperatura do óleo */
const INT16U Parametro_ALE	= 12; /* seleciona um relé para atuar na ocorrência de alarme por temperatura do enrolamento */
const INT16U Parametro_DSE 	= 13; /* seleciona um relé para atuar na ocorrência de desligamento por temperatura do enrolamento */
const INT16U Parametro_RL 	= 14; /* seleciona o modo de funcionamento para os Relés */
const INT16U Parametro_VSAN = 15; /* seleciona a medição de temperatura */
const INT16U Parametro_FSAN = 16; /* seleciona a faixa da saída de corrente */
const INT16U Parametro_FESA = 17; /* ajusta o valor de temperatura para o fim de escala da saída de corrente. */
const INT16U Parametro_IESA = 18; /* ajusta o valor de temperatura para o início de escala da saída de corrente */
const INT16U Parametro_GEO  = 19; /* ajuste do gradiente de temperatura enrolamento médio topo do óleo  */
const INT16U Parametro_TE 	= 20; /* ajuste da constante de tempo do enrolamento */
const INT16U Parametro_HS_MAIS = 21; /* ajuste do fator de hot-spot do enrolamento - ABNT NBR 5416 e IEEE Std C57.91-1995.*/
const INT16U Parametro_HS_AST  = 22; /* ajuste do fator de hot-spot do enrolamento - IEC354 */
const INT16U Parametro_2M  = 23; /* ajuste da exponencial de elevação de temperatura do enrolamento */
const INT16U Parametro_CNT = 24; /* ajuste da corrente nominal do transformador */
const INT16U Parametro_CNS = 25; /* ajuste da corrente nominal do transformador referida ao secundário */
const INT16U Parametro_RF1 = 26; /* temperatura para acionamento do 1º grupo de refrigeração forçada */
const INT16U Parametro_RF2 = 27; /* temperatura para acionamento do 2º grupo de refrigeração forçada */
const INT16U Parametro_HIS = 28; /* temperatura para desacionamento dos grupos de refrigeração forçada */
const INT16U Parametro_ALT = 29; /* alternância automática entre os grupos de ventiladores */
const INT16U Parametro_CV1 = 30; /* percentual de carga do transformador para atuação do 1º grupo de refrigeração forçada */
const INT16U Parametro_CV2 = 31; /* percentual de carga do transformador para atuação do 2º grupo de refrigeração forçada */
const INT16U Parametro_HIC = 32; /* Histerese para parada dos grupos de resfriamento por redução da carga do transformador */
const INT16U Parametro_EVH = 33; /* ajuste da hora em que deverão ser acionados os grupos de refrigeração forçada */
const INT16U Parametro_EVM  = 34; /* ajuste do minuto em que deverão ser acionados os grupos de refrigeração forçada */
const INT16U Parametro_TEV  = 35; /* ajuste da tempo que os grupos de refrigeração forçada deverão permanecer acionados */
const INT16U Parametro_HLOG = 36; /* ajusta o valor de variação de temperatura acima da qual o TS fará uma gravação na memória de massa. */
const INT16U Parametro_TLOG = 37; /* ajusta os intervalos de tempo em que o TS fará as gravações na memória de massa */
const INT16U Parametro_RLOG = 38; /* Reset do LOG. Apaga todos os dados na memória de massa do TS. */
const INT16U Parametro_MES  = 39; /* ajuste do mês do calendário */
const INT16U Parametro_DIA  = 40; /* ajuste do dia do calendário */
const INT16U Parametro_ANO  = 41; /* ajuste do ano do calendário */
const INT16U Parametro_HORA = 42; /* ajuste da hora do relógio */
const INT16U Parametro_MIN  = 43; /* ajuste dos minutos do relógio */
const INT16U Modo_RF1  		= 44;
const INT16U Modo_RF2  		= 45;

/* Input registers */
const INT16U Temperatura_oleo 		 		= 1001;
const INT16U Temperatura_enrolamento 		= 1002;
const INT16U Temperatura_RTD2 		 		= 1003;
const INT16U Temperatura_RTD3	 	 		= 1004;
const INT16U Temperatura_maxima_oleo 		= 1005;
const INT16U Temperatura_maxima_enrolamento = 1006;
const INT16U Temperatura_maxima_RTD2 		= 1007;
const INT16U Temperatura_maxima_RTD3 		= 1008;
const INT16U Gradiente_Final_Temperatura 	= 1009;
const INT16U Percentual_carga 				= 1010;
const INT16U Corrente_secundario_TC 		= 1011;
const INT16U Corrente_transformador 		= 1012;
const INT16U Estado_Reles 					= 1013;
const INT16U Variavel_erros 				= 1014;
const INT16U Opcionais 						= 1015;
const INT16U Reles 							= 1016;
const INT16U Ponteiro_LOG 					= 1017;


/* 
 * Supported MODBUS Commands
Command Description
0x03 Read holding registers
0x04 Read input registers
 * 
 * */

#pragma warn_unusedarg off

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "modbus_ts.h"

/* ----------------------- Constants ------------------------------------------*/

const UCHAR TS_ID_string[] = "TS";
const USHORT SIZEOF_TS_ID_STRING = sizeof(TS_ID_string); 
		
static const INT8U usRegInputBuf[TS_REG_INPUT_NREGS] = 
{
		0x11,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x66, 
		0x22,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x77,		
};

static const INT8U usRegHoldingBuf[TS_REG_INPUT_NREGS];

/* ----------------------- Start implementation -----------------------------*/
#if 1

eMBErrorCode
eMBRegInputCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
     
    INT8U  iRegIndex;

    if( ( usAddress >= TS_REG_INPUT_START )
        && ( usAddress + usNRegs <= TS_REG_INPUT_START + TS_REG_INPUT_NREGS ) )
    {
        iRegIndex = ( INT8U )( usAddress - TS_REG_INPUT_START );
        while( usNRegs > 0 )
        {
        	*pucRegBuffer++ = ( INT8U )( usRegInputBuf[iRegIndex]);
			iRegIndex++;
			*pucRegBuffer++ = ( INT8U )( usRegInputBuf[iRegIndex]);
			iRegIndex++;
            usNRegs--;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }


    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
     
    INT8U  iRegIndex;

    if( ( usAddress >= TS_REG_HOLDING_START )
        && ( usAddress + usNRegs <= TS_REG_HOLDING_START + TS_REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( INT8U )( usAddress - TS_REG_HOLDING_START );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( INT8U )( usRegHoldingBuf[iRegIndex]);
            iRegIndex++;
            *pucRegBuffer++ = ( INT8U )( usRegHoldingBuf[iRegIndex]);
            iRegIndex++;
            usNRegs--;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    } 

    return eStatus;
}


eMBErrorCode
eMBRegCoilsCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}

#endif
