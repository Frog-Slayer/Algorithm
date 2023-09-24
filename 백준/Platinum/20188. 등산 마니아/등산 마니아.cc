#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 300001;
int N, x, y;
long long ans;
vector<vector<int>> adj;
vector<vector<int>> child;

int makeTree(int root, int parent){
	int size = 1;
	for (auto c : adj[root]){
		if (c == parent) continue;
		child[root].push_back(c);
		long long subSize = makeTree(c, root);
		size += subSize;
		ans += 1LL * subSize * (N - subSize) + subSize * (subSize - 1) / 2;
	}
	return size; 
}

int main(){
	scanf("%d", &N);
	adj.resize(N + 1);
	child.resize(N + 1);
	for (int i = 0; i < N - 1; i++){
		scanf("%d%d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	makeTree(1, 0);

	printf("%lld", ans);
}