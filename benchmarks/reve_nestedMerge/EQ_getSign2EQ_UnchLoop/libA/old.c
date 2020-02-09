extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret = x;
  if (x > 0)
  {
    INLINED_RET_0 = __inlineCall(foo(5, 900));
    ret = INLINED_RET_0;
  }

  return ret;
}


