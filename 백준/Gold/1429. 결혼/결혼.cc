#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

const int INF = 100;

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<vector<bool>> v(N, vector<bool>(M));
	vector<int> man_cover(N), lady_cover(M);

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;

		for (int j = 0; j < M; j++){
			if (s[j] == '1') {
				man_cover[i] |= (1 << j);
				lady_cover[j] |= (1 << i);
			}
		}
	}

	int ans = INF; 

	for (int i = 0; i < N; i++) if (!man_cover[i]) ans = -1;
	for (int i = 0; i < M; i++) if (!lady_cover[i]) ans = -1;

	for (int i = 0; i < (1 << N); i++) {

		for (int j = 0; j < (1 << M); j++) {
			int man = i, lady = j;//married
			
			for (int k = 0; k < N; k++) {
				if (i & (1 << k)) lady |= man_cover[k]; 
			}

			for (int k = 0; k < M; k++) {
				if (j & (1 << k)) man |= lady_cover[k]; 
			}

			if (man == (1 << N) - 1 && lady == (1 << M) - 1) {
				ans = min(ans, __builtin_popcount(i) + __builtin_popcount(j));
			}
		}
	}

	cout << (ans == INF? -1 : ans);

}
