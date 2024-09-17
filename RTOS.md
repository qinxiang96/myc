# 一. 处理器
## 1.1 类型
cortex-M0
R系列：实时操作系统
M0系列：微控制器，主打低功耗和混合信号处理
cortex-M0微处理器主要包括处理器内核、嵌套向量中断控制器NVIC、调试子系统、内部总线系统

## 1.2 通用寄存器
R0-R7为低端寄存器，可作为16位或32位指令操作数，
R8-R12为高端寄存器，只能用作32位操作数

特殊寄存器
R13：堆栈指针SP（主栈指针MSP，进程栈指针PSP）
R14：连接寄存器LR，用于存储子程序或者函数调用的返回地址
R15：程序计数器PC，存储下一条将要执行的指令地址

## 1.3 异常和中断
外部的中断称为中断
内核的中断称为异常

cortex-M0最多处理外部中断数为32个

# 二. 主控制器MCU
## 2.1 


# 三. OLED模块
## 3.1 原理

驱动IC
4针脚I2C接口、

接线图：飞线用于接通板子的正负极
GND-->电源负极
VCC-->电源正
SCL时钟-->PB8
SDA-->PB9

7针脚SPI接口
像素


## 3.2 移植
将屏驱动的部分放到自己工程的一个单独的文件夹中（一般有4个文件：OLED.c OLED.h OLED_Data.c OLED_Data.h)
OLED_Data.c 字库定义-汉字的显示需要有对应的字库-汉字的大小都是16*16的点阵-字模数据就是点阵数据，决定哪些像素亮哪些像素不亮

字模的生成
    取模方式，列行式（先从左往右，再从上到下）
    图像数据也可以自定义，取模软件只接受BMP格式的

然后就可以在自己的.c文件中使用和操作OLED了

## 3.3 函数
显示函数
绘图函数

显示设置
OLED_WriteCommand(0xA1);设置左右方向，0xA1正常，0xA0左右反置

## 3.4 屏驱动IC
用来扫描驱动的芯片，任务是接收数据、显示存储、扫描刷新
其引脚分别接到了屏幕点阵的行和列，下面接通讯的引脚，需要显示的内容通过通讯引脚传递
驱动接口：128个SEG引脚和64个COM引脚，对应128*64像素点阵显示屏
内置显示存储器：GDDRAM 128*64bit SRAM
供电：VDD:1.65-3.3V IC逻辑；VCC:7-15V 面板驱动(屏幕底板有升压电路，通过命令控制，所以VCC可以不接)
    拓展：MOS场效应管（GDS VDD正 VSS负）
通信接口（通讯协议）：8位6800/8080并行接口，3/4线SPI接口，I2C接口（使用BS0-BS2这3个引脚控制选择哪种通信接口，接VCC就是接高电平，接四条线就是接低电平，时钟和输入和输出)
R/W#(WR#):读操作、写操作、读写的时机
CS#:片选chip select 低电平选中芯片
RES#:复位reset 低电平芯片复位
D/C#:命令低电平，数据高电平

运行过程：数据通过通讯引脚发送到IC的MCU,MCU判断数据是数据还是命令，分别做不同的处理，数据写入到GDDRAM的对应位置上，然后通过显示控制器，把内容扫描刷新到屏幕上
振荡器用于提供刷新屏幕的时钟，CL是时钟输入角，CLS(CLOCK SELECT)是时钟源选择脚--CLS接高电平，选择内部时钟，CL引脚不用，CLS接低电平，选择外部时钟，CL加一个外部时钟源

## 3.5 I2C通讯
起始-发送从机地址+起始位（二进制转化为16进制传输）-接收应答-继续发送下一个字节或终止时序
非连续时序：发送一个命令，接收应答，继续发送一个或多个数据，终止时序
MyI2C_SendByte(0x78);//寻址，OLED模块的地址
unit8_t Ack = MyI2C_ReceiveAck();//OLED对0x78的应答信号
MyI2C_SendByte(0x00);//control byte 非连续模式写命令
MyI2C_ReceiveAck();
MyI2C_SendByte(command);//data byte
MyI2C_Stop();

void OLED_WriteCommand(uint8_t Command){
    MyI2C_Start();
    MyI2C_SendByte(0x78);//寻址，OLED模块的地址
    MyI2C_ReceiveAck();//OLED对0x78的应答信号
    MyI2C_SendByte(0x00);//control byte 非连续模式写命令
    MyI2C_ReceiveAck();
    MyI2C_SendByte(Command);//data byte
    MyI2C_Stop();
}

void OLED_WriteData(uint8_t Data){
    MyI2C_Start();
    MyI2C_SendByte(0x78);//寻址
    MyI2C_ReceiveAck();//应答信号
    MyI2C_SendByte(0x40);//control byte 非连续模式写命令
    MyI2C_ReceiveAck();
    MyI2C_SendByte(Data);//data byte
    MyI2C_Stop();
}

void OLED_Init(void){
    MyI2C_Init();
    Delay_ms(100);
    OLED_WriteCommand(0xAE);//调用这个函数有3种方式，一将函数在最前面声明，二将函数声明放到头文件中，三将函数放在调用前定义 //0xAE表示显示关闭
    OLED_WriteCommand(0xD5);//双字节命令
    OLED_WriteCommand(0x80);//双字节命令

}
void OLED_SetCursor(unit8_t X,unit8_t Page ){
    OLED_WriteCommand(0x00 | (X & 0x0F));
    OLED_WriteCommand(0x10 | (X & 0xF0) >> 4);
    OLED_WriteCommand(0xB0 | Page);
}

// 显示字母A 先设置起始坐标，再写入字模
OLED_SetCursor(10,2);
OLED_WriteData(0x00);
OLED_WriteData(0x7C);
OLED_WriteData(0x12);
OLED_WriteData(0x11);
OLED_WriteData(0x12);
OLED_WriteData(0x7C);

ASCII码是一套数字到字符的映射标准，规定了用什么数字表示什么字符
char s[] = "hi";等效于char s[] = {0x68,0x69,0x00};0x00表示字符串结尾，空字符，作为字符串结束标志位使用

void OLED_ShowChar(unit8_t x,unit8_t Page,char Char,unit8_t FontSize){
    if(FontSize == 6){//6*8点阵
        OLED_SetCursor(X,Page);
        for(unit8_t i = 0; i<6;i++){
            OLED_WriteData(OLED_F6x8[Char - ' '][i]);
        }
    }
    else if(FontSize == 8){//8*16点阵
        OLED_SetCursor(X,Page);
        for(unit8_t i = 0; i<8;i++){
            OLED_WriteData(OLED_F8x16[Char - ' '][i]);
        }
        OLED_SetCursor(X,Page+1);
        for(unit8_t i = 0; i<8;i++){
            OLED_WriteData(OLED_F8x16[Char - ' '][i+8]);
        }
    }
    
}
void OLED_ShowString(unit8_t X,unit8_t Page, char *String,unit8_t FontSize){
    for(unit8_t i =0;Sting[i] != '\0';i ++){
        OLED_ShowChar(X+i*FontSize,Page,String[i],FontSize);
    }
}

## 3.6 缓存区
数据直接写入到GDDRAM的对应位置
弊端：只能以页为单位进行指定，只能以字节为单位进行显示

在ST32中定义一个显存数组，可直接读取内部的数组

# 四、硬件原理图
原理图：表示电路板上各器件之间连接原理的图表

## 4.1 复位
芯片运行必须复位，因为如果不复位，他是随机运行的，复位会完整的执行所有的程序
## 4.2 晶振
提供时钟信号
## 4.3 上拉下拉电阻
上拉和下拉电阻主要用于数字电路中，以确保某一信号线上具有确定的逻辑电平，从而避免输入悬空，产生不确定状态。
上拉电阻将信号线连接到电源正极（通常是+Vcc）。当输入引脚没有被驱动时（即未连接到其他电路），上拉电阻会将该引脚的电平“拉”到高电平（逻辑1）。
下拉电阻将信号线连接到电源的地（GND）。当输入引脚未被驱动时，下拉电阻将信号线的电平“拉”到低电平（逻辑0）。
## 4.4 跳线帽
## 4.5 二极管
D1 负极连接芯片的引脚
## 4.6 电容
两条平行线
作用：降压，比如220V的电压和灯泡之间加一个电容（当电容的容量为1.5uf时，有容抗，承担210V的压降）
滤波
延时
耦合：使高频信号通过电容流向地，从而使芯片免受高频信号的干扰
## 4.7 网络标号
电气连接点，具有相同网络标号表示连接在一起
## 4.8 烧录孔











