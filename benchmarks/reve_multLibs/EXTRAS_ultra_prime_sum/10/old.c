extern int __inlineCall(int);
int lib(int a)
{
  int i = 2;
  int count = 0;
  while (i < a)
  {
    if ((a % i) != 0)
    {
      count++;
    }

    i++;
  }

  return count;
}

int client(int n, int n_copy1, int n_copy2, int n_copy3, int n_copy4, int n_copy5, int n_copy6, int n_copy7, int n_copy8, int n_copy9)
{
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    if (__inlineCall(lib(i)) == 0)
    {
      sum += i;
    }

    i++;
  }

  int i_copy1 = 0;
  int sum_copy1 = 0;
  while (i_copy1 <= n_copy1)
  {
    if (__inlineCall(lib(i_copy1)) == 0)
    {
      sum_copy1 += i_copy1;
    }

    i_copy1++;
  }

  int i_copy2 = 0;
  int sum_copy2 = 0;
  while (i_copy2 <= n_copy2)
  {
    if (__inlineCall(lib(i_copy2)) == 0)
    {
      sum_copy2 += i_copy2;
    }

    i_copy2++;
  }

  int i_copy3 = 0;
  int sum_copy3 = 0;
  while (i_copy3 <= n_copy3)
  {
    if (__inlineCall(lib(i_copy3)) == 0)
    {
      sum_copy3 += i_copy3;
    }

    i_copy3++;
  }

  int i_copy4 = 0;
  int sum_copy4 = 0;
  while (i_copy4 <= n_copy4)
  {
    if (__inlineCall(lib(i_copy4)) == 0)
    {
      sum_copy4 += i_copy4;
    }

    i_copy4++;
  }

  int i_copy5 = 0;
  int sum_copy5 = 0;
  while (i_copy5 <= n_copy5)
  {
    if (__inlineCall(lib(i_copy5)) == 0)
    {
      sum_copy5 += i_copy5;
    }

    i_copy5++;
  }

  int i_copy6 = 0;
  int sum_copy6 = 0;
  while (i_copy6 <= n_copy6)
  {
    if (__inlineCall(lib(i_copy6)) == 0)
    {
      sum_copy6 += i_copy6;
    }

    i_copy6++;
  }

  int i_copy7 = 0;
  int sum_copy7 = 0;
  while (i_copy7 <= n_copy7)
  {
    if (__inlineCall(lib(i_copy7)) == 0)
    {
      sum_copy7 += i_copy7;
    }

    i_copy7++;
  }

  int i_copy8 = 0;
  int sum_copy8 = 0;
  while (i_copy8 <= n_copy8)
  {
    if (__inlineCall(lib(i_copy8)) == 0)
    {
      sum_copy8 += i_copy8;
    }

    i_copy8++;
  }

  int i_copy9 = 0;
  int sum_copy9 = 0;
  while (i_copy9 <= n_copy9)
  {
    if (__inlineCall(lib(i_copy9)) == 0)
    {
      sum_copy9 += i_copy9;
    }

    i_copy9++;
  }

  return (((((((((__inlineCall(lib(sum)) == 0) + (__inlineCall(lib(sum_copy1)) == 0)) + (__inlineCall(lib(sum_copy2)) == 0)) + (__inlineCall(lib(sum_copy3)) == 0)) + (__inlineCall(lib(sum_copy4)) == 0)) + (__inlineCall(lib(sum_copy5)) == 0)) + (__inlineCall(lib(sum_copy6)) == 0)) + (__inlineCall(lib(sum_copy7)) == 0)) + (__inlineCall(lib(sum_copy8)) == 0)) + (__inlineCall(lib(sum_copy9)) == 0);
}

