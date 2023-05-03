#include "ApartmentLinkedList.h"

void ApartmentLinkedList::add_apartment(std::string command,std::string name, int max_bandwidth)
{
	num_of_apartments += 1;
	if (command.compare("head") == 0)
	{
		insert_head(name, max_bandwidth);
		return;
	}
	char* cstr = new char[command.length() + 1];
	std::strcpy(cstr, command.c_str());
	
	char* p = strtok(cstr, "_");
	char* x = strtok(NULL, "_");

	std::string insert_command = p;
	std::string insert_apartment_name = x;
	
	if (insert_command.compare("after")==0)
	{
		insert_after(insert_apartment_name, name, max_bandwidth);
	}
	else if  (insert_command.compare("before")==0)
	{
		insert_before(insert_apartment_name, name, max_bandwidth);
	}
}

void ApartmentLinkedList::add_flat(std::string apartment_name, int index,int initial_bandwidth, int id)
{
	ApartmentNode* curr = head;
	
	for (curr; curr->apartment_name.compare(apartment_name) != 0; curr = curr->nextP);

	FlatLinkedList* flat_list = curr->flat_list;

	if (flat_list == NULL) 
	{
		flat_list = new FlatLinkedList;
	}
	else 
	{
		if (flat_list->sum_of_initial_bandwidths() == curr->max_bandwidth)
		{
			FlatNode* new_node = FlatNode::getnode(id, 0);
			new_node->is_empty = 1;
			flat_list->add_to_index(index, new_node);
		}
		else if ((flat_list->sum_of_initial_bandwidths() + initial_bandwidth) > curr->max_bandwidth)
		{
			FlatNode* new_node = FlatNode::getnode(id, curr->max_bandwidth - initial_bandwidth);
			flat_list->add_to_index(index, new_node);
		}
		else
		{
			FlatNode* new_node = FlatNode::getnode(id, initial_bandwidth);
			flat_list->add_to_index(index, new_node);
		}
	}
}

ApartmentLinkedList* ApartmentLinkedList::remove_apartment(std::string apartment_name)
{
	ApartmentNode* prev = tail;
	ApartmentNode* curr = head;

	for (curr, prev; curr->apartment_name.compare(apartment_name) != 0;prev = curr, curr = curr->nextP);
	
	if (num_of_apartments == 1) 
	{
		ApartmentNode::freenode(curr);
		head = NULL;
		tail = NULL;
		num_of_apartments -= 1;
		return NULL;
	}
	else 
	{
		if (curr == head)
		{
			head = curr->nextP;
			tail->nextP = head;
			ApartmentNode::freenode(curr);
		}
		else if (curr == tail)
		{
			prev->nextP = head;
			tail = prev;
			ApartmentNode::freenode(curr);
		}
		else
		{
			prev->nextP = curr->nextP;
			ApartmentNode::freenode(curr);
		}
		num_of_apartments -= 1;
		return this;
	}
}

void ApartmentLinkedList::make_flat_empty(std::string apartment_name, int id)
{
	ApartmentNode* curr = head;

	for (curr; curr->apartment_name.compare(apartment_name) != 0; curr = curr->nextP);

	FlatNode* currFlat = curr->flat_list->head;

	for (currFlat; currFlat->id != id; curr = curr->nextP);

	currFlat->is_empty = 1;
	currFlat->initial_bandwidth = 0;
}

int ApartmentLinkedList::find_sum_of_max_bandwidth()
{
	int sum = 0;
	if (head != NULL)
	{
		ApartmentNode* curr = head;
		for (curr; curr->nextP != NULL; curr = curr->nextP)
		{
			sum += curr->max_bandwidth;
		};
	}
	return sum;
}

ApartmentLinkedList* ApartmentLinkedList::merge_two_apartments(std::string apartment_1, std::string apartment_2)
{
	ApartmentNode* apartment_1_node = head;
	for (apartment_1_node; apartment_1_node->apartment_name.compare(apartment_1) != 0;
		apartment_1_node = apartment_1_node->nextP);

	ApartmentNode* apartment_2_node = head;
	for (apartment_2_node; apartment_2_node->apartment_name.compare(apartment_2) != 0;
		apartment_2_node = apartment_2_node->nextP);

	FlatLinkedList* temp_list_1 = apartment_1_node->flat_list;
	FlatLinkedList* temp_list_2 = apartment_2_node->flat_list;


	if (temp_list_1 == NULL && temp_list_2 == NULL)
	{
		//do nothing
	}
	else if(temp_list_1 == NULL)
	{
		temp_list_1 = new FlatLinkedList;
		temp_list_1->head = temp_list_2->head;
		temp_list_1->tail = temp_list_2->tail;
		temp_list_2->head = NULL;
		temp_list_2->tail = NULL;


	}
	else if (temp_list_2 ==NULL)
	{
		//do nothing
	}
	else
	{
		temp_list_1->tail->nextP = temp_list_2->head;
		temp_list_2->head->prevP = temp_list_1->tail;
		temp_list_2->head = NULL;
		temp_list_2->tail = NULL;
	}

	apartment_1_node->max_bandwidth += apartment_2_node->max_bandwidth;
	return this->remove_apartment(apartment_2);
}

void ApartmentLinkedList::insert_head(std::string name, int max_bandwith) 
{
	ApartmentNode* new_node = ApartmentNode::getnode(name, max_bandwith);

	head = new_node;
	tail = new_node;
	tail->nextP = head;

}

void ApartmentLinkedList::insert_before(std::string insert_apartment_name, std::string name, int max_bandwith)
{
	if (insert_apartment_name.compare(head->apartment_name)==0) 
	{
		ApartmentNode* new_node = ApartmentNode::getnode(name,max_bandwith);

		new_node->nextP = head;
		head = new_node;
		tail->nextP = head;
	}
	else
	{
        ApartmentNode* prev = tail;
        ApartmentNode* curr = head;

        for (curr, prev; curr->apartment_name.compare(insert_apartment_name)!=0; prev = curr, curr = curr->nextP);

        ApartmentNode* x = ApartmentNode::getnode(name,max_bandwith);

        x->nextP = prev->nextP;

        prev->nextP = x;

	}

}

void ApartmentLinkedList::insert_after(std::string insert_apartment_name, std::string name, int max_bandwith)
{
	if (insert_apartment_name.compare(tail->apartment_name) == 0) 
	{
		ApartmentNode* new_node = ApartmentNode::getnode(name, max_bandwith);
		
		new_node->nextP = head;
		tail->nextP = new_node;
		tail = new_node;
	
	}
	else
	{
		ApartmentNode* curr = head;

		for (curr; curr->apartment_name.compare(insert_apartment_name) != 0;curr = curr->nextP);

		ApartmentNode* new_node = ApartmentNode::getnode(name, max_bandwith);
		
		new_node->nextP = curr->nextP;
		curr->nextP = new_node;
	}

}

