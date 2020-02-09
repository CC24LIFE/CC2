extern void __VERIFIER_assume (int);
extern void __VERIFIER_error ();
__attribute__((__noreturn__)) extern void __VERIFIER_error (void);
 #define assert(X) if(!(X)){__VERIFIER_error ();}
 #define assume __VERIFIER_assume
extern int nd();
int main()
{
  int sum = nd();
  client(sum);
}

int client(int sum)
{
  int CLEVER_ret_0_old = 0;
  int CLEVER_ret_0_new = 0;
  {
    CLEVER_ret_0_old = lib_old(sum) == 0;
    CLEVER_ret_0_new = lib_new(sum) == 0;
  }
  assert(CLEVER_ret_0_old == CLEVER_ret_0_new);
}

int lib_old(int a)
{
  if ((((((0 == (0 == (a % 3))) & (0 == (a % 2))) & (0 == (4 < a))) & (2 < a)) & 1) & (3 < a))
  {
    return 1;
  }

  return 99999;
}

int lib_new(int a)
{
  if ((((((0 == (0 == (a % 3))) & (0 == (a % 2))) & (0 == (4 < a))) & (2 < a)) & 1) & (3 < a))
  {
    return 1;
  }

  return 99999;
}

