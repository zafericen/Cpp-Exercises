#ifndef APARTMENT_LINKED_LIST_H
#define APARTMENT_LINKED_LIST_H
 
#include "ApartmentNode.h"
#include <iostream>
#include <vector>
//class for storing apartmentnodes and performing actions on them 
class ApartmentLinkedList
{
public:
	//linkedd list members
	ApartmentNode* head = NULL;
	ApartmentNode* tail = NULL;
	//mothod that takes new apartment node and inserting it to apartment list based on given commands
	void add_apartment(ApartmentNode* new_node, std::string command);
	//method that finds apartment based on its name and adds new flat to its flat list
	void add_flat(std::string apartment_name,int index,int initial_bandwidth, int id);
	//removes apartment from linked list and returns updated list
	ApartmentLinkedList* remove_apartment(std::string apartment_name);
	//makes certain flat of certain apartment empty
	void make_flat_empty(std::string apartment_name, int id);
	//adds all max bandwiths of apartments and retuns it
	int find_sum_of_max_bandwidth();
	//takes apartment_2's flat list and adds it to apartment_1 and deletes apartment to
	ApartmentLinkedList* merge_two_apartments(std::string apartment_1, std::string apartment_2);
	/*
	takes some flats based on id and removes them from thier lists and adds them to specified 
	apartment's specified flat list's specified index
	*/
	void relocate_flats_to_same_apartments(std::string new_apartment_name, int flat_id_to_shift,std::vector<int> id_array);
	//writes all the apartments and their attiributes(bandwith,flatlist...) in the street
	std::string list_apartments();

private:
	//helper member for some functions
	int num_of_apartments = 0;
	//helper functions for some functions that needs to find apartments based on name
	ApartmentNode* find_apartment(std::string apartment_name);
	//helper function for inserting to head adn initializing apartment list
	void insert_head(ApartmentNode* new_node);
	//helper function for inserting new node before certain node
	void insert_before(std::string insert_apartment_name, ApartmentNode* new_node);
	//helper function for inserting new node after certain node
	void insert_after(std::string insert_apartment_name, ApartmentNode* new_node);
};
#endif 