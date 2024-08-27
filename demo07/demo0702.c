#include <stdio.h>

void minmax(int a[], int len, int *min,int *max){
    int i;
    *min = *max = a[0];
    for ( i = 1; i < len; i++)
    {
        if (a[i] < *min)
        {
            *min = a[i];
        }
        if (a[i] > *max)
        {
            *max = a[i];
        }
        
        
    }
    
}