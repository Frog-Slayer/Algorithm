#include <iostream>
#include <bitset>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int L, N, M;
pair<int, int> pos[5], sz[5];
vector<int> v;
bool has_answer;
char buffer[11], ans_map[101], tmp_map[101];
bitset<100> bs, piece[5], tmp, ans;

bool push(int p) {
	for (int i = 0; i < L * L; i++) {
		int row = i / L, col = i % L;
		N = sz[p].first, M = sz[p].second;

		if (row + N > L || col + M > L) continue; 
		if ((bs & (piece[p] << i)) != 0) continue;
		if (((bs | (piece[p] << i)) & (~ans)) != 0) continue;
		
		bs |= (piece[p] << i);
		pos[p] = {row, col};
		return true;
	}

	return false;
}

void solve(){
	bool can_push_all = true;
	bs = 0;

	for (int p = 0; p < 5 && can_push_all; p++) {
		if (!push(v[p])){
			can_push_all= false;
			break;
		}
	}

	if (can_push_all) {
		for (int k = 0; k < 5; k++) {
			int p = v[k];
			int x = pos[p].first, y = pos[p].second;
			N = sz[p].first, M = sz[p].second;

			for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
					if (piece[p][i * L + j]) tmp_map[(i + x) * L + j + y] = (p + 1) + '0';
			}
		}
		
		if (!ans_map[0] || strcmp(tmp_map, ans_map) < 0) memcpy(ans_map, tmp_map, L * L);
		has_answer = true;
	}
}

int main() {
	scanf("%d", &L);

	for (int i = 0; i < L * L; i++) {
		ans <<= 1;
		ans |= 1;
	}

	int cnt = 0;

	for (int i = 0; i < 5; i++) {
		scanf("%d%d", &N, &M);
		sz[i] = { N, M };
		v.emplace_back(i);

		for (int j = 0; j < N; j++) {
			scanf("%s", buffer);
			tmp = 0;

			for (int k = 0; k < M; k++) {
				if (buffer[k] == '#') tmp |= (1 << k), cnt++;
			}

			for (int k = 0; k < j; k++) tmp <<= L;
			piece[i] |= tmp;
		}
	}

	if (cnt != L * L) {
		printf("gg");
		return 0;
	}

	do {
		solve();
	} while (next_permutation(v.begin(), v.end()));

	if (has_answer) {
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < L; j++) {
				printf("%c", ans_map[i * L + j]);
			}
			printf("\n");
		}
	}
	else printf("gg");
}