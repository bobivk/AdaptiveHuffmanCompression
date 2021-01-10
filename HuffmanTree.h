#pragma once
#include"Node.h"


struct HuffmanTree
{
	Node* root;
	Node* NYTNode;
	Node* leaves[256]{ nullptr };//leaves indexed by char value
	Node* nodes[512]{ nullptr }; //all nodes indexed by order - 256 leaves + 255 internal nodes
	
	HuffmanTree();
	~HuffmanTree();
	void createNewNode(int symbol);
	bool firstReadOf(int symbol);
	void insertSymbol(int symbol);
	void updateTree(Node* from);
	void swapNodes(Node*, Node*);
};

