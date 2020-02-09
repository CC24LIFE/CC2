int lib(int x)
{
  int counter = 0;
  while ((x % 2) == 0)
  {
    x = x / 2;
    counter++;
  }

  return counter;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11, int x_copy12, int x_copy13, int x_copy14)
{
  int ret;
  if (lib(x) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  int ret_copy1;
  if (lib(x_copy1) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  int ret_copy2;
  if (lib(x_copy2) == 0)
  {
    ret_copy2 = 1;
  }
  else
  {
    ret_copy2 = 0;
  }

  int ret_copy3;
  if (lib(x_copy3) == 0)
  {
    ret_copy3 = 1;
  }
  else
  {
    ret_copy3 = 0;
  }

  int ret_copy4;
  if (lib(x_copy4) == 0)
  {
    ret_copy4 = 1;
  }
  else
  {
    ret_copy4 = 0;
  }

  int ret_copy5;
  if (lib(x_copy5) == 0)
  {
    ret_copy5 = 1;
  }
  else
  {
    ret_copy5 = 0;
  }

  int ret_copy6;
  if (lib(x_copy6) == 0)
  {
    ret_copy6 = 1;
  }
  else
  {
    ret_copy6 = 0;
  }

  int ret_copy7;
  if (lib(x_copy7) == 0)
  {
    ret_copy7 = 1;
  }
  else
  {
    ret_copy7 = 0;
  }

  int ret_copy8;
  if (lib(x_copy8) == 0)
  {
    ret_copy8 = 1;
  }
  else
  {
    ret_copy8 = 0;
  }

  int ret_copy9;
  if (lib(x_copy9) == 0)
  {
    ret_copy9 = 1;
  }
  else
  {
    ret_copy9 = 0;
  }

  int ret_copy10;
  if (lib(x_copy10) == 0)
  {
    ret_copy10 = 1;
  }
  else
  {
    ret_copy10 = 0;
  }

  int ret_copy11;
  if (lib(x_copy11) == 0)
  {
    ret_copy11 = 1;
  }
  else
  {
    ret_copy11 = 0;
  }

  int ret_copy12;
  if (lib(x_copy12) == 0)
  {
    ret_copy12 = 1;
  }
  else
  {
    ret_copy12 = 0;
  }

  int ret_copy13;
  if (lib(x_copy13) == 0)
  {
    ret_copy13 = 1;
  }
  else
  {
    ret_copy13 = 0;
  }

  int ret_copy14;
  if (lib(x_copy14) == 0)
  {
    ret_copy14 = 1;
  }
  else
  {
    ret_copy14 = 0;
  }

  return (((((((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9) + ret_copy10) + ret_copy11) + ret_copy12) + ret_copy13) + ret_copy14;
}

