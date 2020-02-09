int lib(int x)
{
  int ret;
  if (x < 5)
    ret = 5;
  else
    ret = x;

  return ret;
}

int client(int x)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    if (x < 0)
    {
      ret = (-lib((-x) * 5)) / 5;
    }
    else
    {
      ret = (lib((x + 1) * 5) / 5) - 1;
    }

  }

  return ret;
}

