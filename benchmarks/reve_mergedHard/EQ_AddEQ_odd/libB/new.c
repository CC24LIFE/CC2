extern int __inlineCall(int);
int lib(int x)
{
  return (x + 1) % 2;
}

int clientmain(int x_copy1)
{
  int ret_copy1;
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  return __inlineCall(lib(5)) + ret_copy1;
}

