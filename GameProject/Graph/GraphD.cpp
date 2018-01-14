#include "GraphD.h"



GraphD::GraphD()
{

}

GraphD::GraphD(std::list <std::pair <int, int>> arcs)
{
	for (std::list<std::pair<int, int>>::iterator it = arcs.begin(); it != arcs.end(); it++)
	{
		insert(it->first, it->second); 
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


void GraphD::erase(int first, int second)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i].data == first)
		{
			for (std::list<node>::iterator itAd = graph[i].Adyacentes.begin(); itAd != graph[i].Adyacentes.end(); ++itAd)
			{
				if (itAd->data == second)
				{
					graph[i].Adyacentes.erase(itAd); 
					break; 
				}
			}
		}
	}
}

int GraphD::NodeIndex(int node)
{
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[i].data == node)
		{
			return graph[i].Adyacentes.size(); 
			break; 
		}
	}
}


bool GraphD::path(int nodeStart, int nodeEnd)
{
	std::vector<node>tmpGraph(graph); 

	for (int i = 0; i < tmpGraph.size(); i++)
	{
		if (tmpGraph[i].data == nodeStart)
		{
			for (std::list<node>::iterator itAd = tmpGraph[i].Adyacentes.begin(); itAd != tmpGraph[i].Adyacentes.end(); itAd++)
			{
				if (itAd->data == nodeEnd) return true; 
				else path(itAd->data, nodeEnd); 
			}
		}
	}
	return false; 
}

bool GraphD::EulerGraph()
{
	int OddIndexNode = 0; 
	for (int i = 0; i < graph.size(); i++)
	{
		if (NodeIndex(graph[i].data) % 2 != 0)
		{
			OddIndexNode++; 
		}
		if (OddIndexNode >= 2) return true; 
	}

	return false; 
}