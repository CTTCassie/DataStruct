//1、求二叉树中两个结点的最近的公共祖先-->三叉链
namespace ThreeTree
{
	template<class T>
	struct ThreeTreeNode
	{
		T _data;
		ThreeTreeNode<T> *_left;
		ThreeTreeNode<T> *_right;
		ThreeTreeNode<T> *_parent;
		ThreeTreeNode(const T& data)
			:_data(data)
			, _left(NULL)
			, _right(NULL)
		{}
	};
	template<class T>
	class ThreeTree
	{
		typedef ThreeTreeNode<T> Node;
	public:
		ThreeTree()
			:_root(NULL)
		{}
		ThreeTree(const T *array, size_t size, const T& invaild)
		{
			size_t index = 0;
			Node *parent = NULL;
			_root=_CreateThreeTree(array,size,invaild,index,parent);
		}
		~ThreeTree()
		{
			_Destroy(_root);
		}
		void FindNodeR(Node *root, const T& data, Node *&node)
		{
			if (root == NULL)
				return;

			if (root->_data == data)
				node = root;

			FindNodeR(root->_left,data,node);

			FindNodeR(root->_right,data,node);
		}
		int FindLowPublicParent(const T& d1, const T& d2)
		{
			int count1 = 1;
			int count2 = 1;
			//找到两个结点的对应位置
			Node *n1 = NULL;
			FindNodeR(_root,d1,n1);
			Node *n2 = NULL;
			FindNodeR(_root,d2,n2);
			//统计两条不同路径上结点的数量
			Node *cur = n1;
			while (cur->_parent)
			{
				count1++;
				cur = cur->_parent;
			}
			cur = n2;
			while (cur->_parent)
			{
				count2++;
				cur = cur->_parent;
			}
			Node *res = NULL;
			
			if (count1 >= count2)
				res=_FindLowPPNode(n1, n2, count1 - count2);
			else
				res=_FindLowPPNode(n2, n1, count2 - count1);

			return res->_data;
		}
	private:
		//另长的路径先走差值步，然后两个路径上的结点一起向前走
		Node *_FindLowPPNode(Node *n1, Node *n2, int sub)
		{
			while (sub--)
			{
				n1 = n1->_parent;
			}
			while (n1 && n2)
			{
				n1 = n1->_parent;
				n2 = n2->_parent;
				if (n1 == n2)
				{
					return n1;
				}
			}
			return NULL;
		}
		Node *_CreateThreeTree(const T *array, size_t size, const T& invaild, size_t& index,Node *parent)
		{
			assert(array);
			Node *root = NULL;
			if (index < size && array[index] != invaild)
			{
				root = new Node(array[index]);
				root->_parent = parent;
				root->_left = _CreateThreeTree(array,size,invaild,++index,root);
				root->_right = _CreateThreeTree(array,size,invaild,++index,root);
			}
			return root;
		}
		void _Destroy(Node *&root)
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
	void TestThreeTree()
	{
		int array[] = { 0, 1, 3, 5, '#', '#', 6, '#', '#', 4, 7, '#', '#', 8, '#', '#', 2 };
		size_t size = sizeof(array) / sizeof(array[0]);
		ThreeTree<int> tree(array, size, '#');
		cout << tree.FindLowPublicParent(5, 7) << endl;  //Node-->1
		cout << tree.FindLowPublicParent(5, 4) << endl;  //Node-->1
		cout << tree.FindLowPublicParent(3, 2) << endl;  //Node-->0
	}
}


//2、求二叉树中两个结点的最近的公共祖先-->是搜索二叉树
Node *FindLowPublicParent(const T& d1, const T& d2)
{
	Node *cur = _root;
	while (cur)
	{
		if (cur->_data > d1 && cur->_data > d2)
		{
			cur = cur->_left;
		}
		else if (cur->_data < d1 && cur->_data < d2)
		{
			cur = cur->_right;
		}
		//找到了
		else if ((cur->_data >= d1 && cur->_data <= d2) \
			|| (cur->_data <= d1 && cur->_data >= d2))
		{
			return cur;
		}
	}
	return NULL;
}


//3、求二叉树中两个结点的最近的公共祖先-->是普通的二叉树
//(1)、递归的方法，遍历了两次该二叉树
Node *FLPPNodeNormal(const T& d1, const T& d2)
{
	return _FLPPNodeNormal(_root, d1, d2);
}
Node *_FLPPNodeNormal(Node *root, const T& d1, const T& d2)
{
	if (root == NULL)
		return NULL;
	if (root->_data == d1 || root->_data == d2)
		return root;
	Node *left = _FLPPNodeNormal(root->_left, d1, d2);
	Node *right = _FLPPNodeNormal(root->_right, d1, d2);
	//两个结点分别在左右子树中
	if (left && right)
		return root;

	return left ? left : right;
}

//(2)、利用两个栈，时间复杂度为O(N)
//使得长的先pop掉差值的元素，然后两个栈一起pop
Node *_FLPPNodeNormalNoR(stack<Node *> s1, stack<Node *>s2, int sub)
{
	while (sub--)
	{
		s1.pop();
	}
	while (!s1.empty() && !s2.empty())
	{
		s1.pop();
		s2.pop();
		if (s1.top() == s2.top())
		{
			return s1.top();
		}
	}
	return NULL;
}
Node *FLPPNodeNormalNoR(const T& d1, const T& d2)
{
	//查找两条路径并存入辅助栈中
	stack<Node *> s1;
	_FindPath(_root, d1, s1);

	stack<Node *> s2;
	_FindPath(_root, d2, s2);

	if (s1.size() > s2.size())
		return _FLPPNodeNormalNoR(s1, s2, s1.size() - s2.size());
	else
		return _FLPPNodeNormalNoR(s2, s1, s2.size() - s1.size());

}
//找到结点所对应的路径并存入辅助栈中
bool _FindPath(Node *root, const T& d, stack<Node *>& s)
{
	if (root == NULL)
		return false;
	if (root->_data == d)
	{
		s.push(root);
		return true;
	}
	s.push(root);
	bool left = _FindPath(root->_left, d, s);
	bool right = _FindPath(root->_right, d, s);
	if (left == false && right == false)
	{
		s.pop();
		return false;
	}
	return true;
}