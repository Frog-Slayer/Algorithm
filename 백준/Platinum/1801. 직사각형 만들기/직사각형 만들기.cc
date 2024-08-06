#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int same_length[(1 << 16)];
vector<int> sticks;

void dp(int state, int idx, int left, int right) {
	if (left == right) same_length[state] = max(left, same_length[state]);
	if (idx == N) return;

	int len = sticks[idx];

	dp(state | (1 << idx), idx + 1, left + len, right);
	dp(state | (1 << idx), idx + 1, left, right + len); 
	dp(state, idx + 1, left, right);
}

int main() {
	scanf("%d", &N);
	sticks.resize(N);

	for (int i = 0; i < N; i++) scanf("%d", &sticks[i]);

	dp(0, 0, 0, 0);

	for (int i = 0; i < 1 << N; i++) {
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) same_length[i] = max(same_length[i], same_length[i ^ (1 << j)]);
		}
	}

	int ans = 0;

	for (int i = 0; i < (1 << N); i++) {
		int a = same_length[i];
		int b = same_length[(~i) & ((1 << N) - 1)];
		
		ans = max(ans, a * b);
	}

	printf("%d", ans ? ans : -1);

}