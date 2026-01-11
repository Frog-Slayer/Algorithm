#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

#define fastio cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;

vector<int> binarize(string s) { 
	vector<int> binarized;
	binarized.reserve(s.length() * 5);

	for (char c : s) { 
		int i = c - 'A' + 1;
		if (c == ' ') i = 0;

		for (int bit = 4; bit >= 0; bit--) {
			binarized.push_back((i >> bit) & 1);
		}
	}

	return binarized;
}

void solve(int r, int c, string s) { 
	vector<int> binarized = binarize(s);
	vector<vector<int>> v(r, vector<int>(c, -1));

	int idx = 0, x = 0, y = 0, dir = 0;
	vector<int> dx = {0, 1, 0, -1};
	vector<int> dy = {1, 0, -1, 0};

	while (idx < binarized.size()) { 
		v[x][y] = binarized[idx++];

		int nx = x + dx[dir], ny = y + dy[dir];
		
		if (nx < 0 || ny < 0 || nx >= r || ny >= c || v[nx][ny] >= 0) { 
			dir = (dir + 1) % 4;
		}

		x += dx[dir], y += dy[dir];

	}

	for (auto &row : v) { 
		for (int & i : row) { 
			cout << (i > 0);
		}
	}

	cout << '\n';
}

int main() { 
	fastio;

	int T;
	cin >> T;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (T--) { 
		string line;
		getline(cin, line);

		int r = 0, c = 0;
		int i = 0;

		while (i < line.size() && line[i] == ' ') i++;
		while (i < line.size() && isdigit(line[i]))
			r = r * 10 + (line[i++] - '0');

		while (i < line.size() && line[i] == ' ') i++;
		while (i < line.size() && isdigit(line[i]))
			c = c * 10 + (line[i++] - '0');

		i++;
		string s = line.substr(i);

		solve(r, c, s);
	}
}
