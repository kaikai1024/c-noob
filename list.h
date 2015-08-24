/*
*
*\file                  list.h
*\brief                 头文件
*\detail				结构体以及列表的各种操作声明
*
*\author				王旭东
*\version				v1
*\date					2015.8.21
*
*/

#define SAME     1
#ifndef LIST
#define LISt
typedef struct list
{
	struct list *next;
	struct element *myElement;
	char name[50];
	int count;
}list;

typedef struct element
{
	struct element *next;
	int mailSize;
	char date[20];
}element;
#endif
list* initList();

list* addList(list *aimList, char name[], int nameSize);

void addElement(list *aimList, char date[], int dateSize, int mailSize);

list* seachList(list *aimList, char name[], int nameSize);

void printList(list *aimList);
