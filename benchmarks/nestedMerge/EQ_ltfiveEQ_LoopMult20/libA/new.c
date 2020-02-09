int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
}

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  if (x < 0)
  {
    int x_copy0 = (-x) * 5;
    int ret_copy0 = 0;
    if ((x_copy0 >= 18) && (x_copy0 < 22))
    {
      ret_copy0 = foo(x_copy0, 20);
    }

    INLINED_RET_0 = ret_copy0;
    ret = (-INLINED_RET_0) / 5;
  }
  else
  {
    int x_copy1 = (x + 1) * 5;
    int ret_copy1 = 0;
    if ((x_copy1 >= 18) && (x_copy1 < 22))
    {
      ret_copy1 = foo(x_copy1, 20);
    }

    INLINED_RET_1 = ret_copy1;
    ret = (INLINED_RET_1 / 5) - 1;
  }

  return ret;
}


