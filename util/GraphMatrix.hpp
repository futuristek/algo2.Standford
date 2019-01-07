#ifndef GRAPHMATRIX_HPP
#define GRAPHMATRIX_HPP

#include <vector>
#include <limits>

class GraphMatrix {
public:
	GraphMatrix(int n, int m) {
		matrix = std::vector<std::vector<int>>(n, std::vector<int>(m));
		for (size_t i = 0; i < matrix.size(); i++) {
			for (size_t j = 0; j < matrix[i].size(); j++) {
				matrix[i][j] = std::numeric_limits<int>::max();
			}
		}
		this->n = n;
		this->m = m;
	}

	void addEdge(int i, int j, int v) {
		matrix[i][j] =	v;
	}

	bool isEdge(int i, int j) const {
		return (matrix[i][j] == std::numeric_limits<int>::max() ? false : true);
	}

	int getEdge(int i, int j) const {
		return matrix[i][j];
	}

	int numNodes() const {
		return n;
	}

	int numEdges() const {
		return m;
	}

private:
	std::vector<std::vector<int>> matrix;
	int n;
	int m;
};

#endif /* GRAPHMATRIX_HPP */
