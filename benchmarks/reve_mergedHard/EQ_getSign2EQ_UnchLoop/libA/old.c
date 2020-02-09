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

int client(int x)
{
  int ret = x;
  if (x > 0)
  {
    ret = __inlineCall(lib(x));
  }

  return ret + __inlineCall(lib(5));
}

