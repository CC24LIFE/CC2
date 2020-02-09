int foo(int a, int b);
int clientmain()
{
  return (foo(5, 900) + foo(5, 900)) + foo(5, 900);
}

int foo(int a, int b)
{
  int c = a + b;
  return c + 3;
}

