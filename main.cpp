#include<iostream>
#include"Encoder.h"
#include"Decoder.h"

using namespace std;


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

void testTreeUpdate() {
    HuffmanTree tree;
    printBT(tree.root);
    tree.updateTree('a');
    printBT(tree.root);
    tree.updateTree('a');
    printBT(tree.root);
    tree.updateTree('r');
    printBT(tree.root);
    tree.updateTree('d');
    printBT(tree.root);
    tree.updateTree('v');
    printBT(tree.root);
    tree.updateTree('a');
    printBT(tree.root);
    tree.updateTree('r');
    printBT(tree.root);
    tree.updateTree('k');
    printBT(tree.root);
    tree.updateTree('a');
    printBT(tree.root);
}

int findOrderOfBlockLeader(vector<Node*>& nodes, int orderOfCurrent) {
    int result = orderOfCurrent;
    for (int i = orderOfCurrent; i < 512; ++i) {
        if (nodes[i]->weight == nodes[orderOfCurrent]->weight) {
            result = i;
        }
    }
    return result;
}

int main() {
    Encoder encoder;
    encoder.encodeToTXT("testIn1.txt", "testOut1.txt");

   /*

    */
    /*
    vector<Node*> nodes(520, nullptr);
    nodes[512] = new Node(34, 3, nullptr, nullptr, nullptr);
    nodes[511] = new Node(35, 2, nullptr, nullptr, nullptr);
    nodes[510] = new Node(36, 2, nullptr, nullptr, nullptr);
    nodes[509] = new Node(37, 2, nullptr, nullptr, nullptr);
    nodes[508] = new Node(38, 1, nullptr, nullptr, nullptr);
    nodes[507] = new Node(39, 1, nullptr, nullptr, nullptr);
    nodes[506] = new Node(40, 1, nullptr, nullptr, nullptr);
    cout << findOrderOfBlockLeader(nodes, 506);
    */
	return 0;
}