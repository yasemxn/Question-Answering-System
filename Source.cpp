#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Functions.h"
using namespace std;

int main()
{
	cout << "it is starting... " << endl;
	auto start = std::chrono::high_resolution_clock::now();

	startAlgorithm();

	auto end = std::chrono::high_resolution_clock::now();

	cout << "Run time-> " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << endl << endl;

	system("pause");

}
