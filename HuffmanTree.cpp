#include "HuffmanTree.h"


HuffmanTree::HuffmanTree() {
	root = new Node(-1, 0, nullptr, nullptr, nullptr);
	NYTNode = root;
}
HuffmanTree::~HuffmanTree() {
	delete[] nodes;
}


int HuffmanTree::findOrderOfBlockLeader(int orderOfCurrent) {
	for (int i = orderOfCurrent; i < 511; ++i) {
		if (nodes[i]->weight > nodes[orderOfCurrent]->weight) return orderOfCurrent;
		if (nodes[i]->weight < nodes[i + 1]->weight && nodes[i]->weight == nodes[orderOfCurrent]->weight) {
			if (nodes[orderOfCurrent]->parent == nodes[i] || nodes[orderOfCurrent] == root) {
				return orderOfCurrent;
			}
			else return i;
		}
	}
	return orderOfCurrent;
}

void HuffmanTree::updateTree(int fromOrder) {
	if (fromOrder == 512) return; //root
	int orderOfBlockLeader = findOrderOfBlockLeader(fromOrder);
	++nodes[fromOrder]->weight;
	if (orderOfBlockLeader != fromOrder) {
		swapNodes(nodes[fromOrder], nodes[orderOfBlockLeader]);
		//after swapping our current node's order is 'orderOfBlockLeader'
		updateTree(nodes[orderOfBlockLeader]->parent->order);
	}
}

//Creates new NYT on the left of old NYT
//and creates a new leaf node of symbol
//on the right. Old NYT becomes internal node.
void HuffmanTree::createNewNode(int symbol) {

	//creates the NYT node last so correct ordering is maintained
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
void HuffmanTree::setParent(Node* node, Node* newParent) {
	if (node == nullptr) return;
	node->parent = newParent;
}

void HuffmanTree::swapNodes(Node* lhs, Node* rhs) {
	if (lhs == root || rhs == root) return; //we can not swap with root
	if (lhs->parent == rhs || rhs->parent == lhs) return; //we can not swap with parent
	//swap pointers of parents first
	if (lhs->parent->left == lhs) {
		lhs->parent->left = rhs;
	}
	else {
		lhs->parent->right = rhs;
	}
	if (rhs->parent->left == lhs) {
		rhs->parent->left = lhs;
	}
	else {
		rhs->parent->right = lhs;
	}
	//swap pointers of children
	setParent(lhs->left, rhs);
	setParent(lhs->right, rhs);
	setParent(rhs->left, lhs);
	setParent(rhs->right, lhs);

	//swap all values
	std::swap(lhs->value, rhs->value);
	std::swap(lhs->weight, rhs->weight);
	std::swap(lhs->left, rhs->left);
	std::swap(lhs->right, rhs->right);
	std::swap(lhs->parent, rhs->parent);
	//we do not need to swap them in the 'nodes' or 'leaves' arrays as we already swapped everything about the nodes
	//std::swap(nodes[lhs->order], nodes[rhs->order]);
	
	/*
	"Although the pointers must be swapped in the tree, be sure to reset the order to fit the new arrangement.
	The orders of the two swapped nodes should not be swapped- or if they are, should be re-swapped.
	Order is not a measure related to the value in a node- it is related to that node's position in the tree."
	*/
}
void reversePath(std::vector<bool>& path) {
	int n = path.size();
	for (int i = 0; i < n / 2; i++) {
		bool temp = path[i];
		path[i] = path[n - i - 1];
		path[n - i - 1] = temp;
	}
}

std::vector<bool> HuffmanTree::getPathToNode(Node* node) {
	std::vector<bool> result;
	while (node != root) {
		if (node->isLeftChild()) {
			result.push_back(0);
		}
		else result.push_back(1);
		node = node->parent;
	}
	reversePath(result);
	return result;
}