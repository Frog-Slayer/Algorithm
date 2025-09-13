#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<int> parent, group;
vector<set<int>> color;

int find(int a) { 
	if (a == group[a]) return a;
	return group[a] = find(group[a]);
}

void merge(int a, int b) { 
	a = find(a), b = find(b);
	if (a == b) return;
	if (color[a].size() < color[b].size()) swap(a, b);
	group[b] = a;
	color[a].merge(color[b]);
}

int main() {
	fastio;

	int N, Q;
	cin >> N >> Q;

	parent.resize(N + 1);
	group.resize(N + 1);
	color.resize(N + 1);

	for (int i = 2; i <= N; i++) cin >> parent[i];
	for (int i = 1; i <= N; i++) { 
		group[i] = i;
		int c;
		cin >> c;

		color[i].emplace(c);
	}

	vector<tuple<int, int>> queries;

	for (int i = 0; i < N - 1 + Q; i++) { 
		int q, a;
		cin >> q >> a;

		queries.emplace_back(q, a);
	}

	reverse(all(queries));

	vector<int> ans;

	for (auto [q, a] : queries) { 
		if (q == 1) merge(a, parent[a]);
		else ans.emplace_back(color[find(a)].size());
	}

	reverse(all(ans));

	for (int a : ans) cout << a << '\n';
}
