#include <iostream>
#include <queue>
using namespace std;

int N, M;
char maze[100][101];
int dist[100][100];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

queue<pair<int, int>> q;

int main(){
	scanf("%d%d", &M, &N);

	for (int i = 0; i < N; i++) {
		scanf("%s", maze[i]);
		for (int j = 0; j < M; j++) dist[i][j] = 100000;
	}

	q.push({0, 0});
	dist[0][0] = 0;

	while (!q.empty()){
		pair<int, int> front = q.front();
		q.pop();

		int x = front.first, y = front.second;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

			if (maze[nx][ny] == '0') {
				if (dist[nx][ny] <= dist[x][y]) continue;
				dist[nx][ny] = dist[x][y];
				q.push({nx, ny});
			}
			else {
				if (dist[nx][ny] <= dist[x][y] + 1) continue;
				dist[nx][ny] = dist[x][y] + 1; 
				q.push({nx, ny});
			}

		}
	}

	printf("%d", dist[N-1][M-1]);


}