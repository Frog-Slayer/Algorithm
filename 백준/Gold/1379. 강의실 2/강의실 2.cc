#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() {
	fastio;

	int N;
	cin >> N;

	vector<tuple<int, int, int>> v;

	for (int i = 0; i < N; i++) {
		int n, s, e;
		cin >> n >> s >> e;

		v.emplace_back(s, e, n);
	}

	sort(all(v));
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	vector<int> ans(N + 1);

	int roomIdx = 0;

	for (auto &[s, e, n] : v) {
		if (!pq.empty()) {
			auto [end, room] = pq.top();
			
			if (end <= s) {
				ans[n] = room;
				pq.pop();
				pq.emplace(e, room);
				continue;
			}
		}

		ans[n] = ++roomIdx;
		pq.emplace(e, roomIdx);
	}

	cout << roomIdx << '\n';

	for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}