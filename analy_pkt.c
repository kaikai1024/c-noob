
#include "analy_pro.h"
#include "mailAnalysis.h"


int analy_pkt(char buf[], unsigned int len)
{

	struct ether_header *p_eth;
	struct ip *p_ip;
	struct arphdr *p_arp;
	struct tcphdr *p_tcp;
	struct udphdr *p_udp;
	struct icmphdr *p_icmp;
	char * tmp = NULL;
	unsigned short eth_type;
	list * from = initList();
	list * to = initList();

	if(len < sizeof(struct ether_header))
	{
		debug(0, "size < ethhdr");
		return 0;
	}
	p_eth = (struct ether_header *)buf;
	analy_ether(p_eth);
	eth_type = ntohs(p_eth->ether_type);
	
	if(ETHERTYPE_IP == eth_type )
	{
		if(len < sizeof(struct ether_header) + sizeof(struct ip))
		{
			debug(0, "size < ethhdr + iphdr");
			return 0;
		}
		p_ip = (struct ip *)(buf + sizeof (struct ether_header));
		analy_ip(p_ip);

		switch(p_ip->ip_p)
		{
			case IPPROTO_TCP:
					if(len < sizeof(struct ether_header)+sizeof(struct ip)+sizeof(struct tcphdr))
					{
						debug(0, "size < ethhdr + iphdr + tcphdr");
						return 0;
					}
					p_tcp = (struct tcphdr *)(buf + sizeof(struct ether_header) + sizeof(struct ip));
					analy_tcp(p_tcp);

					if(587 == p_tcp->source || 587 == p_tcp->dest)
					{
						debug(0, "\n\n\nsmtp\n\n\n");
						tmp = buf + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr);
						mailAnalysis(tmp,len,from,to);
					}

					if(110 == p_tcp->source || 110 == p_tcp->dest)
					{
						debug(0, "\n\n\npop\n\n\n");
						//tmp = buf + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr);
						//mailAnalysis(tmp,len);
					}

					break;

				case IPPROTO_UDP:
					if(len < sizeof(struct ether_header)+sizeof(struct ip)+sizeof(struct udphdr))
					{
						debug(0, "size < ethhdr + iphdr + udphdr");
						return 0;
					}
					p_udp = (struct udphdr *)(buf + sizeof(struct ether_header) +  sizeof(struct ip));
					analy_udp(p_udp);
					break;

				case IPPROTO_ICMP:
					if(len < sizeof(struct ether_header)+sizeof(struct ip)+sizeof(struct icmphdr))
					{
						debug(0, "size < ethhdr + iphdr + icmphdr");
						return 0;
					}
					p_icmp = (struct icmphdr *)(buf + sizeof(struct ether_header) + sizeof(struct ip));
					analy_icmp(p_icmp);
					break;
				default:
					debug(p_ip->ip_p, "ip--other");
					return 0;
					break;
		}
	}

	else if(ETHERTYPE_ARP == eth_type)
	{
		if(len < sizeof(struct ether_header) + sizeof(struct arphdr))
		{
			debug(0, "size < ethhdr + arphdr");
			return 0;
		}

		p_arp = (struct arphdr *)(buf + sizeof (struct ether_header));
		analy_arp(p_arp);
	}

	else if (ETHERTYPE_REVARP == eth_type)
	{
		if(len < sizeof(struct ether_header) + sizeof(struct arphdr))
		{
			debug(0, "size < ethhdr + arphdr");
			return 0;
		}
		p_arp = (struct arphdr *)(buf + sizeof (struct ether_header));
		analy_rarp(p_arp);
	}

	else
	{
		debug(eth_type, "ether--other");
		return 0;
	}

	return 0;	
}

