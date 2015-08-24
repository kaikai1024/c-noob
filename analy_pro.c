
#include "analy_pro.h"

void analy_ether(struct ether_header * p_eth)
{
	char *eth_type_str = NULL;
	unsigned short eth_type = ntohs(p_eth->ether_type);

	switch(eth_type)
	{
		case 0x0200:
			eth_type_str = "ETHERTYPE_PUP";
			break;
		case 0x0800:
			eth_type_str = "ETHERTYPE_IP";
			break;
		case 0x0806:
			eth_type_str = "ETHERTYPE_ARP";
			break;
		case 0x0835:
			eth_type_str = "ETHERTYPE_REVARP";
			break;
		default:
			eth_type_str = "Unrecognized";
			break;
	}

	debug(1,"analy eth...");
	
	printf("ether_dhost= %02X:%02X:%02X:%02X:%02X:%02X\n", p_eth->ether_dhost[0], p_eth->ether_dhost[1], p_eth->ether_dhost[2], p_eth->ether_dhost[3], p_eth->ether_dhost[4], p_eth->ether_dhost[5]);
	printf("ether_shost= %02X:%02X:%02X:%02X:%02X:%02X\n", p_eth->ether_shost[0], p_eth->ether_shost[1], p_eth->ether_shost[2], p_eth->ether_shost[3], p_eth->ether_shost[4], p_eth->ether_shost[5]);
	printf("ether_type=%#04x(%s)\n", eth_type, eth_type_str);
	
}

void analy_ip(struct ip * p_ip)
{
	debug(1, "analy ip...");
	char *p_str = NULL;
	unsigned char p = p_ip->ip_p;
	switch(p){
		case 0:
			p_str = "IPPROTO_IP";
			break;
		case 1:
			p_str = "IPPROTO_ICMP";
			break;
		case 2:
			p_str = "IPPROTO_IGMP";
			break;
		case 6:
			p_str = "IPPROTO_TCP";
			break;
		case 17:
			p_str = "IPPROTO_UDP";
			break;
		default:
			p_str = "Unrecognized";
			break;
	}

	printf("ip_hl 		= %u\n", p_ip->ip_hl << 2);
	printf("ip_v  		= %u\n", p_ip->ip_v);
	printf("ip_tos  	= %u\n", p_ip->ip_tos);
	printf("ip_len  	= %u\n", ntohs(p_ip->ip_len));
	printf("ip_id	= %u\n", ntohs(p_ip->ip_id));
	printf("ip_off  	= %u\n", ntohs(p_ip->ip_off));
	printf("ip_ttl  	= %u\n", p_ip->ip_ttl);
	printf("ip_p  		= %u(%s)\n", p, p_str);
	printf("ip_sum  	= %u\n", ntohs(p_ip->ip_sum));
	printf("ip_src  	= %s\n", inet_ntoa(p_ip->ip_src));
	printf("ip_dst  	= %s\n", inet_ntoa(p_ip->ip_dst));

	debug(2, "analy ip...");
}

void analy_arp(struct arphdr * p_arp)
{
	debug(1, "analy arp");
	debug(2, "analy arp");
}

void analy_rarp(struct arphdr * p_arp)
{
	debug(1, "analy rarp");
	debug(2, "analy rarp");
}

char * analy_tcp(struct tcphdr * p_tcp)
{
	debug(1, "analy tcp...")	;
	
	printf("source  = %u\n", ntohs(p_tcp->source));
	printf("dest  	= %u\n", ntohs(p_tcp->dest));
	printf("seq  		= %u\n", ntohl(p_tcp->seq));
	printf("ack_seq		= %u\n", ntohl(p_tcp->ack_seq));
	printf("res1  		= %u\n", p_tcp->res1);
	printf("doff  		= %u\n", p_tcp->doff);
	printf("fin  		= %u\n", p_tcp->fin);
	printf("syn  		= %u\n", p_tcp->syn);
	printf("rst  		= %u\n", p_tcp->rst);
	printf("psh  		= %u\n", p_tcp->psh);
	printf("ack  		= %u\n", p_tcp->ack);
	printf("urg  		= %u\n", p_tcp->urg);
	printf("res2  		= %u\n", p_tcp->res2);
	printf("window  	= %u\n", ntohs(p_tcp->window));
	printf("check		= %u\n", ntohs(p_tcp->check));
	printf("urg  		= %u\n", ntohs(p_tcp->urg_ptr));

	debug(2, "analy tcp...")	;
}

void analy_udp(struct  udphdr * p_udp)
{
	debug(1, "analy udp...")	;

	printf("source  	= %u\n", ntohs(p_udp->source));
	printf("dest  		= %u\n", ntohs(p_udp->dest));
	printf("len  		= %u\n", ntohs(p_udp->len));
	printf("check		= %u\n", ntohs(p_udp->check));

	debug(2, "analy udp...")	;
}

void analy_icmp(struct icmphdr * p_icmp)
{
	debug(1, "analy icmp...");

	printf("type		= %u\n", p_icmp->type);
	printf("code		= %u\n", p_icmp->code);
	printf("checksum	= %u\n", ntohs(p_icmp->checksum));

	debug(2, "analy icmp...");
}
