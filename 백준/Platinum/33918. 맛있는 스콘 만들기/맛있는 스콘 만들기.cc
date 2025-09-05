#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

struct Segtree{ 
	int N;
	vector<int> tree;

	Segtree(int N) : tree(4 * N), N(N) {}

	void update(int node, int start, int end, int idx, int val) { 
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) /2;

		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, int val) {
		update(1, 0, N - 1, idx, val);
	}

	int query(int node, int start, int end, int left, int right) { 
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) /2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	int query(int left, int right) { 
		return query(1, 0, N - 1, left, right);
	}
};

int dp[201][25001] = {0, };

int main() {
	fastio;
	
	int N, M, C, D;
	cin >> N >> M >> C >> D;

	vector<int> b(N + 1);
	for (int i = 1; i <= N; i++) cin >> b[i];

	vector<Segtree> trees(C, Segtree(M / C + 1));

	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= M; k++) { 
			int mmax = trees[k % C].query((k - D) / C, min(M, (k + D)) / C);
			dp[i][k] = mmax + M - abs(b[i] - k);
		}
		
		for (int j = 1; j <= M; j++) trees[j % C].update(j / C, dp[i][j]);
	}

	int ans = 0;

	for (int i = 1; i <= M; i++) ans = max(ans, dp[N][i]);

	cout << ans;
}
