#define _CRT_SECURE_NO_WARNINGS 1

void Display(int *a,size_t size)
{
	for (size_t i=0;i<size;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
//升序
void InsertSort(int *a,size_t size)
{
	assert(a);
	for (size_t i=1;i<size;++i)
	{
		int tmp=a[i];
		int pos=i-1;
		while (pos >= 0 && a[pos] > tmp)
		{
			a[pos+1]=a[pos];
			--pos;
		}
		a[pos+1]=tmp;
	}
}

void ShellSort(int *a,size_t size)
{
	int gap=size;
	while(gap > 1)
	{
		gap=gap/3+1;     //确定增量
		for (size_t i=gap;i<size;++i)
		{
			int tmp=a[i];
			int pos=i-gap;
			while (pos >= 0 && a[pos] > tmp)
			{
				a[pos+gap]=a[pos];
				pos -= gap;
			}
			a[pos+gap]=tmp;
		}
	}
}

void testSort()
{
	int a[]={2,5,4,9,3,6,8,7,1,0};
	size_t size=sizeof(a)/sizeof(a[0]);
	InsertSort(a,size);
	Display(a,size);
	ShellSort(a,size);
	Display(a,size);
}