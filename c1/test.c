/*
**文件名：test.c
**功能：对链表接口进行功能上的测试
**作者：冯开开
**版本：version1
**生成日期：2015/08/17
*/

#include <string.h>
#include <stdio.h>
#include "ap_manage.h"

int main()
{
	unsigned int max = 0, input_num = 0, tmp = 0;
	int i = 0;
	char mac[USER_MAC_LEN] = {0};
	List * p_list = NULL;
	void * p_head_mem = NULL;
	AP_USER_ENTRY  ap_user;

	debug(1, "please input the max number:");
	scanf("%d", &max);

	/*init the list
	**初始化链表*/
	p_head_mem = malloc(MEMERY_SIZE);
	debug((unsigned long)p_head_mem, "malloc the memery_size");
	p_list = (List *) p_head_mem;
	list_init(p_list, max);
	list_ergodic(p_list);

	/*add the user
	**添加用户*/
	debug(1, "input the number of users:");
	scanf("%d", &input_num);
	debug(1, "add the new user:(6)");

	while(input_num != tmp)
	{
		scanf("%s", mac);
		strcpy(ap_user.mac, mac);
		debug(1, ap_user.mac);
		list_add_user(ap_user, p_list);
		tmp++;
	}

	/*ergodic the list
	**遍历链表*/
	debug(1, "add user ---- end\n");
	list_ergodic(p_list);

	/*sort the list
	**对链表进行排序*/
	list_sort(p_list);
	list_ergodic(p_list);

	/*search the user
	**查找用户*/
	debug(1, "input the user of searing:");
	scanf("%s", mac);
	strcpy(ap_user.mac, mac);
	list_search(ap_user, p_list);

	/*delet the user
	**删除用户*/
	debug(1, "input the user of deleting:");
	scanf("%s", mac);
	strcpy(ap_user.mac, mac);
	p_list = list_del_user(ap_user, p_list);
	list_ergodic(p_list);

	/*delet the whole list
	**删除整个链表*/
	list_del_link(&p_list);
	debug((unsigned long)p_list, "list_");
	list_ergodic(p_list);

	return 0;
}
