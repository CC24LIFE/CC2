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
  return (lib(x) + lib(x_copy1)) + lib(x_copy2);
}

