int foo(int a, int b);

int client(int n) {
    int count = 0;
    int final_ret = 0;
    while (n > 1000){
        n = n /1000;
        count+= (lib(n));
    }
    int digit = count + lib(n);
    if ((n % 10) != 0){
        final_ret =  digit;
    }else{
        final_ret =  0;
    }
    return final_ret;
}

int lib(int n) {
	if (n < 0)
	    return -1;
	else if (n <= 10)
	    return 1;
	else if (n <= 100)
	    return 2;
	else if (n <= 1000)
	    return 3;
    else
        return 4;
}