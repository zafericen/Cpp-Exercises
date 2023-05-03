#include "ApartmentNode.h"

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

ApartmentNode::ApartmentNode(std::string name = NULL, int max_bandwidth = NULL)
{
	this->apartment_name = name;
	this->max_bandwidth = max_bandwidth;
}
ApartmentNode::~ApartmentNode()
{
	FlatNode* head = flat_list.head;
	while (head->nextP != NULL)
	{
		FlatNode* x = head;
		head = head->nextP;
		FlatNode::freenode(x);
	}
}
