//计数排序,时间复杂度为O(N+范围)
void CountSort(int *arr, int size)
{
	assert(arr);
	int max = arr[0];
	int min = arr[0];
	//找到最大最小值
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int range = max - min + 1;
	int *tmp = new int[range];
	memset(tmp,0,sizeof(int)*range);
	//统计出现的次数
	for (int i = 0; i < size; i++)
	{
		tmp[arr[i] - min]++;
	}
	//还原arr
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		while (tmp[i]--)
		{
			arr[index++] = i + min;
		}
	}
	delete[]tmp;
}