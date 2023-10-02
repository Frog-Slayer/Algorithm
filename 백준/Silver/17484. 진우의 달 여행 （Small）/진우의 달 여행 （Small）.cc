#include <iostream>
using namespace std;

const int MAXNM = 6;

int N, M, ans = 666;
int fuel[MAXNM][MAXNM];

int move(int col, int row, int prevDirection, int sum){
	if (row == N) return sum;
	int ret = 666;
	for (int i = -1; i <= 1; i++){
		if (i == prevDirection) continue;
		if (col + i < 0 || col + i >= M) continue;
		ret = min(ret, move(col + i, row + 1, i, sum + fuel[row][col]));	
	}
	return ret;	
}

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			scanf("%d", &fuel[i][j]);
		}
	}

	for (int i = 0; i < M; i++){
		ans = min(ans, move(i, 0, -2, 0));
	}

	printf("%d", ans);
}