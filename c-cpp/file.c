#include<stdio.h>



int main()
{
    int x = 10;
    int *ptr = &x;
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);
    printf("Value of ptr: %p\n", ptr);
    printf("Value pointed by ptr: %d\n", *ptr);
    printf("Address pointed by ptr: %p\n", ptr);
    return 0;
}