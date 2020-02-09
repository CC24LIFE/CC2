int lib(int x)
{
  return x % 5;
}

int client(int x, int x_copy1, int x_copy2, int x_copy3, int x_copy4, int x_copy5, int x_copy6, int x_copy7)
{
  int ret;
  if ((x < (-100)) || (x > 100))
  {
    ret = x;
  }
  else
  {
    x = (x * 5) * 6;
    if (lib(x) == 0)
    {
      ret = 1;
    }
    else
    {
      ret = 0;
    }

  }

  int ret_copy1;
  if ((x_copy1 < (-100)) || (x_copy1 > 100))
  {
    ret_copy1 = x_copy1;
  }
  else
  {
    x_copy1 = (x_copy1 * 5) * 6;
    if (lib(x_copy1) == 0)
    {
      ret_copy1 = 1;
    }
    else
    {
      ret_copy1 = 0;
    }

  }

  int ret_copy2;
  if ((x_copy2 < (-100)) || (x_copy2 > 100))
  {
    ret_copy2 = x_copy2;
  }
  else
  {
    x_copy2 = (x_copy2 * 5) * 6;
    if (lib(x_copy2) == 0)
    {
      ret_copy2 = 1;
    }
    else
    {
      ret_copy2 = 0;
    }

  }

  int ret_copy3;
  if ((x_copy3 < (-100)) || (x_copy3 > 100))
  {
    ret_copy3 = x_copy3;
  }
  else
  {
    x_copy3 = (x_copy3 * 5) * 6;
    if (lib(x_copy3) == 0)
    {
      ret_copy3 = 1;
    }
    else
    {
      ret_copy3 = 0;
    }

  }

  int ret_copy4;
  if ((x_copy4 < (-100)) || (x_copy4 > 100))
  {
    ret_copy4 = x_copy4;
  }
  else
  {
    x_copy4 = (x_copy4 * 5) * 6;
    if (lib(x_copy4) == 0)
    {
      ret_copy4 = 1;
    }
    else
    {
      ret_copy4 = 0;
    }

  }

  int ret_copy5;
  if ((x_copy5 < (-100)) || (x_copy5 > 100))
  {
    ret_copy5 = x_copy5;
  }
  else
  {
    x_copy5 = (x_copy5 * 5) * 6;
    if (lib(x_copy5) == 0)
    {
      ret_copy5 = 1;
    }
    else
    {
      ret_copy5 = 0;
    }

  }

  int ret_copy6;
  if ((x_copy6 < (-100)) || (x_copy6 > 100))
  {
    ret_copy6 = x_copy6;
  }
  else
  {
    x_copy6 = (x_copy6 * 5) * 6;
    if (lib(x_copy6) == 0)
    {
      ret_copy6 = 1;
    }
    else
    {
      ret_copy6 = 0;
    }

  }

  int ret_copy7;
  if ((x_copy7 < (-100)) || (x_copy7 > 100))
  {
    ret_copy7 = x_copy7;
  }
  else
  {
    x_copy7 = (x_copy7 * 5) * 6;
    if (lib(x_copy7) == 0)
    {
      ret_copy7 = 1;
    }
    else
    {
      ret_copy7 = 0;
    }

  }

  return ((((((ret + ret_copy1) + ret_copy2) + ret_copy3) + ret_copy4) + ret_copy5) + ret_copy6) + ret_copy7;
}

