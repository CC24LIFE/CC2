int lib(int *a, int n) {

   int i = 1;
   int maxv = a[0];
   int result;
   while((i < n)) {
      if(a[i] >= maxv) {
         maxv = a[i];
      }
      i++;
   }
   i++;
   result = maxv;
   return result;
}


int client(int x){
    int a[1000];
    for (int i =0; i < 1000; i++){
        a[i] = i;
    }

    if (x <= 1000)
        return lib(&a, x);
    else
        return 0;
}