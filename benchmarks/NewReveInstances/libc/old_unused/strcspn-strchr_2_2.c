/* openbsd strchr */
//#include <string.h>

/*__weak_alias(index, strchr);
__attribute__((always_inline))

char *
strchr(const char *p, int ch)
{
	for (;; ++p) {
		if (*p == (char) ch)
			return((char *)p);
		if (!*p)
			return((char *)NULL);
	}
	// NOTREACHED 
}
DEF_STRONG(strchr);*/ //ORIGINAL

/* glibc */
/*@ rel_in
   (and
      (= s$1 s$2)
      (= reject$1 reject$2)
      (> reject$1 0)
      (forall
         ((i Int))
         (= (select HEAP$1 i) (select HEAP$2 i))))
@*/
#include <stddef.h>
extern int __mark(int);

static char *strchr(const char *s, int c_in) { //register const char *t
    register char ch;

    ch = c_in;
    for (;__mark(42);) {
        if (*s == ch)
            break;
        if (!*s)
            return 0;
        ++s;
        if (*s == ch)
            break;
        if (!*s)
            return 0;
        ++s;
        if (*s == ch)
            break;
        if (!*s)
            return 0;
        ++s;
    }
    return (char *)s;
}

//CLEVERCLIENTSTART
size_t strcspn(const char *s, const char *reject) {
    size_t count = 0;

    while ((*s)) {
        char ch = *s++;
        if (strchr(reject, ch) == NULL) {
            ++count;
        } else {
            return count;
        }
    }

    return count;
}
//CLEVERCLIENTEND
