#pragma once
#include "Employee.h"
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
class CoffeeShop
{
public:
	//time t
	float global_time = 0;
	//queue that stores coffee order's order
	CoffeeQueue* order_queue = new CoffeeQueue;
	// priority queue that stores finished coffee orders relative to their enter time
	CoffeeQueue* finished_coffee_queue = new TimePriorityCoffeeQueue;
	//employee lists
	std::vector<Employee *> cashier_list;
	std::vector<Employee *> barista_list;
	//main method that manages entire coffee shop
	void manage_shop(const char* input_argument, const char* output_argument, int model_type);
	//method that reads input and creates orders and employees
	void read_input(const char* input_argument);
	//method that initializes all variables of employees and orders thus "opens the shop"
	void open_shop(int model_type);
	//method that selects next smallest time possible action
	/*
	* action numbers:
	*	0 = push order to cashier queue
	*	1 = push order to available cashier
	*	2 = push finished order to barista queue
	*	3 = push finished order to available barista
	*	4 = push finished coffee to customer
	*/
	void next_action(int model_type);
	
	//methods that finds smallest and available employees acording to list that was given
	Employee* find_smallest(std::vector<Employee *>& employee_vector);
	Employee* find_available(std::vector<Employee *>& employee_vector);
	//method that returns index of spesific element in the give vector
	int get_index(std::vector<Employee * > list, Employee* key);
	//method that returns action number acording to possibilities of given arguments
	int action_selector(CoffeeNode*, Employee*, Employee*, int model_type);
	//method that writes output to given file path
	void write_output(const char* output_argument,int model_type);
	//method that even rounds given variable and returns 
	float round(float var);

};

