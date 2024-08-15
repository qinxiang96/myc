#include <stdio.h>
#define FILENAME "./1.txt"
#define WRITEWOEDS "These words are written in file.\n这是新加入的文件内容\n"
int main(){
    FILE *fd = NULL;//文件描述符
    size_t Nmemb = 1;//以单次写入某个长度的方式写入的个数
    printf("run start");
    fd = fopen(FILENAME, "a");//打开一个名为FILENAME的文件，如果改文件夹没有则创建，权限为可读可写
    if(NULL == fd){//判断是否打开成功
        perror("open");
                    return -1;
    }
    fwrite(WRITEWOEDS,sizeof(WRITEWOEDS),Nmemb,fd);//往文件写入WRITEWORDS字符串，不覆盖原文内容
    fclose(fd);//关闭文件
    fd = NULL;//清空指针
    printf("run end");  while (1);
   
    

}