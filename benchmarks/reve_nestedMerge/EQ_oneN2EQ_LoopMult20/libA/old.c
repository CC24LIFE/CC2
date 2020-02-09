extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= b; ++i)
    c += a;

  return c;
}

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  int x_copy0 = x;
  int ret_copy0 = 0;
  if ((x_copy0 >= 18) && (x_copy0 < 22))
  {
    ret_copy0 = __inlineCall(foo(x_copy0, 20));
  }

  INLINED_RET_0 = ret_copy0;
  if (x > INLINED_RET_0)
  {
    ret = x;
  }
  else
  {
    int x_copy1 = x;
    int ret_copy1 = 0;
    if ((x_copy1 >= 18) && (x_copy1 < 22))
    {
      ret_copy1 = __inlineCall(foo(x_copy1, 20));
    }

    INLINED_RET_1 = ret_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


