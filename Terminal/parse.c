#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "parse.h"

int parse(char *buffer, char **pBuffer)
{
	pBuffer[0] = strtok(buffer, " ");

	int i;
	for(i=1; pBuffer[i-1] != NULL; i++)
	{
		pBuffer[i] = strtok(NULL, " ");
	}

	return i-1;
}