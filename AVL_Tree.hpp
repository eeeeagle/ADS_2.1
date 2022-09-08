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
        int         key;
        std::string value;
        Node*       left, * right;
        int         height;

        Node(const int& key, const std::string& value)
            : left(nullptr), right(nullptr), height(0)
        {
            this->key    = key;
            this->value = value;
        }

        Node(const Node& node)
            : key(node.key), value(node.value), left(nullptr), right(nullptr), height(node.height)
        {}

    }* root;

    int height(Node* node)
    {
        int t;
        if (node == NULL)
        {
            return -1;
        }
        else
        {
            t = node->height;
            return t;
        }
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
                {
                    node = rotate_l(node);
                }
                else
                {
                    node = b_rotate_left(node);
                }
            }
        }
        else if (key > node->key)
        {
            insert(key, value, node->right);
            if ((height(node->right) - height(node->left)) == 2)
            {
                if (key > (node->right)->key)
                {
                    node = rotate_r(node);
                }
                else
                {
                    node = b_rotate_right(node);
                }
            }
        }
        else
            return nullptr;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        return node; 
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
    
    std::pair<int, std::string> delete_min(Node*& root)
    {
        if (root->left == NULL)
        {
            std::pair<int, std::string> temp(root->key, root->value);
            root = root->right;
            return temp;
        }
        else
            return delete_min(root->left);
    }

        
    void erase(int key, Node*& root)
    {
        Node* temp;
        if (root == NULL)
        {
            return;
        }
        else if (key < root->key)
        {
            erase(key, root->left);
        }
        else if (key > root->key)
        {
            erase(key, root->right);
        }
        else if ((root->left == NULL) && (root->right == NULL))
        {
            temp = root;
            delete temp;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            std::pair<int, std::string> tmp = delete_min(root->right);
            root->key = tmp.first;
            root->value = tmp.second;
            
        }
    }

    void print(Node* ptr, int space = 0) const
    {
        if (ptr == NULL)
            return;

        print(ptr->right, space + 1);

        std::cout << std::endl;
        for (int i = 0; i < space; i++)
            std::cout << "     ";
        std::cout << "[" << ptr->key << "][" << ptr->value << "]" << std::endl;

        print(ptr->left, space + 1);
    }
    
    Node* copy_tree(Node* node)
    {
        if(node == nullptr)
            return nullptr;
        Node* new_node = new Node(*node);
        new_node->left = copy_tree(node->left);
        new_node->right = copy_tree(node->right);
        return new_node;
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
        : root(nullptr)
    {
        root = copy_tree(tree.root);
    }

    ~AVL_Tree()
    {
        delete_tree(root);
    }

    AVL_Tree& operator =(const AVL_Tree& tree)
    {
        
        AVL_Tree res(tree);
        std::swap(root, res.root);
        return *this;
    }
    std::string find(int key) const
    {
        const Node* tmp = find(key, this->root);
        if (tmp == nullptr)
            return "NULL";
        return tmp->value;
    }

    bool insert(int key, std::string value)
    {
        if (insert(key, value, this->root))
            return true;
        return false;
    }

    void print() const
    {
        print(root);
    }

    void erase(int key)
    {
        erase(key, this->root);
    }
};
#endif
