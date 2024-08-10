#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee{
	int id;
	int pay;
	int time;

	Employee(int a, int b, int c) : id(a), pay(b), time(c) {}

	bool operator<(const Employee &rhs) {
		if (time == rhs.time) return pay < rhs.pay;
		return time < rhs.time;
	}
};

const int INF = 33333;
int N, M;
vector<int> id, pay, pay_to_id, work_time, tree, cnt, boss;
vector<vector<int>> adj;
vector<Employee> employees;

void init() {
	tree.resize(4 * N + 4);
	adj.resize(N + 1);
	boss.resize(N + 1);
	cnt.resize(N + 1);
}

void compress(vector<int> &v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

void update(int node, int start, int end, int left, int right, int val) {
	if (right < start || end < left) return;
	if (start == end){
		tree[node] = val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);
	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return 0;
	if (start == end) return tree[node];

	int mid = (start + end) / 2;
	int l = query(node * 2, start, mid, left, right);
	if (l) return l;
	return query(node * 2 + 1, mid + 1, end, left, right);
}

void make_tree(int node) {
	cnt[node]++;
	for (int &child : adj[node]) {
		make_tree(child);
		cnt[node] += cnt[child];
	}
};

int main() {
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		id.emplace_back(a);
		pay.emplace_back(b);
		work_time.emplace_back(c);

		employees.emplace_back(a, b, c);
	}

	init();

	compress(id);
	compress(pay);
	compress(work_time);
	sort(employees.begin(), employees.end());
	
	for (int i = N - 1; i >= 0; i--) {
		Employee &e = employees[i];
		int p = lower_bound(pay.begin(), pay.end(), e.pay) - pay.begin();
		int idx = lower_bound(id.begin(), id.end(), e.id) - id.begin() + 1;
		int q = query(1, 0, N, p, N);

		update(1, 0, N, p, p, idx);
		boss[idx] = id[q - 1];
		adj[q].push_back(idx);
	}

	make_tree(0);

	for (int i = 0; i < M; i++) {
		int q;
		scanf("%d", &q);
		q = lower_bound(id.begin(), id.end(), q) - id.begin() + 1;
		
		printf("%d %d\n", boss[q], cnt[q] - 1);
	}
}

