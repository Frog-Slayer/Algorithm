#include <iostream>
using namespace std;

int N, e;
int guilty[16];
int R[16][16];

void vote(int i, bool cancel) {
	for (int j = 0; j < N; j++) {
		guilty[j] += R[i][j] * (cancel ? -1 : 1);
	}
}

int solve(int flag, int left, int day){
	if (flag & (1 << e)) return day;
	if (left == 1) return day;
	int ret = day;

	if (left % 2) {//낮
		int most_guilty = -200, idx = -1;

		for (int i = 0; i < N; i++) {
			if (flag & (1 << i)) continue;
			if (guilty[i] > most_guilty) {
				most_guilty = guilty[i];
				idx = i;
			}
		}

		if (idx == e) return day;
		if (left == 2) return day;
		return solve(flag | (1 << idx), left - 1, day + 1);
	}
	else {//밤
		for (int i = 0; i < N; i++) {
			if (flag & (1 << i)) continue;

			vote(i, false);
			int new_flag = flag | (1 << i);

			ret = max(ret, solve(new_flag, left - 1, day));
			vote(i, true);
		}
	}
	return ret;
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++) scanf("%d", &guilty[i]);

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++) {
			scanf("%d", &R[i][j]);
		}
	}

	scanf("%d", &e);

	printf("%d", solve(0, N, !(N % 2)));
}