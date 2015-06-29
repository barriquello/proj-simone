/*
 * modbus_ts.h
 *
 *  Created on: Jan 30, 2015
 *      Author: Gisele
 */

#ifndef MODBUS_TS_H_
#define MODBUS_TS_H_

#define TS_REG_INPUT_START  1000
#define TS_REG_INPUT_NREGS  16

#define TS_REG_HOLDING_START  0000
#define TS_REG_HOLDING_NREGS  48

#define TS_REG_OFFSET		  (4)

#define TS_SLAVE_ADDRESS	(0x01)   // END � Endere�o do TS na comunica��o serial, faixa de ajuste: 1 a 31 

typedef union {
  INT8U Byte;
  struct {
	INT8U b0      :1;
	INT8U b1      :1;     
	INT8U b2      :1;     
	INT8U b3      :1;     
	INT8U b4      :1;     
	INT8U b5      :1; 
	INT8U b6      :1;     
    INT8U b7      :1;     
  } Bits;  
} U8;

/*
Estado_Rele_RF1
Estado_Rele_RF2
Estado_Rele_Autodiagnostico
Unused
Estado_Rele_1
Estado_Rele_2
Estado_Rele_3
Estado_Rele_4
*/

typedef union {
  INT8U Val;
  struct {
	INT8U Estado_Rele_RF1      :1;
	INT8U Estado_Rele_RF2      :1;     
	INT8U Estado_Rele_Autodiagnostico      :1;     
	INT8U       			 :1;     
	INT8U Estado_Rele_1      :1;     
	INT8U Estado_Rele_2      :1; 
	INT8U Estado_Rele_3      :1;     
    INT8U Estado_Rele_4      :1;     
  } Bits;  
} Estado_Reles_t;


/*
Opcional_RTDs_adicionais
Opcional_Saida_Analogica
Opcional_Comunica��o_Serial_RS485
Nao_utilizado
Opcional_Memoria_Massa
Opcional_Pre_resfriamento
Opcional_Exercicio_ventiladores
Nao_utilizado
*/

typedef union {
  INT8U Val;
  struct {
	INT8U Opcional_RTDs_adicionais      	:1;
	INT8U Opcional_Saida_Analogica      	:1;     
	INT8U Opcional_Comunica��o_Serial_RS485 :1;     
	INT8U       							:1;     
	INT8U Opcional_Memoria_Massa      		:1;     
	INT8U Opcional_Pre_resfriamento      	:1; 
	INT8U Opcional_Exercicio_ventiladores   :1;     
    INT8U       							:1;     
  } Bits;  
} Opcionais_t;

/*
Alarme_Temperatura_enrolamento
Alarme_Temperatura_oleo
Desligamento_Temperatura_enrolamento
Desligamento_Temperatura_oleo
Nao_utilizado
Nao_utilizado
Nao_utilizado
Nao_utilizado
*/

typedef union {
  INT8U Val;
  struct {
	INT8U Alarme_Temperatura_enrolamento      	:1;
	INT8U Alarme_Temperatura_oleo      			:1;     
	INT8U Desligamento_Temperatura_enrolamento  :1;     
	INT8U Desligamento_Temperatura_oleo  		:1;     
	INT8U    :1;     
	INT8U    :1; 
	INT8U    :1;     
    INT8U    :1;     
  } Bits;  
} Alarmes_t;



typedef union
{	
	struct   							/* Faixa de Medi��o ou Estado - Passo */
	{
		INT8U Device_id;	/* device id */
		INT8U Hora;			/* timestamp of last reading */
		INT8U Minuto;		/* timestamp of last reading  */
		INT8U Segundo;		/* timestamp of last reading */
		INT8U Temperatura_oleo; 			/* -55...200 - 0,1 */
		INT8U Temperatura_enrolamento;  	/* -55...200 - 0,1 */
		INT8U Temperatura_RTD2;				/* -55...200 - 0,1 */
		INT8U Temperatura_RTD3;				/* -55...200 - 0,1 */
		INT8U Temperatura_maxima_oleo;  	/* -55...200 - 0,1 */
		INT8U Temperatura_maxima_enrolamento; /* -55...200 - 0,1 */
		INT8U Temperatura_maxima_RTD2;		/* -55...200 - 0,1 */
		INT8U Temperatura_maxima_RTD3;  	/* -55...200 - 0,1 */
		INT8U Gradiente_Final_Temperatura; 	/* -55...55 - 0,01 */
		INT8U Percentual_carga;				/* 0...100 - 0,1 */
		INT8U Corrente_secundario_TC;		/* 0...10 - 0,01 */
		INT8U Corrente_transformador;       /* 0...99,98 - 0,01 */
		Estado_Reles_t Estado_Reles;		/* bitmap */
		INT8U Variavel_erros;				/* ?? */
		Opcionais_t Opcionais;				/* bitmap */
		Alarmes_t Reles;					/* bitmap */
	}Reg;	
	INT8U Regs[16+4]; 
}modbus_ts_input_register_list;


typedef union
{
	struct
	{
		/* Holding registers */
		INT8U Parametro_ALMO;  /* alarme por temperatura do �leo */
		INT8U Parametro_DSLO;  /* desligamento por temperatura do �leo */
		INT8U Parametro_RDSO;  /* retardo para o desligamento por temperatura do �leo */
		INT8U Parametro_ALME;  /* alarme por temperatura do enrolamento */
		INT8U Parametro_DSLE;  /* desligamento por temperatura do enrolamento */
		INT8U Parametro_RDSE;  /* retardo para o desligamento por temperatura do enrolamento*/
		INT8U Parametro_IDI ;  /* sele��o do idioma para as legendas */ 
		INT8U Parametro_RTDS;  /* seleciona quantos sensores de temperatura Pt100 */
		INT8U Parametro_DISP;  /* seleciona o modo de exibi��o do display */
		INT8U Parametro_ALO ; /* seleciona um rel� para atuar na ocorr�ncia de alarme por temperatura do �leo */
		INT8U Parametro_DSO ; /* seleciona um rel� para atuar na ocorr�ncia de desligamento por temperatura do �leo */
		INT8U Parametro_ALE	; /* seleciona um rel� para atuar na ocorr�ncia de alarme por temperatura do enrolamento */
		INT8U Parametro_DSE 	; /* seleciona um rel� para atuar na ocorr�ncia de desligamento por temperatura do enrolamento */
		INT8U Parametro_RL 	; /* seleciona o modo de funcionamento para os Rel�s */
		INT8U Parametro_VSAN ; /* seleciona a medi��o de temperatura */
		INT8U Parametro_FSAN ; /* seleciona a faixa da sa�da de corrente */
		INT8U Parametro_FESA ; /* ajusta o valor de temperatura para o fim de escala da sa�da de corrente. */
		INT8U Parametro_IESA ; /* ajusta o valor de temperatura para o in�cio de escala da sa�da de corrente */
		INT8U Parametro_GEO  ; /* ajuste do gradiente de temperatura enrolamento m�dio topo do �leo  */
		INT8U Parametro_TE 	; /* ajuste da constante de tempo do enrolamento */
		INT8U Parametro_HS_MAIS ; /* ajuste do fator de hot-spot do enrolamento - ABNT NBR 5416 e IEEE Std C57.91-1995.*/
		INT8U Parametro_HS_AST  ; /* ajuste do fator de hot-spot do enrolamento - IEC354 */
		INT8U Parametro_2M  ; /* ajuste da exponencial de eleva��o de temperatura do enrolamento */
		INT8U Parametro_CNT ; /* ajuste da corrente nominal do transformador */
		INT8U Parametro_CNS ; /* ajuste da corrente nominal do transformador referida ao secund�rio */
		INT8U Parametro_RF1 ; /* temperatura para acionamento do 1� grupo de refrigera��o for�ada */
		INT8U Parametro_RF2 ; /* temperatura para acionamento do 2� grupo de refrigera��o for�ada */
		INT8U Parametro_HIS ; /* temperatura para desacionamento dos grupos de refrigera��o for�ada */
		INT8U Parametro_ALT ; /* altern�ncia autom�tica entre os grupos de ventiladores */
		INT8U Parametro_CV1 ; /* percentual de carga do transformador para atua��o do 1� grupo de refrigera��o for�ada */
		INT8U Parametro_CV2 ; /* percentual de carga do transformador para atua��o do 2� grupo de refrigera��o for�ada */
		INT8U Parametro_HIC ; /* Histerese para parada dos grupos de resfriamento por redu��o da carga do transformador */
		INT8U Parametro_EVH ; /* ajuste da hora em que dever�o ser acionados os grupos de refrigera��o for�ada */
		INT8U Parametro_EVM ; /* ajuste do minuto em que dever�o ser acionados os grupos de refrigera��o for�ada */
		INT8U Parametro_TEV ; /* ajuste da tempo que os grupos de refrigera��o for�ada dever�o permanecer acionados */
		INT8U Parametro_HLOG; /* ajusta o valor de varia��o de temperatura acima da qual o TS far� uma grava��o na mem�ria de massa. */
		INT8U Parametro_TLOG; /* ajusta os intervalos de tempo em que o TS far� as grava��es na mem�ria de massa */
		INT8U Parametro_RLOG; /* Reset do LOG. Apaga todos os dados na mem�ria de massa do TS. */
		INT8U Parametro_MES ; /* ajuste do m�s do calend�rio */
		INT8U Parametro_DIA ; /* ajuste do dia do calend�rio */
		INT8U Parametro_ANO ; /* ajuste do ano do calend�rio */
		INT8U Parametro_HORA; /* ajuste da hora do rel�gio */
		INT8U Parametro_MIN ; /* ajuste dos minutos do rel�gio */
		INT8U Modo_RF1;
		INT8U Modo_RF2;		
	}Reg;
	INT8U Regs[46]; 
}modbus_ts_holding_register_list;


#include "mb.h"
eMBErrorCode eMBRegInputCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );

#endif /* MODBUS_TS_H_ */
