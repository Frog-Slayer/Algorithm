#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<int> parent;
vector<vector<int>> enemy;

int find(int a) { 
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

void merge(int a, int b) { 
	a = find(a), b = find(b);
	if (a == b) return;
	parent[a] = b;
}

int main() {
	fastio;

	int n, m;
	cin >> n >> m;

	parent.resize(n + 1);
	enemy.resize(n + 1);

	for (int i = 1; i <= n; i++) parent[i] = i;

	for (int i = 0; i < m; i++) { 
		char ef;
		int p, q;
		cin >> ef >> p >> q;

		if (ef == 'F') merge(p, q);
		else { 
			enemy[p].emplace_back(q);
			enemy[q].emplace_back(p);
		}
	}

	for (int i = 1; i <= n; i++) { 
		for (int e : enemy[i]) { 
			for (int j : enemy[e]) { 
				merge(i, j);
			}
		}
	}

	for (int i = 1; i <= n; i++) parent[i] = find(i);

	sort(all(parent));
	parent.erase(unique(all(parent)), parent.end());

	cout << parent.size() - 1;
}
