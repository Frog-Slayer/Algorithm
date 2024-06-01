#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAX_N = 1000000;

int N, M;
int A[MAX_N], cnt[MAX_N];

vector<tuple<int, int, int>> queries;
vector<int> ans;
vector<int> compress;

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		scanf("%d", &A[i]);
		compress.push_back(A[i]);
	}

	sort(compress.begin(), compress.end());
	compress.erase(unique(compress.begin(), compress.end()), compress.end());

	for (int i = 0; i < N; i++){
		A[i] = lower_bound(compress.begin(), compress.end(), A[i]) - compress.begin();
	}

	scanf("%d", &M);
	ans.resize(M);

	for (int q = 0; q < M; q++){
		int i, j;
		scanf("%d%d", &i, &j);
		queries.emplace_back(q, i-1, j-1);
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

	int distinct_count = 0;

	for (int i = s; i <= e; i++){
		cnt[A[i]]++;
		if (cnt[A[i]] == 1) distinct_count++;
	}

	ans[idx] = distinct_count;

	for (int i = 1; i < M; i++){
		tie(idx, s, e) = queries[i];
		while (left > s) {
			if (++cnt[A[--left]] == 1) distinct_count++;
		}

		while (left < s) {
			if (--cnt[A[left++]] == 0) distinct_count--;
		}

		while (right > e) {
			if (--cnt[A[right--]] == 0) distinct_count--;

		}

		while (right < e) {
			if (++cnt[A[++right]] == 1) distinct_count++;
		}

		ans[idx] = distinct_count;
	}

	for (int a : ans) printf("%d\n", a);

}