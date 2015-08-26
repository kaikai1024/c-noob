/*
**文件名：ap_manage.h
**功能：链表接口的声明，结构体的定义
**作者：冯开开
**版本：version1
**生成日期：2015/08/17
*/

#include "debug.h"
#include <stdlib.h>

#define MEMERY_SIZE ( 4 * 1024 * 1024)

/*存储了用户的mac地址信息*/
typedef struct _AP_USER_ENTRY
{
	unsigned char mac[USER_MAC_LEN];
} AP_USER_ENTRY;

/*定义了用户节点*/
struct ap_node
{
	AP_USER_ENTRY ap_user;
	struct ap_node * p_prev;
	struct ap_node * p_next;
};

/*定义了链表节点*/
struct list 
{
	/*p_head指向已经添加的节点*/
	struct ap_node * p_head;
	/*p_spare_head指向已经删除的节点*/
	struct ap_node * p_spare_head;
	/*添加节点数目*/
	unsigned int count;
	/*删除节点数目*/
	unsigned int count_spare;
	/*最大可添加节点数目*/
	unsigned int  max;
};

typedef struct list List;

int list_init(List *p_list, unsigned int max);
void list_del_link(List ** p_p_list);
int list_ergodic(List *p_list);
struct ap_node * list_search(AP_USER_ENTRY ap_user, List * p_list);
List * list_sort(List *p_list);
int list_add_user(AP_USER_ENTRY ap_user, List *p_list);
List * list_del_user(AP_USER_ENTRY ap_user, List *p_list);
