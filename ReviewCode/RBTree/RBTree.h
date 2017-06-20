#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	RBTreeNode<K,V> *_left;
	RBTreeNode<K,V> *_right;
	RBTreeNode<K,V> *_parent;
	Color color;
	RBTreeNode(const K& key,const V& value)  //新增结点是红色的
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,color(RED)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		if(_root == NULL)    //根结点是黑色的
		{
			_root=new Node(key,value);
			_root->color=BLACK;
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
			else    //找到了
			{
				return false;
			}
		}
		cur=new Node(key,value);   //插入新节点
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

		while(parent && parent->color == RED)
		{
			Node *grandfather=parent->_parent;
			if(grandfather->_left == parent)
			{
				Node *uncle=grandfather->_right;
				if(uncle && uncle->color == RED)   //uncle存在且uncle是红色结点
				{
					parent->color=uncle->color=BLACK;
					grandfather->color=RED;
					cur=grandfather;
					parent=cur->_parent;
				}
				else    //uncle不存在或者是uncle是黑色结点
				{
					if(parent->_right == cur)
					{
						RotateL(parent);
						swap(cur,parent);
					}
					RotateR(grandfather);
					parent->color=BLACK;
					grandfather->color=RED;
					break;
				}
			}
			else
			{
				Node *uncle=grandfather->_left;
				if(uncle && uncle->color == RED)
				{
					parent->color=uncle->color=BLACK;
					grandfather->color=RED;
					cur=grandfather;
					parent=cur->_parent;
				}
				else   //uncle不存在或者为黑色
				{
					if(parent->_left == cur)
					{
						RotateR(parent);
						swap(cur,parent);
					}
					RotateL(grandfather);
					parent->color=BLACK;
					grandfather->color=RED;
					break;
				}
			}
		}
		_root->color=BLACK;
		return true;
	}
	bool IsRBTree()
	{
		if(_root == NULL)
			return true;
		if(_root->color == RED)    //根结点是黑色结点
			return false;

		Node *cur=_root;
		int blackNum=0;
		//统计其中一条路径上黑色结点的数量，基准值
		while(cur)
		{
			if(cur->color == BLACK)
			{
				blackNum++;
			}
			cur=cur->_left;
		}
		int count=0;    //计数器，通过计算其他路径上黑色结点的数量，与基准值做对比
		return _IsRBTree(_root,blackNum,count);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
private:
	bool _IsRBTree(Node *root,const int blackNum,int count)
	{
		if(root == NULL)
			return true;
		if(root->color == RED && root->_parent->color == RED)
		{
			cout<<"存在连续的红结点"<<endl;
			return false;
		}
		if(root->color == BLACK)
			++count;

		if(root->_left == NULL && root->_right == NULL)
		{
			if(count != blackNum)
			{
				cout<<"黑色结点的数量不相等"<<endl;
				return false;
			}
		}
		return _IsRBTree(root->_left,blackNum,count) \
			&& _IsRBTree(root->_right,blackNum,count);
	}
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void RotateL(Node *parent)
	{
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		parent->_right=subRL;
		if(subRL)
			subRL->_parent=parent;
		subR->_left=parent;
		Node *ppNode=parent->_parent;
		parent->_parent=subR;
		if(ppNode == NULL)   //_root == NULL
		{
			_root=subR;
			subR->_parent=NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left=subR;
			else
				ppNode->_right=subR;

			subR->_parent=ppNode;
		}
	}
	void RotateR(Node *parent)
	{
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		parent->_left=subLR;
		if(subLR)
			subLR->_parent=parent;
		subL->_right=parent;
		Node *ppNode=parent->_parent;
		parent->_parent=subL;
		if(ppNode == NULL)
		{
			_root=subL;
			subL->_parent=NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left=subL;
			else
				ppNode->_right=subL;

			subL->_parent=ppNode;
		}
	}
private:
	Node *_root;
};

void TestRBTree()
{
	//int array[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	int array[]={4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	RBTree<int,int> rb;
	for(int i=0;i<sizeof(array)/sizeof(array[0]);i++)
	{
		rb.Insert(array[i],i);
		cout<<array[i]<<"IsRBTree?"<<rb.IsRBTree()<<endl;
	}
	rb.InOrder();
	cout<<"IsRBTree?"<<rb.IsRBTree()<<endl;
}