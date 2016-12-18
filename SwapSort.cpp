#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include<cassert>
using namespace std;

//void SwapSort(char *pArr,int *pPos,int n)
//{
//	assert(pArr);
//	assert(pPos);
//	int *tmp=new int[n];
//	for (int i=0;i<n;++i)
//	{
//		tmp[i]=pArr[pPos[i]];
//	}
//	for (int i=0;i<n;++i)
//	{
//		pArr[i]=tmp[i];
//	}
//	delete []tmp;
//}


void SwapSort(char *pArr,int *pPos,int n)
{
	int i=0;
	char tmp=0;
	int count=0;    //记录排序过的数据个数
	int flag=0;     //标记坑的位置
	assert(pArr);
	assert(pPos);
	while (count < n)
	{
		if (i == pPos[i])
		{
			i++;
			count++;
		}
		else
		{
			tmp=pArr[i];
			flag=i;
			while (1)
			{
				pArr[i]=pArr[pPos[i]];
				i=pPos[i];
				count++;
				if(flag == pPos[i])    //如果此位置恰好要填tmp
					break;
			}
			pArr[i]=tmp;
			count++;
			//如果tmp不是在最后一次才被填入正确的位置
			//从当前坑的下一个位置做新的坑
			i=flag+1;
		}
	}
}

int main()
{
	char pArr[]={'A','B','C','D','E'};
	//int pPos[]={3,0,1,4,2};
	//int pPos[]={3,4,1,0,2};
	int pPos[]={2,0,1,4,3};
	int size=sizeof(pArr)/sizeof(pArr[0]);
	SwapSort(pArr,pPos,size);
	for (int i=0;i<size;++i)
	{
		cout<<pArr[i]<<" ";
	}
	cout<<endl;
	system("pause");
	return 0;
}