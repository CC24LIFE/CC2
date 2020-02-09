extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x, int x_copy1, int x_copy2)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = __inlineCall(foo(x, 20));

  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
    ret_copy1 = __inlineCall(foo(x_copy1, 20));

  int ret_copy2 = 0;
  if ((x_copy2 >= 18) && (x_copy2 < 22))
    ret_copy2 = __inlineCall(foo(x_copy2, 20));

  return (ret + ret_copy1) + ret_copy2;
}

int foo(int a, int b)
{
  int c = 0;
  if (a < 0)
  {
    for (int i = 1; i <= a; ++i)
      c += b;

  }

  return c;
}

