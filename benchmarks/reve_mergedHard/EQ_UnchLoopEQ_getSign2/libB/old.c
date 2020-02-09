extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x == 0)
    ret = 0;
  else
    if (x < 0)
    ret = -1;
  else
    ret = 1;


  return ret;
}

int clientmain(int x_copy1)
{
  int ret_copy1 = x_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  return __inlineCall(lib(5)) + ret_copy1;
}

