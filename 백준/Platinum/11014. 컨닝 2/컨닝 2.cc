#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 80, MAXM = 81;	
int N, M;
vector<vector<int>> task;
char seats[MAXN][MAXM + 1];
bool visited[MAXN * MAXM + 1];
int by[MAXN * MAXM + 1];
int seatCnt;
int idx[MAXN][MAXM];
int dir[6][2] = {{-1, -1}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}, {1, 1}};

bool match(int a){
	if (visited[a]) return false;
	visited[a] = true;
	for (int possibleTask : task[a]){
		if (!by[possibleTask] || match(by[possibleTask])){
			by[possibleTask] = a;
			return true;
		}
	}
	return false;
} 

int main(){
	int C;
	scanf("%d", &C);

	while (C--){
		seatCnt = 0;
		for (int i = 0; i <= N * M; i++) visited[i] = by[i] = 0;

		scanf("%d%d", &N, &M);
		task.clear();
		task.resize(N * M + 1);

		for (int i = 0; i < N; i++) {
			scanf("%s", seats[i]);
			for (int j = 0; j < M; j++) {
				if (seats[i][j] == '.') idx[i][j] = ++seatCnt;
			}
		}

		for (int i = 0; i < N; i++){
			for (int j = 0; j < M; j += 2){
				if (seats[i][j] == '.') {
					for (int d = 0; d < 6; d++) {
						int x = i + dir[d][0];
						int y = j + dir[d][1];

						if (x < 0 || x >= N || y < 0 || y >= M) continue;
						if (seats[x][y] == 'x') continue;

						task[idx[i][j]].push_back(idx[x][y]);
					}
				}
			}
		}
		
		int ans = 0;
		for (int i = 1; i <= seatCnt; i++){
			for (int j = 0; j <= seatCnt; j++) visited[j] = false;
			if (match(i)) ans++;
		}

		printf("%d\n", seatCnt - ans);
	}
}