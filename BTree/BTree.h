#pragma once

#include<iostream>
using namespace std;

template<class K,class V,int M>   //M������Ǻ��ӵ�����
struct BTreeNode
{
	//���һ�����ڷ���
	pair<K, V> _kvs[M];
	BTreeNode<K, V, M> *_subs[M+1];
	BTreeNode<K, V, M> *_parent;
	size_t _size;    //ʵ�ʴ洢�Ľ�����
	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (int i = 0; i < M + 1; ++i)
		{
			_kvs[i] = make_pair(K(),V());   //_kvs�ĳ�ʼ����ֵ�ǿ�
			_subs[i] = NULL;
		}
	}
};

template<class K,class V,int M>
class BTree
{
	typedef BTreeNode<K, V, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	pair<Node *, int> FindNode(const K& key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i < cur->_size)
			{
				if (cur->_kvs[i].first == key)
					return make_pair(cur, i);
				else if (cur->_kvs[i].first > key)
					break;
				else
					i++;
			}
			//��ʱ���������������1��������cur��β�� 2���ҵ�����ȷ��λ��
			parent = cur;
			cur = cur->_subs[i];
		}
		return make_pair(parent,-1);
	}
	void InsertKV(Node *cur, pair<K,V> newKV, Node *sub)   //sub�����Ǻ��ӽ��Ҳ�����ǿս��
	{
		int end = cur->_size - 1;
		while (end >= 0)
		{
			if (cur->_kvs[end].first < newKV.first)
				break;
			else    //cur->_kvs[end].first > kv.first
			{
				cur->_kvs[end + 1] = cur->_kvs[end];
				cur->_subs[end + 2] = cur->_subs[end+1];   //Ų�������Һ���
				--end;
			}
		}
		cur->_kvs[end + 1] = newKV;
		//���º��Ӻ͸���
		cur->_subs[end + 2] = sub;
		if (sub)
		{
			sub->_parent = cur;
		}
		cur->_size++;
	}
	bool Insert(pair<K, V> kv)
	{
		if (_root == NULL)   //����
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			_root->_size = 1;
			return true;
		}
		pair<Node *, int> res = FindNode(kv.first);
		if (res.second != -1)   //ԭ����B���д��ڸ�kv
		{
			return false;
		}
		Node *cur = res.first;
		Node *sub = NULL;
		pair<K,V> newKV = kv;
		while (1)
		{
			InsertKV(cur, newKV, sub);
			if (cur->_size < M)   //���û�������ɹ�
			{
				return true;
			}
			//��������Ҫ���з���
			Node *brother = new Node;
			int mid = cur->_size / 2;
			int j = 0;
			for (size_t i = mid + 1; i < cur->_size; ++i)
			{
				brother->_kvs[j] = cur->_kvs[i];
				//��cur�ĺ���ҲҪ������ȥ
				if (cur->_subs[i])
				{
					brother->_subs[j] = cur->_subs[i];  //��������
					brother->_subs[j + 1] = sub;        //�����Һ���
					cur->_subs[i] = NULL;
					//�������Һ��ӵĸ��ڵ�
					brother->_subs[j]->_parent = brother;
					brother->_subs[j + 1]->_parent = brother;
				}
				brother->_size++;
				cur->_kvs[i] = make_pair(K(),V());
				cur->_size--;
				j++;
			}
			//���ѵ������
			if (cur->_parent == NULL)
			{
				_root = new Node;
				//��midλ�õĽ�㿽�����ϲ㣬���¸��׵����Һ���
				_root->_kvs[0] = cur->_kvs[mid];
				_root->_subs[0] = cur;
				_root->_subs[1] = brother;
				_root->_size++;

				cur->_kvs[mid] = make_pair(K(),V());
				cur->_size--;
				//����cur��brother�ĸ����
				cur->_parent = _root;
				brother->_parent = _root;
				return true;
			}
			//��δ���µ������
			newKV = cur->_kvs[mid];
			cur->_kvs[mid] = make_pair(K(),V());
			cur->_size--;
			sub = brother;
			cur = cur->_parent;
		}
		return true;
	}
private:
	void _InOrder(Node *root)
	{
		if (root == NULL)
			return;
		size_t i = 0;
		for (; i < root->_size; i++)
		{
			_InOrder(root->_subs[i]);
			cout << root->_kvs[i].first << " ";
		}
		_InOrder(root->_subs[i]);
	}
protected:
	Node *_root;
};

void TestBTree()
{
	int arr[] = { 53, 75, 139, 49, 145, 36, 101 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	BTree<int,int, 3> tree;
	for (size_t i = 0; i < size; i++)
	{
		tree.Insert(make_pair(arr[i], i));
	}
	tree.InOrder();
}