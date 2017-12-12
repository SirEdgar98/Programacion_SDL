#pragma once
#include "Node.h"
#include <iostream>
class BST
{
public:

	BST();
	~BST();
	Node* Search(int key);
	void Insert(int key);
	void PreOrder();
	void InOrder();
	void PostOrder();
	bool Exist(int key);

private:
	Node *root;
	Node* Search(Node* node, int key);
	void Insert(Node** node, int key);
	void PreOrder(Node *node);
	void InOrder(Node *node);
	void PostOrder(Node *node);


};
