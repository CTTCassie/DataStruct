#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include<cassert>
using namespace std;

#include "BankF.h"

void testBank()
{
	int index=0;
	int flag=1;
	while (flag)
	{
		Menu();
		cout<<"请输入您的选择"<<endl;
		cin>>index;
		switch(index)
		{
		case 1:
			Safe(Available,Allocation,Need);
			if(IsSafe())  
			{  
				cout<<"该时刻是安全的，安全序列为>"; 
				for (int i = 0; i < n ; ++i)  
				{  
					printf("p%d->",SafeSeries[i]);
				}  
				cout<<"end"<<endl;
				//分配成功将Finish的值置为false
				for(int i = 0; i < n; ++i)  
				{  
					Finish[i] = false;  
				}  
			}  
			else  
			{  
				cout<<"该时刻是不安全的"<<endl;
			} 
			break;
		case 2:
			BankA();
			if(IsSafe())  
			{  
				cout<<"安全序列为>"; 
				for (int i = 0; i < n ; ++i)  
				{  
					printf("p%d->",SafeSeries[i]);
				}  
				cout<<"end"<<endl;
				//分配成功将Finish的值置为false
				for(int i = 0; i < n; ++i)  
				{  
					Finish[i] = false;  
				}  
			}  
			else  
			{  
				cout<<"进程请求资源不被允许"<<endl;
			} 
			break;
		case 3:
			Init();
			break;
		case 4:
			Display();
			break;
		case 0:
			flag=0;
			break;
		default:
			cout<<"您的输入错误,请重新输入"<<endl;
			break;
		}
	}
}

int main()  
{  
	testBank();
	system("pause");
	return 0;  
}