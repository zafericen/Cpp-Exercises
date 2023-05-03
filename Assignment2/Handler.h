#ifndef HANDLER_H
#define HANDLER_H

#include "ApartmentLinkedList.h"
#include <fstream>
#include <sstream>

//namespace for helper functions
namespace Handler
{
	//reads input and calls relevant functions based on input file
	void run_program(const char* input_argument, const char* output_argument, ApartmentLinkedList* apartment_list);

	//function for spliting std::string and adding splitted substrings to a vector
	void split(std::vector<std::string>& splited, std::string line, char delimeter);

};
#endif
