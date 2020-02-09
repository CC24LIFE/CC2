extern int __inlineCall(int);
int lib(int x, int b)
{
  int ret = 1;
  int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  if (b == 0)
  {
    ret = 0;
  }
  else
  {
    int done = 0;
    for (int i = 0; i < 8; i++)
    {
      int mod = x % primes[i];
      if ((!done) && (mod == 0))
      {
        ret = 0;
        done = 1;
      }

    }

  }

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11)
{
  int ret;
  int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done = 0;
  for (int i = 0; i < 8; i++)
  {
    if ((!done) && (x == primes[i]))
    {
      ret = 1;
      done = 1;
    }

  }

  if (!done)
    ret = __inlineCall(lib(x, 1));

  int ret_copy1;
  int primes_copy1[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy1 = 0;
  for (int i_copy1 = 0; i_copy1 < 8; i_copy1++)
  {
    if ((!done_copy1) && (x_copy1 == primes_copy1[i_copy1]))
    {
      ret_copy1 = 1;
      done_copy1 = 1;
    }

  }

  if (!done_copy1)
    ret_copy1 = __inlineCall(lib(x_copy1, 1));

  int ret_copy2;
  int primes_copy2[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy2 = 0;
  for (int i_copy2 = 0; i_copy2 < 8; i_copy2++)
  {
    if ((!done_copy2) && (x_copy2 == primes_copy2[i_copy2]))
    {
      ret_copy2 = 1;
      done_copy2 = 1;
    }

  }

  if (!done_copy2)
    ret_copy2 = __inlineCall(lib(x_copy2, 1));

  int ret_copy3;
  int primes_copy3[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy3 = 0;
  for (int i_copy3 = 0; i_copy3 < 8; i_copy3++)
  {
    if ((!done_copy3) && (x_copy3 == primes_copy3[i_copy3]))
    {
      ret_copy3 = 1;
      done_copy3 = 1;
    }

  }

  if (!done_copy3)
    ret_copy3 = __inlineCall(lib(x_copy3, 1));

  int ret_copy4;
  int primes_copy4[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy4 = 0;
  for (int i_copy4 = 0; i_copy4 < 8; i_copy4++)
  {
    if ((!done_copy4) && (x_copy4 == primes_copy4[i_copy4]))
    {
      ret_copy4 = 1;
      done_copy4 = 1;
    }

  }

  if (!done_copy4)
    ret_copy4 = __inlineCall(lib(x_copy4, 1));

  int ret_copy5;
  int primes_copy5[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy5 = 0;
  for (int i_copy5 = 0; i_copy5 < 8; i_copy5++)
  {
    if ((!done_copy5) && (x_copy5 == primes_copy5[i_copy5]))
    {
      ret_copy5 = 1;
      done_copy5 = 1;
    }

  }

  if (!done_copy5)
    ret_copy5 = __inlineCall(lib(x_copy5, 1));

  int ret_copy6;
  int primes_copy6[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy6 = 0;
  for (int i_copy6 = 0; i_copy6 < 8; i_copy6++)
  {
    if ((!done_copy6) && (x_copy6 == primes_copy6[i_copy6]))
    {
      ret_copy6 = 1;
      done_copy6 = 1;
    }

  }

  if (!done_copy6)
    ret_copy6 = __inlineCall(lib(x_copy6, 1));

  int ret_copy7;
  int primes_copy7[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy7 = 0;
  for (int i_copy7 = 0; i_copy7 < 8; i_copy7++)
  {
    if ((!done_copy7) && (x_copy7 == primes_copy7[i_copy7]))
    {
      ret_copy7 = 1;
      done_copy7 = 1;
    }

  }

  if (!done_copy7)
    ret_copy7 = __inlineCall(lib(x_copy7, 1));

  int ret_copy8;
  int primes_copy8[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy8 = 0;
  for (int i_copy8 = 0; i_copy8 < 8; i_copy8++)
  {
    if ((!done_copy8) && (x_copy8 == primes_copy8[i_copy8]))
    {
      ret_copy8 = 1;
      done_copy8 = 1;
    }

  }

  if (!done_copy8)
    ret_copy8 = __inlineCall(lib(x_copy8, 1));

  int ret_copy9;
  int primes_copy9[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy9 = 0;
  for (int i_copy9 = 0; i_copy9 < 8; i_copy9++)
  {
    if ((!done_copy9) && (x_copy9 == primes_copy9[i_copy9]))
    {
      ret_copy9 = 1;
      done_copy9 = 1;
    }

  }

  if (!done_copy9)
    ret_copy9 = __inlineCall(lib(x_copy9, 1));

  int ret_copy10;
  int primes_copy10[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy10 = 0;
  for (int i_copy10 = 0; i_copy10 < 8; i_copy10++)
  {
    if ((!done_copy10) && (x_copy10 == primes_copy10[i_copy10]))
    {
      ret_copy10 = 1;
      done_copy10 = 1;
    }

  }

  if (!done_copy10)
    ret_copy10 = __inlineCall(lib(x_copy10, 1));

  int ret_copy11;
  int primes_copy11[8] = {2, 3, 5, 7, 11, 13, 17, 19};
  int done_copy11 = 0;
  for (int i_copy11 = 0; i_copy11 < 8; i_copy11++)
  {
    if ((!done_copy11) && (x_copy11 == primes_copy11[i_copy11]))
    {
      ret_copy11 = 1;
      done_copy11 = 1;
    }

  }

  if (!done_copy11)
    ret_copy11 = __inlineCall(lib(x_copy11, 1));

  return ((((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9) + ret_copy10) + ret_copy11;
}

