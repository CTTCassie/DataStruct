#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<map>
#include<set>
#include<vector>
#include<string>

void TestSet()
{
	//set��K���͵�
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
	cout<<Myset.count("right")<<endl;   //1 ͳ��right���ֵĴ���,set��ȥ�ص�
	it=Myset.find("left");
	if(it != Myset.end())    //�ҵ���
	{
		cout<<*it<<endl;     //left
	}
	//Myset.erase(it);      //ɾ��һ��������
	Myset.erase(it,Myset.end());   //ɾ������������֮��ķ�Χ
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

//����һ��pair�Ķ��󷵻�
template<class K,class V>
pair<string,int> make_pair(const K& key,const V& value)
{
	return pair<string,int>(key,value);
}

void TestDict()
{
	//map��K��V���͵�
	map<string,string> dict;
	dict.insert(pair<string,string>("value","ֵ"));
	dict.insert(pair<string,string>("left","���"));
	dict.insert(pair<string,string>("right","�ұ�"));
	dict.insert(pair<string,string>("up","��"));
	dict.insert(pair<string,string>("down","��"));
	dict["left"]="ʣ��";    //Ҳ����ʹ��operator[]����������޸����ݵ�value
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
		//����һ
		//map<string,int>::iterator it=countMap.find(fruits[i]);
		//if(it != countMap.end())    //�ҵ���
		//{
		//	it->second++;
		//}
		//else    //û���ҵ�����뵽map��
		//{
		//	//countMap.insert(pair<string,int>(fruits[i],1));
		//	countMap.insert(make_pair(fruits[i],1));
		//}

		//��������ֻ����һ��
		//pair<MapIt,bool> res=countMap.insert(make_pair(fruits[i],1));
		//if(res.second == false)    //�ҵ��ˣ�����ʧ��
		//{
		//	res.first->second++;
		//}

		//������������operator[]��ʵ�֣�operator[]�ĵײ�������insert��ʵ�ֵ�
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
	fruits.push_back("����");
	fruits.push_back("��");
	fruits.push_back("ˮ����");
	fruits.push_back("��");
	fruits.push_back("����");
	fruits.push_back("ˮ����");
	fruits.push_back("�㽶");
	fruits.push_back("����");
	fruits.push_back("��");
	fruits.push_back("ˮ����");
	fruits.push_back("��");
	fruits.push_back("����");
	fruits.push_back("ˮ����");
	fruits.push_back("�㽶");

	vector<int> res=GetTopKFruits(fruits);
	for(size_t i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;   // 4 4 4 2
}