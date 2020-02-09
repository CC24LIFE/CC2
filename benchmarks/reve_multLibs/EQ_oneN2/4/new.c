extern int __inlineCall(int);
int lib(int x)
{
  int ret;
  if (x > 11)
    ret = 11;
  else
    ret = x - 1;

  return ret;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3)
{
  int ret;
  if (x > __inlineCall(lib(x)))
    ret = x;
  else
    ret = __inlineCall(lib(x));

  int ret_copy1;
  if (x_copy1 > __inlineCall(lib(x_copy1)))
    ret_copy1 = x_copy1;
  else
    ret_copy1 = __inlineCall(lib(x_copy1));

  int ret_copy2;
  if (x_copy2 > __inlineCall(lib(x_copy2)))
    ret_copy2 = x_copy2;
  else
    ret_copy2 = __inlineCall(lib(x_copy2));

  int ret_copy3;
  if (x_copy3 > __inlineCall(lib(x_copy3)))
    ret_copy3 = x_copy3;
  else
    ret_copy3 = __inlineCall(lib(x_copy3));

  return ((ret + ret_copy1) + ret_copy2) + ret_copy3;
}

