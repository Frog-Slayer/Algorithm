#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const int INF = 1e9 + 7;

struct Segtree {
	int N;
	vector<int> tree;

	Segtree(int N) : N(N), tree(4 * N, -1) {}

	void update(int node, int start, int end, int idx, int val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = max(tree[node], val);
			return;
		}
	
		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, int val) {
		update(1, 0, N - 1, idx, val);
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return -1;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	
	}

	int query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	}
};

int main() {
	fastio;

	int T;
	cin >> T;

	while (T--) {
		int N, X;
		cin >> N >> X;

		vector<ll> accsum(N), sorted;

		for (int i = 0; i < N; i++) {
			cin >> accsum[i];
			if (i) accsum[i] += accsum[i - 1];
			sorted.emplace_back(accsum[i]);
			sorted.emplace_back(accsum[i] - X);
		}

		sort(all(sorted));
		sorted.erase(unique(all(sorted)), sorted.end());

		Segtree tree(sorted.size());
		int ans = INF;

		for (int i = 0; i < N; i++) {
			int qry = lower_bound(all(sorted), accsum[i] - X) - sorted.begin();
			qry = tree.query(0, qry);

			if (qry >= 0) ans = min(ans, i - qry);

			int upd = lower_bound(all(sorted), accsum[i]) - sorted.begin();
			tree.update(upd, i);

			ll a = accsum[i] - (i ? accsum[i - 1] : 0); 
			if (a >= X) ans = 1;
		}

		if (ans && ans != INF) cout << ans << '\n';
		else cout << "-1\n";

	}

}