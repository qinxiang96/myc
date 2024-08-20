#include <stdio.h>
typedef struct 
{
    int status;
    void (*statusChange)();
}T_Device;
T_Device g_device;
//注册函数，可以把状态注册到里面去
void addCallbackFunc(void (*pstatusChange)(int status)){
    g_device.statusChange = pstatusChange;
}
int getStatus(){
    return g_device.status;
}
//运行函数
void run(){
    g_device.status = 10;
    if(g_device.status == 10){
        if (g_device.statusChange != NULL)
        {
            g_device.statusChange(g_device.status);
        }
        
    }
}
//用户代码
void callBack(int status){
    printf("status = %d\n",status);
}
void main(){
    addCallbackFunc(callBack);
    run();
}
