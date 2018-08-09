#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int pwd()
{
	char pwd[1024];
	if(getcwd(pwd, sizeof(pwd)) == NULL)
	{
		printf("PWD error\n");
		return -1;
	}
	else
	{
		printf("%s\n", pwd);
		return 0;
	}
}




int main(int argc, char const **argv)
{
	if(argc != 1)
	{
		printf("1 args req\n");
		return -1;
	}

	pwd();

	
	return 0;
}