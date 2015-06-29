/*! \file Timer_RTC_DS1307.h
 \brief Interface para ler/escrever data no DS1307.
 
 Funcoes de leitura e escrita sao feitas por IIC.
 */


/*! \defgroup timersGroup Timers*/

/** \addtogroup timersGroup
 *  @{
 */

#ifndef TIMER_RTC_DS1307_H_
#define TIMER_RTC_DS1307_H_

#include "rtc_ds1307.h"
#include "BRTOS.h"

/*! \def SEC_ADDRESS
 \brief Endereco de memoria dos segundos no DS1307.

 \def MIN_ADDRESS
 \brief Endereco de memoria dos minutos no DS1307.
 
 \def HOUR_ADDRESS
 \brief Endereco de memoria das horas no DS1307.
 
 \def WEEK_DAY_ADDRESS
 \brief Endereco de memoria do dia da semana no DS1307.
 
 \def DAY_ADDRESS
 \brief Endereco de memoria do dia do mes no DS1307.
 
 \def MONTH_ADDRESS
 \brief Endereco de memoria dos meses no DS1307.
 
 \def YEAR_ADDRESS
 \brief Endereco de memoria dos anos no DS1307.
 */

#define SEC_ADDRESS 	0x00
#define MIN_ADDRESS 	0x01
#define HOUR_ADDRESS 	0x02
#define WEEK_DAY_ADDRESS 0x03
#define DAY_ADDRESS 	0x04
#define MONTH_ADDRESS 	0x05
#define YEAR_ADDRESS 	0x06
#define RTC_YEAR_INIT 	(2000)

/*! \struct RTC_DS1307

    \brief Estrutura para manter informacoes do calendario.
   
    Os dados da estrutura devem ser lidos do DS1307 usando as funcoes deste arquivo.
 */

typedef struct
{
	INT8U Sec; 		 /*!< Segundos (0-59) */
	INT8U Min; 		 /*!< Minutos (0-59) */
	INT8U Hour;		 /*!< Horas (1-12 no formato AM/PM) (0-23 no formato 24h)*/
	INT8U Day; 	 	 /*!< Dia do mes (1-31)*/
	INT8U DayOfWeek; /*!< Dia da semana (1-7) */
	INT8U Month; 	 /*!< Mes (1-12) */
	INT16U Year; 	 /*!< Ano (2000-2099)*/	
} RTC_DS1307;

/*! \fn INT8U RTC_DS1307_GetSeconds(void)
 \return Segundos do DS1307.
 
 \fn INT8U RTC_DS1307_GetMinutes(void)
 \return Minutos do DS1307.
 
 \fn INT8U RTC_DS1307_GetHours(void)
 \return Hras do DS1307.
 
 \fn INT8U RTC_DS1307_GetDayOfMonth(void)
 \return Dia do mes do DS1307.
 
 \fn INT8U RTC_DS1307_GetMonth(void)
 \return Mes do DS1307.
 
 \fn INT8U RTC_DS1307_GetYear(void)
 \return Ano do DS1307.
 

 \fn void RTC_DS1307_Set_Time(INT8U hour, INT8U min,INT8U sec)
 \brief Grava nova hora no DS1307.
 
 \param hour Nova hora a ser gravada.
 \param min Novo minuto a ser gravado.
 \param sec Novo segundo a ser gravado.
 
 
 \fn void RTC_DS1307_Set_Date(INT8U year, INT8U month, INT8U day)
 \brief Grava nova data no DS1307.
 
 \param year Novo ano a ser gravado.
 \param month Novo mes a ser gravado.
 \param day Novo dia a ser gravado.
 
 
 \fn void  RTC_DS1307_Update(RTC_DS1307 *rtc_timer)
 \brief Atualiza o calendario da estrutura rtc_timer lendo os dados no DS1307.
 \param rtc_timer Estrutura a ser atualizada.
 
 \fn void void Start_RTC_DS1307_OSC(void)
 \brief Habilita oscilador do DS1307

 \fn void Set_24h_Format(void)
 \brief Habilita formato 24h no DS1307
 
 \fn void Set_AM_PM_Mode(void)
 \brief Habilita modo AM/PM no DS1307
 
 
 \fn INT8U Div10(INT8U n)
 \brief Divisao rapida por 10
 \param n Valor a ser dividido.
 \return n/10
 */

INT8U RTC_DS1307_GetSeconds(void);
INT8U RTC_DS1307_GetMinutes(void);
INT8U RTC_DS1307_GetHours(void);
INT8U RTC_DS1307_GetDayOfMonth(void);
INT8U RTC_DS1307_GetMonth(void);
INT8U RTC_DS1307_GetYear(void);

INT8U RTC_DS1307_GetStatus(void);
void RTC_DS1307_SetStatus(INT8U st);

void RTC_DS1307_Set_Time(INT8U hour, INT8U min,	INT8U sec);
void RTC_DS1307_Set_Date(INT8U year, INT8U month, INT8U day);
void RTC_DS1307_Update(RTC_DS1307 *rtc_timer);
void RTC_DS1307_Config(void);
void RTC_DS1307_Start_OSC(void);

INT8U Get_Hour_Format(void);
void Set_24h_Format(void);
void Set_AM_PM_Mode(void);


//INT8U Div10(INT8U n);
#endif 

/** @}*/
