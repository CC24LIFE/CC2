extern int __mark(int);


static void libmemcpy(int *dest, int *src, int size) {
   int i = 0;
   while(__mark(42) & (i < size)) {
      dest[i] = src[i];
      i++;
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
