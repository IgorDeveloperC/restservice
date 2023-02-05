#pragma once

#include<map>


using namespace std;


class Cache_map {
public:
	Cache_map();
	Cache_map(const int& max_capacity);

	void Add(int& key, int& value);  //add key, value and time in cache

	int Find(int& key);
private:
	int _counter = 0;
	int getNextValue();
	const int _capacity;	
	map<int, pair <int, int>> _cache;           //pair contain first-value, second-time cache
	map<int,int> _time_cache;
};
