extern int __inlineCall(int);
int foo(int a, int b);
int clientmain(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7, int x_copy8, int x_copy9, int x_copy10, int x_copy11, int x_copy12, int x_copy13, int x_copy14)
{
  int ret = 0;
  if ((x >= 18) && (x < 22))
    ret = __inlineCall(foo(x, 20));

  int ret_copy1 = 0;
  if ((x_copy1 >= 18) && (x_copy1 < 22))
    ret_copy1 = __inlineCall(foo(x_copy1, 20));

  int ret_copy2 = 0;
  if ((x_copy2 >= 18) && (x_copy2 < 22))
    ret_copy2 = __inlineCall(foo(x_copy2, 20));

  int ret_copy3 = 0;
  if ((x_copy3 >= 18) && (x_copy3 < 22))
    ret_copy3 = __inlineCall(foo(x_copy3, 20));

  int ret_copy4 = 0;
  if ((x_copy4 >= 18) && (x_copy4 < 22))
    ret_copy4 = __inlineCall(foo(x_copy4, 20));

  int ret_copy5 = 0;
  if ((x_copy5 >= 18) && (x_copy5 < 22))
    ret_copy5 = __inlineCall(foo(x_copy5, 20));

  int ret_copy6 = 0;
  if ((x_copy6 >= 18) && (x_copy6 < 22))
    ret_copy6 = __inlineCall(foo(x_copy6, 20));

  int ret_copy7 = 0;
  if ((x_copy7 >= 18) && (x_copy7 < 22))
    ret_copy7 = __inlineCall(foo(x_copy7, 20));

  int ret_copy8 = 0;
  if ((x_copy8 >= 18) && (x_copy8 < 22))
    ret_copy8 = __inlineCall(foo(x_copy8, 20));

  int ret_copy9 = 0;
  if ((x_copy9 >= 18) && (x_copy9 < 22))
    ret_copy9 = __inlineCall(foo(x_copy9, 20));

  int ret_copy10 = 0;
  if ((x_copy10 >= 18) && (x_copy10 < 22))
    ret_copy10 = __inlineCall(foo(x_copy10, 20));

  int ret_copy11 = 0;
  if ((x_copy11 >= 18) && (x_copy11 < 22))
    ret_copy11 = __inlineCall(foo(x_copy11, 20));

  int ret_copy12 = 0;
  if ((x_copy12 >= 18) && (x_copy12 < 22))
    ret_copy12 = __inlineCall(foo(x_copy12, 20));

  int ret_copy13 = 0;
  if ((x_copy13 >= 18) && (x_copy13 < 22))
    ret_copy13 = __inlineCall(foo(x_copy13, 20));

  int ret_copy14 = 0;
  if ((x_copy14 >= 18) && (x_copy14 < 22))
    ret_copy14 = __inlineCall(foo(x_copy14, 20));

  return (((((((((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7) + ret_copy8) + ret_copy9) + ret_copy10) + ret_copy11) + ret_copy12) + ret_copy13) + ret_copy14;
}

int foo(int a, int b)
{
  int c = 0;
  for (int i = 1; i <= b; ++i)
    c -= a;

  return c;
}

