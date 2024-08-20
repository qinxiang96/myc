#include <stdio.h>
#include <stdarg.h>
#define OPEN_LOG 1
#define LOG_LEVEL LOG_DEBUG

typedef enum{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
}E_LOGLEVEL;

char *EM_LOGLevelGet(const int level){
    if(level == LOG_DEBUG){
        return "DEBUG";
    }else if(level == LOG_INFO){
        return "INFO";
    }else if(level == LOG_WARN){
        return "WARN";
    }else if(level == LOG_ERROR){
        return "ERROR";
    }
    return "UNKNOWN";
}
//可变参数

void test(char *fmt,...){
    va_list arg1;
    va_start(arg1,fmt);
    printf("%d\n", va_arg(arg1,int));
    printf("%d\n", va_arg(arg1,int));
    printf("%d\n", va_arg(arg1,int));
    va_end(arg1);
}
//日志方法，可控制日志的输出
void EM_LOG(const int level, char *fmt,...){
    #ifdef OPEN_LOG
    va_list arg;
    va_start(arg,fmt);
    char buf[1+vsnprintf(NULL,0,fmt,arg)];
    vsnprintf(buf,sizeof(buf),fmt,arg);
    va_end(arg);
    if (level >= LOG_LEVEL)
    {
        printf("%s\n",buf);
    }
    
    
    #endif
}
int main(){
    int a = 10,b = 11;
    test("",a,b);
    EM_LOG(LOG_INFO,"app start...");
    EM_LOG(LOG_DEBUG,"A = %d",a);
    return 0;
}