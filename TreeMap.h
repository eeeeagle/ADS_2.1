#pragma once

template<class T1, class T2>
class TreeMap
{
	struct TreeNode
	{
		T1 key;
		T2 value;
		TreeNode* left, * right, * parent;
		TreeNode(const T1& key, const T2& value, const TreeNode* parent = nullptr);
	}* root;
	int height;
	class TreeIterator
	{
		TreeNode* pointer;
	public:
		TreeIterator(const TreeNode* pointer);
		TreeIterator& operator ++();
		TreeIterator& operator --();
		bool operator ==(const TreeIterator& iter) const;
		bool operator !=(const TreeIterator& iter) const;
		TreeNode& operator *();
	};
	TreeIterator begin();
	TreeIterator end();
public:
	TreeMap();
	TreeMap(const TreeMap<T1, T2>& map);
	~TreeMap();
	//Map& operator = (const Map& map);
	//Pair& operator[](const T1 key);
	void print() const;
	bool insert(const T1& key, const T2& value);
	const T2& find(const T1& key) const;
	bool erase(const T1& key);	
};