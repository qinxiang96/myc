#include "stm32f10x.h"
#include "OLED.h"

int main(void){
    OLED_Init();
    OLED_ShowString(0,0,"hello world!",OLED_8X16);//������ ������ ���� �ֺ�
    return 0;

}