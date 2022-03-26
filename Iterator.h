#pragma once
#include <iostream>

using namespace std;

template<class T1, class T2>
class Iterator
{
	pair<T1, T2>* _iter;
public:
	Iterator(pair<T1, T2>* iter) : _iter(iter) {}

	Iterator& operator ++()
	{
		_iter++;
		return *this;
	}

	Iterator& operator --()
	{
		_iter--;
		return *this;
	}

	pair<T1, T2>& operator *()
	{
		return *_iter;
	}
}; 