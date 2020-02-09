extern int __inlineCall(int);
int lib(int x)
{
  return x % 5;
}

int client(int x, int x_copy1)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    x = (x * 5) * 6;
    if (__inlineCall(lib(x)) == 0)
    {
      ret = 1;
    }
    else
    {
      ret = 0;
    }

  }

  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    x_copy1 = (x_copy1 * 5) * 6;
    if (__inlineCall(lib(x_copy1)) == 0)
    {
      ret_copy1 = 1;
    }
    else
    {
      ret_copy1 = 0;
    }

  }

  return ret + ret_copy1;
}

