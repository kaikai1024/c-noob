
#include "mailAnalysis.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int mailAnalysis(char *mailData, int mailSize, list *fromList, list *toList)
{
	char *positionDate,*positionFrom,*positionTo;
	FILE *fp;
	char tagDate[LENDATE] = "Date";
	char mailDate[50],mailFrom[50],mailTo[50];
	int lenDate,lenFrom,lenTo;
	list *plist = NULL;
	int flag=_strcmp(mailData,tagDate,LENDATE);
	if(flag==WRONGMESG)	return WRONGMESG;

	positionDate = mailData;
	positionFrom = searchLocal(mailData, FROM);
	positionTo = searchLocal(mailData, TO);

	recordMessage(positionFrom, mailDate, lenDate);
	recordMessage(positionDate, mailFrom, lenFrom);
	recordMessage(positionDate, mailTo, lenTo);

	//搜索发件人信息
	plist = searchList(fromList,mailFrom,lenFrom);
	if (plist == NULL)
	{
		list *temp = addList(fromList,mailFrom,lenFrom);
		addElement(temp, mailDate, lenDate, mailSize);
	}
	else
	{
		addElement(plist, mailDate, lenDate, mailSize);
	}

	//搜索收件人信息
	plist = searchList(toList,mailTo,lenTo);
	if (plist == NULL)
	{
		list *temp = addList(toList,mailTo,lenTo);
		addElement(temp, mailDate, lenDate, mailSize);
	}
	else
	{
		addElement(plist, mailDate, lenDate, mailSize);
	}

	printList(fromList);
	printList(toList);

	fp=fopen("user_mesg_from.txt","a");
	fprintf(fp, "%s\n", mailDate);
	fprintf(fp, "%s\n", mailFrom);
	fprintf(fp, "%s\n", mailTo);
	fprintf(fp, "%d\n", mailSize);
	fclose(fp);


	return RIGHT;
}

char *searchLocal(char *Data,int numb)
{
	while(numb!=0)
	{
		if(*Data == 0x0a)
		{
			--numb;
		}
		else if (Data == NULL)
		{
			return NULL;
		}
		++Data;
	}
	return Data;
}

void recordMessage(char *pData,char data[], int size)
{
	do
	{
		data[size] = *pData;
		++pData;
		++size;
	}while(*pData == 0x0a);
	data[size] = *pData;
	printf("%s", data );
}

int _strcmp(char *str1, char *str2, int len)
{
	while(len!=0)
	{
		if(*str1 != *str2)
		{
			return WRONGMESG;
		}
		else if (str1 == NULL || str2 == NULL)
		{
			return WRONGMESG;
		}
		++str1;
		++str2;
	}
	return RIGHT;
}
