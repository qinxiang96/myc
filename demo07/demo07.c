#include <stdio.h>
int main(){
    int a = 10;
    printf("a�ĵ�ַ=%p \n",&a);//a�ĵ�ַ=0x16f2d7108 
    int *p;//��ʼ��һ��p��ָ��
    p = &a;//��a�ĵ�ַ��ֵ��ָ��p
    printf("pָ��ĵ�ַ�ǣ�%p\n",p);//pָ��ĵ�ַ�ǣ�0x16b4af108
    printf("pָ���ַ��ֵ��%d\n",*p);//pָ���ַ��ֵ��10
    int b = 20;
    swap(&a,&b); //&��ȡint���͵ı���a�ĵ�ַ
    printf("a = %d, b = %d \n",a,b);
    return 0;
}
// ָ�� ���ã�ʹ�ú�������AB��ֵ�����ݴ�����ʱ����������������ֻ�贫��ָ�룻�����ӵ����ݽṹ�����У�������

void swap(int *data1, int *data2){
    int temp = *data2;
    *data2 = *data1;
    *data1 = temp;
}
