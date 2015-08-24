#include "list.h"

#define FROM       1
#define TO         2
#define LENDATE    4
#define WRONGMESG  0
#define RIGHT      1

int mailAnalysis(char *mailData, int mailSize, list *fromList, list *toList);

char *searchLocal(char *Data,int numb);

void recordMessage(char *pData,char data[], int size);

int _strcmp(char *str1, char *str2, int len);
