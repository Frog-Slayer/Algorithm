#include <iostream>
using namespace std;

int N, M;
char A[50][51], B[50][51];

void flip(int x, int y) {
	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			A[i][j] = A[i][j] == '0' ? '1' : '0';
		}
	}
}

int main() {
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%s", A[i]);
	}

	for (int i = 0; i < N; i++) {
		scanf("%s", B[i]);
	}

	int ans = 0;
	if (N >= 3 && M >= 3) {
		for (int i = 0; i < N - 2; i++) { 
			for (int j = 0; j < M - 2; j++) {
				if (A[i][j] != B[i][j]) {
					flip(i, j);
					ans++;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (A[i][j] != B[i][j]){
				ans = -1;
				break;
			}
		}

		if (ans < 0) break;
	}

	printf("%d", ans);
}