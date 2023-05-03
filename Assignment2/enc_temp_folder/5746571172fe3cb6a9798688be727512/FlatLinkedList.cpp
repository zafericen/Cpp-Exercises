#include "FlatLinkedList.h"

int FlatLinkedList::sum_of_bandwidths()
{
	int sum = 0;
	if (head != NULL) 
	{
		FlatNode* curr = head;
		for (curr; curr->nextP != NULL; curr = curr->nextP)
		{
			sum += curr->initial_bandwidth;
		};
	}

	return sum;
}

void FlatLinkedList::add_to_index(int index, FlatNode* new_node)
{
	if (head == NULL) 
	{
		head = new_node;
		tail = new_node;
	}
	else if (index == 0)
	{
		new_node->nextP = head;
		head->prevP = new_node;
		head = new_node;
	}
	else if (index == num_of_flats)
	{
		tail->nextP = new_node;
		new_node->prevP = tail;
		tail = new_node;
	}
	else
	{
		FlatNode* curr = head;

		for (int i = 0; i < index - 1; i++) 
		{
			curr = curr->nextP;
		}
		new_node->prevP = curr;
		new_node->nextP = curr->nextP;
		new_node->nextP->prevP = new_node;
		curr->nextP = new_node;

	}
}
