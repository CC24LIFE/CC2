int foo(int a, int b);
int clientmain()
{
  return (((((((((((foo(5, 900) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900);
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

