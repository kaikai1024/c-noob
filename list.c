/*
*
*\file                  list.c
*\brief                 接口函数
*\detail				列表的各种操作
*
*\author				王旭东
*\version				v1
*\date					2015.8.21
*
*/

#include "list.h"
#include <malloc.h>
#include <stdio.h>
//#include "mailAnalysis.h"

list* initList()
{
	list *plist = (list *)malloc(sizeof(list));
	plist->next = NULL;
	plist->myElement = NULL;
	return plist;
}

list* addList(list *aimList, char name[], int nameSize)
{
	list *plist = (list *)malloc(sizeof(list));
	plist->next = aimList->next;
	aimList->next = plist;
	plist->myElement = NULL;
	plist->count = 0;
	int i;
	for ( i = 0; i < nameSize; ++i)
	{
		plist->name[i] = name[i];
	}
	return plist;
}

void addElement(list *aimList, char date[], int dateSize, int mailSize)
{
	element *pelement = (element *)malloc(sizeof(element));
	pelement->next = aimList->myElement;
	aimList->myElement = pelement;
	pelement->mailSize = mailSize;
	++(aimList->count);
	int i;
	for ( i = 0; i < dateSize; ++i)
	{
		pelement->date[dateSize] = date[dateSize];
	}
}

list* searchList(list *aimList, char name[], int nameSize)
{
	while(1)
	{
		int flag=_strcmp(aimList->name,name,nameSize);
		if (flag == SAME)
		{
			return aimList;
		}
		if (aimList->next == NULL)
		{
			return NULL;
		}
		aimList = aimList->next;
	}
}

void printList(list *aimList)
{
	
	while(aimList->next != NULL)
	{
		aimList = aimList->next;
		printf("%s", aimList->name);
		printf("邮件数量：%d", aimList->count );
		element *pelement = aimList->myElement;
		int i;
		for ( i = 0; i < aimList->count; ++i)
		{
			printf("%s", pelement->date);
			printf("%d\n", pelement->mailSize);
			pelement = pelement->next;
		}
	}
}
