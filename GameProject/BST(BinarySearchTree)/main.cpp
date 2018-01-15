#include "BTS.h"

int main()
{
	BST *BinaryTree = new BST; 

	BinaryTree->Insert(10);
	BinaryTree->Insert(9);
	BinaryTree->Insert(8);
	BinaryTree->Insert(7);
	BinaryTree->Insert(6);
	BinaryTree->Insert(5);
	BinaryTree->Insert(4);
	BinaryTree->Insert(3);
	BinaryTree->Insert(2);
	BinaryTree->Insert(1);
	BinaryTree->Insert(0);


	


	//BinaryTree->PostOrder();
	std::cout << std::endl; 
	BinaryTree->PreOrder();
	std::cout << std::endl; 

	
	std::cout << BinaryTree->Height() << std::endl;
	BinaryTree->~BST(); 
	//BinaryTree->InOrder();
	std::cout << std::endl;
	

}