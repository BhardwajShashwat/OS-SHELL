#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <dirent.h>
#include "parse.h"
#include "exec.h"

#define BUFFSIZE 1024

void trim(char buffer[]);

int main()
{
	char home[100]="/home/shashwat";
// OS name
	struct utsname unamedata;
	if(uname(&unamedata) == -1)
	{
		printf("uname error\n");
		return -1;
	}

//Hostname
	char hostname[128];
	if(gethostname(hostname, 128) == -1)
	{
		printf("hostname error");
	}

//CWD
	char cwd[1024];

//Buffer
	char buffer[BUFFSIZE];
	char *pBuffer[BUFFSIZE];
	int i;
//Shell
	while(1)
	{
	//Update cwd
		if(getcwd(cwd, sizeof(cwd)) == NULL) printf("cwd error");
	//Get Line
		memset(buffer, '\0', sizeof(buffer));
		for(i=0; i<BUFFSIZE; i++) pBuffer[i] = NULL;
		printf("<%s@%s:%s>", hostname, unamedata.sysname, cwd);
		fgets(buffer, BUFFSIZE, stdin);
		trim(buffer);

	//Parse
		int argNo = parse(buffer, pBuffer);

	//Exit
		if(strcmp(pBuffer[0], "exit") == 0) break;

	//CD
		if(strcmp(pBuffer[0], "cd") == 0){
			if( argNo == 1 ||strcmp(pBuffer[1], "~") == 0 ) chdir(home);
		 	else chdir(pBuffer[1]);
		 	continue;
		 }

	//Execute
		exec(argNo, pBuffer);
	}
	


	return 0;
}






void trim(char buffer[])
{
	int i;
//First nonempty char
	for(i=0; i<BUFFSIZE; i++) if(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\0') break;
	int firstNonEmpty = i;
//Last nonempty char
	for(i=BUFFSIZE-1; i>=0; i--) if(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\0') break;
	int lastNonEmpty = i;
	for(i=0; i<=(lastNonEmpty - firstNonEmpty); i++)
	{
		buffer[i] = buffer[firstNonEmpty + i];
	}
	buffer[lastNonEmpty - firstNonEmpty +1] = '\0';
}