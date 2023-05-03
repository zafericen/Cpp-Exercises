#include "ApartmentLinkedList.h"
#include <vector>

void ApartmentLinkedList::add_apartment(std::string name, std::string command, int max_bandwidth)
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
	ApartmentNode* curr = find_apartment(apartment_name);

	if (curr->flat_list == NULL)
	{
		curr->flat_list = new FlatLinkedList;
	}

	FlatLinkedList* flat_list = curr->flat_list;

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
	ApartmentNode* curr = find_apartment(apartment_name);

	FlatNode* currFlat = curr->flat_list->get_flat_by_id(id);

	currFlat->is_empty = 1;
	currFlat->initial_bandwidth = 0;
}

int ApartmentLinkedList::find_sum_of_max_bandwidth()
{
	int sum = 0;
	if (head != NULL)
	{
		ApartmentNode* curr = head;
		for (int i = 0; i<num_of_apartments ;i++)
		{
			sum += curr->max_bandwidth;
			curr = curr->nextP;
		};
	}
	return sum;
}

ApartmentLinkedList* ApartmentLinkedList::merge_two_apartments(std::string apartment_1, std::string apartment_2)
{
	ApartmentNode* apartment_1_node = find_apartment(apartment_1);

	ApartmentNode* apartment_2_node = find_apartment(apartment_2);

	FlatLinkedList* temp_list_1 = apartment_1_node->flat_list;
	FlatLinkedList* temp_list_2 = apartment_2_node->flat_list;


	if (temp_list_1 == NULL && temp_list_2 == NULL)
	{
		//do nothing
	}
	else if(temp_list_1 == NULL)
	{
		apartment_1_node->flat_list = new FlatLinkedList;
		temp_list_1 = apartment_1_node->flat_list;

		temp_list_1->head = temp_list_2->head;
		temp_list_1->tail = temp_list_2->tail;
		temp_list_2->head = NULL;
		temp_list_2->tail = NULL;

		temp_list_1->num_of_flats += temp_list_2->num_of_flats;
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

		temp_list_1->num_of_flats += temp_list_2->num_of_flats;
	}
	
	apartment_1_node->max_bandwidth += apartment_2_node->max_bandwidth;
	return this->remove_apartment(apartment_2);
}

void ApartmentLinkedList::relocate_flats_to_same_apartments(std::string new_apartment_name,
	int flat_id_to_shift,std::vector<int>  id_array)
{
	ApartmentNode* new_apartment = find_apartment(new_apartment_name);
	
	int shift_index = 0;

	FlatNode* shift_flat = new_apartment->flat_list->head;
	for (shift_flat;shift_flat->id != flat_id_to_shift ; shift_flat = shift_flat->nextP)
	{
		shift_index += 1;
	}

	for (int i : id_array)
	{
		ApartmentNode* apartment_p = head;
		for (int i2 = 0; i2 < num_of_apartments; i2++)
		{
			if (apartment_p->flat_list == NULL) 
			{
				break;
			}
			FlatNode* flat_p = apartment_p->flat_list->get_flat_by_id(i);

			if (flat_p == NULL)
			{
				apartment_p = apartment_p->nextP;
				continue;
			}
			else
			{
				flat_p = apartment_p->flat_list->remove_flat(flat_p);
				apartment_p->max_bandwidth -= flat_p->initial_bandwidth;

				new_apartment->flat_list->add_to_index(shift_index, flat_p);
				new_apartment->max_bandwidth += flat_p->initial_bandwidth;
				shift_index += 1;
				break;
			}
		}
	}

}

std::string ApartmentLinkedList::list_apartments()
{
	std::string return_string = "";

	ApartmentNode* curr = head;
	for (int i = 0;i<num_of_apartments;i++)
	{
		return_string += curr->apartment_name + "(" + std::to_string(curr->max_bandwidth) + ")";

		if(curr->flat_list == NULL)
		{
			continue;
		}

		FlatNode* currFlat = curr->flat_list->head;
		for(currFlat;currFlat != NULL; currFlat = currFlat ->nextP)
		{
			return_string = return_string +  "\t "+ "Flat" + std::to_string(currFlat->id) + 
				"(" + std::to_string(currFlat->initial_bandwidth) + ")" ; 
		}

		return_string += "\n";

		curr = curr->nextP;
	}

	return return_string;
}

ApartmentNode* ApartmentLinkedList::find_apartment(std::string apartment_name)
{
	ApartmentNode* apartment = head;
	for (apartment; apartment->apartment_name.compare(apartment_name) != 0;
		apartment = apartment->nextP);
	return apartment;
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

		while (curr->apartment_name.compare(insert_apartment_name) != 0)
		{
			prev = curr;
			curr = curr->nextP;
		}

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
		ApartmentNode* curr = find_apartment(insert_apartment_name);

		ApartmentNode* new_node = ApartmentNode::getnode(name, max_bandwith);
		
		new_node->nextP = curr->nextP;
		curr->nextP = new_node;
	}

}

