#pragma once

#include<vector>

class BitMap
{
public:
	BitMap(size_t range)
	{
		_bitMap.resize((range >> 5) +1);
	}
	void Set(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		_bitMap[index] |= (1 << num);
	}
	void ReSet(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		_bitMap[index] &= (~(1 << num));
	}
	bool Test(size_t x)
	{
		size_t index=x>>5;
		size_t num=x%32;
		return _bitMap[index] & (1 << num);
	}
protected:
	vector<size_t> _bitMap;
};

void TextBitMap()
{
	BitMap bm(1024);
	bm.Set(4);
	bm.Set(44);
	bm.Set(444);
	cout<<"Test 4?"<<bm.Test(4)<<endl;
	cout<<"Test 44?"<<bm.Test(44)<<endl;
	cout<<"Test 444?"<<bm.Test(444)<<endl;

	bm.ReSet(44);
	cout<<"Test 44?"<<bm.Test(44)<<endl;
}