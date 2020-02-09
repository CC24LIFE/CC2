int foo(int a, int b)
{
  int c = b + a;
  return c;
}

int clientmain()
{
  int INLINED_RET_0;
  INLINED_RET_0 = foo(5, 900);
  return INLINED_RET_0;
}


