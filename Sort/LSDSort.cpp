int GetMaxDigit(int *arr, int size)
{
	int base = 10;   //标识数量级
	int digit = 1;   //统计最大的位数
	for (int i = 0; i < size; i++)
	{
		while (arr[i] > base)
		{
			++digit;
			base *= 10;
		}
	}
	return digit;
}
void LSDSort(int *arr, int size)
{
	assert(arr);
	int base = 1;
	//求出数组中的最大的位数
	int digit = GetMaxDigit(arr,size);
	int *count = new int[10];
	memset(count,0,sizeof(int)*10);
	int *start = new int[10];
	start[0] = 0;
	int *tmp = new int[size];
	while (digit--)
	{
		//count统计数字出现的次数
		for (int i = 0; i < size; i++)
		{
			count[(arr[i] / base) % 10]++;
		}
		//计算每个数字的起始位置
		for (int i = 1; i < 10; i++)
		{
			start[i] = start[i - 1] + count[i - 1];
		}
		//将数据写到辅助数组tmp中
		for (int i = 0; i < size; i++)
		{
			int num = (arr[i] / base) % 10;
			tmp[start[num]] = arr[i];
			start[num]++;
		}
		//将tmp中的内容写到arr中
		for (int i = 0; i < size; i++)
		{
			arr[i] = tmp[i];
		}
		base *= 10;
	}
	delete[]tmp;
}