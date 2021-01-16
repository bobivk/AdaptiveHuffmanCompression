#include "HuffmanTree.h"

unsigned HuffmanTree::LOWEST_NODE_ORDER{ 512 };

void printBT1(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "L " : "R ");

		// print the value of the node
		std::cout << node->order << "," << char(node->value) << "," << node->weight << std::endl;

		// enter the next tree level - left and right branch
		printBT1(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBT1(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}
void printBT1(const Node* node)
{
	printBT1("", node, false);
	std::cout << std::endl << std::endl;
}

HuffmanTree::HuffmanTree() {
	root = new Node(-1, 0, LOWEST_NODE_ORDER, nullptr, nullptr, nullptr);
	--LOWEST_NODE_ORDER;
	NYTNode = root;
	nodes = std::vector<Node*>(513, nullptr);
	leaves = std::vector<Node*>(257, nullptr);
	nodes[512] = root;
}
// [  , , 1, 1, 1, 2, 2, 3, 4]
//       506    508 509 510 511 512 

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
void printLeaves(HuffmanTree* tree) {
	for (auto i : tree->leaves) {
		if(i != nullptr)
			std::cout << i->value << " ";
	}
	std::cout << std::endl;
}

void HuffmanTree::updateTree(int symbol) {
	std::cout << "Updating for " << symbol << "\n";
	Node* current{ nullptr };
	if (firstReadOf(symbol)) {
		createNewNode(symbol);
		current = NYTNode->parent; //go to old NYT node
	}
	else {
		current = leaves[symbol];//go to symbol external node
		setAsBlockLeader(current);
		++current->weight;
	}
	while (current != root) {//Is this root node
		current = current->parent; //go to parent
		setAsBlockLeader(current);
		std::cout << "Incrementing weight of " << current->order << std::endl;
		++current->weight;
	}
	printBT1(root);
	printLeaves(this);
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
	std::cout << "create leaf " << newLeaf->order;
	Node* newNYT = new Node(-1, 0, LOWEST_NODE_ORDER, nullptr, nullptr, NYTNode);
	--LOWEST_NODE_ORDER;
	nodes[newNYT->order] = newNYT;
	std::cout << "create NYT " << newNYT->order << '\n';
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

	//update leaves vector
	if (left->isLeaf()) leaves[left->value] = right;
	if (right->isLeaf()) leaves[right->value] = left;
//swap pointers of parents first
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
	//swap pointers of children
	setParent(left->left, right);
	setParent(left->right, right);
	setParent(right->left, left);
	setParent(right->right, left);

	//swap all values
	std::swap(left->value, right->value);
	std::swap(left->weight, right->weight);
	std::swap(left->left, right->left);
	std::swap(left->right, right->right);
	std::swap(left->parent, right->parent);
	

	
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


/*
void HuffmanTree::insertSymbol(int symbol) {
	if (firstReadOf(symbol)) {
		createNewNode(symbol);
	}
	updateTree(leaves[symbol]->order);
}
*/
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

n = alphabet size,
k = number of distinct letters in file

procedure Update;
begin
	leaf ToIncrement := 0;
	q := leaf node corresponding to x ;
	if (q is the O-node) and (k < n - 1) then
		begin (Special Case # 1)
		Replace q by an internal NYT with two children, such that the right child corresponds to x;
		q := internal NYT just created;
		leafToIncrement := the right child of q
	end
	else begin
		Interchange q in the tree with the leader of its block;
		if q is the sibling of the O-node then
		begin (Special Case #2)
			leaf ToIncrement := q;
			q := parent of q
		end
	end;


	while q is not the root of the Huffman tree
		do
		(Main loop; q must be the leader of its block)
			SlideAndZncrement(q);
			if leaf Tolncrement # 0 then (Handle the two special cases)
				SlideAndIncrement(leaf ToIncrement)

		end;


procedure SlideAndIncrement(p);
begin
	wt := weight of p;
	b := block following p’s block in the linked list;
	if ((p is a leaf) and (b is the block of internal nodes of weight wt))
		or ((p is an internal node) and
			(b is the block of leaves of weight wt + 1)) then
	begin
		Slide p in the tree ahead of the nodes in b;
		p’s weight := wt + 1;
		if p is a leaf then p := new parent of p
		else p := former parent of p
	end;
end;


*/
