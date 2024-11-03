#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define lb(x) lower_bound(all(total_quest), x) - total_quest.begin()
#define ub(x) upper_bound(all(total_quest), x) - total_quest.begin()

vector<int> total_quest;

struct Segtree {
	int N;
	vector<int> tree;

	Segtree(int _N) : N(_N), tree(4 * _N) {}

	void update(int node, int start, int end, int idx) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node]++;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx);
		update(node * 2 + 1, mid + 1, end, idx);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx) {
		update(1, 0, N - 1, lb(idx));
	}

	int query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];

		int mid = (start + end) / 2;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}

	int query(int left, int right) {
		return (right - left + 1) - query(1, 0, N - 1, lb(left), ub(right) - 1);
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> quests;

	for (int i = 0; i < N; i++) {
		int Q;
		cin >> Q;
		quests.emplace_back(Q);
		total_quest.emplace_back(Q);
	}

	int M;
	cin >> M;

	vector<tuple<int, int, int>> queries;

	for (int i = 0; i < M; i++) {
		int cmd;
		cin >> cmd;

		if (cmd == 1) {
			int X;
			cin >> X;
			total_quest.emplace_back(X);
			queries.emplace_back(1, X, 0);
		}
		else {
			int L, R;
			cin >> L >> R;
			queries.emplace_back(2, L, R);
		}
	}

	sort(all(total_quest));

	Segtree tree(total_quest.size());

	for (auto &q : quests) tree.update(q);

	for (auto &[cmd, param1, param2] : queries) {
		if (cmd == 1) tree.update(param1);
		else {
			cout << tree.query(param1, param2) << '\n';
		}
	}
}