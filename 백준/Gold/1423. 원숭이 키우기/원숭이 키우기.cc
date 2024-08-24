#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
int N, D;
vector<int> num, power;
ll sum, dp[101];

int main() {
	scanf("%d", &N);
	num.resize(N);
	power.resize(N);

	for (int i = 0; i < N; i++) scanf("%d", &num[i]);

	for (int i = 0; i < N; i++) {
		scanf("%d", &power[i]);
		sum += (ll) num[i] * power[i];
	}

	scanf("%d", &D);

	for (int i = 0; i < N; i++) num[i] = min(num[i], D);

	for (int level = 0; level < N; level++) {
		for (int j = 0; j < num[level]; j++) {
			for (int d = D; d >= 0; d--) {
				for (int up = level + 1; up < N && up - level + d <= D; up++) {
					dp[up - level + d] = max(dp[up - level + d], dp[d] + power[up] - power[level]);
				}
			}
		}
	}

	printf("%lld", dp[D] + sum);
}