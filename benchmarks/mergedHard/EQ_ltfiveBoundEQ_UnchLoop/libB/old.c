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
      ret = (-foo((-x) * 5, (-x) * 5)) / 5;
    }
    else
    {
      ret = (foo((x + 1) * 5, (x + 1) * 5) / 5) - 1;
    }

  }

  return ret + foo(5, 900);
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

