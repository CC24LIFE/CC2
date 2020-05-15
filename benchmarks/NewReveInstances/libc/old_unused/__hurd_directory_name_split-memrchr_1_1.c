/* openbsd */
#include <stddef.h>

extern int __mark(int);
void *memrchr(const void *s, int c, size_t n) {
    const unsigned char *cp;

    if (n != 0) {
        cp = (unsigned char *)s + n;
        do {
            if (*(--cp) == (unsigned char)c)
                return ((void *)cp);
        } while (__mark(0) & (--n != 0));
    }
    return (NULL);
}


#include "hurd.h"
#include "hurd/lookup.h"
#include <string.h>
#include <fcntl.h>


/* This is the same as hurd_file_name_split, except that it ignores
   trailing slashes (so *NAME is never "").  */
error_t
__hurd_directory_name_split (error_t (*use_init_port)
			     (int which, error_t (*operate) (file_t)),
			     file_t (*get_dtable_port) (int fd),
			     error_t (*lookup)
			     (file_t dir, const char *name, int flags, mode_t mode,
			      retry_type *do_retry, string_t retry_name,
			      mach_port_t *result),
			     const char *file_name,
			     file_t *dir, char **name)
{
  error_t addref (file_t crdir)
    {
      *dir = crdir;
      return __mach_port_mod_refs (__mach_task_self (),
				   crdir, MACH_PORT_RIGHT_SEND, +1);
    }

  const char *lastslash = strrchr (file_name, '/');

  if (lastslash != NULL && lastslash[1] == '\0')
    {
      /* Trailing slash doesn't count.  Look back further.  */

      /* Back up over all trailing slashes.  */
      while (lastslash > file_name && *lastslash == '/')
	--lastslash;

      /* Find the last one earlier in the string, before the trailing ones.  */
      lastslash = memrchr (file_name, '/', lastslash - file_name);
    }

  if (lastslash != NULL)
    {
      if (lastslash == file_name)
	{
	  /* "/foobar" => crdir + "foobar".  */
	  *name = (char *) file_name + 1;
	  return (*use_init_port) (INIT_PORT_CRDIR, &addref);
	}
      else
	{
	  /* "/dir1/dir2/.../file".  */
	  char dirname[lastslash - file_name + 1];
	  memcpy (dirname, file_name, lastslash - file_name);
	  dirname[lastslash - file_name] = '\0';
	  *name = (char *) lastslash + 1;
	  return
	    __hurd_file_name_lookup (use_init_port, get_dtable_port, lookup,
				     dirname, 0, 0, dir);
	}
    }
  else if (file_name[0] == '\0')
    return ENOENT;
  else
    {
      /* "foobar" => cwdir + "foobar".  */
      *name = (char *) file_name;
      return (*use_init_port) (INIT_PORT_CWDIR, &addref);
    }
}
