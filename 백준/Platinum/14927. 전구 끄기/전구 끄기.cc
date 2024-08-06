#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 18;
int N, bulb[MAX_N][MAX_N], tmp[MAX_N][MAX_N];
int dx[] = {-1, 0, 0, 0, 1}, dy[] = {0, -1, 0, 1, 0};

void toggle(int i, int j, int tmp[MAX_N][MAX_N]){
	for (int d = 0; d < 5; d++) {
		int x = i + dx[d], y = j + dy[d];
		if (x < 0 || x >= N || y < 0 || y >= N) continue;
		tmp[x][y] = 1 - tmp[x][y];
	}
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) scanf("%d", &bulb[i][j]);
	}

	int ans = 1e9;

	for (int i = 0; i < (1 << N); i++) {
		int cnt = 0;
		for (int k = 0; k < N; k++) for (int l = 0; l < N; l++) tmp[k][l] = bulb[k][l];

		for (int j = 0; j < N; j++) {
			if (i & (1 << j)){
				cnt++;
				toggle(0, j, tmp);
			}
		}

		for (int j = 1; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (tmp[j - 1][k]) {
					cnt++;
					toggle(j, k, tmp);
				}
			}
		}

		int cur = 0;
		for (int k = 0; k < N; k++) for (int l = 0; l < N; l++) cur += tmp[k][l];

		if (!cur) ans = min(ans, cnt);
	}

	printf("%d", ans == 1e9 ? -1 : ans);
}
