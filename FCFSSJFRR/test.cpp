#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <queue>
#include<windows.h>
using namespace std;

#include "FCFSSJFRR.h"

void testPCB()
{
	PCB pcb;
	int choice=0;
	int index=1;
	while (index)
	{
		menu();
		cout<<"����������ѡ��>";
		cin>>choice;
		switch(choice)
		{
		case 1:
			if(!pcb.IsEmpty())
			{
				cout<<"��ʱû�н����ڵȴ�"<<endl;
				break;
			}
			else
			{
				cout<<"�����ȷ���Ľ��̵����㷨>"<<endl;
				pcb.FCFS();
			}
			break;
		case 2:
			if(!pcb.IsEmpty())
			{
				cout<<"��ʱû�н����ڵȴ�"<<endl;
				break;
			}
			else
			{
				cout<<"����ҵ���ȵĽ��̵����㷨>"<<endl;
				pcb.SJF();
			}
			break;
		case 3:
			if(!pcb.IsEmpty())
			{
				cout<<"��ʱû�н����ڵȴ�"<<endl;
				break;
			}
			else
			{
				double q=0.0;
				cout<<"ʱ��Ƭ��ת�Ľ��̵����㷨>"<<endl;
				cout<<"������ʱ��Ƭ�Ĵ�С>";
				cin>>q;
				pcb.RR(q);
			}
			break;
		case 4:
			pcb.Input();
			break;
		case 0:
			index=0;
			break;
		default:
			cout<<"error"<<endl;
			break;
		}
	}
}

int main()
{
	testPCB();
	system("pause");
	return 0;
}