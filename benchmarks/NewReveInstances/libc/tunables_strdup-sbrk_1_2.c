/* dietlibc */
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
extern int __mark(int);
extern int __libc_brk(void *end_data_segment);

extern void *__curbrk;


static void *sbrk(ptrdiff_t increment) {
    void *oldbrk;
    if (__curbrk == 0)
        if (__libc_brk(0) < 0)
            return (void *)-1;
    if (increment == 0)
        return __curbrk;
    __mark(0);
    oldbrk = __curbrk;
    if (__libc_brk((char *)oldbrk + increment) < 0)
        return (void *)-1;
    return oldbrk;
}


////////////////////////////////////////////////////////////////
//#include <startup.h>
//#include <stdint.h>
#include <stdbool.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <sysdep.h>
#include <fcntl.h>
//#include <ldsodefs.h>

//#include "dl-tunables.h"
//#include <not-errno.h>
extern void _dl_fatal_printf(const char*);

//CLEVERCLIENTSTART
char *
tunables_strdup (const char *in)
{
  size_t i = 0;

  while (in[i++] != '\0');
  char *out = sbrk (i);

  /* For most of the tunables code, we ignore user errors.  However,
     this is a system error - and running out of memory at program
     startup should be reported, so we do.  */
  if (out == (void *)-1)
    _dl_fatal_printf ("sbrk() failure while processing tunables\n");

  i--;

  while (i-- > 0)
    out[i] = in[i];

  return out;
}
//CLEVERCLIENTEND

////////////////////////////////////////////////////////////////
