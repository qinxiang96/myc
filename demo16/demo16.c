#include <stdio.h>
#include <stdlib.h>
// mallocȥ����ռ䣬����Ŀռ��С�����ֽ�Ϊ��λ�ģ����صĽ����void*,��Ҫ����ת��Ϊ�Լ���Ҫ�����ͣ�
// û�пռ��ˣ��������ʧ��
// freeȥ�ͷſռ䣬freeֻ���malloc�ĵ�ַ
// ���������⣺������û��free����ʱ�������ڴ����½����������ˣ������Ҳ������ʵ�free��ʱ��
//              free������free
//              ��ַ����ˣ�ֱ��ȥfree
int main(){
    int number;
    int* a;
    int i;
    printf("����������");
    scanf("%d",&number);
    a=(int*)malloc(number*sizeof(int));
    for ( i = 0; i < number; i++)
    {
        scanf("%d",a[i]);

    }
    for ( i = number - 1; i >= 0; i--)
    {
        printf("%d ",a[i]);
    }
    free(a);
    return 0;
    
}