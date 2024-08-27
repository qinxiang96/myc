#include <stdio.h>
#include <stdlib.h>
// malloc去申请空间，申请的空间大小是以字节为单位的，返回的结果是void*,需要类型转换为自己需要的类型，
// 没有空间了，如果申请失败
// free去释放空间，free只针对malloc的地址
// 常见的问题：申请了没有free，长时间运行内存逐渐下降，新手忘了，老手找不到合适的free的时机
//              free过了再free
//              地址变过了，直接去free
int main(){
    int number;
    int* a;
    int i;
    printf("输入数量：");
    scanf("%d",&number);
    a=(int*)malloc(number*sizeof(int));
    for ( i = 0; i < number; i++)
    {
        scanf("%d",a[i]);

    }
    for ( i = number - 1; i >= 0; i--)
    {
        printf("%d ",a[i]);
    }
    free(a);
    return 0;
    
}