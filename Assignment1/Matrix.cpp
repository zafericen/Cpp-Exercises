#include "Matrix.h"



Matrix::Matrix(int x_size, int y_size, const char* fileName)
{
	size[0] = x_size;
	size[1] = y_size;
	matrix_array = initializeMatrix(fileName);
}

Matrix::~Matrix()
{
	for (int y{}; y < size[1]; ++y) 
	{
		delete[] matrix_array[y];
	}
	delete[] matrix_array;
}

int Matrix::dotProduct(Matrix& key_matrix,Matrix& map_matrix)
{
	int return_number{ 0 };
	for (int y = 0; y < key_matrix.size[1]; y++)
	{
		for (int x = 0; x < key_matrix.size[0]; x++)
		{
			return_number += key_matrix[y][x] * map_matrix[y+key_matrix.position[1]][x+key_matrix.position[0]];
		}
	}
	return return_number;
}

int* Matrix::operator[](int index)
{
	return matrix_array[index];
}

int** Matrix::initializeMatrix(const char* fileName)
{
	int** return_array{ new int*[size[1]] };
	std::ifstream matrixFile(fileName);
	for (int y{ 0 }; y < size[1]; ++y) {

		return_array[y] = new int[size[0]];

		for (int x{ 0 }; x < size[0]; ++x) {
			matrixFile >> return_array[y][x];
		}
	}
	matrixFile.close();
	return return_array;
}

