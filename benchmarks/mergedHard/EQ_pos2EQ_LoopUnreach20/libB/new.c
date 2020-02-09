int foo(int a, int b);
int client(int x, int x_copy1)
{
  int ret;
  if (x > 0)
  {
    ret = -foo(-x, -x);
  }
  else
  {
    ret = foo(x, x);
  }

  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
    ret_copy1 = foo(x_copy1, 20);

  return ret + ret_copy1;
}

int foo(int a, int b)
{
  int c = 0;
  if (a < 0)
  {
    for (int i = 1; i <= a; ++i)
      c += b;

  }

  return c;
}

