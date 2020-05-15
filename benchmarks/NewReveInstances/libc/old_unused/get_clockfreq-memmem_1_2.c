// dietlibc
#include <stddef.h>
extern int __mark(int);
extern int memcmp (const void *, const void *, unsigned long);
void *memmem(const void* haystack, size_t hl, const void* needle, size_t nl) {
  int i;
  if (nl>hl) return 0;
  for (i=hl-nl+1; __mark(42) & i; --i) {
    if (!memcmp(haystack,needle,nl))
      return (char*)haystack;
    ++haystack;
  }
  return 0;
}


#define _GNU_SOURCE	1
//#include <argp.h>
//#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>

#ifndef MAX_THREADS
# define MAX_THREADS		100000
#endif
#ifndef DEFAULT_THREADS
# define DEFAULT_THREADS	50
#endif


#define OPT_TO_THREAD		300
#define OPT_TO_PROCESS		301
#define OPT_SYNC_SIGNAL		302
#define OPT_SYNC_JOIN		303
#define OPT_TOPLEVEL		304


/*static const struct argp_option options[] =
  {
    { NULL, 0, NULL, 0, "\
This is a test for threads so we allow ther user to selection the number of \
threads which are used at any one time.  Independently the total number of \
rounds can be selected.  This is the total number of threads which will have \
run when the process terminates:" },
    { "threads", 't', "NUMBER", 0, "Number of threads used at once" },
    { "starts", 's', "NUMBER", 0, "Total number of working threads" },
    { "toplevel", OPT_TOPLEVEL, "NUMBER", 0,
      "Number of toplevel threads which start the other threads; this \
implies --sync-join" },

    { NULL, 0, NULL, 0, "\
Each thread can do one of two things: sleep or do work.  The latter is 100% \
CPU bound.  The work load is the probability a thread does work.  All values \
from zero to 100 (inclusive) are valid.  How often each thread repeats this \
can be determined by the number of rounds.  The work cost determines how long \
each work session (not sleeping) takes.  If it is zero a thread would \
effectively nothing.  By setting the number of rounds to zero the thread \
does no work at all and pure thread creation times can be measured." },
    { "workload", 'w', "PERCENT", 0, "Percentage of time spent working" },
    { "workcost", 'c', "NUMBER", 0,
      "Factor in the cost of each round of working" },
    { "rounds", 'r', "NUMBER", 0, "Number of rounds each thread runs" },

    { NULL, 0, NULL, 0, "\
There are a number of different methods how thread creation can be \
synchronized.  Synchronization is necessary since the number of concurrently \
running threads is limited." },
    { "sync-signal", OPT_SYNC_SIGNAL, NULL, 0,
      "Synchronize using a signal (default)" },
    { "sync-join", OPT_SYNC_JOIN, NULL, 0, "Synchronize using pthread_join" },

    { NULL, 0, NULL, 0, "\
One parameter for each threads execution is the size of the stack.  If this \
parameter is not used the system's default stack size is used.  If many \
threads are used the stack size should be chosen quite small." },
    { "stacksize", 'S', "BYTES", 0, "Size of threads stack" },
    { "guardsize", 'g', "BYTES", 0,
      "Size of stack guard area; must fit into the stack" },

    { NULL, 0, NULL, 0, "Signal options:" },
    { "to-thread", OPT_TO_THREAD, NULL, 0, "Send signal to main thread" },
    { "to-process", OPT_TO_PROCESS, NULL, 0,
      "Send signal to process (default)" },

    { NULL, 0, NULL, 0, "Administrative options:" },
    { "progress", 'p', NULL, 0, "Show signs of progress" },
    { "timing", 'T', NULL, 0,
      "Measure time from startup to the last thread finishing" },
    { NULL, 0, NULL, 0, NULL }
  };  */


/* We use 64bit values for the times.  */
typedef unsigned long long int hp_timing_t;

//CLEVERCLIENTSTART
hp_timing_t
get_clockfreq ()
{
  /* We read the information from the /proc filesystem.  It contains at
     least one line like
	cpu MHz         : 497.840237
     or also
	cpu MHz         : 497.841
     We search for this line and convert the number in an integer.  */
  static hp_timing_t result;
  int fd;

  /* If this function was called before, we know the result.  */
  if (result != 0)
    return result;

  fd = open ("/proc/cpuinfo", O_RDONLY);
  if (__glibc_likely (fd != -1))
    {
      /* XXX AFAIK the /proc filesystem can generate "files" only up
         to a size of 4096 bytes.  */
      char buf[4096];
      ssize_t n;

      n = read (fd, buf, sizeof buf);
      if (__builtin_expect (n, 1) > 0)
	{
	  char *mhz = memmem (buf, n, "cpu MHz", 7);

	  if (__glibc_likely (mhz != NULL))
	    {
	      char *endp = buf + n;
	      int seen_decpoint = 0;
	      int ndigits = 0;

	      /* Search for the beginning of the string.  */
	      while (mhz < endp && (*mhz < '0' || *mhz > '9') && *mhz != '\n')
		++mhz;

	      while (mhz < endp && *mhz != '\n')
		{
		  if (*mhz >= '0' && *mhz <= '9')
		    {
		      result *= 10;
		      result += *mhz - '0';
		      if (seen_decpoint)
			++ndigits;
		    }
		  else if (*mhz == '.')
		    seen_decpoint = 1;

		  ++mhz;
		}

	      /* Compensate for missing digits at the end.  */
	      while (ndigits++ < 6)
		result *= 10;
	    }
	}

      close (fd);
    }

  return result;
}
//CLEVERCLIENTEND
