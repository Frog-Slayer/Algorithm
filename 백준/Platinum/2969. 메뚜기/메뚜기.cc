#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int MAX_N = 1500;

struct Segtree {
	int N;
	vector<short> tree;
	
	Segtree(short N) : N(N), tree(4 * N) {}

	void update(int node, int start, int end, int idx, short val) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = val;
			return;
		}

		int mid = (start + end) / 2;
		if (idx <= mid) update(node * 2, start, mid, idx, val);
		else update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int idx, short val) {
		update(1, 0, N - 1, idx, val);
	}

	short query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
	}

	short query(int left, int right) {
		left = max(left, 0);
		right = min(right, N - 1);
		return query(1, 0, N - 1, left, right);
	}
	
};

short dp[MAX_N][MAX_N], tmp[MAX_N][MAX_N];
vector<Segtree> horizontal, vertical;

int main() {
	fastio;

	int N;
	cin >> N;

	int R, C;
	cin >> R >> C;

	int idx = 0;
	vector<tuple<int, short, short>> v(N * N);

	horizontal.assign(N, Segtree(N));
	vertical.assign(N, Segtree(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int flower;
			cin >> flower;

			v[idx++] = make_tuple(flower, i, j);
		}
	}

	sort(all(v), greater<>());

	for (int i = 0, j = 0; i < N * N; i = j) {
		while (j < N * N && get<0>(v[j]) == get<0>(v[i])) j++; 

		int mx = 0;

		for (int k = i; k < j; k++) {
			auto &[c, x, y] = v[k];
			int mx = 0;

			mx = max(mx, x - 1 >= 0 ? max(horizontal[x - 1].query(0, y - 2), horizontal[x - 1].query(y + 2, N - 1)) : 0);
			mx = max(mx, x + 1 < N ? max(horizontal[x + 1].query(0, y - 2), horizontal[x + 1].query(y + 2, N - 1)) : 0);
			mx = max(mx, y - 1 >= 0 ? max(vertical[y - 1].query(0, x - 2), vertical[y - 1].query(x + 2, N - 1)) : 0);
			mx = max(mx, y + 1 < N ? max(vertical[y + 1].query(0, x - 2), vertical[y + 1].query(x + 2, N - 1)) : 0);

			tmp[x][y] = mx + 1;
		}

		for (int k = i; k < j; k++) {
			auto &[c, x, y] = v[k];
			dp[x][y] = tmp[x][y];

			horizontal[x].update(y, tmp[x][y]);
			vertical[y].update(x, tmp[x][y]);
		}
	}

	cout << dp[--R][--C];
}
