extern int __inlineCall(int);
int lib(int x, int y)
{
  return x / y;
}

int clientmain(int c_copy1, int d_copy1)
{
  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1, d_copy1));
  }

  return __inlineCall(lib(5, 900)) + ret_copy1;
}

