#define _CRT_SECURE_NO_WARNINGS 1

#include "BigData.h"

void testInvaild()
{
	cout<<BigData("12345678")<<endl;
	cout<<BigData("+12345678")<<endl;
	cout<<BigData("-12345678")<<endl;
	cout<<BigData("1234abc34567")<<endl;
	cout<<BigData("abc123456")<<endl;
	cout<<BigData("000123456")<<endl;
	cout<<BigData("000000000")<<endl;
	cout<<BigData("		12345")<<endl;
	cout<<BigData("		")<<endl;
	cout<<BigData("0")<<endl;
}

void testAdd()
{
	BigData b1("999999999999999999999999999999999");
	BigData b2("99");
	BigData b3("99");
	BigData b4("999999999999999999999999999999999");
	cout<<b1+b2<<endl;
	cout<<b3+b4<<endl;
}

void testSub()
{
	BigData b1("2222222");  //一次借位
	BigData b2("99");
	BigData b3("100000000000000000000000000000000");  //多次借位
	BigData b4("99");
	cout<<b1-b2<<endl;
	cout<<b3-b4<<endl;
}

void testMul()
{
	BigData b1("999999999999999999999999999999999");
	BigData b2("99");
	BigData b3("100000000000000000000000000000001");
	BigData b4("99");
	BigData b5("99");
	BigData b6("999999999999999999999999999999999");
	cout<<b1*b2<<endl;
	cout<<b3*b4<<endl;
	cout<<b5*b6<<endl;
}

void testDiv()
{
	BigData b1("22222222222222222222222222");
	BigData b2("33");
	cout<<b1/b2<<endl;
}

int main()
{
	//testInvaild();
	//testAdd();
	//testSub();
	//testMul();
	testDiv();
	system("pause");
	return 0;
}