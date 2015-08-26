/*
**文件名：debug.c
**功能：一些调试函数的定义
**作者：冯开开
**版本：version1
**生成日期：2015/08/17
*/

#include "debug.h"

int debug(int int_inf,char inf [])
{
	int i = 0;

	if(int_inf == ERROR)
	{
		printf("\t-1--error:%s\n", inf);
	}
	else if (int_inf == INFO)
	{
		printf("\t1--info:%s\n", inf);
	}
	else if (int_inf == WARNING)
	{
		printf("\t0--warning:%s\n", inf);
	}
	else if(int_inf == DEBUG)
	{
		printf("\t-2--debug:%s\n", inf);
	}
	else if (int_inf == 16)
	{
		printf("mac address :\n");
		for (i = 0; i < USER_MAC_LEN; i++)
		{
			printf("0x%x\t", inf[i]);
		}
		printf("\n");
	}
	else 
	  printf("\tok: %d--%s\n", int_inf,inf);
	
	return 0;	
}
