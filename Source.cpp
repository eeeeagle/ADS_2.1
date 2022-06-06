#include "AVL_Tree.hpp"
#include <conio.h>

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
		key = _getch();
	return key;
}

int tree_menu_info()
{
	std::cout << "  [1] Insert" << std::endl;
	std::cout << "  [2] Delete" << std::endl;
	std::cout << "  [3] Find"   << std::endl;
	std::cout << "  [4] Print"  << std::endl;
	std::cout << "[ESC] Return" << std::endl;
	
	while (true)
	{
		int key = get_key();
		if (key == 49 || key == 50 || key == 51 || key == 52 || key == 27)
			return key;
	}
}

void tree_menu(AVL_Tree& tree)
{
	while (true)
	{
		int key = tree_menu_info();
		system("cls");
		if (key == 27)
		{
			return;
		}
		else if (key == 49)
		{
			std::cout << "   Enter key: ";
			std::cin >> key;
				
			std::string value;
			std::cout << "Enter string: ";
			std::cin >> value;

			tree.insert(key, value);
		}
		else if (key == 50)
		{
			std::cout << "Enter key: ";
			std::cin >> key;
			tree.erase(key);
		}
		else if (key == 51)
		{
			std::cout << "Enter key: ";
			std::cin >> key;

			std::cout << tree.find(key) << std::endl;
			system("pause");
		}
		else if (key == 52)
		{
			tree.print();
			system("pause");
		}
		system("cls");
	}
}

int main_info()
{
	std::cout << "  [1] Tree 1 menu"		   << std::endl;
	std::cout << "  [2] Tree 2 menu"		   << std::endl;
	std::cout << "  [3] Copy tree 1 to tree 2" << std::endl;
	std::cout << "[ESC] Exit"				   << std::endl;

	while (true)
	{
		int key = get_key();
		if (key == 49 || key == 50 || key == 51 || key == 27)
			return key;
	}
}

int main()
{
	AVL_Tree tree_1;
	AVL_Tree tree_2;

	while (true)
	{
		int key = main_info();
		system("cls");
		if (key == 27)
		{
			return 0;
		}
		else if (key == 49)
		{
			tree_menu(tree_1);
		}
		else if (key == 50)
		{
			tree_menu(tree_2);
		}
		else if (key == 51)
		{
			tree_2 = AVL_Tree(tree_1);
		}
		system("cls");
	}
}
