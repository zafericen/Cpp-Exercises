#ifndef FLAT_LINKED_LIST_H
#define FLAT_LINKED_LIST_H

#include "FlatNode.h"
//class for storing flatnodes and performing actions on them
class FlatLinkedList
{
public:
	//linked list members
	FlatNode* head = NULL;
	FlatNode* tail = NULL;
	int num_of_flats = 0;

	//returns total of bandwiths of flats it stores
	int sum_of_initial_bandwidths();
	//adds new flat node to spesific index in the linked list
	void add_to_index(int index, FlatNode* new_node);
	//finds spesific flat which its id is identical to argument and returns its pointer
	FlatNode* get_flat_by_id(int id);
	//removes flat from linked list
	FlatNode* remove_flat(FlatNode* remove_flat);
};

#endif