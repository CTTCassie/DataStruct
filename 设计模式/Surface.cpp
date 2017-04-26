#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;
//读文件
class FileReader
{
	friend class EncryptFacade;//声明友元类，可以在一个类中访问另一个类的成员方法
public:
	string Read(string fileNameSrc)
	{
		cout<<"读文件"<<endl;
		return fileNameSrc;
	}
	~FileReader()
	{
		cout<<"~FileReader()"<<endl;
	}
};
//写文件
class FileWriter
{
	friend class EncryptFacade;
public:
	string Write(string entryptText,string fileNameDes)
	{
		char *dest=(char *)(fileNameDes.c_str());
		const char *src=entryptText.c_str();
		strcpy(dest,src);
		cout<<"写文件"<<endl;
		return fileNameDes;
	}
	~FileWriter()
	{
		cout<<"~FileWriter()"<<endl;
	}
};
//给文件加密
class CipherMachine
{
	friend class EncryptFacade;
public:
	string Encrypt(string plainText)
	{
		cout<<"rsa加密"<<endl;
		return plainText;
	}
	~CipherMachine()
	{
		cout<<"~CipherMachine()"<<endl;
	}
};
//外观类，给读，写，加密做一个公共的访问接口
class EncryptFacade
{
public:
	EncryptFacade()
		:reader(new FileReader())
		,writer(new FileWriter())
		,cipher(new CipherMachine())
	{}
	void fileEncrypt(string fileNameSrc,string fileNameDes)
	{
		string plainSrc=reader->Read(fileNameSrc);//读数据
		string entryptSrc=cipher->Encrypt(plainSrc);//加密数据
		writer->Write(entryptSrc,fileNameDes);//写入数据
	}
	~EncryptFacade()
	{
		cout<<"~EncryptFacade()"<<endl;
	}
private:
	FileReader *reader;
	FileWriter *writer;
	CipherMachine *cipher;
};

int main()
{
	string src="i am student!";
	string dest;
	EncryptFacade *entry=new EncryptFacade();
	entry->fileEncrypt(src,dest);
	delete(entry);
	system("pause");
	return 0;
}