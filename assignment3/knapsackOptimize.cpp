#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

class Knapsack {
public:
	Knapsack(const char* fileName) {
		ifstream file(fileName);
		string line;
		getline(file, line);
		istringstream is(line);
		is >> knapsack_size >> numItems;

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

	int maxValue(int i, int x) {
		if (i == 0 || x == 0)
			return 0;

		//cout << "i = " << i << " x = " << x << endl;

		pair<int, int> key(i - 1, x);
		int  left_val;

		if (S.find(key) != S.end())	{
			left_val = S[key];
		} else {
			left_val = maxValue(i - 1, x);
			S[key] = left_val;
		}


		//cout << " i = " << i  << " weight[i] = " << weight[i] << " x = " << x << endl;
		if (weight[i] <= x) {
			pair<int, int> key2(i - 1, x - weight[i]);
			int left_lower_val;
			if (S.find(key2) != S.end()) {
				left_lower_val  = S[key2];
			} else {
				left_lower_val = maxValue(i - 1, x -weight[i]);
				S[key2] = left_lower_val;
			}

			return max(left_val, left_lower_val + value[i]);
		} else {
			return left_val;
		}

	}

    vector<int> optimalSet() {
        if (selected.empty()) {
            optimalSetImpl(numItems, knapsack_size);
        }

        return selected;
    }

    void optimalSetImpl(int i, int x) {
        if (i == 0)
            return;

        if (S[make_pair(i, x)] > S[make_pair(i - 1, x)]) {
            selected.push_back(i);
            optimalSetImpl(i - 1, x - weight[i]);
        } else {
            optimalSetImpl(i - 1, x);
        }
    }

	int getNumItems() {
		return numItems;
	}

	int getSize() {
		return knapsack_size;
	}

	int getMapSize() {
		return S.size();
	}

private:
	int knapsack_size;
	int numItems;
	vector<int> value;
	vector<int> weight;
    vector<int> selected;
    map<pair<int, int>, int> S;
};

int main() {
	Knapsack knapsack("knapsack_big.txt");
	cout << knapsack.maxValue(knapsack.getNumItems(), knapsack.getSize()) << endl;
}
