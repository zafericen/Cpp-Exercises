#pragma once
#include "CoffeeNode.h"
#include <iostream>
class CoffeeQueue
{
public:
	//queue attributes
	CoffeeNode* head{ nullptr };
	CoffeeNode* tail{ nullptr };
	int size = 0;
	int max_size = 0;
	//base queue enqueue method
	virtual void enqueue(CoffeeNode* new_node);
	//dequeue for every class
	CoffeeNode* dequeue();
};

class BaristaCoffeeQueue: public CoffeeQueue
{
public:
	//priority queue based on price
	void enqueue(CoffeeNode* new_node) override;
};

class TimePriorityCoffeeQueue : public CoffeeQueue 
{
public:
	//priority queue based on enter time
	void enqueue(CoffeeNode* new_node) override;
};