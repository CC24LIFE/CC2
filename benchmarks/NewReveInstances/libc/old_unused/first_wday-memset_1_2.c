/* dietlibc */
#include <stddef.h>

extern int __mark(int);
void* memset(void * dst, int c, size_t n) {
    register char * a = dst;
    n++;	/* this actually creates smaller code than using count-- */
    while (--n) {
        *a++ = c;
        __mark(0);
    }
    return dst;
}

/////////////////////////////
/* Copyright (C) 2002-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */


// #include <string.h>
// #include "pthreadP.h"


// int
// __pthread_mutexattr_init (pthread_mutexattr_t *attr)
// {
//   ASSERT_TYPE_SIZE (pthread_mutexattr_t, __SIZEOF_PTHREAD_MUTEXATTR_T);
//   ASSERT_PTHREAD_INTERNAL_SIZE (pthread_mutexattr_t,
// 				struct pthread_mutexattr);

//   if (sizeof (struct pthread_mutexattr) != sizeof (pthread_mutexattr_t))
//     memset (attr, '\0', sizeof (*attr));

//   /* We use bit 31 to signal whether the mutex is going to be
//      process-shared or not.  By default it is zero, i.e., the mutex is
//      not process-shared.  */
//   ((struct pthread_mutexattr *) attr)->mutexkind = PTHREAD_MUTEX_NORMAL;

//   return 0;
// }

/* Convert a string representation of time to a time value.
   Copyright (C) 1997-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Mark Kettenis <kettenis@phys.uva.nl>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <limits.h>
#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <alloca.h>

#define TM_YEAR_BASE 1900


/* Prototypes for local functions.  */
int first_wday (int year, int mon, int wday);
static int check_mday (int year, int mon, int mday);

/* Set to one of the following values to indicate an error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allication failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification Example: February 31 or a time is
        specified that can not be represented in a time_t (representing
        the time in seconds since 00:00:00 UTC, January 1, 1970) */
int getdate_err;


/* Returns the first weekday WDAY of month MON in the year YEAR.  */

//CLEVERCLIENTSTART
int
first_wday (int year, int mon, int wday)
{
  struct tm tm;

  if (wday == INT_MIN)
    return 1;

  memset (&tm, 0, sizeof (struct tm));
  tm.tm_year = year;
  tm.tm_mon = mon;
  tm.tm_mday = 1;
  mktime (&tm);

  return (1 + (wday - tm.tm_wday + 7) % 7);
}
//CLEVERCLIENTEND


///////////////////////////////////////////////
