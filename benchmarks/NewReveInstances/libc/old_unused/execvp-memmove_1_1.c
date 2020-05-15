// openbsd
#include <stddef.h>
extern int __mark(int);
void *memmove(void *dst0, const void *src0, size_t length) {
    char *dst = dst0;
    const char *src = src0;
    size_t t;

    if (length == 0 || dst == src) /* nothing to do */
        goto done;

    if ((unsigned long)dst < (unsigned long)src) {
        t = length;
        if (t) {
            do {
                *dst++ = *src++;
            } while (__mark(0) & (--t));
        }
    } else {
        src += length;
        dst += length;
        t = length;
        if (t) {
            do {
                *--dst = *--src;
            } while (__mark(1) & (--t));
        }
    }
done:
    return (dst0);
}


// //////////////////////////////////////////////////////
// //https://github.com/openbsd/src/blob/master/lib/libc/regex/regcomp.c
// #include <sys/types.h>
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <limits.h>
// #include <stdlib.h>
// #include <regex.h>

// /#include "utils.h"
// #include "regex2.h"

// #include "cclass.h"
// #include "cname.h"

// /*
//  * parse structure, passed up and down to avoid global variables and
//  * other clumsinesses
//  */
// struct parse {
// 	char *next;		/* next character in RE */
// 	char *end;		/* end of string (-> NUL normally) */
// 	int error;		/* has an error been seen? */
// 	sop *strip;		/* malloced strip */
// 	sopno ssize;		/* malloced strip size (allocated) */
// 	sopno slen;		/* malloced strip length (used) */
// 	int ncsalloc;		/* number of csets allocated */
// 	struct re_guts *g;
// #	define	NPAREN	10	/* we need to remember () 1-9 for back refs */
// 	sopno pbegin[NPAREN];	/* -> ( ([0] unused) */
// 	sopno pend[NPAREN];	/* -> ) ([0] unused) */
// };

// static void p_ere(struct parse *, int);
// static void p_ere_exp(struct parse *);
// static void p_str(struct parse *);
// static void p_bre(struct parse *, int, int);
// static int p_simp_re(struct parse *, int);
// static int p_count(struct parse *);
// static void p_bracket(struct parse *);
// static void p_b_term(struct parse *, cset *);
// static void p_b_cclass(struct parse *, cset *);
// static void p_b_eclass(struct parse *, cset *);
// static char p_b_symbol(struct parse *);
// static char p_b_coll_elem(struct parse *, int);
// static char othercase(int);
// static void bothcases(struct parse *, int);
// static void ordinary(struct parse *, int);
// static void backslash(struct parse *, int);
// static void nonnewline(struct parse *);
// static void repeat(struct parse *, sopno, int, int);
// static int seterr(struct parse *, int);
// static cset *allocset(struct parse *);
// static void freeset(struct parse *, cset *);
// static int freezeset(struct parse *, cset *);
// static int firstch(struct parse *, cset *);
// static int nch(struct parse *, cset *);
// static void mcadd(struct parse *, cset *, char *);
// static void mcinvert(struct parse *, cset *);
// static void mccase(struct parse *, cset *);
// static int isinsets(struct re_guts *, int);
// static int samesets(struct re_guts *, int, int);
// static void categorize(struct parse *, struct re_guts *);
// static sopno dupl(struct parse *, sopno, sopno);
// static void doemit(struct parse *, sop, size_t);
// static void doinsert(struct parse *, sop, size_t, sopno);
// static void dofwd(struct parse *, sopno, sop);
// static int enlarge(struct parse *, sopno);
// static void stripsnug(struct parse *, struct re_guts *);
// static void findmust(struct parse *, struct re_guts *);
// static sopno pluscount(struct parse *, struct re_guts *);

// static char nuls[10];		/* place to point scanner in event of error */

// /*
//  * macros for use with parse structure
//  * BEWARE:  these know that the parse structure is named `p' !!!
//  */
// #define	PEEK()	(*p->next)
// #define	PEEK2()	(*(p->next+1))
// #define	MORE()	(p->next < p->end)
// #define	MORE2()	(p->next+1 < p->end)
// #define	SEE(c)	(MORE() && PEEK() == (c))
// #define	SEETWO(a, b)	(MORE() && MORE2() && PEEK() == (a) && PEEK2() == (b))
// #define	EAT(c)	((SEE(c)) ? (NEXT(), 1) : 0)
// #define	EATTWO(a, b)	((SEETWO(a, b)) ? (NEXT2(), 1) : 0)
// #define	NEXT()	(p->next++)
// #define	NEXT2()	(p->next += 2)
// #define	NEXTn(n)	(p->next += (n))
// #define	GETNEXT()	(*p->next++)
// #define	SETERROR(e)	seterr(p, (e))
// #define	REQUIRE(co, e)	(void) ((co) || SETERROR(e))
// #define	EMIT(op, sopnd)	doemit(p, (sop)(op), (size_t)(sopnd))
// #define	INSERT(op, pos)	doinsert(p, (sop)(op), HERE()-(pos)+1, pos)
// #define	AHEAD(pos)		dofwd(p, pos, HERE()-(pos))
// #define	ASTERN(sop, pos)	EMIT(sop, HERE()-pos)
// #define	HERE()		(p->slen)
// #define	THERE()		(p->slen - 1)
// #define	THERETHERE()	(p->slen - 2)
// #define	DROP(n)	(p->slen -= (n))

// #ifndef NDEBUG
// static int never = 0;		/* for use in asserts; shuts lint up */
// #else
// #define	never	0		/* some <assert.h>s have bugs too */
// #endif

// /*
//  - doinsert - insert a sop into the strip
//  */
// void
// doinsert(struct parse *p, sop op, size_t opnd, sopno pos)
// {
// 	sopno sn;
// 	sop s;
// 	int i;

// 	/* avoid making error situations worse */
// 	if (p->error != 0)
// 		return;

// 	sn = HERE();
// 	EMIT(op, opnd);		/* do checks, ensure space */
// 	assert(HERE() == sn+1);
// 	s = p->strip[sn];

// 	/* adjust paren pointers */
// 	assert(pos > 0);
// 	for (i = 1; i < NPAREN; i++) {
// 		if (p->pbegin[i] >= pos) {
// 			p->pbegin[i]++;
// 		}
// 		if (p->pend[i] >= pos) {
// 			p->pend[i]++;
// 		}
// 	}

// 	memmove((char *)&p->strip[pos+1], (char *)&p->strip[pos],
// 						(HERE()-pos-1)*sizeof(sop));
// 	p->strip[pos] = s;
// }



#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
//#include "exec_lib.h"
//#include "dietfeatures.h"
#include <paths.h>

#include <linux/limits.h>

extern int __exec_shell(const char *file, char *const argv[]);

//CLEVERCLIENTSTART
int execvp(const char *file, char *const argv[]) {
  const char *path=getenv("PATH");
  char *cur,*next;
  char buf[PATH_MAX];
  if (strchr((char*)file,'/')) {
    if (execve(file,argv,__environ)==-1) { //modified: __environ
      if (errno==ENOEXEC)
	__exec_shell(file,argv);
      return -1;
    }
  }
  if (!path) path=_PATH_DEFPATH;
  for (cur=(char*)path; cur; cur=next) {
    next=strchr(cur,':');
    if (!next)
      next=cur+strlen(cur);
    if (next==cur) {
      buf[0]='.';
      cur--;
    } else {
      if (next-cur>=PATH_MAX-3) { error: errno=EINVAL; return -1; }
      memmove(buf,cur,(size_t)(next-cur));
    }
    buf[next-cur]='/';
    {
      int len=strlen(file);
      if (len+(next-cur)>=PATH_MAX-2) goto error;
      memmove(&buf[next-cur+1],file,strlen(file)+1);
    }
    if (execve(buf,argv,__environ)==-1) {  //modified: __environ
      if (errno==ENOEXEC)
	return __exec_shell(buf,argv);
      if ((errno!=EACCES) && (errno!=ENOENT) && (errno!=ENOTDIR)) return -1;
    }
    if (*next==0) break;
    next++;
  }
  return -1;
}
//CLEVERCLIENTEND