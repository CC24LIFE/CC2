int lib(int n){
    int result;
    if(n > 0){
        int acc = 1;
        int x = 1;
        while(x < n + 1){
            acc = acc * x;
            x = x+1;
        }
        result= acc;
    }else{
    result =  0;
    }
    return result;
}


int factorial(int x){
    if(x<5){
        return lib(x);
    }else{
        return 0;
    }
}