extern int __inlineCall(int);
int lib(int x)
{
  return x % 5;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8)
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

  int ret_copy1;
  x_copy1 = (x_copy1 * 5) * 6;
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  int ret_copy2;
  x_copy2 = (x_copy2 * 5) * 6;
  if (__inlineCall(lib(x_copy2)) == 0)
  {
    ret_copy2 = 1;
  }
  else
  {
    ret_copy2 = 0;
  }

  int ret_copy3;
  x_copy3 = (x_copy3 * 5) * 6;
  if (__inlineCall(lib(x_copy3)) == 0)
  {
    ret_copy3 = 1;
  }
  else
  {
    ret_copy3 = 0;
  }

  int ret_copy4;
  x_copy4 = (x_copy4 * 5) * 6;
  if (__inlineCall(lib(x_copy4)) == 0)
  {
    ret_copy4 = 1;
  }
  else
  {
    ret_copy4 = 0;
  }

  int ret_copy5;
  x_copy5 = (x_copy5 * 5) * 6;
  if (__inlineCall(lib(x_copy5)) == 0)
  {
    ret_copy5 = 1;
  }
  else
  {
    ret_copy5 = 0;
  }

  int ret_copy6;
  x_copy6 = (x_copy6 * 5) * 6;
  if (__inlineCall(lib(x_copy6)) == 0)
  {
    ret_copy6 = 1;
  }
  else
  {
    ret_copy6 = 0;
  }

  int ret_copy7;
  x_copy7 = (x_copy7 * 5) * 6;
  if (__inlineCall(lib(x_copy7)) == 0)
  {
    ret_copy7 = 1;
  }
  else
  {
    ret_copy7 = 0;
  }

  int ret_copy8;
  x_copy8 = (x_copy8 * 5) * 6;
  if (__inlineCall(lib(x_copy8)) == 0)
  {
    ret_copy8 = 1;
  }
  else
  {
    ret_copy8 = 0;
  }

  return (((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8;
}

