#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include "dietstdio.h"

struct str_data {
  char* str;
  size_t len;
  size_t size;
};


extern int __mark(int);

static int libmemcpy(int *dest, int *src, int size) {
   int *start = src;
   while(__mark(42) & (src - start < size)) {
      *dest = *src;
      dest++;
      src++;
   }
   return 1;
}

//CLEVERCLIENTSTART
int swrite(const void*ptr, size_t nmemb, void* cookie) {
  struct str_data* sd=cookie;
  size_t tmp=sd->size-sd->len;
  if (tmp>0) {
    size_t len=nmemb;
    if (len>tmp) len=tmp;
    if (sd->str) {
      libmemcpy(sd->str+sd->len,ptr,len);
      sd->str[sd->len+len]=0;
    }   
    sd->len+=len;
  }
  return nmemb;
}
//CLEVERCLIENTEND


