extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x_copy1)
{
  return __inlineCall(foo(5, 900)) + __inlineCall(foo(x_copy1, x_copy1));
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

