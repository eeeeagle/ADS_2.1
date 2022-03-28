#include "Tree.hpp"

/*_______________________NODE_________________________________*/

template <class T1, class T2>
Map<T1, T2>::Node::Node(const T1& key, const T2& value, const int height, const Node* parent)
	: left(nullptr), right(nullptr), parent(parent)
{
	this->key = key;
	this->value = value;
	this->height = height;
}

/*_______________________ITERATOR_____________________________*/


template<class T1, class T2>
Map<T1, T2>::Iterator::Iterator(const Node* pointer)
	: pointer(pointer)
{}

template<class T1, class T2>
Map<T1, T2>::Iterator& Map<T1, T2>::Iterator::operator ++()
{
	if (pointer == nullptr)
	{
		pointer = root;
		if (pointer == nullptr)
			throw "Empty tree";
		while (pointer->left)
			pointer = pointer->left;
	}
	else
	{
		if (pointer->right)
		{
			pointer = pointer->right;
			while (pointer->left)
				pointer = pointer->left;
		}
		else
		{
			Node temp = pointer->parent;
			while (temp && pointer == temp->right)
			{
				pointer = temp;
				temp = temp->parent;
			}
			pointer = temp;
		}
	}
	return *this;
}

template<class T1, class T2>
Map<T1, T2>::Iterator& Map<T1, T2>::Iterator::operator --()
{
	if (pointer == nullptr)
	{
		pointer = root;
		if (pointer == nullptr)
			throw "Empty tree";
		while (pointer->right)
			pointer = pointer->right;
	}
	else
	{
		if (pointer->left)
		{
			pointer = pointer->left;
			while (pointer->right)
				pointer = pointer->right;
		}
		else
		{
			Node temp = pointer->parent;
			while (temp && pointer == temp->left)
			{
				pointer = temp;
				temp = temp->parent;
			}
			pointer = temp;
		}
	}
	return *this;
}

template<class T1, class T2>
bool Map<T1, T2>::Iterator::operator ==(const Iterator& iter) const
{
	return *this == *iter;
}

template<class T1, class T2>
bool Map<T1, T2>::Iterator::operator !=(const Iterator& iter) const
{
	return *this != *iter;
}

template<class T1, class T2>
Map<T1, T2>::Node& Map<T1, T2>::Iterator::operator *()
{
	return *pointer;
}

/*________________________MAP_________________________________*/

template <class T1, class T2>
Map<T1, T2>::Map() 
	: root(nullptr)
{}

template <class T1, class T2>
Map<T1, T2>::Map(const Map& map) 
	: root(nullptr)
{}

template <class T1, class T2>
Map<T1, T2>::~Map()
{
	if (root)
		delete root;
}

template <class T1, class T2> template <class Functor>
void Map<T1, T2>::traverse(Functor functor)
{
	for (auto iter : begin())
	{
		functor(iter);
	}
}

template <class T1, class T2>
Map<T1, T2>::Iterator Map<T1, T2>::begin()
{
	Node temp = root;
	while (temp->left)
		temp = temp->left;
	return Iterator(temp);
}

template <class T1, class T2>
Map<T1, T2>::Iterator Map<T1, T2>::end()
{
	return Iterator(nullptr);
}

template <class T1, class T2>
void Map<T1, T2>::print(const Node& node) const
{
	std::cout << node.key << ':' << node.key << std::endl;
}

template <class T1, class T2>
bool Map<T1, T2>::insert(const T1& key, const T2& value)
{
	for (auto iter : begin())
	{
		if ((*iter).key == key)
			return false;
	}
	return false;
}

template <class T1, class T2>
const T2& Map<T1, T2>::find(const T1& key) const
{
	for (auto iter : begin())
	{
		if ((*iter).key == key)
			return iter->value;
	}
	throw "[!] Object with this key doesn't exist [!]";
}

template <class T1, class T2>
bool Map<T1, T2>::erase(const T1& key)
{
	for (auto iter : begin())
	{
		if ((*iter).key == key)
			return true;
	}
	return false;
}

template Map<int, char>;