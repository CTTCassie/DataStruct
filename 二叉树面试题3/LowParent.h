#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T> *_right;
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};
template<class T>
class PublicLowParent
{
	typedef BinaryTreeNode<T> Node;
public:
	PublicLowParent()
		:_root(NULL)
	{}
	PublicLowParent(const T* a,size_t size,const T& invalid)
	{
		size_t index=0;
		_root=_CreatTree(a,size,index,invalid);
	}
	~PublicLowParent()
	{
		_Destroy(_root);
	}
public:
	//�����Ƕ��������������
	Node *FindPublicLowParent(const T& index1,const T& index2)
	{
		Node *cur=_root;
		while (cur)
		{
			//������ֵ������Ҫ���ҽ���ֵ�������������в���
			if(cur->_data > index1 && cur->_data > index2)
			{
				cur=cur->_left;
			}
			//������ֵ������Ҫ���ҽ���ֵ��С�����������в���
			else if(cur->_data < index1 && cur->_data < index2)
			{
				cur=cur->_right;
			}
			//�ҵ���͹������Ƚ��
			else if(cur->_data >= index1 && cur->_data <= index2
				|| cur->_data <= index1 && cur->_data >= index2)
			{
				return cur;
			}
		}
		return NULL;
	}
	//��������������Ҳ�����ڸ����
	Node *FindLowParent(const T& index1,const T& index2)
	{
		return _FindLowParentNode(_root,index1,index2);
	}
protected:
	Node *_FindLowParentNode(Node *root,const T& index1,const T& index2)
	{
		Node *first=NULL;
		Node *second=NULL;
		if(NULL == root)
			return NULL;
		if(root->_data == index1 || root->_data == index2)
			return root;
		first=_FindLowParentNode(root->_left,index1,index2);
		second=_FindLowParentNode(root->_right,index1,index2);
		if(first && second)
			return root;
		return first ? first : second;
	}
	Node *_CreatTree(const T* a,size_t size,size_t& index,const T& invalid)
	{
		assert(a);
		Node *root=NULL;
		if(index < size && a[index] != invalid)
		{
			root=new Node(a[index]);
			root->_left=_CreatTree(a,size,++index,invalid);
			root->_right=_CreatTree(a,size,++index,invalid);
		}
		return root;
	}
	void Destroy(Node *&root)
	{
		if(NULL == root)
			return ;
		Node *cur=root;
		if(cur)
		{
			Destroy(cur->_left);
			Destroy(cur->_right);
			delete cur;
			cur=NULL;
		}
	}
protected:
	Node *_root;
};
void testPublicLowParent()
{
	int array[]={8,6,5,'#','#',7,'#','#',10,9,'#','#',11};
	size_t size=sizeof(array)/sizeof(array[0]);
	PublicLowParent<int> bt(array,size,'#');
	BinaryTreeNode<int> *ret=bt.FindPublicLowParent(10,11);
	if(ret != NULL)
		cout<<"������͹�������:"<<ret->_data<<endl;
	else
		cout<<"��������͹�������"<<endl;
	PublicLowParent<int> bt1(array,size,'#');
	BinaryTreeNode<int> *ret1=bt1.FindLowParent(6,5);
	if(ret1 != NULL)
		cout<<"������͹�������:"<<ret1->_data<<endl;
	else
		cout<<"��������͹�������"<<endl;
}