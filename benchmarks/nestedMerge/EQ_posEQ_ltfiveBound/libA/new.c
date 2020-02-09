int lib(int x)
{
  int ret;
  if (x < 0)
    ret = 0;
  else
    ret = x;

  return ret;
}

int client(int x)
{
  int INLINED_RET_1;
  int INLINED_RET_0;
  int ret;
  if (x > 0)
  {
    int x_copy0 = -x;
    int ret_copy0;
    if ((x_copy0 < (-100)) || (x_copy0 > 100))
    {
      ret_copy0 = x_copy0;
    }
    else
    {
      if (x_copy0 < 0)
      {
        ret_copy0 = (-lib((-x_copy0) * 5)) / 5;
      }
      else
      {
        ret_copy0 = (lib((x_copy0 + 1) * 5) / 5) - 1;
      }

    }

    INLINED_RET_0 = ret_copy0;
    ret = -INLINED_RET_0;
  }
  else
  {
    int x_copy1 = x;
    int ret_copy1;
    if ((x_copy1 < (-100)) || (x_copy1 > 100))
    {
      ret_copy1 = x_copy1;
    }
    else
    {
      if (x_copy1 < 0)
      {
        ret_copy1 = (-lib((-x_copy1) * 5)) / 5;
      }
      else
      {
        ret_copy1 = (lib((x_copy1 + 1) * 5) / 5) - 1;
      }

    }

    INLINED_RET_1 = ret_copy1;
    ret = INLINED_RET_1;
  }

  return ret;
}


