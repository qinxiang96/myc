#include <stdio.h>
typedef struct node
{
    char data;
    struct node *pnext;
    
}t_node;

int main(){
    t_node node1;
    t_node node2;
    node1.data = 1;
    node2.data = 2;
    node1.pnext = &node2;
    printf("node2 data = %d\n",node2.data);
    printf("node2 data = %d\n",node1.pnext->data);
    return 0;
}