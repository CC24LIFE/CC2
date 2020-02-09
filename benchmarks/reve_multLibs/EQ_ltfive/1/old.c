extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x < 5)
    ret = 5;
  else
    ret = x;

  return ret;
}

int client(int x)
{
  int ret;
  if (x < 0)
  {
    ret = (-__inlineCall(lib((-x) * 5))) / 5;
  }
  else
  {
    ret = (__inlineCall(lib((x + 1) * 5)) / 5) - 1;
  }

  return ret;
}

