#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

struct Hongjoon{
	pair<int, int> pos = {0, 0};
	vector<pair<int, int>> v = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	int dir = 0;

	void rotate(char c) {
		if (c == 'R') dir++;
		else dir--;

		dir = (dir + 4) % 4;
	}

	void forward() {
		pos = { pos.first + v[dir].first, pos.second + v[dir].second};
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	string s;
	cin >> s;

	Hongjoon hj;
	set<pair<int, int>> st;

	st.emplace(hj.pos);

	int min_x = 0, min_y = 0, max_x = 0, max_y = 0;

	for (int i = 0; i < N; i++) {
		if (s[i] == 'F') hj.forward();
		else hj.rotate(s[i]);

		st.emplace(hj.pos);

		int x = hj.pos.first, y = hj.pos.second;

		min_x = min(min_x, x);
		min_y = min(min_y, y);
		max_x = max(max_x, x);
		max_y = max(max_y, y);
	}

	for (int i = min_x; i <= max_x; i++) {
		for (int j = min_y; j <= max_y; j++) {
			if (st.find(make_pair(i, j)) != st.end()) cout << '.';
			else cout << '#';
		}

		cout << '\n';
	}


}