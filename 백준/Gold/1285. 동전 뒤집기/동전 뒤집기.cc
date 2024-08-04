#include <iostream>
using namespace std;

int N;
char coins[20][21];

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%s", coins[i]);
	}

	int ans = 0;
	for (int i = 1; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				for (int k = 0; k < N; k++) coins[j][k] = coins[j][k] == 'T' ? 'H' : 'T';
			}
			else for (int k = 0; k < N; k++) coins[j][k] = coins[j][k];
		}

		int sum = 0;
		for (int j = 0; j < N; j++) {
			int cnt = 0;
			for (int k = 0; k < N; k++) cnt += coins[k][j] == 'H';
			if (cnt > N / 2) sum += cnt;
			else sum += (N - cnt);
		}
		ans = max(ans, sum);

		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				for (int k = 0; k < N; k++) coins[j][k] = coins[j][k] == 'T' ? 'H' : 'T';
			}
			else for (int k = 0; k < N; k++) coins[j][k] = coins[j][k];
		}
	}

	printf("%d", N * N - ans);
}