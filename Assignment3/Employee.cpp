#include "Employee.h"

CoffeeNode* Employee::pass_order()
{

	CoffeeNode* pass_coffee = curr_coffeeP;
	curr_coffeeP = nullptr;
	is_busy = false;
	return pass_coffee;
}

void Employee::pass_order_to_queue()
{
	CoffeeNode* pass_coffee = curr_coffeeP;
	curr_coffeeP = nullptr;
	is_busy = false;
	pass_queue->enqueue(pass_coffee);
}

float Employee::utilization(float global_time)
{
	return total_busy_time/global_time;
}

void Cashier::take_order(CoffeeNode* coffee_order, float enter_time)
{
	curr_coffeeP = coffee_order;
	total_busy_time += curr_coffeeP->cashier_order_time;
	order_finish_time = curr_coffeeP->cashier_order_time + enter_time;

	is_busy = true;
}

void Cashier::take_order_from_queue(float enter_time)
{
	if (supply_queue->head == nullptr || is_busy)
	{
		return;
	}
	take_order(supply_queue->dequeue(), enter_time);
}

void Barista::take_order(CoffeeNode* coffee_order,float enter_time)
{
	curr_coffeeP = coffee_order;
	total_busy_time += curr_coffeeP->barista_prepare_time;
	order_finish_time = curr_coffeeP->barista_prepare_time + enter_time;

	is_busy = true;
}
void Barista::take_order_from_queue(float enter_time)
{
	if (supply_queue->head == nullptr || is_busy)
	{
		return;
	}
	take_order(supply_queue->dequeue(), enter_time);
}


