#include <iostream>
using namespace std;

int N;
char buffer[21];
int as_bit[20];

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%s", buffer);

		for (int j = 0; j < N; j++) if (buffer[j] == 'H') as_bit[i] |= (1 << j);
	}

	int ans = 0;
	for (int i = 1; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) if (i & (1 << j)) as_bit[j] = ~as_bit[j]; 

		int sum = 0;
		for (int j = 0; j < N; j++) {
			int cnt = 0;
			for (int k = 0; k < N; k++) cnt += (as_bit[k]) & (1 << j) ? 1 : 0;
			if (cnt > N / 2) sum += cnt;
			else sum += (N - cnt);
		}

		for (int j = 0; j < N; j++) if (i & (1 << j)) as_bit[j] = ~as_bit[j]; 
		ans = max(ans, sum);
	}

	printf("%d", N * N - ans);
}