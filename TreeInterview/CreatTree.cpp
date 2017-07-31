#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cassert>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T> *_right;
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T *pre,T *in,size_t size)
	{
		assert(pre && in);
		//前序遍历的第一个结点就是根结点
		_root=new Node(pre[0]);
		_ReCreatTree(pre,in,size,_root);
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
protected:
	void _ReCreatTree(T *pre,T *in,size_t size,Node *&root)
	{
		if(size <= 0)
			return ;
		if(NULL == root)
			root=new Node(pre[0]);
		int index=0;
		while (index < size)
		{
			if(in[index] == pre[0])
				break;
			++index;
		}
		int left=index;
		int right=size-index-1;
		_ReCreatTree(pre+1,in,left,root->_left);
		_ReCreatTree(pre+index+1,in+index+1,right,root->_right);
	}
	void _PostOrder(Node *root)
	{
		if(NULL == root)
			return ;
		Node *cur=root;
		if (cur)
		{
			_PostOrder(cur->_left);
			_PostOrder(cur->_right);
			cout<<cur->_data<<" ";
		}
	}
protected:
	Node *_root;
};
void testCreatTreeByPreIn()
{
	int pre[]={0,1,3,4,2,5};
	int in[]={3,1,4,0,5,2};
	size_t size1=sizeof(pre)/sizeof(pre[0]);
	size_t size2=sizeof(in)/sizeof(in[0]);
	if(size1 == size2)
	{
		BinaryTree<int> bt(pre,in,size1);
		bt.PostOrder();
	}
	else
		cout<<"error"<<endl;
}
int main()
{
	testCreatTreeByPreIn();
	system("pause");
	return 0;
}