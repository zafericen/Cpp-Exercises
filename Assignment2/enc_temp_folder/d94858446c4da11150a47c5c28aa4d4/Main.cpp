#include "ApartmentLinkedList.h"
#include <iostream>

int main()
{
	ApartmentLinkedList* deneme_list = new ApartmentLinkedList;
	deneme_list->add_apartment("head", "X", 50);
	deneme_list->add_apartment("after_X", "Z", 75);
	deneme_list->add_apartment("before_Z", "Y", 75);
	deneme_list->add_flat("X", 0, 25, 1);
	deneme_list->add_flat("X", 0, 25, 2);
	deneme_list->add_flat("X", 0, 25, 3);
	deneme_list->add_flat("X", 0, 25, 4);

	deneme_list->add_flat("Y", 0, 25, 8);
	deneme_list->add_flat("Y", 0, 25, 7);
	deneme_list->add_flat("Y", 0, 25, 6);
	deneme_list->add_flat("Y", 0, 25, 5);

	std::cout<< deneme_list->head->flat_list->head->id;
}
