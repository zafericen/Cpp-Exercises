#include "TreeNode.h"
//for elimination of circular dependency
#include "BinarySearchTree.h"
#include <queue>

TreeNode::TreeNode():
	name(""), l_child(nullptr), r_child(nullptr)
{
}
TreeNode::TreeNode(std::string node_name, TreeNode* left_child, TreeNode* right_child):
	name(node_name),l_child(left_child),r_child(right_child)
{
}
PrimaryNode::PrimaryNode(std::string node_name, TreeNode* left_child, TreeNode* right_child):
	TreeNode::TreeNode(node_name, left_child, right_child),secondary_tree(nullptr)
{
}
SecondaryNode::SecondaryNode(std::string node_name, int price, TreeNode* left_child, TreeNode* right_child):
	TreeNode(node_name, left_child, right_child), price(price)
{
}
AVLTreeNode::AVLTreeNode(std::string node_name, int given_price, TreeNode* left_child, TreeNode* right_child):
	SecondaryNode(node_name,given_price,left_child,right_child)
{
}
RBTreeNode::RBTreeNode(std::string node_name, int given_price, TreeNode* left_child, TreeNode* right_child):
	SecondaryNode(node_name,given_price, left_child, right_child)
{
}

std::string TreeNode::print_by_level(TreeNode* root)
{
	std::string return_string;
	if (root == nullptr)
	{
		return "{}";
	}

	std::queue<TreeNode*> q;
	q.push(root);

	while (!q.empty())
	{
		int num_of_nodes = q.size();

		TreeNode* prev_node = nullptr;

		while (num_of_nodes--)
		{
			TreeNode* temp = q.front();
			q.pop();

			return_string += temp->get_node_information();

			if (temp->l_child != nullptr)
			{
				q.push(temp->l_child);
			}
			if (temp->r_child != nullptr)
			{
				q.push(temp->r_child);
			}
			if (num_of_nodes && dynamic_cast<SecondaryNode*>(root) != nullptr)
			{
				return_string += ",";
			}
			prev_node = temp;
		}
		if (dynamic_cast<SecondaryNode*>(root) != nullptr)
		{
			return_string += "\n\t";
		}
	}
	return_string.pop_back();
	return return_string;
}

std::string PrimaryNode::get_node_information()
{
	std::string return_string = "\"" + name + "\":";

	if (secondary_tree->root == nullptr)
	{
		return_string += "{}\n";
	}
	else
	{
		return_string += "\n\t" + print_by_level(secondary_tree->root);
		
	}
	
	return return_string;
}


std::string SecondaryNode::get_node_information()
{
	return "\"" + name + "\":" + "\"" + std::to_string(price) + "\"";
}

int TreeNode::find_height(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int left_tree_height = find_height(root->l_child);
	int right_tree_height = find_height(root->r_child);

	if (left_tree_height >= right_tree_height)
	{
		return left_tree_height + 1;
	}
	else
	{
		return right_tree_height + 1;
	}
}

bool TreeNode::is_red(TreeNode* node)
{
	if (node == nullptr)
	{
		return false;
	}
	return node->get_color().compare("red") == 0;
}

void TreeNode::set_color(std::string color)
{
	return;
}
void RBTreeNode::set_color(std::string color)
{
	this->color = color;
}

std::string TreeNode::get_color()
{
	return "";
}
std::string RBTreeNode::get_color()
{
	return color;
}

void TreeNode::flip_color()
{
	set_color(is_red(this) ? "black" : "red");
	if (nullptr != l_child) {
		l_child->set_color(is_red(this) ? "black" : "red");
	}
	if (nullptr != r_child) {
		r_child->set_color(is_red(this) ? "black" : "red");
	}
}