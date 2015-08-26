/*
*
*\file                  get_pkt.c
*\brief                 源文件
*\detail				获得数据包
*
*\author				冯开开
*\version				v1
*\date					2015.8.25
*
*/
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <unistd.h>  

#include <sys/socket.h>  
#include <sys/ioctl.h>  

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>

#define BUF_SIZE (2048)
#define SUCCESS  (0)
#define FAULSE   (-1)

int set_promisc(char *nif, int sock);

int main()  
{  
	char buf[BUF_SIZE] 	= {0}; 
	int	 sock 			= 0;
	int  promisc_flag	= 0;
	int  len 			= 0; 

	/*建立socke,*/
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) ;
	if(-1 == sock) 
	{
		IPIKE_CFG_INFO_ERROR("socket");  
	}

	promisc_flag = set_promisc("eth0", sock) ; 
	promisc_flag = set_promisc("eth1", sock) ; 
	if(-1 == promisc_flag)
	{
		IPIKE_CFG_INFO_ERROR("set_promisc failed"); 
	}

	system("ifconfig");

	while(1)
	{	
		memset(buf , 0, BUF_SIZE);
		len = recvfrom(sock, buf, BUF_SIZE, 0, NULL, NULL);
		if( -1 == len)
		{
			IPIKE_CFG_INFO_ERROR("receive nothing");  
			return FAULSE;
		}
		IPIKE_CFG_INFO_INFO("recvfrom:%d", len);

		analy_pkt(buf, len);
		sleep(1);
		perror("dump");
	} 
 
}

int set_promisc(char *nif, int sock )  
{  
	struct ifreq ifr;  
                
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, nif, strlen(nif) + 1);
 
	if(-1 == (ioctl(sock, SIOCGIFFLAGS, &ifr)))  
	{         
		IPIKE_CFG_INFO_ERROR( "ioctl_before");  
		return FAULSE;
	}  
   
	ifr.ifr_flags |= IFF_PROMISC;  
  
	if(-1 == ioctl(sock, SIOCSIFFLAGS, &ifr)) 
	{ 
		IPIKE_CFG_INFO_ERROR( "ioctl_after");  
		return FAULSE;
	}  

	return SUCCESS;
}  
