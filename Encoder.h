#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"HuffmanTree.h"
struct Encoder {
	HuffmanTree tree;
	

	void writePathToFile(std::vector<bool>& path, std::ofstream& out, char& byte, int& bitNumber);
	void encode(const std::string inputFile, const std::string outputFile);

};