#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<map>
#include<set>
#include<vector>
#include<string>

void TestSet()
{
	//set是K类型的
	set<string> Myset;
	Myset.insert("left");
	Myset.insert("right");
	Myset.insert("high");
	Myset.insert("low");
	Myset.insert("right");
	Myset.insert("right");
	cout<<"size?"<<Myset.size()<<endl;  //4
	cout<<"max_size?"<<Myset.max_size()<<endl;
	set<string>::iterator it=Myset.begin();
	while(it != Myset.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	cout<<Myset.count("right")<<endl;   //1 统计right出现的次数,set是去重的
	it=Myset.find("left");
	if(it != Myset.end())    //找到了
	{
		cout<<*it<<endl;     //left
	}
	//Myset.erase(it);      //删除一个迭代器
	Myset.erase(it,Myset.end());   //删除两个迭代器之间的范围
}




//template<class K,class V>
//struct pair
//{
//	K first;
//	V second;
//	pair(const K& key,const V& value)
//		:first(key)
//		,second(value)
//	{}
//};

//构造一个pair的对象返回
template<class K,class V>
pair<string,int> make_pair(const K& key,const V& value)
{
	return pair<string,int>(key,value);
}

void TestDict()
{
	//map是K，V类型的
	map<string,string> dict;
	dict.insert(pair<string,string>("value","值"));
	dict.insert(pair<string,string>("left","左边"));
	dict.insert(pair<string,string>("right","右边"));
	dict.insert(pair<string,string>("up","上"));
	dict.insert(pair<string,string>("down","下"));
	dict["left"]="剩余";    //也可以使用operator[]来插入或者修改数据的value
	map<string,string>::iterator it=dict.begin();
	while(it != dict.end())
	{
		cout<<(*it).first<<":"<<(*it).second<<endl;
		++it;
	}
	cout<<endl;

}


vector<int> GetTopKFruits(const vector<string>& fruits)
{
	typedef map<string,int> Map;
	typedef map<string,int>::iterator MapIt;
	vector<int> v;
	//map<string,int> countMap;
	Map countMap;
	for(size_t i=0;i<fruits.size();i++)
	{
		//方法一
		//map<string,int>::iterator it=countMap.find(fruits[i]);
		//if(it != countMap.end())    //找到了
		//{
		//	it->second++;
		//}
		//else    //没有找到则插入到map中
		//{
		//	//countMap.insert(pair<string,int>(fruits[i],1));
		//	countMap.insert(make_pair(fruits[i],1));
		//}

		//方法二，只查找一次
		//pair<MapIt,bool> res=countMap.insert(make_pair(fruits[i],1));
		//if(res.second == false)    //找到了，插入失败
		//{
		//	res.first->second++;
		//}

		//方法三，利用operator[]来实现，operator[]的底层是利用insert来实现的
		countMap[fruits[i]]++;
	}
	map<string,int>::iterator it=countMap.begin();
	while(it != countMap.end())
	{
		v.push_back(it->second);
		++it;
	}
	return v;
}
void TestFruits()
{
	vector<string> fruits;
	fruits.push_back("菠萝");
	fruits.push_back("梨");
	fruits.push_back("水蜜桃");
	fruits.push_back("梨");
	fruits.push_back("菠萝");
	fruits.push_back("水蜜桃");
	fruits.push_back("香蕉");
	fruits.push_back("菠萝");
	fruits.push_back("梨");
	fruits.push_back("水蜜桃");
	fruits.push_back("梨");
	fruits.push_back("菠萝");
	fruits.push_back("水蜜桃");
	fruits.push_back("香蕉");

	vector<int> res=GetTopKFruits(fruits);
	for(size_t i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;   // 4 4 4 2
}