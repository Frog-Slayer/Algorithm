#include <iostream>
using namespace std;

const int MAX_N = 100000;
bool is_prime[MAX_N + 1];
int cnt[MAX_N + 1];

int main() {
	for (int i = 2; i < MAX_N + 1; i++) is_prime[i] = true;

	for (int i = 2; i < MAX_N + 1; i++) {
		if (!is_prime[i]) continue;

		for (int j = i * 2; j < MAX_N + 1; j += i) {
			is_prime[j] = false;
			int k = j;
			while (k % i == 0) {
				cnt[j]++;
				k /= i;
			}
		}
	}

	int A, B;
	scanf("%d%d", &A, &B);

	int ans = 0;
	for (int i = A; i <= B; i++) {
		ans += is_prime[cnt[i]];
	}

	printf("%d", ans);
}