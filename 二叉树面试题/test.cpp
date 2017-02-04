#define _CRT_SECURE_NO_WARNINGS 1

#include "TreeInterview.h"

void testTree()
{
	//int array[]={1,2,3,4,'#','#',5};
	//int array[]={1,2,4,'#',6,'#',3,'#',5};
	int array[]={1,2,4,6,8,'#','#','#','#',5,'#',7,'#',9,'#','#',3};
	size_t size=sizeof(array)/sizeof(array[0]);
	Tree<int> tree(array,size,'#');
	int ret=tree.GetFurthestRange(tree.GetRoot());
	cout<<"FurthestRange>"<<ret<<endl;
}
void testShadow()
{
	//int array[]={8,6,5,'#','#',7,'#','#',10,9,'#','#',11};
	int array[]={8,6,5,9,3,'#','#'};
	size_t size=sizeof(array)/sizeof(array[0]);
	Tree<int> tree(array,size,'#');
	tree.InOrder();
	tree.GetBinaryTreeShadow(tree.GetRoot());
	tree.InOrder();
}
int main()
{
	//testTree();
	testShadow();
	system("pause");
	return 0;
}