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
五、回调函数
void addCallbackFunc(void *(statusChange)(int status)){}
六、看门狗
不喂狗就会重启
七、RTOS
实时操作系统
提供事件驱动型设计方式，使得RTOS只是在处理实际任务时才会运行，能更合理的利用CPU。
在实际项目中，如果程序等待一个超时事件，传统的无RTOS情况下，要么在原地一直等待而不能执行其他任务，要么使用复杂的状态机制
使用RTOS则可以很方便的将当前任务阻塞在该事件下，然后自动去执行别的任务
