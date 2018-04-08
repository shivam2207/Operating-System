#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<string.h>
#include<limits.h>
#include<vector>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void TOKENIZE_COMMAND(vector<string> space_split,char *command[])
{
	int i=0;
	vector<string>::iterator over_space;
	for(over_space=space_split.begin();over_space!=space_split.end();over_space++)
	{
		command[i]=new char[2000];
		strcpy(command[i],(*over_space).c_str());
		i++;          
	}
}

void EXECUTE_COMMAND(char *command[])
{
	int pd[2];
	pipe(pd);
	if(!fork())
	{
		close(1);
		dup2(pd[1],1);
		execvp(command[0],command);
		abort();
	}
	wait(0);
	dup2(pd[0],0);
	close(pd[1]);
}

void EXECUTE_COMMAND_FORK(char *command[],int fd0,int fd1)
{
	int pd[2];
	pipe(pd);
	if(!fork())
	{
		if(fd0!=0)
		{
			dup2(fd0,STDIN_FILENO);
		}
		if(fd1!=0)
		{
			dup2(fd1,STDOUT_FILENO);
		}
		close(1);
		dup2(pd[1],1);
		execvp(command[0],command);
		abort();
	}
	wait(0);
	dup2(pd[0],0);
	close(pd[1]);
}
