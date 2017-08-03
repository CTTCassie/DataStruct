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
				res = JudgeSubTree(root1->_left, root2->_left);

			if (res == false)
				res = HasSubTree(root1->_left, root2);   //左子树中找

			if (res == false)
				res = HasSubTree(root1->_right, root2);  //右子树中找
		}
		return res;
	}
	bool JudgeSubTree(Node *root1, Node * root2)
	{
		if (root2 == NULL)
			return true;
		if (root1 == NULL)
			return false;

		if (root1->_data != root2->_data)
			return false;
		//左右子树也都必须一样
		return JudgeSubTree(root1->_left, root2->_left) && \
			JudgeSubTree(root1->_right, root2->_right);
	}