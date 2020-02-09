int client(int x, int x_copy1)
{
  lib(x);
  return lib(x_copy1);
}

int lib(int x)
{
  if (x == 0)
    return 0;

  if (x < 0)
    return -1;
  else
    return 1;

}



int main()
{
  int x;
  return client(x);
}

