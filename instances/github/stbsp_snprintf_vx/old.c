int abstracted_vxLogBufPrint(unsigned number) {
        //since the string representation of uint is at most 10 digits
        __CPROVER_assume(number > 0 && number <= 10);
        unsigned buf = 256;
        char buffer[256];
        //int written = stbsp_snprintf(buf, 256, "Engine log for frame %ju:\n", vxFrameNumber);
        unsigned written = abstracted_stbsp_snprintf(buf, 256, 22 + number, buffer);
        written += abstracted_stbsp_snprintf(buf - written, 256 - written, 120, buffer);
        return written;
}


 //this library abstract away buff writing and string formatting with uninterrupted function with general assumptions.
unsigned int abstracted_stbsp_snprintf(unsigned int buf_size, unsigned int count, unsigned int string_length, char* buf){
  unsigned int length;
  if ( (count == 0) && !buf_size ){
        length = string_length;
        __CPROVER_assume(length >= 0 );
  }else{
    if (count == 0){
        length = 0;
    }else{
        if (string_length >= count){
            //if the buffer is not large enough, some character is written to the last pos
            buf[count -1] = 1;
        }else{
             buf[string_length] = 1;
        }

         if (string_length >= count){
            length = count;
        }else{
           length = string_length;
        }

        if (length >= count){
            length = length -1;
        }
        buf[length] = 0;
    }
  }

  return length;
 }