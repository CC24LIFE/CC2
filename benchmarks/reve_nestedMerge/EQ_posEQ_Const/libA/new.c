extern int __inlineCall(int);

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

int client(int x)
{
  int INLINED_RET_0;
  int INLINED_RET_1;
  int ret;
  if (x > 0)
  {
    INLINED_RET_0 = __inlineCall(foo(5, 900));
    ret = -INLINED_RET_0;
  }
  else
  {
    INLINED_RET_1 = __inlineCall(foo(5, 900));
    ret = INLINED_RET_1;
  }

  return ret;
}


