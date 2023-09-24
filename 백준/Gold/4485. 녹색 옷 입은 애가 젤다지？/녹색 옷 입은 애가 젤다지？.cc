#include <iostream>
#include <queue>
using namespace std;


const int MAX_N = 125;
const int INF = 2144444444;

typedef pair<int, pair<int, int>> POINT;

int N, t;
int cave[MAX_N][MAX_N];
int cost[MAX_N][MAX_N];
priority_queue<POINT, vector<POINT>, greater<>> pq;

int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1 ,0}};

int main(){
	while (true){
		scanf("%d", &N);
		t++;
		if (!N) break;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				scanf("%d", &cave[i][j]);
				cost[i][j] = INF;
			}
		}

		cost[0][0] = cave[0][0];
		pq.push({0, {0, 0}});

		while (!pq.empty()){
			POINT top= pq.top();
			pq.pop();

			int x = top.second.first;
			int y = top.second.second;

			for (int i = 0; i < 4; i++){
				int nx = x + d[i][0];
				int ny = y + d[i][1];

				if (nx <0 || ny < 0 || nx >= N || ny >= N) continue;
				if (cost[nx][ny] <= cost[x][y] + cave[nx][ny]) continue;

				cost[nx][ny] = cost[x][y] + cave[nx][ny];
				pq.push({cave[nx][ny], {nx, ny}});
			}
		}
		printf("Problem %d: %d\n", t, cost[N-1][N-1]);
	}
}