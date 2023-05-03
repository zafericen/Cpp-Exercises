#include "Handler.h"

namespace Handler {
	void run_program(const char* input_argument, const char* output_argument, ApartmentLinkedList* apartment_list)
	{
		std::ifstream input_reader{ input_argument };
		std::ofstream output_file(output_argument);

		std::string curr_line;

		while (std::getline(input_reader, curr_line)) {
			std::vector<std::string> splitted_line;
			split(splitted_line, curr_line, '\t');

			if (splitted_line[0].compare("add_apartment") == 0) 
			{
				ApartmentNode* new_node = ApartmentNode::getnode(splitted_line[1],std::stoi(splitted_line[3]));
				apartment_list->add_apartment(new_node, splitted_line[2]);
			}
			else if (splitted_line[0].compare("add_flat") == 0)
			{
				apartment_list->add_flat(splitted_line[1], std::stoi(splitted_line[2]), std::stoi(splitted_line[3]), std::stoi(splitted_line[4]));
			}
			else if (splitted_line[0].compare("remove_apartment") == 0)
			{
				apartment_list->remove_apartment(splitted_line[1]);
			}
			else if (splitted_line[0].compare("make_flat_empty")) 
			{
				apartment_list->make_flat_empty(splitted_line[1], std::stoi(splitted_line[2]));
			}
			else if (splitted_line[0].compare("find_sum_of_max_bandwidths") == 0)
			{
				output_file << "sum of bandwidth:" << apartment_list->find_sum_of_max_bandwidth() << "\n\n";
			}
			else if (splitted_line[0].compare("merge_two_apartments") == 0) 
			{
				apartment_list->merge_two_apartments(splitted_line[1], splitted_line[2]);
			}
			else if (splitted_line[0].compare("relocate_flats_to_same_apartment") == 0)
			{
				std::vector<int> id_array = {};
				
				std::vector<std::string> id_array_string;  ;
				split(id_array_string, splitted_line[3].substr(1, splitted_line[3].size() - 2), ',');

				for (std::string ids : id_array_string) {
					id_array.push_back(std::stoi(ids));
				}

				apartment_list->relocate_flats_to_same_apartments(splitted_line[1], std::stoi(splitted_line[2]), id_array);
			}
			else if (splitted_line[0].compare("list_apartments") == 0) {
				output_file << apartment_list->list_apartments() << "\n";
			}
			
		}
	}

	void split(std::vector<std::string>& splited, std::string line, const char delimeter)
	{
		std::stringstream ss(line);
		std::string token;
		while (!ss.eof()) {
			std::getline(ss, token, delimeter);
			splited.push_back(token);
		}
	}
}
