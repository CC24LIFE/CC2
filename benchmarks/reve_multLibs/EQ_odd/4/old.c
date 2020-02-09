extern int __inlineCall(int);
int lib(int x)
{
  int counter = 0;
  while ((x % 2) == 0)
  {
    x = x / 2;
    counter++;
  }

  return counter;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3)
{
  int ret;
  if (__inlineCall(lib(x)) == 0)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  int ret_copy1;
  if (__inlineCall(lib(x_copy1)) == 0)
  {
    ret_copy1 = 1;
  }
  else
  {
    ret_copy1 = 0;
  }

  int ret_copy2;
  if (__inlineCall(lib(x_copy2)) == 0)
  {
    ret_copy2 = 1;
  }
  else
  {
    ret_copy2 = 0;
  }

  int ret_copy3;
  if (__inlineCall(lib(x_copy3)) == 0)
  {
    ret_copy3 = 1;
  }
  else
  {
    ret_copy3 = 0;
  }

  return ((ret + ret_copy1) + ret_copy2) + ret_copy3;
}

