#ifndef APARTMENT_NODE_H
#define APARTMENT_NODE_H

#include "FlatLinkedList.h"
#include <string>
//class for apartment nodes
class ApartmentNode
{
public:
	//apartment node members
	std::string apartment_name;
	int max_bandwidth;
	FlatLinkedList* flat_list = NULL;

	ApartmentNode* nextP=NULL;
	
	//method to get new node based on arguments
	static ApartmentNode* getnode(std::string name, int max_bandwith);
	//method to delete apartment node from heap
	static void freenode(ApartmentNode* p);

	//constructer for class
	ApartmentNode(std::string name,int max_bandwidth);
	//deconstructer to delete flat list
	~ApartmentNode();
};

#endif