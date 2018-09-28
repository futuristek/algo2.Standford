#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

int main() {
	auto f = ifstream("jobs.txt");
	string line;
	getline(f, line);
	list<pair<int, int>> jobs;

	while (getline(f, line)) {
		auto ss = stringstream(line);
		pair<int, int> j;
		ss >> j.first >> j.second;
		jobs.push_back(j);
	}

	jobs.sort([](pair<int, int> &a, pair<int, int> &b) {
			return a.first/(float)a.second > b.first/(float)b.second;
		});

	long long sumLen = 0, sumWeightTime = 0;
	
	for (auto &x: jobs) {
		sumLen += x.second;
		sumWeightTime += sumLen*x.first;
	}

	cout << "Sum of weighted completion time: " << sumWeightTime << endl;
	return 0;
}
