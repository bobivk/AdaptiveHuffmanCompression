#include<iostream>
using namespace std;

int main() {
	cout << "ab";
	cout << char(0) << char(1);
	cout << "ba";
	cout << char(128) << char(129) << char(250);
	cout << "cc";
	cout << char(255) << char(256);
	return 0;
}