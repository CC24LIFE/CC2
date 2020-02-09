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

int client(int x, int x_copy1)
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

  int ret_copy1;
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  return ret + ret_copy1;
}

