int lib(int x)
{
  int ret;
  if (x <= 0)
    ret = -1;
  else
    ret = 1;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11, int x_copy12)
{
  return (((((((((((lib(x) + lib(x_copy1)) + lib(x_copy2)) + lib(x_copy3)) + lib(x_copy4)) + lib(x_copy5)) + lib(x_copy6)) + lib(x_copy7)) + lib(x_copy8)) + lib(x_copy9)) + lib(x_copy10)) + lib(x_copy11)) + lib(x_copy12);
}

