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

int set_promisc(char *nif, int sock);

int main()  
{  
	char buf[BUF_SIZE] = {0}; 
	int	 sock = 0;
	unsigned int len = 0; 

	/*建立socke,*/
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) ;
	if(-1 == sock) 
		debug(-1, "socket");  

	debug(set_promisc("eth0", sock), "set_promisc"); 
	system("ifconfig");

	while(1)
	{	
		memset(buf , 0, BUF_SIZE);
		len = recvfrom(sock, buf, BUF_SIZE, 0, NULL, NULL);
		debug(len, "recvfrom");

		analy_pkt(buf, len);
		 
		perror("dump");
	} 
 
}

int set_promisc(char *nif, int sock )  
{  
	struct ifreq ifr;  
                
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, nif, strlen(nif) + 1);

	if(-1 == (ioctl(sock, SIOCGIFFLAGS, &ifr)))  //获得flag
	{         
		debug(-1, "ioctl_before");  
		return -1;
	}  
   
	ifr.ifr_flags |= IFF_PROMISC;  //重置flag标志
  
	if(-1 == ioctl(sock, SIOCSIFFLAGS, &ifr))  //改变模式
	{ 
		debug(-1, "ioctl_after");  
		return -1;
	}  
	return 0;
}  
