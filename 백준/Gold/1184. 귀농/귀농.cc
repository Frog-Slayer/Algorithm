#include <iostream>
#include <unordered_map>
using namespace std;

const int MAX_N = 50;
int N, ans;
int A[MAX_N][MAX_N];

int ranged_sum(int x1, int y1, int x2, int y2) {
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	return A[x2][y2] - (x1 ? A[x1 - 1][y2] : 0) - (y1 ? A[x2][y1 - 1] : 0) + (x1 && y1 ? A[x1 - 1][y1 - 1] : 0) + 2500000;
}

int calculate_possible_sum(int x, int y, bool left_top) {
	int ret = 0;
	unordered_map<int, int> sum;

	if (left_top) {
		for (int i = 0; i <= x; i++){
			for (int j = 0; j <= y; j++) {
				sum[ranged_sum(i, j, x, y)]++;
			}
		}

		for (int i = x + 1; i < N; i++) {
			for (int j = y + 1; j < N; j++) {
				int tmp = sum[ranged_sum(x + 1, y + 1, i, j)];
				ret += tmp;
			}
		}
	}
	else {
		for (int i = 0; i <= x; i++) {
			for (int j = y + 1; j < N; j++) {
				sum[ranged_sum(x, y + 1, i, j)]++;
			}
		}

		for (int i = x + 1; i < N; i++) {
			for (int j = 0; j <= y; j++) {
				int tmp = sum[ranged_sum(x + 1, y, i, j)];
				ret += tmp;
			}
		}

	}
	return ret;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++) {
			scanf("%d", &A[i][j]);
			if (j) A[i][j] += A[i][j - 1];
			if (i) A[i][j] += A[i - 1][j];
			if (i && j) A[i][j] -= A[i - 1][j - 1];
		}
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1; j++) {
			ans += calculate_possible_sum(i, j, true);
			ans += calculate_possible_sum(i, j, false);
		}
	}

	printf("%d", ans);
}
