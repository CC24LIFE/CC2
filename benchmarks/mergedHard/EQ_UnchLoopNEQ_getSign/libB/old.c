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

int clientmain(int x_copy1)
{
  return lib(5) + lib(x_copy1);
}

