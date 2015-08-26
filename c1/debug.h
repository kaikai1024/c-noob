/*
**文件名：debug.h
**功能：调试接口的一些声明
**作者：冯开开
**版本：version1
**生成日期：2015/08/17
*/

#include <stdio.h>

#define USER_MAC_LEN (6)

#define INFO 1
#define DEBUG -2
#define WARNING 0
#define ERROR -1 

int debug(int int_inf, char inf []);
