#pragma once
#ifndef Tree
#define Tree
#include <iostream>

template<class Key, class T, class Compare = std::less<Key>>
class Map
{
private:
	struct Node
	{
		Key key;
		T value;
		int balance;
		Node* left, * right, * parent;
		

		Node(const Key& key, const T& value, const Node* parent = nullptr)
			: balance(0), left(nullptr), right(nullptr), parent(parent)
		{
			this->key = key;
			this->value = value;
		}
	}* root;

	class Iterator
	{
	private:
		Node* pointer;
	public:
		Iterator(const Node* pointer = nullptr) 
			: pointer(pointer) 
		{}

		Iterator(const Iterator& iterator) 
			: pointer(iterator.pointer) 
		{}

		Iterator& operator ++()
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

		Iterator& operator --()
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

		bool operator ==(const Iterator& iter) const
		{
			return pointer == iter.pointer;
		}

		bool operator !=(const Iterator& iter) const
		{
			return pointer != iter.pointer;
		}

		Node& operator *()
		{
			return *pointer;
		}
	};

	Iterator begin()
	{
		Node* temp = root;
		if (temp)
		{
			while (temp->left)
				temp = temp->left;
		}
		return Iterator(temp);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	template<class Functor> void traverse(Functor functor)
	{
		for (auto iter : begin())
		{
			functor(*iter);
		}
	}

public:
	Map() 
		: root(nullptr) 
	{}

	Map(const Map& map)
		: root(nullptr) 
	{}

	~Map()
	{
		if (root)
			delete root;
	}

	void print_node(const Node& node) const
	{
		std::cout << node.key << ':' << node.value << std::endl;
	}

	bool insert(const Key& key, const T& value) 
	{
		if (begin() == end())
		{
			root = new Node(key, value);
			return true;
		}

		for (auto iter : begin())
		{
			if (Compare((*iter).key, key) == std::less)
			{
				if ((*iter).left == nullptr)
				{
					(*iter).left = new Node(key, value);
					(*iter).balance--;
					return true;
				}
			}
			else if (Compare((*iter).key, key) == std::greater)
			{
				if ((*iter).right == nullptr)
				{
					(*iter).right = new Node(key, value);
					(*iter).balance++;
					return true;
				}
			}
			else
				return false;
		}
		return true;
	}

	const T& find(const Key& key) const
	{
		for (auto iter : begin())
		{
			if (Compare((*iter).key, key) == std::equal)
				return (*iter).value;
		}
		throw "[!] Object with this key doesn't exist [!]";
	}

	bool erase(const Key& key) 
	{
		for (auto iter : begin())
		{
			if (Compare((*iter).key, key))
			{
				return true;
			}
		}
		return false;
	}
};
#endif