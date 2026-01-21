#include <iostream>
#include <queue>

using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

bool same(vector<int> &shape, vector<int>& sample, vector<int> &sample2) { 
	int N = shape.size();

	for (int i = 0; i < N; i++) { 
		if (shape[i] == sample[0]) { 
			bool is_same = true;

			for (int j = 0; j < N; j++) { 
				if (shape[(i + j) % N] != sample[j]) { 
					is_same = false;
					break;
				}
			}

			if (is_same) return true;
		}
		
		if (shape[i] == sample2[0]) { 
			bool is_same = true;

			for (int j = 0; j < N; j++) { 
				if (shape[(i + j) % N] != sample2[j]) { 
					is_same = false;
					break;
				}
			}

			if (is_same) return true;
		}
	}

	return false;
}



int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> sample(N);
	vector<int> sample2;

	for (int i = 0; i < N; i++) cin >> sample[i];

	for (int i = N - 1; i >= 0; i--) { 
		sample2.emplace_back((sample[i] + 1) % 4 + 1);
	}

	int T;
	cin >> T;

	vector<vector<int>> ans;

	for (int i = 0; i < T; i++) {
		vector<int> shape(N);

		for (int j = 0; j < N; j++) cin >> shape[j]; 
		if (same(shape, sample, sample2)) ans.emplace_back(shape);
	}

	cout << ans.size() << '\n';

	for (auto &v : ans) { 
		for (auto &i : v) cout << i << ' ';
		cout << '\n';
	}
}
