#include <stdio.h>
#include <string.h>
// 结构体的定义
struct Books
{
    /* data */
    char title[50];
    char author[50];
    int id;
}book = {"c语言","xiaozhi",2024};

void printBook(struct Books book)
{
    /* data */
    printf("%s\n",book.title);
    printf("%s\n",book.author);
    printf("%d\n",book.id);
};
void printBookByTick(struct Books *book){//通过指针传递
    strcpy(book->author,"qin");//改变book中author的值
    printf("%s\n",book->title);
    printf("%s\n",book->author);
    printf("%d\n",book->id);
    

}

int main(){
    printf("%s\n",book.title);
    printf("%d\n",book.id);
    printBook(book);
    printBookByTick(&book);//指针要通过&取值
}
