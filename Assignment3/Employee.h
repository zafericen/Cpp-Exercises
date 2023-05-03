#pragma once
#include "CoffeeQueue.h"

class Employee
{
public:
	//employee attirubets
	float order_finish_time = 0.0f;
	float total_busy_time = 0;
	bool is_busy = false;
	//current coffee order that employee is working
	CoffeeNode* curr_coffeeP{nullptr};
	//queues that emlployee takes and passes orders
	CoffeeQueue* supply_queue{ nullptr };
	CoffeeQueue* pass_queue{ nullptr };
	//virtual methods for base employee class
	virtual void take_order(CoffeeNode* coffee_order,float enter_time) = 0;
	virtual void take_order_from_queue(float enter_time) = 0;
	//base methods for every employee
	CoffeeNode* pass_order();
	void pass_order_to_queue();
	float utilization(float global_time);
};

class Cashier :public Employee
{
public:
	//cashier's methods of employee 
	void take_order(CoffeeNode* coffee_order, float enter_time) override;
	void take_order_from_queue(float enter_time);
};

class Barista : public Employee
{
public:
	//barista's methods of employee
	void take_order(CoffeeNode* coffee_order, float enter_time) override;
	void take_order_from_queue(float enter_time);
};


