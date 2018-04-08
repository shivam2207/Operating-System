#include<sstream>
void DISPLAY_HISTORY();
void DISPLAY_HISTORY(int input);
int GET_COUNT();
string to_string(int num)
{
	ostringstream ss;
	ss<<num;
	string n=ss.str();
	return n;
}

string PARSE_COMMAND(string input)
{
	char command[1000];
	int pos=0;
	while((input[pos]>='0' && input[pos]<='9') || input[pos]==' ')
	{
		pos++;
	}
	strcpy(command,&input[pos]);
	string ret(command);
	return ret;
}

string GET_COMMAND(int input)
{
	string command;
	char buff[1000];
	char history_path[1000];
	strcpy(history_path,getenv("HOME"));
	strcat(history_path,"/history.txt");
	char count_path[1000];
	strcpy(count_path,getenv("HOME"));
	strcat(count_path,"/count.txt");
	int count=GET_COUNT();
	FILE *fp=fopen(history_path,"r");
	if(input<0)
	{
		input=input* -1;
		input=(count-input)-1;
		while(input>0)
		{
			fgets(buff, 1000, fp);
			input--;
		}
		fgets(buff, 1000, fp);
		fclose(fp);
		string str(buff);
		return str;   
	}
	else
	{
		while(input>0)
		{
			fgets(buff, 1000, fp);
			input--;
		}
		fclose(fp);
		string str(buff);
		return str;   
	}
}

string GET_COMMAND(string comm)
{
	string command;
	int len=comm.length();
	char buff[1000];
	char history_path[1000];
	strcpy(history_path,getenv("HOME"));
	strcat(history_path,"/history.txt");
	FILE *fp=fopen(history_path,"r");
	while(fgets(buff,1000,fp))
	{
		string temp=PARSE_COMMAND(string(buff));
		string tmp=temp.substr(0,len);
		if(tmp.compare(comm)==0)
		{
			command=string(buff);
		}
	}
	fclose(fp);
	return command;
}

string PARSE_HISTORY_INPUT(string input)
{
	string command;
	char num[100];
	int pos=0;
	while(input[pos]==' ')
	{
		pos++;
	}
	pos++;
	if(input[pos]=='!')
	{
		command=GET_COMMAND(-1);
	}
	else if(input[pos]=='-')
	{
		pos++;
		strcpy(num,&input[pos]);
		command=GET_COMMAND(0-atoi(num));
	}
	else
	{
		strcpy(num,&input[pos]);
		if(num[0]>='a' && num[0]<='z')
		{
			command=GET_COMMAND(string(num));
		}
		else
		{
			command=GET_COMMAND(atoi(num));
			cout<<command<<endl;
		}
	}
	return PARSE_COMMAND(command);

}

void CREATE_HISTORY()
{
	char history_path[1000];
	char count_path[1000];
	strcpy(history_path,getenv("HOME"));
	strcat(history_path,"/history.txt");
	strcpy(count_path,getenv("HOME"));
	strcat(count_path,"/count.txt");
	FILE *fp=fopen(history_path,"a");
	fclose(fp);
	if( access(count_path, F_OK ) == -1 ) 
	{
		fp=fopen(count_path,"w");
		fprintf(fp,"1");
		fclose(fp);
	}
}
void DISPLAY_HISTORY(int input)
{
	char buff[1000];
	char history_path[1000];
	strcpy(history_path,getenv("HOME"));
	strcat(history_path,"/history.txt");
	char count_path[1000];
	strcpy(count_path,getenv("HOME"));
	strcat(count_path,"/count.txt");
	int count=GET_COUNT();
	if(input>=count)
	{
		DISPLAY_HISTORY();   
	}
	else
	{
		FILE *fp=fopen(history_path,"r");
		if(input<0)
		{
			input=input* -1;
			if(input>=count)
			{
				DISPLAY_HISTORY();
			}
			else
			{
				input=count-input+1;
				while(input>0)
				{
					fgets(buff, 1000, fp);
					input--;
				}
				while(fgets(buff, 1000, fp)!=NULL)
				{
					cout<<buff;
				}
				fclose(fp);
			}
		}
		else
		{
			while(input>0)
			{
				fgets(buff, 1000, fp);
				cout<<buff;
				input--;
			}
			fclose(fp);
		}
	}
}
int GET_COUNT()
{
	char count_path[1000];
	strcpy(count_path,getenv("HOME"));
	strcat(count_path,"/count.txt");
	char buff[1000];
	FILE *fp = fopen(count_path, "r");
	fscanf(fp, "%s", buff);
	fclose(fp);
	return atoi(buff);
}

void UPDATE_COUNT()
{
	char count_path[1000];
	strcpy(count_path,getenv("HOME"));
	strcat(count_path,"/count.txt"); 
	char buff[1000];
	FILE *fp = fopen(count_path, "r");
	fscanf(fp, "%s", buff);
	fclose(fp);
	int count=atoi(buff)+1;
	fp = fopen(count_path, "w");
	fprintf(fp,"%s",(to_string(count)).c_str());
	fclose(fp);
}

void RECORD_HISTORY(string input)
{
	if(input.length()!=0)
	{
		char format[1000];
		char history_path[1000];
		strcpy(history_path,getenv("HOME"));
		strcat(history_path,"/history.txt");
		int count=GET_COUNT();
		UPDATE_COUNT();
		strcpy(format,(to_string(count)).c_str());
		strcat(format,"  ");
		strcat(format,input.c_str());
		strcat(format,"\n");
		FILE *fp=fopen(history_path,"a");
		fprintf(fp,"%s",format);
		fclose(fp);
	}
}

void DISPLAY_HISTORY()
{
	char buff[1000];
	char history_path[1000];
	strcpy(history_path,getenv("HOME"));
	strcat(history_path,"/history.txt");
	FILE *fp = fopen(history_path, "r");
	while(fgets(buff, 1000, fp)!=NULL)
	{
		cout<<buff;
	}
}
