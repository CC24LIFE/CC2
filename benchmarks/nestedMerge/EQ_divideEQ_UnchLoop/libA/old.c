int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

int client(int c, int d)
{
  int INLINED_RET_0;
  int ret;
  if (d == 0)
  {
    ret = 0;
  }
  else
  {
    INLINED_RET_0 = foo(5, 900);
    ret = INLINED_RET_0;
  }

  return ret;
}


