#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<vector<int>> edges(501);
vector<int> match(501);
vector<bool> visited(501);

bool dfs(int x) { 
	for (int y : edges[x]) { 
		if (visited[y]) continue;
		visited[y] = true;
		if (!match[y] || dfs(match[y])) { 
			match[y] = x;
			return true;
		}
	}

	return false;
}

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<int> xx, yy;

	for (int i = 0; i < N; i++) { 
		int x, y;
		cin >> x >> y;

		edges[x].emplace_back(y);
		xx.emplace_back(x);
		yy.emplace_back(y);
	}

	sort(all(xx));
	xx.erase(unique(all(xx)), xx.end());

	sort(all(yy));
	yy.erase(unique(all(yy)), yy.end());

	int cnt = 0;

	for (int i = 1; i <= 500; i++) { 
		fill(all(visited), false);
		if (dfs(i)) cnt++;
	}

	if (xx.size() == yy.size() && xx.size() == cnt) cout << "Slavko";
	else cout << "Mirko";
}