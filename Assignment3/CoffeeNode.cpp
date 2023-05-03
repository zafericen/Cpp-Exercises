#include "CoffeeNode.h"

CoffeeNode::CoffeeNode(float enter_time, float order_time, float prepare_time, float price):
	enter_time(enter_time),cashier_order_time(order_time),barista_prepare_time(prepare_time),price(price)
{
}

float CoffeeNode::turnaround_times()
{
	return coffee_finished_time - enter_time ;
}
