#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

bool check(int limit, vector<vector<int>> &row_cut, int col_cut_limit) {
	int r = row_cut.size(), c = row_cut[0].size();
	int max_sum = 0, cnt = 0;

	vector<int> sums(r, 0);

	for (int i = 0; i < c; i++) {
		bool is_possible = true;
		for (int j = 0; j < r; j++) {
			if (sums[j] + row_cut[j][i] > limit) {
				is_possible = false;
				break;
			}
		}

		for (int j = 0; j < r; j++) {
			if (is_possible) sums[j] += row_cut[j][i];
			else sums[j] = row_cut[j][i];

			max_sum = max(max_sum, sums[j]);
		}

		if (!is_possible) cnt++;
	}

	return cnt <= col_cut_limit && max_sum <= limit;
}

int main() {
	//fastio;
	
	int N, M, R, S;
	cin >> N >> M >> R >> S;

	vector<vector<int>> v(N, vector<int>(M));

	int sum = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> v[i][j];
			sum += v[i][j];
		}
	}

	int ans = sum;

	vector<bool> row_cut(N - 1);

	for (int i = 0; i < R; i++) row_cut[N - 2 - i] = 1;

	do {
		vector<vector<int>> prefix_sum_row_cut(R + 1, vector<int>(M));

		int row = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) prefix_sum_row_cut[row][j] += v[i][j];
			if (row_cut[i]) row++;
		}

		int left = 0, right = sum;

		while (left <= right) {
			int mid = (left + right) / 2;

			if (check(mid, prefix_sum_row_cut, S)){
				right = mid - 1;	
				ans = min(ans, mid);
			}
			else left = mid + 1;
		}
	}
	while (next_permutation(all(row_cut)));


	cout << ans;
}
