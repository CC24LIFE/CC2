extern int __mark(int);

static void libmemcpy(int *dest, int *src, int size) {
   src--;
   dest--;

   while(__mark(42) & (size > 0)) {
      dest++;
      src++;
      *dest = *src;
      size--;
   }
}

#include <sys/types.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern int strnlen(const char*, size_t);

//CLEVERCLIENTSTART
char *
strndup(const char *str, size_t maxlen)
{
        char *copy;
        size_t len;

        len = strnlen(str, maxlen);
        copy = malloc(len + 1); 
        if (copy != NULL) {
                (void)libmemcpy(copy, str, len);
                copy[len] = '\0';
        }

        return copy;
}
//CLEVERCLIENTEND
