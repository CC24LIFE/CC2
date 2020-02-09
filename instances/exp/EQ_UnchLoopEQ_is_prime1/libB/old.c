int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
int lib(unsigned int x, int b)
{
  if (b == 0)
  {
    return 0;
  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      int mod = x % primes[i];
      if (mod == 0)
        return 0;

    }

  }

  return 1;
}

int clientmain(unsigned int x_copy1)
{
  return lib(5, 900) + lib(x_copy1, 0);
}

int main()
{
  unsigned int x;
  return client(x);
}

