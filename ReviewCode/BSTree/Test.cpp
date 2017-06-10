#define _CRT_SECURE_NO_WARNINGS 1

#include "BSTree.h"

void TestBSTree()
{
	int array[]={5,3,4,1,7,8,2,6,0,9};;
	int len=sizeof(array)/sizeof(array[0]);
	BSTree<int> tree;
	for (int i=0;i<len;i++)
	{
		tree.Insert(array[i]);
	}
	tree.InOrder();
	for(int i=0;i<len;i++)
	{
		tree.Remove(array[i]);
	}
	//tree.Remove(1);
	//tree.Remove(2);
	//tree.Remove(5);
	//tree.Remove(7);
	tree.InOrder();
}

void TestBSTreeR()
{
	int array[]={5,3,4,1,7,8,2,6,0,9};;
	int len=sizeof(array)/sizeof(array[0]);
	BSTree<int> tree;
	for (int i=0;i<len;i++)
	{
		tree.InsertR(array[i]);
	}
	tree.InOrder();
	cout<<"Find 3:"<<tree.Find(3)<<endl;  //1
	//for(int i=0;i<len;i++)
	//{
	//	tree.RemoveR(array[i]);
	//}
	//tree.InOrder();
	//cout<<"Find 3:"<<tree.Find(3)<<endl;   //0
}

int main()
{
	//TestBSTree();
	TestBSTreeR();
	system("pause");
	return 0;
}