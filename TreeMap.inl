#include "TreeMap.h"

/*_______________________NODE_________________________________*/

template <class T1, class T2>
TreeMap<T1, T2>::TreeNode::TreeNode(const T1& key, const T2& value, const TreeNode* parent)
	: left(nullptr), right(nullptr), parent(parent)
{
	this->key = key;
	this->value = value;
}

/*_______________________ITERATOR_____________________________*/


template<class T1, class T2>
TreeMap<T1, T2>::TreeIterator::TreeIterator(const TreeNode* pointer)
	: pointer(pointer)
{}

template<class T1, class T2>
TreeMap<T1, T2>::TreeIterator& TreeMap<T1, T2>::TreeIterator::operator ++()
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
TreeMap<T1, T2>::TreeIterator& TreeMap<T1, T2>::TreeIterator::operator --()
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
bool TreeMap<T1, T2>::TreeIterator::operator ==(const TreeIterator& iter) const
{
	return *this == *iter;
}

template<class T1, class T2>
bool TreeMap<T1, T2>::TreeIterator::operator !=(const TreeIterator& iter) const
{
	return *this != *iter;
}

template<class T1, class T2>
TreeMap<T1, T2>::TreeNode& TreeMap<T1, T2>::TreeIterator::operator *()
{
	return *pointer;
}

/*________________________MAP_________________________________*/

template <class T1, class T2>
TreeMap<T1, T2>::TreeMap() 
	: root(nullptr), height(0) 
{}

template <class T1, class T2>
TreeMap<T1, T2>::TreeMap(const TreeMap& map) 
	: root(nullptr)
{}

template <class T1, class T2>
TreeMap<T1, T2>::~TreeMap()
{
	if (root)
		delete root;
}

template <class T1, class T2>
TreeMap<T1, T2>::TreeIterator TreeMap<T1, T2>::begin()
{
	Node temp = root;
	while (temp->left)
		temp = temp->left;
	return TreeIterator(temp);
}

template <class T1, class T2>
TreeMap<T1, T2>::TreeIterator TreeMap<T1, T2>::end()
{
	return TreeIterator(nullptr);
}

template <class T1, class T2>
void TreeMap<T1, T2>::print() const
{

}


template <class T1, class T2>
bool TreeMap<T1, T2>::insert(const T1& key, const T2& value)
{
	return false;
}


template <class T1, class T2>
const T2& TreeMap<T1, T2>::find(const T1& key) const
{
	for (auto iter : begin())
	{
		if ((*iter).key == key)
			return iter->value;
	}
	throw "Object doesn't exist";
}

template <class T1, class T2>
bool TreeMap<T1, T2>::erase(const T1& key)
{

}