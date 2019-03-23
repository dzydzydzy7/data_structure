#pragma once
#include <iostream>
using namespace std;
#define CAPACITY 30

class Stack
{
public:
	int elem[CAPACITY];
	int top;
	Stack() { top = 0; }
	void push(int p) { elem[top++] = p; }
	int pop() { return elem[--top]; }
	bool notEmpty() { return top; }
};

int *buildNext(string P);

int kmp(string P, string T);