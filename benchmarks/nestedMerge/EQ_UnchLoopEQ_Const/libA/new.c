int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

int clientmain()
{
  int INLINED_RET_0;
  INLINED_RET_0 = foo(5, 900);
  return INLINED_RET_0;
}


