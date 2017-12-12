#include "BTS.h"


BST::BST() { root = nullptr; };

BST::~BST() {
	//TODO

};

Node*  BST::Search(int key) {
	return Search(root, key);
};


Node * BST::Search(Node* node, int key) {

	// Base Cases: root is null or key is present at root
	if (node == nullptr) { return node; };
	if (node->key == key) { return node; };

	// Key is greater than root's key
	if (node->key < key) { return Search(node->right, key); }

	// Key is smaller than root's key
	return Search(node->left, key);
};

void BST::Insert(int key) {
	return Insert(&root, key);
};

void BST::Insert(Node** node, int key) {
	if (*node == nullptr)
		*node = new Node(key);
	else
	{
		//key is smaller than key in current node
		if (key < (*node)->key)
			Insert(&((*node)->left), key);
		else
		{   //key is greater than key in current node
			if (key >(*node)->key)
				Insert(&((*node)->right), key);
			//key duplicate ignored

		}
	}
}



void BST::PreOrder()
{
	PreOrder(root);
}

void BST::InOrder()
{
	InOrder(root);
}

void BST::PostOrder()
{
	PostOrder(root);
}


void BST::PreOrder(Node *node)
{
	if (node != nullptr)
	{
		std::cout << node->key << " ";
		PreOrder(node->left);
		PreOrder(node->right);
	}
}

void BST::InOrder(Node *node)
{
	if (node != nullptr)
	{
		InOrder(node->left);
		std::cout << node->key << " ";
		InOrder(node->right);

	}
}

void BST::PostOrder(Node *node)
{
	if (node != nullptr)
	{

		PostOrder(node->left);
		PostOrder(node->right);
		std::cout << node->key << " ";

	}
}

bool BST::Exist(int key) {

	return !(Search(key) == nullptr);

};