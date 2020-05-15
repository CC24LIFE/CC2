//https://github.com/caisah/Sedgewick-algorithms-in-c-exercises-and-examples/blob/master/07-quicksort/7.01-the_basic_algorithm/examples/prog_7.1-7.2-quicksort.c#L11
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
//#define exch(A, B) {Item t = A; A = B; B = t;}

int partition(Item a[], int l, int r)
{
  int i = l-1, j = r;
  Item v = a[r];

  for (;;)
    {
      while (less(a[++i], v));
      while (less(v, a[--j]))
	if (j == l)
	  break;
      if (i >= j)
	break;
      swap(&a[i], &a[j], 1);
    }
  swap(&a[i], &a[j], 1);
  return i;
}

extern int __mark(int);
void swap(int *a, int *b, int n) {
    int i = 0;
    int t;
    while (__mark(42) & (i < n)) {
        t = a[i];
        a[i] = b[i];
        b[i] = t;
        i++;
    }
}
