/*
**文件名：ap_manage.c
**功能：实现了链表的一些功能的接口：增删改查，遍历排序
**作者：冯开开
**版本：version1
**生成日期：2015/08/17
*/

#include "ap_manage.h" 

/*get a spare node
**static struct ap_node * get_spare_node(List * p_list);
**在添加节点到申请内存的尾部时，调用此函数来获得一个已经删除的空闲的节点空间
**参数p_list 为链表指针，返回一个节点指针，即即将要添加的节点指针
*/
static struct ap_node * get_spare_node(List * p_list)
{
	struct ap_node * p_spare_head, * p_spare_tail;
	p_spare_head = p_list->p_spare_head;
	p_spare_tail = p_spare_head->p_prev;

	if(p_spare_tail == p_spare_head)
	{
		debug(0, "no spare node ");
		return p_spare_head;
	}

	if(p_spare_tail->p_prev == p_spare_head)
		p_spare_head->p_next = p_spare_head;

	else
	{
		p_spare_head->p_prev = p_spare_tail->p_prev;
		p_spare_head->p_prev->p_next = NULL;
	}

	return p_spare_tail;
	debug(1, "list_del_user tail\n");
}

/*when delet an node add a spare node to the list
**static void add_spare_node(List * p_list, struct ap_node * spare_node);
**当删除一个节点是，把删除的节点进行回收，即用链表记录下来
**参数p_list是一个链表指针，spare_node是被删除的节点的指针
**无返回值
*/
static void add_spare_node(List * p_list, struct ap_node * spare_node)
{
	struct ap_node * p_spare_head, * p_spare_tail;
	p_spare_head = p_list->p_spare_head;
	p_spare_tail = p_spare_head->p_prev;

	p_spare_tail->p_next = spare_node;
	spare_node->p_next = NULL;
	p_spare_head->p_prev = spare_node;
}

/*compare the array
**static int array_equal(char mac1[], char mac2[],int size);
**比较数组内容是否相等
**参数分别为两个字符数组和其大小
**返回值为0则不相等1则为相等
*/
static int array_equal(char mac1[], char mac2[],int size)
{
	int i = 0;

	while (i < size)
	{
		if(mac1[i] != mac2[i])
			return 0;
		i++;
	}

	return 1;
}

/*when searching the user ,use this to compare the mac address
**static int user_equal(AP_USER_ENTRY ap_user , struct ap_node * p_node);
**ap 用户节点比较是否相同，时比较其中的字符数组，要调用数组比较函数
**ap_user是一个用户节点的结构体，p_node则是用户节点结构体的指针
**返回值为0则不相等为1相等
*/
static int user_equal(AP_USER_ENTRY ap_user , struct ap_node * p_node)
{
	if(array_equal(p_node->ap_user.mac, ap_user.mac, USER_MAC_LEN))
	{
		//debug(1, "user equal");
		return 1;
	}
	else 
	{
		//debug(0, "user not equal")	;
		return 0;
	}
}

/*exchange the two array
**static void exch_arr(char mac1[], char mac2[], int size);
**交换两个字符数组的内容
**参数为两个字符数组和其大小
**无返回值
*/
static void exch_arr(char mac1[], char mac2[], int size)
{
	char tmp = 0;
	int i = 0;

	for(; i < size; i++)
	{
		tmp = mac1[i];
		mac1[i] = mac2[i];
		mac2[i] = tmp;
	}

}

/*copy the new user to the list
**static void copy_user(AP_USER_ENTRY ap_user, struct ap_node *p_node) ;
**拷贝要添加的用户结构体到用户指针所指向的结构体中
**ap_user为用户的结构体，p_node为用户结构体的指针
**无返回值
*/
static void copy_user(AP_USER_ENTRY ap_user, struct ap_node *p_node) 
{
	int i = 0;

	for (; i < USER_MAC_LEN ; i++)	
	{
		p_node->ap_user.mac[i] = ap_user.mac[i];
	}

	//debug(1,"copy user is ok");
}

/*init head node pointting itself
**int list_init(List * p_list, unsigned int max);
**初始化链表，对其中的链表结构体和两个头结构体进行初始化
**p_list链表指针，max为最大能添加的节点的数目
**成功则返回1
*/
int list_init(List * p_list, unsigned int max)
{
	struct ap_node * p_new_node;
	struct ap_node * p_new_spare_node;
	p_new_node =(struct ap_node *) (p_list + sizeof(List));
	p_new_spare_node =(struct ap_node *) (p_new_node + sizeof(struct ap_node));

	p_new_node->p_next = p_new_node;
	p_new_node->p_prev = p_new_node;

	p_new_spare_node->p_next = p_new_node;
	p_new_spare_node->p_prev = p_new_node;

	p_list->max = max;
	p_list->count = 0;
	p_list->count_spare = 0;
	p_list->p_head = p_new_node;
	p_list->p_spare_head = p_new_spare_node;

	debug(1, "list_init");
	return 1;

}

/*del from the bottom to the head ,last del the list 
**void list_del_link(List ** p_list);
**删除整个链表
**p_p_list为链表指针的指针
**无返回值
*/
void list_del_link(List ** p_p_list)
{
	free (*p_p_list);
	*p_p_list = NULL;
	debug((unsigned long)*(p_p_list), "list_del_link");
}

/*from the head to the tail,output the amc address
**int list_ergodic(List * p_list);
**对链表进行遍历
**p_list为链表指针
**不存在返回-1，没有用户返回0，正确遍历返回1
*/
int list_ergodic(List * p_list)
{
	if(p_list == NULL)
	{
		debug(-1, "list not exit");
		return -1;
	}

	debug(1, "ergodic --- start");

	struct ap_node * p_head, *p_tmp;
	unsigned int i = 0;

	debug(p_list->count, "count of user:");
	debug(p_list->max, "count of max:");

	p_head = p_list->p_head;
	p_tmp = p_head->p_next;

	if(p_tmp == p_head)
	{
		debug(1, "ergodic --- no user");
		return 0;
	}

	/*output all the user's mac
	 *输出所有用户的mac地址*/
	while(p_tmp)
	{
		debug(16, p_tmp->ap_user.mac);
		p_tmp = p_tmp->p_next;
	}

	debug(1, "ergodic --- ok\n");
	return 0;
}

/*seach the user'mac from the list
**struct ap_node * list_search(AP_USER_ENTRY ap_user, List * p_list);
**在链表中查找所给节点是否存在
**ap_user为要查找的节点，p_list为要查找的链表
**没有找到返回头结点，找到则返回找到的链表中节点指针
*/
struct ap_node * list_search(AP_USER_ENTRY ap_user, List * p_list)
{
	struct ap_node * p_head, *p_tmp;
	p_head = p_list->p_head;
	p_tmp = p_head->p_next;

	if(p_tmp == p_head)
	{
		debug(0, "list_search --- no user");
		return p_head;
	}

	while(p_tmp && !user_equal(ap_user,p_tmp))
	{
		debug(0, p_tmp->ap_user.mac);
		p_tmp = p_tmp->p_next;
	}

	if (!p_tmp)
	{
		debug(0, "list_search --- do not find it");
		return p_head;
	}

	debug(1, "list_search --- find it");
	debug(1, p_tmp->ap_user.mac);

	return p_tmp; 
}

/*sort th list ,only compare the array[0],increase
**List * list_sort(List *p_list);
**对链表进行排序。依据节点中字符数组的第一个字节的大小从小到大进行排序
**p_list要进行排序的链表指针
**返回链表指针
*/
List * list_sort(List *p_list)
{
	struct ap_node *p_head, *p_tmp, *p_tmp2;
	p_head = p_list->p_head;
	p_tmp = p_head->p_next;

	if(p_tmp == p_head)
	{
		debug(0, "no user\n");
		return p_list;
	}

	while (p_tmp->p_next)
	{
		p_tmp2 = p_head->p_prev;

		while (p_tmp2 != p_tmp)
		{
			debug(1, p_tmp->ap_user.mac);
			if(p_tmp2->ap_user.mac[0] < p_tmp2->p_prev->ap_user.mac[0])
			{
				exch_arr(p_tmp->ap_user.mac, p_tmp2->ap_user.mac, USER_MAC_LEN);
			}
			p_tmp2 = p_tmp2->p_prev;
		}

		p_tmp = p_tmp->p_next;
	}

	debug(1, "sort the list --- ok");
	return p_list;
}

/*add an user to the list's tail
**int list_add_user(AP_USER_ENTRY ap_user, List * p_list);
**添加新用户，没有空间则从空闲链表中获得
**ap_user为要添加的新用户，p_list为要添加的链表指针
**返回0则没有成功添加，为1则成功添加
*/
int list_add_user(AP_USER_ENTRY ap_user, List * p_list)
{
	struct ap_node * p_new_node, *p_head, *p_tail;
	p_head = p_list->p_head;
	p_tail = p_head->p_prev;
	unsigned long use_mem = (unsigned long) (p_tail - p_head);
	unsigned long size_mem = MEMERY_SIZE - 2* sizeof(struct ap_node);

	debug(use_mem,"use_mem");
	debug(size_mem,"size_mem");

	if(p_list->count == p_list->max )
	{
		debug(0, "count eq max.can not add user please delet first");
		return 0;
	}

	if(use_mem > size_mem)
	{
		debug(0, "memory no enough");
		p_new_node = get_spare_node(p_list);
		if(p_new_node == p_list->p_spare_head)
			return 0;
	}
	else
		p_new_node = (struct ap_node *) (p_tail + sizeof(struct ap_node));
	
	copy_user(ap_user, p_new_node);
	
	p_tail->p_next = p_new_node;
	p_new_node->p_prev = p_tail;
	p_new_node->p_next = NULL;
	p_head->p_prev= p_new_node;
	p_list->count++;

	debug(1, ap_user.mac);
	return 1;
}

/*delete an user from the tail
**List * list_del_user(AP_USER_ENTRY ap_user, List * p_list);
**删除指定用户的节点，然后把删除节点添加进空闲链表中
**ap_user是要删除的用户信息节点，p_list为要查找的链表
**返回链表节点
*/
List * list_del_user(AP_USER_ENTRY ap_user, List * p_list)
{
	struct ap_node  *p_head, *p_tail, *p_tmp;
	p_head = p_list->p_head;
	p_tail = p_head->p_prev;
	p_tmp = list_search(ap_user, p_list);
	//debug(1,p_tmp->ap_user.mac);

	if(p_tmp == p_head)
	{
		debug(0, "no user or no find it ");
		return p_list;
	}
	else if(p_tmp == p_tail)
	{
		/*only one user
		**只有一个用户*/
		if(p_tmp->p_prev == p_head)
		{
			p_head->p_prev = p_head;
			p_head->p_next = p_head;
		}
		else
		{
			p_head->p_prev = p_tmp->p_prev;
			p_head->p_prev->p_next = NULL;
		}
		debug(1, "list_del_user tail\n");
	}	
	else
	{
		p_tmp->p_prev->p_next = p_tmp->p_next;
		p_tmp->p_next->p_prev = p_tmp->p_prev;
		debug(1, "list_del_user tmp\n");
	}

	p_list->count --;
	add_spare_node(p_list,p_tmp);

	return p_list;
}
