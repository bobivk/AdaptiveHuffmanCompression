#include"Node.h"

	Node::Node()
		: value(-1), weight(0), order(LOWEST_ORDER), left(nullptr), right(nullptr), parent(nullptr)
	{
		--LOWEST_ORDER;
	}

	Node::Node(int _value, int _weight, Node* l, Node* r, Node* p)
		:value(_value), weight(_weight), order(LOWEST_ORDER), left(l), right(r), parent(p)
	{
		--LOWEST_ORDER;
	}

	Node* Node::getSibling() {
		return this->parent->right;
	}
	int Node::getWeightOfSibling() {
		return this->parent->right->weight;
	}
	bool Node::isLeaf() {
		return right == nullptr && left == nullptr;
	}
	bool Node::isInner() {
		return !isLeaf();
	}

int Node::LOWEST_ORDER{ 512 };
/*
void swapNodes(Node* lhs, Node* rhs) {
	std::swap(lhs->value, rhs->value);
	std::swap(lhs->weight, rhs->weight);
	std::swap(lhs->left, rhs->left);
	std::swap(lhs->right, rhs->right);
	//std::swap(lhs->order, rhs->order);
	//order should not be swapped since it is tied to the position in the tree, not the value of the node
}
*/
/*
When swapping, make sure to remember:

The root should never be swapped with anything
Remember that you are moving up the tree so things above are not updated. Therefore, be sure never to swap a node with its parent.
Although the pointers must be swapped in the tree, be sure to reset the order to fit the new arrangement.
The orders of the two swapped nides should not be swapped- or if they are, should be re-swapped. 
Order is not a measure related to the value in a node- it is related to that node's position in the tree.

*/