/*
*
*\file                  analy_pkt.c
*\brief                 源文件
*\detail				分析数据包
*
*\author				冯开开
*\version				v1
*\date					2015.8.25
*
*/
#include "analy_pro.h"
#include "mailAnalysis.h"
#include "debug.h"

#define SUCCESS (0)

/*
 *\fn					int analy_pkt(char buf[], unsigned int len);
 *\brief				分析包
 *\details				通过指针到移动依次分析包到结构
 *
 *
 *\param(in)			buf字符数组，数据包到长度
 *\param(out)			
 *
 *\return				void
 *\retval
 *
 * \note
 * */
int analy_pkt(char buf[], unsigned int len)
{

	struct ether_header *p_eth;
	struct ip *p_ip;
	struct arphdr *p_arp;
	struct tcphdr *p_tcp;
	struct udphdr *p_udp;
	struct icmphdr *p_icmp;

	char * tmp 				= NULL;
	unsigned short eth_type = 0;

	list * from = initList();
	list * to   = initList();

	if(len < sizeof(struct ether_header))
	{
		IPIKE_CFG_INFO_INFO("size < ethhdr");
		return SUCCESS;
	}

	p_eth	 = (struct ether_header *)buf;
	eth_type = ntohs(p_eth->ether_type);
	//analy_ether(p_eth);
	
	if (ETHERTYPE_IP == eth_type)
	{
		if (len < sizeof(struct ether_header) + sizeof(struct ip))
		{
			IPIKE_CFG_INFO_INFO("size < ethhdr + iphdr");
			return SUCCESS;
		}

		p_ip = (struct ip *)(buf + sizeof (struct ether_header));
		//analy_ip(p_ip);

		switch ( p_ip->ip_p )
		{
		case IPPROTO_TCP:
			if(len < sizeof(struct ether_header) + sizeof(struct ip)+sizeof(struct tcphdr))
		    {
		    	IPIKE_CFG_INFO_INFO("size < ethhdr + iphdr + tcphdr");
				return SUCCESS;
			}
			p_tcp = (struct tcphdr *)(buf + sizeof(struct ether_header) + sizeof(struct ip));
			analy_tcp(p_tcp);

			if(587 == ntohs( p_tcp->source) || 587 == ntohs(p_tcp->dest) )
			{
				IPIKE_CFG_INFO_INFO("\n\n\nsmtp\n\n\n");
				tmp = buf + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr);
				mailAnalysis(tmp, len, from, to);
			}

			if(110 == ntohs(p_tcp->source) || 110 == ntohs(p_tcp->dest) )
			{
				IPIKE_CFG_INFO_INFO("\n\n\npop\n\n\n");
			}
			break;

		case IPPROTO_UDP:
			if(len < sizeof(struct ether_header)+sizeof(struct ip) + sizeof(struct udphdr))
			{
				IPIKE_CFG_INFO_INFO("size < ethhdr + iphdr + udphdr");
				return SUCCESS;
			}
			p_udp = (struct udphdr *)(buf + sizeof(struct ether_header) +  sizeof(struct ip));
			//analy_udp(p_udp);
			break;

		case IPPROTO_ICMP:
			if(len < sizeof(struct ether_header)+sizeof(struct ip)+sizeof(struct icmphdr))
			{
				IPIKE_CFG_INFO_INFO("size < ethhdr + iphdr + icmphdr");
				return SUCCESS;
			}

			p_icmp = (struct icmphdr *)(buf + sizeof(struct ether_header) + sizeof(struct ip));
			analy_icmp(p_icmp);
			break;
		default:
			IPIKE_CFG_INFO_INFO("ip--other");
			return SUCCESS;
		}

	}

	else if(ETHERTYPE_ARP == eth_type)
	{
		if(len < sizeof(struct ether_header) + sizeof(struct arphdr))
		{
			IPIKE_CFG_INFO_INFO("size < ethhdr + arphdr");
			return SUCCESS;
		}

		p_arp = (struct arphdr *)(buf + sizeof (struct ether_header));
		analy_arp(p_arp);
	}

	else if (ETHERTYPE_REVARP == eth_type)
	{
		if(len < sizeof(struct ether_header) + sizeof(struct arphdr))
		{
			IPIKE_CFG_INFO_INFO("size < ethhdr + arphdr");
			return SUCCESS;
		}

		p_arp = (struct arphdr *)(buf + sizeof (struct ether_header));
		analy_rarp(p_arp);
	}

	else
	{
		IPIKE_CFG_INFO_INFO("ether--other");
		return SUCCESS;
	}

	return SUCCESS;	
}

