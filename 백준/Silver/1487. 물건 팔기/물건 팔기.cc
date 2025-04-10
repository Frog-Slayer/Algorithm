#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> cost(N), fee(N);

	for (int i = 0; i < N; i++) cin >> cost[i] >> fee[i];

	int max_profit = 0, max_profit_cost = 1e6 + 7;

	for (int i = 0; i < N; i++) {
		int cur = cost[i];
		int profit = 0;

		for (int j = 0; j < N; j++) {
			if (cost[j] >= cur && cur > fee[j]) profit += cur - fee[j];
		}

		if (profit >= max_profit) {
			if (max_profit == profit) max_profit_cost = min(max_profit_cost, cur);
			else max_profit_cost = cur;

			max_profit = profit;
		}

	}

	cout << (max_profit > 0 ? max_profit_cost : 0);
	
}
