int foo(int a, int b);

int clientmain(int x, int x_1)

{

  int ret = 0;

  if ((x >= 13) && (x < 16))

    ret = foo(x, 15);



  ret;

  int ret_1 = 0;

  if ((x_1 >= 13) && (x_1 < 16))

    ret_1 = foo(x_1, 15);



  return ret_1;

}



int foo(int a, int b)

{

  int c = 0;

  for (int i = 1; i <= b; ++i)

    c -= a;



  return c;

}