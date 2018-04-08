#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
int nol(char*);
int noc(char*);
int now(char*);
int lol(char*);
int op(char*);
int count,fs,n;
char c;
//simulate wc
int main(int argc,char *argv[])
{
	int nl,nc,nw,ll,nb,i,c;
	int fnl=0,fnc=0,fnw=0,fll=0,fnb=0;
	char *p;	
	if(argc==2)
	{
		fnl=1;
		fnc=1;
		fnw=1;
	}
	if(argc==3)
	{
		p=argv[1];
		++p;
		while(p!=argv[2])
		{
			c=*p;
			if(c=='l')
				fnl=1;
			if(c=='w')
				fnw=1;
			if(c=='c')
				fnc=1;
			if(c=='m')
				fnb=1;
			if(c=='L')
				fll=1;
			p++;
		}
	}
	else
	{	
		for(i=1;i<argc-1;i++)
		{
			p=argv[i];
			++p;
			if(*p=='l')
				fnl=1;
			if(*p=='w')
				fnw=1;
			if(*p=='c')
				fnc=1;
			if(*p=='m')
				fnb=1;
			if(*p=='L')
				fll=1;
		}
	}

								
	if(fnl==1)
	{		
		nl=nol(argv[argc-1]);
		printf(" %d",nl);
	}

	if(fnw==1)
	{
		nw=now(argv[argc-1]);
		printf(" %d",nw);
	}
	
	if(fnc==1)
	{
		nc=noc(argv[argc-1]);
		printf(" %d",nc);
	}
	
	if(fnb==1)
	{
		nb=noc(argv[argc-1]);
		printf(" %d",nb);
	}
	
	if(fll==1)
	{
		ll=lol(argv[argc-1]);
		printf(" %d",ll);
	}
	printf(" %s\n",argv[argc-1]);
	return(0);
}

	int nol(char *b)// number of lines.
	{
		count=0;
		fs=op(b);		
		while((n=read(fs,&c,1))>0)
		{
			if(c=='\n')
				count++;
		}
		return count;
	}

	int noc(char *b)// number of character
	{
		count=0;
		fs=op(b);	
		while((n=read(fs,&c,1))>0)
		{
			count++;
		}
		return(count);
	}

	int now(char *b)// number of words
	{
		int flag=0;
		count=0;
		fs=op(b);
		while((n=read(fs,&c,1))>0)
		{
			if(c==' '||c=='\n'||c=='\t')
			{	
				if(flag==0)
				{
					count++;
					flag=1;
				}			
			}
			else
				flag=0;
		}
		return(count);
	}
	
	int lol(char *b)//length of longestline
	{
		int max=0;
		count=0;
		fs=op(b);		
		while((n=read(fs,&c,1))>0)
		{
			count++;
			if(c=='\n')
			{
				if(max<count)
					max=count;
				else
					max=max;
				count=0;
			}
		}
		return(max-1);
	}

	int op(char *b)
	{
		fs=open(b,O_RDONLY);
		return(fs);
	}
