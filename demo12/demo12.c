#include <stdio.h>
//将16进制的数转化为十进制的数字 %ld用于打印long int类型的整数
unsigned char time_buffer[4] = {0x5F,0xCB,0x0F,0x4F};
unsigned int time;
unsigned int u8Tou32B(unsigned char *buffer){
    return (((((((unsigned int)buffer[0])<<8)|buffer[1])<<8)|buffer[2])<<8)|buffer[3];
}
void main(){
    time = u8Tou32B(time_buffer);
    printf("time = %u s \n",time);
}