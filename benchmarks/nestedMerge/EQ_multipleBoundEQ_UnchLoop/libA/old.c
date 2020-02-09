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
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    x = (x * 5) * 6;
    INLINED_RET_0 = foo(5, 900);
    if (INLINED_RET_0 == 0)
    {
      ret = 1;
    }
    else
    {
      ret = 0;
    }

  }

  return ret;
}


