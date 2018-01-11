#include "GraphD.h"



GraphD::GraphD()
{

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
		if (graph[it].data == second)
		{
			existsNodeSecond = true;
		}
		if (!existsNodeSecond)
		{
			node n; 
			n.data = second; 
			graph.push_back(n);
		}

	}

	if (!existsNodeFirst)
	{
		node n; 
		n.data = first; 

		graph.push_back(n); 

		for (int it = 0; it != graph.size(); it++)
		{
			if (graph[it].data == first)
			{
				node n; 
				n.data = second; 
				graph.push_back(n); 
			}
		}
	}

}
