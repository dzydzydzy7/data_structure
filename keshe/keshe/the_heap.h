#pragma once
#include <iostream>
using namespace std;
#define SETCAPA 30
#define MAXEDGE 30


struct Edge
{
	int head;
	int tail;
	int weight;
};

int vexSet[SETCAPA];

class Heap
{
private:
	struct Edge edges[MAXEDGE];
	int size;
public:
	Heap();
	{
		szie = 
	}
};
