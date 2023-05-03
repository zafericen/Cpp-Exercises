#include "ApartmentNode.h"
#include <iostream>

ApartmentNode* ApartmentNode::getnode(std::string name, int apartment_max_bandwith)
{
	ApartmentNode* p;
	p = new ApartmentNode(name, apartment_max_bandwith);
	return p;
}

void ApartmentNode::freenode(ApartmentNode* p)
{
	delete p;
}

ApartmentNode::ApartmentNode(std::string name, int max_bandwidth)
{
	this->apartment_name = name;
	this->max_bandwidth = max_bandwidth;
}
ApartmentNode::~ApartmentNode()
{
	if (flat_list != NULL) 
	{
		FlatNode* head = flat_list->head;
		while (head != NULL)
		{
			FlatNode* x = head;
			head = head->nextP;
			FlatNode::freenode(x);
		}
		delete flat_list;
	}
}
