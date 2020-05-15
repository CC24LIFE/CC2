//https://github.com/torvalds/linux/blob/master/lib/string.c#L722


extern int __mark(int);
static int strcmp(const char *p1, const char *p2) {
    const unsigned char *s1 = (const unsigned char *)p1;
    const unsigned char *s2 = (const unsigned char *)p2;
    unsigned char c1, c2;

    do {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while ((c1 == c2) && __mark(42));

    return c1 - c2;
}


#include <linux/types.h>
#include <linux/string.h>
//#include <linux/ctype.h>
#include <linux/kernel.h>
//#include <linux/export.h>
//#include <linux/bug.h>
#include <linux/errno.h>
//#include <linux/slab.h>

//#include <asm/byteorder.h>
//#include <asm/word-at-a-time.h>
//#include <asm/page.h>


/**
 * match_string - matches given string in an array
 * @array:	array of strings
 * @n:		number of strings in the array or -1 for NULL terminated arrays
 * @string:	string to match with
 *
 * This routine will look for a string in an array of strings up to the
 * n-th element in the array or until the first NULL element.
 *
 * Historically the value of -1 for @n, was used to search in arrays that
 * are NULL terminated. However, the function does not make a distinction
 * when finishing the search: either @n elements have been compared OR
 * the first NULL element was found.
 *
 * Return:
 * index of a @string in the @array if matches, or %-EINVAL otherwise.
 */

//CLEVERCLIENTSTART
int match_string(const char * const *array, size_t n, const char *string)
{
	int index;
	const char *item;

	for (index = 0; index < n; index++) {
		item = array[index];
		if (!item)
			break;
		if (!strcmp(item, string))
			return index;
	}

	return -EINVAL;
}
//CLEVERCLIENTEND
