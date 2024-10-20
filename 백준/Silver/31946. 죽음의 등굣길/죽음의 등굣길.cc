#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;
	int N, M;
	
	cin >> N >> M;

	vector<vector<int>> block(N, vector<int>(M));
	vector<vector<bool>> visited(N, vector<bool>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> block[i][j];
		}
	}

	int X;
	cin >> X;

	queue<pair<int, int>> q;

	q.push({0, 0});
	visited[0][0] = true;

	while (!q.empty()) {
		pair<int, int> front = q.front();
		q.pop();

		for (int i = -X; i <= X; i++) {
			for (int j = -X; j <= X; j++) {
				if (abs(i) + abs(j) > X) continue;
				int nx = front.first + i, ny = front.second + j;
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (visited[nx][ny]) continue;
				if (block[nx][ny] != block[front.first][front.second]) continue;

				visited[nx][ny] = true;
				q.push({nx, ny});
			}
		}
	}

	if (visited[N - 1][M - 1]) cout << "ALIVE";
	else cout << "DEAD";

}