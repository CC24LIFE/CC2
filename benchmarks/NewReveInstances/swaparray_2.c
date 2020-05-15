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

/*@ rel_in (and (= a$1 a$2) (= b$1 b$2) (= n$1 n$2) (forall ((i Int)) (= (select HEAP$1 i) (select HEAP$2 i))) (> a$1 (+ b$1 n$1))) @*/
extern int __mark(int);

void swap(int *a, int *b, int n) {
   int *start = a;
   while(__mark(42) & (a-start < n)) {
      *a = *a+*b;
      *b = *a-*b;
      *a = *a-*b;
      a++;
      b++;
   }
}
