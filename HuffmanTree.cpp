#include "HuffmanTree.h"

void printBTt(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "L " : "R ");

		// print the value of the node
		std::cout << node->order << "," << char(node->value) << "," << node->weight << std::endl;

		// enter the next tree level - left and right branch
		printBTt(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBTt(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}
void printBTt(const Node* node)
{
	printBTt("", node, false);
	std::cout << std::endl << std::endl;
}

unsigned HuffmanTree::LOWEST_NODE_ORDER{ 512 };

HuffmanTree::HuffmanTree() {
	root = new Node(-1, 0, LOWEST_NODE_ORDER, nullptr, nullptr, nullptr);
	--LOWEST_NODE_ORDER;
	NYTNode = root;
	nodes = std::vector<Node*>(513, nullptr);
	leaves = std::vector<Node*>(257, nullptr);
	nodes[512] = root;
}

int HuffmanTree::findOrderOfBlockLeader(int orderOfCurrent) {
	
	for (int i = orderOfCurrent + 1; i < 512; ++i) {
		if (nodes[i]->weight == nodes[orderOfCurrent]->weight) {
			orderOfCurrent = i;
		}
	}
	return orderOfCurrent;

}

void HuffmanTree::setAsBlockLeader(Node* node) {
	int orderOfBlockLeader = findOrderOfBlockLeader(node->order);
	//if not, swap with highest ordered node in block
	if (orderOfBlockLeader != node->order) {
		swapNodes(nodes[node->order], nodes[orderOfBlockLeader]);
	}
}


void HuffmanTree::updateTree(int symbol) {
	using namespace std;
	//cout << "update for " << char(symbol) << endl;
	Node* current{ nullptr };
	if (firstReadOf(symbol)) {
		createNewNode(symbol);
		current = NYTNode->parent; //go to old NYT node
	}
	else {
		current = leaves[symbol];//go to symbol external node
		setAsBlockLeader(current);
		//cout << "incrementing " << current->order << endl;
		++current->weight;
	}
	while (current != root) {
		current = current->parent; 
		//cout << "go to parent "<< current->order << endl;
		setAsBlockLeader(current);
		//cout << "increment " << current->order << endl;
		++current->weight;
	}
	//printBTt(root);

}

//Creates new NYT on the left of old NYT
//and creates a new leaf node of symbol
//on the right. Old NYT becomes internal node.
void HuffmanTree::createNewNode(int symbol) {
	NYTNode->weight++;
	//creates the NYT node last so correct ordering is maintained
	Node* newLeaf = new Node(symbol, 1, LOWEST_NODE_ORDER, nullptr, nullptr, NYTNode);
	--LOWEST_NODE_ORDER;
	nodes[newLeaf->order] = newLeaf;
	Node* newNYT = new Node(-1, 0, LOWEST_NODE_ORDER, nullptr, nullptr, NYTNode);
	--LOWEST_NODE_ORDER;
	nodes[newNYT->order] = newNYT;
	NYTNode->right = newLeaf;
	NYTNode->left = newNYT;
	NYTNode = newNYT;
	leaves[symbol] = newLeaf;
}

bool HuffmanTree::firstReadOf(int symbol) {
	return leaves[symbol] == nullptr;
}

void HuffmanTree::setParent(Node* node, Node* newParent) {
	if (node == nullptr) return;
	node->parent = newParent;
}

void HuffmanTree::swapNodes(Node* left, Node* right) {

	if (left == nullptr || right == nullptr) return;
	if (left == root || right == root) return; //we can not swap with root
	if (left->parent == right || right->parent == left) return; //we can not swap with parent
	//std::cout << "swapping " << left->order << " with " << right->order << std::endl;

	nodes[left->order] = right;
	nodes[right->order] = left;

	if (left->parent == right->parent) {
		left->parent->right = left;
		left->parent->left = right;
	}
	else {
		if (left->parent->left == left) {
			left->parent->left = right;
		}
		else {
			left->parent->right = right;
		}
		if (right->parent->left == right) {
			right->parent->left = left;
		}
		else {
			right->parent->right = left;
		}
		std::swap(left->parent, right->parent);
	}
	std::swap(left->order, right->order);
	
	//we do not need to swap the weight since nodes are of equal weight
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
	//we get path to root and then reverse it
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

