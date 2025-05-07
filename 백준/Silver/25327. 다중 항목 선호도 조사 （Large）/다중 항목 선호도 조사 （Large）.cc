#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	int cnt[4][4][4] = {0, };

	map<string, int> s, f, c;
	s.emplace("-", 0);
	f.emplace("-", 0);
	c.emplace("-", 0);

	for (int i = 0; i < N; i++) {
		string sub, fruit, color;
		cin >> sub >> fruit >> color;

		if (s.find(sub) == s.end()) s.emplace(sub, s.size());
		if (f.find(fruit) == f.end()) f.emplace(fruit, f.size());
		if (c.find(color) == c.end()) c.emplace(color, c.size());

		for (int i : {0, s[sub]}) {
			for (int j : {0, f[fruit]}) {
				for (int k : {0, c[color]}) {
					cnt[i][j][k]++;
				}
			}
		}
	}

	for (int i = 0; i < M; i++) {
		string sub, fruit, color;
		cin >> sub >> fruit >> color;

		if (s.find(sub) == s.end()) s.emplace(sub, s.size());
		if (f.find(fruit) == f.end()) f.emplace(fruit, f.size());
		if (c.find(color) == c.end()) c.emplace(color, c.size());

		cout << cnt[s[sub]][f[fruit]][c[color]] << '\n';
	}

	
}
