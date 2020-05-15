// # include <stdarg.h>

// /* A substitute for snprintf that is good enough for zdump.  */
// static int ATTRIBUTE_FORMAT((printf, 3, 4))
// my_snprintf(char *s, size_t size, char const *format, ...) 
// {
//   int n;
//   va_list args;
//   char const *arg;
//   size_t arglen, slen;
//   char buf[1024];
//   va_start(args, format);
//   if (strcmp(format, "%s") == 0) { 
//     arg = va_arg(args, char const *);
//     arglen = strlen(arg);
//   } else {
//     n = vsprintf(buf, format, args);
//     if (n < 0) { 
//       va_end(args);
//       return n;
//     }    
//     arg = buf; 
//     arglen = n; 
//   }
//   slen = arglen < size ? arglen : size - 1; 
//   memcpy(s, arg, slen);
//   s[slen] = '\0';
//   n = arglen <= INT_MAX ? arglen : -1;
//   va_end(args);
//   return n;
// }

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
   int i = 0;
   while(__mark(42) & (i < size)) {
      dest[i] = src[i];
      i++;
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


/*#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "dietstdio.h"

struct str_data {
  char* str;
  size_t len;
  size_t size;
};

static int swrite(const void*ptr, size_t nmemb, void* cookie) {
  struct str_data* sd=cookie;
  size_t tmp=sd->size-sd->len;
  if (tmp>0) {
    size_t len=nmemb;
    if (len>tmp) len=tmp;
    if (sd->str) {
      memcpy(sd->str+sd->len,ptr,len);
      sd->str[sd->len+len]=0;
    }   
    sd->len+=len;
  }
  return nmemb;
}

int vsnprintf(char* str, size_t size, const char *format, va_list arg_ptr) {
  int n;
  struct str_data sd = { str, 0, size?size-1:0 };
  struct arg_printf ap = { &sd, swrite };
  n=__v_printf(&ap,format,arg_ptr);
  if (str && size && n>=0) {
    if (size!=(size_t)-1 && ((size_t)n>=size)) str[size-1]=0;
    else str[n]=0;
  }
  return n;
}
*/
