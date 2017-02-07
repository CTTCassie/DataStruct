#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stack>
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
	//Node *FindPublicLowParent(const T& index1,const T& index2)
	//{
	//	Node *cur=_root;
	//	while (cur)
	//	{
	//		//������ֵ������Ҫ���ҽ���ֵ�������������в���
	//		if(cur->_data > index1 && cur->_data > index2)
	//		{
	//			cur=cur->_left;
	//		}
	//		//������ֵ������Ҫ���ҽ���ֵ��С�����������в���
	//		else if(cur->_data < index1 && cur->_data < index2)
	//		{
	//			cur=cur->_right;
	//		}
	//		//�ҵ���͹������Ƚ��
	//		else if(cur->_data >= index1 && cur->_data <= index2
	//			|| cur->_data <= index1 && cur->_data >= index2)
	//		{
	//			return cur;
	//		}
	//	}
	//	return NULL;
	//}
	////��������������Ҳ�����ڸ����
	//Node *FindLowParent(const T& index1,const T& index2)
	//{
	//	return _FindLowParentNode(_root,index1,index2);
	//}
	//Node *_FindLowParentNode(Node *root,const T& index1,const T& index2)
	//{
	//	Node *first=NULL;
	//	Node *second=NULL;
	//	if(NULL == root)
	//		return NULL;
	//	if(root->_data == index1 || root->_data == index2)
	//		return root;
	//	first=_FindLowParentNode(root->_left,index1,index2);
	//	second=_FindLowParentNode(root->_right,index1,index2);
	//	if(first && second)
	//		return root;
	//	return first ? first : second;
	//}
	//����ջ����·�����ҵ���һ��key��ͬ�Ľ��
	Node * FindPublicParentNode(const T& index1,const T& index2)
	{
		int sub=0;
		stack<Node *>s1;
		_FindPath(_root,s1,index1);
		stack<Node *>s2;
		_FindPath(_root,s2,index2);
		if(s1.size() > s2.size())
		{
			sub=s1.size()-s2.size();
			return _FindFirstParentNode(s1,s2,sub);
		}
		else   //s1.size() <= s2.size()
		{
			sub=s2.size()-s1.size();
			return _FindFirstParentNode(s2,s1,sub);
		}
		return NULL;
	}
	Node *_FindFirstParentNode(stack<Node *>s1,stack<Node *>s2,int sub)
	{
		//ʹ����·������sub��
		while(sub--)
		{
			s1.pop();
		}
		//����ջһ��ֱ���ҵ���һ����ͬ��Ԫ��
		while(!s1.empty() && !s2.empty() && s1.top() != s2.top())
		{
			s1.pop();
			s2.pop();
		}
		return s1.top();
	}
	bool _FindPath(Node *root,stack<Node *>&s,const T index)
	{
		if(NULL == root)
			return false;
		if(root->_data == index)
		{
			s.push(root);
			return true;
		}
		s.push(root);
		bool left=_FindPath(root->_left,s,index);
		bool right=_FindPath(root->_right,s,index);
		if(left == false && right == false)
		{
			s.pop();
			return false;
		}
		return true;
	}
protected:
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
	//int array[]={8,6,5,'#','#',7,'#','#',10,9,'#','#',11};
	int array[]={0,1,3,5,'#','#',6,'#','#',4,7,'#','#',8,'#','#',2};
	size_t size=sizeof(array)/sizeof(array[0]);
	PublicLowParent<int> bt(array,size,'#');
	BinaryTreeNode<int> *ret=bt.FindPublicParentNode(5,4);
	cout<<"������͹�������:"<<ret->_data<<endl;
}