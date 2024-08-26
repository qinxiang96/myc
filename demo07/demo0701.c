#include <stdio.h>
#include <demo0702.h>
int main(void){
    int a[] = {1,2,3,4,5,6,7,8,9,55,};
    int min,max;
    minmax(a,sizeof(a),&min,&max);
    printf("min = %d,max = %d\n",min,max);
    return 0;
}