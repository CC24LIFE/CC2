int foo(int a, int b)
{
  int c = 1;
  for (int i = 0; i < a; ++i)
  {
    c = c + b;
  }

  return c;
}

int clientmain()
{
  int INLINED_RET_0;
  INLINED_RET_0 = foo(5, 900);
  return INLINED_RET_0;
}


