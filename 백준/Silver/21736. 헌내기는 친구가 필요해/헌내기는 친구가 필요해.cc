#include <iostream>
#include <queue>
using namespace std;

const int MAX_N = 600;
int N, M;
char campus[MAX_N][MAX_N + 1];
pair<int, int> start;

queue<pair<int, int>> q;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++){
		scanf("%s", campus[i]);
		for (int j = 0; j < M; j++){
			if (campus[i][j] == 'I') {
				q.push({i, j});
				campus[i][j] = 'X';
			}
		}
	}

	int ans = 0;

	while (!q.empty()){
		pair<int, int> front = q.front();
		q.pop();
		
		int x = front.first, y = front.second;

		for (int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
			if (campus[nx][ny] == 'X') continue;
			if (campus[nx][ny] == 'P') ans++;
			campus[nx][ny] = 'X';
			q.push({nx, ny});
		}
	}

	if (ans) printf("%d", ans);
	else printf("TT");
}