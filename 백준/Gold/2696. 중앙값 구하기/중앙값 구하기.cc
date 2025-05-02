#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int T;
	cin >> T;

	while (T--) {
		int M;
		cin >> M;

		priority_queue<int, vector<int>, less<>> lpq;
		priority_queue<int, vector<int>, greater<>> rpq;

		vector<int> ans;

		for (int i = 0; i < M; i++) {
			int e;
			cin >> e;

			if (lpq.size() == rpq.size()) lpq.push(e);
			else rpq.push(e);

			if (!lpq.empty() && !rpq.empty()) {
				int ltop = lpq.top(), rtop = rpq.top();
				if (ltop > rtop) {
					lpq.pop();
					lpq.push(rtop);

					rpq.pop();
					rpq.push(ltop);
				}
			}

			if (i % 2 == 0) ans.emplace_back(lpq.top());
		}

		cout << ans.size();
		for (int i = 0; i < ans.size(); i++) {
			if (i % 10 == 0) cout << '\n';
			cout << ans[i] << ' ';
		}

		cout << '\n';
	}

}
