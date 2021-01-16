#pragma once
#include<fstream>
#include<stack>
#include"HuffmanTree.h"
struct Decoder
{

	HuffmanTree tree;
	void readFromFile(std::ifstream& in, char* memblock);
	unsigned char decodeCharTXT(std::istream& in);
	void decode(std::string inputFile, std::string outputFile);
	void decodeTXT(std::istream& in, std::ostream& out);
};

