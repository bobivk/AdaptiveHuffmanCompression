#include<iostream>
using namespace std;
#include"Encoder.h"
#include"Decoder.h"



void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "L " : "R ");

        // print the value of the node
        std::cout << node->order << "," <<char(node->value) << "," << node->weight << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}
void printBT(const Node* node)
{
    printBT("", node, false);
    cout << endl << endl;
}

int findOrderOfBlockLeader(vector<Node*>& nodes, int orderOfCurrent) {
    for (int i = orderOfCurrent + 1; i < 511; ++i) {
        if (nodes[i]->weight < nodes[i + 1]->weight //block leader
            && nodes[i]->weight == nodes[orderOfCurrent]->weight) {// block lead is in the same block
            
            return i;
        }
        if (nodes[i]->weight > nodes[orderOfCurrent]->weight) return orderOfCurrent;
    }
    return orderOfCurrent;
}

int main() {/*
    HuffmanTree tree;
    printBT(tree.root);
    tree.insertSymbol('a');
    printBT(tree.root);
    tree.insertSymbol('a');
    printBT(tree.root);
    tree.insertSymbol('r');
    printBT(tree.root);
    tree.insertSymbol('d');
    printBT(tree.root);
    tree.insertSymbol('v');
    printBT(tree.root);
    tree.insertSymbol('a');
    printBT(tree.root);
    tree.insertSymbol('r');
    printBT(tree.root);
    tree.insertSymbol('k');
    printBT(tree.root);
    tree.insertSymbol('a');
    printBT(tree.root);
    */

    vector<Node*> nodes(520, nullptr);
    nodes[512] = new Node(34, 3, nullptr, nullptr, nullptr);
    nodes[511] = new Node(35, 2, nullptr, nullptr, nullptr);
    nodes[510] = new Node(36, 2, nullptr, nullptr, nullptr);
    nodes[509] = new Node(37, 2, nullptr, nullptr, nullptr);
    nodes[508] = new Node(38, 1, nullptr, nullptr, nullptr);
    nodes[507] = new Node(39, 1, nullptr, nullptr, nullptr);
    nodes[506] = new Node(40, 1, nullptr, nullptr, nullptr);
    cout << findOrderOfBlockLeader(nodes, 509);
	return 0;
}