int foo(int a, int b);
int clientmain(int x_copy1)
{
  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -foo(-x_copy1, -x_copy1);
  }
  else
  {
    ret_copy1 = foo(x_copy1, x_copy1);
  }

  return foo(5, 900) + ret_copy1;
}

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

