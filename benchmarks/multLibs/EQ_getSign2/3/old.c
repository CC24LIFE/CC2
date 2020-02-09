int lib(int x)
{
  int ret;
  if (x == 0)
    ret = 0;
  else
    if (x < 0)
    ret = -1;
  else
    ret = 1;


  return ret;
}

int client(int x, int x_copy1, int x_copy2)
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

  return (ret + ret_copy1) + ret_copy2;
}

