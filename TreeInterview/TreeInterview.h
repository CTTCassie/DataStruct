#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include <iostream>
#include <cassert>
#include<stack>
using namespace std;

template<class T>
struct TreeNode
{
	TreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
	T _data;
	TreeNode<T> *_left;
	TreeNode<T> *_right;
};

template<class T>
class Tree
{
	typedef TreeNode<T> Node;
public:
	Tree()
		:_root(NULL)
	{}
	Tree(const T* a,const size_t& size,const T& invalid)
	{
		size_t index=0;
		_root=_CreatTree(a,size,index,invalid);
	}
	~Tree()
	{
		_Destroy(_root);
	}
public:
	Node *GetRoot()
	{
		return _root;
	}
	int GetFurthestRange(Node *root)
	{
		assert(root);
		int range=0;
		_GetFurthestRange(root,range);
		return range;
	}
	void GetBinaryTreeShadow(Node *root)
	{
		if(NULL == root)
			return ;
		if((NULL == root->_left) && (NULL == root->_right))
			return ;
		Node *tmp=root->_left;
		root->_left=root->_right;
		root->_right=tmp;
		if(root->_left)
			GetBinaryTreeShadow(root->_left);
		if(root->_right)
			GetBinaryTreeShadow(root->_right);
	}
	void GetBinaryTreeShadow(Node *root)
	{
		if(NULL == root)
			return ;
		stack<Node *> s;
		s.push(root);
		while(s.size())
		{
			Node *root=s.top();
			s.pop();
			if(root->_left || root->_right)
			{
				Node *tmp=root->_left;
				root->_left=root->_right;
				root->_right=tmp;
			}
			if(root->_left)
				s.push(root->_left);
			if(root->_right)
				s.push(root->_right);
		}
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
protected:
	void _PrevOrder(Node *root)
	{
		Node *cur=root;
		if(cur)
		{
			cout<<cur->_data<<" ";
			_PrevOrder(cur->_left);
			_PrevOrder(cur->_right);
		}
	}
	void _InOrder(Node *root)
	{
		Node *cur=root;
		if(cur)
		{
			_InOrder(cur->_left);
			cout<<cur->_data<<" ";
			_InOrder(cur->_right);
		}
	}
	void _PostOrder(Node *root)
	{
		Node *cur=root;
		if(cur)
		{
			_PostOrder(cur->_left);
			_PostOrder(cur->_right);
			cout<<cur->_data<<" ";
		}
	}
	int _GetFurthestRange(Node *root,int& range)
	{
		if(root == NULL)
			return 0;
		int leftFR=_GetFurthestRange(root->_left,range);
		int rightFR=_GetFurthestRange(root->_right,range);
		if(leftFR+rightFR > range)
			range=leftFR+rightFR;
		return leftFR > rightFR ? leftFR+1 : rightFR+1;
	}
	Node *_CreatTree(const T* a,size_t size,size_t& index,const T& invalid)
	{
		assert(a);
		Node *root=NULL;
		if(index < size && a[index] != invalid)
		{
			root=new Node(a[index]);
			root->_left=_CreatTree(a,size,++index,invalid);
			root->_right=_CreatTree(a,size,++index,invalid);
		}
		return root;
	}
	void _Destroy(Node *&root)
	{
		if(root == NULL)
			return ;
		Node *cur=root;
		if(cur)
		{
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete cur;
			cur=NULL;
		}
	}
protected:
	Node *_root;
};