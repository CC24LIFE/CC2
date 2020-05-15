#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef int Item;

#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t = A; A = B; B = t;}

void sort(Item a[], int l, int r)
{
  int i, j;

  for (i = l; i < r; i++)
    {
      int min = i;
      int valmin = findmin(&a[j], r-i+1); //quite modified here
      for (j = i+1; j <= r; j++) 
         if (a[j] == valmin)
            min = j;
      exch(a[i], a[min]);
    }
}


extern int __mark(int);

int findmin(int *a, int n) {

   int i = 1;
   int min = 0;
   int result;

   while(__mark(42) & (i < n)) {
      if(a[i] <= a[min]) {
         min = i;
      }
      i++;
   }

   result = a[min];
   return result;
}
