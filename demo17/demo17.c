#include <stdio.h>
#include <string.h>
int main(){
    char line[] = "hello";
    printf("strlen = %lu\n", strlen(line));
    printf("sizeof = %lu\n", sizeof(line));//strlen = 5 sizeof = 6
    return 0;
}