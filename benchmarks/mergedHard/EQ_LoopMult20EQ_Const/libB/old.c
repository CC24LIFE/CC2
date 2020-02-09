int foo(int a, int b);
int clientmain(int x)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = foo(x, 20);

  return ret + foo(5, 900);
}

int foo(int a, int b)
{
  int c = a + b;
  return c + 3;
}

