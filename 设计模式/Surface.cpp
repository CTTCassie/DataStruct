#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;
//���ļ�
class FileReader
{
	friend class EncryptFacade;//������Ԫ�࣬������һ�����з�����һ����ĳ�Ա����
public:
	string Read(string fileNameSrc)
	{
		cout<<"���ļ�"<<endl;
		return fileNameSrc;
	}
	~FileReader()
	{
		cout<<"~FileReader()"<<endl;
	}
};
//д�ļ�
class FileWriter
{
	friend class EncryptFacade;
public:
	string Write(string entryptText,string fileNameDes)
	{
		char *dest=(char *)(fileNameDes.c_str());
		const char *src=entryptText.c_str();
		strcpy(dest,src);
		cout<<"д�ļ�"<<endl;
		return fileNameDes;
	}
	~FileWriter()
	{
		cout<<"~FileWriter()"<<endl;
	}
};
//���ļ�����
class CipherMachine
{
	friend class EncryptFacade;
public:
	string Encrypt(string plainText)
	{
		cout<<"rsa����"<<endl;
		return plainText;
	}
	~CipherMachine()
	{
		cout<<"~CipherMachine()"<<endl;
	}
};
//����࣬������д��������һ�������ķ��ʽӿ�
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
		string plainSrc=reader->Read(fileNameSrc);//������
		string entryptSrc=cipher->Encrypt(plainSrc);//��������
		writer->Write(entryptSrc,fileNameDes);//д������
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