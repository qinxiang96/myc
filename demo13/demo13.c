#include <stdio.h>
typedef struct 
{
    int status;
    void (*statusChange)();
}T_Device;
T_Device g_device;
//ע�ắ�������԰�״̬ע�ᵽ����ȥ
void addCallbackFunc(void (*pstatusChange)(int status)){
    g_device.statusChange = pstatusChange;
}
int getStatus(){
    return g_device.status;
}
//���к���
void run(){
    g_device.status = 10;
    if(g_device.status == 10){
        if (g_device.statusChange != NULL)
        {
            g_device.statusChange(g_device.status);
        }
        
    }
}
//�û�����
void callBack(int status){
    printf("status = %d\n",status);
}
void main(){
    addCallbackFunc(callBack);
    run();
}
