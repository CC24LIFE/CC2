extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x < 0)
  {
    ret = -x;
  }
  else
  {
    ret = x;
  }

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9)
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

  int ret_copy7;
  if (x_copy7 > 0)
  {
    ret_copy7 = -__inlineCall(lib(-x_copy7));
  }
  else
  {
    ret_copy7 = __inlineCall(lib(x_copy7));
  }

  int ret_copy8;
  if (x_copy8 > 0)
  {
    ret_copy8 = -__inlineCall(lib(-x_copy8));
  }
  else
  {
    ret_copy8 = __inlineCall(lib(x_copy8));
  }

  int ret_copy9;
  if (x_copy9 > 0)
  {
    ret_copy9 = -__inlineCall(lib(-x_copy9));
  }
  else
  {
    ret_copy9 = __inlineCall(lib(x_copy9));
  }

  return ((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9;
}

