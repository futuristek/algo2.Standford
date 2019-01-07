#ifndef FLOYD_WARSHALL_CPP
#define FLOYD_WARSHALL_CPP

/*
 * An implementation of Floyd Warshall algorithm
 * Base case A[i, j, 0]
 * if i == j, A[i, j, 0] = 0
 * if i != j and (i, j) is an edge, A[i, j, 0] = Edge(i, j)
 * if i != j, and (i, j) is not an edge, A[i, j, 0] = +infinity
 */

#include <vector>
#include "../util/GraphHash.hpp"
#include <limits>

class FloydWarshall {
public:
	FloydWarshall(const GraphHash& g) {
		auto N = g.numNodes();
		A = std::vector<std::vector<std::vector<long long>>>(N, std::vector<std::vector<long long>>(N, std::vector<long long>(N)));

		auto inf = std::numeric_limits<long long>::max();
		// Init to base case
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N;  j++) {
				if (i == j) {
					A[i][j][0] = 0;
				} else {
					if (g.isEdge(i, j)) {
						A[i][j][0] = g.getEdge(i, j);
					} else {
						A[i][j][0] = inf;
					}
				}
			}
		}

		for (int k = 1; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N;  j++) {
				if (A[i][k][k - 1]  == inf || A[k][j][k - 1] == inf) {
						A[i][j][k] = A[i][j][k - 1];
					} else {
						A[i][j][k] = std::min(A[i][j][k - 1], A[i][k][k - 1] + A[k][j][k - 1]);
					}
				}
			}
		}
	}

	int shortest() {
		auto N = A.size();
		auto s = A[0][0][N - 1];
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N;  j++) {
				s = std::min(A[i][j][N -1], s);
			}
		}
		return s;
	}

	bool hasNegativeCycle() {
		auto N = A.size();
		for (size_t i = 0; i < N; i++) {
			if (A[i][i][N - 1] < 0) {
				return true;
			}
		}
		return false;
	}

private:
	std::vector< std::vector< std::vector<long long> > > A;
};

#endif /* FLOYD_WARSHALL_CPP */
