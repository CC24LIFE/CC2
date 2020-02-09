extern int __inlineCall(int);
int foo(int a, int b);
int clientmain()
{
  return ((((((((((((__inlineCall(foo(5, 900)) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900))) + __inlineCall(foo(5, 900));
}

int foo(int a, int b)
{
  int c = b + a;
  return c;
}

