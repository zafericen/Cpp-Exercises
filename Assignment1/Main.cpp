#include "Matrix.h"
#include "GameRules.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[])
{
	//initialazing sizes of matrixes
	int map_matrix_size_y = atoi(strtok(argv[1], "x"));
	int map_matrix_size_x = atoi(strtok(NULL, "x"));
	int key_matrix_size = atoi(argv[2]);
	//initialazing names of files
	const char* map_file_name = argv[3];
	const char* key_file_name = argv[4];
	const char* output_file_name = argv[5];
	//creating map matrix and key matrix objects
	Matrix key_matrix{ key_matrix_size,key_matrix_size,key_file_name };
	Matrix map_matrix{ map_matrix_size_x,map_matrix_size_y,map_file_name };
	//searching until game is finished
	GameRules::search(key_matrix, map_matrix);
	//writing the output
	GameRules::writeOutPut(output_file_name);
}