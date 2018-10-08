#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Edge {
public:
	Edge() = default;

	Edge(int a, int b, int len): a(a), b(b), len(len) {
	}

	bool equal(const Edge e) {
		if (a == e.a && b == e.b)
			return true;
		else
			return false;
	}

	int getEither() {
		return a;
	}

	int getOther(int n) {
		if (a == n)
			return b;
		else
			return a;
	}

	int getLen() {
		return len;
	}

private:
	int a;
	int b;
	int len;
};

class Prim {
public:
	Prim(unordered_map<int, vector<Edge> > &G): marked(G.size(), false) {
		visit(G, 1);
		while (!crossEdges.empty()) {
			auto minEdge = delMin();
			auto v = minEdge.getEither();
			auto u = minEdge.getOther(v);
			
			cout << " Min edge " << v << ", " << u << "[" << marked[v] << " " << marked[u] << "]" << endl;

			if (marked[v] && marked[u])
				continue;
			mst.push_back(minEdge);
			if (!marked[v]) visit(G, v);
			if (!marked[u]) visit(G, u);
		}
	}

	void visit(unordered_map<int, vector<Edge> > &G, int n) {
		marked[n] = true;
		for (auto &edges: G[n]) {
			auto other = edges.getOther(n);
			if (!marked[other])
				crossEdges.push_back(edges);
		}
	}

	Edge delMin() {
		auto minEdge = crossEdges.front();

		// first pass to get min len
		for (auto &edge: crossEdges) {
			if (edge.getLen() < minEdge.getLen()) {
				minEdge = edge;
			}
		}
		//second pass to delete the same edges
		auto it = crossEdges.begin();
		while (it != crossEdges.end()) {
			if (it->equal(minEdge)) {
				it = crossEdges.erase(it);
			} else {
				++it;
			}
		}

		return minEdge;
	}

	int mstLenSum() {
		auto sum = 0;
		for (auto &e: mst) {
			sum += e.getLen();
		}
		return sum;
	}

private:
	vector<bool> marked;
	vector<Edge> mst;
	list<Edge> crossEdges;
};

void createGraph(unordered_map<int, vector<Edge> > &G) {
	auto f = ifstream("edges.txt");

	int numNodes = 0, numEdges = 0;
	string line;
	getline(f, line);
	stringstream(line) >> numNodes >> numEdges;

	while(getline(f, line)) {
		int a = -1, b = -1, len = -1;
		stringstream(line) >> a >> b >> len;

		if (G.find(a) == G.end()) {
			G[a] = vector<Edge>();
		}
		G[a].push_back(Edge(a, b, len));
		
		if (G.find(b) == G.end()) {
			G[b] = vector<Edge>();
		}

		G[b].push_back(Edge(b, a, len));
	}
}

int main() {

	auto G = unordered_map<int, vector<Edge> >();
	createGraph(G);
	cout << "MST sum of length = " << Prim(G).mstLenSum() << endl;
	return 0;
}
