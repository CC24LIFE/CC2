/* openbsd */
#include <stddef.h>

extern int __mark(int);

static int strncmp(const char *s1, const char *s2, size_t n) {

    if (n == 0)
        return (0);
    do {
        if (*s1 != *s2++)
            return (*(unsigned char *)s1 - *(unsigned char *)--s2);
        if (*s1++ == 0)
            break;
    } while (__mark(42) & (--n != 0));
    return (0);
}

///
#include <ctype.h>
#include <fnmatch.h>
#include <string.h>

#define NOTFIRST 128

#define STRUCT_CHARCLASS(c) { #c , is##c }

static struct charclass {
  char * class;
  int (*istype)(int);
} allclasses[] = { 
  STRUCT_CHARCLASS(alnum),
  STRUCT_CHARCLASS(alpha),
  STRUCT_CHARCLASS(blank),
  STRUCT_CHARCLASS(cntrl),
  STRUCT_CHARCLASS(digit),
  STRUCT_CHARCLASS(graph),
  STRUCT_CHARCLASS(lower),
  STRUCT_CHARCLASS(print),
  STRUCT_CHARCLASS(punct),
  STRUCT_CHARCLASS(space),
  STRUCT_CHARCLASS(upper),
  STRUCT_CHARCLASS(xdigit),
};

/* look for "class:]" in pattern */

//CLEVERCLIENTSTART
struct charclass *charclass_lookup(const char *pattern) {
  unsigned int i;

  for (i = 0; i< sizeof(allclasses)/sizeof(*allclasses); i++) {
    int len = strlen(allclasses[i].class);
    if (!strncmp(pattern, allclasses[i].class, len)) {
      pattern += len;
      if (strncmp(pattern, ":]", 2)) goto noclass;
      return &allclasses[i];
    }   
  }
noclass:
  return NULL;
}
//CLEVERCLIENTEND

/////////////////////////////////