extern int __inlineCall(int);
int lib(int x, int y)
{
  return x / y;
}

int client(int c, int d, int c_copy1, int d_copy1, int c_copy2, int d_copy2, int c_copy3, int d_copy3, int c_copy4, int d_copy4, int c_copy5, int d_copy5, int c_copy6, int d_copy6)
{
  int ret;
  if (d == 0)
  {
    ret = 0;
  }
  else
  {
    ret = __inlineCall(lib(c, d));
  }

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = __inlineCall(lib(c_copy1, d_copy1));
  }

  int ret_copy2;
  if (d_copy2 == 0)
  {
    ret_copy2 = 0;
  }
  else
  {
    ret_copy2 = __inlineCall(lib(c_copy2, d_copy2));
  }

  int ret_copy3;
  if (d_copy3 == 0)
  {
    ret_copy3 = 0;
  }
  else
  {
    ret_copy3 = __inlineCall(lib(c_copy3, d_copy3));
  }

  int ret_copy4;
  if (d_copy4 == 0)
  {
    ret_copy4 = 0;
  }
  else
  {
    ret_copy4 = __inlineCall(lib(c_copy4, d_copy4));
  }

  int ret_copy5;
  if (d_copy5 == 0)
  {
    ret_copy5 = 0;
  }
  else
  {
    ret_copy5 = __inlineCall(lib(c_copy5, d_copy5));
  }

  int ret_copy6;
  if (d_copy6 == 0)
  {
    ret_copy6 = 0;
  }
  else
  {
    ret_copy6 = __inlineCall(lib(c_copy6, d_copy6));
  }

  return (((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6;
}

