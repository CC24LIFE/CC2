extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x, int c_copy1, int d_copy1)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = __inlineCall(foo(x, 20));

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(foo(c_copy1, d_copy1));
  }

  return ret + ret_copy1;
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
}

