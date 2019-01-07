#ifndef GRAPHHASH_HPP
#define GRAPHHASH_HPP

#include <unordered_map>
#include <limits>

class GraphHash {
public:
	GraphHash(int n, int m) {
		this->n = n;
		this->m = m;
	}

	void addEdge(int i, int j, int v) {
		auto k = key(i, j);
		map[k] = v;
	}

	bool isEdge(int i, int j) const {
		return (map.find(key(i, j)) != map.end() ? true : false);
	}

	int getEdge(int i, int j) const {
		return map.at(key(i, j));
	}

	int numNodes() const {
		return n;
	}

	int numEdges() const {
		return m;
	}

private:
	size_t key(int i, int j) const {
		return ((size_t) i << 32 | (unsigned int) j);
	}

private:
	std::unordered_map<size_t, int> map;
	int n;
	int m;
};

#endif /* GRAPHHASH_HPP */
