#include "Map.h"

template <class T1, class T2>
Map<T1, T2>::Map(const int size) : _data(nullptr), _size(0), _capacity(0) 
{
	if (size > 0)
	{
		_data = new pair<T1, T2>[size];
		_capacity = size;
	}
}

template <class T1, class T2>
Map<T1, T2>::~Map()
{
	delete[] _data;
}

template <class T1, class T2>
bool Map<T1, T2>::increaseCapacity()
{
	int newSize = int(_capacity * 1.1);
	if (newSize < INT_MAX)
	{
		pair<T1, T2>* newMap = new pair<T1, T2>[newSize];
		for (int i = 0; i < _size; i++)
			newMap[i] = _data[i];
		delete[] _data;
		_data = newMap;
		_capacity = newSize;
		return true;
	}
	return false;
}

template <class T1, class T2>
Iterator<T1, T2> Map<T1, T2>::begin()
{
	return Iterator<T1, T2>(&_data[0]);
}

template <class T1, class T2>
Iterator<T1, T2> Map<T1, T2>::end()
{
	return Iterator<T1, T2>(&_data[_size]);
}

template <class T1, class T2>
void Map<T1, T2>::print() const
{

}


template <class T1, class T2>
bool Map<T1, T2>::insert(const T1& key, const T2& data)
{

}


template <class T1, class T2>
const T2& Map<T1, T2>::find(const T1& key) const
{
	
}

template <class T1, class T2>
bool Map<T1, T2>::erase(const T1& key)
{
}