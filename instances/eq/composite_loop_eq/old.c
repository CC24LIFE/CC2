

int client(int x, int y) {
    int return_val = 0;
	if (x>=18 && x<22)
		return_val += lib(x,20);
	else
	    return_val += 0;

    if (y>=18 && y<22)
		return_val += lib(y,20);
	else
	    return_val += 0;

	return return_val;

}

int lib(int a, int b) {
	int c=0;
	for (int i=1;i<=b;++i)
		c+=a;
	
	return c;
}
