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
		cout<<"����������ѡ��"<<endl;
		cin>>index;
		switch(index)
		{
		case 1:
			Safe(Available,Allocation,Need);
			if(IsSafe())  
			{  
				cout<<"��ʱ���ǰ�ȫ�ģ���ȫ����Ϊ>"; 
				for (int i = 0; i < n ; ++i)  
				{  
					printf("p%d->",SafeSeries[i]);
				}  
				cout<<"end"<<endl;
				//����ɹ���Finish��ֵ��Ϊfalse
				for(int i = 0; i < n; ++i)  
				{  
					Finish[i] = false;  
				}  
			}  
			else  
			{  
				cout<<"��ʱ���ǲ���ȫ��"<<endl;
			} 
			break;
		case 2:
			BankA();
			if(IsSafe())  
			{  
				cout<<"��ȫ����Ϊ>"; 
				for (int i = 0; i < n ; ++i)  
				{  
					printf("p%d->",SafeSeries[i]);
				}  
				cout<<"end"<<endl;
				//����ɹ���Finish��ֵ��Ϊfalse
				for(int i = 0; i < n; ++i)  
				{  
					Finish[i] = false;  
				}  
			}  
			else  
			{  
				cout<<"����������Դ��������"<<endl;
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
			cout<<"�����������,����������"<<endl;
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