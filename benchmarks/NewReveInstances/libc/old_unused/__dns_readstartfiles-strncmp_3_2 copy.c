/* dietlibc */
#include <stddef.h>

extern int __mark(int);
int strncmp(const char *s1, const char *s2, size_t n) {
    register const unsigned char *a = (const unsigned char *)s1;
    register const unsigned char *b = (const unsigned char *)s2;
    register const unsigned char *fini = a + n;
    while (a != fini) {
        register int res = *a - *b;
        if (res)
            return res;
        if (!*a)
            return 0;
        ++a;
        ++b;
        __mark(42);
    }
    return 0;
}

/////////////////////////////////////////////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <resolv.h>
#include <bits/types/res_state.h>
#include <net/if.h>
//#include "dietfeatures.h"

/* the ad-hoc internal API from hell ;-) */
void __dns_make_fd(void);
void __dns_make_fd6(void);
void __dns_readstartfiles(void);
int __dns_decodename(const unsigned char *packet,unsigned int offset,unsigned char *dest,
		     unsigned int maxlen,const unsigned char* behindpacket);

#ifdef WANT_FULL_RESOLV_CONF
unsigned int __dns_search;
char *__dns_domains[8];
#endif

void __dns_readstartfiles(void) {
  int fd;
  char __buf[4096];
  char *buf=__buf;
  int len;
  if (_res.nscount>0) return;
  {
    char *cacheip=getenv("DNSCACHEIP");
#ifdef WANT_FULL_RESOLV_CONF
    __dns_search=0;
#endif
    if (cacheip)
      if (parsesockaddr(cacheip,_res.nsaddr_list))
	++_res.nscount;
  }
  _res.options=RES_RECURSE;
  if ((fd=open("/etc/resolv.conf",O_RDONLY))<0) return;
  len=read(fd,buf,4096);
  close(fd);
  {
    char *last=buf+len;
    for (; buf<last;) {
      if (!strncmp(buf,"nameserver",10)) {
	buf+=10;
	while (buf<last && *buf!='\n') {
	  while (buf<last && isblank(*buf)) ++buf;
	  {
	    char *tmp=buf;
	    struct sockaddr_in i;
	    char save;
	    while (buf<last && !isspace(*buf)) ++buf;
	    if (buf>=last) break;
	    save=*buf;
	    *buf=0;
	    if (parsesockaddr(tmp,&_res.nsaddr_list[_res.nscount]))
	      if (_res.nscount<MAXNS) ++_res.nscount;
	    *buf=save;
	  }
	}
      }
#ifdef WANT_FULL_RESOLV_CONF
      else if ((!strncmp(buf,"search",6) || !strncmp(buf,"domain",6)) &&
	       (__dns_search < sizeof(__dns_domains)/sizeof(__dns_domains[0]))) {
	buf+=6;
	while (buf<last && *buf!='\n') {
	  char save;
	  while (buf<last && (*buf==',' || isblank(*buf))) ++buf;
	  __dns_domains[__dns_search]=buf;
	  while (buf<last && (*buf=='.' || *buf=='-' || isalnum(*buf))) ++buf;
	  save=*buf;
	  if (buf<last) *buf=0;
	  if (__dns_domains[__dns_search]<buf &&
	      (__dns_domains[__dns_search]=strdup(__dns_domains[__dns_search])))
	    ++__dns_search;
	  if (buf<last) *buf=save;
	}
	continue;
      }
#endif
      while (buf<last && *buf!='\n') ++buf;
      while (buf<last && *buf=='\n') ++buf;
    }
  }
}
