#include "back_functions.h"
#include "front_functions.h"
 
Graph g;

int main()
{
	mainPrint();
	int c;
	while (cin >> c)
	{
		system("cls");
		if (c == 1)	frontFunc();
		else if (c == 2) backFunc();
		else break;
		mainPrint();
	}
	return 0;
}
