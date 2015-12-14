
//
//
// Time routines
//
// Copyright (C) 2002 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.  
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.  
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
// SUCH DAMAGE.
// 
#include "printf_lib.h"
#include "time_lib.h"
#include "stdio.h"
#include <stdint.h>

#ifndef CONST
#define CONST const
#endif

#ifndef PROGMEM
#define PROGMEM
#endif

#if COLDUINO && __GNUC__
#define STATIC
#else
#define STATIC static
#endif

static struct tm tmbuf;

CONST uint8_t _ytab[2][12] PROGMEM = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

#ifndef _WIN32
uint8_t _daylight = 0;              // Non-zero if daylight savings time is used
#endif

long _dstbias = 0;                  // Offset for Daylight Saving Time
long _timezone = 0;                 // Difference in seconds between GMT and local time

STATIC struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf)
{
  time_t time = *timer;
  uint32_t dayclock, dayno;
  int year = EPOCH_YR;

  dayclock = (uint32_t) time % SECS_DAY;
  dayno = (uint32_t) time / SECS_DAY;

  tmbuf->tm_sec = (int)(dayclock % 60);
  tmbuf->tm_min = (int)(dayclock % 3600) / 60;
  tmbuf->tm_hour = (int)(dayclock / 3600);
  tmbuf->tm_wday = (int)((dayno + 4) % 7); // Day 0 was a thursday
  while (dayno >= (uint32_t) YEARSIZE(year)) {
    dayno -= YEARSIZE(year);
    year++;
  }
  tmbuf->tm_year = year - YEAR0;
  tmbuf->tm_yday = (int)dayno;
  tmbuf->tm_mon = 0;
  while (dayno >= (uint32_t) PGM_READ_BYTE(_ytab[LEAPYEAR(year)][tmbuf->tm_mon])) {
    dayno -= PGM_READ_BYTE(_ytab[LEAPYEAR(year)][tmbuf->tm_mon]);
    tmbuf->tm_mon++;
  }
  tmbuf->tm_mday = (int)(dayno + 1);
  tmbuf->tm_isdst = 0;
  //tmbuf->tm_gmtoff = 0;
  //tmbuf->tm_zone = "UTC";
  return tmbuf;
}

STATIC struct tm *localtime_r(const time_t *timer, struct tm *tmbuf)
{
  time_t t;

  t = *timer - _timezone;
  return gmtime_r(&t, tmbuf);
}

#ifndef KERNEL
struct tm *gmtime(const time_t *timer) 
{
  return gmtime_r(timer, &tmbuf);
}

struct tm *localtime(const time_t *timer) {
  return localtime_r(timer, &tmbuf);
}
#endif


time_t mktime(struct tm *tmbuf) 
{
  long day, year;
  int tm_year;
  int yday, month;
  /*unsigned*/ long seconds;
  int overflow;
  long dst;

  tmbuf->tm_min += tmbuf->tm_sec / 60;
  tmbuf->tm_sec %= 60;
  if (tmbuf->tm_sec < 0) {
    tmbuf->tm_sec += 60;
    tmbuf->tm_min--;
  }
  tmbuf->tm_hour += tmbuf->tm_min / 60;
  tmbuf->tm_min = tmbuf->tm_min % 60;
  if (tmbuf->tm_min < 0) {
    tmbuf->tm_min += 60;
    tmbuf->tm_hour--;
  }
  day = tmbuf->tm_hour / 24;
  tmbuf->tm_hour= tmbuf->tm_hour % 24;
  if (tmbuf->tm_hour < 0) {
    tmbuf->tm_hour += 24;
    day--;
  }
  tmbuf->tm_year += tmbuf->tm_mon / 12;
  tmbuf->tm_mon %= 12;
  if (tmbuf->tm_mon < 0) {
    tmbuf->tm_mon += 12;
    tmbuf->tm_year--;
  }
  day += (tmbuf->tm_mday - 1);
  while (day < 0) {
    if(--tmbuf->tm_mon < 0) {
      tmbuf->tm_year--;
      tmbuf->tm_mon = 11;
    }
    day += PGM_READ_BYTE(_ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon]);
  }
  while (day >= PGM_READ_BYTE(_ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon])) {
    day -= PGM_READ_BYTE(_ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon]);
    if (++(tmbuf->tm_mon) == 12) {
      tmbuf->tm_mon = 0;
      tmbuf->tm_year++;
    }
  }
  tmbuf->tm_mday = day + 1;
  year = EPOCH_YR;
  if (tmbuf->tm_year < year - YEAR0) return (time_t) -1;
  seconds = 0;
  day = 0;                      // Means days since day 0 now
  overflow = 0;

  // Assume that when day becomes negative, there will certainly
  // be overflow on seconds.
  // The check for overflow needs not to be done for leapyears
  // divisible by 400.
  // The code only works when year (1970) is not a leapyear.
  tm_year = tmbuf->tm_year + YEAR0;

  if (TIME_MAX / 365 < tm_year - year) overflow++;
  day = (tm_year - year) * 365;
  if (TIME_MAX - day < (tm_year - year) / 4 + 1) overflow++;
  day += (tm_year - year) / 4 + ((tm_year % 4) && tm_year % 4 < year % 4);
  day -= (tm_year - year) / 100 + ((tm_year % 100) && tm_year % 100 < year % 100);
  day += (tm_year - year) / 400 + ((tm_year % 400) && tm_year % 400 < year % 400);

  yday = month = 0;
  while (month < tmbuf->tm_mon) {
    yday += PGM_READ_BYTE(_ytab[LEAPYEAR(tm_year)][month]);
    month++;
  }
  yday += (tmbuf->tm_mday - 1);
  if (day + yday < 0) overflow++;
  day += yday;

  tmbuf->tm_yday = yday;
  tmbuf->tm_wday = (day + 4) % 7;               // Day 0 was thursday (4)

  seconds = ((tmbuf->tm_hour * 60L) + tmbuf->tm_min) * 60L + tmbuf->tm_sec;

  if ((TIME_MAX - seconds) / SECS_DAY < day) overflow++;
  seconds += day * SECS_DAY;

  // Now adjust according to timezone and daylight saving time
  if (((_timezone > 0) && (TIME_MAX - _timezone < seconds)) || 
      ((_timezone < 0) && (seconds < -_timezone))) {
          overflow++;
  }
  seconds += _timezone;

  if (tmbuf->tm_isdst) {
    dst = _dstbias;
  } else {
    dst = 0;
  }

  if (dst > seconds) overflow++;        // dst is always non-negative
  seconds -= dst;

  if (overflow) return (time_t) -1;

  if ((time_t) seconds != seconds) return (time_t) -1;
  return (time_t) seconds;
}

#ifndef _WIN32
time_t ConvertDateTimeToUnixTime(OSDateTime * dt)
{
	struct tm tm;
	time_t unix_time;
	
	tm.tm_hour = dt->time.RTC_Hour;
	tm.tm_min = dt->time.RTC_Minute;
	tm.tm_sec = dt->time.RTC_Second;
	
	tm.tm_year = dt->date.RTC_Year - 1900;
	tm.tm_mon = dt->date.RTC_Month - 1;
	tm.tm_mday = dt->date.RTC_Day;	
	
	unix_time = mktime(&tm);	
	return unix_time;
}
#endif

#define SUNDAY_DEF  "Sunday"
#define MONDAY_DEF  "Monday"
#define TUESDAY_DEF  "Tuesday"
#define WEDNESDAY_DEF  "Wednesday"	 
#define THURSDAY_DEF  "Thursday"
#define FRIDAY_DEF  "Friday" 
#define SATURDAY_DEF  "Saturday"

CONST char SUNDAY_str[] PROGMEM = SUNDAY_DEF;
CONST char MONDAY_str[] PROGMEM=MONDAY_DEF;
CONST char TUESDAY_str[] PROGMEM=TUESDAY_DEF;
CONST char WEDNESDAY_str[] PROGMEM=WEDNESDAY_DEF;
CONST char THURSDAY_str[] PROGMEM=THURSDAY_DEF;
CONST char FRIDAY_str[] PROGMEM=FRIDAY_DEF;
CONST char SATURDAY_str[] PROGMEM=SATURDAY_DEF;

#define JANUARY_DEF		"January"
#define FEBRUARY_DEF	"February"
#define MARCH_DEF		"March"
#define APRIL_DEF		"April"
#define MAY_DEF			"May"
#define JUNE_DEF		"June"
#define JULY_DEF		"July"
#define AUGUST_DEF		"August"
#define SEPTEMBER_DEF	"September"
#define OCTOBER_DEF		"October"
#define NOVEMBER_DEF	"November"
#define DECEMBER_DEF	"December"

CONST char JANUARY_str[] PROGMEM = JANUARY_DEF;
CONST char FEBRUARY_str[] PROGMEM = FEBRUARY_DEF;
CONST char MARCH_str[] PROGMEM = MARCH_DEF;
CONST char APRIL_str[] PROGMEM = APRIL_DEF;
CONST char MAY_str[] PROGMEM = MAY_DEF;
CONST char JUNE_str[] PROGMEM = JUNE_DEF;
CONST char JULY_str[] PROGMEM = JULY_DEF;
CONST char AUGUST_str[] PROGMEM = AUGUST_DEF;
CONST char SEPTEMBER_str[] PROGMEM = SEPTEMBER_DEF;
CONST char OCTOBER_str[] PROGMEM = OCTOBER_DEF;
CONST char NOVEMBER_str[] PROGMEM =  NOVEMBER_DEF;
CONST char DECEMBER_str[] PROGMEM = DECEMBER_DEF;

  
CONST char * CONST _days[] PROGMEM = {
	SUNDAY_str,
	MONDAY_str,
	TUESDAY_str,
	WEDNESDAY_str,
	THURSDAY_str,
	FRIDAY_str,
	SATURDAY_str
};

CONST char * CONST _days_abbrev[] = {
  "Sun", "Mon", "Tue", "Wed", 
  "Thu", "Fri", "Sat"
};

CONST char * CONST _months[] PROGMEM= {
	JANUARY_str,
	FEBRUARY_str,
	MARCH_str,
	APRIL_str,
	MAY_str,
	JUNE_str,
	JULY_str,
	AUGUST_str,
	SEPTEMBER_str,
	OCTOBER_str,
	NOVEMBER_str,
	DECEMBER_str,
};

CONST char * CONST _months_abbrev[] = 
{
  "Jan", "Feb", "Mar",
  "Apr", "May", "Jun",
  "Jul", "Aug", "Sep",
  "Oct", "Nov", "Dec"
};


static char *_fmt(const char *format, const struct tm *t, char *pt, const char *ptlim);
static char *_conv(const int n, const char *format, char *pt, const char *ptlim);
static char *_add(const char *str, char *pt, const char *ptlim);

size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *t) {
  char *p;

  p = _fmt(((format == NULL) ? "%c" : format), t, s, s + maxsize);
  if (p == s + maxsize) return 0;
  *p = '\0';
  return (size_t)(p - s);
}

static char *_fmt(const char *format, const struct tm *t, char *pt, const char *ptlim) {
  for ( ; *format; ++format) {
    if (*format == '%') {
      if (*format == 'E') {
        format++; // Alternate Era
      } else if (*format == 'O') {
        format++; // Alternate numeric symbols
      }

      switch (*++format) {
        case '\0':
          --format;
          break;

        case 'A':
          pt = _add((t->tm_wday < 0 || t->tm_wday > 6) ? "?" : _days[t->tm_wday], pt, ptlim);
          continue;

        case 'a':
          pt = _add((t->tm_wday < 0 || t->tm_wday > 6) ? "?" : _days_abbrev[t->tm_wday], pt, ptlim);
          continue;

        case 'B':
          pt = _add((t->tm_mon < 0 || t->tm_mon > 11) ? "?" : _months[t->tm_mon], pt, ptlim);
          continue;

        case 'b':
        case 'h':
          pt = _add((t->tm_mon < 0 || t->tm_mon > 11) ? "?" : _months_abbrev[t->tm_mon], pt, ptlim);
          continue;

        case 'C':
          pt = _conv((t->tm_year + TM_YEAR_BASE) / 100, "%02d", pt, ptlim);
          continue;

        case 'c':
          pt = _fmt("%a %b %e %H:%M:%S %Y", t, pt, ptlim);
          continue;

        case 'D':
          pt = _fmt("%m/%d/%y", t, pt, ptlim);
          continue;

        case 'd':
          pt = _conv(t->tm_mday, "%02d", pt, ptlim);
          continue;

        case 'e':
          pt = _conv(t->tm_mday, "%2d", pt, ptlim);
          continue;

        case 'F':
          pt = _fmt("%Y-%m-%d", t, pt, ptlim);
          continue;

        case 'H':
          pt = _conv(t->tm_hour, "%02d", pt, ptlim);
          continue;

        case 'I':
          pt = _conv((t->tm_hour % 12) ? (t->tm_hour % 12) : 12, "%02d", pt, ptlim);
          continue;

        case 'j':
          pt = _conv(t->tm_yday + 1, "%03d", pt, ptlim);
          continue;

        case 'k':
          pt = _conv(t->tm_hour, "%2d", pt, ptlim);
          continue;

        case 'l':
          pt = _conv((t->tm_hour % 12) ? (t->tm_hour % 12) : 12, "%2d", pt, ptlim);
          continue;

        case 'M':
          pt = _conv(t->tm_min, "%02d", pt, ptlim);
          continue;

        case 'm':
          pt = _conv(t->tm_mon + 1, "%02d", pt, ptlim);
          continue;

        case 'n':
          pt = _add("\n", pt, ptlim);
          continue;

        case 'p':
          pt = _add((t->tm_hour >= 12) ? "pm" : "am", pt, ptlim);
          continue;

        case 'R':
          pt = _fmt("%H:%M", t, pt, ptlim);
          continue;

        case 'r':
          pt = _fmt("%I:%M:%S %p", t, pt, ptlim);
          continue;

        case 'S':
          pt = _conv(t->tm_sec, "%02d", pt, ptlim);
          continue;

        case 's': {
          struct tm  tm;
          char buf[32];
          time_t mkt;

          tm = *t;
          mkt = mktime(&tm);
          SNPRINTF(buf, sizeof(buf)-1, "%lu", mkt);
          pt = _add(buf, pt, ptlim);
          continue;
        }

        case 'T':
          pt = _fmt("%H:%M:%S", t, pt, ptlim);
          continue;

        case 't':
          pt = _add("\t", pt, ptlim);
          continue;

        case 'U':
          pt = _conv((t->tm_yday + 7 - t->tm_wday) / 7, "%02d", pt, ptlim);
          continue;

        case 'u':
          pt = _conv((t->tm_wday == 0) ? 7 : t->tm_wday, "%d", pt, ptlim);
          continue;

        case 'V':   // ISO 8601 week number
        case 'G':   // ISO 8601 year (four digits)
        case 'g': { // ISO 8601 year (two digits)
          int  year;
          int  yday;
          int  wday;
          int  w;

          year = t->tm_year + TM_YEAR_BASE;
          yday = t->tm_yday;
          wday = t->tm_wday;
          while (1) {
            int  len;
            int  bot;
            int  top;

            len = LEAPYEAR(year) ? DAYSPERLYEAR : DAYSPERNYEAR;
            bot = ((yday + 11 - wday) % DAYSPERWEEK) - 3;
            top = bot - (len % DAYSPERWEEK);
            if (top < -3) top += DAYSPERWEEK;
            top += len;
            if (yday >= top) {
              ++year;
              w = 1;
              break;
            }
            if (yday >= bot) {
              w = 1 + ((yday - bot) / DAYSPERWEEK);
              break;
            }
            --year;
            yday += LEAPYEAR(year) ? DAYSPERLYEAR : DAYSPERNYEAR;
          }
          if (*format == 'V') {
            pt = _conv(w, "%02d", pt, ptlim);
          } else if (*format == 'g') {
            pt = _conv(year % 100, "%02d", pt, ptlim);
          } else {
            pt = _conv(year, "%04d", pt, ptlim);
          }
          continue;
        }

        case 'v':
          pt = _fmt("%e-%b-%Y", t, pt, ptlim);
          continue;

        case 'W':
          pt = _conv((t->tm_yday + 7 - (t->tm_wday ? (t->tm_wday - 1) : 6)) / 7, "%02d", pt, ptlim);
          continue;

        case 'w':
          pt = _conv(t->tm_wday, "%d", pt, ptlim);
          continue;

        case 'X':
          pt = _fmt("%H:%M:%S", t, pt, ptlim);
          continue;

        case 'x':
          pt = _fmt("%m/%d/%y", t, pt, ptlim);
          continue;

        case 'y':
          pt = _conv((t->tm_year + TM_YEAR_BASE) % 100, "%02d", pt, ptlim);
          continue;

        case 'Y':
          pt = _conv(t->tm_year + TM_YEAR_BASE, "%04d", pt, ptlim);
          continue;

        case 'Z':
          pt = _add("?", pt, ptlim);
          continue;

        case 'z': {
          long absoff;
          if (_timezone >= 0) {
            absoff = _timezone;
            pt = _add("+", pt, ptlim);
          } else {
            absoff = _timezone;
            pt = _add("-", pt, ptlim);
          }
          pt = _conv(absoff / 3600, "%02d", pt, ptlim);
          pt = _conv((absoff % 3600) / 60, "%02d", pt, ptlim);

          continue;
        }

        case '+':
          pt = _fmt("%a, %d %b %Y %H:%M:%S %z", t, pt, ptlim);
          continue;

        case '%':
        default:
          break;
      }
    }

    if (pt == ptlim) break;
    *pt++ = *format;
  }

  return pt;
}

static char *_conv(const int n, const char *format, char *pt, const char *ptlim) {
  char  buf[32];

  SNPRINTF(buf, sizeof(buf)-1, format, n);
  return _add(buf, pt, ptlim);
}

static char *_add(const char *str, char *pt, const char *ptlim) {
  while (pt < ptlim && (*pt = *str++) != '\0') ++pt;
  return pt;
}

