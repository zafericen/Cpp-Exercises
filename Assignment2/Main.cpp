#include "Handler.h"
#include <iostream>



int main(int argc, char* argv[])
{
	ApartmentLinkedList* apartment_list = new ApartmentLinkedList;
	
	Handler::run_program(argv[1], argv[2],apartment_list);
}


