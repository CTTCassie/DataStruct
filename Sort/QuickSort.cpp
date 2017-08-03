//快排的左右指针法
int PartSort1(int *arr,int begin,int end)
{
	int left = begin;
	int right = end;
	int key = arr[end];   //选择最后一个值做关键字
	while (left < right)
	{
		while (left < right && arr[left] <= key)
		{
			++left;
		}
		while (left < right && arr[right] >= key)
		{
			--right;
		}
		if (left < right)
		{
			swap(arr[left],arr[right]);
		}
	}
	swap(arr[right],arr[end]);
	return left;
}
//快排的挖坑法
int PartSort2(int *arr, int begin, int end)
{
	int left = begin;
	int right = end;
	int key = arr[end];  //选择最后一个值做关键字
	while (left < right)
	{
		while (left < right && arr[left] < key)
		{
			++left;
		}
		swap(arr[left],arr[right]);
		while (left < right && arr[right] > key)
		{
			--right;
		}
		swap(arr[right],arr[right]);
	}
	arr[left] = key;
	return left;
}
//快排的前后指针法-->可用于单链表的排序，在这里给的区间是左闭右开的区间
int PartSort3(int *arr, int start, int end)
{
	int prev = start;
	int cur = start+1;
	int key = arr[start];
	while (cur != end)
	{
		//cur向前遍历找到比prev小的值
		if (arr[cur] < key)
		{
			//如果cur和prev不指向相同的位置才交换cur和prev的下一个位置
			++prev;
			if (cur != prev)
			{
				swap(arr[cur],arr[prev]);
			}
		}
		++cur;
	}
	swap(arr[prev],arr[start]);
	return prev;
}
void QuickSort(int *arr,int begin,int end)
{
	assert(arr);
	if (begin < end)
	{
		//int mid = PartSort1(arr,start,end);
		//int mid = PartSort2(arr,start,end);
		int mid = PartSort3(arr, begin, end+1);
		QuickSort(arr, begin, mid-1);
		QuickSort(arr, mid + 1, end);
	}
}
void QuickSortNoR(int *arr, int begin, int end)
{
	stack<int> s;  //借助一个栈来实现，先入右区间，再入左区间
	s.push(end);
	s.push(begin);
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();
		int mid = PartSort1(arr,left,right); //划分的两段区间  left mid-1 mid+1 right
		if (left < mid - 1)
		{
			s.push(mid - 1);
			s.push(left);
		}
		if (mid + 1 < right)
		{
			s.push(right);
			s.push(mid + 1);
		}
	}
}