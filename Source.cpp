#include "AVL_Tree.hpp"

int main()
{
	AVL_Tree map;

	map.insert(4, "ss");
	map.insert(2, "ss");
	map.insert(7, "ss");
	map.insert(4, "ss");
	map.insert(3, "ss");
	map.insert(6, "ss");
	map.insert(-7, "ss");
	map.insert(1, "ss");
	map.insert(-4, "ss");
	map.insert(9, "ss");
	map.insert(15, "ss");
	map.insert(12, "ss");
	map.insert(5, "ss");

	map.print_debug();

	std::cout << map.find(9) << std::endl;
	map.erase(9);
	std::cout << map.find(9) << std::endl;

	map.print_debug();

	return 0;
}
