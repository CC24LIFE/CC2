extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x_copy1)
{
  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
    ret_copy1 = __inlineCall(foo(x_copy1, 20));

  return __inlineCall(foo(5, 900)) + ret_copy1;
}

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

