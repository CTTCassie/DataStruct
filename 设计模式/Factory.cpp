#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

class Log
{
public:
	virtual void writelog()=0;  //纯虚函数实现抽象方法
};
class FileLog:public Log
{
public:
	virtual void writelog()
	{
		cout<<"FileLog is running..."<<endl;
	}
};
class DatabaseLog:public Log
{
public:
	virtual void writelog()
	{
		cout<<"DatabaseLog is running..."<<endl;
	}
};
class LogFactory
{
public:
	static Log* createlog(char *str)
	{
		if(strcmp(str,"FileLog") == 0)
		{
			return new FileLog;
		}
		else if(strcmp(str,"DatabaseLog") == 0)
		{
			return new DatabaseLog;
		}
		else  
		{
			throw -1;
		}
	}
};

int main()
{
	Log *log;
	try
	{
		log=LogFactory::createlog("FileLog");
		log->writelog();
		log=LogFactory::createlog("DatabaseLog");
		log->writelog();
		log=LogFactory::createlog("ObjectLog");
		log->writelog();   //not exist
	}
	catch(...)
	{
		cout<<"not exist..."<<endl;
	}
	system("pause");
	return 0;
}