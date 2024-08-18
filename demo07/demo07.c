#include <stdio.h>
int main(){
    int a = 10;
    printf("a的地址=%p \n",&a);//a的地址=0x16f2d7108 
    int *p;//初始化一个p的指针
    p = &a;//将p指针赋值给a
    printf("p指向的地址是：%p\n",p);//p指向的地址是：0x16b4af108
    printf("p指向地址的值：%d\n",*p);//p指向地址的值：10
    return 0;
}
// 指针 作用：使用函数交换AB的值；传递大数组时，无需整个拷贝，只需传递指针；更复杂的数据结构，队列，链表，树
