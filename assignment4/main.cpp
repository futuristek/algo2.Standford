#include <iostream>
#include <sstream>
#include <fstream>
#include "../util/GraphHash.hpp"
#include "floyd_warshall.hpp"
using namespace std;


GraphHash createGraph(const char* fileName) {
	ifstream f(fileName);
	string line;
	getline(f, line);
	stringstream ss(line);
	int numNodes, numEdges;
	ss >> numNodes >> numEdges;

	GraphHash g(numNodes, numEdges);

	while(getline(f, line)) {
		int i, j, v;
		stringstream sss(line);
		sss >> i >> j >> v;
		g.addEdge(i - 1, j - 1, v);
	}

	return g;
}

int main() {
	auto g1 = createGraph("g1.txt");
	auto g2 = createGraph("g2.txt");
	auto g3 = createGraph("g3.txt");

	FloydWarshall fw1(g1);
	if (fw1.hasNegativeCycle())
		cout << "NULL" << endl;
	else
		cout << fw1.shortest() << endl;

	FloydWarshall fw2(g2);
	if (fw2.hasNegativeCycle())
		cout << "NULL" << endl;
	else
		cout << fw2.shortest() << endl;

	FloydWarshall fw3(g3);
	if (fw3.hasNegativeCycle())
		cout << "NULL" << endl;
	else
		cout << fw3.shortest() << endl;
}
