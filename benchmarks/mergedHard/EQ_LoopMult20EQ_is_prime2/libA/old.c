int foo(int a, int b);
int clientmain(int x, int x_copy1)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = foo(x, 20);

  int ret_copy1;
  if (x_copy1 < 19)
  {
    ret_copy1 = foo(20, 1);
  }
  else
  {
    ret_copy1 = foo(x_copy1, 1);
  }

  return ret + ret_copy1;
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= b; ++i)
    c += a;

  return c;
}

