int foo(int a, int b)
{
  int c = a + b;
  return c + 3;
}

int client(int x)
{
  int INLINED_RET_0;
  int ret;
  INLINED_RET_0 = foo(5, 900);
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


