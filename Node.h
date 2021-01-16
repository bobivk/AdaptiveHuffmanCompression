#pragma once
#include<utility> //std::swap
#include<iostream>
/*
Tree must have the following invariants:
-Each node has a sibling
-Node's with higher weights have higher orders
-On each level, the node farthest to the right will have the highest order although there might be other nodes with equal weight
-Leaf nodes contain character values, except the Not Yet Transmitted(NYT) node which is the node whereat all new characters are added
-Internal nodes contain weights equal to the sum of their children's weights
-All nodes of the same weight will be in consecutive order.

Before updating, we search for the highest ordered node with the same weight as soon-to-be-updated node.
If found, we swap the two
Then we increment the weight and go up the tree incrementing the weight of all of its parents.
*/

struct Node
{
	int value;    //0 - 256 char value
	int weight;   //number of times the value has occured in file so far, NYT node always has weight = 0
	int order;    //nodes with higher weight must have higher orders, order must increase from left to right and from bottom to top
	
	Node* left;
	Node* right;
	Node* parent;

	Node(int _value, int _weight, unsigned LOWEST_ORDER, Node* l, Node* r, Node* p);
	bool isLeaf();
	bool isInner();
	bool isLeftChild();
};