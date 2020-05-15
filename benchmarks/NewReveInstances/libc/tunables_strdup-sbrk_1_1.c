/*@ opt -signed @*/
/* glibc */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#define ENOMEM 42
extern int __mark(int);
extern int __set_errno(int);
extern int __libc_brk(void *end_data_segment);

extern void *__curbrk;


static void *sbrk(ptrdiff_t increment) {
    void *oldbrk;

    /* If this is not part of the dynamic library or the library is used
       via dynamic loading in a statically linked program update
       __curbrk from the kernel's brk value.  That way two separate
       instances of __libc_brk and __sbrk can share the heap, returning
       interleaved pieces of it.  */
    if (__curbrk == NULL /*|| __libc_multiple_libcs*/)
        if (__libc_brk(0) < 0) /* Initialize the break.  */
            return (void *)-1;

    if (increment == 0)
        return __curbrk;

    __mark(0);
    oldbrk = __curbrk;
    // moritz: look like overflow prevention, without overflows the
    // first one is never true so we can let it in and it’s still
    // equal to the dietlibc version
    if (increment > 0 &&
        /*?*/ ((uintptr_t)oldbrk + (uintptr_t)increment < (uintptr_t)oldbrk)
        /*: ((uintptr_t)oldbrk < (uintptr_t)-increment)*/) {
        __set_errno(ENOMEM);
        return (void *)-1;
    }

    if (__libc_brk(oldbrk + increment) < 0)
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
