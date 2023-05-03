#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "Matrix.h"
#include <iostream>
#include <string>
#include <fstream>

//namespace for implement the rules of the game
namespace GameRules
{	
	//variable for controlling if the game is finished or not
	extern bool isTresuareFound;
	//variable for writing output to output file
	extern std::string outputString;
	//function that moves key matrix over the map matrix according to command that takes
	//this function updates output string according to command
	void move(int command, Matrix& key_matrix, Matrix& map_matrix);
	//function that move key matrix and searching for tresuare;if it finds it finishes,if not it searchs again recursivly
	//this function updates output string for every search operation
	void search(Matrix& key_matrix, Matrix& map_matrix);
	//writing output string to the file 
	void writeOutPut(const char* output_file_name);
	
};

#endif
