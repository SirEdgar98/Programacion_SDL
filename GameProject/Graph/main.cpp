#include "GraphD.h"
#include <iostream>


int main()
{

	std::list <std::pair <int, int>> arcs = { {8,9}, {8,10} ,{10,11}, {8,11} };
	GraphD g;
	GraphD g2(arcs);

	g.insert(1, 2);
	g.insert(1, 3);
	g.insert(1, 4); 
	g.insert(2, 5);
	g.insert(2, 4);
	g.insert(3, 5);
	g.insert(4, 6);

	g2.insert(11, 9); 

	std::cout << "Bieeen" << std::endl; 
	

	

	return 0;
}