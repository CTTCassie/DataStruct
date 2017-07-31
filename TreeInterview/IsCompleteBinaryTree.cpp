#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cassert>
#include<queue>
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
	BinaryTree(const T*a,size_t size,const T& invalid)
	{
		size_t index=0;
		_root=_CreatTree(a,size,index,invalid);
	}
	//设置标志位的方法
	bool IsCompleteBinaryTree1()
	{
		bool flag=false;
		queue<Node *>q;
		q.push(_root);
		Node *cur=q.front();
		while (cur)
		{
			//有右孩子无左孩子
			if(cur->_left == NULL && cur->_right != NULL)
				return false;
			//标志位为true并且当前结点存在孩子
			if(flag == true && (cur->_left || cur->_right))
				return false;
			//如果当前结点少一个孩子
			if(cur->_left == NULL || cur->_right == NULL)
				flag=true;
			if(cur->_left)
				q.push(cur->_left);
			if(cur->_right)
				q.push(cur->_right);
			q.pop();
			if(!q.empty())
				cur=q.front();
			else
				cur=NULL;
		}
		return true;
	}
	//利用辅助队列的办法
	bool IsCompleteBinaryTree2()
	{
		queue<Node *>q;
		q.push(_root);
		Node *cur=q.front();
		//按照层序遍历的办法入队列直到遇到第一个NULL停止
		while (cur)
		{
			q.push(cur->_left);
			q.push(cur->_right);
			q.pop();
			cur=q.front();
		}
		//如果队列中全为NULL则是完全二叉树，否则不是
		while(!q.empty())
		{
			if(q.front())
				return false;
			q.pop();
		}
		return true;
	}
protected:
	Node* _CreatTree(const T*a,size_t size,size_t& index,const T& invalid)
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
protected:
	Node *_root;
};
void testIsCompleteTree()
{
	//int array[]={0,1,3,'#','#','#',2,4,'#','#',5};    //false
	//int array[]={0,1,3,'#','#',4,'#','#',2,5,'#','#','#'}; //true
	//int array[]={0,1,3,'#','#',4,'#','#',2};  //true
	int array[]={0,1,3,'#','#','#',2};
	size_t size=sizeof(array)/sizeof(array[0]);
	BinaryTree<int> bt(array,size,'#');
	bool ret=bt.IsCompleteBinaryTree2();
	if(ret == true)
		cout<<"是完全二叉树"<<endl;
	else
		cout<<"不是完全二叉树"<<endl;
}
int main()
{
	testIsCompleteTree();
	system("pause");
	return 0;
}