#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
char buffer[11];
ll cnt[1 << 10], ans;

int main() {
	int N, K;
	scanf("%d%d", &N, &K);

	for (int i = 0; i < N; i++) {
		scanf("%s", buffer);
		int flag = 0;

		for (int j = 0; j < 10; j++) {
			flag |= 1 << (buffer[j] - '0');
		}
		cnt[flag]++;
	}

	for (int i = 0; i < 1 << 10; i++) {

		for (int j = i; j < 1 << 10; j++) {
			if (!cnt[i] || !cnt[j]) continue;
			int flag = i | j, c = 0;
			for (int k = 0; k < 10; k++) c += ((flag & (1 << k)) != 0);

			if (c == K) {
				if (i == j) ans += cnt[i] * (cnt[i] - 1) / 2;
				else ans += cnt[i] * cnt[j];
			}
		}
	}

	printf("%lld", ans);

}