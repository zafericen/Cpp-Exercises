#pragma once
#include <cstddef>
class CoffeeNode
{
public:
	//coffee order's attributes
	float enter_time;
	float cashier_order_time;
	float barista_prepare_time;
	float price;
	float coffee_finished_time{ 0.0f };
	//next node pointer
	CoffeeNode* nextP{ nullptr };
	//default constructor
	CoffeeNode(float enter_time, float order_time, float prepare_time,float price);
	//returns turnaround time of orders
	float turnaround_times();
};

