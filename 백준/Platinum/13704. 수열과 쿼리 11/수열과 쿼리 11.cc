#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

const int MAX_N = 100000;
int N, K, M;
long long cur;
vector<int> A;
vector<long long> cnt(1 << 20), ans;
vector<tuple<int, int, int>> queries;

int main() {
	scanf("%d%d", &N, &K);

	A.resize(N + 1);
	
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		A[i] ^= A[i - 1];
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		queries.emplace_back(i, l - 1, r);
	}

	ans.resize(M);

	int k = sqrt(N);

	sort(queries.begin(), queries.end(), [k](auto &q1, auto& q2) {
			auto &[i1, s1, e1] = q1;
			auto &[i2, s2, e2] = q2;

			if (s1/k == s2/k) return e1 < e2;
			return s1/k < s2/k;
			});

	
	int left = get<1>(queries[0]), right = left - 1;

	for (int i = 0; i < M; i++){
		auto& [idx, s, e] = queries[i];
		ans[idx] = cur;

		while (s < left) {
			cur += cnt[A[--left] ^ K];
			cnt[A[left]]++;
		}

		while (s > left) {
			cnt[A[left]]--;
			cur -= cnt[A[left++] ^ K];
		}

		while (e > right) {
			cur += cnt[A[++right] ^ K];
			cnt[A[right]]++;
		}

		while (e < right) {
			cnt[A[right]]--;
			cur -= cnt[A[right--] ^ K];
		}

		ans[idx] = cur;
	}

	for (long long a : ans) printf("%lld\n", a);
}
