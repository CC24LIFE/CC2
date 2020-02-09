extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = 0;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c + 1;
}

int client(int x)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int ret;
  if (x < 0)
  {
    INLINED_RET_0 = __inlineCall(foo(5, 900));
    ret = (-INLINED_RET_0) / 5;
  }
  else
  {
    INLINED_RET_1 = __inlineCall(foo(5, 900));
    ret = (INLINED_RET_1 / 5) - 1;
  }

  return ret;
}


