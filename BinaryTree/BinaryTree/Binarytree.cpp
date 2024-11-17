#include "Binarytree.h"
void BinaryTree:: addInt(int newData)
{
	if (root == 0)
	{
		root = new Node(newData);
	}
	else
	{
		Node* current = root;
		Node* newNode = 0;
		while (newNode == 0)
		{
			if (current->data >= newData)
			{
				if (current->leftChild != 0)
				{
					current = current->leftChild;
					continue;
				}
				newNode = new Node(newData, current);
				current->leftChild = newNode;
			}
			else
			{
				if (current->rightChild != 0)
				{
					current = current->rightChild;
					continue;
				}
				newNode = new Node (newData, current);
				current->rightChild = newNode;
			}
		}
	}
}

void BinaryTree::print()
{
	Node* queue[100];
	int queueCounter = 0;

	queue[queueCounter++] = root;

	while (queueCounter != 0) {
		Node* current = queue[0];
		//удалить
		queueCounter--;
		for (int i = 0; i < queueCounter; i++)
		{
			queue[i] = queue[i + 1];
		}
		if (current->parent)
			std::cout << current->parent->data;
		std::cout << " " << current->data << std::endl;
		if (current->leftChild)
			queue[queueCounter++] = current->leftChild;
		if (current->rightChild)
			queue[queueCounter++] = current->rightChild;
	}
}

void BinaryTree::searchElement(int Data)
{
}

void BinaryTree::deleteelement(int Data)
{
	Node* current = root;
	while (current->data != Data)
	{
		if (current->data >= Data)
		{
			if (current->leftChild != 0)
			{
				current = current->leftChild;
				continue;
			}
		}
		else
		{
			if (current->rightChild != 0)
			{
				current = current->rightChild;
				
				continue;
			}
		}
	}
	Node* nodeToDelete = current;
	if (!current->rightChild)
	{
		current->leftChild->parent = current->parent;
		current->parent->leftChild = current->leftChild;
	}
	else
	{
		current->parent = current->rightChild;
		current->rightChild->parent = current->parent;
	}
	//if ((current->leftChild && !current->rightChild) || (current->rightChild && !current->leftChild))
	//{
	//	if (current->leftChild)
	//	{
	//		current ->parent = current->leftChild -> parent;
	//		current->leftChild->parent = current->parent;
	//	}
	//	else
	//	{
	//		current -> parent = current->rightChil;
	//		current->rightChild->parent = current->parent;
	//	}

	//}
	//else
	//{
	//	//current = current->leftChild;
	//	//while (current->rightChild)
	//	//{
	//	//	current = current->rightChild;
	//	//}
	//	//current->parent->rightChild = 0;

	//	//current->parent = nodeToDelete->parent;


	//}
}


