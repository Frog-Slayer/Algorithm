#include <iostream>
#include <vector>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

typedef long long ll;
const int MOD = 998'244'353;
const int MAX_N = 1 << 20;//1048576

string S;
int N;
ll tens[MAX_N];

struct Segtree {
	ll tree[MAX_N << 1][10] = {0, };
 	ll lazy[MAX_N << 1][10] = {0, };

	void init(int node, int start, int end) {
		for (int i = 0; i < 10; i++) lazy[node][i] = i;
		if (start == end){
			tree[node][S[start] - '0'] = 1;
			return;
		}

		int mid = (start + end) / 2;
		init(node * 2, start, mid);
		init(node * 2 + 1, mid + 1, end);

		for (int i = 0; i < 10; i++) tree[node][i] = (tens[end - mid] * tree[node * 2][i] + tree[node * 2 + 1][i]) % MOD;
	}
	
	void propagate(int node, int start, int end) {
		bool go_prop = false;
		for (int i = 0; i < 10; i++) go_prop |= (lazy[node][i] != i);
		if (!go_prop) return;

		ll tmp[10] = {0, };
		for (int i = 0; i < 10; i++) {
			tmp[lazy[node][i]] += tree[node][i];
			tmp[lazy[node][i]] %= MOD;
		}

		for (int i = 0; i < 10; i++) tree[node][i] = tmp[i];

		if (start != end) {
			for (int child : {node * 2, node * 2 + 1}) {
				for (int i = 0; i < 10; i++) tmp[i] = lazy[node][lazy[child][i]];
				for (int i = 0; i < 10; i++) lazy[child][i] = tmp[i];
			}
		}

		for (int i = 0; i < 10; i++) lazy[node][i] = i;
	}

	void update(int node, int start, int end, int left, int right, int from, int to) {
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) {
			lazy[node][from] = to;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, from, to);
		update(node * 2 + 1, mid + 1, end, left, right, from, to);

		for (int i = 0; i < 10; i++) tree[node][i] = (tens[end - mid] * tree[node * 2][i] + tree[node * 2 + 1][i]) % MOD;
	}

	void update(int left, int right, int a, int b) {
		update(1, 0, N - 1, left, right, a, b);
	}

	ll query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) {
			ll ret = 0;
			for (int i = 0; i < 10; i++){
				ret += tree[node][i] * i;
				ret %= MOD;
			}
			return ret;
		}

		int mid = (start + end) / 2;
		if (mid >= right) return query(node * 2, start, mid, left, right);
		return (tens[min(end, right) - mid] * query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right)) % MOD;
	}

	int query(int left, int right) {
		return query(1, 0, N - 1, left, right);
	}

} tree;

int main() {
	fastio;
	cin >> S;

	N = S.length();

	tens[0] = 1;
	for (int i = 1; i <= N; i++) tens[i] = (tens[i - 1] * 10) % MOD;
	tree.init(1, 0, N - 1);

	int Q;
	cin >> Q;

	for (int q = 0; q < Q; q++) {
		int op, i, j;
		cin >> op >> i >> j;
		i--; j--;//0

		if (op == 1) {
			int from, to;
			cin >> from >> to;
			tree.update(i, j, from, to);
		}
		else cout << tree.query(i, j) << '\n';
	}
}