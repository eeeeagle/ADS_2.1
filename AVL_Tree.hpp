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

	int height(Node* node)
	{
		return node ? node->height : -1;
	}

	Node* rotate_l(Node*& root)
	{
		Node* root2 = root->left;
		root->left = root2->right;
		root2->right = root;
		root->height = std::max(height(root->left), height(root->right)) + 1;
		root2->height = std::max(height(root2->left), root->height) + 1;
		return root2;
	}

	Node* rotate_r(Node*& root)
	{
		Node* root2 = root->right;
		root->right = root2->left;
		root2->left = root;
		root->height = std::max(height(root->left), height(root->right)) + 1;
		root2->height = std::max(root->height, height(root2->right)) + 1;
		return root2;
	}
	
	Node* b_rotate_left(Node*& root)
	{
		root->left = rotate_r(root->left);
		return rotate_l(root);
	}
	
	Node* b_rotate_right(Node*& root)
	{
		root->right = rotate_l(root->right);
		return rotate_r(root);
	}

	Node* insert(const int& key, const std::string& value, Node*& node)
	{
		if (node == nullptr)
		{
			node = new Node(key, value);
			return node;
		}

		if (key < node->key)
		{
			insert(key, value, node->left);
			if ((height(node->left) - height(node->right)) == 2)
			{
				if (key < (node->left)->key)
					node = rotate_l(node);
				else
					node = b_rotate_left(node);
			}
		}
		else if (key > node->key)
		{
			insert(key, value, node->right);
			if ((height(node->right) - height(node->left)) == 2)
			{
				if (key > (node->right)->key)
					node = rotate_r(node);
				else
					node = b_rotate_right(node);
			}
		}
		else
			return nullptr;

		node->height = std::max(height(node->left), height(node->right)) + 1;
	}

	const Node* find(const int& key, const Node* node) const
	{
		if (node == nullptr)
			return nullptr;

		if (key < node->key)
			return find(key, node->left);
		else if (key > node->key)
			return find(key, node->right);
		else
			return node;
	}

	Node* erase(const int& key, Node* node)
	{
		if (node == nullptr)
			return node;

		if (key < node->key)
			node->left = erase(key, node->left);
		else if (key > node->key)
			node->right = erase(key, node->right);
		else
		{
			if (node->left == nullptr || node->right == nullptr)
			{
				Node* temp = node->left;
				if (temp == nullptr)
					temp = node->right;

				if (temp == nullptr)
				{
					temp = node;
					node = nullptr;
				}
				else
					*node = *temp;

				delete temp;
			}
			else
			{
				*node = *node->left;
				//node->right = erase(temp->key, node->right);
			}
		}
		return node;
	}

	void print_debug(Node* ptr, int space) const
	{
		if (ptr == NULL)
			return;

		space += 5;

		print_debug(ptr->right, space);

		std::cout << std::endl;
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << "[" << ptr->key << "][" << ptr->value << "]" << std::endl;

		print_debug(ptr->left, space);
	}

	void print(const Node*& node) const
	{
		if (node == NULL)
			return;

		print(node->left);
		std::cout << "[" << node->key << "][" << node->value << "]" << std::endl;
		print(node->right);
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

	~AVL_Tree()
	{
		delete_tree(root);
	}

	std::string find(const int& key) const
	{
		const Node* tmp = find(key, this->root);
		if (tmp == nullptr)
			return "NULL";
		return tmp->value;
	}

	bool insert(const int& key, const std::string& value)
	{
		if (insert(key, value, this->root))
			return true;
		return false;
	}

	void print() const
	{
		print(root);
	}

	void erase(const int& key)
	{
		
		if (erase(key, this->root))
			return true;
		return false;
	}

	void print_debug() const
	{
		print_debug(root, 0);
	}
};
#endif
