#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

int block[1000][1000], cnt[1000][1000];
queue<tuple<int, int>> q;

int main() { 
	fastio;

	int R, C;
	cin >> R >> C;

	for (int i = 0; i < R; i++) { 
		for (int j = 0; j < C; j++) { 
			cin >> block[i][j];
			if (block[i][j]) { 
				if (i) cnt[i][j] = INT_MAX;
				else q.emplace(0, j);
			}
		}
	}


	int N;
	cin >> N;

	vector<tuple<int, int>> rules;

	for (int i = 0; i < N; i++) { 
		int r, c;
		cin >> r >> c;
		rules.emplace_back(r, c);
	}

	int ans = INT_MAX;

	while (!q.empty()) { 
		auto [i, j] = q.front();
		if (i == R - 1) { 
			ans = min(ans, cnt[i][j]);
			break;
		}
		q.pop();

		for (auto &[r, c] : rules) { 
			int nx = i + r, ny = j + c;
			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (!block[nx][ny]) continue;
			if (cnt[nx][ny] <= cnt[i][j] + 1) continue;
			cnt[nx][ny] = cnt[i][j] + 1;
			q.emplace(nx, ny);
		}
	}

	cout << (ans == INT_MAX ? -1 : ans);
}
