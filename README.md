# myc
笔记
一、
define预处理器：可以通过define的方式初始化一个常量
#define pi 3.14f
二、
static 的用法：
1、限制作用域
文件a.c
static void func(){}
void testc(){}
文件b.c
不能调用func()
只能调用testc()
2、管理生命周期
被static修改的变量只初始化一次，调用时的值不会被重置
三、
结构体
typedef struct{
    int a;
    char b;
}t_c;
四、
指针
变量为表示数据而生，指针为了传递数据而生
指针就是一个变量，不过放的是别的变量地址

