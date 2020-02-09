int foo(int a, int b);
int clientmain(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = foo(x, 20);

  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
    ret_copy1 = foo(x_copy1, 20);

  int ret_copy2 = 0;
  if ((x_copy2 >= 18) && (x_copy2 < 22))
    ret_copy2 = foo(x_copy2, 20);

  int ret_copy3 = 0;
  if ((x_copy3 >= 18) && (x_copy3 < 22))
    ret_copy3 = foo(x_copy3, 20);

  int ret_copy4 = 0;
  if ((x_copy4 >= 18) && (x_copy4 < 22))
    ret_copy4 = foo(x_copy4, 20);

  return (((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4;
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= b; ++i)
    c -= a;

  return c;
}

