#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int R, C;
	cin >> R >> C;

	vector<string> v(R);

	for (int i = 0; i < R; i++) cin >> v[i];

	set<string> string_set;

	for (int i = 0; i < R; i++) {
		string s;

		for (int j = 0; j <= C; j++) {
			if (j == C || v[i][j] == '#'){
				if (s.length() > 1) string_set.insert(s); 
				s = "";
				continue;
			}
			else s = s + v[i][j];
		}
	}
	

	for (int i = 0; i < C; i++) {
		string s;
		for (int j = 0; j <= R; j++) {
			if (j == R || v[j][i] == '#'){
				if (s.length() > 1) string_set.insert(s); 
				s = "";
				continue;
			}
			else s = s + v[j][i];
		}
	}

	cout << *string_set.begin();

}

