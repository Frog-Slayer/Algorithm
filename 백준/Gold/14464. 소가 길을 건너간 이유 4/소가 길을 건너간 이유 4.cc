#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int main() { 
	fastio;

	int C, N;
	cin >> C >> N;

	multiset<int> chicken;
	vector<pair<int, int>> cow(N);

	for (int i = 0; i < C; i++) {
		int t;
		cin >> t;
		chicken.insert(t);
	}

	for (int i = 0; i < N; i++) cin >> cow[i].second >> cow[i].first;

	sort(all(cow));

	int ans = 0;

	for (int i = 0, cur = 0; i < N; i++) { 
		auto [b, a] = cow[i];
		auto it = chicken.lower_bound(a);

		if (it != chicken.end() && *it <= b) { 
			ans++;
			chicken.erase(it);
		}
	}

	cout << ans;
}
