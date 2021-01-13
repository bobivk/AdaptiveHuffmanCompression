#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include"HuffmanTree.h"
struct Encoder {
	HuffmanTree tree;
	

	void writeBitsetToFile(std::vector<bool>* path, std::ofstream& out, unsigned char& byte, int& bitNumber);
	void addToBitset(std::vector<bool>* bitset, std::vector<bool>&);
	void addToBitset(std::vector<bool>* bitset, int);
	void writePathToFileTXT(std::ofstream& out, std::vector<bool>& path, int& bitCount);
	void writeCharToFileTXT(std::ofstream& out, unsigned char x, int& bitCount);
	void encode(const std::string inputFile, const std::string outputFile);
	void encodeToTXT(const std::string inputFile, const std::string outputFile);

};