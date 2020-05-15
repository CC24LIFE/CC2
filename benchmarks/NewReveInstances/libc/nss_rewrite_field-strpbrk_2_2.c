/* dietlibc */
extern int __mark(int);
static char *strpbrk(const char *s, const char *accept) {
    register unsigned int i;
    for (; __mark(0) & (*s); s++)
        for (i = 0; __mark(1) & accept[i]; i++)
            if (*s == accept[i])
                return (char *)s;
    return 0;
}

//#include <nss.h>
#include <string.h>
# define NSS_INVALID_FIELD_CHARACTERS ":\n"
const char nss_invalid_field_characters[] = NSS_INVALID_FIELD_CHARACTERS;
//extern const char nss_invalid_field_characters[] attribute_hidden;
extern char * strdup (const char *s); 


/* Rewrite VALUE to a valid field value in the NSS database.  Invalid
   characters are replaced with a single space character ' '.  If
   VALUE is NULL, the empty string is returned.  *TO_BE_FREED is
   overwritten with a pointer the caller has to free if the function
   returns successfully.  On failure, return NULL.  */

//CLEVERCLIENTSTART
const char *
nss_rewrite_field (const char *value, char **to_be_freed)
{
  *to_be_freed = NULL;
  if (value == NULL)
    return "";

  /* Search for non-allowed characters.  */
  const char *p = strpbrk (value, nss_invalid_field_characters);
  if (p == NULL)
    return value;
  *to_be_freed = strdup (value);
  if (*to_be_freed == NULL)
    return NULL;

  /* Switch pointer to freshly-allocated buffer.  */
  char *bad = *to_be_freed + (p - value);
  do
    {
      *bad = ' ';
      bad = strpbrk (bad + 1, nss_invalid_field_characters);
    }
  while (bad != NULL);

  return *to_be_freed;
}
//CLEVERCLIENTEND