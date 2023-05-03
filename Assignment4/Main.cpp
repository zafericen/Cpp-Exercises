#include "Handler.h"
#include <iostream>
int main(int argc, char* argv[])
{
	BinarySearchTree* first_part_tree = new BinarySearchTree;
	first_part_tree->balanced_tree_type = 1;

	Handler::read_and_execute(argv[1], argv[2], first_part_tree);

	BinarySearchTree* second_part_tree = new BinarySearchTree;
	second_part_tree->balanced_tree_type = 2;

	Handler::read_and_execute(argv[1], argv[3], second_part_tree);
}
