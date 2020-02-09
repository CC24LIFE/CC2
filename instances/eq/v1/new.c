int lib(int x)
{
  return (x + 1) % 2;
}

int client(int x, unsigned int x_copy1)
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

  return ret + lib(x_copy1);
}

int main()
{
  int x;
  return client(x);
}

