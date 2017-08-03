	//根据前序和中序重建二叉树
	Node *ReBuildTree(const T *prev,int s1, const T *in,int s2)
	{
		if (prev == NULL || in == NULL || s1 != s2)
			return NULL;
		
		return _ReBuildTree(prev,0,s1,in,0,s2);
	}
	Node *_ReBuildTree(const T *prev, int start1, int end1, const T *in, int start2, int end2)
	{
		//前序遍历的第一个结点是根结点
		Node *root=new Node(prev[start1]);
		//在中序遍历中找到该结点的位置
		int pos = 0;
		while (pos < end2)
		{
			if (in[pos] == prev[start1])
			{
				break;
			}
			++pos;
		}
		int left = pos - start2;
		int right = start1 + left;
		//递归左子树
		if (left > 0)
			root->_left = _ReBuildTree(prev,start1+1,right,in,start2,pos-1);
		//递归右子树
		if (pos < end2)
			root->_right = _ReBuildTree(prev,right+1,end1,in,pos+1,end2);

		return root;
	}