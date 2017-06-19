#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<cassert>

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K,V> *_left;
	AVLTreeNode<K,V> *_right;
	AVLTreeNode<K,V> *_parent;
	int _bf;   //ƽ������,�������ĸ߶�-�������ĸ߶�
	AVLTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{
		_DestroyTree(_root);
	}
public:
	bool Insert(const K& key,const V& value)
	{
		if(_root == NULL)
		{
			_root=new Node(key,value);
			return true;
		}
		Node *parent=NULL;
		Node *cur=_root;
		while(cur)
		{
			if(cur->_key < key)
			{
				parent=cur;
				cur=cur->_right;
			}
			else if(cur->_key > key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else     //�ҵ���
			{
				return false;
			}
		}
		cur=new Node(key,value);
		if(parent->_key < key)
		{
			parent->_right=cur;
			cur->_parent=parent;
		}
		else
		{
			parent->_left=cur;
			cur->_parent=parent;
		}

		while (parent)
		{
			if(parent->_left == cur)
				parent->_bf -= 1;
			else if(parent->_right == cur)
				parent->_bf += 1;
			if(parent->_bf == 0)    //����ƽ����������
				break;
			else if(parent->_bf == 1 || parent->_bf == -1)   //�������ϵ���
			{
				cur=parent;
				parent=parent->_parent;
			}
			else if(abs(parent->_bf) == 2)    //��Ҫ��ת
			{
				if(parent->_bf == 2)
				{
					if(cur->_bf == 1)
						RorateL(parent);    //����
					else   //cur->_bf == -1
						RorateRL(parent);   //����˫��
				}
				else    //parent->_bf == -2
				{
					if(cur->_bf == -1)
						RorateR(parent);    //�ҵ���
					else   //cur->_bf == 1
						RorateLR(parent);   //����˫��
				}
			}
			else    //error
			{
				assert(false);
			}
		}
		return true;
	}
	Node *Find(const K& key)
	{
		if(_root == NULL)
			return NULL;
		Node *cur=_root;
		while(cur)
		{
			if(cur->_key < key)
				cur=cur->_right;
			else if(cur->_key > key)
				cur=cur->_left;
			else
				return cur;
		}
		return NULL;
	}
	bool IsBlance()    //�ж�һ�Ŷ����������Ƿ���ƽ�������
	{
		return _IsBlance(_root);
	}
	bool IsBlanceOP()
	{
		int height=0;
		return _IsBlanceOP(_root,height);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
private:
	void RorateL(Node *parent)    //����
	{
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		parent->_right=subRL;
		if(subRL)     //�ý�����Ϊ��
			subRL->_parent=parent;
		subR->_left=parent;
		Node *ppNode=parent->_parent;   //��¼parent���ĸ����
		parent->_parent=subR;
		if(_root == parent)   //ppNode == NULL
		{
			_root=subR;
			_root->_parent=NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left=subR;
			else
				ppNode->_right=subR;

			subR->_parent=ppNode;
		}
		parent->_bf=subR->_bf=0;    //����ƽ������
	}
	void RorateR(Node *parent)     //�ҵ���
	{
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		parent->_left=subLR;
		if(subLR)
			subLR->_parent=parent;
		subL->_right=parent;
		Node *ppNode=parent->_parent;
		parent->_parent=subL;
		if(_root == parent)    //_root == NULL
		{
			_root=subL;
			_root->_parent=NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left=subL;
			else
				ppNode->_right=subL;

			subL->_parent=ppNode;   //���¸����
		}
		subL->_bf=parent->_bf=0;    //����ƽ������
	}
	void RorateLR(Node *parent)     //����˫��
	{
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		int bf=subLR->_bf;
		RorateL(parent->_left);
		RorateR(parent);
		if(bf == 0)     //subLR���������
		{
			subLR->_bf=subL->_bf=parent->_bf=0;
		}
		else if(bf == -1)    //���������subLR�����
		{
			subL->_bf=0;
			parent->_bf=1;
			subLR->_bf=-1;
		}
		else     //���������subLR���ұ�
		{
			subL->_bf=-1;
			parent->_bf=0;
			subLR->_bf=1;
		}
	}
	void RorateRL(Node *parent)     //����˫��
	{
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		int bf=subRL->_bf;
		RorateR(parent->_right);
		RorateL(parent);
		if(bf == 0)       //���������subRL
		{
			subRL->_bf=parent->_bf=subR->_bf;
		}
		else  if(bf == 1)   //���������subRL���ұ�
		{
			parent->_bf=-1;
			subR->_bf=0;
			subRL->_bf=1;
		}
		else     //���������subRL�����
		{
			parent->_bf=0;
			subR->_bf=1;
			subRL->_bf=-1;
		}
	}
	int _GetHeight(Node *root)     //�����ĸ߶�
	{
		if(root == NULL)
			return 0;
		int LSize=_GetHeight(root->_left)+1;
		int RSize=_GetHeight(root->_right)+1;
		return LSize > RSize ? LSize : RSize;
	}
	bool _IsBlance(Node *root)    //O(N^N)������ǰ�����
	{
		if(root == NULL)
			return true;
		int left=_GetHeight(root->_left);
		int right=_GetHeight(root->_right);
		int bf=right-left;
		if(root->_bf != bf)
		{
			cout<<root->_key<<"UnIsBlance"<<endl;
			return false;
		}
		return abs(bf) < 2 && _IsBlance(root->_left) \
			&& _IsBlance(root->_right);
	}
	bool _IsBlanceOP(Node *root,int& height)  //O(N)�����ƺ������,�ڱ�����ʱ��ֱ�Ӵ���height��ֵ
	{
		if(root == NULL)   //����������Ҷ�ӽ��ĺ��ӽ��
		{
			height=0;
			return true;
		}
		int left=0;
		_IsBlanceOP(root->_left,height);
		int right=0;
		_IsBlanceOP(root->_right,height);
		int bf=right-left;
		if(abs(bf) >= 2)
			return false;
		height=1+left > right ? left : right;
		return true;
	}
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void _DestroyTree(Node *&root)   //��������ķ�ʽ����һ����
	{
		if(root == NULL)
			return ;
		_DestroyTree(root->_left);
		_DestroyTree(root->_right);
		delete root;
	}
protected:
	Node *_root;
};

void TestAVLTree()
{
	//int array[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	int array[]={4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int,int> avl;
	//���������ж�ӦԪ�ص��±꣬ʱ�临�Ӷȴ�O(n)~O(lgn)
	for(int i=0;i<sizeof(array)/sizeof(array[0]);i++)
	{
		avl.Insert(array[i],i);
	}
	avl.InOrder();
	//cout<<"IsBlance?"<<avl.IsBlance()<<endl;
	cout<<"IsBlanceOP?"<<avl.IsBlanceOP()<<endl;

	AVLTreeNode<int,int> *ret=avl.Find(16);
	if(ret)
	{
		cout<<"Find 16?"<<ret->_key<<endl;
	}
}