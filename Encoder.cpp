#include"Encoder.h"


void Encoder::writeBitsetToFile(std::vector<bool>* path, std::ofstream& out, unsigned char& byte, int& bitNumber) {
	for (int i = bitNumber; i < path->size(); ++i) {
		if (bitNumber != 0 && bitNumber % 8 == 0) {
			out.write((char*)byte, 8);
			byte = 0;
			bitNumber = 0;
		}
		byte <<= 1;
		byte |= path->at(i);
		++bitNumber;
	}
}
void Encoder::addToBitset(std::vector<bool>* bitset, std::vector<bool>& path) {
	bitset->insert(std::end(*bitset), std::begin(path), std::end(path));
}

void Encoder::addToBitset(std::vector<bool> *bitset, int x) {
	std::stack<bool> stack;
	for (int i = 0; i < 8; ++i) {
		stack.push((x >> i) & 1);
	}
	for (int i = 0; i < 8; ++i) {
		bitset->push_back(stack.top());
		stack.pop();
	}
}


void Encoder::encode(const std::string inputFile, const std::string outputFile) {
	std::ifstream input(inputFile);
	std::ofstream output(outputFile, std::ios::binary);
	auto bitset = new std::vector<bool>();

	while(input.peek()){

		unsigned char x = input.get();
		if (tree.firstReadOf(x)) {
			std::vector<bool> NYTpath = tree.getPathToNode(tree.NYTNode);
			addToBitset(bitset, NYTpath);
			addToBitset(bitset, x);
		}
		else {
			std::vector<bool> nodePath = tree.getPathToNode(tree.leaves[x]);
			addToBitset(bitset, nodePath);
		}
		tree.updateTree(x);
	}
	addToBitset(bitset, PSEUDO_EOF);
	unsigned char byte{ 0 };
	int bitNumber{ 0 };
	int tailOfZeroes = bitset->size() % 8;
	for (int i = 0; i < tailOfZeroes; ++i) 
		bitset->push_back(0);
	writeBitsetToFile(bitset, output, byte, bitNumber);
	delete bitset;
}

void Encoder::writePathToFileTXT(std::ofstream& out, std::vector<bool>& path, int& bitCount) {
	if (bitCount == 8) {
		out << " ";
		bitCount = 0;
	}
	for (auto i : path) {
		out << i;
	}
}
void Encoder::writeCharToFileTXT(std::ofstream& out, unsigned char x, int& bitCount) {
	std::stack<bool> stack;
	for (int i = 0; i < 8; ++i) {
		stack.push((x >> i) & 1);
	}
	for (int i = 0; i < 8; ++i) {
		if (bitCount == 8) {
			out << " ";
			bitCount = 0;
		}
		out << stack.top();
		stack.pop();
	}
}


void Encoder::encodeToTXT(const std::string inputFile, const std::string outputFile) {
	std::ifstream input(inputFile);
	std::ofstream output(outputFile, std::ios::trunc);

	int bitCount = 0;
	while (input.peek() != EOF) {
		unsigned char x = input.get();
		if (tree.firstReadOf(x)) {
			std::vector<bool> NYTpath = tree.getPathToNode(tree.NYTNode);
			writePathToFileTXT(output, NYTpath, bitCount);
			writeCharToFileTXT(output, x, bitCount);
		}
		else {
			std::vector<bool> nodePath = tree.getPathToNode(tree.leaves[x]);
			writePathToFileTXT(output, nodePath, bitCount);
		}
		tree.updateTree(x);
	}
	writeCharToFileTXT(output, PSEUDO_EOF, bitCount);
}


/*
void Encoder::encode(const std::string inputFile, const std::string outputFile) {
	std::ifstream input(inputFile);
	std::ofstream output(outputFile, std::ios::binary);
	unsigned char remainder{ 0 };
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
		tree.updateTree(x);
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