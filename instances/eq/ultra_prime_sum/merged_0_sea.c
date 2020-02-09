extern void __VERIFIER_assume (int);
extern void __VERIFIER_error ();
__attribute__((__noreturn__)) extern void __VERIFIER_error (void);
 #define assert(X) if(!(X)){__VERIFIER_error ();}
 #define assume __VERIFIER_assume
extern int nd();
int main()
{
  int a = nd();
  lib(a);
}

int lib(int a)
{
  int i__CLEVER_EXT;
  int sum;
  int n__CLEVER_EXT;
  if (!((i__CLEVER_EXT <= n__CLEVER_EXT) & (a == i__CLEVER_EXT)))
    return 0;

  if (0 == (2 < a))
    return 0;

  if ((((((((((((((((((((((((((0 == (a % 7)) & (9 < a)) & (0 == (0 == (a % 12)))) & (0 == (0 == (a % 3)))) & (6 < a)) & (2 < a)) & (10 < a)) & (0 == (14 < a))) & 1) & (5 < a)) & (0 == (0 == (a % 11)))) & (0 == (0 == (a % 13)))) & (0 == (0 == (a % 9)))) & (8 < a)) & (0 == (0 == (a % 8)))) & (0 == (0 == (a % 10)))) & (13 < a)) & (0 == (0 == (a % 5)))) & (0 == (a % 2))) & (0 == (0 == (a % 6)))) & (3 < a)) & (11 < a)) & (4 < a)) & (0 == (0 == (a % 4)))) & (12 < a)) & (7 < a))
    return 0;

  int count_new;
  int count_old;
  int CLEVER_ret_0_old = 0;
  int CLEVER_ret_0_new = 0;
  int i = 2;
  int count = count_new = (count_old = 0);
  while ((i < a) || (i < a))
  {
    if (i < a)
    {
      if ((a % i) != 0)
      {
        count_old++;
        count_new = 1;
      }

      i++;
    }

  }

  CLEVER_ret_0_old = count_old;
  CLEVER_ret_0_new = count_new;
  assert((((((0 == (0 == CLEVER_ret_0_old)) & (0 == (0 == CLEVER_ret_0_new))) | ((0 == CLEVER_ret_0_old) & (0 == CLEVER_ret_0_new))) | (((0 == CLEVER_ret_0_old) & (0 == (0 == CLEVER_ret_0_new))) & ((sum + i) == sum))) | (((0 == (0 == CLEVER_ret_0_old)) & (0 == CLEVER_ret_0_new)) & (sum == (sum + i)))) | (CLEVER_ret_0_old == CLEVER_ret_0_new));
}

