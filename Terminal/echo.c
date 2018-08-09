#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int echo(int argNo, char **pBuffer)
{
	int i;
	for(i=1; i<=argNo-1; i++) if(strcmp(pBuffer[i],"&")!=0){
		printf("%s ",pBuffer[i]);
		if (strcmp(pBuffer[i],">")==0) break;
		if (strcmp(pBuffer[i],">>")==0) break;

	}
	printf("\b\n");
	return 0;
}



int main(int argc, char **argv)
{
	int argNo=0;

	while(argv[argNo] != NULL)
	{
		argNo++;
	}
	echo(argNo, argv);
	return 0;
}
