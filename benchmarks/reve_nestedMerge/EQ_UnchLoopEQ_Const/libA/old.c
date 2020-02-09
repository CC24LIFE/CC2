extern int __inlineCall(int);

int foo(int a, int b)
{
  int c = a + b;
  return c + 3;
}

int clientmain()
{
  int INLINED_RET_0;
  INLINED_RET_0 = __inlineCall(foo(5, 900));
  return INLINED_RET_0;
}


