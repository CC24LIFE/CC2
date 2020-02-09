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
  int ret;
  INLINED_RET_0 = __inlineCall(foo(5, 900));
  if (INLINED_RET_0 == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  return ret;
}


