void SelectSort(int *arr, int size)
{
	assert(arr);
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		//在left~right区间中找到最大和最小值
		int max = arr[left];
		int min = arr[right];
		for (int i = left; i <= right; i++)
		{
			if (arr[i] < arr[min])
				min = i;
			if (arr[i] > arr[max])
				max = i;
		}
		//交换left和min，right和max所对应的值
		swap(arr[left],arr[min]);
		if (left == max)
		{
			max = min;
		}
		swap(arr[right],arr[max]);
		++left;
		--right;
	}
}