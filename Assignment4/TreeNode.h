#pragma once
#include <string>

class BalancedBinarySearchTree;

class TreeNode
{
public:
	std::string name;
	TreeNode* l_child;
	TreeNode* r_child;
	

	TreeNode();
	TreeNode(std::string node_name, TreeNode* left_child = nullptr, TreeNode* right_child = nullptr);

	virtual std::string get_node_information() = 0;
	virtual void set_color(std::string color);
	virtual std::string get_color();
	virtual void flip_color();

	static int find_height(TreeNode* root);
	static bool is_red(TreeNode*);
	static std::string print_by_level(TreeNode* root);
};

class PrimaryNode: public TreeNode
{
public:
	BalancedBinarySearchTree* secondary_tree;
	PrimaryNode(std::string node_name, TreeNode* left_child = nullptr, TreeNode* right_child = nullptr);
	virtual std::string get_node_information();
};

class SecondaryNode: public TreeNode
{
public:
	int price;
	virtual std::string get_node_information();
	SecondaryNode(std::string node_name, int price , TreeNode* left_child = nullptr, TreeNode* right_child = nullptr);
};

class AVLTreeNode: public SecondaryNode
{
public:
	AVLTreeNode(std::string node_name, int price ,TreeNode* left_child = nullptr, TreeNode* right_child = nullptr);
};

class RBTreeNode: public SecondaryNode
{
public:
	virtual void set_color(std::string color);
	virtual std::string get_color();
	RBTreeNode(std::string node_name, int price , TreeNode* left_child = nullptr, TreeNode* right_child = nullptr);
	std::string color = "red";
};
