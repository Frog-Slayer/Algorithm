#include <iostream>
using namespace std;

int mcn[30][30];

int main(){
	int T, N, M;

	scanf("%d", &T);
	for (int i = 1; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (j > i) continue;
			else if (j == i || j == 0) mcn[i][j] = 1;
			else {
				mcn[i][j] = mcn[i - 1][j - 1] + mcn[i - 1][j];
			}


		}


	}
	while (T--) {
		scanf("%d%d", &N, &M);


		printf("%d\n", mcn[M][N]);
	}

}