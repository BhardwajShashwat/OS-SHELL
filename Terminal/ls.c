#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>



int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *dp;
	char *path = ".";
	struct stat st;
	struct passwd *us;
	struct group *gr;
	struct tm *tme;
	char cwd[1024];
	char temp[1024];


	getcwd(cwd,sizeof(cwd));
	strcat(cwd, "/");

	if (argc > 1)
	{
		if (argv[argc-1][0] != '-')
		{
			path = argv[argc-1];
		}
	}

	strcat(cwd, path);
	strcat(cwd, "/");

	if ((dir = opendir(path)) == NULL)
	{
		perror("Cannot open.");
		return 1;
	}

	int flag;
	int l=0, a=0;
	while((flag = getopt(argc, argv, "la")) != -1)
	{
		switch(flag) {
			case 'a':
				a=1;
				break;

			case 'l':
				l=1;
				break;

			default:
				break;
		}
	}

	if (l==1)
	{
		while ((dp = readdir(dir)) != NULL)
		{
			strcpy(temp, cwd);
			strcat(temp, dp->d_name);
			//printf("%s\n", temp);
			if ((stat(temp, &st)) == -1) printf("Failed to stat\n");
			/*ls -al or ls -la or ls -a -l or ls -l -a*/
			if (a==1)
			{
				printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
				printf( (st.st_mode & S_IRUSR) ? "r" : "-");
				printf( (st.st_mode & S_IWUSR) ? "w" : "-");
				printf( (st.st_mode & S_IXUSR) ? "x" : "-");
				printf( (st.st_mode & S_IRGRP) ? "r" : "-");
				printf( (st.st_mode & S_IWGRP) ? "w" : "-");
				printf( (st.st_mode & S_IXGRP) ? "x" : "-");
				printf( (st.st_mode & S_IROTH) ? "r" : "-");
				printf( (st.st_mode & S_IWOTH) ? "w" : "-");
				printf( (st.st_mode & S_IXOTH) ? "x" : "-");
				printf(" %lo ",st.st_nlink);
				us = getpwuid(st.st_uid);
				gr = getgrgid(st.st_gid);
				printf("%s ",us->pw_name);
				printf("%s ",gr->gr_name);
				printf("%ld ",st.st_size);
				tme = gmtime(&st.st_mtime);
				switch(tme->tm_mon){
					case 0:
						printf("Jan");
						break;
					case 1:
						printf("Feb");
						break;
					case 2:
						printf("Mar");
						break;
					case 3:
						printf("Apr");
						break;
					case 4:
						printf("May");
						break;
					case 5:
						printf("Jun");
						break;
					case 6:
						printf("Jul");
						break;
					case 7:
						printf("Aug");
						break;
					case 8:
						printf("Sep");
						break;
					case 9:
						printf("Oct");
						break;
					case 10:
						printf("Nov");
						break;
					case 11:
						printf("Dec");
						break;
				}
				printf(" ");
				printf("%d ",tme->tm_mday);
				printf("%d:",(tme->tm_hour)+1);
				printf("%d ",(tme->tm_min)+1);
				printf("%s\n",dp->d_name);
			}
			else
			{
				/*ls -l*/
				if (dp->d_name[0]!='.')
				{
					printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
					printf( (st.st_mode & S_IRUSR) ? "r" : "-");
					printf( (st.st_mode & S_IWUSR) ? "w" : "-");
					printf( (st.st_mode & S_IXUSR) ? "x" : "-");
					printf( (st.st_mode & S_IRGRP) ? "r" : "-");
					printf( (st.st_mode & S_IWGRP) ? "w" : "-");
					printf( (st.st_mode & S_IXGRP) ? "x" : "-");
					printf( (st.st_mode & S_IROTH) ? "r" : "-");
					printf( (st.st_mode & S_IWOTH) ? "w" : "-");
					printf( (st.st_mode & S_IXOTH) ? "x" : "-");
					printf(" %lo ",st.st_nlink);
					us = getpwuid(st.st_uid);
					gr = getgrgid(st.st_gid);
					printf("%s ",us->pw_name);
					printf("%s ",gr->gr_name);
					printf("%ld ",st.st_size);
					tme = gmtime(&st.st_mtime);
					switch(tme->tm_mon){
						case 0:
							printf("Jan");
							break;
						case 1:
							printf("Feb");
							break;
						case 2:
							printf("Mar");
							break;
						case 3:
							printf("Apr");
							break;
						case 4:
							printf("May");
							break;
						case 5:
							printf("Jun");
							break;
						case 6:
							printf("Jul");
							break;
						case 7:
							printf("Aug");
							break;
						case 8:
							printf("Sep");
							break;
						case 9:
							printf("Oct");
							break;
						case 10:
							printf("Nov");
							break;
						case 11:
							printf("Dec");
							break;
					}
					printf(" ");
					printf("%d ",tme->tm_mday);
					printf("%d:",(tme->tm_hour)+1);
					printf("%d ",(tme->tm_min)+1);
					printf("%s\n",dp->d_name);
				}
			}
		}
	}

	/*ls*/
	else if (a==0)
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_name[0] != '.')
			{
				printf("%s  ", dp->d_name);
			}
		}
		printf("\n");
	}

	/*ls -a*/
	else if (a==1)
	{
		while ((dp = readdir(dir)) != NULL)
		{
			printf("%s  ", dp->d_name);
		}
		printf("\n");
	}

	return 0;
}