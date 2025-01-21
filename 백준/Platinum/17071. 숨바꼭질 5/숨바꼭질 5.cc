#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int MAX = 500000;

int solve(int N, int K) {
	int t = 1;

	queue<int> q;
	vector<vector<bool>> v(2, vector<bool>(MAX + 1));
	v[0][N] = true;

	q.push(N);

	while (!q.empty()) {
		K += t;

		if (K > MAX) return -1;

		if (v[t & 1][K]) return t;

		int q_size = q.size();

		for (int i = 0; i < q_size; i++) {
			int front = q.front();
			q.pop();

			for (int next : {front - 1, front + 1, front * 2}) {
				if (next == K) return t;
				if (next < 0 || next > MAX) continue;
				if (v[t & 1][next]) continue;
				v[t & 1][next] = true;
				q.push(next);
			}
		}
		t++;
	}

	return -1;
}

int main() {
	fastio;

	int N, K;
	cin >> N >> K;

	if (N == K) cout << 0;
	else cout << solve(N, K);
}