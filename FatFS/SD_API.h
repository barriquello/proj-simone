#ifndef SD_API_H_
#define SD_API_H_

#include "BRTOS.h"
#include "SD.h"
#include "ff.h"


/* Defines */
#define SD_FAT_MUTEX_EN		1		// Enable SD/FAT file system mutex
#define SD_BMP				0		// Enable SD/BMP file read
#define SD_GLCD_CALIB		0
#define SD_WAVE				0		// Enable SD/WAVE file read



#if (SD_WAVE ==1)
	#define TestWaveFileSuport 	1
	#define WAV_NAME_SIZE		13
	#define WAV_LIST_SIZE		20
#endif

/// SD defines
#define API_COMMAND_FAIL     (INT8U)0x80
#define API_COMMAND_OK       (INT8U)0x81
#define API_FILENAME_ERROR   (INT8U)0x82

#define NO_CAPS              (INT8U)0x83
#define CAPS_1               (INT8U)0x84
#define CAPS_2               (INT8U)0x85
#define CAPS_12              (INT8U)0x86

#define WRITE_BUFFER_SIZE    512


INT8U SDCard_Init(INT8U verbose);
INT8U SDCard_SafeRemove(INT8U verbose);

void ListFiles(INT8U *pname1);
INT8U ReadFile(CHAR8 *FileName, INT8U verbose);
INT8U RenameFile(CHAR8 *OldFileName,CHAR8 *NewFileName, INT8U verbose);
INT8U CreateFile(CHAR8 *FileName, INT8U verbose);
INT8U CreateDir(CHAR8 *FileName, INT8U verbose);
INT8U DeleteFile(CHAR8 *FileName, INT8U verbose);
INT8U file_name_verify(CHAR8 *pname1,CHAR8 *pname2, INT8U *pfile, INT8U num);
INT8U ChangeDir(CHAR8 *FileName, INT8U verbose);
INT8U CopyFile(CHAR8 *SrcFileName,CHAR8 *DstFileName, INT8U verbose);
INT8U WriteUptimeLog(INT8U verbose);
void SDCard_ResourceInit(INT8U priority);
INT8U GetLastCreatedFileName(char fileName[]);
INT8U WriteFile(FIL* fp,  const char* filename, INT8U *ptr_data, INT8U length);

FRESULT open_append (FIL* fp, const char* path );    /* [OUT] File object to create , [IN]  File name to be opened */
FRESULT empty_directory (char* path);      /* Working buffer filled with start directory */

void CSVListFiles(char **files);

#if 0
INT8U WriteFile(INT8U *FileName, void (*fill_buffer)(void),INT8U verbose);
INT8U FormatDisk(INT8U verbose);
INT8U cmd_verify_zeros(INT8U *pfile, INT8U num);
#endif


extern FIL      file_obj;

//Mensagens padrão da API do SD
extern const INT8U *SD_API_FILE_NOT_FOUND;
extern const INT8U *SD_API_FILE_INVALID;
extern const INT8U *SD_API_CARD_BUSY;
extern const INT8U *SD_API_CARD_NOT_PRESENT;


/******** COMANDS USED IN THE APPLICATION *************/
typedef enum
{
 FILE_FOUND_DUMMY,
 FILE_NOT_FOUND_DUMMY,
 FILE_CREATE_OK_DUMMY,
 NO_FILE_ENTRY_AVAILABLE_DUMMY,
 NO_FAT_ENTRY_AVAIlABLE_DUMMY,
 ERROR_IDLE_DUMMY,
 FILE_DELETED_DUMMY,
 SD_FAT_OK,
 SD_FAT_ERROR,
 SD_BUSY,
 SD_INACTIVE,
 SD_CARD_FORMATTING,
 SD_CARD_FORMATTED,
 SD_FILE_RENAMING,
 SD_FILE_RENAMED,
 SD_FILE_WRITING,   
 SD_FILE_DELETING, 
 SD_FILE_DELETED, 
 SD_DELETE_FILE_DENIED, 
 SD_FILE_LISTING,
 SD_FILE_READING, 
 SD_FILE_READ,
 SD_DIR_CREATING,
 SD_DIR_CHANGING,
 SD_FILE_COPYING,
 SD_FILE_COPIED,
 SD_COPY_FILE_FAILURE,
 SD_FILE_NOT_FOUND,
 SD_FILE_FOUND,
 SD_CREATE_FILE_FAILURE,
 SD_CREATE_FILE_OK,
 SD_CREATE_DIR_OK,
 SD_CREATE_DIR_FAILURE, 
 SD_OPEN_DIR_OK,
 SD_OPEN_DIR_FAILURE,  
 SD_FILE_WRITE_FAILURE,
 SD_FILE_WRITTEN,
 SD_FILE_SUPPORTED,
 SD_FILE_NOT_SUPPORTED,
 VERBOSE_ON,
 VERBOSE_OFF
} SD_STATE;

enum   //estados existentes na máqiuna
{
    NOME,
    EXTENSAO,
    FIM,
};


#if (SD_WAVE == 1)
	//Wave File Header - The Canonical Form:
	//Wave data files is little-endian. Big-endian Wave's have the identifier RIFX instead of RIFF.
	//8-bit samples are stored as unsigned bytes, ranging from 0 to 255.
	//16-bit samples are stored as 2's-complement signed integers, ranging from -32768 to 32767.

	// Struct aligned in 2 bytes: __attribute__((packed, aligned(2)))
	#pragma push
	#pragma pack(2)
	typedef struct 
	{	
	   unsigned long	ChunkID;		//4 bytes = "RIFF" / decimal: 1179011410 / 0x46464952 little-endian / 0x52494646 big-endian form
	   unsigned long	ChunkSize;		//4 bytes
	   unsigned long	Format; 		//4 bytes = "WAVE" / decimal: 1163280727/ 0x57415645 big-endian form 
	   unsigned long	Subchunk1ID; 	//4 bytes = "fmt"  /decimal:544501094 / 0x666d7420 big-endian form
	   unsigned long	Subchunk1Size; 	//4 bytes
	   unsigned short	AudioFormat;	//2 bytes: 0 =???;  1 = Linear quantization (0x1000 big-endian form); Others = compression
	   unsigned short	NumChannels;	//2 bytes: Mono = 1 (0x1000 big-endian form); Stereo = 2(0x2000 big-endian form); etc.
	   unsigned long	SampleRate;		//4 bytes: 8000, 44100 (0x44AC0000 big-endian form ), etc.
	   unsigned long	ByteRate;		//4 bytes: SampleRate * NumChannels * BitsPerSample/8
	   unsigned short	BlockAlign;		//2 bytes: NumChannels * BitsPerSample/8
	   unsigned short	BitsPerSamples;	//2 bytes: 8 = 8 bits; 16 = 16 bits; etc.
	   unsigned long	Subchunk2ID;	//4 bytes = "data" /decimal:220982 / 0x64617461 big-endian form
	   unsigned long	Subchunk2Size;	//4 bytes: NumSamples * NumChannels * BitsPerSample/8
	// unsigned long 	Data;			//(ChunkSize) bytes 
	} WAVE_FILE;
	#pragma pop
	
	typedef struct { 
		   INT8U*	Buff;
		   INT16U	Size;
		   INT16U 	SampleRate;		//SampleRate	
		   INT8U	BitRate;		//BitsPerSamples	
		   INT8U	NumChannels;	//NumChannels

		} WAVE_BUFFER;
	
#endif

#if (SD_WAVE == 1)
	void 	Wave_NullBufferError(void);
	INT8U 	Wave_ReadFile(CHAR8 *FileName, INT8U* Buffer0, INT8U* Buffer1);
	void	Wave_SetSampleRate(INT16U WaveSampleRate);
	void	InstallPlayComponents(void);
	void 	WavListFiles(char **files);
	extern  INT8U		 WaveBuffer0[512];	// Play Buffer A
	extern  INT8U		 WaveBuffer1[512];	// Play Buffer B
	extern  BRTOS_Sem	 *SyncWaveBuffer;	//Semaforo
	extern  BRTOS_Mbox	 *SendWaveBuffer;	//Mail box
	extern  WAVE_BUFFER  WaveBuff;			// Wave play buffer + info	
#endif

#endif
