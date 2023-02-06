#include "../include/Cache_map.h"

Cache_map::Cache_map() :_capacity(10) {};
Cache_map::Cache_map(const int& max_capacity) :_capacity(max_capacity) {};

void Cache_map::Add(int& key, int& value) {
	int current_task_counter = getNextValue();
	if (_cache.size() < _capacity) {
		if (_cache.count(key)) {							  //erase old current_task_counter if exist key
			_time_cache.erase(_cache[key].second);
		}
	}
	else {
		_cache.erase(_time_cache.begin()->second);
		_time_cache.erase(_time_cache.begin()->first);
	}

	_cache.insert_or_assign(key, make_pair(value, current_task_counter));    //new fitch how insert 
	_time_cache.insert_or_assign(current_task_counter, key);
}

int Cache_map::Find(int& key) {
	if (!_cache.count(key)) {
		return -1;
	}

	int current_task_counter = getNextValue();			 //update current counter
	_time_cache.erase(_cache[key].second);
	_time_cache.insert_or_assign(current_task_counter, key);
	_cache[key].second = current_task_counter;
	return _cache[key].first;
}

int Cache_map::getNextValue() {
	_counter += 1;
	return _counter;
}