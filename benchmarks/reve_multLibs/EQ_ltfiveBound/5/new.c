extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x < 0)
    ret = 0;
  else
    ret = x;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    if (x < 0)
    {
      ret = (-__inlineCall(lib((-x) * 5))) / 5;
    }
    else
    {
      ret = (__inlineCall(lib((x + 1) * 5)) / 5) - 1;
    }

  }

  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    if (x_copy1 < 0)
    {
      ret_copy1 = (-__inlineCall(lib((-x_copy1) * 5))) / 5;
    }
    else
    {
      ret_copy1 = (__inlineCall(lib((x_copy1 + 1) * 5)) / 5) - 1;
    }

  }

  int ret_copy2;
  if ((x_copy2 < (-100)) || (x_copy2 > 100))
  {
    ret_copy2 = x_copy2;
  }
  else
  {
    if (x_copy2 < 0)
    {
      ret_copy2 = (-__inlineCall(lib((-x_copy2) * 5))) / 5;
    }
    else
    {
      ret_copy2 = (__inlineCall(lib((x_copy2 + 1) * 5)) / 5) - 1;
    }

  }

  int ret_copy3;
  if ((x_copy3 < (-100)) || (x_copy3 > 100))
  {
    ret_copy3 = x_copy3;
  }
  else
  {
    if (x_copy3 < 0)
    {
      ret_copy3 = (-__inlineCall(lib((-x_copy3) * 5))) / 5;
    }
    else
    {
      ret_copy3 = (__inlineCall(lib((x_copy3 + 1) * 5)) / 5) - 1;
    }

  }

  int ret_copy4;
  if ((x_copy4 < (-100)) || (x_copy4 > 100))
  {
    ret_copy4 = x_copy4;
  }
  else
  {
    if (x_copy4 < 0)
    {
      ret_copy4 = (-__inlineCall(lib((-x_copy4) * 5))) / 5;
    }
    else
    {
      ret_copy4 = (__inlineCall(lib((x_copy4 + 1) * 5)) / 5) - 1;
    }

  }

  return (((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4;
}

