int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
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


