extern char **environ;
void SET_ENV(string env_var)
{
	char *env=new char[2000];
	strcpy(env,env_var.c_str());
	// cout<<"env= "<<env<<endl;
	putenv(env);
}

void EXPORT()
{
	vector<string> exp;
	vector<string>::iterator it;
	int count=0;
	while(environ[count])
	{
		exp.push_back(environ[count]);
		count++;
	}
	sort(exp.begin(),exp.end());
	for(it=exp.begin();it!=exp.end();it++)
	{
		cout<<"declare -x "<<*it<<endl;
	}
}