#include <iostream>
using namespace std;

const int MAXN = 250;
int N, B, K;
int mat[MAXN + 1][MAXN + 1];
int minElem[MAXN + 1][MAXN + 1], maxElem[MAXN + 1][MAXN + 1];

int main(){
	scanf("%d%d%d", &N, &B, &K);

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			scanf("%d", &mat[i][j]);
			minElem[i][j] = MAXN;
		}
	}

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N - B + 1; j++){
			int m = MAXN, M = 0;

			for (int k = 0; k < B; k++){
				m = min(m, mat[i][j + k]);
				M = max(M, mat[i][j + k]);
			}

			minElem[i][j] = m;
			maxElem[i][j] = M;
		}
	}


	for (int k = 0; k < K; k++){
		int row, col;
		scanf("%d%d", &row, &col);

		int M = 0, m = MAXN;
		for (int j = row; j < row + B; j++){
			M = max(M, maxElem[j][col]);
			m = min(m, minElem[j][col]);
		}

		printf("%d\n", M - m);
	}

}