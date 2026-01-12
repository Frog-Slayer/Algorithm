#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	int K;
	cin >> K;

	vector<int> price(K + 1);

	for (int i = 1; i <= K; i++) cin >> price[i];

	int X;
	cin >> X;

	set<int> labels;

	for (int i = 0; i < 4; i++) { 
		int label;
		cin >> label;
		labels.emplace(label);
	}

	int T;
	cin >> T;

	int ans = 0;
	map<int, int> meals;

	for (int i = 0; i < T; i++) { 
		int m;
		cin >> m;
		meals[m]++;
		ans += price[m];
	}

	for (int i = 0; i <= T; i++) { 
		int sum = i * X;

		for (auto &[meal, cnt] : meals) { 
			if (labels.count(meal)) sum += max(cnt - i, 0) * price[meal];
			else sum += cnt * price[meal];
		}

		ans = min(ans, sum);
	}

	cout << ans;
}