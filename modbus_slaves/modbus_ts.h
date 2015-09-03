/*
 * modbus_ts.h
 *
 *  Created on: Jan 30, 2015
 *      Author: Gisele
 */

#ifndef MODBUS_TS_H_
#define MODBUS_TS_H_

#include "stdint.h"

#define TS_REG_INPUT_START  1000
#define TS_REG_INPUT_NREGS  16

#define TS_REG_HOLDING_START  0000
#define TS_REG_HOLDING_NREGS  48

#define TS_REG_OFFSET		  (4)

#define TS_SLAVE_ADDRESS	(0x01)   // END � Endere�o do TS na comunica��o serial, faixa de ajuste: 1 a 31 

typedef union {
  uint8_t Byte;
  struct {
	uint8_t b0      :1;
	uint8_t b1      :1;
	uint8_t b2      :1;
	uint8_t b3      :1;
	uint8_t b4      :1;
	uint8_t b5      :1;
	uint8_t b6      :1;
    uint8_t b7      :1;
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
  uint8_t Val;
  struct {
	uint8_t Estado_Rele_RF1      :1;
	uint8_t Estado_Rele_RF2      :1;
	uint8_t Estado_Rele_Autodiagnostico      :1;
	uint8_t       			 :1;
	uint8_t Estado_Rele_1      :1;
	uint8_t Estado_Rele_2      :1;
	uint8_t Estado_Rele_3      :1;
    uint8_t Estado_Rele_4      :1;
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
  uint8_t Val;
  struct {
	uint8_t Opcional_RTDs_adicionais      	:1;
	uint8_t Opcional_Saida_Analogica      	:1;
	uint8_t Opcional_RS485 					:1;
	uint8_t Unused  						:1;
	uint8_t Opcional_Memoria_Massa      	:1;
	uint8_t Opcional_Pre_resfriamento      	:1;
	uint8_t Opcional_Exercicio_ventiladores :1;
    uint8_t       							:1;
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
  uint8_t Val;
  struct {
	uint8_t Alarme_Temperatura_enrolamento      	:1;
	uint8_t Alarme_Temperatura_oleo      			:1;
	uint8_t Desligamento_Temperatura_enrolamento  :1;
	uint8_t Desligamento_Temperatura_oleo  		:1;
	uint8_t    :1;
	uint8_t    :1;
	uint8_t    :1;
    uint8_t    :1;
  } Bits;  
} Alarmes_t;



typedef union
{	
	struct   							/* Faixa de Medi��o ou Estado - Passo */
	{
		uint8_t Device_id;	/* device id */
		uint8_t Hora;			/* timestamp of last reading */
		uint8_t Minuto;		/* timestamp of last reading  */
		uint8_t Segundo;		/* timestamp of last reading */
		uint8_t Temperatura_oleo; 			/* -55...200 - 0,1 */
		uint8_t Temperatura_enrolamento;  	/* -55...200 - 0,1 */
		uint8_t Temperatura_RTD2;				/* -55...200 - 0,1 */
		uint8_t Temperatura_RTD3;				/* -55...200 - 0,1 */
		uint8_t Temperatura_maxima_oleo;  	/* -55...200 - 0,1 */
		uint8_t Temperatura_maxima_enrolamento; /* -55...200 - 0,1 */
		uint8_t Temperatura_maxima_RTD2;		/* -55...200 - 0,1 */
		uint8_t Temperatura_maxima_RTD3;  	/* -55...200 - 0,1 */
		uint8_t Gradiente_Final_Temperatura; 	/* -55...55 - 0,01 */
		uint8_t Percentual_carga;				/* 0...100 - 0,1 */
		uint8_t Corrente_secundario_TC;		/* 0...10 - 0,01 */
		uint8_t Corrente_transformador;       /* 0...99,98 - 0,01 */
		Estado_Reles_t Estado_Reles;		/* bitmap */
		uint8_t Variavel_erros;				/* ?? */
		Opcionais_t Opcionais;				/* bitmap */
		Alarmes_t Reles;					/* bitmap */
	}Reg;	
	uint8_t Regs[16+4];
}modbus_ts_input_register_list;


typedef union
{
	struct
	{
		/* Holding registers */
		uint8_t Parametro_ALMO;  /* alarme por temperatura do �leo */
		uint8_t Parametro_DSLO;  /* desligamento por temperatura do �leo */
		uint8_t Parametro_RDSO;  /* retardo para o desligamento por temperatura do �leo */
		uint8_t Parametro_ALME;  /* alarme por temperatura do enrolamento */
		uint8_t Parametro_DSLE;  /* desligamento por temperatura do enrolamento */
		uint8_t Parametro_RDSE;  /* retardo para o desligamento por temperatura do enrolamento*/
		uint8_t Parametro_IDI ;  /* sele��o do idioma para as legendas */
		uint8_t Parametro_RTDS;  /* seleciona quantos sensores de temperatura Pt100 */
		uint8_t Parametro_DISP;  /* seleciona o modo de exibi��o do display */
		uint8_t Parametro_ALO ; /* seleciona um rel� para atuar na ocorr�ncia de alarme por temperatura do �leo */
		uint8_t Parametro_DSO ; /* seleciona um rel� para atuar na ocorr�ncia de desligamento por temperatura do �leo */
		uint8_t Parametro_ALE	; /* seleciona um rel� para atuar na ocorr�ncia de alarme por temperatura do enrolamento */
		uint8_t Parametro_DSE 	; /* seleciona um rel� para atuar na ocorr�ncia de desligamento por temperatura do enrolamento */
		uint8_t Parametro_RL 	; /* seleciona o modo de funcionamento para os Rel�s */
		uint8_t Parametro_VSAN ; /* seleciona a medi��o de temperatura */
		uint8_t Parametro_FSAN ; /* seleciona a faixa da sa�da de corrente */
		uint8_t Parametro_FESA ; /* ajusta o valor de temperatura para o fim de escala da sa�da de corrente. */
		uint8_t Parametro_IESA ; /* ajusta o valor de temperatura para o in�cio de escala da sa�da de corrente */
		uint8_t Parametro_GEO  ; /* ajuste do gradiente de temperatura enrolamento m�dio topo do �leo  */
		uint8_t Parametro_TE 	; /* ajuste da constante de tempo do enrolamento */
		uint8_t Parametro_HS_MAIS ; /* ajuste do fator de hot-spot do enrolamento - ABNT NBR 5416 e IEEE Std C57.91-1995.*/
		uint8_t Parametro_HS_AST  ; /* ajuste do fator de hot-spot do enrolamento - IEC354 */
		uint8_t Parametro_2M  ; /* ajuste da exponencial de eleva��o de temperatura do enrolamento */
		uint8_t Parametro_CNT ; /* ajuste da corrente nominal do transformador */
		uint8_t Parametro_CNS ; /* ajuste da corrente nominal do transformador referida ao secund�rio */
		uint8_t Parametro_RF1 ; /* temperatura para acionamento do 1� grupo de refrigera��o for�ada */
		uint8_t Parametro_RF2 ; /* temperatura para acionamento do 2� grupo de refrigera��o for�ada */
		uint8_t Parametro_HIS ; /* temperatura para desacionamento dos grupos de refrigera��o for�ada */
		uint8_t Parametro_ALT ; /* altern�ncia autom�tica entre os grupos de ventiladores */
		uint8_t Parametro_CV1 ; /* percentual de carga do transformador para atua��o do 1� grupo de refrigera��o for�ada */
		uint8_t Parametro_CV2 ; /* percentual de carga do transformador para atua��o do 2� grupo de refrigera��o for�ada */
		uint8_t Parametro_HIC ; /* Histerese para parada dos grupos de resfriamento por redu��o da carga do transformador */
		uint8_t Parametro_EVH ; /* ajuste da hora em que dever�o ser acionados os grupos de refrigera��o for�ada */
		uint8_t Parametro_EVM ; /* ajuste do minuto em que dever�o ser acionados os grupos de refrigera��o for�ada */
		uint8_t Parametro_TEV ; /* ajuste da tempo que os grupos de refrigera��o for�ada dever�o permanecer acionados */
		uint8_t Parametro_HLOG; /* ajusta o valor de varia��o de temperatura acima da qual o TS far� uma grava��o na mem�ria de massa. */
		uint8_t Parametro_TLOG; /* ajusta os intervalos de tempo em que o TS far� as grava��es na mem�ria de massa */
		uint8_t Parametro_RLOG; /* Reset do LOG. Apaga todos os dados na mem�ria de massa do TS. */
		uint8_t Parametro_MES ; /* ajuste do m�s do calend�rio */
		uint8_t Parametro_DIA ; /* ajuste do dia do calend�rio */
		uint8_t Parametro_ANO ; /* ajuste do ano do calend�rio */
		uint8_t Parametro_HORA; /* ajuste da hora do rel�gio */
		uint8_t Parametro_MIN ; /* ajuste dos minutos do rel�gio */
		uint8_t Modo_RF1;
		uint8_t Modo_RF2;
	}Reg;
	uint8_t Regs[46];
}modbus_ts_holding_register_list;

#if COLDUINO  
#include "mb.h"
eMBErrorCode eMBRegInputCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB_TS( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );
#endif

#endif /* MODBUS_TS_H_ */
