#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int INF = 99999;

int main() {
	fastio;

	int N;
	cin >> N;

	vector<int> A(N);
	vector<int> cnt(N, INF);
	for (int i = 0; i < N; i++) cin >> A[i];
	
	int a, b;
	cin >> a >> b;
	a--; b--;

	cnt[a] = 0;
	queue<int> q;
	q.emplace(a);

	while (!q.empty()) {
		int front = q.front();
		q.pop();

		for (int i = front + A[front]; i < N; i += A[front]) {
			if (cnt[i] != INF) continue;
			cnt[i] = cnt[front] + 1;

			q.emplace(i);
		}

		for (int i = front - A[front]; i >= 0; i -= A[front]) {
			if (cnt[i] != INF) continue;
			cnt[i] = cnt[front] + 1;

			q.emplace(i);
		}
	}

	if (cnt[b] != INF) cout << cnt[b];
	else cout << -1;

}
