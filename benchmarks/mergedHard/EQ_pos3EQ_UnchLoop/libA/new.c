int lib(int x)
{
  int ret = x;
  if (x < 0)
  {
    ret = -x;
  }

  return ret;
}

int client(int x)
{
  int ret = -x;
  if (x < 0)
  {
    ret = lib(x);
  }

  return ret + lib(5);
}

