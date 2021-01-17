﻿#include<iostream>
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
}
void printLeaves1(HuffmanTree* tree) {
    for (auto i : tree->leaves) {
        if (i != nullptr)
            std::cout << i->value << " ";
    }
    std::cout << std::endl;
}

void testNodeSwap() {
    HuffmanTree tree;
    tree.updateTree('a');

    tree.updateTree('a');

    tree.updateTree('r');

    tree.updateTree('d');

    tree.updateTree('v');

    tree.updateTree('a');

    tree.updateTree('r');

    tree.updateTree('k');
    tree.root->left->weight++;
    printBT(tree.root);
    printLeaves1(&tree);
    std::cout << "-------------------------" << std::endl;
    tree.swapNodes(tree.root->left, tree.root->right);
    printBT(tree.root);
    printLeaves1(&tree);
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

void encode(const char* inFile, const char* outFile) {
    Encoder encoder;
    std::ifstream textIn (inFile);
    std::ofstream codeOut(outFile);
    encoder.encodeToTXT(textIn, codeOut);
    textIn.close();
    codeOut.close();
}

void decode(const char* inFile, const char* outFile) {
    Decoder decoder;
    std::ifstream codeIn(inFile);
    std::ofstream textOut(outFile);
    decoder.decodeTXT(codeIn, textOut);
    codeIn.close();
    textOut.close();
}

int main1(int argc, char* argv[]) {
    //std::ifstream textIn("testIn2.txt");
    //std::ofstream codeOut("testOut2.txt");
    //std::ifstream codeIn("testOut2.txt");
    //std::ofstream textOut("testInB.txt");
    //testNodeSwap();
    //Encoder encoder;
    //Decoder decoder;
    //cout << decoder.decodeCharTXT(input);
    //encoder.encodeToTXT(textIn, codeOut);
    //decoder.decodeTXT(codeIn, textOut);


    if (!(argv[2][0] == '-') && (argv[2][1] == 'i') && !(argv[2][0] == '-') && (argv[2][1] == 'o'))
    {
        cout << "type: Huffman -c[ompress] | -d[ecompress]] -i <inputfile> -o <outputfile>" << endl;
        return 0;
    }
    if ((argv[1][0] == '-') && (argv[1][1] == 'c')) {
        encode(argv[3], argv[5]);
    }
    if ((argv[1][0] == '-') && (argv[1][1] == 'd')) {
        decode(argv[3], argv[5]);
    }

    return 0;
}
int main() {
    encode("testIn1.txt", "testOut1.txt");
    //encode("1984.txt", "1984code.txt");

    //decode("1984code.txt", "1984decoded.txt");
    
    //testTreeUpdate();
    //encode("testIn2.txt", "1984code.txt");
    return 0;
}