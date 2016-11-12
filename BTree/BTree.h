#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

template<class K,int M>
struct BTreeNode
{
	//多给一个便于分裂
	K _keys[M];                //关键字数组
	BTreeNode<K,M> *_sub[M+1]; //链接子树的指针数组
	BTreeNode<K,M> *_parent;
	int _size;                 //关键字的个数
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i=0;i<M;++i)
		{
			_keys[i]=K();
			_sub[i]=NULL;
		}
		_sub[M]=NULL;
	}
};

template<class K,int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	pair<Node *,int> Find(const K& key)
	{
		Node *cur=_root;
		Node *parent=NULL;
		while (cur)
		{
			int i=0;
			while (i < cur->_size)
			{
				if (cur->_keys[i] < key)
					++i;
				else if(cur->_keys[i] > key)
					break;
				else                         //找到了
					return pair<Node *,int>(cur,i);
			}
			parent=cur;
			cur=cur->_sub[i];
		}
		return pair<Node *,int>(parent,-1);   //没有找到
	}
	bool Insert(const K& key)
	{
		if (_root == NULL)     //空树
		{
			_root=new Node;
			_root->_keys[0]=key;
			_root->_size=1;
			return true;
		}
		pair<Node *,int> ret=Find(key);
		if(ret.second != -1)        //找到了不再插入
			return false;

		Node *cur=ret.first;
		Node *sub=NULL;
		K NewKey=key;
		while (1)
		{
			InsertKey(cur,NewKey,sub);
			if(cur->_size < M)    //如果cur没满则停止
				return true;
			//cur满,分裂，拷贝key和孩子
			size_t mid=cur->_size/2;
			Node *tmp=new Node;
			int j=0;
			for (int i=mid+1;i<cur->_size;++i)
			{
				tmp->_keys[j]=cur->_keys[i];
				//连续分裂
				if (cur->_sub[i])
				{
					tmp->_sub[j]=cur->_sub[i];
					tmp->_sub[j+1]=sub;
					cur->_sub[i]=NULL;
					tmp->_sub[j]->_parent=tmp;
					tmp->_sub[j+1]->_parent=tmp;
				}
				tmp->_size++;
				cur->_keys[i]=K();
				cur->_size--;
				j++;
			}
			if(cur->_parent == NULL)       //分裂到根结点
			{
				_root=new Node;
				_root->_keys[0]=cur->_keys[mid];
				_root->_sub[0]=cur;
				_root->_sub[1]=tmp;
				_root->_size++;
				cur->_keys[mid]=K();
				cur->_size--;

				tmp->_parent=_root; //链接
				cur->_parent=_root;
				return true;
			}
			//没有分裂到根结点
			NewKey=cur->_keys[mid];
			cur->_keys[mid]=K();
			cur->_size--;
			sub=tmp;
			cur=cur->_parent;
		}
		return true;
	}
	void InsertKey(Node *cur,const K& key,Node *sub)
	{
		int i=cur->_size-1;
		while (i >= 0)
		{
			if (cur->_keys[i] < key)
				break;
			else
			{
				cur->_keys[i+1]=cur->_keys[i];
				cur->_sub[i+2]=cur->_sub[i+1];
				--i;
			}
		}
		cur->_keys[i+1]=key;
		cur->_sub[i+2]=sub;
		if(sub)
			sub->_parent=cur;
		cur->_size++;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
public:
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return ;
		_InOrder(root->_sub[0]);
		for (int i=0;i<root->_size;++i)
		{
			cout<<root->_keys[i]<<" ";
		}
		for (int i=1;i<M;++i)
		{
			_InOrder(root->_sub[i]);
		}
	}
protected:
	Node *_root;
};

void testBTree()
{
	int array[]={53, 75, 139, 49, 145, 36,101};
	int size=sizeof(array)/sizeof(array[0]);
	BTree<int,3> tree;
	for (int i=0;i<size;++i)
	{
		tree.Insert(array[i]);
	}
	tree.InOrder();
}