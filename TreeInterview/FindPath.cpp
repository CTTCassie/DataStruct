#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cassert>
#include<vector>
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
	BinaryTree(const T* a,size_t size,const T& invalid)
	{
		size_t index=0;
		_root=_CreatTree(a,size,index,invalid);
	}
	void FindPath(int num)
	{
		assert(num >= 0);
		vector<Node *>path;
		int cur=0;
		_FindPath(_root,num,path,cur);
	}
protected:
	void _FindPath(Node *root,int num,vector<Node *>& path,int& cur)
	{
		cur += root->_data;
		path.push_back(root);
		//是叶子结点而且路径上的值和输入的值相等
		if(root->_left == NULL && root->_right == NULL && cur == num)
		{
			cout<<"Legal Path:";
			vector<Node *>::iterator it=path.begin();
			while (it != path.end())
			{
				cout<<(*it)->_data<<" ";
				++it;
			}
			cout<<endl;
		}
		//不是叶子结点则继续遍历左子树和右子树
		if(root->_left)
			_FindPath(root->_left,num,path,cur);
		if (root->_right)
			_FindPath(root->_right,num,path,cur);
		//如果不是则返回上层结点并修改cur的值
		cur -= root->_data;
		path.pop_back();
	}
	Node *_CreatTree(const T* a,size_t size,size_t& index,const T& invalid)
	{
		Node *root=NULL;
		assert(a);
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
void testFindPath()
{
	int array[]={10,5,4,'#','#',7,'#','#',12};
	size_t size=sizeof(array)/sizeof(array[0]);
	BinaryTree<int> bt(array,size,'#');
	int index=0;
	cout<<"请输入需要查找路径的整数:";
	cin>>index;
	bt.FindPath(index);
}
int main()
{
	testFindPath();
	system("pause");
	return 0;
}