#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int main() { 
	fastio;

	double prob[8][8];

	for (int i = 0; i < 8; i++) { 
		for (int j = i + 1; j < 8; j++) { 
			cin >> prob[i][j];
			prob[i][j] /= 100;
			prob[j][i] = 1 - prob[i][j];
		}
	}

	double win_rate[3][8];// [i][j] = 2^i강에 j가 올라갈 확률

	for (int i = 0; i < 8; i += 2) { 
		win_rate[2][i] = prob[i][i + 1];
		win_rate[2][i + 1] = prob[i + 1][i];
	}

	for (int i = 0; i < 8; i += 4) { 
		win_rate[1][i] = win_rate[2][i] * (win_rate[2][i + 2] * prob[i][i + 2] + win_rate[2][i + 3] * prob[i][i + 3]);
		win_rate[1][i + 1] = win_rate[2][i + 1] * (win_rate[2][i + 2] * prob[i + 1][i + 2] + win_rate[2][i + 3] * prob[i + 1][i + 3]);
		win_rate[1][i + 2] = win_rate[2][i + 2] * (win_rate[2][i] * prob[i + 2][i] + win_rate[2][i + 1] * prob[i + 2][i + 1]);
		win_rate[1][i + 3] = win_rate[2][i + 3] * (win_rate[2][i] * prob[i + 3][i] + win_rate[2][i + 1] * prob[i + 3][i + 1]);
	}

	auto pb = [&](std::initializer_list<int> v, int me) { 
		double ret = 0;

		for (auto i : v) {
			ret += win_rate[1][i] * prob[me][i];
		}

		return ret;
	};

	for (int i = 0; i < 8; i++) { 
		if (i < 4) { 
			win_rate[0][i] = win_rate[1][i] * pb({4, 5, 6, 7}, i);
		} else { 
			win_rate[0][i] = win_rate[1][i] * pb({0, 1, 2, 3}, i);
		}
	}

	cout << fixed;
	cout.precision(14);

	for (int i = 0; i < 8; i++) { 
		cout << win_rate[0][i] << ' ';
	}

}