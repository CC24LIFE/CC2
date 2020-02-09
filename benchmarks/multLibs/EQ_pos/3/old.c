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

int client(int x, int x_copy1, int x_copy2)
{
  int ret;
  if (x > 0)
  {
    ret = -lib(-x);
  }
  else
  {
    ret = lib(x);
  }

  int ret_copy1;
  if (x_copy1 > 0)
  {
    ret_copy1 = -lib(-x_copy1);
  }
  else
  {
    ret_copy1 = lib(x_copy1);
  }

  int ret_copy2;
  if (x_copy2 > 0)
  {
    ret_copy2 = -lib(-x_copy2);
  }
  else
  {
    ret_copy2 = lib(x_copy2);
  }

  return (ret + ret_copy1) + ret_copy2;
}

