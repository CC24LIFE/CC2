int lib(int x)
{
  int ret;
  if (x < 5)
    ret = 5;
  else
    ret = x;

  return ret;
}

int client(int x, int x_copy1, int x_copy2)
{
  int ret;
  if (x < 0)
  {
    ret = (-lib((-x) * 5)) / 5;
  }
  else
  {
    ret = (lib((x + 1) * 5) / 5) - 1;
  }

  int ret_copy1;
  if (x_copy1 < 0)
  {
    ret_copy1 = (-lib((-x_copy1) * 5)) / 5;
  }
  else
  {
    ret_copy1 = (lib((x_copy1 + 1) * 5) / 5) - 1;
  }

  int ret_copy2;
  if (x_copy2 < 0)
  {
    ret_copy2 = (-lib((-x_copy2) * 5)) / 5;
  }
  else
  {
    ret_copy2 = (lib((x_copy2 + 1) * 5) / 5) - 1;
  }

  return (ret + ret_copy1) + ret_copy2;
}

