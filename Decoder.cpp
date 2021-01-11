#include "Decoder.h"

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

