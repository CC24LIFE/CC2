int lib(int x)
{
  int ret;
  if (x <= 0)
    ret = -1;
  else
    ret = 1;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7)
{
  int ret = x;
  if (x > 0)
  {
    ret = lib(x);
  }

  int ret_copy1 = x_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = lib(x_copy1);
  }

  int ret_copy2 = x_copy2;
  if (x_copy2 > 0)
  {
    ret_copy2 = lib(x_copy2);
  }

  int ret_copy3 = x_copy3;
  if (x_copy3 > 0)
  {
    ret_copy3 = lib(x_copy3);
  }

  int ret_copy4 = x_copy4;
  if (x_copy4 > 0)
  {
    ret_copy4 = lib(x_copy4);
  }

  int ret_copy5 = x_copy5;
  if (x_copy5 > 0)
  {
    ret_copy5 = lib(x_copy5);
  }

  int ret_copy6 = x_copy6;
  if (x_copy6 > 0)
  {
    ret_copy6 = lib(x_copy6);
  }

  int ret_copy7 = x_copy7;
  if (x_copy7 > 0)
  {
    ret_copy7 = lib(x_copy7);
  }

  return ((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7;
}

