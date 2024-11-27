#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

struct Union_Find {
	vector<int> parent;

	Union_Find(int N) : parent(N + 1) {
		for (int i = 1; i <= N; i++) parent[i] = i;
	}

	int find(int a) {
		if (a == parent[a]) return a;
		return parent[a] = find(parent[a]);
	}

	void merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		parent[a] = b;
	}

};

int main() {
	fastio;
	
	int V, E;
	cin >> V >> E;

	Union_Find uf(V);

	vector<int> degree(V + 1);

	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		degree[a]++;
		degree[b]++;

		uf.merge(a, b);
	}

	int ans = 0;

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j < i; j++) {
			if (uf.find(i) == uf.find(j)) continue;
			if (!(degree[i] & 1) && degree[i]) continue;
			if (!(degree[j] & 1) && degree[j]) continue;
			uf.merge(i, j);
			degree[i]++; degree[j]++;
			ans++;
		}
	}

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j < i; j++) {
			if (uf.find(i) == uf.find(j)) continue;
			uf.merge(i, j);
			degree[i]++; degree[j]++;
			ans++;
		}
	}

	int cnt = 0;

	for (int i = 1; i <= V; i++) cnt += (degree[i] & 1);

	if (cnt > 2) ans += (cnt - 2)/2;

	cout << ans;

}