#pragma once
struct value
{
	double x;
	char* surname;
};

struct node
{
	value v;
	int height = 1;
	node* left = nullptr;
	node* right = nullptr;
};