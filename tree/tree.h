#pragma once
#include "queue.h"
#include "structs.h"

struct tree
{
	node* root = nullptr;
};

bool add(tree& t, value v, char* letter);
int find(tree  t, double value);
bool remove(tree& t, double value);
void drop(tree& t);

queue prefix_traverse(tree& t);
queue infix_traverse(tree& t);
queue postfix_traverse(tree& t);
queue wide_traverse(tree& t);