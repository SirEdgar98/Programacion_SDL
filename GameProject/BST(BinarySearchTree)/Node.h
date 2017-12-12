#pragma once

class Node {

public:
	int key;
	Node *left;
	Node *right;
	Node() :key(-1), left(nullptr), right(nullptr) {};
	Node(int akey) :key(akey), left(nullptr), right(nullptr) {};
};