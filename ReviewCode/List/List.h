#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>
#include<stack>

struct ListNode
{
	int data;
	struct ListNode *next;
	ListNode(const int& d=0)
		:data(d)
		,next(NULL)
	{}
};
class List
{
	friend ostream& operator<<(ostream& os,ListNode *head);
public:
	void PushBack(ListNode *&head,const int& d)
	{
		ListNode *newNode=new ListNode(d);
		if(head == NULL)    //空链表
		{
			head=new ListNode(d);
		}
		else  if(head->next == NULL)   //只有一个结点
		{
			head->next=newNode;
		}
		else   //有两个或者两个以上的结点
		{
			ListNode *cur=head;
			while(cur->next)   //找到最后一个结点
			{
				cur=cur->next;
			}
			cur->next=newNode; //插入新节点
		}
	}
	ListNode *FindNode(ListNode *head,int d)
	{
		assert(head);
		ListNode *cur=head;
		while(cur)
		{
			if(cur->data == d)
				return cur;
			cur=cur->next;
		}
		return NULL;
	}
	void ShowList(ListNode *head)
	{
		assert(head);
		ListNode *cur=head;
		while(cur)
		{
			cout<<cur->data<<" ";
			cur=cur->next;
		}
		cout<<endl;
	}
	void DestroyList(ListNode *&head)
	{
		assert(head);
		ListNode *cur=head;
		while(cur)
		{
			ListNode *del=cur;
			cur=cur->next;
			delete del;
			del=NULL;
		}
	}
public:
	//删除无头单链表的非尾结点，替换法
	void DelNotTail(ListNode *pos)
	{
		assert(pos && pos->next);
		ListNode *del=pos->next;
		pos->data=del->data;
		pos->next=del->next;
		delete del;
		del=NULL;
	}
	//删除倒数第k个结点，只允许遍历一遍链表
	void DelKNode(ListNode *head,int k)
	{
		assert(head);
		ListNode *prev=head;
		ListNode *slow=head;
		while(prev)
		{
			k--;
			//slow指向倒数第k个结点
			if(k < 0)
			{
				slow=slow->next;
			}
			prev=prev->next;   //prev先指向正数第k个结点
		}
		if(k <= 0)   //删除slow所指向的结点
		{
			DelNotTail(slow);
			//ListNode *del=slow->next;
			//slow->data=del->data;
			//slow->next=del->next;
			//delete del;
			//del=NULL;
		}
	}
	//查找链表的中间节点，只允许遍历一遍链表
	ListNode *FindMidNode(ListNode *head)
	{
		ListNode *fast=head;   //快慢指针
		ListNode *slow=head;
		while(fast && fast->next)
		{
			fast=fast->next->next;
			slow=slow->next;
		}
		return slow;
	}
	//在当前结点前插一个结点(无头单链表),实现方法类似删除无头单链表的非尾结点
	void InsertFrontNode(ListNode *pos,int d)
	{
		assert(pos);
		ListNode *newNode=new ListNode(d);
		newNode->next=pos->next;
		pos->next=newNode;
		int tmp=newNode->data;
		newNode->data=pos->data;
		pos->data=tmp;
	}

	//从尾到头打印单链表，利用辅助栈的结构
	void ReverseShowList(ListNode *head)
	{
		stack<ListNode *> s;
		ListNode *cur=head;
		while(cur)
		{
			s.push(cur);
			cur=cur->next;
		}
		while(!s.empty())
		{
			ListNode *top=s.top();
			cout<<top->data<<" ";
			s.pop();
		}
		cout<<endl;
	}
	//反转单链表
	ListNode *ReverseList(ListNode *head)
	{
		assert(head || head->next);  //头指针为空或者只有一个结点
		ListNode *cur=head;
		ListNode *newHead=NULL;
		ListNode *newCur=NULL;
		while(cur)
		{
			newCur=cur;
			cur=cur->next;
			newCur->next=newHead;
			newHead=newCur;   //更新头
		}
		return newHead;
	}
	//合并两个有序的单链表,不开辟新的空间
	ListNode *MergeNoR(ListNode *plist1,ListNode *plist2)
	{
		ListNode *p1=plist1;
		ListNode *p2=plist2;
		ListNode *newHead=NULL;
		ListNode *tail=NULL;
		if(p1 == p2)      //三种特殊情况
			return p1;
		if(p1 == NULL)
			return p2;
		if(p2 == NULL)
			return p1;
		if(p1->data < p2->data)  //为新的链表选取新的头指针
		{
			newHead=p1;
			tail=p1;
			p1=p1->next;
		}
		else
		{
			newHead=p2;
			tail=p2;
			p2=p2->next;
		}
		while(p1 != NULL && p2 != NULL)
		{
			if(p1->data < p2->data)
			{
				tail->next=p1;
				tail=tail->next;
				p1=p1->next;
			}
			else
			{
				tail->next=p2;
				tail=tail->next;
				p2=p2->next;
			}
		}
		if(p1 != NULL)    //有可能有的链表的部分数据尚未完全插入
			tail->next=p1;
		if(p2 != NULL)
			tail->next=p2;
		return newHead;
	}
	ListNode *MergeR(ListNode *plist1,ListNode *plist2)
	{
		ListNode *p1=plist1;
		ListNode *p2=plist2;
		ListNode *plist3=NULL;
		if(p1 == p2)
			return p1;
		if(p1 == NULL)
			return p2;
		if(p2 == NULL)
			return p1;
		if(p1->data < p2->data)
		{
			plist3=p1;
			plist3->next=MergeR(p1->next,p2);
		}
		else
		{
			plist3=p2;
			plist3->next=MergeR(p1,p2->next);
		}
		return plist3;
	}
	//单链表实现约瑟夫环
	ListNode *JosephCycle(ListNode *head,int k)
	{
		assert(head);
		ListNode *cur=head;
		while(cur->next != cur)   //有超过一个人存在
		{
			int m=k;     //m保存k的值，可以重复使用
			while(--m)   //cur指向将要退出的结点
			{
				cur=cur->next;
			}
			cout<<"del:"<<cur->data<<endl;
			ListNode *del=cur->next;  //利用交换的方式，最后要删除的结点是cur的下一个结点
			cur->data=del->data;
			cur->next=del->next;
			delete del;
			del=NULL;
		}
		return cur;
	}
	//判断链表是否带环，带环则返回相遇点
	ListNode *CheckCycle(ListNode *head)
	{
		assert(head);
		ListNode *fast=head;
		ListNode *slow=head;
		while(fast && fast->next)
		{
			fast=fast->next->next;
			slow=slow->next;
			if(fast == slow)
				return slow;
		}
		return NULL;
	}
	//如果带环则求出链表长度
	int GetCircleLength(ListNode *head)
	{
		assert(head);
		ListNode *meet=CheckCycle(head);
		assert(meet);
		ListNode *cur=meet;
		int count=1;
		while(cur->next != meet)
		{
			count++;
			cur=cur->next;
		}
		return count;
	}
	//求出带环链表的入口节点
	ListNode *GetCircleEntryNode(ListNode *head,ListNode *meet)
	{
		assert(head);
		assert(meet);
		//prev从相遇点开始，slow从链表头开始
		//prev和slow的再次相遇点就是入口节点
		ListNode *prev=meet;
		ListNode *slow=head;
		while(prev != slow)
		{
			prev=prev->next;
			slow=slow->next;
		}
		return slow; 
	}
	//判断链表是否相交，并求出交点(链表不带环)
	bool CheckCross(ListNode *plist1,ListNode *plist2)
	{
		assert(plist1);
		assert(plist2);
		ListNode *p1=plist1;
		ListNode *p2=plist2;
		//p1,p2分别指向两条链表的尾结点
		while(p1->next)
		{
			p1=p1->next;
		}
		while(p2->next)
		{
			p2=p2->next;
		}
		if(p1 == p2)
			return true;    //相交
		else
			return false;   //不相交
	}
	ListNode *GetCrossEntryNode1(ListNode *plist1,ListNode *plist2)
	{
		assert(plist1);
		assert(plist2);
		ListNode *cur1=plist1;
		ListNode *cur2=plist2;
		int count1=0;
		int count2=0;
		//统计链表1和链表2的长度
		while(cur1)
		{
			count1++;
			cur1=cur1->next;
		}
		while(cur2)
		{
			count2++;
			cur2=cur2->next;
		}
		cur1=plist1;
		cur2=plist2;
		//长链表先走count1-count2步，然后两个指针再一起前进
		if(count1-count2 >= 0)
		{
			while(count1-count2)
			{
				cur1=cur1->next;
				count1--;
			}
			while(cur1 != cur2)
			{
				cur1=cur1->next;
				cur2=cur2->next;
			}
		}
		else    //count1 < count2
		{
			while(count2-count1)
			{
				cur2=cur2->next;
				count2--;
			}
			while(cur1 != cur2)
			{
				cur1=cur1->next;
				cur2=cur2->next;
			}
		}
		return cur1;
	}
	ListNode *GetCrossEntryNode2(ListNode *plist1,ListNode *plist2)
	{
		assert(plist1);
		assert(plist2);
		ListNode *cur=plist1;
		//构造环
		while(cur->next)
		{
			cur=cur->next;
		}
		cur->next=plist2;
		ListNode *meet=CheckCycle(plist1);
		return GetCircleEntryNode(plist1,meet);
	}
	//判断链表是否相交，并求出交点(链表可能带环)
	bool CheckCrossCircle(ListNode *plist1,ListNode *plist2)
	{
		assert(plist1);
		assert(plist2);
		ListNode *meet1=CheckCycle(plist1);
		ListNode *meet2=CheckCycle(plist2);
		//如果有一个不带环则必然不相交
		assert(meet1);
		assert(meet2);
		//两个链表都带环，如果相遇点在同一个环内则必然相交
		ListNode *m1=meet1;
		ListNode *m2=meet2;
		while(m1 != m2)
		{
			m1=m1->next;
		}
		if(m1 == m2)
			return true;
		else
			return false;
	}
	ListNode *GetCrossCircleNode(ListNode *plist1,ListNode *plist2)
	{
		assert(plist1);
		assert(plist2);
		ListNode *meet1=CheckCycle(plist1);
		ListNode *meet2=CheckCycle(plist2);
		assert(meet1);
		assert(meet2);
		ListNode *entry1=GetCircleEntryNode(plist1,meet1);
		ListNode *entry2=GetCircleEntryNode(plist2,meet2);
		if(entry1 == entry2)      //交点在环外
		{
			//tail指向相遇点的第一个节点
			//重新构造环
			ListNode *tail=entry1;
			while(tail->next != entry1)
			{
				tail=tail->next;
			}
			tail->next=plist1;
			ListNode *meet=CheckCycle(plist2);
			return GetCircleEntryNode(plist2,meet);
		}
		else  //交点在环内
		{
			//交点就是entry1或者是entry2
			return entry2;
		}
	}
	void BubbleSort(ListNode *plist)
	{
		assert(plist);
		ListNode *cur=plist;
		ListNode *tail=NULL;
		bool flag=true;
		while(cur != tail)
		{
			while(cur->next != tail)
			{
				if(cur->data > cur->next->data)    //升序排序
				{
					flag=false;
					int tmp=cur->data;
					cur->data=cur->next->data;
					cur->next->data=tmp;
				}
				cur=cur->next;
			}
			if(flag == true)
			{
				break;
			}
			tail=cur;    //不断缩小比较的范围
			cur=plist;
		}
	}
	//删除链表中重复的结点
	ListNode* DeleteDuplication(ListNode* head)
	{
		assert(head);
		ListNode *prev=NULL;
		ListNode *cur=head;
		while(cur)
		{
			ListNode *next=cur->next;
			int flag=1;
			//当前结点的数据域和它的下一个结点的数据域相同则修改flag
			if(next && cur->data == next->data)
			{
				flag=0;
			}
			//未修改，则继续遍历下一个结点
			if(flag == 1)
			{
				prev=cur;
				cur=cur->next;
			}
			//修改flag，则删除所有数据域相同的结点
			else
			{
				int d=cur->data;
				ListNode *del=cur;
				while(del && del->data == d)
				{
					next=del->next;
					delete del;
					del=next;
				}
				if(prev == NULL)
					head=next;
				else
					prev->next=next;
				cur=next;      //更新cur的值
			}
		}
		return head;
	}
};
ostream& operator<<(ostream& os,ListNode *head)   //输出运算符的重载
{
	ListNode *cur=head;
	while(cur)
	{
		os<<cur->data<<" ";
		cur=cur->next;
	}
	return os;
}

void TestMergeList()
{
	ListNode *h1=NULL;
	List l1;
	l1.PushBack(h1,1);
	l1.PushBack(h1,3);
	l1.PushBack(h1,4);
	l1.PushBack(h1,5);
	l1.PushBack(h1,7);
	l1.PushBack(h1,9);

	ListNode *h2=NULL;
	List l2;
	l2.PushBack(h2,2);
	l2.PushBack(h2,4);
	l2.PushBack(h2,6);
	l2.PushBack(h2,8);
	//ListNode *newHead=l1.MergeNoR(h1,h2);
	ListNode *newHead=l1.MergeR(h1,h2);
	l1.ShowList(newHead);
	l1.DestroyList(h1);
}
void TestBasicList()
{
	ListNode *head=NULL;
	List list;
	for(int i=1;i<=10;i++)
	{
		list.PushBack(head,i);
	}
	//ListNode *pos=list.FindNode(head,9);
	//list.DelNotTail(pos);
	//list.ShowList(head);
	//pos=list.FindNode(head,1);
	//list.DelNotTail(pos);
	//list.ShowList(head);
	//pos=list.FindNode(head,10);
	//list.DelNotTail(pos);   //error，此时的结点10是尾结点
	//list.ShowList(head); 

	//ListNode *mid=list.FindMidNode(head);   //6 7 8 9 10
	//cout<<mid<<endl;
	//list.DelKNode(head,2);
	//mid=list.FindMidNode(head);
	//cout<<mid<<endl;    //5 6 7 8 10
	////1 2 3 4 5 6 7 8 10
	//list.DelKNode(head,9);
	//cout<<head<<endl;   //2 3 4 5 6 7 8 10

	cout<<head<<endl;   //1 2 3 4 5 6 7 8 9 10
	ListNode *pos=list.FindNode(head,9);
	list.InsertFrontNode(pos,12);
	cout<<head<<endl;   //1 2 3 4 5 6 7 8 12 9 10
}
void TestReverseList()
{
	ListNode *head=NULL;
	List list;
	ListNode *newHead=NULL;
	list.PushBack(head,1);
	list.PushBack(head,2);
	list.PushBack(head,3);
	list.PushBack(head,4);
	list.PushBack(head,5);
	list.ShowList(head);   //1 2 3 4 5
	list.ReverseShowList(head);   //5 4 3 2 1
	newHead=list.ReverseList(head);
	list.ShowList(newHead);//5 4 3 2 1
	list.DestroyList(newHead);
}
void TestJosephCycle()
{
	ListNode *head=NULL;
	List list;
	for(int i=1;i<=10;i++)
	{
		list.PushBack(head,i);
	}
	cout<<head<<endl;
	ListNode *last=list.FindNode(head,10);  //构造约瑟夫环
	last->next=list.FindNode(head,1);
	ListNode *survivor=list.JosephCycle(head,3);
	cout<<"survivor:"<<survivor->data<<endl;
}
void TestCircleList()
{
	ListNode *head=NULL;
	List list;
	//构造环的过程
	for(int i=1;i<=10;i++)
	{
		list.PushBack(head,i);
	}
	ListNode *tail=list.FindNode(head,10);
	tail->next=list.FindNode(head,4);

	ListNode *meet=list.CheckCycle(head);
	cout<<"meet:"<<meet->data<<endl;   //8

	int count=list.GetCircleLength(head);
	cout<<"count:"<<count<<endl;       //7

	ListNode *entry=list.GetCircleEntryNode(head,meet);
	cout<<"entry:"<<entry->data<<endl;           //4
}
void TestCrossList()
{
	ListNode *plist1=NULL;
	ListNode *plist2=NULL;
	List list1,list2;
	list1.PushBack(plist1,1);
	list1.PushBack(plist1,2);
	for(int i=1;i<=10;i++)
	{
		list2.PushBack(plist2,i);
	}
	cout<<list1.CheckCross(plist1,plist2)<<endl;   //0
	ListNode *tail=list1.FindNode(plist1,2);
	tail->next=list2.FindNode(plist2,5);

	cout<<list1.CheckCross(plist1,plist2)<<endl;   //1

	ListNode *cross1=list1.GetCrossEntryNode1(plist1,plist2);
	cout<<"cross1:"<<cross1->data<<endl;            //5

	ListNode *cross2=list1.GetCrossEntryNode2(plist1,plist2);
	cout<<"cross2:"<<cross2->data<<endl;            //5
}
void TestCrossCircle()
{
	ListNode *plist1=NULL;
	ListNode *plist2=NULL;
	List list1,list2;
	for(int i=1;i<=10;i++)
	{
		list1.PushBack(plist1,i);
	}
	list2.PushBack(plist2,2);
	list2.PushBack(plist2,4);
	list2.PushBack(plist2,6);
	//带环链表的相交问题，交点在环外
	//ListNode *tail=list1.FindNode(plist1,10);
	//tail->next=list1.FindNode(plist1,4);

	//tail=list2.FindNode(plist2,6);
	//tail->next=list1.FindNode(plist1,3);

	//cout<<list1.CheckCrossCircle(plist1,plist2)<<endl;   //1
	//ListNode *entry=list1.GetCrossCircleNode(plist1,plist2);
	//cout<<"entry:"<<entry->data<<endl;    //3

	//带环链表的相交问题，交点在环上
	ListNode *tail=list1.FindNode(plist1,10);
	tail->next=list1.FindNode(plist1,4);
	tail=list2.FindNode(plist2,6);
	tail->next=list1.FindNode(plist1,6);
	cout<<list1.CheckCrossCircle(plist1,plist2)<<endl;   //1
	ListNode *entry=list1.GetCrossCircleNode(plist1,plist2);
	cout<<"entry:"<<entry->data<<endl;    //4
}
void TestBubbleSort()
{
	ListNode *head=NULL;
	List list;
	for(int i=10;i>=0;i--)
	{
		list.PushBack(head,i);
	}
	cout<<head<<endl;
	list.BubbleSort(head);
	cout<<head<<endl;

	list.DestroyList(head);
}
void TestDD()
{
	ListNode *head=NULL;
	List list;
	list.PushBack(head,1);
	list.PushBack(head,2);
	list.PushBack(head,2);
	list.PushBack(head,2);
	list.PushBack(head,3);
	list.PushBack(head,3);
	list.PushBack(head,4);
	list.PushBack(head,5);
	cout<<head<<endl;
	list.DeleteDuplication(head);
	cout<<head<<endl;    //1 4 5
}