#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>


namespace OpenHash
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE,
	};
	template<class K,class V>
	struct HashNode
	{
		pair<K,V> _kv;
		State _state;
		HashNode()
			:_state(EMPTY)
		{}
	};

	template<class K>
	struct __Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>   
	struct __Hash<string>  //�ػ�
	{
		static size_t BKDRHash(const char *str)
		{
			size_t seed= 131;// 31 131 1313 13131 131313
			size_t hash= 0;
			while(*str)
			{
				hash=hash*seed+ (*str++);
			}
			return(hash& 0x7FFFFFFF);
		}
		size_t operator()(const string& s)
		{
			return BKDRHash(s.c_str());
		}
	};
	template<class K,class V,class HashFunc=__Hash<K>>
	class HashTables
	{
		typedef HashNode<K,V> Node;
	public:
		HashTables()
			:_size(0)
		{}

		bool LineSurvey(const pair<K,V>& kv,size_t& index)  //����̽��
		{
			while(_tables[index]._state == EXIST)
			{
				//��ʼ̽��
				if(_tables[index]._kv.first == kv.first)  //����
				{
					return false;
				}
				//����̽��
				++index;
				if(index == _tables.size())
				{
					index=0;
				}
			}
			return true;
		}
		bool SquareSurvey(const pair<K,V>& kv,size_t& index)   //����̽��
		{
			int i=1;
			while(_tables[index]._state == EXIST)
			{
				if(_tables[index]._kv.first == kv.first)
				{
					return false;
				}
				index += i*i;
				i += 1;
				 //������̽��Խ���ʱ��ʹ���µ�indexģ��ϣ��ĳ��ȣ���ʱ��index�����ҵ���λ��
				index %= _tables.size();
			}
			return true;
		}
		bool Insert(const pair<K,V>& kv)
		{
			CheckCapacity();
			size_t index=_HashFunc(kv.first);

			if(LineSurvey(kv,index))  //����̽�����λ��
			{
				_tables[index]._kv=kv;
				_tables[index]._state=EXIST;

				_size++;
			}
			return true;
		}
		Node *FindNode(const K& key)
		{
			size_t index=_HashFunc(key);
			while(_tables[index]._state != EMPTY)
			{
				if(_tables[index]._kv.first == key)
				{
					if(_tables[index]._state == EXIST)
						return &_tables[index];
					else   //״̬��ɾ��DELETE
						return NULL;
				}
				++index;   //��ʼ������һ��λ��
				if(index == _tables.size())   //�ҵ�����Ľ�β
				{
					index=0;
				}
			}
			return NULL;
		}
		bool Remove(const K& key)   //αɾ����
		{
			Node *res=FindNode(key);
			if(res)
			{
				res->_state=DELETE;
				_size--;
				return true;
			}
			else   //�ý�㲻����
			{
				return false;
			}
		}
		void ShowHashTables()
		{
			for(size_t i=0;i<_tables.size();i++)
			{
				if(_tables[i]._state == EXIST)
				{
					cout<<_tables[i]._kv.first<<" ";
				}
			}
			cout<<endl;
		}
	private:
		size_t GetNextPrime(size_t size)
		{
			const int _PrimeSize= 28;
			static const unsigned long_PrimeList[_PrimeSize] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for(size_t i=0;i<_PrimeSize;i++)
			{
				if(long_PrimeList[i] > size)
				{
					return long_PrimeList[i];
				}
			}
			return long_PrimeList[_PrimeSize-1];
		}
		void CheckCapacity()
		{
			if(_tables.empty())   //�ձ�
			{
				_tables.resize(GetNextPrime(0));
			}
			else
			{   //����
				if(_size*10 % _tables.size() == 7)   //�����غ�����С��0.7
				{
					size_t newSize=GetNextPrime(_tables.size());

					HashTables<K,V> newTables;    //�����±�
					newTables._tables.resize(newSize);

					for(size_t i=0;i<_tables.size();i++)
					{
						if(_tables[i]._state == EXIST)
						{
							newTables.Insert(_tables[i]._kv);
						}
					}
					_tables.swap(newTables._tables);   //�����±���ԭ��
				}
			}
		}
		size_t _HashFunc(const K& key)
		{
			HashFunc hash;
			return hash(key)%_tables.size();
		}
	protected:
		vector<Node> _tables;
		size_t _size;       //ʵ�ʲ����ϣ���е�Ԫ�ظ���
	};
	void TestHashTables()
	{
		int array[]={89,18,49,58,9};
		HashTables<int,int> tables;
		for(size_t i=0;i<sizeof(array)/sizeof(array[0]);i++)
		{
			tables.Insert(make_pair<int,int>(array[i],i));
		}
		tables.Remove(9);
		cout<<tables.FindNode(9)<<endl;

		for(size_t i=0;i<80;i++)   //��������
		{
			tables.Insert(make_pair<int,int>(i,i));
		}
		//tables.ShowHashTables();

		HashTables<string,string,__Hash<string>> dict;
		dict.Insert(make_pair<string,string>("left","���"));
		dict.Insert(make_pair<string,string>("right","�ұ�"));
		dict.Insert(make_pair<string,string>("sort","����"));
		dict.Insert(make_pair<string,string>("tfel","���"));
	}
}

namespace HashBucket
{
	template<class K,class V>
	struct HashNode
	{
		pair<const K,V> _kv;
		HashNode<K,V> *_next;
		HashNode(const pair<K,V> kv)
			:_kv(kv)
			,_next(NULL)
		{}
	};

	template<class K>
	struct __Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct __Hash<string>
	{
		static size_t BKDRHash(const char *str)   //�ַ�����ϣ�㷨��ʹ���ַ���ת��Ϊ����
		{
			unsigned int seed= 131;// 31 131 1313 13131 131313
			unsigned int hash= 0;
			while(*str)
			{
				hash=hash*seed+ (*str++);
			}
			return(hash& 0x7FFFFFFF);
		}
		size_t operator()(const string& s)
		{
			return BKDRHash(s.c_str());
		}
	};

	template<class K,class V,class HashFunc=__Hash<K>>
	class HashTables
	{
		typedef HashNode<K,V> Node;
	public:
		HashTables()
			:_size(0)
		{}
		bool Insert(const pair<K,V>& kv)
		{
			CheckCapacity();
			size_t index=_HashFunc(kv.first,_tables.size());

			Node *cur=_tables[index];
			while(cur)
			{
				if(cur->_kv.first == kv.first)
					return false;
				cur=cur->_next;
			}
			//�����ڵĻ���ͷ��
			Node *newNode=new Node(kv);
			
			newNode->_next=_tables[index];
			_tables[index]=newNode;

			_size++;
			return true;
		}
		Node *FindNode(const K& key)
		{
			for(size_t i=0;i<_tables.size();i++)
			{
				Node *cur=_tables[i];
				while(cur)
				{
					if(cur->_kv.first == key)
						return cur;

					cur=cur->_next;
				}
			}
			return NULL;
		}
		bool Remove(const K& key)
		{
			size_t index=_HashFunc(key,_tables.size());
			Node *cur=_tables[index];
			Node *prev=NULL;
			while(cur)
			{
				if(cur->_kv.first == key)   //ɾ��
				{
					if(prev)   //ɾ�������м�ڵ������β���
						prev->_next=cur->_next;
					else       //prev == NULL ɾ�����ǵ�һ�����
						_tables[index]=cur->_next;

					delete cur;
					_size--;
					return true;
				}
				prev=cur;
				cur=cur->_next;
			}
			return false;
		}
	private:
		size_t GetNextPrime(size_t size)
		{
			const int _PrimeSize= 28;
			static const unsigned long_PrimeList[_PrimeSize] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for(int i=0;i<_PrimeSize;i++)
			{
				if(long_PrimeList[i] > size)
					return long_PrimeList[i];
				else
					continue;
			}
			return long_PrimeList[_PrimeSize-1];
		}
		void CheckCapacity()
		{
			if(_tables.size() == _size)   //��ʱ���غ�����Ϊ1
			{
				vector<Node *> newHash;
				size_t prime=GetNextPrime(_tables.size());
				newHash.resize(prime);
				for(size_t i=0;i<_tables.size();i++)   //����ԭ��ϣ��
				{
					Node *cur=_tables[i];
					while(cur)
					{
						Node *next=cur->_next;
						size_t index=_HashFunc(cur->_kv.first,newHash.size());   //�������±��еļ�ֵ
						//ͷ��
						cur->_next=newHash[index];
						newHash[index]=cur;

						cur=next;
					}
					_tables[i]=NULL;   //���뵽�±�֮��ԭ���λ����NULL
				}
				_tables.swap(newHash);  //����ԭ�����±�
			}
		}
		size_t _HashFunc(const K& key,size_t size)
		{
			HashFunc hash;
			return hash(key)%size;
		}
	protected:
		vector<Node *> _tables;
		size_t _size;
	};
	void TestHashTables()
	{
		int array[]={51,105,52,3,55,2,106,53,0};
		HashTables<int,int> tables;
		for(int i=0;i<sizeof(array)/sizeof(array[0]);i++)
		{
			tables.Insert(make_pair(array[i],i));
		}
		for(int i=0;i<80;i++)
		{
			tables.Insert(make_pair(i,i));
		}
		tables.Remove(2);
		tables.Remove(55);
		cout<<tables.FindNode(2)<<endl;
		cout<<tables.FindNode(55)<<endl;

		HashTables<string,string,__Hash<string>> dict;
		dict.Insert(make_pair("left","���"));
		dict.Insert(make_pair("right","�ұ�"));
		dict.Insert(make_pair("sort","����"));
		dict.Insert(make_pair("tfel","���"));
	}
}