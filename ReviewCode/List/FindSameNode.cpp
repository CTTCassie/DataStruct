	//求已排序单链表的相同数据,要求时间复杂度为O(1)
	vector<LinkNode *> FindSameNode(LinkNode *pHead1, LinkNode *pHead2)
	{
		vector<LinkNode *> tmp;
		if (pHead1 == NULL || pHead2 == NULL)
			return tmp;
		LinkNode *cur1 = pHead1;
		LinkNode *cur2 = pHead2;
		while (cur1 && cur2)
		{
			//两个指针不相同则让小的数据先走
			if (cur1->_data < cur2->_data)
			{
				cur1 = cur1->_next;
			}
			else if (cur1->_data > cur2->_data)
			{
				cur2 = cur2->_next;
			}
			else   //两个指针相同则同时向后遍历
			{
				tmp.push_back(cur1);
				cur1 = cur1->_next;
				cur2 = cur2->_next;
			}
		}
		return tmp;
	}