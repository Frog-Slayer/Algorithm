#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

const int MAX_N = 250000;
int N, M;
char buffer[MAX_N + 1];
int tree[10][MAX_N * 4 + 4], lazy[MAX_N * 4 + 4];

void propagate(int node, int start, int end) {
	if (lazy[node]) {
		lazy[node] %= 10;
	
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		int tmp[10];
		for (int i = 0; i < 10; i++) tmp[i] = tree[i][node];
		for (int i = 0; i < 10; i++) tree[(i + lazy[node]) % 10][node] = tmp[i];
		lazy[node] = 0;
	}
}

void shift(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		lazy[node]++;
		propagate(node, start, end);
		return;
	}

	int mid = (start + end) >> 1;
	shift(node * 2, start, mid, left, right);
	shift(node * 2 + 1, mid + 1, end, left, right);
	for (int i = 0; i < 10; i++) {
		tree[i][node] = tree[i][node * 2] + tree[i][node * 2 + 1];
	}
}

void shift(int left, int right) {
	shift(1, 1, N, left, right);
}

void update(int tree_no, int node, int start, int end, int idx){
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[tree_no][node]++;
		return;
	}

	int mid = (start + end) >> 1;
	update(tree_no, node * 2, start, mid, idx);
	update(tree_no, node * 2 + 1, mid + 1, end, idx);
	tree[tree_no][node] = tree[tree_no][node * 2] + tree[tree_no][node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0 ;
	if (left <= start && end <= right) {
		int ret = 0;
		for (int i = 0; i < 10; i++) ret += i * tree[i][node]; 
		return ret;
	}
	
	int mid = (start + end) >> 1;
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
	scanf("%d%d", &N, &M);
	scanf("%s", buffer);
	
	for (int i = 0; i < N; i++) {
		update(buffer[i] - '0', 1, 1, N, i + 1);
	}

	for (int i = 0; i < M; i++) {
		int A, B;
		scanf("%d%d", &A, &B);
		printf("%d\n", query(1, 1, N, A, B));
		shift(A, B);
	}
}