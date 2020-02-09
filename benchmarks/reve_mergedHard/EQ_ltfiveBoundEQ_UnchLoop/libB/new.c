extern int __inlineCall(int);
int foo(int a, int b);
int client(int x)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    if (x < 0)
    {
      ret = (-__inlineCall(foo((-x) * 5, (-x) * 5))) / 5;
    }
    else
    {
      ret = (__inlineCall(foo((x + 1) * 5, (x + 1) * 5)) / 5) - 1;
    }

  }

  return ret + __inlineCall(foo(5, 900));
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

