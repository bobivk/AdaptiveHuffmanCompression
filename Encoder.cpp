#include<iostream>
#include<fstream>
#include<vector>
#include"HuffmanTree.h"

/*
key verbs:

insert new value,
give birth to new nodes,
update weight,
check if max in weight class,
swap,
isRoot,
move to parent
*/

//char of value 256 marks the end of the file
const int PSEUDO_EOF = 256;

struct Encoder {

	HuffmanTree tree;

	

	void encode(std::string inputFile, std::string outputFile) {
		std::ifstream input(inputFile);
		std::ofstream output(outputFile);

		while (input.peek()) {
			int x = int(input.get());
			tree.insertSymbol(x);
			if (tree.firstReadOf(x)) {
				//output NYT code followed by code of x
			}
			else {
				//output code of x
			}
			//addCharToTree(x);
		}
	}

	void slideAndIncrement(Node* current) {
		if (current == nullptr) return;
		Node* blockLeader = current;
		//findBlockLeader(root, current);
		if (blockLeader != current) {
			//swapNodes(blockLeader, current);
		}
		++current->weight;
		slideAndIncrement(current->parent);
	}
};


/*
	Node* findNodeOf(int x) {
		auto foundNode = leaves.find(x);
		if (foundNode == leaves.end()) {
			return NYTNode;
		}
		else return foundNode->second;
	}
	void addCharToTree(char x) {
		Node* nodeOfX = findNodeOf(x);
		if (nodeOfX == NYTNode) {
			Node* newParent = new Node('\0', 1, 3, false, NYTNode, nullptr, NYTNode->parent);
			newParent->left = NYTNode;
			//create a node for x
			Node* newNode = new Node(x, 1, 2, false, nullptr, nullptr, newParent);
			newParent->right = newNode;
			leaves.insert({ x, newNode });
		}
		else {
			nodeOfX->weight++;
		}
		updateTree(nodeOfX);
	}
	/*
	void updateTree() {
		Node* current = nullNode->parent;
		while (current != huffRoot) {
			current->weight++;
			if (current->weight > current->getWeightOfSibling()) {
				swapNodes(current, current->getSibling());
			}
			if (current->weight > current->parent->weight) {
				swapNodes(current, current->parent);
			}
		}
	}*/
	/*
	void findBlockLeader(Node* current, Node*& max)  {
		if (current == nullptr || max == root) return;
		if (current->weight == max->weight &&
			current != max->parent &&
			current->order > max->order) {
			max = current;
		}
		findBlockLeader(current->left, max);
		findBlockLeader(current->right, max);
	}
	*/