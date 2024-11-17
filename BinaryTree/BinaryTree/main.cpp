#include <iostream>
#include "Binarytree.h"

using namespace std;

int main()
{
	BinaryTree btree;
	btree.addInt(5);
	btree.addInt(4);
	btree.addInt(-17);
	btree.addInt(3);
	btree.addInt(20);
	btree.addInt(43);
	btree.addInt(13);
	btree.addInt(11);
	btree.addInt(18);
	btree.addInt(15);
	btree.addInt(19);
	btree.addInt(49);

	btree.deleteelement(-17);
	//btree.deleteelement(43);
	//btree.deleteelement(20);

	btree.print();
	return 0;
}
