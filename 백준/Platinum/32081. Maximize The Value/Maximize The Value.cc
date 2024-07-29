#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long ll;
const ll INF = 1e11;
int N, M, Q;
vector<ll> ans;
unordered_map<int, vector<pair<int, int>>> L, R;
unordered_map<int, vector<tuple<int, int, int>>> queries;

struct Node{
    ll left = 0;
    ll right = 0;
    ll total = 0;
    ll sum = 0;
};

vector<Node> tree;

void update(int node, int start, int end, int idx, int val) {
    if (end < idx || idx < start) return;
    if (start == end) {
        tree[node].left = val;
        tree[node].right = val;
        tree[node].sum = val;
        tree[node].total = val;
        return;
    }

	int mid = (start + end) / 2;

	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	Node& left_sub = tree[node * 2];
	Node& right_sub = tree[node * 2 + 1];

    Node& ret = tree[node];
	ret.left = max(left_sub.left, left_sub.sum + right_sub.left); 
	ret.right = max(right_sub.right, right_sub.sum + left_sub.right);
    ret.sum = left_sub.sum + right_sub.sum;
	ret.total = max({ret.left, ret.right, left_sub.total, right_sub.total, left_sub.right + right_sub.left});
}

Node query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return { -INF, -INF, -INF, 0};
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end)/2;
	Node left_sub = query(node * 2, start, mid, left, right); 
	Node right_sub = query(node * 2 + 1, mid + 1, end, left, right); 

    Node ret;
	ret.left = max(left_sub.left, left_sub.sum + right_sub.left); 
	ret.right = max(right_sub.right, right_sub.sum + left_sub.right);
    ret.sum = left_sub.sum + right_sub.sum;

	ret.total = max({ret.left, ret.right, left_sub.total, right_sub.total, left_sub.right + right_sub.left});

	return ret;
}

int main() {
	scanf("%d%d", &N, &M);
	tree.resize(M * 4 + 4);

	for (int i = 1; i <= M; i++) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		L[l].emplace_back(i, x);
		R[r].emplace_back(i, x);
	}

	scanf("%d", &Q);

	ans.resize(Q);

	for (int i = 0; i < Q; i++) {
		int k, s, t;
		scanf("%d%d%d", &k, &s, &t);
		queries[k].emplace_back(s, t, i);
	}

	for (int i = 0; i < N; i++) {
		for (auto &p : R[i]) {
			update(1, 1, M, p.first, 0);
		}

		for (auto &p : L[i + 1]) {
			update(1, 1, M, p.first, p.second);
		}

		for (auto &q : queries[i + 1]) {
			int s, t, idx;
			tie(s, t, idx) = q;
			ans[idx] = query(1, 1, M, s, t).total;
		}
	}

	for (int i = 0; i < Q; i++) printf("%lld\n", ans[i]);
}