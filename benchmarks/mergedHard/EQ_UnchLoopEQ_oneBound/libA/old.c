int foo(int a, int b);
int clientmain(int x_copy1)
{
  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    if (x_copy1 > foo(x_copy1, x_copy1))
      ret_copy1 = x_copy1;
    else
      ret_copy1 = foo(x_copy1, x_copy1);

  }

  return foo(5, 900) + ret_copy1;
}

int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

