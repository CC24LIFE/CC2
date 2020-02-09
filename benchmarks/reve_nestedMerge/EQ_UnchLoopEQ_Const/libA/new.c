extern int __inlineCall(int);

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

int clientmain()
{
  int INLINED_RET_0;
  INLINED_RET_0 = __inlineCall(foo(5, 900));
  return INLINED_RET_0;
}


