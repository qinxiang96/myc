C语言相关知识
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

# Mac机记录笔记
一、
信号量&互斥量：创建、获取、释放、删除
信号量用于同步，任务间或者任务和中断间同步
互斥量用于互锁，用于保护同时只能有一个任务访问的资源，为资源上一把锁
二值信号量：同步
计数信号量：资源使用统计
互斥量：互斥信号量其实就是一个拥有优先级继承的二值信号量
递归互斥：互斥中嵌套互斥
优先级反转：由于高优先级任务在等优先级任务释放信号量的过程中，低优先级被中优先级任务抢夺CPU，最终导致中优先级任务比高优先级任务先运行，也就是优先级翻转
而互斥信号量就可以将这个影响降到最低，当高优先级任务发现需要信号量被低级信号量占用需要等待时，就将优先级任务变成和自己同级优先级，就不至于在等待的过程中被中优先级抢夺CPU

二、运算符
按位与&：根据2个数的二进制进行运算，1-0->0;0-1->0;1-1->1;0-0->0
按位或|：0-0->0;其他的都是1
按位异或^：1-0->1;0-1->1;1-1->0;0-0->0
按位取反~：1取0,0取1，即~a=-(a+1)
原码
反码
补码
左移<<:左边溢出的数字被丢弃，右边的用0补充

三、十六进制
0-9 10个数
A-F 6个数
一共16个数

四、数组和指针的关系
函数参数表中的数组实际是指针
但可以用数组的运算符[]进行计算
数组变量是特殊的指针
数组变量本身表达地址

所指向的值是const表示不能通过这指针去修改那个变量
const int *p = &i;
*p = 26;//ERROR
p = &j;//OK
i = 22;//OK

总是可以把一个非const的值转换为const的
void f(const int* x);
int a = 15;
f(&a);//ok
const int b = a;
f(&b);//ok
b = a + 1;//error

五、指针的类型转换
void*表示不知道指向什么东西的指针
指针也可以转换类型
int *p = &i;
void*q = (void*)p;
这并没有改变p所指的变量的类型，而是让后人用不同的眼光通过p看所指的变量：我不再当你是int，我认为你就是个void

六、动态内存分配
// malloc去申请空间，申请的空间大小是以字节为单位的，返回的结果是void*,需要类型转换为自己需要的类型，
// 没有空间了，如果申请失败
// free去释放空间，free只针对malloc的地址
// 常见的问题：申请了没有free，长时间运行内存逐渐下降，新手忘了，老手找不到合适的free的时机
//              free过了再free
//              地址变过了，直接去freeC

七、putchar
int putchar(int c);
向标准输出写一个字符
返回写了几个字符，EOF(-1)表示写失败
EOF是一个宏

八、getchar
int getchar(void)
从标准输入读入一个字符
返回类型是int是为了返回EOF(-1)

九、字符串数组
char **a
a是一个指针，指向另一个指针，那个指针指向一个字符串

十、Mac开发
gcc hello.c
会生成a.out
./a.out
执行a.out文件

十一、strlen
size_t strlen(const char *s)
返回s的字符串长度（不包括结尾的0）

十二、编译预处理
#define PI 3.14
在C语言的编译器开始编译之前，编译预处理程序会把程序中的名字换成值
完全的文本替换

定义没有值的宏
#define _DEBUG
这类宏用于条件编译的，后面有其他的编译预处理指令来检查这个宏是否已经被定义过了
预定义的宏
_LINE_ 表示行号

十三、多文件执行命令
方式一：
gcc -Wall -Wextra -g3 /Users/qinxiang/Documents/code/myc/demo19/main.c /Users/qinxiang/Documents/code/myc/demo19/max.c -o /Users/qinxiang/Documents/code/myc/demo19/output/main

cd /Users/qinxiang/Documents/code/myc/demo19/output
./main

输出
6

方式二：
cd 目标文件夹
gcc main.c max.c

会生成a.out

执行a.out
./a.out

输出
6

实验：
gcc --save-temps main.c -c
只做编译不做链接

查看最后几行
tail main.i





十四、#include
编译器预处理指令，和宏一样，在编译之前就处理了
把那个文件的全部文本内容原封不动的插入到他所在的地方
所以也不一定要在.c文件的最前面定义#include

其中" "和<>的区别：
""要求编译器首先在当前目录寻找这个文件，如果没有，到编译器指定的目录去找
<>让编译器直接去指定目录找

十五、标准头文件结构
防止重复定义
运行条件编译和宏，保证这个头文件在一个编译单元中只会被#include一次

#ifndef _MAX_H_
#define _MAX_H_
//在这里定义方法，防止重复定义
#endif

十六、extern
extern  int gAll;
用extern修饰的变量，在其他文件中也可以被使用





