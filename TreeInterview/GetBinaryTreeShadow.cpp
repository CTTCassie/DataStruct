	//求二叉树的镜像,递归
	void GetBinaryTreeShadow(Node *root)
	{
		if (root == NULL)  //空树
			return;

		if (root->_left == NULL && root->_right == NULL)  //叶子结点
			return;

		Node *tmp = root->_left;
		root->_left = root->_right;
		root->_right = tmp;

		if (root->_left)
			GetBinaryTreeShadow(root->_left);

		if (root->_right)
			GetBinaryTreeShadow(root->_right);

	}
	//非递归
	void GetBinaryTreeShadowNoR(Node *root)
	{
		if (root == NULL)
			return;

		stack<Node *> s;  //辅助栈
		s.push(root);

		while (!s.empty())
		{
			Node *top = s.top();
			s.pop();
			//交换左右子树
			Node *tmp = top->_left;
			top->_left = top->_right;
			top->_right = tmp;
			//如果左右子树不为空的话则继续递归
			if (top->_left)
				s.push(top->_left);

			if (top->_right)
				s.push(top->_right);
		}
	}