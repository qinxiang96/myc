#include <stdio.h>
// 通过宏定义的判断去执行，相当于程序执行的开关 #ifdef 如果定义了就执行 #ifndef 如果没有定义就执行
#define SQUARE(x) (x)*(x)
//#define DEBUG
#ifdef DEBUG
    #define  MESSAGE "bug!"

#endif
typedef unsigned int uint32;//取别名
typedef struct 
{
    char title[50];
    char author[50];
    int id;
}Books;//给一个结构体取别名
typedef enum{
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5
}DAY;//定义一个枚举

int main(){
    uint32 a = 10;
    printf("%d\n",SQUARE(2));
    #ifdef DEBUG
    printf("message:%s\n",MESSAGE);
    #endif
    printf("%d\n",a);
    Books book = {"我的书","我",1};
    printf("%s\n",book.author);
    printf("%d\n",MON);
    scanf("%d",&a);//定义一个输入，取其值用&
    printf("输出的是：%d\n",a);
}