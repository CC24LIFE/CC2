int client(int n ,int m){
    int i = 0;
    int sum = 0;
    while (i<=n){
        if (lib(i) == 0 ){
            sum +=i;
        }
        i++;
    }
    int j = 0;
    int sum_delta = 0;

     while (j<=m){
        if (lib(j) == 0 ){
            sum_delta +=j;
        }
        j++;
    }

    return sum_delta - sum;
}

int lib(int a){
    int i = 2;
    int count = 0;
    while (i < a){
        if ((a % i ) != 0){
            count++;
        }
        i++;
    }
    return count;
}