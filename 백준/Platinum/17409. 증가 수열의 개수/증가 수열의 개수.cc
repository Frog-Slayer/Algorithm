#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAX_N = 100000;
const int MOD = 1e9 + 7;
const int MAX_K = 10;
int N, K;

int tree[MAX_K + 1][MAX_N * 4 + 4];

void update(int k, int node, int start, int end, int left, int right, int val) {
	if (right < start || end < left) return;
	if (start == end) {
		tree[k][node] += val;
		tree[k][node] %= MOD;
		return;
	}

	int mid = (start + end) / 2;
	update(k, node * 2, start, mid, left, right, val);
	update(k, node * 2 + 1, mid + 1, end, left, right, val);

	tree[k][node] = tree[k][node * 2] + tree[k][node * 2 + 1];
	tree[k][node] %= MOD;
}

int query(int k, int node, int start, int end, int left, int right){
	if (right < start || end < left) return 0 ;
	if (left <= start && end <= right) return tree[k][node]; 

	int mid = (start + end) / 2;
	return (query(k, node * 2, start, mid, left, right) + query(k, node * 2 + 1, mid + 1, end, left, right)) % MOD;
}

int main() {
	scanf("%d%d", &N, &K);

	for (int i = 0; i < N; i++) {
		int A;
		scanf("%d", &A);

		for (int k = 1; k <= K; k++) {
			int q = query(k - 1, 1, 1, N, 1, A - 1); 
			update(k, 1, 1, N, A, A, q);
		}
		update(1, 1, 1, N, A, A, 1);
	}

	printf("%d", query(K, 1, 1, N, 1, N));

}