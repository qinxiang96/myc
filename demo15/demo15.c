#include <stdio.h>
int main(){
    int a,b;
    a=1;
    b=2;
    int logic1 = a>b;
    int logic2 = a<b;
    int logic3 = a<b?"ÊÇ":"·ñ";
    printf("%d\n",logic1);
    printf("%d\n",logic2);
    printf("%d\n",logic3);
}