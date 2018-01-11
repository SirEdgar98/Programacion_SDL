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
	//Metodos
	GraphD(); // Vector de arcos
	~GraphD();

	//Insertar un arco
	void insert(int first, int second); 
	//Eliminar un arco
	void erase(int first, int second); 
	//Indice de un nodo
	int NodeIndex(node *Node); 
	//Camino entre un nodo y otro
	bool paht(node *start, node *end); 
	//Circuito a partir de un nodo	
	bool circuit(node *start, node *end);
	//Euleriano?
	bool EulerGraph(GraphD *graph);
	//Imprimir los arcos
	void printArcs(); 
};

