int lib(int x)
{
  int ret;
  if (x > 10)
    ret = 12;
  else
    ret = x + 1;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11, int x_copy12, int x_copy13, int x_copy14)
{
  int ret;
  if (x > lib(x))
    ret = x;
  else
    ret = lib(x);

  int ret_copy1;
  if (x_copy1 > lib(x_copy1))
    ret_copy1 = x_copy1;
  else
    ret_copy1 = lib(x_copy1);

  int ret_copy2;
  if (x_copy2 > lib(x_copy2))
    ret_copy2 = x_copy2;
  else
    ret_copy2 = lib(x_copy2);

  int ret_copy3;
  if (x_copy3 > lib(x_copy3))
    ret_copy3 = x_copy3;
  else
    ret_copy3 = lib(x_copy3);

  int ret_copy4;
  if (x_copy4 > lib(x_copy4))
    ret_copy4 = x_copy4;
  else
    ret_copy4 = lib(x_copy4);

  int ret_copy5;
  if (x_copy5 > lib(x_copy5))
    ret_copy5 = x_copy5;
  else
    ret_copy5 = lib(x_copy5);

  int ret_copy6;
  if (x_copy6 > lib(x_copy6))
    ret_copy6 = x_copy6;
  else
    ret_copy6 = lib(x_copy6);

  int ret_copy7;
  if (x_copy7 > lib(x_copy7))
    ret_copy7 = x_copy7;
  else
    ret_copy7 = lib(x_copy7);

  int ret_copy8;
  if (x_copy8 > lib(x_copy8))
    ret_copy8 = x_copy8;
  else
    ret_copy8 = lib(x_copy8);

  int ret_copy9;
  if (x_copy9 > lib(x_copy9))
    ret_copy9 = x_copy9;
  else
    ret_copy9 = lib(x_copy9);

  int ret_copy10;
  if (x_copy10 > lib(x_copy10))
    ret_copy10 = x_copy10;
  else
    ret_copy10 = lib(x_copy10);

  int ret_copy11;
  if (x_copy11 > lib(x_copy11))
    ret_copy11 = x_copy11;
  else
    ret_copy11 = lib(x_copy11);

  int ret_copy12;
  if (x_copy12 > lib(x_copy12))
    ret_copy12 = x_copy12;
  else
    ret_copy12 = lib(x_copy12);

  int ret_copy13;
  if (x_copy13 > lib(x_copy13))
    ret_copy13 = x_copy13;
  else
    ret_copy13 = lib(x_copy13);

  int ret_copy14;
  if (x_copy14 > lib(x_copy14))
    ret_copy14 = x_copy14;
  else
    ret_copy14 = lib(x_copy14);

  return (((((((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9) + ret_copy10) + ret_copy11) + ret_copy12) + ret_copy13) + ret_copy14;
}

