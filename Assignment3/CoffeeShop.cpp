#include "CoffeeShop.h"

void CoffeeShop::manage_shop(const char* input_argument, const char* output_argument, int model_type)
{
	read_input(input_argument);

	open_shop(model_type);

	int coffee_count = order_queue->size;

	while (coffee_count != finished_coffee_queue->size)
	{
		next_action(model_type);
	}

	write_output(output_argument,model_type);
}

void CoffeeShop::open_shop(int model_type)
{
	if (model_type == 0)
	{
		CoffeeQueue* cashier_queue = new CoffeeQueue;
		CoffeeQueue* barista_queue = new BaristaCoffeeQueue;

		for (Employee* curr_cashier : cashier_list)
		{
			curr_cashier->supply_queue = cashier_queue;
			curr_cashier->pass_queue = barista_queue;
		}
		for (Employee* curr_barista : barista_list)
		{
			curr_barista->supply_queue = barista_queue;
			curr_barista->pass_queue = finished_coffee_queue;
		}
		
	}
	else if (model_type == 1)
	{
		CoffeeQueue* cashier_queue = new CoffeeQueue;
		for (Employee* curr_barista : barista_list)
		{
			CoffeeQueue* barista_queue = new BaristaCoffeeQueue;
			curr_barista->supply_queue = barista_queue;
			curr_barista->pass_queue = finished_coffee_queue;
		}
		for (int i = 0;  i< cashier_list.size();++i)
		{
			Employee* curr_cashier = cashier_list.at(i);
			Employee* curr_barista = barista_list.at(i / 3);
			curr_cashier->supply_queue = cashier_queue;
			curr_cashier->pass_queue = curr_barista->supply_queue;
		}
	}
}

void CoffeeShop::next_action(int model_type)
{
	CoffeeNode* smallest_time_coffee = order_queue->head;
	Employee* smallest_time_cashier = find_smallest(cashier_list);
	Employee* smallest_time_barista = find_smallest(barista_list);
	
	int action_number = action_selector(smallest_time_coffee, smallest_time_cashier, smallest_time_barista, model_type);
	
	if (action_number == 0)
	{
		//push order to cashier queue
		global_time = smallest_time_coffee->enter_time;
		cashier_list.at(0)->supply_queue->enqueue(order_queue->dequeue());
	}
	else if (action_number == 1)
	{
		//push order to available cashier
		global_time = smallest_time_coffee->enter_time;
		Employee* avail_cashier = find_available(cashier_list);
		avail_cashier->take_order(order_queue->dequeue(), global_time);
	}
	else if (action_number == 2)
	{
		//push finished order to barista queue
		global_time = smallest_time_cashier->order_finish_time;
		smallest_time_cashier->pass_order_to_queue();
		smallest_time_cashier->take_order_from_queue(global_time);
	}
	else if (action_number == 3)
	{
		//push finished order to available barista
		global_time = smallest_time_cashier->order_finish_time;
		CoffeeNode* finished_order = smallest_time_cashier->pass_order();
		if (model_type == 0)
		{
			//model type N
			Employee* avail_barista = find_available(barista_list);
			avail_barista->take_order(finished_order, global_time);
		}
		else if (model_type == 1)
		{
			//model type N/3
			int cashier_id = get_index(cashier_list, smallest_time_cashier);
			Employee* avail_barista = barista_list.at(cashier_id / 3);
			avail_barista->take_order(finished_order, global_time);
		}
		smallest_time_cashier->take_order_from_queue(global_time);
	}
	else if (action_number == 4)
	{
		//push finished coffee to customer
		global_time = smallest_time_barista->order_finish_time;
		smallest_time_barista->curr_coffeeP->coffee_finished_time = global_time;
		smallest_time_barista->pass_order_to_queue();
		smallest_time_barista->take_order_from_queue(global_time);
	}
}

int CoffeeShop::action_selector(CoffeeNode* smallest_time_coffee, 
	Employee* smallest_time_cashier, Employee* smallest_time_barista, int model_type)
{
	//dummy value
	float finish_time_coffee{ 2000000.0f };
	if (smallest_time_coffee != nullptr)
	{
		finish_time_coffee = smallest_time_coffee->enter_time;
	}
	//dummy value
	float finish_time_cashier{ 2000000.0f };
	if (smallest_time_cashier != nullptr)
	{
		finish_time_cashier = smallest_time_cashier->order_finish_time;
	}
	//dummy value
	float finish_time_barista{ 2000000.0f };
	if (smallest_time_barista != nullptr)
	{
		finish_time_barista = smallest_time_barista->order_finish_time;
	}

	if (finish_time_coffee < finish_time_barista && finish_time_coffee < finish_time_cashier)
	{
		Employee* avail_cashier = find_available(cashier_list);

		if (avail_cashier == nullptr)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if (finish_time_cashier < finish_time_coffee && finish_time_cashier < finish_time_barista)
	{
		if (model_type == 0)
		{
			Employee* avail_barista = find_available(barista_list);
			if (avail_barista == nullptr)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
		else if(model_type == 1)
		{
			int cashier_id = get_index(cashier_list, smallest_time_cashier);
			Employee* avail_barista = barista_list.at(cashier_id / 3);
			if (avail_barista->is_busy)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else if (finish_time_barista < finish_time_coffee && finish_time_barista < finish_time_cashier)
	{
		return 4;
	}
}

Employee* CoffeeShop::find_smallest(std::vector<Employee*>& employee_vector)
{
	
	Employee* return_employee = employee_vector.at(0);

	for (int i = 0; i < employee_vector.size(); i++)
	{
		if (employee_vector.at(i)->is_busy && !return_employee->is_busy)
		{
			return_employee = employee_vector.at(i);
		}
		else if (employee_vector.at(i)->is_busy)
		{
			if (employee_vector.at(i)->order_finish_time < return_employee->order_finish_time)
			{
				return_employee = employee_vector.at(i);
			}
		}
		
	}
	if (!return_employee->is_busy)
	{
		
		return nullptr ;
	}
	else
	{
		return return_employee;
	}
}

Employee* CoffeeShop::find_available(std::vector<Employee*> &employee_vector)
{
	Employee* return_employee = nullptr;

	for (int i = 0; i < employee_vector.size(); i++)
	{
		if (employee_vector.at(i)->is_busy)
		{
			continue;
		}
		else if (!employee_vector.at(i)->is_busy)
		{
			return_employee = employee_vector.at(i);
			break;
		}
	}
	return return_employee;
}

int CoffeeShop::get_index(std::vector<Employee*> list, Employee* key)
{
	int index{ 0 };
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i) == key)
		{
			index = i;
			break;
		}
	}
	return index;
}

void CoffeeShop::read_input(const char* input_path)
{
	std::ifstream reader{ input_path };

	int cashier_count,coffee_count;

	reader >> cashier_count;
	reader >> coffee_count;

	for (int i = 0 ; i < coffee_count; ++i) {
		float enter_time, cashier_time, barista_time, price;
		reader >> enter_time;
		reader >> cashier_time;
		reader >> barista_time;
		reader >> price;
		order_queue->enqueue(new CoffeeNode{ enter_time, cashier_time, barista_time, price});
	}
	for (int i2 = 0 ; i2 < cashier_count; ++i2)
	{
		cashier_list.push_back(new Cashier);
	}
	for (int i3 = 0; i3 < cashier_count/3; ++i3)
	{
		barista_list.push_back(new Barista);
	}
	reader.close();
}

float CoffeeShop::round(float var)
{
	float value = (int)(var * 100 + .5);
	return value / 100;
}

void CoffeeShop::write_output(const char* output_argument,int model_type)
{
	std::ofstream output_file;
	if (model_type == 0)
	{
		output_file.open(output_argument);
	}
	else
	{
		output_file.open(output_argument, std::fstream::app);
	}
	

	output_file << global_time << "\n";
	output_file << cashier_list.at(0)->supply_queue->max_size << "\n";
	if (model_type == 0)
	{
		output_file << barista_list.at(0)->supply_queue->max_size << "\n";
	}
	else if(model_type == 1)
	{
		for (Employee* curr_barista: barista_list)
		{
			output_file << curr_barista->supply_queue->max_size << "\n";
		}
	}

	for (Employee* curr_cashier : cashier_list)
	{
		output_file << std::fixed << std::setprecision(2) << round(curr_cashier->utilization(global_time))<< "\n";
	}

	for (Employee* curr_barista : barista_list)
	{
		output_file << std::fixed << std::setprecision(2) <<  round(curr_barista->utilization(global_time)) << "\n";
	}

	while (finished_coffee_queue->size !=0)
	{
		CoffeeNode* curr_coffee = finished_coffee_queue->dequeue();
		output_file << std::fixed << std::setprecision(2) << round(curr_coffee->turnaround_times()) << "\n";
		delete curr_coffee;
	}
	output_file << "\n";
	output_file.close();
}