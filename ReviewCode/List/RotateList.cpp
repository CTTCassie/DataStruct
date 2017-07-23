namespace Link
{
	struct LinkNode
	{
		int _data;
		LinkNode *_next;
		LinkNode(const int& data = 0)
			:_data(data)
			, _next(NULL)
		{}
	};
	LinkNode *Reverse(LinkNode *pHead)
	{
		if (pHead == NULL || pHead->_next == NULL)
			return pHead;
		LinkNode *cur = pHead;
		LinkNode *newHead = NULL;
		LinkNode *newCur = NULL;
		while (cur)
		{
			newCur = cur;
			cur = cur->_next;
			newCur->_next = newHead;
			newHead = newCur;
		}
		return newHead;
	}
	LinkNode *RotateList1(LinkNode *pHead, size_t k)
	{
		if (pHead == NULL || pHead->_next == NULL || k < 2)
			return pHead;

		LinkNode *tail = pHead;
		//使得tail指向第k个节点
		for (size_t i = 1; i < k; i++)
		{
			tail = tail->_next;
		}
		//将第k个节点与后续节点截断
		LinkNode *cur = tail->_next;
		//只翻转前面一部分数据
		tail->_next = NULL;
		LinkNode *newHead=Reverse(pHead);
		//再将后续节点挂在翻转之后链表的后面
		tail = newHead;
		while (tail->_next)
		{
			tail = tail->_next;
		}
		tail->_next = cur;
		return newHead;
	}
	//链表中不满足k的数据不逆置
	LinkNode *RotateList2(LinkNode *pHead, int k)
	{
		if (pHead == NULL || pHead->_next == NULL || k < 2)
			return pHead;
		LinkNode *tail = pHead;
		//tail找到分组的结尾元素
		for (int i = 0; i < k; ++i)
		{
			if (tail)
				tail = tail->_next;
			else   //链表的个数连一个k都无法满足
				return pHead;
		}
		//nextTail查找下一个分组的结尾元素
		LinkNode *nextTail = RotateList2(tail, k);
		//Reverse
		LinkNode *cur = pHead;
		LinkNode *newHead = NULL;
		LinkNode *newCur = NULL;
		while (cur != tail)
		{
			newCur = cur;
			cur = cur->_next;
			newCur->_next = newHead ? newHead : nextTail;
			newHead = newCur;
		}
		return newHead;
	}
	//链表中不满足k分组的也要逆置
	LinkNode *RotateList3(LinkNode *pHead, int k)
	{
		if (pHead == NULL || pHead->_next == NULL || k < 2)
			return pHead;

		LinkNode *cur = pHead;
		LinkNode *newHead = NULL;
		LinkNode *newCur = NULL;
		int count = 0;
		//每逆置一个元素count就增加1
		while (cur != NULL && count < k)
		{
			newCur = cur;
			cur = cur->_next;
			newCur->_next = newHead;
			newHead = newCur;
			count++;
		}
		//跳出循环有两种情况
		//1、cur遍历到链表结尾
		//2、其中一个分组已经完成
		if (cur != NULL)
		{
			//链表尚未遍历完
			pHead->_next=RotateList3(cur,k);
		}
		return newHead;
	}
	void DisplayList(LinkNode *pHead)
	{
		if (pHead == NULL)
			return;
		LinkNode *cur = pHead;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
	void TestRotateList()
	{
		LinkNode *n1 = new LinkNode(1);
		LinkNode *n2 = new LinkNode(2);
		LinkNode *n3 = new LinkNode(3);
		LinkNode *n4 = new LinkNode(4);
		LinkNode *n5 = new LinkNode(5);
		LinkNode *n6 = new LinkNode(6);
		n1->_next = n2;
		n2->_next = n3;
		n3->_next = n4;
		n4->_next = n5;
		n5->_next = n6;

		DisplayList(n1);
		LinkNode *newHead=RotateList3(n1,4);
		DisplayList(newHead);
	}
}