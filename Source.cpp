#include "AVL_Tree.hpp"
#include <conio.h>

int get_key()
{
    int key = _getch();
    if ((key == 0) || (key == 224))
        key = _getch();
    return key - 48;
}

int tree_menu_info()
{
    std::cout << "[1] Insert" << std::endl;
    std::cout << "[2] Delete" << std::endl;
    std::cout << "[3] Find"   << std::endl;
    std::cout << "[4] Print"  << std::endl;
    std::cout << "[5] Return" << std::endl;
    
    while (true)
    {
        int key = get_key();
        if (key == 1 || key == 2 || key == 3 || key == 4 || key == 5)
            return key;
    }
}

void tree_menu(AVL_Tree& tree)
{
    while (true)
    {
        int key = tree_menu_info();
        system("cls");
        if (key == 5)
        {
            return;
        }
        else if (key == 1)
        {
            std::cout << "   Enter key: ";
            std::cin >> key;
                
            std::string value;
            std::cout << "Enter string: ";
            std::cin >> value;

            tree.insert(key, value);
        }
        else if (key == 2)
        {
            std::cout << "Enter key: ";
            std::cin >> key;
            tree.erase(key);
        }
        else if (key == 3)
        {
            std::cout << "Enter key: ";
            std::cin >> key;

            std::cout << tree.find(key) << std::endl;
            system("pause");
        }
        else if (key == 4)
        {
            tree.print();
            system("pause");
        }
        system("cls");
    }
}

int main_info()
{
    std::cout << "[1] Tree menu"        << std::endl;
    std::cout << "[2] Copy Tree menu"   << std::endl;
    std::cout << "[3] Exit"             << std::endl;

    while (true)
    {
        int key = get_key();
        if (key == 1 || key == 2 || key == 3)
            return key;
    }
}

int main()
{
    AVL_Tree tree;

    while (true)
    {
        int key = main_info();
        system("cls");
        if (key == 3)
        {
            return 0;
        }
        else if (key == 1)
        {
            tree_menu(tree);
        }
        else if (key == 2)
        {
            AVL_Tree tree_copy(tree);
            tree_menu(tree_copy);
        }
        system("cls");
    }
}
