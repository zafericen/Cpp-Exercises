#include "Handler.h"
#include <queue>

void Handler::read_and_execute(const char* input_argument, const char* output_argument, BinarySearchTree* tree)
{

	std::ifstream input_reader{ input_argument };
	std::ofstream output_file(output_argument);
	std::string curr_line{};

	if (input_reader.is_open())
	{
		while (std::getline(input_reader, curr_line))
		{
			std::vector<std::string> splited_line;
			split(splited_line, curr_line, '\t');

			if (splited_line[0].compare("insert") == 0)
			{
				tree->insert(splited_line[1], splited_line[2], std::stoi(splited_line[3]));
			}

			else if (splited_line[0].compare("remove") == 0)
			{
				tree->remove(splited_line[1], splited_line[2]);
			}

			else if (splited_line[0].compare("printAllItems") == 0)
			{
				output_file << "command:" << splited_line[0] << "\n{\n";
				output_file << tree->printAllItems();
				output_file << "\n}\n";
			}

			else if (splited_line[0].compare("printAllItemsInCategory") == 0)
			{
				output_file << "command:" << splited_line[0] << "\t" << splited_line[1] << "\n{\n";
				output_file << tree->printAllItemsInCategory(splited_line[1]);
				output_file << "}\n";
			}

			else if (splited_line[0].compare("printItem") == 0 || splited_line[0].compare("find") == 0)
			{
				output_file << "command:" << splited_line[0] << "\t" << splited_line[1] << "\t" << splited_line[2] << "\n{";
				output_file << tree->find(splited_line[1], splited_line[2]);
				output_file << "}\n";
			}

			else if (splited_line[0].compare("updateData") == 0)
			{
				tree->update_data(splited_line[1], splited_line[2], std::stoi(splited_line[3]));
			}
		}
		input_reader.close();
		output_file.close();
	}
}

void Handler::split(std::vector<std::string>& splited, std::string line, const char delimeter)
{
	std::stringstream string_stream(line);
	std::string token;

	while (!string_stream.eof()) {
		std::getline(string_stream, token, delimeter);
		splited.push_back(token);
	}
}