#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../util/WeightedQuickUnionFind.hpp"

using namespace std;

namespace Params {
    constexpr int BITS = 24;
}

class Graph {
public:
    Graph();
    void findNeighbor();
    void mergeDistLessThanThree(bitset<Params::BITS>);
    int clusters();

private:
    unordered_map<bitset<Params::BITS>, int> map;
    WeightedQuickUnionFind uf;
};

Graph::Graph() {
    ifstream myFile("clustering_big.txt");

    if(myFile.is_open()) {
        string line;
        getline(myFile, line);

        int id = 0;
        // Should consier duplicated lines
        while (getline(myFile, line)) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            auto bs = bitset<Params::BITS>(line);
            if (map.find(bs) == map.end()) {
                map[bitset<Params::BITS>(line)] = id;
                id++;
            }
        }
    } else {
        cout << "Can't open file." << endl;
        exit(1);
    }

    uf = WeightedQuickUnionFind(map.size());

    //cout << map.size() << " " << uf.getNumSets() << endl;
}

void Graph::findNeighbor() {
    for (auto & elm : map) {
        mergeDistLessThanThree(elm.first);
    }
}

void Graph::mergeDistLessThanThree(bitset<Params::BITS> bset) {
    auto id = map[bset];

    //cout << "Before one id = " << id << endl;
    //uf.print();
    // Change one bit at a time
    for (std::size_t i = 0; i < bset.size(); i++) {
        bset.flip(i);
        if (map.find(bset) != map.end()) {
            if (!uf.connected(id, map[bset])) {
                uf.doUnion(id, map[bset]);
            }
        }
        bset.flip(i);
    }

    //cout << "Before two " << endl;
    //uf.print();
    for (std::size_t i = 0; i < bset.size(); i++) {
        bset.flip(i);
        for (std::size_t j = i + 1; j < bset.size(); j++) {
            bset.flip(j);
            if (map.find(bset) != map.end()) {
                if (!uf.connected(id, map[bset])) {
                    uf.doUnion(id, map[bset]);
                }
            }
            bset.flip(j);
        }

        bset.flip(i);
    }

    //cout << "After two " << endl;
    //uf.print();
}

int Graph::clusters() {
    return uf.getCount();
}

int main() {
    Graph g;
    g.findNeighbor();
    cout << "Number of clusters = " << g.clusters() << endl;
    return 0;
}