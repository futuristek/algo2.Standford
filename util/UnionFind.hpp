#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
#include <vector>

class UnionFind {
public:
    UnionFind() = default;
    UnionFind(int N): vec(N + 1) {
        for (int i = 1; i < N + 1; ++i)
            vec[i] = i;

        numSets = N;
    }

    bool connected(int v, int w);
    void doUnion(int v, int w);
    int  find(int v);
    int getNumSets();

private:
    std::vector<int> vec;
    int numSets;
};

bool UnionFind::connected(int v, int w) {
    return vec[v] == vec[w];
}

void UnionFind::doUnion(int v, int w) {
    auto wSetNum = vec[w];
    for (int i = 1; i < vec.size() + 1; ++i) {
        if (vec[i] == wSetNum)
            vec[i] = vec[v];
    }

    numSets--;
}

int UnionFind::find(int v) {
    return vec[v];
}

int UnionFind::getNumSets() {
    return numSets;
}
#endif