
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>  
#include <netinet/ip.h>  
#include <netinet/tcp.h>  
#include <netinet/udp.h> 
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <arpa/inet.h>   
#include <sys/types.h>

void analy_ether(struct ether_header * p_eth);
void analy_ip(struct ip * p_ip);
void analy_arp(struct arphdr * p_arp);
void analy_rarp(struct arphdr * p_arp);
char * analy_tcp(struct tcphdr * p_tcp);
void analy_udp(struct  udphdr * p_udp);
void analy_icmp(struct icmphdr * p_icmp);
