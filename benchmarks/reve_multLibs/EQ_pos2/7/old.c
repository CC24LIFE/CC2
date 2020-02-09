extern int __inlineCall(int);
int lib(int x)
{
  int counter = 0;
  while (x < 0)
  {
    x++;
    counter++;
  }

  return counter;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6)
{
  int ret;
  if (x > 0)
  {
    ret = -__inlineCall(lib(-x));
  }
  else
  {
    ret = __inlineCall(lib(x));
  }

  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -__inlineCall(lib(-x_copy1));
  }
  else
  {
    ret_copy1 = __inlineCall(lib(x_copy1));
  }

  int ret_copy2;
  if (x_copy2 > 0)
  {
    ret_copy2 = -__inlineCall(lib(-x_copy2));
  }
  else
  {
    ret_copy2 = __inlineCall(lib(x_copy2));
  }

  int ret_copy3;
  if (x_copy3 > 0)
  {
    ret_copy3 = -__inlineCall(lib(-x_copy3));
  }
  else
  {
    ret_copy3 = __inlineCall(lib(x_copy3));
  }

  int ret_copy4;
  if (x_copy4 > 0)
  {
    ret_copy4 = -__inlineCall(lib(-x_copy4));
  }
  else
  {
    ret_copy4 = __inlineCall(lib(x_copy4));
  }

  int ret_copy5;
  if (x_copy5 > 0)
  {
    ret_copy5 = -__inlineCall(lib(-x_copy5));
  }
  else
  {
    ret_copy5 = __inlineCall(lib(x_copy5));
  }

  int ret_copy6;
  if (x_copy6 > 0)
  {
    ret_copy6 = -__inlineCall(lib(-x_copy6));
  }
  else
  {
    ret_copy6 = __inlineCall(lib(x_copy6));
  }

  return (((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6;
}

