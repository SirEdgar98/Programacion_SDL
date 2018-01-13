#include "GraphD.h"



GraphD::GraphD()
{

}

GraphD::GraphD(std::list <std::pair <int, int>> arcs)
{
	for (std::list<std::pair<int, int>>::iterator it = arcs.begin(); it != arcs.end(); it++)
	{
		insert((*it).first, (*it).second); 
	}
}


GraphD::~GraphD()
{
}

void GraphD::insert(int first, int second)
{
	bool existsNodeFirst = false;
	bool existsNodeSecond = false; 
	bool existsAdyacent = false; 

	for (int it = 0; it != graph.size(); it++)
	{
		if(graph[it].data == first)
		{
			existsNodeFirst = true; 

			for (std::list<node>::iterator itAd = graph[it].Adyacentes.begin(); itAd != graph[it].Adyacentes.end(); itAd++)
			{
				if (itAd->data == second)
				{
					existsAdyacent = true;
				}

			}
			if (!existsAdyacent)
			{
				node n; 
				n.data = second; 
				graph[it].Adyacentes.push_back(n);
			}

		}
		
	}
	

	
	
	if (!existsNodeFirst)
	{
		node n1; 
		n1.data = first; 
		node n2;
		n2.data = second;

		graph.push_back(n1); 

		for (int it = 0; it != graph.size(); it++)
		{
			if (graph[it].data == first)
			{
				node n; 
				n.data = second; 
				graph[it].Adyacentes.push_back(n); 
			}
		}
		for (int it = 0; it < graph.size(); it++)
		{
			if (graph[it].data == n2.data)
				existsNodeSecond = true; 
		}
		if (!existsNodeSecond)
			graph.push_back(n2); 
	}

	for (int it = 0; it < graph.size(); it++)
	{
		if (graph[it].data == second)
		{
			existsNodeSecond = true;
		}

	}
		if (!existsNodeSecond)
		{
			node n;
			n.data = second;
			graph.push_back(n);
		}
}
