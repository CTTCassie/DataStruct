#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<string>
typedef long long INT64;

class BigData
{
public:
	friend ostream& operator<<(ostream& os,const BigData& b);
	BigData(INT64 value);
	BigData(const std::string& strData);
	BigData operator+(const BigData& b);
	BigData operator-(const BigData& b);
	BigData operator*(const BigData& b);
	BigData operator/(const BigData& b);
private:
	bool IsINT64OverFlow(const string& strData);
	BigData Add(string left,string right);
	BigData Sub(string left,string right);
	BigData Mul(string left,string right);
	BigData Div(string left,string right);
	bool IsLeftLarge(const char *pleft,const size_t dataLen,const char *pright,const size_t rightsize);
	char SubLoop(char* &pleft, size_t& dataLen, const char *pright,const size_t rightsize);
private:
	INT64 _value;
	std::string _strData;
};