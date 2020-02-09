int lib(int n){
    int result;
    if(n <= 0){
        result =  1;
    }else{
        result =  n * lib(n-1);
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