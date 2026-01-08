// void pointer example
#include<stdio.h>


/*
 a good summary of all this
 void pointer is a pointer that can point to any data type
 we need to cast it to the correct data type to access the value
 in this case, we cast it to an int pointer
 and this whole syntax is called dereferencing a void pointer
 what is this syntax ? *(int*)ptr
 */

int main(){
    int num = 10;
    float fnum = 3.14;
    
    void *ptr;
        
    ptr = &num;
    printf("Integer: %d\n", *(int*)ptr);
        
    
    
    ptr = &fnum;
    printf("Float: %f\n", *(float*)ptr);
    
}
