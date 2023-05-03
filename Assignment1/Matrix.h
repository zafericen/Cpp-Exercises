#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>

class Matrix
{
public:
	//matrix members
	int** matrix_array;
	int size[2];
	int position[2]{0, 0};

	//constructor and deconstructor
	Matrix(int x_size, int y_size, const char* fileName);
	~Matrix();
	//initialing matrix array based on the file
	int** initializeMatrix(const char* fileName);
	//function that takes dot product of two matrix
	static int dotProduct(Matrix& key_matrix , Matrix& map_matrix);
	//operator [] definition to easly access the array member of the object
	int* operator[](int index);
};
#endif
