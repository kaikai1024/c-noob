#include <stdio.h>
#include <stdlib.h>
void debug(int n, char *info)  
{  
	switch (n)
	{
		case -1:
			perror(info);
			exit(n);  
			break;
		case 0:
			printf("\tinfo:---%s", info);
		case 1:
			printf("\t%s---start\n", info);
			break;
		case 2:
			printf("\t%s---end\n", info);
			break;
		default:
			printf("\t%s:%d---ok\n", info, n);
			break;
	}
} 
