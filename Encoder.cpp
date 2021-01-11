#include"Encoder.h"


void Encoder::writePathToFile(std::vector<bool>& path, std::ofstream& out, char& byte, int& bitNumber) {
	for (int i = bitNumber; i < path.size(); ++i) {
		if (i != 0 && i % 8 == 0) {
			out.write((char*)byte, sizeof(byte));
			byte = 0;
			bitNumber = 0;
		}
		byte <<= 1;
		byte |= path[i];
		++bitNumber;
	}
}
/*
void Encoder::encode(const std::string inputFile, const std::string outputFile) {
	std::ifstream input(inputFile);
	std::ofstream output(outputFile, std::ios::binary);

}
*/

void Encoder::encode(const std::string inputFile, const std::string outputFile) {
	std::ifstream input(inputFile);
	std::ofstream output(outputFile, std::ios::binary);
	char remainder{ 0 };
	int bitNumber{ 0 };
	while (input.peek()) {
		int x = int(input.get());
		if (tree.firstReadOf(x)) {
			//output NYT path followed by x in binary
			std::vector<bool> NYTpath = tree.getPathToNode(tree.NYTNode);
			writePathToFile(NYTpath, output, remainder, bitNumber);
			output.write((const char*)x, sizeof(x));
		}
		else {
			//output path to the leaf of x
			std::vector<bool> nodePath = tree.getPathToNode(tree.leaves[x]);
			writePathToFile(nodePath, output, remainder, bitNumber);
		}
		tree.insertSymbol(x);
	}
	if (remainder) {
		for (int i = 0; i < (8 - bitNumber); ++i) {
			remainder <<= 1;
		}
		output.write((char*)remainder, sizeof(remainder));
		output.write((char*)PSEUDO_EOF, sizeof(PSEUDO_EOF));
	}
}


/*
	Node* findNodeOf(int x) {
		auto foundNode = leaves.find(x);
		if (foundNode == leaves.end()) {
			return NYTNode;
		}
		else return foundNode->second;
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