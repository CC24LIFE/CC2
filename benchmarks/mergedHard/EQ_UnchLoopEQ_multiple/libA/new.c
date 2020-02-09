int foo(int a, int b);
int clientmain(int x_copy1)
{
  int ret_copy1;
  x_copy1 = (x_copy1 * 5) * 6;
  if (foo(x_copy1, x_copy1) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  return foo(5, 900) + ret_copy1;
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c + 1;
}

