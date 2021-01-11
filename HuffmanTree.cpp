#include "HuffmanTree.h"


HuffmanTree::HuffmanTree() {
	root = new Node(-1, 0, nullptr, nullptr, nullptr);
	NYTNode = root;
	nodes = std::vector<Node*>(513, nullptr);
	leaves = std::vector<Node*>(257, nullptr);
	nodes[512] = root;
}
// [  , , 1, 1, 1, 2, 2, 3, 4]
//       506    508 509 510 511 512 

int HuffmanTree::findOrderOfBlockLeader(int orderOfCurrent) {
	for (int i = orderOfCurrent + 1; i < 511; ++i) {

		if (nodes[i]->weight < nodes[i + 1]->weight //block leader
			&& nodes[i]->weight == nodes[orderOfCurrent]->weight) {// block lead is in the same block
			
			return i;
		}
		if (nodes[i]->weight > nodes[orderOfCurrent]->weight) return orderOfCurrent;
	}
	return orderOfCurrent;
}
/*
void HuffmanTree::updateTree(int fromOrder) {
	if (fromOrder == 512) {
		++root->weight;
		return;
	}
	int orderOfBlockLeader = findOrderOfBlockLeader(fromOrder);
	std::cout << "Increment weight of " << fromOrder << std::endl;
	if (orderOfBlockLeader != fromOrder) {
		std::cout << "swapping " << fromOrder << " with  " << orderOfBlockLeader << std::endl;
		swapNodes(nodes[fromOrder], nodes[orderOfBlockLeader]);
	}
	//after swapping our current node's order is 'orderOfBlockLeader'
	++nodes[fromOrder]->weight;
	updateTree(nodes[orderOfBlockLeader]->parent->order);
}

procedure Update;
begin
leaf ToIncrement := 0;
q := leaf node corresponding to ai,,, ;
if (q is the O-node) and (k < n - 1) then
begin 1 Special Case # 1)
Replace q by an internal O-node with two leaf O-node children, such that the right child
corresponds to at,,, ;
q := internal O-node just created;
leaf ToIncrement := the right child of q
end
else begin
Interchange q in the tree with the leader of its block;
if q is the sibling of the O-node then
begin {Special Case #2)
leaf ToIncrement := q;
q := parent of q
end
end;


while q is not the root of the Huffman tree do
(Main loop; q must he the leader of its block]
SlideAndZncrement(q);
if leaf Tolncrement # 0 then (Handle the two special cases)
SlideAndIncrement(leaf ToIncrement)
end;
procedure SlideAndIncrement(p);
begin
wt := weight of p;
b := block following p�s block in the linked list;
if ((p is a leaf) and (b is the block of internal nodes of weight wt))
or ((p is an internal node) and
(b is the block of leaves of weight wt + 1)) then
begin
Slide p in the tree ahead of the nodes in b;
p�s weight := wt + 1;
if p is a leaf then p := new parent of p
else p := former parent of p
end
end:


*/

void HuffmanTree::updateTree(int fromOrder) {
	if (fromOrder == 512) {
		++root->weight;
		return;
	}
	int blockLeaderOrder = findOrderOfBlockLeader(fromOrder);
	if (blockLeaderOrder == fromOrder) {
		++nodes[fromOrder]->weight;
	}
	else {
		std::cout << "Swapping nodes " << fromOrder << " " << blockLeaderOrder << "\n";
		swapNodes(nodes[fromOrder], nodes[blockLeaderOrder]);
	}
}


//Creates new NYT on the left of old NYT
//and creates a new leaf node of symbol
//on the right. Old NYT becomes internal node.
void HuffmanTree::createNewNode(int symbol) {

	//creates the NYT node last so correct ordering is maintained
	Node* newLeaf = new Node(symbol, 0, nullptr, nullptr, NYTNode);
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