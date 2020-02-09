int foo(int a, int b);
int clientmain(int x)
{
  foo(2, 2);
  return foo(2, 2) + foo(5, 900);
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
}

