#include "ApartmentLinkedList.h"
#include <iostream>

int main()
{
	ApartmentLinkedList deneme_list;
	deneme_list.add_apartment("head", "X", 50);
	deneme_list.add_apartment("after_X", "Z", 75);
	deneme_list.add_apartment("before_Z", "Y", 75);
	deneme_list.remove_apartment("X");
	deneme_list.remove_apartment("Y");
	deneme_list.remove_apartment("Z");
	std::cout << deneme_list.head->apartment_name;
}
