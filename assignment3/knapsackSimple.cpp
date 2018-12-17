#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Knapsack {
public:
	Knapsack(const char* fileName) {
		ifstream file(fileName);
		string line;
		getline(file, line);
		istringstream is(line);
		is >> knapsack_size >> numItems;

		S = vector<vector<int> >(numItems + 1, vector<int>(knapsack_size + 1, 0));
		value.push_back(0);
		weight.push_back(0);

		while(getline(file, line)) {
			istringstream is(line);
			int v, w;
			is >> v >> w;
			value.push_back(v);
			weight.push_back(w);
		}
	}

	int maxValue() {
		for (int i = 1; i < numItems + 1; i++) {
			for (int x = 1; x < knapsack_size + 1; x++) {
				if (weight[i] <= x) {
					S[i][x] = max(S[i - 1][x], S[i - 1][x - weight[i]] + value[i]);
				} else {
					S[i][x] = S[i - 1][x];
				}
			}
		}

		return S[numItems][knapsack_size];
	}

	void print() {
		for (int i = 0; i < numItems + 1; i++) {
			for (int x = 0; x < knapsack_size + 1; x++) {
				cout << S[i][x] << " ";
			}
			cout << endl;
		}
	}

private:
	int knapsack_size;
	int numItems;
	vector<int> value;
	vector<int> weight;
	vector<vector<int> > S;
};

int main() {
	Knapsack knapsack("knapsack1.txt");
	cout << knapsack.maxValue() << endl;
}
