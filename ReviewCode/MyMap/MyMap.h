#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<string>

enum Color
{
	RED,
	BLACK,
};

template<class KV>
struct RBTreeNode
{
	KV _kv;
	RBTreeNode<KV> *_left;
	RBTreeNode<KV> *_right;
	RBTreeNode<KV> *_parent;
	Color color;
	RBTreeNode(const KV& kv)  //新增结点是红色的
		:_kv(kv)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,color(RED)
	{}
};

template<class KV,class KVRef,class KVPtr>
struct RBTreeIterator
{
	typedef RBTreeNode<KV> Node;
	typedef RBTreeIterator<KV,KVRef,KVPtr> Self;

	RBTreeIterator(Node *node)
		:_node(node)
	{}
	KVRef operator*()
	{
		return _node->_kv;
	}
	KVPtr operator->()
	{
		return &(operator*());
	}
	Self& operator++()     //找中序遍历的下一个结点
	{
		if(_node->_right == NULL)   //右树为空
		{
			Node *cur=_node;
			Node *parent=cur->_parent;
			while(parent)
			{
				if(parent->_left == cur)  //cur是parent的左
				{
					_node=parent;
					break;
				}
				else     //cur是parent的右
				{
					cur=parent;
					parent=cur->_parent;
				}
			}
			//
			_node=parent;
		}
		else    //右树不为空
		{
			Node *subLeft=_node->_right;   //找右树的最左结点
			while(subLeft->_left)
			{
				subLeft=subLeft->_left;
			}
			_node=subLeft;
		}
		return *this;
	}
	Self& operator--()
	{

	}
	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
	Node *_node;
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<pair<K,V>> Node;
public:
	typedef RBTreeIterator<pair<K,V>,pair<K,V>&,pair<K,V>*> Iterator;

	RBTree()
		:_root(NULL)
	{}
	~RBTree()
	{
		_destroy(_root);
	}
	Iterator Begin()   //返回最左结点
	{
		Node *cur=_root;
		while(cur && cur->_left)
		{
			cur=cur->_left;
		}
		return Iterator(cur);
	}
	Iterator End()
	{
		return Iterator(NULL);
	}
	bool Insert(const pair<K,V>& kv)
	{
		if(_root == NULL)    //根结点是黑色的
		{
			_root=new Node(kv);
			_root->color=BLACK;
			return true;
		}
		Node *parent=NULL;
		Node *cur=_root;
		while(cur)
		{
			if(cur->_kv.first < kv.first)
			{
				parent=cur;
				cur=cur->_right;
			}
			else if(cur->_kv.first > kv.first)
			{
				parent=cur;
				cur=cur->_left;
			}
			else    //找到了
			{
				return false;
			}
		}
		cur=new Node(kv);   //插入新节点
		if(parent->_kv.first < kv.first)
		{
			parent->_right=cur;
			cur->_parent=parent;
		}
		else
		{
			parent->_left=cur;
			cur->_parent=parent;
		}

		while(parent && parent->color == RED)   //parent存在且parent的颜色是红色的，不存在连续的红结点
		{
			Node *grandfather=parent->_parent;  //祖父结点
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
					if(parent->_right == cur) //情况3
					{
						RotateL(parent);
						swap(cur,parent);   //旋转之后，交换cur和parent的位置
					}
					RotateR(grandfather);    //情况2
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
	bool Find(const K& key)
	{
		Node *cur=_root;
		while(cur)
		{
			if(cur->_kv.first < key)
			{
				cur=cur->_right;
			}
			else if(cur->_kv.first > key)
			{
				cur=cur->_left;
			}
			else   //找到了
			{
				return true;
			}
		}
		return false;
	}
	Node *FindMinNode()   //最小结点是最左结点
	{
		Node *cur=_root;
		while(cur->_left)
		{
			cur=cur->_left;
		}
		return cur;
	}
	Node *FindMaxNode()   //最大结点是最右结点
	{
		Node *cur=_root;
		while(cur->_right)
		{
			cur=cur->_right;
		}
		return cur;
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
	void RotateL(Node *parent)   //左单旋
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
	void RotateR(Node *parent)   //右单旋
	{
		Node *subL=parent->_left;
		Node *subLR=subL->_right;

		parent->_left=subLR;
		if(subLR)
			subLR->_parent=parent;

		subL->_right=parent;
		Node *ppNode=parent->_parent;
		parent->_parent=subL;

		if(ppNode == NULL)    //_root == NULL
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
	void _destroy(Node *&root)
	{
		if(root == NULL)
			return;
		_destroy(root->_left);
		_destroy(root->_right);
		delete root;
	}
private:
	Node *_root;
};

void TestMap()
{
	RBTree<string,string> dict;
	dict.Insert(make_pair<string,string>("left","左边"));
	dict.Insert(make_pair<string,string>("right","右边"));
	dict.Insert(make_pair<string,string>("sort","排序"));

	RBTree<string,string>::Iterator it=dict.Begin();
	while(it != dict.End())
	{
		cout<<it->first<<" "<<it->second<<endl;
		++it;
	}
}
void TestRBTree()
{
	int array[]={4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	RBTree<int,int> tree;
	for(size_t i=0;i<sizeof(array)/sizeof(array[0]);i++)
	{
		tree.Insert(make_pair(array[i],i));
	}
	RBTreeNode<pair<int,int>> *min=tree.FindMinNode();
	RBTreeNode<pair<int,int>> *max=tree.FindMaxNode();
}