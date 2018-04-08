string PARSE_REDIRECT(string input)
{
	vector<char> token;
	int pos=0;
	while(input[pos]!='\0')
	{
		if(input[pos]=='<' || input[pos]=='>')
		{
			token.push_back(input[pos]);
			token.push_back(' ');
			pos++;
		}
		else if(input[pos+1]=='<' || input[pos+1]=='>')
		{
			token.push_back(input[pos]);
			token.push_back(' ');
			pos++;
		}
		else
		{
			token.push_back(input[pos]);
			pos++;
		}
	}
	string s(token.begin(),token.end());
	return s;
}

void REDIRECT(string input)
{
	int pd[2];
	pipe(pd);
	if(!fork())
	{
int fd0=0;
int fd1=0;
	char  *command[1000];
	string com;
	int i=0;
	for(int i=0;i<1000;i++)
	{
		command[i]='\0';
	}
	char input_source[1000];
	char output_source[1000];
	vector<string> space_split;
	vector<string>::iterator over_space;
	com=PARSE_REDIRECT(input);
	space_split=PARSE_STRING(com,' ');
	for(over_space=space_split.begin();over_space!=space_split.end();over_space++)
	{
		if((*over_space).compare("<")==0)
		{
			strcpy(input_source,(*(over_space+1)).c_str());
		}
		else if((*over_space).compare(">")==0)
		{
			strcpy(output_source,(*(over_space+1)).c_str());
		}
	}
	for(over_space=space_split.begin();over_space!=space_split.end();over_space++)
	{
		if((*over_space).compare("<")==0 || (*over_space).compare(">")==0)
		{
			over_space=over_space+1;
		}
		else
		{
			command[i]=new char[1000];
			strcpy(command[i],(*over_space).c_str());
			i++;
		}
	}
	
   close(1);
		dup2(pd[1],1);
if(strlen(input_source)!=0)
	{
		fd0 = open(input_source,O_RDONLY);
		dup2(fd0, STDIN_FILENO);
		close(fd0);
	}
	if (strlen(output_source)!=0)
	{
		fd1 = creat(output_source, 0666) ;
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
	}
		
		execvp(command[0],command);
		abort();
	}
	wait(0);
	dup2(pd[0],0);
	close(pd[1]);
	//EXECUTE_COMMAND(command);
}

void REDIRECT_NO_PIPE(string input)
{
	string com;
	char  *command[1000];
	int i=0;
	char input_source[1000];
	char output_source[1000];
	for(int i=0;i<1000;i++)
	{
		command[i]='\0';
	}
	vector<string> space_split;
	vector<string>::iterator over_space;
	com=PARSE_REDIRECT(input);
	space_split=PARSE_STRING(com,' ');
	for(over_space=space_split.begin();over_space!=space_split.end();over_space++)
	{
		if((*over_space).compare("<")==0)
		{
			strcpy(input_source,(*(over_space+1)).c_str());
		}
		else if((*over_space).compare(">")==0)
		{
			strcpy(output_source,(*(over_space+1)).c_str());
		}
	}
	for(over_space=space_split.begin();over_space!=space_split.end();over_space++)
	{
		if((*over_space).compare("<")==0 || (*over_space).compare(">")==0)
		{
			over_space=over_space+1;
		}
		else
		{
			command[i]=new char[1000];
			strcpy(command[i],(*over_space).c_str());
			i++;
		}
	}
	if(strlen(input_source)!=0)
	{
		int fd0 = open(input_source,O_RDONLY);
		dup2(fd0, STDIN_FILENO);
		close(fd0);
	}
	if (strlen(output_source)!=0)
	{
		int fd1 = creat(output_source, 0666) ;
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
	}
	execvp(command[0],command);
	abort();
}