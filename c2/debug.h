/*
*
*\file                  debug.h
*\brief                 头文件
*\detail				宏定义
*
*\author				王旭东
*\version				v1
*\date					2015.8.25
*
*/

#define IPIKE_CFG_INFO_ERROR(info,args...) \
	printf("[error]%s %d: "info, __FUNCTION__, __LINE__, ##args)
#define DEBUG

#ifdef DEBUG 
#define IPIKE_CFG_INFO_DEBUG(info,args...) \ printf("[debug]%s %d: "info, __FUNCTION__, __LINE__, ##args)
#define IPIKE_CFG_INFO_WARNING(info,args...) \ printf("[warning]%s %d: "info, __FUNCTION__, __LINE__, ##args)
#define IPIKE_CFG_INFO_INFO(info,args...) \
   printf("%s %d: "info, "\n", __FUNCTION__, __LINE__, ##args)
#else 
#define IPIKE_CFG_INFO_DEBUG(info,args...) 
#define IPIKE_CFG_INFO_WARNING(info,args...) 
#define IPIKE_CFG_INFO_INFO(info,args...) \
   printf("%s %d: "info, "\n",__FUNCTION__, __LINE__, ##args)
#endif
