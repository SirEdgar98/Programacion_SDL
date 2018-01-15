#include "BTS.h"


BST::BST() { root = nullptr; };

BST::~BST()
{
	destructor(root); 
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

int BST::Height()
{
	return Height(root);
}

int BST::GetNumberNodesR()
{
	return getNumberNodesRecursive(root); 
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

int BST::Height(Node *node)
{
	int alturaLeft = 0; 
	int alturaRight = 0; 

	if (node != nullptr)
	{
			alturaLeft = Height(node->left) + 1; 
			alturaRight = Height(node->right) + 1 ;
	}

	if (alturaLeft >= alturaRight) return alturaLeft; 
	if (alturaRight >= alturaLeft) return alturaRight;
}


int BST::getNumberNodesRecursive(Node *node)
{

	if (node == nullptr) return 0; 

	int totalNodes = 0; 

	if (node->left != nullptr)
	{
		totalNodes = getNumberNodesRecursive(node->left);
		totalNodes++; 
	}
	if (node->right != nullptr)
	{
		totalNodes = getNumberNodesRecursive(node->right); 
		totalNodes++;
	}

	return totalNodes; 
}
//int BST::getNumberNodes(Node *node)
//{
//	
//}

void BST::destructor(Node *node)
{
	if (node->left != nullptr)
	{
		destructor(node->left);
		node->left = nullptr;
	}
	if (node->right != nullptr)
	{
		destructor(node->right);
		node->right = nullptr;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		delete[] node;
		node = nullptr;
	};
}
bool BST::Exist(int key) {

	return !(Search(key) == nullptr);

}
