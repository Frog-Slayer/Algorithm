#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	int N;
	vector<int> tree;
	vector<int> T;

	Segtree(int N, vector<int> &T): N(N), tree(4 * N), T(T) {}

	void update(int node, int start, int end, int idx){
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = idx; 
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx);
		update(node * 2 + 1, mid + 1, end, idx);

		tree[node] = T[tree[node *2]] < T[tree[node * 2 + 1]] ? tree[node * 2]: tree[node * 2 + 1];
	}

	void update(int idx) {
		update(1, 1, N, idx);
	}

	int query(int node, int start, int end, int left, int right){
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;

		int lquery = query(node * 2, start, mid, left, right);
		int rquery = query(node * 2 + 1, mid + 1, end, left, right);

		return T[lquery] < T[rquery] ? lquery : rquery; 
	}

	int query(int left, int right) {
		return query(1, 1, N, left, right);
	}

	ll solve(int left, int right) {
		int min_idx = query(left, right);

		ll ret = (ll)(right - left + 1) * T[min_idx];

		if (left < min_idx) ret = max(ret, solve(left, min_idx - 1));
		if (min_idx < right) ret = max(ret, solve(min_idx + 1, right));

		return ret;
	}
};

int main() {
	fastio;
	
	int N;
	cin >> N;

	vector<int> T(N + 1);

	T[0] = 1111111;
	for (int i = 1; i <= N; i++) cin >> T[i];

	Segtree tree(N, T);

	for (int i = 1; i <= N; i++) tree.update(i);

	cout << tree.solve(1, N);
}