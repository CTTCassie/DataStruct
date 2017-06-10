#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	K _key;
	BSTreeNode<K> *_left;
	BSTreeNode<K> *_right;
	BSTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{
		_Delete(_root);
	}
public:
	bool Insert(const K& key)
	{
		if(_root == NULL)  //空树
		{
			_root=new Node(key);
			return true;
		}
		Node *cur=_root;
		Node *parent=NULL;
		while (cur)
		{
			if(cur->_key < key)   //右树中查找
			{
				parent=cur;
				cur=cur->_right;
			}
			else if(cur->_key > key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else{   //已经存在不需要再次插入
				return false;
			}
		}
		if(parent->_key < key)   //插入到右树中
			parent->_right=new Node(key);
		else                  //插入到左树中
			parent->_left=new Node(key);
		return true;
	}
	bool Remove(const K& key)
	{
		Node *cur=_root;
		Node *parent=NULL;
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
			else   //找到了
			{
				Node *del=cur;
				if(cur->_left == NULL)     //左为空
				{
					if(_root == cur)    //删除的是根结点而且左为空
					{
						_root=cur->_right;
					}
					else
					{
						if(parent->_left == cur)
							parent->_left=cur->_right;
						else
							parent->_right=cur->_right;
					}
				}
				else if(cur->_right == NULL)  //右为空
				{
					if(_root == cur)    //要删除的结点是根结点而且右为空
					{
						_root=cur->_left;
					}
					else
					{
						if(parent->_left == cur)
							parent->_left=cur->_left;
						else
							parent->_right=cur->_left;	
					}
				}
				else    //左右都不为空，替换法
				{
					Node *parent=cur;
					//找到当前结点右子树的最左结点，也可以找到当前结点左子树的最右结点
					Node *subLeft=cur->_right;
					while(subLeft->_left)
					{
						parent=subLeft;
						subLeft=subLeft->_left;
					}
					del=subLeft;
					cur->_key=subLeft->_key;
					if(parent->_left == subLeft)
						parent->_left=subLeft->_right;
					else
						parent->_right=subLeft->_right;
				}
				delete del;
				return true;
			}
		}
		return false;
	}
	bool InsertR(const K& key)    //递归版本的插入
	{
		return _InsertR(_root,key);
	}
	bool RemoveR(const K& key)   //递归版本的删除
	{
		return _RemoveR(_root,key);
	}
	bool Find(const K& key)   //查找结点
	{
		if(_root == NULL)
			return false;
		Node *cur=_root;
		while (cur)
		{
			if(cur->_key < key)
				cur=cur->_right;
			else if(cur->_key > key)
				cur=cur->_left;
			else
				return true;
		}
		return false;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
private:
	bool _InsertR(Node *&root,const K& key)
	{
		if(root == NULL)
		{
			root=new Node(key);
			return true;
		}
		if(root->_key < key)
			return _InsertR(root->_right,key);
		else if(root->_key > key)
			return _InsertR(root->_left,key);
		else   //要插入的结点已经存在
			return false;
	}
	bool _RemoveR(Node *&root,const K& key)
	{
		if(root == NULL)
			return false;
		if(root->_key < key)
			return _RemoveR(root->_right,key);
		else if(root->_key > key)
			return _RemoveR(root->_left,key);
		else    //已经找到了
		{
			Node *del=root;
			if(root->_left == NULL)    //左为空
				root=root->_right;
			else if(root->_right == NULL)  //右为空
				root=root->_left;
			else   //左右都不为空
			{
				Node *parent=root;
				//查找当前结点右子树的最左结点
				Node *subLeft=root->_right;
				while(subLeft->_left)
				{
					parent=subLeft;
					subLeft=subLeft->_left;
				}
				del=subLeft;
				root->_key=subLeft->_key;
				if(parent->_left == subLeft)
					parent->_left=subLeft->_right;
				else
					parent->_right=subLeft->_right;
			}
			delete del;
			return true;
		}
		return false;
	}
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void _Delete(Node *&root)   //后序遍历的方式删除一棵树
	{
		if(root == NULL)
		{
			return;
		}
		_Delete(root->_left);
		_Delete(root->_right);
		delete root;
	}
protected:
	Node *_root;
};