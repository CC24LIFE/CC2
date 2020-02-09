int lib(int x)
{
  int ret;
  if (x > 10)
    ret = 11;
  else
    ret = x;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    if (x > lib(x))
      ret = x;
    else
      ret = lib(x);

  }

  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    if (x_copy1 > lib(x_copy1))
      ret_copy1 = x_copy1;
    else
      ret_copy1 = lib(x_copy1);

  }

  int ret_copy2;
  if ((x_copy2 < (-100)) || (x_copy2 > 100))
  {
    ret_copy2 = x_copy2;
  }
  else
  {
    if (x_copy2 > lib(x_copy2))
      ret_copy2 = x_copy2;
    else
      ret_copy2 = lib(x_copy2);

  }

  int ret_copy3;
  if ((x_copy3 < (-100)) || (x_copy3 > 100))
  {
    ret_copy3 = x_copy3;
  }
  else
  {
    if (x_copy3 > lib(x_copy3))
      ret_copy3 = x_copy3;
    else
      ret_copy3 = lib(x_copy3);

  }

  int ret_copy4;
  if ((x_copy4 < (-100)) || (x_copy4 > 100))
  {
    ret_copy4 = x_copy4;
  }
  else
  {
    if (x_copy4 > lib(x_copy4))
      ret_copy4 = x_copy4;
    else
      ret_copy4 = lib(x_copy4);

  }

  int ret_copy5;
  if ((x_copy5 < (-100)) || (x_copy5 > 100))
  {
    ret_copy5 = x_copy5;
  }
  else
  {
    if (x_copy5 > lib(x_copy5))
      ret_copy5 = x_copy5;
    else
      ret_copy5 = lib(x_copy5);

  }

  return ((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5;
}

