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
		cout<<"请输入您的选择>";
		cin>>choice;
		switch(choice)
		{
		case 1:
			if(!pcb.IsEmpty())
			{
				cout<<"此时没有进程在等待"<<endl;
				break;
			}
			else
			{
				cout<<"先来先服务的进程调度算法>"<<endl;
				pcb.FCFS();
			}
			break;
		case 2:
			if(!pcb.IsEmpty())
			{
				cout<<"此时没有进程在等待"<<endl;
				break;
			}
			else
			{
				cout<<"短作业优先的进程调度算法>"<<endl;
				pcb.SJF();
			}
			break;
		case 3:
			if(!pcb.IsEmpty())
			{
				cout<<"此时没有进程在等待"<<endl;
				break;
			}
			else
			{
				double q=0.0;
				cout<<"时间片轮转的进程调度算法>"<<endl;
				cout<<"请输入时间片的大小>";
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