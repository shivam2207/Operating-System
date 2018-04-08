#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int pf(int);
int fs,o; 
int main(int argc,char *argv[])
{
	int n,count=0,m,i;
	char c;
	char *p=argv[1];
	if(argc==2)
	{
		fs=open(argv[argc-1],O_RDONLY);
		if(fs<0)
			printf(":No such file or directory1\n");
		else if(fs==0)
			printf("file is empty\n");
		else
		{
			while((n=read(fs,&c,1))>0)//counting the number of lines
			{
				printf("%c",c);			
				if(c=='\n')
					count++;
			}
		}
		return(0);
	}
	else if(argc==3)
	{
		fs=open(argv[argc-1],O_RDONLY);
		if(fs<0)
			printf(":No such file or directory\n");
		else if(fs==0)
			printf("file is empty\n");
		else
		{
			if(*p=='-')
			{
				p++;
				m=atoi(p);
				o=pf(m);
				printf("\n");
				return(0);
			}
			else
			{
				m=atoi(p);
				if(m<*p)
				{
					printf("%d: No such file or directory\n",m);
					return(0);
				}		
			}
			
		}
	}
	else
	{
		p++;
		m=atoi(p);
		for(i=2;i<argc;i++)
		{
			fs=open(argv[i],O_RDONLY);
			if(fs<=0)
			printf(":No such file or directory");
			else
			{
				printf("::::::::::::::::::::\n");
				printf("%s\n",argv[i]);
				printf("::::::::::::::::::::\n");
				o=pf(m);
				printf("\n");
				//o=getchar();
			}
		}

	}
	return(0);
}

	int pf(int m)// printing the file
	{
		int count=0,n,flag=0;
		static int q;
		char static c;
		char p;		
		while((n=read(fs,&c,1))>0)
		{
			if(count<m)
			{
				printf("%c",c);			
				if(c=='\n')
					count++;
				if(count==m)
					flag=1;
			}
			
			else
			{				
				p=getchar();
				if(p=='\n')
				{	
					if(flag==1)
						printf("%c",c);
					while((n=read(fs,&c,1))>0 && c!='\n')	
					{
						printf("%c",c);	
					}
				}
				if(p=='q')
				{
					q=1;					
					return(0);
				}
				if(p==' ')
				{
					printf("%c",c);
					p=getchar();					
					int g=pf(m);
				}
				if(q==1)
					return(0);
			}
			if(q==1)
				return(0);
		}
		return 0;
	}
