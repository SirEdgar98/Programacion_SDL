#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

class GraphD
{
public:
	//Atributos
	//Nodo
	struct node
	{
		int data; //Datos guardados en el nodo
		std::list<node> Adyacentes; // Lista de nodos adyacentes
	}; 
	
	//Vector Arcos

	std::vector<node> graph; 
	std::vector<node> UsedNodes; 
	//Metodos
	GraphD(); // Constructor vacio 
	GraphD(std::list <std::pair <int,int>> arcs); // Vector de pares de nodos
	~GraphD();

	//Insertar un arco
	void insert(int first, int second); 
	//Eliminar un arco
	void erase(int first, int second); 
	//Indice de un nodo
	int NodeIndex(int node); 
	//Camino entre un nodo y otro
	bool path(int NodeStart, int NodeEnd); 
	//Circuito a partir de un nodo	
	bool circuit(node start, node end);
	//Euleriano?
	bool EulerGraph();
	//Imprimir los arcos
	void printArcs(); 
};

