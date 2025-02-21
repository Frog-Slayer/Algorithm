#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef tuple<char, int, int> edge;

struct Union_Find {
	vector<int> parent;

	Union_Find(int n) : parent(n + 1) {
		for (int i = 1; i <= n; i++) parent[i] = i;
	}

	int find(int a) {
		if (parent[a] == a) return a;
		return parent[a] = find(parent[a]);
	}

	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		parent[a] = b;

		return true;
	}
};

int kruskal(vector<edge> &edges, int n) {
	Union_Find uf(n);
	int ret = 0;

	for (auto &[c, f, t]: edges) {
		if (uf.merge(f, t) == true && c == 'B') ret++;
	}

	return ret;
}

int main() {
	fastio;

	while (true) {
		int n, m, k;
		cin >> n >> m >> k;

		if (!n) return 0;

		vector<tuple<char, int, int>> edges;

		for (int i = 0; i < m; i++) {
			char c;
			int f, t;
			cin >> c >> f >> t;

			edges.emplace_back(c, f, t);
		}

		sort(all(edges));
		int max_blue = kruskal(edges, n);

		sort(all(edges), greater<>());
		int min_blue = kruskal(edges, n);

		int ans = min_blue <= k && k <= max_blue;

		cout << ans << '\n';
	}

}
