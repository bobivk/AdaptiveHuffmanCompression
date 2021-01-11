#pragma once
#include <string>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "Node.h"

/*
key verbs:

insert new value,
give birth to new nodes,
update weight,
check if max in weight class,
swap,
isRoot,
move to parent
*/
const int PSEUDO_EOF = 256;

struct HuffmanTree
{
	Node* root;
	Node* NYTNode;
	std::vector<Node*> leaves;//leaves indexed by char value
	std::vector<Node*> nodes; //all nodes indexed by order - 256 leaves + 255 internal nodes
	
	HuffmanTree();
	void createNewNode(int symbol);
	bool firstReadOf(int symbol);
	void insertSymbol(int symbol);
	int findOrderOfBlockLeader(int orderOfCurrent);
	void setParent(Node* node, Node* newParent);
	void updateTree(int fromOrder);
	void swapNodes(Node*, Node*);
	std::vector<bool> getPathToNode(Node*);
};

