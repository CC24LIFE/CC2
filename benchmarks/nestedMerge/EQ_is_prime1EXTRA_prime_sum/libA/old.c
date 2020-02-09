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

int client(int x)
{
  int INLINED_RET_0;
  int n_copy0 = x;
  int i_copy0 = 0;
  int sum_copy0 = 0;
  while (i_copy0 <= n_copy0)
  {
    if (lib(i_copy0) == 0)
    {
      sum_copy0 += i_copy0;
    }

    i_copy0++;
  }

  INLINED_RET_0 = sum_copy0;
  return INLINED_RET_0;
}


