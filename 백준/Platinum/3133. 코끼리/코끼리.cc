#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int MOD = 1000000007;
int N;
unordered_map<int, vector<int>> plants;
vector<int> xx, yy;

struct Node {
	int len;
	int cnt;

	Node operator+(const Node& rhs) {
		if (len != rhs.len) return max(rhs); 
		return {len, (cnt + rhs.cnt) % MOD};
	}

	Node max(const Node& rhs) {
		if (len < rhs.len) return rhs;
		return *this;
	}
};

vector<Node> tree;

void update(int node, int start, int end, int left, int right, Node val) {
	if (right < start || end < left) return;
	if (start == end) {
		tree[node] = tree[node] + val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int idx, Node val) {
	update(1, 1, yy.size(), idx, idx, val);
}

Node query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return {0, 0};
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

Node query(int left, int right) {
	return query(1, 1, yy.size(), left, right);
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		xx.emplace_back(x);
		yy.emplace_back(y);
		plants[x].emplace_back(y);
	}

	sort(yy.begin(), yy.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());

	tree.resize(yy.size() * 4 + 4);

	sort(xx.begin(), xx.end());
	xx.erase(unique(xx.begin(), xx.end()), xx.end());

	for (int x : xx) {
		vector<int> &v = plants[x];
		sort(v.begin(), v.end(), greater());
	
		for (int &y : v) {
			y = lower_bound(yy.begin(), yy.end(), y) - yy.begin() + 1;
			Node q = query(1, y - 1);
			update(y, {q.len + 1, max(q.cnt, 1)});
		}
	}

	printf("%d\n%d", tree[1].len, tree[1].cnt);

}