#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <tuple>
using namespace std;

typedef long long ll;
const int MAX_N = 1e5;
const int MAX_K = 1e5;

int N, K, M;
int A[MAX_N + 1];

vector<tuple<int, int, int>> queries;
vector<ll> ans;
ll sum = 0;

int fenwick[MAX_K + 1];

void update(int idx, int val){
	while (idx <= MAX_K) {
		fenwick[idx] += val;
		idx += (idx & -idx);
	}
}

int query(int idx) {
	idx = max(idx, 0);
	idx = min(idx, MAX_K);

	int ret = 0;
	while (idx > 0) {
		ret += fenwick[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

void expand(int num){
	sum += query(num + K) - query(num - K - 1);
	update(num, 1);
}

void shrink(int num){
	update(num, -1);
	sum -= query(num + K) - query(num - K - 1);
}

int main(){
	scanf("%d%d", &N, &K);

	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
	}

	scanf("%d", &M);
	ans.resize(M);

	for (int q = 0; q < M; q++){
		int i, j;
		scanf("%d%d", &i, &j);
		queries.emplace_back(q, i, j);
	}

	int k = sqrt(N);

	sort(queries.begin(), queries.end(), [k](tuple<int, int, int>  &a, tuple<int, int, int>  &b) {
			int s1 = get<1>(a), e1 = get<2>(a), s2 = get<1>(b), e2 = get<2>(b);
			if (s1/k < s2/k) return true;
			return (s1/k  == s2/k && e1 < e2);
		});

	int idx, s, e;
	tie(idx, s, e) = queries[0];
	int left = s, right = e;

	for (int i = s; i <= e; i++){
		expand(A[i]);
	}
	ans[idx] = sum;
	
	for (int i = 1; i < M; i++){
		tie(idx, s, e) = queries[i];
		while (left > s) expand(A[--left]);

		while (left < s) shrink(A[left++]); 

		while (right > e) shrink(A[right--]);

		while (right < e) expand(A[++right]);

		ans[idx] = sum;
	}

	for (int i = 0; i < M; i++) printf("%lld\n", ans[i]);
}