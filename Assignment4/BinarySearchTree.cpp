#include "BinarySearchTree.h"

void BinarySearchTree::insert(std::string primary_node_name, std::string secondary_node_name, int price)
{
	TreeNode* added_category_node = add_node_to_tree(primary_node_name, root);

	PrimaryNode* category_node = dynamic_cast<PrimaryNode*>(added_category_node);

	if (category_node->secondary_tree == nullptr)
	{
		if (balanced_tree_type == 1)
		{
			category_node->secondary_tree = new AVLBinarySearchTree;
		}
		else
		{
			category_node->secondary_tree = new RBBinarySearchTree;
		}
	}
	BalancedBinarySearchTree* second_tree = category_node->secondary_tree;
	second_tree->insert_to_balanced_tree(secondary_node_name, price);
}

void BinarySearchTree::remove(std::string primary_node_name, std::string secondary_node_name)
{
	PrimaryNode* category_node = dynamic_cast<PrimaryNode*>(BinarySearchTree::find_node(root, primary_node_name));
	
	if (category_node != nullptr)
	{
		category_node->secondary_tree->remove_from_balanced_tree(secondary_node_name);
	}
}
void BinarySearchTree::update_data(std::string primary_node_name, std::string secondary_node_name, int price)
{
	PrimaryNode* category_node = dynamic_cast<PrimaryNode*>(find_node(root, primary_node_name));

	SecondaryNode* item_node = dynamic_cast<SecondaryNode*>(find_node(category_node->secondary_tree->root, secondary_node_name));

	item_node->price = price;
}

TreeNode* BinarySearchTree::add_node_to_tree(std::string key,TreeNode*& tree_node)
{
	if (tree_node == nullptr)
	{
		tree_node = new PrimaryNode(key);
		return tree_node;
	}
	else if (key < tree_node->name)
	{
		return add_node_to_tree(key, tree_node->l_child);
	}
	else if (key > tree_node->name)
	{
		return add_node_to_tree(key, tree_node->r_child);
	}
	return tree_node;
}

std::string BinarySearchTree::printAllItems()
{
	return TreeNode::print_by_level(root);
}

std::string BinarySearchTree::printAllItemsInCategory(std::string key)
{

	return (find_node(root, key))->get_node_information();
}

std::string BinarySearchTree::find(std::string primary_key, std::string secondary_key)
{
	TreeNode* temp_category_node = find_node(root, primary_key);
	if (temp_category_node == nullptr)
	{
		return "";
	}
	PrimaryNode* category_node = dynamic_cast<PrimaryNode*>(temp_category_node);
	if (category_node->secondary_tree->root == nullptr || find_node(category_node->secondary_tree->root, secondary_key) == nullptr)
	{
		return "";
	}
	return printItem(primary_key, secondary_key);
	
}

std::string BinarySearchTree::printItem(std::string primary_key, std::string secondary_key)
{
	PrimaryNode* category_node = dynamic_cast<PrimaryNode*>(find_node(root, primary_key));
	std::string return_string = "\n\"" + category_node->name + "\":\n\t";
	return_string += find_node(category_node->secondary_tree->root, secondary_key)->get_node_information()+"\n";
	return return_string;
}

TreeNode* BinarySearchTree::most_left_node(TreeNode* tree_node)
{
	TreeNode* curr_node = tree_node;

	while (curr_node->l_child != nullptr)
	{
		curr_node = curr_node->l_child;
	}
	return curr_node;
}

TreeNode* BinarySearchTree::find_node(TreeNode* tree_node, std::string key)
{
	if (tree_node == nullptr)
	{
		return nullptr;
	}
	else if (key < tree_node->name)
	{
		return find_node(tree_node->l_child, key);
	}
	else if (key > tree_node->name)
	{
		return find_node(tree_node->r_child, key);
	}
	else
	{
		return tree_node;
	}
}


void BalancedBinarySearchTree::insert_to_balanced_tree(std::string key, int price)
{
	root = add_node_to_tree(key, root, price);
	root->set_color("black");
}

void BalancedBinarySearchTree::remove_from_balanced_tree(std::string key)
{
	root = delete_node_from_tree(root, key);
}

TreeNode* BalancedBinarySearchTree::delete_node_from_tree(TreeNode* tree_node, std::string delete_key)
{
	if (tree_node == nullptr)
	{
		return tree_node;
	}
	else if (tree_node->name > delete_key)
	{
		tree_node->l_child = delete_node_from_tree(tree_node->l_child, delete_key);
	}
	else if (tree_node->name < delete_key)
	{
		tree_node->r_child = delete_node_from_tree(tree_node->r_child, delete_key);
	}
	else
	{
		TreeNode* temp_node = nullptr;
		//only right child or no child
		if (tree_node->l_child == nullptr)
		{
			temp_node = tree_node->r_child;
			delete tree_node;
			return temp_node;
		}
		//only left child
		else if (tree_node->r_child == nullptr)
		{
			temp_node = tree_node->l_child;
			delete tree_node;
			return temp_node;
		}
		//two children
		else
		{
			temp_node = most_left_node(tree_node->r_child);
			tree_node->name = temp_node->name;
			((SecondaryNode*)tree_node)->price = ((SecondaryNode*)temp_node)->price;
			tree_node->r_child = delete_node_from_tree(tree_node->r_child, temp_node->name);
		}
	}
	return update_balanced_tree(tree_node);
}

TreeNode* BalancedBinarySearchTree::add_node_to_tree(std::string key, TreeNode* tree_node,int price)
{
	if (tree_node == nullptr)
	{
		if (dynamic_cast<AVLBinarySearchTree*>(this) != nullptr)
		{
			tree_node = new AVLTreeNode(key, price);
			return tree_node;
		}
		else if (dynamic_cast<RBBinarySearchTree*>(this) != nullptr)
		{
			tree_node = new RBTreeNode(key, price);
			return tree_node;
		}
	}
	else if (key < tree_node->name)
	{
		tree_node->l_child = add_node_to_tree(key, tree_node->l_child,price);
	}
	else
	{
		tree_node->r_child = add_node_to_tree(key, tree_node->r_child,price);
	}
	return update_balanced_tree(tree_node);
}

TreeNode* BalancedBinarySearchTree::rotate_right(TreeNode* rotate_node)
{
	TreeNode* left_child = rotate_node->l_child;
	TreeNode* lefts_right_child = left_child->r_child;

	left_child->r_child = rotate_node;
	rotate_node->l_child = lefts_right_child;

	return left_child;
}

TreeNode* BalancedBinarySearchTree::rotate_left(TreeNode* rotate_node)
{
	TreeNode* right_child = rotate_node->r_child;
	rotate_node->r_child = right_child->l_child;
	right_child->l_child = rotate_node;


	return right_child;
}

TreeNode* AVLBinarySearchTree::update_balanced_tree(TreeNode* tree_node)
{
	int balance_factor = get_balance_factor(tree_node);
	// left-left case
	if (balance_factor > 1 && get_balance_factor(tree_node->l_child) >= 1)
	{
		return rotate_right(tree_node);
	}
	// right-right case
	else if (balance_factor < -1 && get_balance_factor(tree_node->r_child) <= -1)
	{
		return rotate_left(tree_node);
	}
	//left-right case
	else if (balance_factor > 1 && get_balance_factor(tree_node->l_child) <=-1)
	{
		tree_node->l_child = rotate_left(tree_node->l_child);
		return rotate_right(tree_node);
	}
	//right-left case
	else if (balance_factor < -1 && get_balance_factor(tree_node->r_child) >= 1)
	{
		tree_node->r_child = rotate_right(tree_node->r_child);
		return rotate_left(tree_node);
	}
	//when nothing happens
	return tree_node;
}

int AVLBinarySearchTree::get_balance_factor(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return TreeNode::find_height(root->l_child) - TreeNode::find_height(root->r_child);
}

void RBBinarySearchTree::remove_from_balanced_tree(std::string key)
{
	if (nullptr != root)
	{
		root = deleteRec(root, key);
		if (nullptr != root) {
			root->set_color("black");
		}
	}
}

TreeNode* RBBinarySearchTree::deleteRec(TreeNode* given_node, std::string key)
{
	if (key < given_node->name)
	{
		if (nullptr != given_node->l_child)
		{
			if ((false == TreeNode::is_red(given_node->l_child)) && (false == TreeNode::is_red(given_node->l_child->l_child)))
			{
				given_node = moveRedLeft(given_node);
			}
			given_node->l_child = deleteRec(given_node->l_child, key);
		}
	}
	else
	{
		if (TreeNode::is_red(given_node->l_child))
		{
			given_node = rotate_right(given_node);
		}
		if ((key.compare(given_node->name) == 0) && (nullptr == given_node->r_child))
		{
			delete given_node;
			return nullptr;
		}
		if (nullptr != given_node->r_child)
		{
			if ((false == TreeNode::is_red(given_node->r_child)) && (false == TreeNode::is_red(given_node->r_child->l_child)))
			{
				given_node = moveRedRight(given_node);
			}
			if (key.compare(given_node->name) == 0)
			{
				TreeNode* smallest_node = most_left_node(given_node->r_child);
				given_node->name = smallest_node->name;
				((SecondaryNode*)given_node)->price = ((SecondaryNode*)smallest_node)->price;
				given_node->r_child = deleteMin(given_node->r_child);
			}
			else
			{

				given_node->r_child = deleteRec(given_node->r_child, key);
			}
		}
	}
	return fixUp(given_node);
}

TreeNode* RBBinarySearchTree::deleteMin(TreeNode* given_node)
{
	if (nullptr == given_node->l_child) {
		delete given_node;
		return nullptr;
	}
	if ((false == TreeNode::is_red(given_node->l_child)) && (false == TreeNode::is_red(given_node->l_child->l_child)))
	{
		given_node = moveRedLeft(given_node);
	}
	given_node->l_child = deleteMin(given_node->l_child);

	return fixUp(given_node);
}

TreeNode* RBBinarySearchTree::fixUp(TreeNode* given_node)
{
	if (TreeNode::is_red(given_node->r_child)) {
		given_node = rotate_left(given_node);
	}
	if (TreeNode::is_red(given_node->l_child) && TreeNode::is_red(given_node->l_child->l_child))
	{
		given_node = rotate_right(given_node);
	}
	if (TreeNode::is_red(given_node->l_child) && TreeNode::is_red(given_node->l_child))
	{
		given_node->flip_color();
	}
	return given_node;
}

TreeNode* RBBinarySearchTree::moveRedLeft(TreeNode* given_node)
{
	given_node->flip_color();

	if ((nullptr != given_node->r_child) && TreeNode::is_red(given_node->r_child->l_child))
	{
		given_node->r_child = rotate_right(given_node->r_child);
		given_node = rotate_left(given_node);
		given_node->flip_color();
	}
	return given_node;
}

TreeNode* RBBinarySearchTree::moveRedRight(TreeNode* given_node)
{
	given_node->flip_color();

	if ((nullptr != given_node->l_child) && TreeNode::is_red(given_node->l_child->l_child))
	{
		given_node = rotate_right(given_node);
		given_node->flip_color();
	}
	return given_node;
}

TreeNode* RBBinarySearchTree::update_balanced_tree(TreeNode* tree_node)
{
	if (TreeNode::is_red(tree_node->l_child) && TreeNode::is_red(tree_node->r_child))
	{
		return change_color(tree_node);
	}
	else if (TreeNode::is_red(tree_node->r_child))
	{
		tree_node = rotate_left(tree_node);
		return update_balanced_tree(tree_node);
	}
	else if (TreeNode::is_red(tree_node->l_child) && TreeNode::is_red(tree_node->l_child->l_child))
	{
		tree_node = rotate_right(tree_node);
		return update_balanced_tree(tree_node);
	}
	
	return tree_node;
}

TreeNode* RBBinarySearchTree::rotate_right(TreeNode* rotate_node)
{
	TreeNode* tree_node = BalancedBinarySearchTree::rotate_right(rotate_node);
	tree_node->set_color(tree_node->r_child->get_color());
	tree_node->r_child->set_color("red");
	
	return tree_node;
}

TreeNode* RBBinarySearchTree::rotate_left(TreeNode* rotate_node)
{
	TreeNode* tree_node = BalancedBinarySearchTree::rotate_left(rotate_node);
	tree_node->set_color(tree_node->l_child->get_color());
	tree_node->l_child->set_color("red");
	
	return tree_node;
}

TreeNode* RBBinarySearchTree::change_color(TreeNode* root)
{
	root->l_child->set_color("black");
	root->r_child->set_color("black");
	root->set_color("red");
	
	return root;
}