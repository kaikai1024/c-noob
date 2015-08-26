#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*各层协议头定义*/
#include <netinet/in.h>  
#include <netinet/ip.h>  
#include <netinet/tcp.h>  
#include <netinet/udp.h> 
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <arpa/inet.h>   
#include <sys/types.h>

/*分析链路层协议*/
void analy_ether(struct ether_header * p_eth);
/*分析ip协议*/
void analy_ip(struct ip * p_ip);
/*分析arp协议*/
void analy_arp(struct arphdr * p_arp);
/*分析rarp协议*/
void analy_rarp(struct arphdr * p_arp);
/*分析tcp协议*/
char * analy_tcp(struct tcphdr * p_tcp);
/*分析udp协议*/
void analy_udp(struct  udphdr * p_udp);
/*分析icmp协议*/
void analy_icmp(struct icmphdr * p_icmp);
