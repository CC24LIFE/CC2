extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x < 0)
    ret = 0;
  else
    ret = x;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11, int x_copy12, int x_copy13, int x_copy14)
{
  int ret;
  if (x < 0)
  {
    ret = (-__inlineCall(lib((-x) * 5))) / 5;
  }
  else
  {
    ret = (__inlineCall(lib((x + 1) * 5)) / 5) - 1;
  }

  int ret_copy1;
  if (x_copy1 < 0)
  {
    ret_copy1 = (-__inlineCall(lib((-x_copy1) * 5))) / 5;
  }
  else
  {
    ret_copy1 = (__inlineCall(lib((x_copy1 + 1) * 5)) / 5) - 1;
  }

  int ret_copy2;
  if (x_copy2 < 0)
  {
    ret_copy2 = (-__inlineCall(lib((-x_copy2) * 5))) / 5;
  }
  else
  {
    ret_copy2 = (__inlineCall(lib((x_copy2 + 1) * 5)) / 5) - 1;
  }

  int ret_copy3;
  if (x_copy3 < 0)
  {
    ret_copy3 = (-__inlineCall(lib((-x_copy3) * 5))) / 5;
  }
  else
  {
    ret_copy3 = (__inlineCall(lib((x_copy3 + 1) * 5)) / 5) - 1;
  }

  int ret_copy4;
  if (x_copy4 < 0)
  {
    ret_copy4 = (-__inlineCall(lib((-x_copy4) * 5))) / 5;
  }
  else
  {
    ret_copy4 = (__inlineCall(lib((x_copy4 + 1) * 5)) / 5) - 1;
  }

  int ret_copy5;
  if (x_copy5 < 0)
  {
    ret_copy5 = (-__inlineCall(lib((-x_copy5) * 5))) / 5;
  }
  else
  {
    ret_copy5 = (__inlineCall(lib((x_copy5 + 1) * 5)) / 5) - 1;
  }

  int ret_copy6;
  if (x_copy6 < 0)
  {
    ret_copy6 = (-__inlineCall(lib((-x_copy6) * 5))) / 5;
  }
  else
  {
    ret_copy6 = (__inlineCall(lib((x_copy6 + 1) * 5)) / 5) - 1;
  }

  int ret_copy7;
  if (x_copy7 < 0)
  {
    ret_copy7 = (-__inlineCall(lib((-x_copy7) * 5))) / 5;
  }
  else
  {
    ret_copy7 = (__inlineCall(lib((x_copy7 + 1) * 5)) / 5) - 1;
  }

  int ret_copy8;
  if (x_copy8 < 0)
  {
    ret_copy8 = (-__inlineCall(lib((-x_copy8) * 5))) / 5;
  }
  else
  {
    ret_copy8 = (__inlineCall(lib((x_copy8 + 1) * 5)) / 5) - 1;
  }

  int ret_copy9;
  if (x_copy9 < 0)
  {
    ret_copy9 = (-__inlineCall(lib((-x_copy9) * 5))) / 5;
  }
  else
  {
    ret_copy9 = (__inlineCall(lib((x_copy9 + 1) * 5)) / 5) - 1;
  }

  int ret_copy10;
  if (x_copy10 < 0)
  {
    ret_copy10 = (-__inlineCall(lib((-x_copy10) * 5))) / 5;
  }
  else
  {
    ret_copy10 = (__inlineCall(lib((x_copy10 + 1) * 5)) / 5) - 1;
  }

  int ret_copy11;
  if (x_copy11 < 0)
  {
    ret_copy11 = (-__inlineCall(lib((-x_copy11) * 5))) / 5;
  }
  else
  {
    ret_copy11 = (__inlineCall(lib((x_copy11 + 1) * 5)) / 5) - 1;
  }

  int ret_copy12;
  if (x_copy12 < 0)
  {
    ret_copy12 = (-__inlineCall(lib((-x_copy12) * 5))) / 5;
  }
  else
  {
    ret_copy12 = (__inlineCall(lib((x_copy12 + 1) * 5)) / 5) - 1;
  }

  int ret_copy13;
  if (x_copy13 < 0)
  {
    ret_copy13 = (-__inlineCall(lib((-x_copy13) * 5))) / 5;
  }
  else
  {
    ret_copy13 = (__inlineCall(lib((x_copy13 + 1) * 5)) / 5) - 1;
  }

  int ret_copy14;
  if (x_copy14 < 0)
  {
    ret_copy14 = (-__inlineCall(lib((-x_copy14) * 5))) / 5;
  }
  else
  {
    ret_copy14 = (__inlineCall(lib((x_copy14 + 1) * 5)) / 5) - 1;
  }

  return (((((((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9) + ret_copy10) + ret_copy11) + ret_copy12) + ret_copy13) + ret_copy14;
}

