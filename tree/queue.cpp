#include "queue.h"

void enqueue(queue& q, node* employee)
{
	auto* new_elem = new queue_elem;
	new_elem->tree_node = employee;
	new_elem->prev = q.last;
	if (q.last) q.last->next = new_elem;
	q.last = new_elem;
	if (!q.first) q.first = new_elem;
}
bool dequeue(queue& q, node*& node)
{
	if (!q.first) return false;
	node = q.first->tree_node;
	auto* old_elem = q.first;
	q.first = q.first->next;
	delete old_elem;
	if (q.first) q.first->prev = nullptr;
	else q.last = nullptr;
	return true;
}
void clear(queue& q)
{
	auto* curr = q.first;
	while (curr)
	{
		auto* old_elem = curr;
		curr = curr->next;
		delete old_elem;
	}
}