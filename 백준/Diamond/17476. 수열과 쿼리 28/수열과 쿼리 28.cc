#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef long long ll;
const int MAX_N = 1 << 17;
const ll INF = 1e16;

struct Node {
	Node () {}
	Node(ll m, ll M, ll s) : min(m), max(M), sum(s) {}

	ll min = 0;
	ll max = 0;
	ll sum = 0;

	ll lazy1 = 0;
	ll lazy2 = 0;

	Node operator+(const Node& node) {
		return Node(std::min(min, node.min), std::max(max, node.max), sum + node.sum);
	}
} tree[MAX_N * 2];

void propagate(int node, int start, int end) {
	if (!tree[node].lazy2) { 
		tree[node].min += tree[node].lazy1;
		tree[node].max += tree[node].lazy1;
		tree[node].sum += tree[node].lazy1 * (end - start + 1);

		if (start != end) {
			tree[node * 2].lazy1 += tree[node].lazy1;
			tree[node * 2 + 1].lazy1 += tree[node].lazy1;
		}
	}
	else {
		tree[node].min = tree[node].max = tree[node].lazy1 + tree[node].lazy2;
		tree[node].sum = (end - start + 1) * tree[node].min;
	
		if (start != end) {
			tree[node * 2].lazy1 = tree[node].lazy1;
			tree[node * 2].lazy2 = tree[node].lazy2; 
			tree[node * 2 + 1].lazy1 = tree[node].lazy1;
			tree[node * 2 + 1].lazy2 = tree[node].lazy2;
		}
	}

	tree[node].lazy1 = 0;
	tree[node].lazy2 = 0;
}

void add(int node, int start, int end, int left, int right, ll c){
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		tree[node].lazy1 = c;
		propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;

	add(node * 2, start, mid, left, right, c);
	add(node * 2 + 1, mid + 1, end, left, right, c);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll gauss(ll n) {
	return floor(sqrt(n));
}

void square(int node, int start, int end, int left, int right){
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		ll min_g = gauss(tree[node].min), max_g = gauss(tree[node].max);
		if (min_g == max_g){
			tree[node].lazy2 = min_g;
			propagate(node, start, end);
			return;
		}
		else if (tree[node].min + 1 == tree[node].max){
			tree[node].lazy1 = min_g - tree[node].min;
			propagate(node, start, end);
			return;
		}
	}

	int mid = (start + end) / 2;

	square(node * 2, start, mid, left, right);
	square(node * 2 + 1, mid + 1, end, left, right);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node].sum;

	int mid = (start + end) / 2;

	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}


int main() {
	int N;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		ll A;
		scanf("%lld", &A);
		add(1, 0, MAX_N - 1, i, i, A);
	}

	int Q;
	scanf("%d", &Q);

	for (int i = 0; i < Q; i++) {
		int t, l, r, x;
		scanf("%d%d%d", &t, &l, &r);

		switch (t) {
			case 1:	scanf("%d", &x); add(1, 0, MAX_N - 1, l, r, x);	break;
			case 2: square(1, 0, MAX_N - 1, l, r); break;
			case 3: printf("%lld\n", query(1, 0, MAX_N - 1, l, r));
		}
	}
}

