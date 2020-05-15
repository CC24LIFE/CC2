/* glibc */
#include <stddef.h>
extern int __mark(int);
static char *strchr(const char *s, int c_in) {
    unsigned char c;

    c = (unsigned char)c_in;

    for (;__mark(42);) {
        if (*s == c)
            return (char *)s;
        else if (*s == '\0')
            return NULL;
        if (*++s == c)
            return (char *)s;
        else if (*s == '\0')
            return NULL;
        if (*++s == c)
            return (char *)s;
        else if (*s == '\0')
            return NULL;
        if (*++s == c)
            return (char *)s;
        else if (*s == '\0')
            return NULL;
    }
    return NULL;
}


/*
#include <openssl/asn1.h>

#include <limits.h>
#include <string.h>

#include <openssl/bytestring.h>
#include <openssl/err.h>
#include <openssl/mem.h>

#include "asn1_locl.h"
#include "../bytestring/internal.h"

static int is_printable(uint32_t value);
*/
#include <stdint.h>

/* Return 1 if the character is permitted in a PrintableString */

//CLEVERCLIENTSTART
int is_printable(uint32_t value) //static
{
    int ch;
    if (value > 0x7f)
        return 0;
    ch = (int)value;
    /*
     * Note: we can't use 'isalnum' because certain accented characters may
     * count as alphanumeric in some environments.
     */
    if ((ch >= 'a') && (ch <= 'z'))
        return 1;
    if ((ch >= 'A') && (ch <= 'Z'))
        return 1;
    if ((ch >= '0') && (ch <= '9'))
        return 1;
    if ((ch == ' ') || strchr("'()+,-./:=?", ch))
        return 1;
    return 0;
}
//CLEVERCLIENTEND
