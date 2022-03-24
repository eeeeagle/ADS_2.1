#pragma once
#include "Iterator.h"

template<class T1, class T2>
class Map
{
	pair<T1, T2>* _data;
	int _size, _capacity;
	bool increaseCapacity();
public:
	Map(const int size = 0);
	~Map();
	//Map& operator = (const Map& map);
	//Pair& operator[](const int index);
	Iterator<T1, T2> begin();
	Iterator<T1, T2> end();
	void print() const;
	bool insert(const T1& key, const T2& data);
	const T2& find(const T1& key) const;
	bool erase(const T1& key);
};