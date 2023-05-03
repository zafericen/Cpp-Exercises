#pragma once
#include "BinarySearchTree.h"
#include <sstream>
#include <vector>
#include <fstream>
namespace Handler
{
	void read_and_execute(const char* input_argument, const char* output_argument, BinarySearchTree* tree);
	
	void split(std::vector<std::string>& splited, std::string line, const char delimeter);
};

