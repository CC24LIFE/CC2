extern void __VERIFIER_assume (int);
extern void __VERIFIER_error ();
__attribute__((__noreturn__)) extern void __VERIFIER_error (void);
 #define assert(X) if(!(X)){__VERIFIER_error ();}
 #define assume __VERIFIER_assume
extern int nd();
int main()
{
  int n = nd();
  client(n);
}

int client(int n)
{
  int sum_new;
  int sum_old;
  int CLEVER_ret_0_old = 0;
  int CLEVER_ret_0_new = 0;
  int i = 0;
  int sum = sum_new = (sum_old = 0);
  {
    if ((0 == (i <= n)) & (0 == (2 < sum)))
    {
      sum_new = sum;
      sum_old = sum;
      i = i;
      CLEVER_ret_0_new = 0;
      CLEVER_ret_0_old = 1;
    }
    else
    {
      sum_new = 99999;
      i = 99999;
      CLEVER_ret_0_new = 99999;
      sum_old = 99999;
      CLEVER_ret_0_old = 99999;
    }

  }
  assert(CLEVER_ret_0_old == CLEVER_ret_0_new);
}

int lib_old(int a)
{
  int i = 2;
  int count = 0;
  while (i < a)
  {
    if ((a % i) != 0)
    {
      count++;
    }

    i++;
  }

  return count;
}

int lib_new(int a)
{
  int i = 2;
  int count = 0;
  while (i < a)
  {
    if ((a % i) != 0)
    {
      count = 1;
    }

    i++;
  }

  return count + 1;
}

