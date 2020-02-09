int lib(int x)
{
  if (x > 10)
    return 12;
  else
    return x + 1;

}

int client(int x, int x_copy1)
{
  int ret = 0;
  if (x > lib(x))
    ret = x;
  else
    ret = lib(x);

  int ret_copy1 = 0;
  if (x_copy1 > lib(x_copy1))
    ret_copy1 = x_copy1;
  else
    ret_copy1 = lib(x_copy1);

  return ret_copy1;
}

int main()
{
  int x;
  return client(x);
}

