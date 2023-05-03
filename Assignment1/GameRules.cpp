#include "GameRules.h"



namespace GameRules 
{
	bool isTresuareFound{ false };
	std::string outputString{""};

	void move(int command, Matrix& key_matrix, Matrix& map_matrix)
	{
		int& key_matrix_x = key_matrix.position[0];
		int& key_matrix_y = key_matrix.position[1];
		int& key_matrix_size = key_matrix.size[0];

		outputString += std::to_string(key_matrix_y + (key_matrix_size / 2) ) + "," + 
			std::to_string(key_matrix_x + (key_matrix_size / 2));

		switch (command)
		{
		case 0:
			isTresuareFound = true;
			break;
		case 1:
			key_matrix_y -= key_matrix_size;
			if (key_matrix_y < 0)
			{
				key_matrix_y += key_matrix_size * 2;
			}
			break;
		case 2:
			key_matrix_y += key_matrix_size;
			if (key_matrix_y + (key_matrix_size - 1) >= map_matrix.size[1])
			{
				key_matrix.position[1] -= key_matrix.size[1] * 2;
			}
			break;
		case 3:
			key_matrix_x += key_matrix_size;
			if (key_matrix_x + (key_matrix_size - 1) >= map_matrix.size[0])
			{
				key_matrix_x -= key_matrix_size * 2;
			}
			break;
		case 4:
			key_matrix_x -= key_matrix_size;
			if (key_matrix_x < 0)
			{
				key_matrix_x += key_matrix_size * 2;
			}
			break;
		}
		

	}


	void search(Matrix& key_matrix, Matrix& map_matrix)
	{
		int result_of_dot_product{ Matrix::dotProduct(key_matrix, map_matrix) };
		int mod_of_result{ result_of_dot_product % 5 };
		
		if (mod_of_result >= 0)
		{
			move(mod_of_result, key_matrix, map_matrix);
		}
		else
		{
			mod_of_result += 5;
			move(mod_of_result, key_matrix, map_matrix);
		}

		outputString += ":"+std::to_string(result_of_dot_product) + "\n";

		if (!isTresuareFound)
		{
			search(key_matrix, map_matrix);
		}

	}

	void writeOutPut(const char* output_file_name) 
	{
		std::ofstream outputFile(output_file_name);
		outputFile << outputString;
		outputFile.close();
	}

}
