#include "CoffeeQueue.h"

void CoffeeQueue::enqueue(CoffeeNode* new_node)
{
	new_node->nextP = NULL;

	if (head == NULL && tail == NULL)
	{
		head = tail = new_node;
		size += 1;
		if (max_size < size)
		{
			max_size += 1;
		}
		return;
	}
	tail->nextP = new_node;
	tail = new_node;
	size += 1;
	if (max_size < size)
	{
		max_size += 1;
	}
	
}

CoffeeNode* CoffeeQueue::dequeue()
{
	CoffeeNode* remove_node = head;
	if (head == NULL)
	{
		return nullptr;
	}
	if (head == tail)
	{
		head = tail = NULL;
		size = 0;
	}
	else
	{
		head = head->nextP;
		size -= 1;
	}
	return remove_node;
}

void BaristaCoffeeQueue::enqueue(CoffeeNode* new_node)
{
	if (head == NULL && tail == NULL)
	{
		head = tail = new_node;
		size += 1;
		if (max_size < size)
		{
			max_size += 1;
		}
		return;
	}
	if (head->price < new_node->price)
	{
		new_node->nextP = head;
		head = new_node;
	}
	else if (tail->price > new_node->price)
	{
		tail->nextP = new_node;
		tail = new_node;
	}
	else
	{
		CoffeeNode* curr = head;
		while (curr->nextP != NULL && curr->nextP->price > new_node->price)
		{
			curr = curr->nextP;
		}
		new_node->nextP = curr->nextP;
		curr->nextP = new_node;
	}
	size += 1;
	if (max_size < size)
	{
		max_size += 1;
	}
}

void TimePriorityCoffeeQueue::enqueue(CoffeeNode* new_node)
{
	if (head == NULL && tail == NULL)
	{
		head = tail = new_node;
		size += 1;
		if (max_size < size)
		{
			max_size += 1;
		}
		return;
	}
	if (head->enter_time > new_node->enter_time)
	{
		new_node->nextP = head;
		head = new_node;
	}
	else if (tail->enter_time < new_node->enter_time)
	{
		tail->nextP = new_node;
		tail = new_node;
	}
	else
	{
		CoffeeNode* curr = head;
		while (curr->nextP != NULL && curr->nextP->enter_time < new_node->enter_time)
		{
			curr = curr->nextP;
		}
		new_node->nextP = curr->nextP;
		curr->nextP = new_node;
	}
	size += 1;
	if (max_size < size)
	{
		max_size += 1;
	}
}