#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <limits.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "execute.h"
#include "parser.h"
#include "history.h"
#include "export.h"
#include "redirect.h"
using namespace std;
static string input;
void PARSE_COMMAND(vector<string> pipe_split);
void sigintHandler(int sig_num)
{
	signal(SIGINT, sigintHandler);       
}

void PARSE_COMMAND(vector<string> pipe_split)
{
	vector<string> space_split;
	vector<string>::iterator over_pipe;
	vector<string>::iterator over_space;
	int i=0;
	int status;
	for(over_pipe=pipe_split.begin();over_pipe+1!=pipe_split.end();over_pipe++)
	{
		int inp=0;
		int op=0;
		int pos=0;
		while((*over_pipe)[pos]!='\0')
		{
			if((*over_pipe)[pos]=='<')
			{
				inp=1;
			}
			else if((*over_pipe)[pos]=='>')
			{
				op=1;
			}
			pos++;
		}
		if(inp==0 && op==0)
		{
			space_split=PARSE_STRING(*over_pipe,' ');
			if(space_split[0].compare("echo")==0 && space_split[1][0]=='$')
			{
				cout<<getenv(&space_split[1][1])<<endl;
			}
			else if((space_split[0]).compare("history")==0)
			{
				int cid=0;
				int pd[2];
				pipe(pd);
				if((cid=fork())==0)
				{
					close(1);
					dup2(pd[1],1);
					if(space_split.size()==1)
					{
						DISPLAY_HISTORY();
					}
					else
					{
						DISPLAY_HISTORY(0-atoi(space_split[1].c_str()));
					}
					exit(0);
				}
				else
				{
					waitpid(cid,NULL,0);
					dup2(pd[0],0);
					close(pd[1]);
				}
			}
			else if(space_split[0].compare("exit")==0)
			{
				kill(0,SIGTERM);
				kill (getppid(), SIGKILL);
				abort();
				exit(0); 
			}
			else if(space_split[0].compare("export")==0)
			{
				int pd[2];
				pipe(pd);
				if(!fork())
				{
					close(1);
					dup2(pd[1],1);
					if(space_split.size()==1)
					{
						EXPORT();
					}
					else
					{
						SET_ENV(space_split[1]);
					}
					exit(0);
				}
				wait(&status);
				dup2(pd[0],0);
				close(pd[1]);
			}
			else
			{
				char *command[1000];
				for(int i=0;i<1000;i++)
				{
					command[i]='\0';
				}
				TOKENIZE_COMMAND(space_split,command);
				EXECUTE_COMMAND(command);
			}
		}
		else
		{
			REDIRECT(*over_pipe);
		}
	}
	int inp=0;
	int op=0;
	int pos=0;
	while((*over_pipe)[pos]!='\0')
	{
		if((*over_pipe)[pos]=='<')
		{
			inp=1;
		}
		else if((*over_pipe)[pos]=='>')
		{
			op=1;
		}
		pos++;
	}
	if(inp==0 && op==0)
	{
		space_split=PARSE_STRING(*over_pipe,' ');
		if(space_split[0].compare("echo")==0 && space_split[1][0]=='$')
		{
			cout<<getenv(&space_split[1][1])<<endl;
		}
		else if(space_split[0].compare("export")==0)
		{
			if(space_split.size()==1)
			{
				EXPORT();
			}
			else
			{
				SET_ENV(space_split[1]);
			}
			exit(0);
		}
		else if(space_split[0].compare("cd")==0)
		{
			if(space_split.size()==1 || space_split[1].compare("~")==0)
			{
				char *home=getenv("HOME");
				chdir(home);
			}
			else
			{
				char *home=new char[1000];
				strcpy(home,space_split[1].c_str());
				chdir(home);
			}
		}
		else if(space_split[0].compare("history")==0)
		{
			if(space_split.size()==1)
			{
				DISPLAY_HISTORY();
			}
			else
			{
				DISPLAY_HISTORY(0-atoi(space_split[1].c_str()));
			}
			exit(0);
		}
		else if(space_split[0].compare("exit")==0)
		{
			kill(0,SIGTERM);
			kill (getppid(), SIGKILL);
			abort();
			exit(0); 
		}
		else
		{
			char *command[1000];
			for(int i=0;i<1000;i++)
			{
				command[i]='\0';
			}
			TOKENIZE_COMMAND(space_split,command);
			execvp(command[0],command);
			abort();
		}
	}
	else
	{
		REDIRECT_NO_PIPE(*over_pipe);
		//  REDIRECT(*over_pipe);
	}
}

int main()
{
	int pid=0;
	CREATE_HISTORY();
	signal(SIGINT, sigintHandler);
	int status;
	int temp;
	vector<string> pipe_split;
	while(1)
	{
		if((pid=fork())==0)
		{
			string command;
			string cwd;
			char buff[PATH_MAX+1];
			cwd=getcwd(buff,PATH_MAX+1);
			cout<<"MyShell:@shivam"<<buff<<"$";
			getline(cin,input);
			if(strcmp("exit",input.c_str())==0)
			{
				RECORD_HISTORY(input);
				while(1)
				{
					kill(0,SIGTERM);
					kill (getppid(), SIGKILL);
					abort();
					exit(0);
				}
			}
			if(input.length()==0)
			{
				exit(0);
			}
			else
			{
				int pos=0;
				while(input[pos]==' ')
				{
					pos++;
				}
				if(input[pos]=='!')
				{
					command=PARSE_HISTORY_INPUT(input);
					command=command.substr(0,command.length()-1);
					RECORD_HISTORY(command);
					pipe_split=PARSE_STRING(command,'|');
					PARSE_COMMAND(pipe_split);
				}
				else
				{
					RECORD_HISTORY(input);
					pipe_split=PARSE_STRING(input,'|');
					PARSE_COMMAND(pipe_split);
				}
			}
		}
		else
		{
			waitpid(pid,NULL,0);
		}
	}
	return 0;
}