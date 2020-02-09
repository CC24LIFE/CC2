int foo(int a, int b)
{
  int c = a + b;
  return c;
}

int clientmain(int x)
{
  int INLINED_RET_0;
  int ret = 0;
  if ((x >= 18) && (x < 22))
  {
    INLINED_RET_0 = foo(5, 900);
    ret = INLINED_RET_0;
  }

  return ret;
}


