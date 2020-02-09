int foo(int a, int b);
int clientmain()
{
  return (((((((((((foo(5, 900) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900)) + foo(5, 900);
}

int foo(int a, int b)
{
  const int d = 3;
  int c = b + a;
  return c + d;
}

