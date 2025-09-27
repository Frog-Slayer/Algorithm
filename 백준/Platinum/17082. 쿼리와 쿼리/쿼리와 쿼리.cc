#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	vector<int> tree, lazy;
	int N;

	Segtree(int N) : tree(4 * N + 4), lazy(4 * N + 4),  N(N) {}

	void propagate(int node, int start, int end) { 
		if (lazy[node]) { 
			tree[node] += (end - start + 1) * lazy[node];

			if (start != end) { 
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			
			lazy[node] = 0;
		}
	}

	void update(int node, int start, int end, int left, int right) { 
		propagate(node, start, end);
		if (right < start || end < left) return;
		if (left <= start && end <= right) { 
			lazy[node]++;
			propagate(node, start, end);
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right);
		update(node * 2 + 1, mid + 1, end, left, right);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int left, int right) { 
		update(1, 1, N, left, right);
	}

	int query(int node, int start, int end, int idx) { 
		propagate(node, start, end);
		if (idx < start || end < idx) return 0;
		if (start == end) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, idx) + query(node * 2 + 1, mid + 1, end, idx);
	}

	int query(int idx) { 
		return query(1, 1, N, idx);
	}
};

int main() { 
	fastio;

	int N, M, Q;
	cin >> N >> M >> Q;

	vector<int> a(N + 1), l(M), r(M);
	Segtree segtree(N);

	for (int i = 1; i <= N; i++) cin >> a[i]; 

	for (int i = 0; i < M; i++) cin >> l[i];

	for (int i = 0; i < M; i++) cin >> r[i];

	sort(all(l)); sort(all(r));

	bool print_max = false;

	for (int i = 0; i < M; i++) { 
		if (l[i] > r[i]){ 
			print_max = true;
			break;
		}
		else segtree.update(l[i], r[i]);
	}

	vector<tuple<int, int>> queries(Q);

	for (int i = 0; i < Q; i++) { 
		int c, d;
		cin >> c >> d;
		queries[i] = { c, d };
	}

	if (print_max) { 
		for (int j = 0; j < Q; j++) cout << 1000000000 << '\n';
		return 0;
	}

	multiset<int> s;

	for (int i = 1; i <= N; i++) { 
		if (segtree.query(i)) s.emplace(a[i]);
	}

	for (int i = 0; i < Q; i++) { 
		auto [c, d] = queries[i];

		if (c != d) { 
			if (segtree.query(c)) s.erase(s.lower_bound(a[c]));
			if (segtree.query(d)) s.erase(s.lower_bound(a[d]));

			swap(a[c], a[d]);

			if (segtree.query(c)) s.emplace(a[c]);
			if (segtree.query(d)) s.emplace(a[d]);
		}

		cout << *s.rbegin() << '\n';
	}
}
