#include "HuffmanTree.h"


HuffmanTree::HuffmanTree() {
	NYTNode = root;
}
HuffmanTree::~HuffmanTree() {
	delete[] nodes;
}

void HuffmanTree::updateTree(int fromOrder) {

}

//Creates new NYT on the left of old NYT
//and creates a new leaf node of symbol
//on the right. Old NYT becomes internal node.
void HuffmanTree::createNewNode(int symbol) {

	//creates nyt node last so correct ordering is maintained
	Node* newLeaf = new Node(symbol, 1, nullptr, nullptr, NYTNode);
	nodes[newLeaf->order] = newLeaf;
	Node* newNYT = new Node(-1, 0, nullptr, nullptr, NYTNode);
	nodes[newNYT->order] = newNYT;
	NYTNode->right = newLeaf;
	NYTNode->left = newNYT;
	NYTNode = newNYT;
	leaves[symbol] = newLeaf;
}

bool HuffmanTree::firstReadOf(int symbol) {
	return leaves[symbol] == nullptr;
}
void HuffmanTree::insertSymbol(int symbol) {
	if (firstReadOf(symbol)) {
		createNewNode(symbol);
	}
	else {
		++leaves[symbol]->weight;
	}
	updateTree(leaves[symbol]->order);
}

void HuffmanTree::swapNodes(Node* lhs, Node* rhs) {
	std::swap(lhs->value, rhs->value);
	std::swap(lhs->weight, rhs->weight);
	std::swap(lhs->left, rhs->left);
	std::swap(lhs->right, rhs->right);
	std::swap(lhs->order, rhs->order);
	//std::swap(nodes[lhs->order], nodes[rhs->order]);
	
	/*
	Although the pointers must be swapped in the tree, be sure to reset the order to fit the new arrangement.
	The orders of the two swapped nodes should not be swapped- or if they are, should be re-swapped.
	Order is not a measure related to the value in a node- it is related to that node's position in the tree.*/
}