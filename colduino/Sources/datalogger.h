/*! \file datalogger.h
 \brief Laª dados e grava em um carta£o SD.
 
 Monitora sinais de entrada e os grava em cartao SD.
 Os dados sao gravados em arquivos. Sendo que eh criado um	
 arquivo por hora, com a data atual sendo o nome do arquivo.
 */
#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"
#include "ff.h"

#define MAX_FILE_SIZE 12

/*! 
 \fn void CreateNewFile(char fileName[] , INT16U year, INT8U month, INT8U day,INT8U hour, INT8U min, INT8U sec)
 \brief Formata um novo nome para um novo arquivo.
 
 A data atual (parametros da funcao) e lida do OS, os valores sao convertidos para strings e concatenados.
 Um novo arquivo com a data atual e criado.
 
 \param year Ano atual
 \param month Mes atual
 \param day Dia atual
 \param hour Hora atual
 \param min Minuto atual
 \param sec Segundo atual
 
 
 \fn void WriteFile(...)
 \brief Grava dados no ultimo arquivo criado.
 
 
 \fn void WriteData(void)
 \brief Grava dados no ultimo arquivo criado.
 
 
 \fn void SetLastCreatedFileName(char[] fileName)
 \brief Pega ultimo arquivo gravado no cartao SD.
 
 Pega ultimo arquivo gravado no cartao SD e poe o nome em fileName.
 
 \param fileName Nome do arquivo sendo gravado.
 */

INT32U GetFileCreationDate (char fileName[]);
INT8U SetLastCreatedFileName(char fileName[]);

extern FILINFO Finfo;
extern DIR 	Dir;
extern INT8U  sd_command;

#if (SD_FAT_MUTEX_EN == 1)
extern BRTOS_Mutex *SDCardResource;
#endif

#if _USE_LFN
extern CHAR8 Lfname[256];
#endif

#endif /* DATALOGGER_H_ */
