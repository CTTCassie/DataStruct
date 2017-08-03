struct BinaryTreeNode
{
	int _data;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
	BinaryTreeNode(const int& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};
class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const int *array, size_t size, const char& invaild)
	{
		size_t index = 0;
		_root=_CreateTree(array, size, invaild, index);
	}
	Node *Convert()
	{
		Node *last = NULL;
		//last指向转换之后的最后一个结点
		ConvertNode(_root,last);
		Node *head = last;
		//head指向转换之后的第一个结点
		while (head && head->_left)
		{
			head = head->_left;
		}
		return head;
	}
	void ConvertNode(Node *root, Node *&last)
	{
		if (root == NULL)
			return;
		Node *cur = root;
		if (cur->_left)
		{
			ConvertNode(cur->_left, last);
		}
		cur->_left = last;
		if (last)
		{
			last->_right = cur;
		}
		last = cur;
		if (cur->_right)
		{
			ConvertNode(cur->_right,last);
		}
	}
	void InOrder(Node *root, queue<Node *>& q)
	{
		if (root == NULL)
			return;

		InOrder(root->_left,q);
		q.push(root);
		InOrder(root->_right,q);
	}
	Node *ConvertNoR()
	{
		if (_root == NULL)
			return NULL;

		queue<Node *>q;
		InOrder(_root,q);

		Node *prev = q.front();
		q.pop();
		prev->_left = NULL;
		Node *pHead = prev;  //保存头结点
		while (!q.empty())
		{
			Node *cur = q.front();
			q.pop();
			cur->_left = prev;
			prev->_right = cur;
			prev = cur;
		}
		prev->_right = NULL;
		return pHead;
	}
private:
	Node *_CreateTree(const int *array, size_t size, const char& invaild, size_t& index)
	{
		assert(array);
		Node *root = NULL;
		if (index < size && array[index] != invaild)
		{
			root = new Node(array[index]);
			root->_left = _CreateTree(array,size,invaild,++index);
			root->_right = _CreateTree(array,size,invaild,++index);
		}
		return root;
	}
private:
	Node *_root;
};
void Display(BinaryTreeNode *pHead)
{
	if (pHead == NULL)
		return;
	BinaryTreeNode *cur = pHead;
	while (cur)
	{
		cout << cur->_data << " ";
		cur = cur->_right;
	}
	cout << endl;
}
void TestTree()
{
	int array[] = { 10, 6, 4, '#', '#', 8, '#', '#', 14, 12, '#', '#', 16 };
	size_t size = sizeof(array) / sizeof(array[0]);
	BinaryTree tree(array,size,'#');
	//BinaryTreeNode *res=tree.Convert();
	BinaryTreeNode *res = tree.ConvertNoR();
	Display(res);
}
