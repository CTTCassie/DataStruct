	//单链表的排序之冒泡和快排
	void BullSortList(LinkNode *head)
	{
		if (head == NULL || head->_next == NULL)  //空链表或者只有一个结点
			return;
		LinkNode *tail = NULL;
		LinkNode *cur = head;
		while (cur != tail)
		{
			bool flag = false;
			LinkNode *next = cur->_next;
			while (next != tail)
			{
				if (cur->_data > next->_data)
				{
					swap(cur->_data,next->_data);
					flag = true;
				}
				cur = next;
				next = cur->_next;
			}
			if (flag == false)
			{
				break;
			}
			tail = cur;   //更新尾结点,每次缩小比较的空间
			cur = head;
		}
	}
	void QuickSort(LinkNode *head,LinkNode *tail)
	{
		if (head == NULL || head == tail || head->_next == NULL)
			return;
		int key = head->_data;
		LinkNode *prev = head;
		LinkNode *cur = head->_next;
		while (cur != tail)
		{
			if (cur->_data < key) //找到一个比key小的值
			{
				prev = prev->_next;
				if (prev != cur)   //可能找到相同的位置
				{
					swap(prev->_data, cur->_data);
				}
			}
			cur = cur->_next;
		}
		swap(prev->_data,head->_data);
		//划分区间
		QuickSort(head,prev);
		QuickSort(prev->_next,tail);
	}