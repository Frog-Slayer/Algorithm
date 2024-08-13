#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int N, M;
map<string, int> cnt;
vector<pair<string, int>> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		if (s.length() >= M) cnt[s]++;
	}

	for (auto p : cnt) v.push_back(p);

	sort(v.begin(), v.end(), [](auto &p1, auto &p2) {
			if (p1.second != p2.second) return p1.second > p2.second;
			if (p1.first.length() != p2.first.length()) return p1.first.length() > p2.first.length();
			return p1.first < p2.first;
			});


	for (auto &p : v) cout << p.first << '\n';
}