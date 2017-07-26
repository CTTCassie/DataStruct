#include<iostream>
using namespace std;
#include<cassert>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T> *_right;
	BinaryTreeNode(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
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
	BinaryTree(const T *array, size_t size, const T& invaild)
	{
		size_t index = 0;
		_root = _CreateTree(array, size, invaild, index);
	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
	Node *GetRoot()
	{
		return _root;
	}
	//判断一个结点是否在一棵二叉树中
	bool JudgeNode(const T& data)
	{
		return _JudgeNode(_root,data);
	}
	//判断一颗树是否是另外一颗树的子树
	bool HasSubTree(Node *root1, Node *root2)
	{
		if (root2 == NULL)   //空树是任何树的子树
			return true;
		if (root1 == NULL)   //任何数不是空树的子树
			return false;
		bool res = false;
		if (root1 && root2)
		{
			//根结点相同
			if (root1->_data == root2->_data)
				res=JudgeSubTree(root1->_left,root2->_left);

			if (res == false)
				res=HasSubTree(root1->_left,root2);   //左子树中找

			if (res == false)
				res=HasSubTree(root1->_right,root2);  //右子树中找
		}
		return res;
	}
private:
	bool JudgeSubTree(Node *root1, Node * root2)
	{
		if (root2 == NULL)
			return true;
		if (root1 == NULL)
			return false;

		if (root1->_data != root2->_data)
			return false;
		//左右子树也都必须一样
		return JudgeSubTree(root1->_left, root2->_right) && \
			JudgeSubTree(root1->_right, root2->_right);
	}
	bool _JudgeNode(Node *root, const T& data)
	{
		if (root == NULL)
			return false;

		if (root->_data == data)
			return true;
		
		return _JudgeNode(root->_left, data) || _JudgeNode(root->_right,data);
	}
	Node *_CreateTree(const T *array, size_t size, const T& invaild, size_t& index)
	{
		assert(array);
		Node *root = NULL;
		if (index < size && array[index] != invaild)
		{
			root = new Node(array[index]);
			root->_left = _CreateTree(array, size, invaild, ++index);
			root->_right = _CreateTree(array,size,invaild,++index);
		}
		return root;
	}
	void _Destroy(Node *root)
	{
		if (root == NULL)
			return;

		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
private:
	Node *_root;
};
void TestTree()
{
	int array[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', '#', 7, 8 };
	size_t size = sizeof(array)/sizeof(array[0]);
	BinaryTree<int> tree(array,size,'#');
	cout << tree.JudgeNode(1) << endl;   //1
	cout << tree.JudgeNode(2) << endl;   //1
	cout << tree.JudgeNode(3) << endl;   //1
	cout << tree.JudgeNode(4) << endl;   //1
	cout << tree.JudgeNode(5) << endl;   //1
	cout << tree.JudgeNode(6) << endl;   //1
	cout << tree.JudgeNode(7) << endl;   //1
	cout << tree.JudgeNode(8) << endl;   //1
	cout << tree.JudgeNode(9) << endl;   //0
	cout << tree.JudgeNode(10) << endl;  //0
}
void TestSubTree()
{
	int array1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', '#', 7, 8 };
	int array2[] = { 4, 5, '#', '#', 7 };
	size_t size1 = sizeof(array1) / sizeof(array1[0]);
	size_t size2 = sizeof(array2) / sizeof(array2[0]);
	BinaryTree<int> t1(array1,size1,'#');
	BinaryTree<int> t2(array2,size2,'#');
	cout << t1.HasSubTree(t1.GetRoot(), t2.GetRoot()) << endl;;
}


int main()
{
	//TestTree();
	TestSubTree();
	system("pause");
	return 0;
}