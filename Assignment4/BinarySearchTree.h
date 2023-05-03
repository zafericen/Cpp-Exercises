#pragma once
#include "TreeNode.h"
#include <iostream>
class BinarySearchTree
{
public:
	TreeNode* root{ nullptr };
	int balanced_tree_type{ 0 };

	void insert(std::string primary_node_name, std::string secondary_node_name, int price);
	void remove(std::string primary_node_name, std::string secondary_node_name);
	void update_data(std::string primary_node_name, std::string secondary_node_name, int price);

	std::string printAllItems();
	std::string printAllItemsInCategory(std::string key);
	std::string printItem(std::string primary_key, std::string secondary_key);
	std::string find(std::string primary_key, std::string secondary_key);

	static TreeNode* find_node(TreeNode* tree_node,std::string key);
	virtual TreeNode* add_node_to_tree(std::string key, TreeNode*& tree_node);

	TreeNode* most_left_node(TreeNode* tree_node);
};

class BalancedBinarySearchTree :public BinarySearchTree
{
public:
	void insert_to_balanced_tree(std::string key, int price);
	virtual void remove_from_balanced_tree(std::string key);

protected:
	virtual TreeNode* delete_node_from_tree(TreeNode* tree_node, std::string delete_key);
	virtual TreeNode* add_node_to_tree(std::string key, TreeNode* tree_node, int price);
	virtual TreeNode* rotate_right(TreeNode* rotate_node);
	virtual TreeNode* rotate_left(TreeNode* rotate_node);
	virtual TreeNode* update_balanced_tree(TreeNode* tree_node) = 0;
};

class AVLBinarySearchTree: public BalancedBinarySearchTree
{
private:
	int get_balance_factor(TreeNode* root);
	virtual TreeNode* update_balanced_tree(TreeNode* tree_node);
};

class RBBinarySearchTree: public BalancedBinarySearchTree
{
public:
	virtual void remove_from_balanced_tree(std::string key);
private:
	virtual TreeNode* rotate_right(TreeNode* rotate_node);
	virtual TreeNode* rotate_left(TreeNode* rotate_node);
	TreeNode* change_color(TreeNode* root);
	virtual TreeNode* update_balanced_tree(TreeNode* tree_node);

	TreeNode* deleteRec(TreeNode* given_node, std::string key);
	TreeNode* deleteMin(TreeNode* given_node);
	TreeNode* fixUp(TreeNode* given_node);
	TreeNode* moveRedLeft(TreeNode* given_node);
	TreeNode* moveRedRight(TreeNode* given_node);
};


