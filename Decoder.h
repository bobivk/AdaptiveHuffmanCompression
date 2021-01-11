#pragma once
#include<fstream>
#include<stack>
#include"HuffmanTree.h"
class Decoder
{

	HuffmanTree tree;
	void decode(std::string inputFile, std::string outputFile);
};

