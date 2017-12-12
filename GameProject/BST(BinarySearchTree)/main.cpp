#include "BTS.h"

int main()
{
	BST *BinaryTree = new BST; 

	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);
	BinaryTree->Insert(rand() % 100);


	//BinaryTree->PostOrder();
	std::cout << std::endl; 
	BinaryTree->PreOrder();
	std::cout << std::endl; 
	//BinaryTree->InOrder();
	std::cout << std::endl;
	

}