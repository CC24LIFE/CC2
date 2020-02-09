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

int client(int n, int n_copy1, int n_copy2, int n_copy3)
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

  return (((lib(sum) == 0) + (lib(sum_copy1) == 0)) + (lib(sum_copy2) == 0)) + (lib(sum_copy3) == 0);
}

