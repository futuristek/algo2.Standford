#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
#include <vector>
#include <iostream>

class UnionFind {
public:
    UnionFind() = default;
    UnionFind(int N): vec(N) {
        for (int i = 0; i < N; ++i)
            vec[i] = i;

        numSets = N;
    }

    bool connected(int v, int w);
    void doUnion(int v, int w);
    int  find(int v);
    int getNumSets();
    void print();

private:
    std::vector<int> vec;
    int numSets;
};

bool UnionFind::connected(int v, int w) {
    return vec[v] == vec[w];
}

void UnionFind::doUnion(int v, int w) {
    auto vId = find(v);
    auto wId = find(w);

    if (vId == wId) return;

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == wId)
            vec[i] = vId;
    }

    numSets--;
}

int UnionFind::find(int v) {
    return vec[v];
}

int UnionFind::getNumSets() {
    return numSets;
}

void UnionFind::print() {
    std::cout << "printing UnionFind: " << std::endl;
    for (auto i = 0; i < vec.size(); i++) {
        std::cout << "i = " << i << " id = " << vec[i] << std::endl;
    }
}
#endif