#pragma once
#ifndef AVL_TREE
#define AVL_TREE
#include <iostream>

class AVL_Tree
{
private:
	class Node
	{
	public:
		int				key;
		std::string		value;
		Node*			left, * right;
		int				height;

		Node(const int& key, const std::string& value)
			: left(nullptr), right(nullptr), height(0)
		{
			this->key	= key;
			this->value = value;
		}

		Node(const Node& node)
			: key(node.key), value(node.value), left(nullptr), right(nullptr), height(node.height)
		{}

	}* root;

	int height(Node* node) const
	{
		return node ? node->height : 0;
	}

	int bfactor(Node* node) const
	{
		return height(node->right) - height(node->left);
	}

	void fix_height(Node* node)
	{
		int left = height(node->left);
		int right = height(node->right);
		node->height = (left > right ? left : right) + 1;
	}

	Node* rotate_right(Node* p) // правый поворот вокруг p
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		fix_height(p);
		fix_height(q);
		return q;
	}

	Node* rotate_left(Node* q) // левый поворот вокруг q
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		fix_height(q);
		fix_height(p);
		return p;
	}

	Node* balance(Node* node)
	{
		fix_height(node);
		if (bfactor(node) == 2)
		{
			if (bfactor(node->right) < 0)
				node->right = rotate_right(node->right);
			return rotate_left(node);
		}
		if (bfactor(node) == -2)
		{
			if (bfactor(node->left) > 0)
				node->left = rotate_left(node->left);
			return rotate_right(node);
		}
		return node; // балансировка не нужна
	}

	Node* insert(Node* node, const int& key, const std::string& value)
	{
		if (node == nullptr) 
			return new Node(key, value);

		if (key < node->key)
			node->left = insert(node->left, key, value);
		else if (key > node->key)
			node->right = insert(node->right, key, value);

		return balance(node);
	}

	const Node* find(const Node* node, const int& key) const
	{
		if (node == nullptr)
			return nullptr;

		if (key < node->key)
			return find(node->left, key);
		else if (key > node->key)
			return find(node->right, key);
		else
			return node;
	}

	Node* find_min(Node* node)
	{
		return node->left ? find_min(node->left) : node;
	}

	Node* remove_min(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min(node->left);
		return balance(node);
	}

	Node* erase(Node* node, int key)
	{
		if (node == nullptr)
			return 0;
		
		if (key < node->key)
			node->left = erase(node->left, key);
		else if (key > node->key)
			node->right = erase(node->right, key);
		else
		{
			Node* q = node->left;
			Node* r = node->right;
			delete node;
			if (!r) 
				return q;
			Node* min = find_min(r);
			min->right = remove_min(r);
			min->left = q;
			return balance(min);
		}
		
		return balance(node);
	}

	void print(const Node* ptr, int space = 0) const
	{
		if (ptr == NULL)
			return;

		print(ptr->right, space + 10);

		std::cout << std::endl;
		for (int i = 0; i < space; i++)
			std::cout << " ";
		std::cout << "[" << ptr->key << "][" << ptr->value << "]" << std::endl;

		print(ptr->left, space + 10);
	}

	Node* copy_tree(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		Node* n = new Node(*node);
		n->left = copy_tree(node->left);
		n->right = copy_tree(node->right);
		return n;
	}

	void delete_tree(Node* node)
	{
		if (node)
		{
			delete_tree(node->left);
			delete_tree(node->right);
			delete node;
		}
	}

public:
	
	AVL_Tree()
		: root(nullptr)
	{}

	AVL_Tree(const AVL_Tree& tree)
	{
		root = copy_tree(tree.root);
	}

	~AVL_Tree()
	{
		delete_tree(root);
	}

	std::string find(const int& key) const
	{
		const Node* tmp = find(this->root, key);
		if (tmp == nullptr)
			return "<NULL>";
		return tmp->value;
	}

	bool insert(const int& key, const std::string& value)
	{
		root = insert(this->root, key, value);
		if (root)
			return true;
		return false;
	}

	void print() const
	{
		print(root);
		std::cout << "__________________________________________________\n";
	}

	bool erase(const int& key)
	{
		root = erase(this->root, key);
		if (root)
			return true;
		return false;
	}
};
#endif
