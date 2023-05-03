#include "FlatLinkedList.h"

int FlatLinkedList::sum_of_initial_bandwidths()
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
	num_of_flats += 1;
}

FlatNode* FlatLinkedList::get_flat_by_id(int id)
{
	
	FlatNode* currFlat = head;
	for (currFlat; currFlat != NULL && currFlat->id != id ; currFlat = currFlat->nextP);
	return currFlat;
}

FlatNode* FlatLinkedList::remove_flat(FlatNode* remove_flat)
{
	if (head == remove_flat)
	{
		head = head->nextP;
		head->prevP = NULL;
		remove_flat->nextP = NULL;
	}
	else if (tail == remove_flat)
	{
		tail = tail->prevP;
		tail->nextP = NULL;
		remove_flat->prevP = NULL;
		
	}
	else
	{
		remove_flat->prevP->nextP = remove_flat->nextP;
		remove_flat->nextP->prevP = remove_flat->prevP;
		remove_flat->nextP = NULL;
		remove_flat->prevP = NULL;
	}
	num_of_flats -= 1;
	return remove_flat;
}
