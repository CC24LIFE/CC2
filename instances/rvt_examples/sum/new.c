int int_array[] = {1,2,0,3,4,5,6,8,9,10};

int lib(int n) {
        n = 5;
        n++;
        if (n <= 1) return n;
        return n + n-1 + sum(n-2);
}


//find the missing integer in a 10 integer ascending sequence
int client() {
    int actual_sum = 0;
    for (int i=0; i < 10; i++){
        actual_sum += int_array[i];
    }
    return actual_sum - lib(10);
}