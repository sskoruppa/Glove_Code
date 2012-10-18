#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char* argv[])
{
short data;

if(argc<2)
{
printf("Usage\n\n");
printf("partest1.exe ,,\n\n\n");
return 0;
}

if(!strcmp(argv[1],"read"))
{
data = _inp(atoi(argv[2])); 
printf("Data read from parallel port is  ");
printf("%d\n\n\n\n",data);
}

if(!strcmp(argv[1],"write"))
{
_outp(atoi(argv[2]),atoi(argv[3])); 
printf("Data written to parallel port is  ");
printf("%s\n\n\n\n\n",argv[3]);
}
return 0;
}