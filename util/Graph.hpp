#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include "Edge.hpp"

class Graph {
public:
    Graph(int V): V(V), adj(V) { }

    int numVertices() const {
        return V;
    }

    int numEdges() const {
        return E;
    }

    void addEdge(const Edge e) {
        auto either = e.either();
        auto other = e.other(either);
        adj[either].push_back(e);
        adj[other].push_back(e);
        E++;
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> vec;

        for (int v = 0; v < V; ++v) {
            auto list = adj[v];
            for (auto & e: list) {
                if ((e).other(v) > v)
                    vec.push_back(e);
            }
        }

        return vec;
    }

private:
    std::vector<std::vector<Edge> > adj;
    int V;
    int E;
};
#endif