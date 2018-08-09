#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include "exec.h"

void pipeHandler(char * args[]);


int exec(int argNo, char **argv)
{
	char path[100] = "/home/shashwat/os/assignment3/Terminal/";
	int i=0;

	pid_t pid = fork();

	if(pid == 0)	//ie. child process
	{
		//Making path for defined funcs
		char pwd[4] = "pwd";
		char cd[3] = "cd";
		char echo[5] = "echo";
		char ls[3] = "ls";
		char pinfo[6] = "pinfo";
		int fd0,fd1,fd2,in=0,out=0, outappend = 0;
		char input[64],output[64], outputapp[64];

		if(strcmp(argv[0], pwd) == 0) argv[0] = strcat(path, pwd);
		if(strcmp(argv[0], cd) == 0) argv[0] = strcat(path, cd);
		if(strcmp(argv[0], echo) == 0) argv[0] = strcat(path, echo);
		if(strcmp(argv[0], ls) == 0) argv[0] = strcat(path, ls);
		if(strcmp(argv[0], pinfo) == 0) argv[0] = strcat(path, pinfo);
		
		i=0;
		for(i=0; argv[i]!=NULL;i++)
		{
			if (strcmp(argv[i],"|") == 0)
			{
				pipeHandler(argv);
				return 1;
			}

			if(strcmp(argv[i],">")==0)
			{
				argv[i]=NULL;
				strcpy(output,argv[i+1]);
				out=1;
				continue;
			}  

			if(strcmp(argv[i],"<")==0)
			{     
				argv[i]=NULL;
				strcpy(input,argv[i+1]);
				in=1; 
				continue;
			}

			if(strcmp(argv[i],">>")==0)
			{ 
				argv[i]=NULL;
				strcpy(outputapp,argv[i+1]);
				outappend=1; 
 				continue;
			}
		}

		if(in)
		{   
			int fd0;
			if ((fd0 = open(input, O_RDONLY, 0)) < 0) 
			{
				perror("Couldn't open input file");
				exit(0);
			}           
			dup2(fd0, 0); 

			close(fd0); 
		}

		if (out)
		{

			int fd1 ;
			if ((fd1 = creat(output , 0644)) < 0) 
			{
				perror("Couldn't open the output file");
				exit(0);
			}           

			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}

		if (outappend)
		{
			int fd2 = open(outputapp,O_WRONLY|O_APPEND,0600);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);	
		}

		if(execvp(argv[0], argv) != -1)
		{
			return 0;
		}
		else
		{
			printf("Command not found\n");
			return -1;
		}

	}

	if(strcmp(argv[argNo-1], "&") != 0) wait(NULL);
	return 0;
}


void pipeHandler(char * args[]){
	int filedes[2];
	int filedes2[2];

	int num_cmds = 0;

	char *command[256];

	pid_t pid;

	int err = -1;
	int end = 0;

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	while (args[l] != NULL){
		if (strcmp(args[l],"|") == 0){
			num_cmds++;
		}
		l++;
	}
	num_cmds++;

	while (args[j] != NULL && end != 1){
		k = 0;
		while (strcmp(args[j],"|") != 0){
			command[k] = args[j];
			j++;	
			if (args[j] == NULL){
				end = 1;
				k++;
				break;
			}
			k++;
		}
		command[k] = NULL;
		j++;		

		if (i % 2 != 0){
			pipe(filedes); // for odd i
		}else{
			pipe(filedes2); // for even i
		}

		pid=fork();

		if(pid==-1){			
			if (i != num_cmds - 1){
				if (i % 2 != 0){
					close(filedes[1]); // for odd i
				}else{
					close(filedes2[1]); // for even i
				} 
			}			
			printf("Child process could not be created\n");
			return;
		}
		if(pid==0){
			if (i == 0){
				dup2(filedes2[1], STDOUT_FILENO);
			}
			else if (i == num_cmds - 1){
				if (num_cmds % 2 != 0){ // for odd number of commands
					dup2(filedes[0],STDIN_FILENO);
				}else{ // for even number of commands
					dup2(filedes2[0],STDIN_FILENO);
				}
			}else{ // for odd i
				if (i % 2 != 0){
					dup2(filedes2[0],STDIN_FILENO); 
					dup2(filedes[1],STDOUT_FILENO);
				}else{ // for even i
					dup2(filedes[0],STDIN_FILENO); 
					dup2(filedes2[1],STDOUT_FILENO);					
				} 
			}

			if (execvp(command[0],command)==err){
				kill(getpid(),SIGTERM);
			}		
		}

		if (i == 0){
			close(filedes2[1]);
		}
		else if (i == num_cmds - 1){
			if (num_cmds % 2 != 0){					
				close(filedes[0]);
			}else{					
				close(filedes2[0]);
			}
		}else{
			if (i % 2 != 0){					
				close(filedes2[0]);
				close(filedes[1]);
			}else{					
				close(filedes[0]);
				close(filedes2[1]);
			}
		}

		waitpid(pid,NULL,0);

		i++;	
	}
}