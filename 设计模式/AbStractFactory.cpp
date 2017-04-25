#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#include<iostream>

using namespace std;
//�����Ʒ��
class Connection
{
public:
	virtual ~Connection()
	{
		cout<<"~Connection()"<<endl;
	}
};
class Statement
{
public:
	virtual ~Statement()
	{
		cout<<"~Statement()"<<endl;
	}
};
//ʵ�ֳ����Ʒ�ľ�������Ʒ��
class OracleConnection:public Connection
{
public:
	~OracleConnection()  
	{
		cout<<"~OracleConnection()"<<endl;
	}
};

class MySQLConnection:public Connection
{
public:
	~MySQLConnection()
	{
		cout<<"~MySQLConnection()"<<endl;
	}
};

class OracleStatement:public Statement
{
public:
	~OracleStatement()  
	{
		cout<<"~OracleStatement()"<<endl;
	}
};

class MySQLStatement:public Statement
{
public:
	~MySQLStatement()  
	{
		cout<<"~MySQLStatement()"<<endl;
	}
};
//������󹤳�
class DBFactory
{
public:
	virtual Connection* createConnection() = 0;
	virtual Statement* createStatement() = 0;
	virtual ~DBFactory()
	{
		cout<<"~DBFactory()"<<endl;
	}
};
//ʵ�ֳ��󹤳��ľ��幤����
class OracleFactory:public DBFactory
{
public:
	virtual Connection* createConnection()
	{
		cout<<"Oracle connection is done..."<<endl;
		return new Connection();
	}
	virtual Statement* createStatement()
	{
		cout<<"Oracle statement is done..."<<endl;
		return new Statement();
	}
	~OracleFactory()  
	{
		cout<<"~OracleFactory()"<<endl;
	}
};

class MySQLFactory:public DBFactory
{
public:
	virtual Connection* createConnection()
	{
		cout<<"MySQL connection is done..."<<endl;
		return new Connection();
	}
	virtual Statement* createStatement()
	{
		cout<<"MySQL statement is done..."<<endl;
		return new Statement();
	}
	~MySQLFactory()  
	{
		cout<<"~MySQLFactory()"<<endl;
	}
};
//ģ��client�˲���
int main()
{
	Connection* conn;
	Statement* stat;
	DBFactory* factory;
	try
	{
		factory=new OracleFactory();
		conn=factory->createConnection();
		stat=factory->createStatement();

		factory=new MySQLFactory();
		conn=factory->createConnection();
		stat=factory->createStatement();
	}
	catch (...)
	{
		cout<<"not exist..."<<endl;
	}
	delete(conn);
	delete(stat);
	delete(factory);
	system("pause");
	return 0;
}