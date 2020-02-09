int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= a; ++i)
    c += b;

  return c;
}

int client(int x)
{
  int INLINED_RET_0;
  int x_copy0 = x;
  int ret_copy0 = 0;
  if ((x_copy0 >= 18) && (x_copy0 < 22))
  {
    ret_copy0 = foo(x_copy0, 20);
  }

  INLINED_RET_0 = ret_copy0;
  return INLINED_RET_0;
}


