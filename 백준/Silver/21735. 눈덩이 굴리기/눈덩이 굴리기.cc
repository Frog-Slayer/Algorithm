#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int solve(int N, int time, int sz, int pos, vector<int> &a) {
	if (pos > N) return sz;

	sz += a[pos];
	if (pos == N) return sz;
	if (!time) return sz;

	return max(solve(N, time - 1, sz, pos + 1, a), solve(N, time - 1, sz / 2, pos + 2, a));
}

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<int> a(N + 1);

	for (int i = 1; i <= N; i++) cin >> a[i];

	cout << solve(N, M, 1, 0, a);
}
