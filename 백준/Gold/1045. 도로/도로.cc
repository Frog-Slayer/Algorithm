#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 50;

int parent[MAX_N], cnt[MAX_N];
int N, M;
char adj[MAX_N][MAX_N + 1];
vector<pair<int, int>> v, rest;

int find(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

bool uni(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	parent[a] = b;
	return true;
}

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		parent[i] = i;
		scanf("%s", adj[i]);
		for (int j = 0; j < N; j++) if (adj[i][j] == 'Y' && i < j) v.emplace_back(i, j);
	}

	int edge_cnt = 0;

	for (auto &p : v) {
		if (uni(p.first, p.second)) {
			edge_cnt++;
			cnt[p.first]++;
			cnt[p.second]++;
		}
		else rest.push_back(p);
	}

	if (edge_cnt != N - 1) printf("-1");
	else {
		int t = M - N + 1;

		for (int i = 0; i < min((int)rest.size(), t); i++) {
			cnt[rest[i].first]++;
			cnt[rest[i].second]++;
			edge_cnt++;
		}
		
		if (edge_cnt == M) for (int i = 0; i < N; i++) printf("%d ", cnt[i]); 
		else printf("-1");
	}
}
