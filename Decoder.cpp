#include "Decoder.h"

void readFromFile(std::ifstream& input, char* memblock, int& size) {
	std::streampos fileSize;
	if (!input.is_open()) {
		std::cout << "Could not open input file." << std::endl;
		return;
	}
	fileSize = input.tellg();
	size = fileSize;
	memblock = new char[fileSize];
	input.seekg(0, std::ios::beg);
	input.read(memblock, fileSize);
	input.close();
	std::cout << "File has been read.\n";
}
void readByte(std::ifstream& in, std::vector<bool>& byte) {
	unsigned char x{ 0 };
	in.read((char*)x, 8);
	std::stack<bool> stack;
	for (int i = 0; i < 8; ++i) {
		stack.push((x >> i) & 1);
	}
	for (int i = 0; i < 8; ++i) {
		byte.push_back(stack.top());
		stack.pop();
	}
}

void Decoder::decode(std::string inputFile, std::string outputFile) {
	std::ifstream input(inputFile, std::ios::in | std::ios::binary | std::ios::ate);
	std::ofstream output(outputFile);
	std::vector<bool> byte;
	Node* current = tree.root;
	bool endOfFile = false;
	int i = 0;
	while (!endOfFile) {
		readByte(input, byte);
		if (byte[i] == 1) {
			current = current->right; //go right on 1
		}
		else current = current->left; //go left on 0
		if (current->isLeaf()) {
			if (current == tree.NYTNode) {
				readByte(input, byte);
				for (; i < i + 8; ++i) {

				}
			}
		}

	}
	

	//delete[] memblock;
	// 01100101
	//
}
//read next 8 bits, convert to char
unsigned char Decoder::decodeCharTXT(std::istream& in) {
	unsigned char result{ 0 };
	int bit{ 0 };
	for (int i = 0; i < 8; ++i) {
		bit = in.get();
		result <<= 1;
		if (bit == '1') {
			result |= 1;
		}
	}
	return result;
}

void Decoder::decodeTXT(std::istream& in, std::ostream& out) {
	Node* current = tree.root;
	while (in.peek() != EOF) {
		if (current->isLeaf()) {
			unsigned char toPrint{ 0 };
			if (current == tree.NYTNode){
				toPrint = decodeCharTXT(in);
			}
			else {
				if (current != nullptr) {
					toPrint = current->value;
				}
			}
			out << toPrint;
			tree.updateTree(toPrint);
			current = tree.root;
		}
		else {
			if (current != nullptr) {
				int nextBit = in.get();
				if (nextBit == '0') {
					current = current->left;
				}
				else current = current->right;
			}
		}
	}
}

/*
void getPathFromFile(std::vector<bool>& path, std::stack<bool>& st, std::ifstream& input, char& byte, int& bitNumber) {
	if (bitNumber == 8) {
		byte = 0;
		bitNumber = 0;
		input.read((char*)byte, sizeof(byte));
	}
}
*/
/*
void Decoder::decode(std::string inputFile, std::string outputFile) {
	std::ifstream input(inputFile, std::ios::in|std::ios::binary|std::ios::ate);
	std::ofstream output(outputFile);
	std::streampos fileSize;
	char* memblock;
	boost::dynamic_bitset<> bitset;
	input >> bitset;
	HuffmanTree tree;
	Node* current = tree.root;
	int outputValue{ 0 };
	for (int i = 0; i < bitset.num_blocks * bitset.bits_per_block; ++i) {
		if (current->isLeaf()) {
			if (current == tree.NYTNode) {
				//read the char value
				for (int j = 0; j < 8; ++j)
				{
					outputValue <<= 1;
					outputValue |= bitset[i + j];
				}
				i += 8;
				if (outputValue == PSEUDO_EOF) return;
			}
			else {
				outputValue = current->value;
			}
			tree.insertSymbol(outputValue);
			output.put(outputValue);
			current = tree.root;
		}
		

		if (bitset[i]) {
			current = current->right;
		}
		else current = current->left;
	}
	/*
	if (input.is_open()) {
		fileSize = input.tellg();
		memblock = new char[fileSize];
		input.seekg(0, std::ios::beg);
		input.read(memblock, fileSize);
		input.close();
		std::cout << "File has been read.\n";
		delete[] memblock;
	}
	*/

