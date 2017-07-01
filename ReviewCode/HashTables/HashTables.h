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
	struct __Hash<string>  //特化
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

		bool LineSurvey(const pair<K,V>& kv,size_t& index)  //线性探测
		{
			while(_tables[index]._state == EXIST)
			{
				//开始探测
				if(_tables[index]._kv.first == kv.first)  //存在
				{
					return false;
				}
				//线性探测
				++index;
				if(index == _tables.size())
				{
					index=0;
				}
			}
			return true;
		}
		bool SquareSurvey(const pair<K,V>& kv,size_t& index)   //二次探测
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
				 //当二次探测越界的时候，使得新的index模哈希表的长度，此时的index就是找到的位置
				index %= _tables.size();
			}
			return true;
		}
		bool Insert(const pair<K,V>& kv)
		{
			CheckCapacity();
			size_t index=_HashFunc(kv.first);

			if(LineSurvey(kv,index))  //线性探测插入位置
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
					else   //状态是删除DELETE
						return NULL;
				}
				++index;   //开始查找下一个位置
				if(index == _tables.size())   //找到数组的结尾
				{
					index=0;
				}
			}
			return NULL;
		}
		bool Remove(const K& key)   //伪删除法
		{
			Node *res=FindNode(key);
			if(res)
			{
				res->_state=DELETE;
				_size--;
				return true;
			}
			else   //该结点不存在
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
			if(_tables.empty())   //空表
			{
				_tables.resize(GetNextPrime(0));
			}
			else
			{   //扩容
				if(_size*10 % _tables.size() == 7)   //控制载荷因子小于0.7
				{
					size_t newSize=GetNextPrime(_tables.size());

					HashTables<K,V> newTables;    //构造新表
					newTables._tables.resize(newSize);

					for(size_t i=0;i<_tables.size();i++)
					{
						if(_tables[i]._state == EXIST)
						{
							newTables.Insert(_tables[i]._kv);
						}
					}
					_tables.swap(newTables._tables);   //交换新表与原表
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
		size_t _size;       //实际插入哈希表中的元素个数
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

		for(size_t i=0;i<80;i++)   //测试扩容
		{
			tables.Insert(make_pair<int,int>(i,i));
		}
		//tables.ShowHashTables();

		HashTables<string,string,__Hash<string>> dict;
		dict.Insert(make_pair<string,string>("left","左边"));
		dict.Insert(make_pair<string,string>("right","右边"));
		dict.Insert(make_pair<string,string>("sort","排序"));
		dict.Insert(make_pair<string,string>("tfel","左边"));
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
		static size_t BKDRHash(const char *str)   //字符串哈希算法，使得字符串转变为整形
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
			//不存在的话就头插
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
				if(cur->_kv.first == key)   //删除
				{
					if(prev)   //删除的是中间节点或者是尾结点
						prev->_next=cur->_next;
					else       //prev == NULL 删除的是第一个结点
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
			if(_tables.size() == _size)   //此时的载荷因子为1
			{
				vector<Node *> newHash;
				size_t prime=GetNextPrime(_tables.size());
				newHash.resize(prime);
				for(size_t i=0;i<_tables.size();i++)   //遍历原哈希表
				{
					Node *cur=_tables[i];
					while(cur)
					{
						Node *next=cur->_next;
						size_t index=_HashFunc(cur->_kv.first,newHash.size());   //计算在新表中的键值
						//头插
						cur->_next=newHash[index];
						newHash[index]=cur;

						cur=next;
					}
					_tables[i]=NULL;   //插入到新表之后原表的位置置NULL
				}
				_tables.swap(newHash);  //交换原表与新表
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
		dict.Insert(make_pair("left","左边"));
		dict.Insert(make_pair("right","右边"));
		dict.Insert(make_pair("sort","排序"));
		dict.Insert(make_pair("tfel","左边"));
	}
}