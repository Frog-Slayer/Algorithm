#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
typedef long long ll;

ll sentoryoku(vector<ll> &v) { 
	ll ad = v[0], str = v[1], crit_rate = v[2], crit_dmg = v[3], as = v[4];

	return ad * (100 + str) * (100 * (100 - min(crit_rate, 100LL)) + min(crit_rate, 100LL) * crit_dmg) * (100 + as);
}

void compare_and_print(ll org, ll after_swap){ 
	if (org == after_swap) cout << "0\n";
	else if (org < after_swap) cout << "+\n";
	else cout << "-\n";
}

int main() { 
	fastio;

	vector<vector<ll>> v(4, vector<ll>(5));
	vector<ll> atk(4);

	for (int i = 0; i < 4; i++) { 
		for (int j = 0; j < 5; j++) { 
			cin >> v[i][j];
		}
		atk[i] = sentoryoku(v[i]);
	}

	for (int i = 0; i < 5; i++) { 
		v[0][i] = v[0][i] - v[2][i] + v[3][i];
		v[1][i] = v[1][i] - v[3][i] + v[2][i];
	}

	atk[2] = sentoryoku(v[0]), atk[3] = sentoryoku(v[1]);

	compare_and_print(atk[0], atk[2]);
	compare_and_print(atk[1], atk[3]);
}