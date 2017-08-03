void Merge(int *arr, int *tmp, int begin1, int end1, int begin2, int end2)
{
	//类似有序链表的合并
	int pos = begin1;
	int index = pos;
	//找到两段区间中较小的那一个插入到tmp辅助数组中
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
			tmp[index++] = arr[begin1++];
		else
			tmp[index++] = arr[begin2++];
	}
	//有可能其中一个还没有插完
	while (begin1 <= end1)
	{
		tmp[index++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = arr[begin2++];
	}
	//将tmp的对应位置的元素拷贝到arr中去
	memcpy(arr+pos,tmp+pos,sizeof(int)*(end2-pos+1));
}
void _Merge(int *arr, int *tmp, int begin, int end)
{
	if (begin >= end)
		return;
	//划分子区间
	int mid = begin + (end - begin) / 2;
	_Merge(arr,tmp,begin,mid);
	_Merge(arr, tmp, mid + 1, end);
	//合并对应区间有序
	Merge(arr,tmp,begin,mid,mid+1,end);
}
//递归的归并排序
void MergeSort(int *arr,int size)
{
	int *tmp = new int[size];   //创建辅助空间
	_Merge(arr,tmp, 0, size - 1);
	delete[]tmp;
}
//归并排序的非递归
void MergeSortNoR(int *arr,int size)
{
	int begin1, end1, begin2, end2;
	int *tmp = new int[size];   //创建辅助空间
	for (int i = 1; i < size; i *= 2)   //划分子区间
	{
		for (begin1 = 0; begin1 <= size - i; begin1 = end2)
		{
			end1 = begin1 + i;  //确定区间的下标
			begin2 = begin1 + i;
			end2 = end1 + i;
			if (end2 > size)   //有可能end2越界了
				end2 = size;

			int index = 0;
			//选取较小的一个值插入到tmp的对应位置处
			while (begin1 < end1 && begin2 < end2)
			{
				if (arr[begin1] < arr[begin2])
					tmp[index++] = arr[begin1++];
				else
					tmp[index++] = arr[begin2++];
			}
			while (begin1 < end1)
			{
				arr[--begin2] = arr[--end1];
			}
			while (index > 0)
			{
				arr[--begin2] = tmp[--index];
			}
		}
	}
	delete[]tmp;
}