#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int ans = 200;
vector<bool> v(25, 0);
vector<pair<int, int>> p;
char board[5][6];

int manhattan(pair<int, int> p1, pair<int, int> p2) {
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void solve() {
	vector<pair<int, int>> tmp;
	for (int i = 0; i < 25; i++) if (v[i]) tmp.emplace_back(i / 5, i % 5);

	queue<pair<int, int>> q;
	q.push(tmp[0]);
	int visited = 1;

	while (!q.empty()) {
		pair<int, int> front = q.front();
		q.pop();

		for (int i = 0; i < tmp.size(); i++) {
			if (visited & (1 << i)) continue;
			if (manhattan(front, tmp[i]) == 1){
				visited |= (1 << i);
				q.push(tmp[i]);
			}
		}
	}

	if (visited != (1 << tmp.size()) - 1) return;

	do {
		int sum = 0;
		for (int i = 0; i < p.size(); i++) {
			sum += manhattan(p[i], tmp[i]);
		}

		ans = min(ans, sum);
	} while(next_permutation(tmp.begin(), tmp.end()));
}

int main() {
	for (int i = 0; i < 5; i++) {
		scanf("%s", board[i]);
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == '*'){
				p.emplace_back(i, j);
			}
		}
	}

	for (int i = 0; i < p.size(); i++) v[24 - i] = 1;

	do {
		solve();
	} while (next_permutation(v.begin(), v.end()));

	printf("%d", ans);
}