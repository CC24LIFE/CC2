extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x <= 0)
    ret = -1;
  else
    ret = 1;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3)
{
  return ((__inlineCall(lib(x)) + __inlineCall(lib(x_copy1))) + __inlineCall(lib(x_copy2))) + __inlineCall(lib(x_copy3));
}

