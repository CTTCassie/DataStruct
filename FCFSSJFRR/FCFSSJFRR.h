#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

struct PCBNode
{
	string _name;      
	double _arrivetime; 
	double _needtime;    //估计运行时间
	double _runtime;     //实际运行时间
	double _endtime;     //结束时间
	PCBNode *_next;
	PCBNode(const string& name="",const double arrive=0.0,const double run=0.0)
		:_name(name)
		,_arrivetime(arrive)
		,_needtime(run)
		,_runtime(0.0)
		,_endtime(0.0)
		,_next(NULL)
	{}
};

class PCB
{
	typedef PCBNode Node;
public:
	PCB()
		:_head(NULL)
		,_tail(NULL)
	{}
	~PCB()
	{
		Node *cur=_head;
		while (cur)
		{
			Node *del=cur;
			cur=cur->_next;
			delete del;
			del=NULL;
		}
		_head=NULL;
		_tail=NULL;
	}
public:
	bool IsEmpty()
	{
		return _head == _tail == NULL;
	}
	void Input()
	{
		string name;
		double arrive=0.0;
		double need=0.0;
		int num=0;
		cout<<"请输入您要执行的进程总数>";
		cin>>num;
		for (int i=0;i<num;++i)
		{
			cout<<"请输入进程名>";
			cin>>name;
			cout<<"请输入进程的到达时间>";
			cin>>arrive;
			cout<<"请输入进程的估计运行时间>";
			cin>>need;
			Node *NewNode=new Node(name,arrive,need);
			if(_head == NULL)     //空链表
			{
				_head=NewNode;
				_tail=NewNode;
			}
			else                 //非空链表
			{
				_tail->_next=NewNode;
				_tail=NewNode;
			}
		}
	}
	void Display()
	{
		Node *cur=_head;
		while (cur)
		{
			cout<<"进程名>"<<cur->_name<<" ";
			cout<<"到达时间>"<<cur->_arrivetime<<" ";
			cout<<"运行时间>"<<cur->_needtime<<endl;
			cur=cur->_next;
		}
	}
	void FCFS()
	{
		int count=0;
		Node *cur=_head;
		double finish=0.0;          //完成时间
		double time=0.0;            //周转时间=完成时间-到达时间
		double weighttime=0.0;      //带权周转时间=周转时间/运行时间
		double avertime=0.0;
		double averweighttime=0.0;  
		while(cur)
		{   
			if(finish <= cur->_arrivetime)
			{
				//当完成时间小于到达时间时
				finish=cur->_arrivetime+cur->_needtime;
				time=finish-cur->_arrivetime;
				avertime += time;
				weighttime=time/cur->_needtime;
				averweighttime += weighttime;
			}
			else
			{
				finish += cur->_needtime;
				time=finish-cur->_arrivetime;
				avertime += time;
				weighttime=time/cur->_needtime;
				averweighttime += weighttime;
			}
			cout<<"进程名>"<<cur->_name<<" ";
			cout<<"完成时间>"<<finish<<" ";
			cout<<"周转时间>"<<time<<" ";
			cout<<"带权周转时间>"<<weighttime<<endl;
			count++;
			cur=cur->_next;
		}
		cout<<"平均周转时间>"<<avertime/count<<endl;
		cout<<"平均带权周转时间>"<<averweighttime/count<<endl;
	}
	void SortByRunTime(Node *node)
	{
		Node *cur=node;
		int flag=1;
		Node *tail=NULL;
		while (cur != tail)
		{
			while(cur->_next != tail)
			{
				if (cur->_needtime > cur->_next->_needtime)
				{
					Node *tmp=new Node(cur->_name,cur->_arrivetime,cur->_needtime);
					cur->_name=cur->_next->_name;
					cur->_arrivetime=cur->_next->_arrivetime;
					cur->_needtime=cur->_next->_needtime;

					cur->_next->_name=tmp->_name;
					cur->_next->_arrivetime=tmp->_arrivetime;
					cur->_next->_needtime=tmp->_needtime;
					flag=0;
				}
				cur=cur->_next;
			}
			if(flag == 1)
				break;
			tail=cur;
			cur=node;
		}
	}
	void SJF()
	{
		//对第一个进程之后的其他进程按照运行时间(由小到大)进行排序
		//对排序之后的进程进行类似先来先服务的进程调度算法
		int count=0;
		Node *cur=_head;
		double finish=0.0;
		double time=0.0;
		double weighttime=0.0;
		double avertime=0.0;
		double averweighttime=0.0;  

		SortByRunTime(_head->_next);

		while(cur)
		{   
			if(finish <= cur->_arrivetime)
			{
				//当完成时间小于到达时间时
				finish=cur->_arrivetime+cur->_needtime;
				time=finish-cur->_arrivetime;
				avertime += time;
				weighttime=time/cur->_needtime;
				averweighttime += weighttime;
			}
			else
			{
				finish += cur->_needtime;
				time=finish-cur->_arrivetime;
				avertime += time;
				weighttime=time/cur->_needtime;
				averweighttime += weighttime;
			}
			cout<<"进程名>"<<cur->_name<<" ";
			cout<<"完成时间>"<<finish<<" ";
			cout<<"周转时间>"<<time<<" ";
			cout<<"带权周转时间>"<<weighttime<<endl;
			count++;
			cur=cur->_next;
		}
		cout<<"平均周转时间>"<<avertime/count<<endl;
		cout<<"平均带权周转时间>"<<averweighttime/count<<endl;
	}
	void RR(const double& q)
	{
		double time=0.0;
		double weighttime=0.0;
		double avertime=0.0;
		double averweighttime=0.0;  

		double sys=0.0;      //系统时间
		queue<Node *> q1;    //辅助队列
		int count=0;
		Node *cur=_head;
		while (cur)
		{
			count++;
			q1.push(cur);
			cur=cur->_next;
		}
		cur=_head;
		while (!q1.empty())
		{
			Node *tmp=q1.front();
			if(tmp->_arrivetime <= sys)   //是否有进程到达
			{
				if (tmp->_needtime > q)   //一个时间片里不能执行完成
				{
					Sleep(q);
					tmp->_needtime -= q;
					tmp->_runtime += q;
					sys += q;
					q1.push(tmp);
					q1.pop();
				}
				else
				{
					Sleep(tmp->_needtime);
					sys += tmp->_needtime;
					tmp->_endtime=sys;
					tmp->_runtime += tmp->_needtime;
					tmp->_needtime=0.0;
					q1.pop();
				}
			}
			else
				sys++;
		}
		cur=_head;
		while (cur)
		{
			time=cur->_endtime-cur->_arrivetime;
			avertime += time;
			weighttime=time/cur->_runtime;
			averweighttime += weighttime;
			cout<<"进程名>"<<cur->_name<<" ";
			cout<<"完成时间>"<<cur->_endtime<<" ";
			cout<<"周转时间>"<<time<<" ";
			cout<<"带权周转时间>"<<weighttime<<endl;
			cur=cur->_next;
		}
		cout<<"平均周转时间>"<<avertime/count<<endl;
		cout<<"平均带权周转时间>"<<averweighttime/count<<endl;
	}
protected:
	Node *_head;
	Node *_tail;
};

void menu()
{
	cout<<"*********单批道进程调度算法*******"<<endl;
	cout<<"************* 1.FCFS**************"<<endl;
	cout<<"************* 2.SJF***************"<<endl;
	cout<<"************* 3.RR***************"<<endl;
	cout<<"************* 4.Input*************"<<endl;
	cout<<"************* 0.Exit**************"<<endl;
}