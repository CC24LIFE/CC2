int abstracted_gzprintf(unsigned int buf_size, unsigned int string_length) {
    __CPROVER_assume(buf_size <= 8192);
    unsigned int len = 0;
    if (buf_size ==0){
        len =  0;
    }else{
    int size = (int) buf_size;
    char buffer[size];
    buffer[size - 1] = 0;
    len = abstracted_stbsp_snprintf(buf_size, size, string_length, buffer);

    if (len <= 0 || len >= size || buffer[size - 1] != 0)
        len = 0;

     }

    return len;

}




 //this library abstract away buff writing and string formatting with uninterrupted function with general assumptions.
 unsigned int abstracted_stbsp_snprintf(unsigned int buf_size, unsigned int count, unsigned int string_length, char* buf){
  unsigned int length;
  if ( (count == 0) && !buf_size ){
        //compute_length computes the number of character written into the buf
        length = string_length;
        __CPROVER_assume(length >= 0 );
  }else{
    //compute_length computes the number of character written into the buf
        if (string_length >= count){
            //if the buffer is not large enough, some character is written to the last pos
            buf[count -1] = 1;
        }else{
            buf[string_length] = 1;
        }

        int l;
        length = string_length;
        l = (int)string_length;
        if (l >= count){
            l = count -1;
        }
        buf[l] = 0;
  }

  return length;
 }