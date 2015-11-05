/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/
#include "BRTOS.h"
#include "debug_stack.h"
#include "SD_API.h"
#include "printf_lib.h"
#include "drivers.h"
#include "utils.h"
#include "string.h"
#include "terminal_io.h"
#include "terminal.h"

#define SD_PRINT 1

/* print configuration */
#if SD_PRINT
#if ARDUINO
#define PRINT(a,...)	if(a) {	printf_lib(__VA_ARGS__); }
#define PRINTA(...)		do{printf_lib(__VA_ARGS__); }while(0);
#define PRINT_P(a,...)	if(a) {	printf_terminal_P(__VA_ARGS__); }
#define PRINTA_P(...)	do{printf_terminal_P(__VA_ARGS__); }while(0);
#else
#define PRINT(a,...)	if(a) { printf_lib(__VA_ARGS__);}
#define PRINTA(...)		do{printf_lib(__VA_ARGS__); }while(0);
#define PRINT_P(a,...)	if(a) {	printf_lib(__VA_ARGS__); }
#define PRINTA_P(...)	do{printf_lib(__VA_ARGS__); }while(0);
#endif
#else
#define PRINT(a,...)
#define PRINTA(...)	
#define PRINT_P(a,...)
#define PRINTA_P(...)	
#endif

#if COLDUINO || ARDUINO
#if __GNUC__
#define nop() 		__asm__ volatile ("nop");
#else
#pragma warn_implicitconv off
#define nop()		asm{NOP}
#endif
#elif ARDUINO	
#define nop()		asm("NOP");
#endif	

#if (SD_FAT_MUTEX_EN == 1)
  BRTOS_Mutex *SDCardResource = NULL;
#endif
  
static FATFS FATFS_Obj;


FIL      file_obj;  // File object
DIR		 Dir;	 // Directory object

#if _USE_LFN
CHAR8 Lfname[256];
#endif


/* Mensagens padrão da API do SD */
#define SD_API_FILE_NOT_FOUND_DEF		"File or directory not found.\n\r"
#define SD_API_FILE_INVALID_DEF			"Invalid file or directory name.\n\r"
#define SD_API_CARD_DEF					"\r\nSD card "
#define SD_API_CARD_BUSY_DEF			"busy!\n\r"
#define SD_API_CARD_NOT_PRESENT_DEF		"not present or not initialized !\n\r"
#define SD_API_FILE_REMOVED_DEF			"All contents removed."
#define SD_API_CARD_ERROR_DEF			"Function failed."
#define SD_API_CARD_MOUNTED_DEF			"mounted!\n\r"
#define SD_API_CARD_DETECTED_DEF		"detected!\n\r"
#define SD_API_CARD_MOUNT_FAILURE_DEF   " failed to mount!\n\r"
#define SD_API_CARD_INIT_FAILURE_DEF    " failed to initialize!\n\r"

#if COLDUINO
#define PROGMEM
#define PGM_P const char*
#endif

CONST CHAR8 SD_API_CARD[] PROGMEM =SD_API_CARD_DEF;
CONST CHAR8 SD_API_FILE_NOT_FOUND[] PROGMEM =SD_API_FILE_NOT_FOUND_DEF;
CONST CHAR8 SD_API_FILE_INVALID[] PROGMEM =SD_API_FILE_INVALID_DEF;
CONST CHAR8 SD_API_CARD_NOT_PRESENT[] PROGMEM =SD_API_CARD_NOT_PRESENT_DEF;
CONST CHAR8 SD_API_FILE_REMOVED[] PROGMEM=SD_API_FILE_REMOVED_DEF;
CONST CHAR8 SD_API_CARD_ERROR[] PROGMEM=SD_API_CARD_ERROR_DEF;
CONST CHAR8 SD_API_CARD_MOUNTED[] PROGMEM =SD_API_CARD_MOUNTED_DEF;
CONST CHAR8 SD_API_CARD_DETECTED[] PROGMEM =SD_API_CARD_DETECTED_DEF;
CONST CHAR8 SD_API_CARD_MOUNT_FAILURE[] PROGMEM =SD_API_CARD_MOUNT_FAILURE_DEF;
CONST CHAR8 SD_API_CARD_INIT_FAILURE[] PROGMEM =SD_API_CARD_INIT_FAILURE_DEF;

PGM_P CONST SDCard_StringTable[] PROGMEM =
{
	SD_API_CARD,
	SD_API_FILE_NOT_FOUND,
	SD_API_FILE_INVALID,
	SD_API_CARD_NOT_PRESENT,
	SD_API_FILE_REMOVED,
	SD_API_CARD_ERROR,
	SD_API_CARD_MOUNTED,
	SD_API_CARD_DETECTED,
	SD_API_CARD_MOUNT_FAILURE,
	SD_API_CARD_INIT_FAILURE
};


BRTOS_Mutex * SDCard_ResourceInit(INT8U priority)
{
  // Cria um mutex informando que o recurso está disponível
  // Prioridade máxima a acessar o recurso = priority
#if (SD_FAT_MUTEX_EN == 1)
  OSMutexCreate(&SDCardResource,priority);
#else
  (void)priority;
#endif  
  return SDCardResource;
}

#include "terminal.h"
void SDCard_PrintStatus(INT8U verbose, INT8U status)
{
	#if COLDUINO
		PRINT(verbose==VERBOSE_ON, SDCard_StringTable[0]);	
		PRINT(verbose==VERBOSE_ON, SDCard_StringTable[status]);	
	#else
	if(verbose==VERBOSE_ON)
	{
		printf_terminal_P((PGM_P)pgm_read_word(&(SDCard_StringTable[0])));	
		printf_terminal_P((PGM_P)pgm_read_word(&(SDCard_StringTable[status])));		
	}
	#endif
}

INT8U SDCard_Init(INT8U verbose)
{ 
  FRESULT f_res;
  
#if SD_CARD_PORT && SD_CARD_DETECTION

	#if __GNUC__
	  SD_AUSENT_DIR_OUT();
	  SD_AUSENT_PUP();
	#else
	  _SD_AUSENT = _IN;
	  SD_AUSENT_PULLUP = 1; 
	#endif
	#ifdef SOCKWP
		#if __GNUC__
			SD_WP_DIR_IN();
			SD_WP_PUP();
		#else
			_SD_WP = _IN;
			SD_WP_PULLUP = 1;
		#endif
	#endif
#endif  
  
  nop();nop();nop();  
  if (GetCardInit())
  {    	
	SDCard_PrintStatus(verbose,SD_CARD_MOUNTED);	
    return SD_OK;
  }
  else
  {	
    // Check the status of the SD card and sends messages
    if (SD_AUSENT)
    {	  
      SDCard_PrintStatus(verbose, SD_CARD_NOT_PRESENT);
      return NO_SD_CARD;
    }   
    else
    {         		      
		  // Initialize SD card
		  if (disk_initialize(0) == OK)
		  {
			   SDCard_PrintStatus(verbose, SD_CARD_DETECTED); 
			  
				// Mount FAT File System
				//f_res = f_mount(0, &FATFS_Obj);
    			f_res = f_mount(&FATFS_Obj, "", 0);
        
				if (f_res != FR_OK)
				{		  
				  SDCard_PrintStatus(verbose, SD_CARD_MOUNT_FAILURE);    
				  return MOUNT_SD_FAILS;
				}else
				{     
				  switch(GetCardType())
				  {
					case CT_MMC:
                		PRINT_P((verbose == VERBOSE_ON),PSTR(" MMC v3"));
					  break;

					case CT_SD1:
                		PRINT_P((verbose == VERBOSE_ON), PSTR(" SD v1"));
					  break;
                  
					case CT_SD2:
                		PRINT_P((verbose == VERBOSE_ON),PSTR(" SD v2"));
					  break;
                  
					case CT_SDC:
                		PRINT_P((verbose == VERBOSE_ON),PSTR(" SDHC"));
					  break;
                  
					default:
                		PRINT_P((verbose == VERBOSE_ON),PSTR(" Unknown"));
					  break;
				  }
				  SDCard_PrintStatus(verbose, SD_CARD_MOUNTED);	
			  return SD_OK;
			}
		}else
		{
			SDCard_PrintStatus(verbose, SD_CARD_INIT_FAILURE);
			return INIT_SD_FAILS;
		}
    }
  }
}


INT8U SDCard_SafeRemove(INT8U verbose)
{        
  if (GetCardInit())
  {    
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
      // Umount File System
      //f_mount(0,NULL);
      f_mount(NULL,"", 0);
      SetCardStat(STA_NOINIT | GetCardStat());
      
      #if (SD_FAT_MUTEX_EN == 1)
        OSMutexRelease(SDCardResource);
      #endif    
	    
      PRINT_P((verbose == VERBOSE_ON), PSTR(" is safe to remove!\n\r") );
      return SD_OK;
  }
  else
  {	  
	  SDCard_PrintStatus(verbose, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }    
}

	  
void ListFiles(CHAR8 *ptr)
{
	 FRESULT f_res;
	 INT32U  p1, s1, s2;
	 FILINFO Finfo;  // File Info object
	 FATFS   *fs;	 // Pointer to file system object*/
	 CHAR8 _dir[] = ".";
    
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif  
	  
    if (GetCardInit())
    {      
			// list files
			terminal_newline();
      		if (ptr == NULL) ptr = _dir;
      		
      		p1 = s1 = s2 = 0;
			f_res = f_opendir(&Dir, ptr);
				
			if (!f_res)
			{
  					for(;;)
  					{
				#if _USE_LFN
  						Finfo.lfname = Lfname;
  						Finfo.lfsize = sizeof(Lfname);
				#endif            
  						f_res = f_readdir(&Dir, &Finfo);
  						if ((f_res != FR_OK) || !Finfo.fname[0]) break;
  						if (Finfo.fattrib & AM_DIR)
  						{
  							s2++;
  						} else
  						{
  							s1++;
  							p1 += Finfo.fsize;
  						}

					PRINT(TRUE,"%c%c%c%c%c %u/%02u/%02u %02u:%02u %9l  %s",
					(Finfo.fattrib & AM_DIR) ? 'D' : '-',
					(Finfo.fattrib & AM_RDO) ? 'R' : '-',
					(Finfo.fattrib & AM_HID) ? 'H' : '-',
					(Finfo.fattrib & AM_SYS) ? 'S' : '-',
					(Finfo.fattrib & AM_ARC) ? 'A' : '-',
					(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
					(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63,
					Finfo.fsize, &(Finfo.fname[0]));
										 
                Finfo.fname[0] = 0;
				#if _USE_LFN
  					PRINT(TRUE,"  %s", Lfname);					
				#endif
  					terminal_newline();
				
  				}
			}

			PRINTA("%4l File(s), %l bytes total \n\r%4l Dir(s)", s1, p1, s2);

			if (f_getfree(ptr, (DWORD*)&p1, &fs) == FR_OK)
			{				
				PRINTA(", %l", (uint32_t)(p1 * fs->csize * 512));
				PRINTA_P(PSTR("bytes free \n\r"));
			}     
	}
	else
	{
		SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
	}

    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexRelease(SDCardResource);
    #endif
}



#define CSV_NAME_SIZE  13
void CSVListFiles(char **files)
{
	 FRESULT f_res;
	 INT32U  p1, s1, s2;
	 INT8U   i;
	 INT8U j;
	 CHAR8   *ptr;
	 char	 *file;  
	 FILINFO Finfo;  // File Info object
	 DIR     Dir; // Directory object
    
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
    if (GetCardInit())
    {      
        // list files
      	ptr = ".";
      	
      	p1 = s1 = s2 = 0;
		f_res = f_opendir(&Dir, ptr);
		
		file = (char*)files;				
		if (!f_res) 
		{
			i = 0;
			for(;;)
  			{            
  				f_res = f_readdir(&Dir, &Finfo);
  				if ((f_res != FR_OK) || !Finfo.fname[0]) break;
  				if (Finfo.fattrib & AM_DIR)
  				{
  					s2++;
  				} else
  				{
  					s1++;
  					p1 += Finfo.fsize;
  				}
  				
			    /* CSV is found ? */
  				for(j = 0; j<CSV_NAME_SIZE; j++)
  				{
  					if (Finfo.fname[j] == '.')
  					{
  						if ((Finfo.fname[j+1] == 'C') || (Finfo.fname[j+1] == 'c'))
  						{
  							if ((Finfo.fname[j+2] == 'S') || (Finfo.fname[j+2] == 's'))
							{
  								if ((Finfo.fname[j+3] == 'V') || (Finfo.fname[j+3] == 'v'))
  								{
  					  				for(j = 0; j<CSV_NAME_SIZE; j++)
  					  				{
  					  					
  					  					/* yes. it is a csv file */
  					  					if (j<(CSV_NAME_SIZE-1))
  					  					{
  					  						*file++ = Finfo.fname[j];
  					  					}else
  					  					{
  					  						*file++ = 0;
  					  					}
  					  				}
  					  				i++;  								
  								}
							}
  						}
  					}
  				}  				
  				
  				if (i>=CSV_NAME_SIZE) break; 
				
  			}
		}
	}

    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexRelease(SDCardResource);
    #endif
}

  
INT8U ReadFile(CHAR8 *FileName, INT8U verbose)
{
	INT32U  p1, p2, s2;
	INT16U  cnt = 0;
	INT16U  i = 0;
	INT8U    Buff[16];  // Read/Write Buffer
	  
	if (GetCardInit())
	{

		#if (SD_FAT_MUTEX_EN == 1)
		OSMutexAcquire(SDCardResource);
		#endif
      
		  if (f_open(&file_obj, (CHAR8*)FileName, 	FA_READ) == FR_OK)
		  {  
			PRINT_P((verbose == VERBOSE_ON),PSTR("\n\r"));
        
			p2 = 0;  			
			SetFatTimer((INT32U)0);     
			p1 = f_size(&file_obj);
        
			PRINTA_P(PSTR("file size: ")); PRINTA("%u", p1); PRINTA_P(PSTR(" bytes.\n\r"));
			while (p1) 
			{
				cnt = MIN(p1,sizeof(Buff));
				p1 -= cnt;
				if (f_read(&file_obj, (CHAR8*)Buff, cnt, (UINT*)&s2) != FR_OK)
				{
				  PRINTA_P(PSTR("\n\r file read error. \n\r"));
				  break;
				}else
				{
					p2 += s2;	 					                					
			
					// Imprime dados no terminal
					for(i=0;i<cnt;i++)
					{
					  putchar_terminal(Buff[i]);
					}
					
					//if (cnt != s2) break; 
				}
			} // end while
				
			GetFatTimer(&s2);
			f_close(&file_obj);
        
			PRINTA("\n\r%u", p2);PRINTA_P(PSTR(" bytes read with "));  			  
			PRINTA("%u", s2 ? (p2 * 100 / s2) : 0); PRINTA_P(PSTR(" bytes/sec.\n\r"));   
        
			#if (SD_FAT_MUTEX_EN == 1)
			  OSMutexRelease(SDCardResource);
			#endif        
        
			return SD_FILE_READ;
		} 
		else
		{       
        
			PRINT_P((verbose == VERBOSE_ON),PSTR("\n\r"));
			PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
			PRINT_P((verbose == VERBOSE_ON), PSTR(" not found.\n\r"));
			
			#if (SD_FAT_MUTEX_EN == 1)
			OSMutexRelease(SDCardResource);
			#endif
			
			return SD_FILE_NOT_FOUND;
		}
	}
	else
	{
		SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
		return SD_FAT_ERROR;
	}
}


INT8U ChangeDir(CHAR8 *FileName, INT8U verbose)
{
 
  if (GetCardInit())
  {
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif 
      
      if (f_chdir(FileName) == FR_OK)
      {  
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON),PSTR("\n\r"));    
        return SD_OPEN_DIR_OK;
      }
      else
      {
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rDirectory "));
        PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT_P((verbose == VERBOSE_ON), PSTR(" does not exist !\n\r"));
        
        return SD_OPEN_DIR_FAILURE;
      }
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}

INT8U CreateFile(CHAR8 *FileName, INT8U verbose)
{
  
  if (GetCardInit())
  {
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
	         
      if (f_open(&file_obj, FileName, 	FA_CREATE_NEW) == FR_OK)
      {  
        f_close(&file_obj);
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON), PSTR("\n\r"));
        PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT_P((verbose == VERBOSE_ON), PSTR(" was created successfully.\n\r"));
        
        return SD_CREATE_FILE_OK;
      }
      else
      {
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON),PSTR("\n\r"));
        PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT((verbose == VERBOSE_ON), PSTR(" was not created.\n\r"));        
        return SD_CREATE_FILE_FAILURE;
      }
    
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}


INT8U CreateDir(CHAR8 *FileName, INT8U verbose)
{
  
  if (GetCardInit())
  {
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
  
      PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rDirectory "));
      if (f_mkdir( FileName) == FR_OK)
      {  
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        
        PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT_P((verbose == VERBOSE_ON), PSTR(" was created successfully.\n\r"));
        
        return SD_CREATE_DIR_OK;
      }
      else
      {
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
		PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT_P((verbose == VERBOSE_ON), PSTR(" was not created.\n\r"));
        
        return SD_CREATE_DIR_FAILURE;
      }    
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}


INT8U DeleteFile(CHAR8 *FileName, INT8U verbose)
{
  INT8U sd_status = 0;
  
  if (GetCardInit())
  {  
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
        
      sd_status = f_unlink(FileName);
      
      #if (SD_FAT_MUTEX_EN == 1)
        OSMutexRelease(SDCardResource);
      #endif      
      
      if (sd_status == FR_OK)
      {

        PRINT_P((verbose == VERBOSE_ON), PSTR("\n\r"));                       
        PRINT((verbose == VERBOSE_ON), (CHAR8*)FileName);
        PRINT_P((verbose == VERBOSE_ON), PSTR(" deleted! \n\r"));      
        return SD_FILE_DELETED;
      }
      else
      {
        if (sd_status == FR_DENIED)
        {
           PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rDelete file or directory denied.\n\r"));
           PRINT_P((verbose == VERBOSE_ON), PSTR("Directory is not empty or file is write-protected.\n\r"));        
           return SD_DELETE_FILE_DENIED;
        }
        else
        {
          PRINT((verbose == VERBOSE_ON), SD_API_FILE_NOT_FOUND);
          return SD_FILE_NOT_FOUND;
        }
      }    
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}


INT8U RenameFile(CHAR8 *OldFileName,CHAR8 *NewFileName, INT8U verbose)
{
  INT8U sd_status = 0;
  
  if (GetCardInit())
  {  
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif    
    
        // Passa para a função os nomes dos arquivos
      sd_status = f_rename(OldFileName, NewFileName);
      
      #if (SD_FAT_MUTEX_EN == 1)
        OSMutexRelease(SDCardResource);
      #endif      
      
      if(sd_status == FR_OK)
      {
        PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rFile found and renamed !\n\r"));      
        
        return SD_FILE_RENAMED;
      }
      else
      {
           
        PRINT((verbose == VERBOSE_ON), (CHAR8*)SD_API_FILE_NOT_FOUND);       
        
        return SD_FILE_NOT_FOUND;
      }    
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
	  return SD_FAT_ERROR;
  }
}

#if 1	
INT8U CopyFile(CHAR8 *SrcFileName,CHAR8 *DstFileName, INT8U verbose)
{
	
  INT32U  p1, p2, s1, s2;
  CHAR8   *NewDstName, *CopyName;
  INT8U   f_res = 0;
  FIL      file_obj2;
  INT8U    Buff[16];  // Read/Write Buffer
  
  if (GetCardInit())
  {  
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif
      
      // Passa para a função os nomes dos arquivos
      if (f_open(&file_obj, SrcFileName, FA_OPEN_EXISTING | FA_READ) != FR_OK)
      {        
        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rSource file does not exist !\n\r"));      
        
        return SD_COPY_FILE_FAILURE;      
      }
      
      if (f_open(&file_obj2, DstFileName, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
      {
        // Complementa nome do arquivo
        CopyName = SrcFileName;
        NewDstName = DstFileName;
        
        while(*NewDstName)
        {
          NewDstName++;
        }
        
        NewDstName--;
        if (*NewDstName != '/')
        {
          NewDstName++;
          *NewDstName = '/';
          NewDstName++;
        }else
        {
          NewDstName++;
        }
        
        strcpy(NewDstName,CopyName);
        
        if (f_open(&file_obj2, DstFileName, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {                
          
          #if (SD_FAT_MUTEX_EN == 1)
            OSMutexRelease(SDCardResource);
          #endif          
          
          PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rDestination file could not be created or already exist !\n\r"));       
          
            
          f_close(&file_obj);
          return SD_COPY_FILE_FAILURE;            
        }
      }

      PRINT_P((verbose == VERBOSE_ON), PSTR("\n\rCopying file\n\r"));
     
      
	  SetFatTimer((INT32U)0);  
	  p1 = 0;
		
	  for (;;) 
	  {
		f_res = f_read(&file_obj, Buff, sizeof(Buff), (UINT*)&s1);
		if (f_res || s1 == 0) break;   /* error or eof */
		f_res = f_write(&file_obj2, Buff, s1, (UINT*)&s2);
		p1 += s2;
		if (f_res || s2 < s1) break;   /* error or disk full */											
	  }			
		
	  f_close(&file_obj);
	  f_close(&file_obj2);
      
            
       GetFatTimer(&p2);                                   
       PRINT((verbose == VERBOSE_ON),"\n\r%l", p1);    
	   PRINT_P((verbose == VERBOSE_ON),PSTR(" bytes copied with "));    
	   PRINT((verbose == VERBOSE_ON),"%l", p2 ? (p1 * 100 / p2) : 0);    
	   PRINT_P((verbose == VERBOSE_ON),PSTR(" bytes/sec.\n\r"));    
      
      #if (SD_FAT_MUTEX_EN == 1)
        OSMutexRelease(SDCardResource);
      #endif      
      
      return SD_FILE_COPIED;
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }  
}
#endif



INT8U WriteUptimeLog(INT8U verbose)
{
  OSTime Uptime;
  OSDate UpDate;   
  
  if (GetCardInit())
  {
    #if (SD_FAT_MUTEX_EN == 1)
      OSMutexAcquire(SDCardResource);
    #endif
        
        if (f_open(&file_obj, "uptime.txt", FA_WRITE) == FR_NO_FILE)
        {     
          f_open(&file_obj, "uptime.txt", 	FA_CREATE_NEW | FA_WRITE);
        }
        f_lseek(&file_obj,f_size(&file_obj));
        
        UserEnterCritical();
        Uptime = OSUptime();
        UpDate = OSUpDate();
        UserExitCritical();
        
        f_printf(&file_obj, "Uptime: %d Days, %d Hours, %d minutes and %d seconds \n\r", UpDate.RTC_Day, Uptime.RTC_Hour, Uptime.RTC_Minute,Uptime.RTC_Second);  
        f_close(&file_obj);

        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif        
        
        PRINT_P((verbose == VERBOSE_ON),PSTR("\n\rUptime written !\n\r"));  
        
        return SD_FILE_WRITTEN;   
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}

#include <ctype.h>
/*------------------------------------------------------------/
/ Open or create a file in append mode
/------------------------------------------------------------*/

FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;
    
#if (SD_FAT_MUTEX_EN == 1)
  OSMutexAcquire(SDCardResource);
#endif 
  
    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    
#if (SD_FAT_MUTEX_EN == 1)
  OSMutexRelease(SDCardResource);
#endif     
  
    return fr;
}

/*------------------------------------------------------------/
/ Remove all contents of a directory
/ This function works regardless of _FS_RPATH.
/------------------------------------------------------------*/

FRESULT empty_directory (
    char* path      /* Working buffer filled with start directory */
)
{
    UINT i, j;
    FRESULT fr;
    DIR dir;
    FILINFO fno;
    
#if (SD_FAT_MUTEX_EN == 1)
  OSMutexAcquire(SDCardResource);
#endif 

#if _USE_LFN
    fno.lfname = 0; /* Disable LFN output */
#endif
    fr = f_opendir(&dir, path);
    if (fr == FR_OK) {
        for (i = 0; path[i]; i++) ;
        path[i++] = '/';
        for (;;) {
            fr = f_readdir(&dir, &fno);
            if (fr != FR_OK || !fno.fname[0]) break;
            if (_FS_RPATH && fno.fname[0] == '.') continue;
            j = 0;
            do
                path[i+j] = fno.fname[j];
            while (fno.fname[j++]);
            if (fno.fattrib & AM_DIR) {
                fr = empty_directory(path);
                if (fr != FR_OK) break;
            }
            fr = f_unlink(path);
            if (fr != FR_OK) break;
        }
        path[--i] = '\0';
        f_closedir(&dir);
    }
    
#if (SD_FAT_MUTEX_EN == 1)
  OSMutexRelease(SDCardResource);
#endif     

    return fr;
}

#define NIB_LOW(c)	((c) & 0x0F)
#define NIB_HIGH(c) ((c >> 4) & 0x0F)
		
static void bin2char(CHAR s[], INT8U c)
{
	s[1] = ((NIB_LOW(c)) < 10) ? (NIB_LOW(c)) + '0': (NIB_LOW(c)) + '7'; 
	s[0] = ((NIB_HIGH(c)) < 10) ? (NIB_HIGH(c)) + '0': (NIB_HIGH(c)) + '7'; 
}
		
INT8U WriteFile(FIL* fp,  const char* filename, INT8U *ptr_data, INT8U length)
{

  if (ptr_data == NULL) {  return SD_FAT_ERROR; }
  
  if (GetCardInit())
  {
		#if (SD_FAT_MUTEX_EN == 1)
		OSMutexAcquire(SDCardResource);
		#endif

        
        if (f_open(fp, filename, FA_WRITE) == FR_NO_FILE)
        {     
        	f_open(fp, filename, FA_CREATE_NEW | FA_WRITE); 
        }
        
        /* Move o cursor para o fim do arquivo */
        f_lseek(fp,f_size(fp));
				
		INT8U c;
		CHAR s[2];		
		
		f_putc('W',fp);
		
		while(length > 0)
		{
			c = *ptr_data;			
			ptr_data++;
			length--;
			bin2char(s,c);
			
			f_putc(s[1],fp);
			f_putc(s[0],fp);
			//f_putc(',',fp);
		}
		
		f_printf(fp, "\n\r");
		
        f_close(fp);       

        
        #if (SD_FAT_MUTEX_EN == 1)
          OSMutexRelease(SDCardResource);
        #endif       
        
        return SD_FILE_WRITTEN;    
  }
  else
  {
	  SDCard_PrintStatus(TRUE, SD_CARD_NOT_PRESENT);
      return SD_FAT_ERROR;
  }
}

/* Pega ultimo arquivo criado. A função lista os arquivos por data
 * de criação. Desta forma, o últmo arquivo salvo é o úlitmo listado.
 *  */
INT8U GetLastCreatedFileName(char fileName[])
{

	FRESULT f_res;
	CHAR8 *ptr = ".";
	INT8U ret = FALSE;
	FILINFO Finfo;  // File Info object
	DIR     Dir; // Directory object

#if (SD_FAT_MUTEX_EN == 1)
	OSMutexAcquire(SDCardResource);
#endif    
	if (GetCardInit())
	{
		f_res = f_opendir(&Dir, ptr);
			
		/* Percorre o diretório.*/
		if (!f_res)
		{
			for (;;)
			{
#if _USE_LFN
				Finfo.lfname = Lfname;
				Finfo.lfsize = sizeof(Lfname);
#endif
				f_res = f_readdir(&Dir, &Finfo);

				if ((f_res != FR_OK) || !Finfo.fname[0])
				{
					break;						
				}
				else
				{
					/* guarda nome do ultimo arquivo salvo */
					strcpy(fileName, Finfo.fname);
					ret = TRUE;
				}
					
				Finfo.fname[0] = 0;
			}
		}	
		
	}

#if (SD_FAT_MUTEX_EN == 1)
	OSMutexRelease(SDCardResource);
#endif
	
	return ret;
}