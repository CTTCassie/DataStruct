#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
template<class T>
struct TreeNode
{
	T _data;
	TreeNode<T> *_left;
	TreeNode<T> *_right;
	TreeNode<T> *_parent;
	TreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};
template<class T>
class ThreeBinaryTree
{
	typedef TreeNode<T> Node;
public:
	ThreeBinaryTree()
		:_root(NULL)
	{}
	ThreeBinaryTree(const T*a,size_t size,const T& invalid)
	{
		size_t index=0;
		Node *parent=NULL;
		_root=_CreatTree(a,size,index,parent,invalid);
	}
	int FindPublicLowParent(const T& index1,const T& index2)
	{
		if(index1 == index1)
			return index1;
		Node *first=NULL;
		_FindNode(_root,index1,first);
		Node *second=NULL;
		_FindNode(_root,index2,second);
		//从该结点到叶子结点的路径长
		int count1=1;
		int count2=1;
		Node *cur=first;
		while(cur->_parent)
		{
			count1++;
			cur=cur->_parent;
		}
		cur=second;
		while(cur->_parent)
		{
			count2++;
			cur=cur->_parent;
		}
		//求两条路径的差值
		int sub=abs(count1-count2);
		if(count1 >= count2)
			_FindFirstParentNode(first,second,sub);
		else
			_FindFirstParentNode(second,first,sub);
	}
protected:
	int _FindFirstParentNode(Node *first,Node *second,int sub)
	{
		//使路径较长的先走sub步
		while(--sub)
		{
			first=first->_parent;
		}
		//此时令两个结点同时向前走
		//找到的第一个相同的结点就是满足题意的
		while(first != second)
		{
			first=first->_parent;
			second=second->_parent;
		}
		return first->_data;
	}
	//前序遍历查找结点
	void _FindNode(Node *root,const T&index,Node *&node)
	{
		if(NULL == root)
			return ;
		if(root->_data == index)
			node=root;
		_FindNode(root->_left,index,node);
		_FindNode(root->_right,index,node);
	}
	Node *_CreatTree(const T* a,size_t size,size_t& index,Node *parent,const T& invalid)
	{
		assert(a);
		Node *root=NULL;
		if(index < size && a[index] != invalid)
		{
			root=new Node(a[index]);
			root->_parent=parent;
			root->_left=_CreatTree(a,size,++index,root,invalid);
			root->_right=_CreatTree(a,size,++index,root,invalid);
		}
		return root;
	}
protected:
	Node *_root;
};

void testThreeTree()
{
	int array[]={1,2,3,'#','#',4,'#','#',5,6,'#','#','#'};
	size_t size=sizeof(array)/sizeof(array[0]);
	ThreeBinaryTree<int> bt(array,size,'#');
	int ret=bt.FindPublicLowParent(2,4);
	cout<<"存在最低公共祖先:"<<ret<<endl;
}