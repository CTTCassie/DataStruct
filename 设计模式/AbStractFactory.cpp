#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#include<iostream>

using namespace std;
//抽象产品类
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
//实现抽象产品的具体具体产品类
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
//定义抽象工厂
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
//实现抽象工厂的具体工厂类
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
//模拟client端测试
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