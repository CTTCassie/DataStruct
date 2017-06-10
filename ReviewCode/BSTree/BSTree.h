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
		if(_root == NULL)  //����
		{
			_root=new Node(key);
			return true;
		}
		Node *cur=_root;
		Node *parent=NULL;
		while (cur)
		{
			if(cur->_key < key)   //�����в���
			{
				parent=cur;
				cur=cur->_right;
			}
			else if(cur->_key > key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else{   //�Ѿ����ڲ���Ҫ�ٴβ���
				return false;
			}
		}
		if(parent->_key < key)   //���뵽������
			parent->_right=new Node(key);
		else                  //���뵽������
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
			else   //�ҵ���
			{
				Node *del=cur;
				if(cur->_left == NULL)     //��Ϊ��
				{
					if(_root == cur)    //ɾ�����Ǹ���������Ϊ��
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
				else if(cur->_right == NULL)  //��Ϊ��
				{
					if(_root == cur)    //Ҫɾ���Ľ���Ǹ���������Ϊ��
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
				else    //���Ҷ���Ϊ�գ��滻��
				{
					Node *parent=cur;
					//�ҵ���ǰ����������������㣬Ҳ�����ҵ���ǰ��������������ҽ��
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
	bool InsertR(const K& key)    //�ݹ�汾�Ĳ���
	{
		return _InsertR(_root,key);
	}
	bool RemoveR(const K& key)   //�ݹ�汾��ɾ��
	{
		return _RemoveR(_root,key);
	}
	bool Find(const K& key)   //���ҽ��
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
		else   //Ҫ����Ľ���Ѿ�����
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
		else    //�Ѿ��ҵ���
		{
			Node *del=root;
			if(root->_left == NULL)    //��Ϊ��
				root=root->_right;
			else if(root->_right == NULL)  //��Ϊ��
				root=root->_left;
			else   //���Ҷ���Ϊ��
			{
				Node *parent=root;
				//���ҵ�ǰ�����������������
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
	void _Delete(Node *&root)   //��������ķ�ʽɾ��һ����
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