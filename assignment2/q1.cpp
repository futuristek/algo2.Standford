//
//  q1.cpp
//  assignment2
//
//  Created by Jie Chen on 11/9/18.
//  Copyright © 2018 Jie Chen. All rights reserved.
//

#include "../util/Edge.hpp"
#include "../util/Graph.hpp"
#include "../util/UnionFind.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

Graph getGraph() {
    ifstream myfile("clustering1.txt");
    
     if (!myfile.is_open()) {
     cerr << "Can't open file" << endl;
     exit(0);
     }
    
    int v, w, weight, numNodes;
    string line;
    
    getline(myfile, line);

    stringstream(line) >> numNodes;
    
    Graph g(numNodes);
    
    while(getline(myfile, line)) {
        stringstream(line) >> v >> w >> weight;
        Edge e(v, w, weight);
        g.addEdge(e);
    }
    
    return g;
}


int main() {
    auto cmp = [](Edge &a, Edge &b) {return a.getWeight() > b.getWeight(); };
    priority_queue<Edge, vector<Edge>, decltype(cmp) > minQ(cmp);
    auto g = getGraph();
    auto edges = g.edges();
    
    for (auto const e: edges) {
        minQ.push(e);
    }
    
    UnionFind uf(g.numVertices());
    vector<Edge> mst;
    
    while (!minQ.empty() && mst.size() < (g.numVertices() - 1) && uf.getNumSets() > 3) {
        auto e = minQ.top();
        minQ.pop();
        auto v = e.either(), w = e.other(v);
        
        if (uf.connected(v, w))
            continue;
        
        uf.doUnion(v, w);
        mst.push_back(e);
    }
    
    cout << "Min distanct between 4 clusters = " << mst.back().getWeight() << endl;
    
    return 0;
}