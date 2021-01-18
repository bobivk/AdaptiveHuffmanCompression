#pragma once
#include<fstream>
#include<stack>
#include"HuffmanTree.h"
struct Decoder
{

	HuffmanTree tree;

	unsigned char decodeCharTXT(std::istream& in);
	void decode(std::string inputFile, std::string outputFile);
	void decodeTXT(std::istream& in, std::ostream& out);
};

