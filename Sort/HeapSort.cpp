//升序建大堆，降序建小堆
void AdjustDown(int *arr, int root, int size)   //建堆,时间复杂度是O(N)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child < size)
	{
		//child指向孩子中较大的那个孩子
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			++child;
		}
		//使得父亲是最大的那个结点
		if (arr[parent] < arr[child])
		{
			swap(arr[parent],arr[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int *arr, int size)
{
	assert(arr);
	//从倒数第一个非叶子结点开始建堆
	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		AdjustDown(arr,i,size);
	}
	int end = size - 1;
	for (; end >= 0; end--)
	{
		swap(arr[0],arr[end]);   //交换堆顶和end所处位置的元素
		AdjustDown(arr,0,end);   //0~end之间重新建堆
	}
}