
#ifndef _TIME_LIB_H_
#define _TIME_LIB_H_

/* UTC time function  */
#define YEAR0                   1900
#define EPOCH_YR                1970
#define SECS_DAY                (24L * 60L * 60L)
#define LEAPYEAR(year)          (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)          (LEAPYEAR(year) ? 366 : 365)
#define FIRSTSUNDAY(timp)       (((timp)->tm_yday - (timp)->tm_wday + 420) % 7)
#define FIRSTDAYOF(timp)        (((timp)->tm_wday - (timp)->tm_yday + 420) % 7)

#define TIME_MAX                2147483647L

#define TM_YEAR_BASE   1900
#define DAYSPERLYEAR   366
#define DAYSPERNYEAR   365
#define DAYSPERWEEK    7

#include "BRTOS.h"
#include <time.h>


typedef INT32U time_t;

#if 0
#ifndef _TM_DEFINED
#define _TM_DEFINED

struct tm {
  int tm_sec;                   // Seconds after the minute [0, 59]
  int tm_min;                   // Minutes after the hour [0, 59]
  int tm_hour;                  // Hours since midnight [0, 23]
  int tm_mday;                  // Day of the month [1, 31]
  int tm_mon;                   // Months since January [0, 11]
  int tm_year;                  // Years since 1900
  int tm_wday;                  // Days since Sunday [0, 6]
  int tm_yday;                  // Days since January 1 [0, 365]
  int tm_isdst;                 // Daylight Saving Time flag
  int tm_gmtoff;                // Seconds east of UTC
  char *tm_zone;                // Timezone abbreviation
};

#endif


struct tm
{	
	int tm_sec; /* Segundos, 0-59*/
	int tm_min; /* Minutos, 0-59*/
	int tm_hour; /*Horas 0-23 */
	int tm_mday; /*dia do mês, 1-31 */
	int tm_mon; /* mês a partir de janeiro, 0-11 */
	int tm_year; /* anos a partir de 1900 */
	int tm_wday; /* dias a partir de domingo, 0-6 */
	int tm_yday; /* dias a partir de 1 de janeiro 1-365 */
	int tm_isdst; /* Indicador de horário de verão */
};
#endif

time_t mktime(struct tm *tmbuf);
struct tm *localtime(const time_t *timer);
size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *t);
time_t ConvertDateTimeToUnixTime(OSDateTime * dt);

#endif
