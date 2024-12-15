#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

struct Segtree {
	int N;
	vector<ll> tree, lazy;

	Segtree(int N) : N(N), tree(4 * N), lazy(4 * N) {}

	void propagate(int node, int start, int end) {
		if (!lazy[node]) return;
		tree[node] += lazy[node] * (end - start + 1);

		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
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

	ll query(int node, int start, int end, int left, int right) {
		propagate(node, start, end);
		if (right < start || end < left) return 0 ;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

};

int to_sec(string s) {
	int hh = stoi(s.substr(0, 2));
	int mm = stoi(s.substr(3, 2));
	int ss = stoi(s.substr(6, 8));

	return hh * 3600 + mm * 60 + ss;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<tuple<int, int>> v;

	for (int i = 0; i < N; i++) {
		vector<string> interval(3);
		for (int j = 0; j < 3; j++) cin >> interval[j];

		int s = to_sec(interval[0]), e = to_sec(interval[2]);
		v.emplace_back(s, e);
	}

	Segtree tree(86400);

	for (auto &[s, e] : v) {
		if (s <= e) tree.update(1, 0, 86399, s, e);
		else {
			tree.update(1, 0, 86399, s, 86399);
			tree.update(1, 0, 86399, 0, e);
		}
	}
	
	int Q;
	cin >> Q;

	for (int i = 0; i < Q; i++) {
		vector<string> interval(3);
		for (int j = 0; j < 3; j++) cin >> interval[j];

		int s = to_sec(interval[0]), e = to_sec(interval[2]);
		int diff = e - s + 1; 
		if (e < s) diff += 86400;

		ll q = 0;
		if (s <= e) q += tree.query(1, 0, 86399, s, e);
		else {
			q += tree.query(1, 0, 86399, s, 86399);
			q += tree.query(1, 0, 86399, 0, e);
		}

		cout << fixed << setprecision(10) << (double)q / diff << '\n'; 
	}
}