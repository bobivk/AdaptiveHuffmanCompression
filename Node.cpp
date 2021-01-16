#include"Node.h"


Node::Node(int _value, int _weight, unsigned LOWEST_ORDER, Node* l, Node* r, Node* p)
	:value(_value), weight(_weight), order(LOWEST_ORDER), left(l), right(r), parent(p)
{}

bool Node::isLeaf() {
	return right == nullptr && left == nullptr;
}
bool Node::isInner() {
	return !isLeaf();
}
bool Node::isLeftChild() {
	if (parent != nullptr) {
		return parent->left == this;
	}
	return false;
}