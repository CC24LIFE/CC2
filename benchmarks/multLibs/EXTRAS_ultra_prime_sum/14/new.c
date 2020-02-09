int lib(int a)
{
  int i = 2;
  int count = 0;
  while (i < a)
  {
    if ((a % i) != 0)
    {
      count = 1;
    }

    i++;
  }

  return count;
}

int client(int n, int n_copy1, int n_copy2, int n_copy3, int n_copy4, int n_copy5, int n_copy6, int n_copy7, int n_copy8, int n_copy9, int n_copy10, int n_copy11, int n_copy12, int n_copy13)
{
  int i = 0;
  int sum = 0;
  while (i <= n)
  {
    if (lib(i) == 0)
    {
      sum += i;
    }

    i++;
  }

  int i_copy1 = 0;
  int sum_copy1 = 0;
  while (i_copy1 <= n_copy1)
  {
    if (lib(i_copy1) == 0)
    {
      sum_copy1 += i_copy1;
    }

    i_copy1++;
  }

  int i_copy2 = 0;
  int sum_copy2 = 0;
  while (i_copy2 <= n_copy2)
  {
    if (lib(i_copy2) == 0)
    {
      sum_copy2 += i_copy2;
    }

    i_copy2++;
  }

  int i_copy3 = 0;
  int sum_copy3 = 0;
  while (i_copy3 <= n_copy3)
  {
    if (lib(i_copy3) == 0)
    {
      sum_copy3 += i_copy3;
    }

    i_copy3++;
  }

  int i_copy4 = 0;
  int sum_copy4 = 0;
  while (i_copy4 <= n_copy4)
  {
    if (lib(i_copy4) == 0)
    {
      sum_copy4 += i_copy4;
    }

    i_copy4++;
  }

  int i_copy5 = 0;
  int sum_copy5 = 0;
  while (i_copy5 <= n_copy5)
  {
    if (lib(i_copy5) == 0)
    {
      sum_copy5 += i_copy5;
    }

    i_copy5++;
  }

  int i_copy6 = 0;
  int sum_copy6 = 0;
  while (i_copy6 <= n_copy6)
  {
    if (lib(i_copy6) == 0)
    {
      sum_copy6 += i_copy6;
    }

    i_copy6++;
  }

  int i_copy7 = 0;
  int sum_copy7 = 0;
  while (i_copy7 <= n_copy7)
  {
    if (lib(i_copy7) == 0)
    {
      sum_copy7 += i_copy7;
    }

    i_copy7++;
  }

  int i_copy8 = 0;
  int sum_copy8 = 0;
  while (i_copy8 <= n_copy8)
  {
    if (lib(i_copy8) == 0)
    {
      sum_copy8 += i_copy8;
    }

    i_copy8++;
  }

  int i_copy9 = 0;
  int sum_copy9 = 0;
  while (i_copy9 <= n_copy9)
  {
    if (lib(i_copy9) == 0)
    {
      sum_copy9 += i_copy9;
    }

    i_copy9++;
  }

  int i_copy10 = 0;
  int sum_copy10 = 0;
  while (i_copy10 <= n_copy10)
  {
    if (lib(i_copy10) == 0)
    {
      sum_copy10 += i_copy10;
    }

    i_copy10++;
  }

  int i_copy11 = 0;
  int sum_copy11 = 0;
  while (i_copy11 <= n_copy11)
  {
    if (lib(i_copy11) == 0)
    {
      sum_copy11 += i_copy11;
    }

    i_copy11++;
  }

  int i_copy12 = 0;
  int sum_copy12 = 0;
  while (i_copy12 <= n_copy12)
  {
    if (lib(i_copy12) == 0)
    {
      sum_copy12 += i_copy12;
    }

    i_copy12++;
  }

  int i_copy13 = 0;
  int sum_copy13 = 0;
  while (i_copy13 <= n_copy13)
  {
    if (lib(i_copy13) == 0)
    {
      sum_copy13 += i_copy13;
    }

    i_copy13++;
  }

  return (((((((((((((lib(sum) == 0) + (lib(sum_copy1) == 0)) + (lib(sum_copy2) == 0)) + (lib(sum_copy3) == 0)) + (lib(sum_copy4) == 0)) + (lib(sum_copy5) == 0)) + (lib(sum_copy6) == 0)) + (lib(sum_copy7) == 0)) + (lib(sum_copy8) == 0)) + (lib(sum_copy9) == 0)) + (lib(sum_copy10) == 0)) + (lib(sum_copy11) == 0)) + (lib(sum_copy12) == 0)) + (lib(sum_copy13) == 0);
}

