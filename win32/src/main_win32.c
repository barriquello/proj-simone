/*
 ============================================================================
 Name        : Test_logger.c
 Author      : Carlos H. Barriquello
 Version     :
 Description : Data logger
 ============================================================================

 - Arquivo de log local

1) um arquivo para cada monitor. Monitor � entendido como um conjunto de dados estruturados,
geralmente, associado a um �nico equipamento. Ex.: medidas el�tricas associdas ao um
medidor de grandezas el�tricas.

2) Dados devem guardados na forma de s�ries temporais ordenadas.
Uma s�rie temporal � um conjunto de dados associados a uma estampa de tempo.

3) As s�ries s�o armazenadas no formato ASCII hexadecimal como um conjunto de bytes finalizados
por "nova linha e retorno" (\r\n), correspondendo cada linha a uma entrada de dados com
estampa de tempo.

4) As estampas de tempo podem estar nas entradas de dados, ou serem calculados a partir de uma
estampa inicial (ex. data e hora da cria��o do arquivo), quando estiverem separadas por um
intervalo constante. O formato da estampa � determinada pela vers�o do log. V00 - com estampas calculadas a partir da estampa inicial. As configura��es s�o
guardadas no cabe�alho, V01 - com estampas inclu�das

5) Cada arquivo inicia com um cabe�alho contendo (3 linhas com at� 16 caracteres cada):
L1: Versao e Monitor ID, Bytes por linha e intervalo entre medi��es.
L2: data e hora inicial, flag de sincroniza��o do arquivo,
L3: indice da �ltima linha enviada (4 bytes).
L4: contador de entradas (linhas) (4 bytes)

Ex.: .
V00M00B0080I0030\r\n
TaaaammddhhmmssN\r\n
P0000\r\n
C0000\r\n
00
01
02
03
04


6) Os arquivos do logger s�o nomeados com a data/hora de sua cria��o no formato "AAMMDDHH.txt". Ao iniciar o logger, ele ordena os arquivos por data e tenta abrir o �ltimo arquivo salvo.
Caso ele n�o esteja sincronizado, os dados s�o armazenados no arquivo "99123123.txt". Este arquivo dever� ser renomeado com a data/hora de sua cria��o, quando houver a sincroniza��o do rel�gio do logger.
A data/hora de cria��o ser� obtida a partir da data atual retrocedida de acordo com a quantidade de entradas de dados no arquivo.
Caso j� haja um arquivo com o mesmo nome, o mesmo dever� ser renomeado para a data/ hora logo posterior.

Ex.:

15010107.txt >
...I0030...
T20150101073000S
...
00
01
02
03


99123123.txt >
...
T00000000000000N
...
00
01
02

sincroniza��o em T20150101073400S

-> renomear para:

15010108.txt >
...
T20150101073300S ->
...
00 -> 3300
01 -> 3330
02 -> 3400


7) Caso o contador de entradas seja igual a FFFF (65535). Fecha-se o arquivo e inicia-se um arquivo novo.
8) Caso o indice da �ltima linha enviada seja igual a FFFE (65534), o arquivo dever� ser renomeado com altera��o da extens�o (.txt -> .txd).
9) OS arquivos de log de cada monitor s�o guardados em diret�rios separados nomeados com a ID do monitor.

 */

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys\timeb.h>

#include "minIni.h"
#include "monitor.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

void main_monitor(void);

int main(void)
{

	struct timeb start, end;
	uint16_t diff;

	ftime(&start);

	main_monitor();

	ftime(&end);
	diff = (uint16_t) (1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	printf("\nOperation took %u milliseconds\n", diff);

	getchar();
	return EXIT_SUCCESS;

}
#endif

