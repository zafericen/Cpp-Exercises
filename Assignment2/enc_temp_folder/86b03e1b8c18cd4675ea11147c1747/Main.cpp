#include "ApartmentLinkedList.h"
#include <iostream>

int main()
{
	ApartmentLinkedList* deneme_list = new ApartmentLinkedList;

	deneme_list->add_apartment("X", "head", 50);
	deneme_list->add_apartment( "Z", "after_X", 75);
	deneme_list->add_apartment("Y", "before_Z", 100);
	deneme_list->add_apartment("Q", "after_Z", 150);
	deneme_list->add_apartment("P ", "after_Q", 75);
	deneme_list->add_apartment("R", "before_Y", 125);
	deneme_list->add_apartment("S", "before_P", 100);
	//deneme_list->add_apartment("T", "before_Z", 50);


	//deneme_list->add_flat("X", 0, 25, 1);
	//deneme_list->add_flat("X", 1, 20, 4);

	//deneme_list->add_flat("Z", 0, 20, 9);
	//deneme_list->add_flat("Z", 1, 10, 7);
	//deneme_list->add_flat("Z", 2, 15, 11);
	//deneme_list->add_flat("Z", 1, 45, 2);

	//deneme_list->add_flat("Q", 0, 45, 10);
	//deneme_list->add_flat("Q", 1, 30, 12);
	//deneme_list->add_flat("Q", 1, 25, 13);
	
	//deneme_list->remove_apartment("Y");

	//deneme_list->add_flat("R", 0, 25, 14);
	//deneme_list->add_flat("R", 0, 30, 15);

	//deneme_list->add_flat("T", 0, 55, 16);

	//deneme_list->merge_two_apartments("T", "R");
	//deneme_list->merge_two_apartments("X", "P");

	//deneme_list->add_flat("S", 0, 35, 17);
	//deneme_list->add_flat("S", 1, 25, 18);

	//std::cout << deneme_list->find_sum_of_max_bandwidth();

	//std::cout << deneme_list->list_apartments();

	//deneme_list->make_flat_empty("Z", 2);
	//deneme_list->make_flat_empty("Q", 10);


	std::vector<int> deneme_vector = { 4,2,13 };
	//deneme_list->relocate_flats_to_same_apartments("S",17,deneme_vector);


	//std::cout<< deneme_list->list_apartments();
}
