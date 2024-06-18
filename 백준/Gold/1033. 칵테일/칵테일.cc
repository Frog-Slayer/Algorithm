#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX_N = 10;
int N, visited;
int ans[MAX_N];
vector<vector<int>> adj;

int gcd(int a, int b) {
	int r;
	if (a < b) swap(a, b);

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void dfs(int a, int val) {
	if (visited & (1 << a)) return;
	visited |= (1 << a);
	ans[a] *= val;

	for (int b : adj[a]){
		if (!(visited & (1 << b))) dfs(b, val);
	}
}

int main(){
	scanf("%d", &N);
	adj.resize(N);

	for (int i = 0; i < N; i++) ans[i] = 1;

	for (int i = 0; i < N - 1; i++) {
		int a, b, p, q;
		scanf("%d%d%d%d", &a, &b, &p, &q);
	
		int g = gcd(ans[a], ans[b]);
        
		int a_m = ans[b] / g * p;
		int b_m = ans[a] / g * q;

		g = gcd(a_m, b_m);

		a_m /= g;
		b_m /= g;

		visited = 0;
		dfs(a, a_m);
		dfs(b, b_m);

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 0; i < N; i++) printf("%d ", ans[i]);
}