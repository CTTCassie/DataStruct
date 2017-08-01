void BubbleSort(int *arr, int size)
{
	assert(arr);
	bool flag = false;
	int m = 0;
	int n = 0;
	int s = size - 1;
	for (int i = 1; i < size; i++)
	{
		//正序扫描将最大值向后走
		for (int j = n; j < s; j++)  //i次排序的循环长度取决于i-1次排序时最后的交换位置
		{
			if (arr[j] > arr[j + 1])
			{
				flag = true;
				swap(arr[j],arr[j+1]);
				m = j;   //记录i-1次排序最后的交换位置
			}
		}
		s = m;   //更新最后一次交换的位置
		if (!flag)
			break;
		//反向扫描将最小值往前面走
		for (int j = s; j > n; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				swap(arr[j],arr[j-1]);
				flag = true;
			}
		}
		n++;
		if (!flag)   //排序一趟已经有序
			break;
	}
}