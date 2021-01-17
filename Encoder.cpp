#include"Encoder.h"

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
void printLeaves(HuffmanTree* tree) {
	for (auto i : tree->leaves) {
		if (i != nullptr)
			std::cout << i->value << " ";
	}
	std::cout << std::endl;
}

void Encoder::writeBitsetToFile(std::vector<bool>* path, std::ostream& out, unsigned char& byte, int& bitNumber) {
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
		textSize += 8;
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

void Encoder::writePathToFileTXT(std::ostream& out, std::vector<bool>& path) {
	for (auto i : path) {
		out << i;
	}
}
void Encoder::writeCharToFileTXT(std::ostream& out, unsigned char x) {
	std::stack<bool> stack;
	for (int i = 0; i < 8; ++i) {
		stack.push((x >> i) & 1);
	}
	for (int i = 0; i < 8; ++i) {
		out << stack.top();
		stack.pop();
	}
}


void Encoder::encodeToTXT(std::istream& input, std::ostream& output) {
	while (input.peek() != EOF) {
		unsigned char x = input.get();
		textSize += 8;
		if (tree.firstReadOf(x)) {
			std::vector<bool> NYTpath = tree.getPathToNode(tree.NYTNode);
			writePathToFileTXT(output, NYTpath);
			writeCharToFileTXT(output, x);
			codeSize += NYTpath.size();
			codeSize += 8;
		}
		else {
			std::vector<bool> nodePath = tree.getPathToNode(tree.leaves[x]);
			writePathToFileTXT(output, nodePath);
			codeSize += nodePath.size();
		}
		tree.updateTree(x);
	}
	std::vector<bool> NYTpath = tree.getPathToNode(tree.NYTNode);
	writePathToFileTXT(output, NYTpath);
	writeCharToFileTXT(output, PSEUDO_EOF);
	printBT1(tree.root);
	printLeaves(&tree);
	std::cout << "Compression rate is: " << getCompressionRate() << std::endl;

}

double Encoder::getCompressionRate() {
	return (double) codeSize / (double) textSize;
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


*/