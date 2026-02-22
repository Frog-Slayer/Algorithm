#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef long long ll;

int calc(int si, int sj, int ei, int ej, vector<vector<int>> pond) { 
	int d = pond.size(), w = pond[0].size();
	int min_elv = 10;
	int ret = 0;

	for (int i = si; i <= ei; i++) { 
		min_elv = min(min_elv, pond[i][sj]);
		min_elv = min(min_elv, pond[i][ej]);
	}

	for (int j = sj; j <= ej; j++) { 
		min_elv = min(min_elv, pond[si][j]);
		min_elv = min(min_elv, pond[ei][j]);
	}


	for (int i = si + 1; i < ei; i++) { 
		for (int j = sj + 1; j < ej; j++) { 
			if (pond[i][j] < min_elv) ret += min_elv - pond[i][j];
			else return 0;
		}
	}

	return ret;
}

int main() { 
	fastio;

	while (true) { 
		int d, w;
		cin >> d >> w;

		if (!d && !w) break;

		vector<vector<int>> pond(d, vector<int>(w));

		for (int i = 0; i < d; i++) { 
			for (int j = 0; j < w; j++) { 
				cin >> pond[i][j];
			}
		}

		int ans = 0;

		for (int i = 0; i < d; i++) { 
			for (int j = 0; j < w; j++) { 
				for (int ni = i + 2; ni < d; ni++) { 
					for (int nj = j + 2; nj < w; nj++) { 
						ans = max(ans, calc(i, j, ni, nj, pond));
					}
				}
			}
		}

		cout << ans << '\n';


	}

}
