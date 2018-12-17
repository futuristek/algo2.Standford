#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
#include <vector>
#include <iostream>

class WeightedQuickUnionFind {
public:
    WeightedQuickUnionFind() = default;

    WeightedQuickUnionFind(int N): id(N), compSize(N) {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            compSize[i] = 1;
        }

        count = N;
    }

    bool connected(int v, int w);
    void doUnion(int v, int w);
    int  find(int v);
    int getCount();
    void print();

private:
    std::vector<int> id;
    std::vector<int> compSize;
    int count;
};

bool WeightedQuickUnionFind::connected(int v, int w) {
    return find(v) == find(w);
}

void WeightedQuickUnionFind::doUnion(int v, int w) {
    if (connected(v, w)) return;

    if (compSize[v] < compSize[w]) {
        id[v] = w;
        compSize[w] += compSize[v];
    } else {
        id[w] = v;
        compSize[v] += compSize[w];
    }

    count--;
}

int WeightedQuickUnionFind::find(int v) {
    while (id[v] != v) v = id[v];
    return v;
}

int WeightedQuickUnionFind::getCount() {
    return count;
}

void WeightedQuickUnionFind::print() {
    std::cout << "printing UnionFind: " << std::endl;
    for (auto i = 0; i < id.size(); i++) {
        std::cout << "i = " << i << " id = " << find(i) << std::endl;
    }
}
#endif