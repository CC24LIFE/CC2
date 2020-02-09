int lib(int x, int y)
{
  return x / y;
}

int clientmain(int x, int c_copy1, int d_copy1)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = lib(x, 20);

  int ret_copy1;
  if (d_copy1 == 0)
  {
    ret_copy1 = 0;
  }
  else
  {
    ret_copy1 = lib(c_copy1, d_copy1);
  }

  return ret + ret_copy1;
}

