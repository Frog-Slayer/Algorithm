#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAX_N = 2000;
int A[MAX_N];
map<int, int> sum, cnt;

bool is_good(int i) {
	if (sum.find(A[i]) != sum.end()) {
		return sum[A[i]] > cnt[0] - (A[i] == 0);
	}
	return false;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		cnt[A[i]]++;
	}

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (i == j) continue;
			sum[A[i] + A[j]]++;
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans += is_good(i);
	}

	printf("%d", ans);
}