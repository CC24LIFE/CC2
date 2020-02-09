extern int __inlineCall(int);
int lib(int x)
{
  return x % 6;
}

int client(int x)
{
  int ret;
  x = (x * 5) * 6;
  if (__inlineCall(lib(x)) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  return ret;
}

