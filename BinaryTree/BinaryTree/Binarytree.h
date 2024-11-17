#pragma once
#include <iostream>
class BinaryTree
{
public:
	BinaryTree()
	{
		root = 0;
	}
	~BinaryTree()
	{
		if(root != 0) delete root;
	}

	void addInt(int newData);
	void print();
	void searchElement(int Data);
	void deleteelement(int Data);
private:
	struct Node {

		Node(int _data, Node* _parent = 0) :
			leftChild(0),
			rightChild(0),
			parent(_parent),
			data(_data) {}

		~Node() {
			if (leftChild != 0) delete leftChild;
			if (rightChild != 0) delete rightChild;
		}
		Node* leftChild;
		Node* rightChild;
		Node* parent;

		int data;
	};

	Node* root;
};